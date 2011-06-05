#if CHAPTER >= 6
//
// elf.h -- Defines routines for dealing with Executable and Linking Format files.
//          Written for JamesM's kernel developement tutorials.
//

#include "elf.h"

elf_t elf_from_multiboot (multiboot_t *mb)
{
  int i;
  elf_t elf;
  elf_section_header_t *sh = (elf_section_header_t*)mb->addr;

  uint32_t shstrtab = sh[mb->shndx].addr;
  for (i = 0; i < mb->num; i++)
  {
    const char *name = (const char *) (shstrtab + sh[i].name);
    if (!strcmp (name, ".strtab"))
    {
      elf.strtab = (const char *)sh[i].addr;
      elf.strtabsz = sh[i].size;
    }
    if (!strcmp (name, ".symtab"))
    {
      elf.symtab = (elf_symbol_t*)sh[i].addr;
      elf.symtabsz = sh[i].size;
    }
  }
  return elf;
}

const char *elf_lookup_symbol (uint32_t addr, elf_t *elf)
{
  int i;

  for (i = 0; i < (elf->symtabsz/sizeof (elf_symbol_t)); i++)
  {
    if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2)
      continue;

    if ( (addr >= elf->symtab[i].value) &&
         (addr < (elf->symtab[i].value + elf->symtab[i].size)) )
    {
      const char *name = (const char *) ((uint32_t)elf->strtab + elf->symtab[i].name);
      return name;
    }
  }
}
#endif // CHAPTER >= 6
