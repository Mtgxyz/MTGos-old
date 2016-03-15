#ifndef __HAL_BLOCKDEV_HPP
#define __HAL_BLOCKDEV_HPP
#include <stdint.h>
namespace MTGosHAL {
  class BlockDevice {
  private:
    uint8_t numDevices;
    uint8_t existent; //Bitmap showing which of the up to 8 drives are actually existent.
  public:
    BlockDevice();
    ~BlockDevice();
    auto getDriveCnt() -> uint8_t;
    auto getDriveNumByName(const char *) -> uint8_t; //Returns -1 if device is not existent
    auto readSector(uint32_t drv, uint64_t sectorNum, uint8_t *buf); //Has to be at least 512 bytes big!
    auto readSectors(uint32_t drv, uint64_t sectorNum, uint32_t num, uint8_t *buf); //Has to be at least num*512 bytes big!

  };
}


#endif /* end of include guard: __HAL_BLOCKDEV_HPP */
