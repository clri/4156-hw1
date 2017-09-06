#include<bfd.h>

//definitions
#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))
unsigned long long start, finish;
//#define psp ;//processor speed

int main(int argc, char *argv[]){

  //write to screen if wrong number arguments specified
  if (argc != 3){
    write(1,"Error: Too Many Or Too Few Arguments\n",37);
    return 0;
  }

  //for loop for testing purposes
  //rdtsc(&start);
  //open with dlopen and flag
  dlopen("libobjdata.so",argv[2]);
  //rdtsc(&finish);
  //int q = finish - start;
  //q/= psp;
  //print psp to file

  //argv[1] is the fname
  bfd *b = initialise(argv[1]);
  getsyms(b);

  //dlclose("libobjdata.so");
  //end of for loop
  return 0;
}
