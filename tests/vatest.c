#include "types.h"
#include "stat.h"
#include "user.h"

static int global_value = 2401;

static void
show(char *label, int *address)
{
  printf(1, "%s: VA=%x PA=%x value=%d\n", label, (uint)address,
         va2pa((int)address), *address);
}

int
main(void)
{
  int local_value = 23;
  int *heap_value;
  int pid;

  heap_value = (int*)malloc(sizeof(int));
  if(heap_value == 0){
    printf(1, "vatest: malloc failed\n");
    exit();
  }
  *heap_value = 8;
  printf(1, "Q1: virtual-to-physical translation\n");
  show("global", &global_value);
  show("local", &local_value);
  show("malloc", heap_value);
  printf(1, "unmapped 0x7fffffff -> %d\n", va2pa(0x7fffffff));

  pid = fork();
  if(pid == 0){
    printf(1, "child same global VA=%x PA=%x\n", (uint)&global_value,
           va2pa((int)&global_value));
    exit();
  }
  if(pid < 0)
    printf(1, "vatest: fork failed\n");
  else {
    wait();
    printf(1, "parent same global VA=%x PA=%x\n", (uint)&global_value,
           va2pa((int)&global_value));
  }
  free(heap_value);
  exit();
}
