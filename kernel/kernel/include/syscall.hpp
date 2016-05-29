#ifndef _SYSCALL_HPP
#define _SYSCALL_HPP
#include <stdint.h>
enum class BGColor : uint32_t {
  BLACK=0x000000,
  BLUE=0x0000AA,
  GREEN=0x00AA00,
  CYAN=0x00AAAA,
  RED=0xAA0000,
  MAGENTA=0xAA00AA,
  BROWN=0xAA5500,
  LIGHT_GREY=0xAAAAAA,
  GREY=0x555555,
  LIGHT_BLUE=0x5555FF,
  LIGHT_GREEN=0x55FF55,
  LIGHT_CYAN=0x55FFFF,
  LIGHT_RED=0xFF5555,
  LIGHT_MAGENTA=0xFF55FF,
  YELLOW=0xFFFF55,
  WHITE=0xFFFFFF
};
enum class FGColor : uint32_t {
  BLACK=0x000000,
  BLUE=0x0000AA,
  GREEN=0x00AA00,
  CYAN=0x00AAAA,
  RED=0xAA0000,
  MAGENTA=0xAA00AA,
  BROWN=0xAA5500,
  LIGHT_GREY=0xAAAAAA,
  GREY=0x555555,
  LIGHT_BLUE=0x5555FF,
  LIGHT_GREEN=0x55FF55,
  LIGHT_CYAN=0x55FFFF,
  LIGHT_RED=0xFF5555,
  LIGHT_MAGENTA=0xFF55FF,
  YELLOW=0xFFFF55,
  WHITE=0xFFFFFF
};
class ScreenOut {
  private:
    bool err;
  public:
    ScreenOut(bool err);
    auto operator <<(char*) -> ScreenOut &; // puts(char *)
    auto clrscr() -> ScreenOut &;
    auto setColor(BGColor, FGColor) -> ScreenOut &;
    ~ScreenOut();
};
class Keyboard {
  public:
    Keyboard();
    auto operator >>(char &) -> Keyboard &; // getc()
    auto operator >>(char * &) -> Keyboard &; // gets an entire line
    auto getKeyCode() -> uint32_t; // gets a RAW keycode
    ~Keyboard();
};
class Serial {
    public:
    Serial();
    auto operator <<(char *) -> Serial &; // puts(char *)
    auto operator >>(char &) -> Serial &; // getc()
    auto operator >>(char * &) -> Serial &; // gets an entire line
    ~Serial();
};
class Disk {
  public:
    Disk(char * diskName);
    auto readSector(uint64_t sectorNum, uint8_t buf[512]) -> Disk &;
    auto writeSector(uint64_t sectorNum, uint8_t buf[512]) -> Disk &;
    ~Disk();
};
class MM {
  public:
    MM();
    auto getPage() -> void *;
    auto freePage(void*) -> void;
    ~MM();
};

#endif
