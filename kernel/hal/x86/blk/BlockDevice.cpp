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
  uint16_t ataports[4]={0x1F0,0x170,0x1E8,0x168};
  uint16_t commports[4]={0x3F6,0x376,0x3E6,0x366};
  BlockDevice::BlockDevice(): numDevices(0), existent(0) {
    for(int i=0;i<4;i++) {
      if(inb(ataports[i]+CMD)!=0xFF) {
        outb(ataports[i]+DRV, 0xE0);
        outb(ataports[i]+LBAlo,0x55);
        if(inb(ataports[i]+LBAlo)==0x55) {
          existent|=1<<(i<<1);
          numDevices++;
        }
        outb(ataports[i]+DRV, 0xF0);
        outb(ataports[i]+LBAlo,0x55);
        if(inb(ataports[i]+LBAlo)==0x55) {
          existent|=1<<((i<<1)+1);
          numDevices++;
        }
      }
    }
    if(numDevices==0) {
      err<<"Not a single device was found!\n";
    }
    for(int i=0;i<8;i++) {
      if(!(existent&(1<<i)))
        continue;

    }
  }
  auto BlockDevice::getDriveCnt() -> uint8_t {return numDevices;}
  auto BlockDevice::getDriveNumByName(const char * name) -> uint8_t {
    if(strlen(name)!=5)
      return -1; //Format is ATA[0-3][sl] (regex)
    if((name[0]!=name[2])||(name[2]!='A'))
      return -1;
    if(name[1]!='T')
      return -1;
    uint8_t drivenum=name[3]-0x30;
    if(drivenum>3)
      return -1;
    if((name[4]!='s')&&(name[4]!='l'))
      return -1;
    drivenum<<=1;
    drivenum+=(name[4]=='s')?1:0;
    if(!(existent&(1<<drivenum)))
      return -1;
    return drivenum;
  }
  BlockDevice::~BlockDevice() {};
}