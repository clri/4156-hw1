#include<stdint.h>
#include<bfd.h>
#include<string.h>
//objsym.c part of the library
//just one function
//inttostring is (int,char*)

//gets and prints all section data
void getsyms(bfd *abfd){
  asymbol **symtab;
  //get symbol table
  uint32_t q = bfd_get_symtab_upper_bound(abfd);
  if (q < 0) bfd_perror("negative symbol table size");
  if (q <= 0) return;

  //place symbol table
  symtab = xmalloc(q);
  int nosyms = bfd_canonicalize_symtab(abfd,symtab);
  if (nosyms < 0){
    bfd_perror("negative number of symbols");
    return;
  }

  write(1,"VMA\t\tNAME\n",string_len("NAME\t\tVMA\n"));
  //iterate and print
  char buf[9];
  int i;
  for (i = 0; i < nosyms; ++i){
    //write the value of the vma
    uint32_t usy = (uint32_t)((symtab[i])->value);
    inttostring(usy,buf);
    write(1,"\t",2);

    //write name
    write(1,((symtab[i])->name),string_len(((symtab[i]))->name));
    write(1,"\n",2);
  }

}

