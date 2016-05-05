#include <elf.hpp>
#include <base.hpp>
#include <serial.hpp>
#include <output.hpp>
using namespace MTGosHAL;
auto load(Elf32_Ehdr* file) -> void* {
  if((file->e_ident[0]!=ELFMAG0)||
     (file->e_ident[1]!=ELFMAG1)||
     (file->e_ident[2]!=ELFMAG2)||
     (file->e_ident[3]!=ELFMAG3) ) {
    return nullptr;
    debug << "File is not a valid ELF file!\n";
  }
  Elf32_Phdr *phdr = (Elf32_Phdr*)((uint32_t)(file->e_phoff)+(uint32_t)file);
  debug << "entry=";
  debug << Base::HEXADECIMAL;
  debug << (int)file->e_entry;
  for(int i=0;i<file->e_phnum;i++) {
    uint32_t start=phdr[i].p_vaddr;
    debug << "start=";
    debug << Base::HEXADECIMAL;
    debug << (int)start;
    uint32_t end=start+phdr[i].p_memsz;
    debug << "end=";
    debug << Base::HEXADECIMAL;
    debug << (int)end;
    if((start <= file->e_entry) && (file->e_entry < end)) {
      debug << "start=";
      debug << Base::HEXADECIMAL;
      debug << (int)(file->e_entry-start+phdr[i].p_offset+(uint32_t)file);
      return (void*) (file->e_entry-start+phdr[i].p_offset+(uint32_t)file); //Calculate _start address
    }
  }
  return nullptr;
}
