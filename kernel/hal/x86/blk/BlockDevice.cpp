#include <base.hpp>
#include <blockdev.hpp>
#include <io.h>
#include <textDISP.hpp>
#include <string.h>
#define ATAPIO_ERR 0x01
#define ATAPIO_DRQ 0x08
#define ATAPIO_SRV 0x10
#define ATAPIO_DF  0x20
#define ATAPIO_RDY 0x40
#define ATAPIO_BSY 0x80
#define DATA 0
#define ATAPI_RESV 1
#define SECTOR_CNT 2
#define LBAlo 3
#define LBAmid 4
#define LBAhi 5
#define DRV 6
#define CMD 7
namespace MTGosHAL {
BlockDevice::BlockDevice(): numDevices(0), ata0(0x1F0,0), ata1(0x170,1), ata2(0x1E8,2), ata3(0x168,3) {
    if(getDriveCnt()==0) {
        //err<<"Not a single device was found!\n";
    }
}
auto BlockDevice::getDriveCnt() -> int32_t {return ata0.getDriveCnt()+ata1.getDriveCnt()+ata2.getDriveCnt()+ata3.getDriveCnt();}
auto BlockDevice::getDriveNumByName(const char * name) -> int32_t {
    int32_t tmp;
    if((tmp=ata0.getDriveNumByName(name))!=-1)
        return tmp;
    else if((tmp=ata1.getDriveNumByName(name))!=-1)
        return tmp+ata0.getDriveCnt();
    else if((tmp=ata2.getDriveNumByName(name))!=-1)
        return tmp+ata0.getDriveCnt()+ata1.getDriveCnt();
    else if((tmp=ata3.getDriveNumByName(name))!=-1)
        return tmp+ata0.getDriveCnt()+ata1.getDriveCnt()+ata2.getDriveCnt();
    else return -1;
}
BlockDevice::~BlockDevice() {};
auto BlockDevice::readSector(int32_t drv, uint64_t sectorNum, uint8_t *buf) -> void {
    ata0.readSector(drv, sectorNum, buf);
    ata1.readSector(drv, sectorNum, buf);
    ata2.readSector(drv, sectorNum, buf);
    ata3.readSector(drv, sectorNum, buf);
}
auto BlockDevice::readSector(int32_t drv, uint64_t sectorNum, uint32_t num, uint8_t *buf) -> void {
    ata0.readSector(drv, sectorNum, num, buf);
    ata1.readSector(drv, sectorNum, num, buf);
    ata2.readSector(drv, sectorNum, num, buf);
    ata3.readSector(drv, sectorNum, num, buf);
}
auto BlockDevice::writeSector(int32_t drv, uint64_t sectorNum, uint8_t *buf) -> void {
    ata0.writeSector(drv, sectorNum, buf);
    ata1.writeSector(drv, sectorNum, buf);
    ata2.writeSector(drv, sectorNum, buf);
    ata3.writeSector(drv, sectorNum, buf);
}
auto BlockDevice::writeSector(int32_t drv, uint64_t sectorNum, uint32_t num, uint8_t *buf) -> void {
    ata0.writeSector(drv, sectorNum, num, buf);
    ata1.writeSector(drv, sectorNum, num, buf);
    ata2.writeSector(drv, sectorNum, num, buf);
    ata3.writeSector(drv, sectorNum, num, buf);
}
}
