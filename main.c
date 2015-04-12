#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <elf.h>

int main(int argc, char *argv[])
{
  FILE* ElfFile = NULL;
  char* SectNames = NULL;
  int idx;
  Elf64_Ehdr elf;
   ElfFile = fopen(argv[1], "r");
   if(ElfFile == NULL) {
      printf("Failed to open file\n");
      return 0;
   }
   printf("Reading object file\n");
   fread(&elf, 1, sizeof elf, ElfFile);
//   printf("%x", elf.e_ident[0]);

   if((elf.e_ident[EI_MAG0] != ELFMAG0) 
      && (elf.e_ident[EI_MAG1] != ELFMAG1)
      && (elf.e_ident[EI_MAG2] != ELFMAG2)
      && (elf.e_ident[EI_MAG3] != ELFMAG3)) {
      printf("not an elf file format. giving up\n");
      return 0;
   }


   if(elf.e_ident[EI_CLASS] == ELFCLASS64) {
      printf("obj file is 64 bit\n");
   }

   if(elf.e_ident[EI_VERSION] != EV_CURRENT) {
      printf("obj version is not current. giving up\n");
      return 0;
   }
   switch(elf.e_type) {
   case ET_NONE :
      printf("not a supported file\n");
      return 0;
   case ET_EXEC:
      printf("executable file\n");
      break;
   case ET_CORE:
      printf("core dump\n");
      break;
   }

   if(EM_X86_64 != elf.e_machine) {
      printf("not a 64 bit obj file. giving up\n");
      return 0;
   }

   if(elf.e_version != EV_CURRENT) {
      printf("The obj version is not current. Giving up\n");
   }
   return 0; 
}
