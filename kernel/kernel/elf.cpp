#include <elf.hpp>
auto load(Elf32_Ehdr* file) -> void* {
  if((file->e_ident[0]!=ELFMAG0)||
     (file->e_ident[1]!=ELFMAG1)||
     (file->e_ident[2]!=ELFMAG2)||
     (file->e_ident[3]!=ELFMAG3) )
    return nullptr;
  Elf32_Phdr *phdr = (Elf32_Phdr*)((uint32_t)(file->e_phoff)+(uint32_t)file);
  for(int i=0;i<file->e_phnum;i++) {
    uint32_t start=phdr[i].p_vaddr;
    uint32_t end=start+phdr[i].p_memsz;
    if((start < file->e_entry) && (file->e_entry < end))
      return (void*) (file->e_entry-start+phdr[i].p_offset+(uint32_t)file); //Calculate _start address
  }
  return nullptr;
}
