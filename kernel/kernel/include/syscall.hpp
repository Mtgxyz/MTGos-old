#ifndef _SYSCALL_HPP
#define _SYSCALL_HPP
#include <stdint.h>
enum class BGColor : uint32_t {
  BLACK=0x0000,
  BLUE=0x1000,
  GREEN=0x2000,
  CYAN=0x3000,
  RED=0x4000,
  MAGENTA=0x5000,
  BROWN=0x6000,
  LIGHT_GREY=0x7000,
  GREY=0x8000,
  LIGHT_BLUE=0x9000,
  LIGHT_GREEN=0xA000,
  LIGHT_CYAN=0xB000,
  LIGHT_RED=0xC000,
  LIGHT_MAGENTA=0xD000,
  YELLOW=0xE000,
  WHITE=0xF000
};
enum class FGColor : uint32_t {
  BLACK=0x000,
  BLUE=0x100,
  GREEN=0x200,
  CYAN=0x300,
  RED=0x400,
  MAGENTA=0x500,
  BROWN=0x600,
  LIGHT_GREY=0x700,
  GREY=0x800,
  LIGHT_BLUE=0x900,
  LIGHT_GREEN=0xA00,
  LIGHT_CYAN=0xB00,
  LIGHT_RED=0xC00,
  LIGHT_MAGENTA=0xD00,
  YELLOW=0xE00,
  WHITE=0xF00
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
