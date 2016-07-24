#ifndef __HAL_BLOCKDEV_HPP
#define __HAL_BLOCKDEV_HPP
#include <stdint.h>
namespace MTGosHAL {
  class BlockDevice {
  private:
    uint8_t numDevices;
  public:
    BlockDevice();
    ~BlockDevice();
    auto getDriveCnt() -> int32_t;
    auto getDriveNumByName(const char *) -> int32_t; //Returns -1 if device is not existent
    auto readSector(int32_t drv, uint64_t sectorNum, uint8_t *buf) -> void; //Has to be at least 512 bytes big!
    auto readSector(int32_t drv, uint64_t sectorNum, uint32_t num, uint8_t *buf) -> void; //Has to be at least num*512 bytes big!
    auto writeSector(int32_t drv, uint64_t sectorNum, uint8_t *buf) -> void;
    auto writeSector(int32_t drv, uint64_t sectorNum, uint32_t num, uint8_t *buf) -> void;
  };
}


#endif /* end of include guard: __HAL_BLOCKDEV_HPP */
