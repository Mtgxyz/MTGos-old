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
    void* handle;
  public:
    ScreenOut(bool err);
    auto operator <<(const char*) -> ScreenOut &; // puts(char *)
    auto operator <<(int) -> ScreenOut &;
    auto clrscr() -> ScreenOut &;
    auto setColor(BGColor, FGColor) -> ScreenOut &;
    ~ScreenOut();
};
