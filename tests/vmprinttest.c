#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  char local;
  char *heap;
  int i, end, sz;

  printf(1, "Q3: page-table dump and stack guard\n");
  sz = (int)sbrk(0);
  printf(1, "exec stack guard VA=%x (P=1, U=0 in dump)\n",
         (((uint)&local) & ~(4096-1)) - 4096);
  printf(1, "expected user-accessible pages at start: %d (sz/PGSIZE - guard)\n",
         sz / 4096 - 1);
  printf(1, "initial page table:\n");
  vmprint();

  end = (int)sbrk(8 * 4096);
  if(end < 0){
    printf(1, "sbrk growth failed\n");
    exit();
  }
  heap = (char*)end;
  for(i = 0; i < 8; i++)
    heap[i * 4096] = i;
  printf(1, "after sbrk(8 pages) and touching each page:\n");
  vmprint();

  sbrk(-4096);
  printf(1, "after sbrk(-1 page):\n");
  vmprint();
  exit();
}
