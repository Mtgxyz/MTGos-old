#include <stdint.h>
#include <base.hpp>
#include <blockdev.hpp>
#include <textDISP.hpp>
#include <partitions.hpp>
using namespace MTGosHAL;
union EBPB {
    struct {
        uint8_t drivenum;
        uint8_t ntflags;
        uint8_t signature;
        uint32_t volID;
        uint8_t label[11];
        uint8_t sysident[8];
        uint8_t bootcode[448];
        uint16_t magic;
    }__attribute__((packed)) fat;
    struct {
        uint32_t sectorsPerFAT;
        uint16_t flags;
        uint16_t version;
        uint32_t rootdirClusterNum;
        uint16_t FSInfoSector;
        uint16_t backupSector;
        uint8_t reserved[12];
        uint8_t drivenum;
        uint8_t ntflags;
        uint8_t signature;
        uint32_t volumeID;
        uint8_t label[11];
        uint8_t sysident[8];
        uint8_t bootcode[420];
        uint16_t magic;
    }__attribute__((packed)) fat32;
};
struct BPB {
    uint8_t jmp[3];
    uint8_t OEM[8];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t numberFAT;
    uint16_t numDirent;
    uint16_t totalSectors_s;
    uint8_t mdt;
    uint16_t sectorsPerFAT;
    uint16_t sectorsPerTrack;
    uint16_t noHeads;
    uint32_t noHiddenSectors;
    uint32_t totalSectors_b;
    EBPB ebpb;
}__attribute__((packed));
struct dirent {
    uint8_t filename[11];
    uint8_t flags;
    uint8_t reserved;
    uint8_t creationTenth;
    uint16_t creationTime;
    uint16_t creationDate;
    uint16_t accessDate;
    uint16_t hiClusterNUM;
    uint16_t modifyTime;
    uint16_t modifyDate;
    uint16_t clusterNUM;
    uint32_t fileSize;
}__attribute__((packed));
void readFAT() {
    BPB bpb;
    MBR::MBR part(disk.getDriveNumByName("ATA0m"));
    disk.readSector(disk.getDriveNumByName("ATA0m"),part.getPartBeg(0),(uint8_t*)&bpb);
    out << "Bytes Per Sector: " << (int) bpb.bytesPerSector << "\n";
    out << "Sectors per Cluster: " << (int) bpb.sectorsPerCluster << "\n";
    out << "Reserved Sectors: " << (int) bpb.reservedSectors << "\n";
    out << "Number of FATs: " << (int) bpb.numberFAT << "\n";
    out << "Number of root directory entries: " << (int) bpb.numDirent << "\n";
    uint32_t totalSectors=(bpb.totalSectors_s)?bpb.totalSectors_s:bpb.totalSectors_b;
    out << "Total sectors: " << (int) totalSectors << "\n";
    uint32_t sectorsPerFAT = (bpb.sectorsPerFAT)?bpb.sectorsPerFAT:bpb.ebpb.fat32.sectorsPerFAT;
    out << "Sectors per FAT: " << (int) sectorsPerFAT << "\n";
    uint32_t sizeRootDir = ((bpb.numDirent * 32) + (bpb.bytesPerSector-1)) / bpb.bytesPerSector;
    out << "Size of root dir: " << (int) sizeRootDir << "\n";
    uint32_t firstDataSector = bpb.reservedSectors + (bpb.numberFAT * sectorsPerFAT) + sizeRootDir;
    out << "First data sector: " << (int) firstDataSector << "\n";
    uint32_t dataSectors = totalSectors - (bpb.reservedSectors + (bpb.numberFAT * sectorsPerFAT) + sizeRootDir);
    out << "Data Sectors: " << (int) dataSectors << "\n";
    uint32_t totalClusters = totalSectors / bpb.sectorsPerCluster;
    out << "Cluster count: " << (int) totalClusters << "\n";
    int fatVer;
    if(totalClusters < 4085)
        fatVer=12;
    else if(totalClusters < 65525)
        fatVer=16;
    else if(totalClusters < 268435445)
        fatVer=28;
    else
        fatVer=32;
    out << "Detected file system type: FAT" << fatVer << "\n";
    if(fatVer==12)
        out << "Congratulations! You are running the worst version of FAT!\n";
    if(fatVer>28) {
        out << "Not implemented\n";
        return;
    }
    out << "Reading root directory\n";
    dirent *buf=(dirent*)new uint8_t[(sizeRootDir*512)];
    disk.readSector(disk.getDriveNumByName("ATA0m"),part.getPartBeg(0)+firstDataSector-sizeRootDir, sizeRootDir, (uint8_t*)buf);
    for(int i=0;i<bpb.numDirent;i++) {
        buf[i].flags=0;
        if(buf[i].fileSize==0)
            continue;
        out << (char*)buf[i].filename << "@"<<(int)buf[i].clusterNUM << " - Size: " << (int)buf[i].fileSize << ".\n";
    }
}