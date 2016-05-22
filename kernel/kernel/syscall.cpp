
#include <syscall.hpp>
#include <base.hpp>
#include <textDISP.hpp>
ScreenOut::ScreenOut(bool err): err(err) {
  
}
auto ScreenOut::operator<<(char *text) -> ScreenOut & {
  if(!text)
    return *this;
  if(err)
    MTGosHAL::err << text;
  else
    MTGosHAL::out << text;
  return *this;
}
auto ScreenOut::clrscr() -> ScreenOut & {
  if(err)
    MTGosHAL::err.clrscr();
  else
    MTGosHAL::out.clrscr();
  return *this;
}
auto ScreenOut::setColor(BGColor bg, FGColor fg) -> ScreenOut & {
  if(err)
    MTGosHAL::err << static_cast<MTGosHAL::BG_color>(bg) << static_cast<MTGosHAL::FG_color>(fg) ;
  else
    MTGosHAL::out << static_cast<MTGosHAL::BG_color>(bg) << static_cast<MTGosHAL::FG_color>(fg) ;
  return *this;
}
ScreenOut::~ScreenOut() {}
auto syscall(uint32_t syscall_num, void* handle, void* args) -> void* {
    uint16_t objnum=(uint16_t)(syscall_num>>16);
    uint16_t funcnum=(uint16_t)syscall_num;
    switch(objnum) {
      case 0: {
        ScreenOut *obj = (ScreenOut*)handle;
        switch(funcnum) {
          case 0:
            return (void*)(new ScreenOut(((bool *)args)[0]));
            break;
          case 1:
            
            *obj << ((char**)args)[0];
            return handle;
            break;
          case 2:
            obj->clrscr();
            return handle;
            break;
          case 3: {
            BGColor bg=static_cast<BGColor>(((uint32_t *)args)[0]);
            FGColor fg=static_cast<FGColor>(((uint32_t *)args)[1]);
            obj->setColor(bg,fg);
            return handle;
            break;
          }
          case 0xFFFF:
            delete obj;
            return nullptr;
            break;
          default:
            break;
        }
        break;
      }
      default:
        break;
    }
    return nullptr;
}
