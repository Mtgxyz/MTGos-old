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
#define ALTCMD 0x206
namespace MTGosHAL {
  IDE::IDE(uint16_t baseport, uint8_t num): baseport(baseport), num(num), existent(0), numDevices(0) {
    if(inb(baseport+CMD)!=0xFF) { //Does the ATA controller return floating bus?
      // Checking existence of the master
      outb(baseport+DRV, 0xE0);
      outb(baseport+LBAlo,0x55);
      if(inb(baseport+LBAlo)==0x55) {
        existent|=1;
        numDevices++;
      }
      // Checking existence of the slave
      outb(baseport+DRV, 0xF0);
      outb(baseport+LBAlo,0x55);
      if(inb(baseport+LBAlo)==0x55) {
        existent|=2;
        numDevices++;
      }
    } else {
      //err << "ATA device could not be found!\n";
    }
    outb(baseport+ALTCMD,0x40);
    inb(baseport+CMD);
    inb(baseport+CMD);
    inb(baseport+CMD);
    outb(baseport+ALTCMD,0x00);
  }
  auto IDE::getDriveCnt() -> int32_t {return numDevices;}
  auto IDE::getDriveNumByName(const char* name) -> int32_t {
    if(strlen(name)!=5)
      return -1; //Format is ATA[0-3][sm] (regex)
    if((name[0]!=name[2])||(name[2]!='A'))
      return -1;
    if(name[1]!='T')
      return -1;
    int32_t drivenum=name[3]-0x30;
    if(drivenum!=num)
      return -1;
    if((name[4]!='s')&&(name[4]!='m'))
      return -1;
    drivenum<<=1;
    drivenum+=(name[4]=='s')?1:0;
    if(!(existent&(1<<drivenum)))
      return -1;
    return drivenum;
  }
  auto IDE::readSector(int32_t drive, uint64_t sectorNum, uint8_t *buf) -> void {
    if(drive<(num*2)||drive>(num*2+1))
      return;
    if(!(existent&(1<<(drive-num*2))))
      return;
    outb(baseport+DRV, 0x40 | (drive&1)<<4);
    outb(baseport+SECTOR_CNT, 0);
    outb(baseport+LBAlo, (uint8_t)(sectorNum>>24));
    outb(baseport+LBAmid, (uint8_t)(sectorNum>>32));
    outb(baseport+LBAhi, (uint8_t)(sectorNum>>40));
    outb(baseport+SECTOR_CNT, 1);
    outb(baseport+LBAlo, (uint8_t)(sectorNum));
    outb(baseport+LBAmid, (uint8_t)(sectorNum>>8));
    outb(baseport+LBAhi, (uint8_t)(sectorNum>>16));
    outb(baseport+CMD, 0x24);
    inb(baseport+CMD);
    inb(baseport+CMD);
    inb(baseport+CMD);
    while(inb(baseport+CMD)&0x80);
    uint16_t *bufw=(uint16_t *)buf;
    asm volatile ("rep insw" : : "D"((int)bufw),"d"(baseport),"c"(256));
  }
}
