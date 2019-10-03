#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PHYS_SIZE 0x1000
#define ADDR_SPACE_SIZE 0x100
#define STR_SIZE 40


struct addressSpace{
  int code;
  int heap;
  int stack;
};

int randBetween(unsigned int lower, unsigned int upper){
  srand(time(0));
  return rand()%(upper-lower+1) + lower;
}


void clearMemory(char* m[]){
  for(int i= 0; i<PHYS_SIZE; i++){
    m[i] = malloc(strlen("Free")+1);
    strcpy(m[i],"Free");
  }
}

void memoryDump(char* m[], unsigned int base, unsigned int bound){
  for (int i = base; i <base+bound; i++){
    if (!(i%8)){
      printf("\n");
    }
    printf("%04x:%s\t",i,m[i]);
  }
  printf("\n");
}     

void allocateMemory(char* m[], unsigned int addr, char* owner){
  m[addr] = malloc(strlen(owner)+1);
  strcpy(m[addr], owner);
}

void allocateBlock(char* m[], unsigned int base, unsigned int bound, char* owner){
  for (int i = base; i <=base+bound; i++){
    allocateMemory(m,i,owner);
  }
}

void freeBlock(char* m[], unsigned int base, unsigned int bound){
  allocateBlock(m,base, bound, "Free");
}


int main(int argc, char *argv[]) {

  char* physicalMemory[PHYS_SIZE];
  char owner[STR_SIZE];
  int id = 0;

  clearMemory(physicalMemory);
  memoryDump(physicalMemory, 0, 0xff);

  sprintf(owner,"Job%d",id);
  
  allocateBlock(physicalMemory, 0x0,0xf, owner);
  memoryDump(physicalMemory, 0, 0xff);

  freeBlock(physicalMemory, 0x3, 0x5);
  memoryDump(physicalMemory, 0, 0xff);
  
  // struct addressSpace a = {3,4,5};  
  //printf("%d %d %d\n", a.code, a.heap,a.stack);

  
  return 0;
}

