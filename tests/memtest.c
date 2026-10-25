#include "types.h"
#include "stat.h"
#include "user.h"
#include "meminfo.h"

static void
report(char *label)
{
  struct meminfo mi;
  if(getmeminfo(&mi) < 0){
    printf(1, "getmeminfo failed\n");
    return;
  }
  printf(1, "%s: total=%d free=%d user=%d page-table=%d pages\n", label,
         mi.total_pages, mi.free_pages, mi.user_pages, mi.page_table_pages);
}

int
main(void)
{
  char *region;
  int allocatedfree, childfree;
  struct meminfo mi;
  int pid;

  printf(1, "Q2: physical memory accounting\n");
  report("before allocation");
  if(getmeminfo(&mi) < 0)
    exit();
  region = sbrk(2 * 4096);
  if(region == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }
  region[0] = 1;
  region[4096] = 2;
  report("after two touched heap pages");
  if(getmeminfo(&mi) < 0)
    exit();
  allocatedfree = mi.free_pages;

  pid = fork();
  if(pid == 0){
    if(getmeminfo(&mi) == 0)
      printf(1, "child after fork: free=%d pages\n", mi.free_pages);
    exit();
  }
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }
  wait();
  if(getmeminfo(&mi) == 0){
    childfree = mi.free_pages;
    printf(1, "after child exit and wait: free=%d pages (before fork=%d)\n",
           childfree, allocatedfree);
    printf(1, "reclaimed child pages: %s\n",
           childfree == allocatedfree ? "yes" : "no");
  }
  exit();
}
