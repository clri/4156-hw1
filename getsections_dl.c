
#include<bfd.h>

//definitions
#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))
//#define psp ; //proc speed
unsigned long long start, finish;

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
  
  //char buff[9];
  //test by inttostring(finish - start, buff)
  //double q = finish - start;
  //q/= psp;
  //print psp to file


  bfd *b = initialise(argv[1]);
  getsecs(b);

  //dlclose("libobjdata.so");
  //end of for loop
  return 0;
}
