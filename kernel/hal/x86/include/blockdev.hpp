#ifndef __HAL_BLOCKDEV_HPP
#define __HAL_BLOCKDEV_HPP
#include <stdint.h>
namespace MTGosHAL {
  class IDE {
  private:
    uint8_t existent; //Bitmap showing which of the up to 2 drives are actually existent.
    uint8_t num;
    int32_t numDevices;
    uint16_t baseport;
    IDE() {}
  public:
    IDE(uint16_t baseport, uint8_t num);
    auto getDriveCnt() -> int32_t;
    auto getDriveNumByName(const char *) -> int32_t;
    auto readSector(int32_t drv, uint64_t sectorNum, uint8_t *buf) -> void; //Has to be at least 512 bytes big!
    auto readSectors(int32_t drv, uint64_t sectorNum, uint32_t num, uint8_t *buf) -> void; //Has to be at least num*512 bytes big!
  };
  class BlockDevice {
  private:
    uint8_t numDevices;
    IDE ata0;
    IDE ata1;
    IDE ata2;
    IDE ata3;
  public:
    BlockDevice();
    ~BlockDevice();
    auto getDriveCnt() -> int32_t;
    auto getDriveNumByName(const char *) -> int32_t; //Returns -1 if device is not existent
    auto readSector(int32_t drv, uint64_t sectorNum, uint8_t *buf) -> void; //Has to be at least 512 bytes big!
    auto readSectors(int32_t drv, uint64_t sectorNum, uint32_t num, uint8_t *buf) -> void; //Has to be at least num*512 bytes big!

  };
}


#endif /* end of include guard: __HAL_BLOCKDEV_HPP */
