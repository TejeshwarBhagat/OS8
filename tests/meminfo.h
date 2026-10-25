#ifndef XV6_MEMINFO_H
#define XV6_MEMINFO_H

// Shared kernel/user ABI for sys_getmeminfo().
struct meminfo {
  int total_pages;       // allocator-managed physical frames
  int free_pages;        // currently on the physical free list
  int user_pages;        // virtual address space size / PGSIZE
  int page_table_pages;  // page directory plus all present page tables
};

#endif
