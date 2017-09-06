#include<bfd.h>
#include<stdint.h>
#include<string.h>

//length of string function for writing to the screen
int string_len(const char *s){
  int ans = 0;
  while (*s++) ans++;
  return ans;
}

//convert int to string without sprintf
//writes it to screen in hexadecimal
void inttostring(uint32_t a, char* ans){
  //char ans[9];
  int i = 0;
  while (i < 8){
    int j = 4 * (i + 1);
    int q = a >> (32 - j);
    q &= 0xf;
    char b = (char)q;
    if (b >= 10) b += 55; //hex >= 10
    else b+= 48; //hex < 10
    ans[i++] = b;
  }
  ans[8] = '\0';
  write(1,"0x",string_len("Ox"));
  write(1,ans,string_len(ans));
}

//initialises bfd and opens file fn
//if fn is not an executable object, returns error
bfd *initialise(const char *fn){
  bfd_init();
  bfd *ans = bfd_openr(fn,NULL);
  if (bfd_check_format(ans, bfd_object)) return ans;
  else{
    bfd_perror("not executable file format");
    return NULL;
  }
}

//prints section data to screen
//uses bufr to assign string
void getsec(bfd *abfd, asection *asec, void *bufr){
  write(1,asec->name,string_len(asec->name)); ///name
  write(1,"\t", string_len("\t"));

  //memory address
  inttostring((uint32_t)(asec->vma),bufr); //virtual memory address
  write(1,"\t", string_len("\t"));

  //if the rawsize is not set, output the cooked size
  if (asec->rawsize != 0) inttostring((uint32_t)(asec->rawsize),bufr); //raw size
  else inttostring((uint32_t)(asec->size),bufr);
  write(1,"\t", string_len("\t"));

  //output the size
  inttostring((uint32_t)(asec->size),bufr); //cooked size
  write(1,"\t", string_len("\t"));

  //position
  inttostring((uint32_t)(asec->filepos),bufr);  
  write(1,"\n", string_len("\n"));
}

//gets and prints all section data
void getsecs(bfd *abfd){
  char buf[9];
  write(1,"NAME\tVMA\t\tRAW\t\tCOOKED\t\tPOS\n",string_len("NAME\tVMA\t\tRAW\t\tCOOKED\\ttPOS\n"));
  bfd_map_over_sections(abfd,getsec,(void *)buf);
}

