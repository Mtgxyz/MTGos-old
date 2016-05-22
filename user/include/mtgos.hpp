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
    void* handle;
  public:
    ScreenOut(bool err);
    auto operator <<(char*) -> ScreenOut &; // puts(char *)
    auto clrscr() -> ScreenOut &;
    auto setColor(BGColor, FGColor) -> ScreenOut &;
    ~ScreenOut();
};
