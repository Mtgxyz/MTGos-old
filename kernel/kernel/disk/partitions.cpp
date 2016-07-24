#include <partitions.hpp>
#include <base.hpp>
#include <blockdev.hpp>
namespace MBR {
    struct PartEntry {
        char status;
        uint8_t CHS_start[3];
        char partitionType;
        uint8_t CHS_end[3];
        uint32_t start;
        uint32_t size;
    }__attribute__((packed));
    struct Mbr {
        uint8_t bootstrap[446];
        PartEntry entries[4];
        short bootSignature;
    }__attribute__((packed));
MBR::MBR(uint32_t drive_id):Partitions(drive_id) {
    Mbr mbr;
    MTGosHAL::disk.readSector(drive_id,0,(uint8_t*)&mbr);
    for(int i=0;i<4;i++) {
        if(mbr.entries[i].status&0x7F)
            break;
        count++;
        beg[i]=mbr.entries[i].start;
        end[i]=beg[i]+mbr.entries[i].size;
    }
}
auto MBR::operator=(MBR &o) -> MBR&{
    for(int i=0;i<4;i++) {
        this->beg[i]=o.beg[i];
        this->end[i]=o.end[i];
    }
    Partitions::operator=(o);
    return *this;
}
auto MBR::getPartCount() -> int {
    return count;
}
auto MBR::getPartBeg(int part) -> uint64_t {
    if(part>=count)
        return 0xFFFFFFFFFFFFFFFFull;
    return beg[part];
}
auto MBR::getPartEnd(int part) -> uint64_t {
    if(part>=count)
        return 0xFFFFFFFFFFFFFFFFull;
    return end[part];
}
}