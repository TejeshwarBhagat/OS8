#include "types.h"
#include "stat.h"
#include "user.h"
#include "meminfo.h"

static void
report(char *label)
{
  struct meminfo mi;
  if(getmeminfo(&mi) == 0)
    printf(1, "%s: free=%d user=%d page-table=%d pages\n", label,
           mi.free_pages, mi.user_pages, mi.page_table_pages);
}

int
main(void)
{
  int i, pid;
  char *region, *untouched;
  volatile char *p;
  int offsets[4] = {0, 5*1024*1024, 17*1024*1024, 31*1024*1024};

  printf(1, "Q4: lazy heap allocation\n");
  report("before reservation");
  region = sbrk(32 * 1024 * 1024);
  if(region == (char*)-1){
    printf(1, "32 MB sbrk failed\n");
    exit();
  }
  report("after reserving 32 MB without touching it");
  for(i = 0; i < 4; i++){
    p = (volatile char*)(region + offsets[i]);
    *p = i + 1;
  }
  report("after touching four distant pages");

  pid = fork();
  if(pid == 0){
    p = (volatile char*)(region + 12 * 1024 * 1024);
    *p = 77;                 // A hole copied by fork is demand-zeroed here.
    printf(1, "child touched a previously absent heap page\n");
    exit();
  }
  if(pid < 0)
    printf(1, "fork failed\n");
  else
    wait();
  report("after child exit and wait");

  // sys_write receives a valid but not-yet-touched heap buffer.
  untouched = sbrk(4096);
  if(untouched != (char*)-1){
    printf(1, "writing one byte from untouched heap page (expected NUL): [");
    write(1, untouched, 1);
    printf(1, "]\n");
  }

  pid = fork();
  if(pid == 0){
    *(volatile char*)0x7fffffff = 1; // Outside sz: only this process is killed.
    printf(1, "ERROR: invalid address survived\n");
    exit();
  }
  if(pid > 0)
    wait();
  printf(1, "parent survived invalid child access\n");
  exit();
}
