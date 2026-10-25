# Operating Systems Lab 8 - Memory Management in xv6

**Student:** Tejeshwar Bhagat  
**Roll number:** 2401MC23

## Folder contents

- `diffs/lab8_complete.diff` - complete patch for Questions 1-4, including the user programs in the xv6 source root.
- `tests/` - `vatest.c`, `memtest.c`, `vmprinttest.c`, `lazytest.c`, and the shared `meminfo.h` ABI header.
- `screenshots/` - reserved for one terminal screenshot per question.
- `Lab8_write_up.pdf` - consolidated design and verification report.
- `output_log.txt` - build/run evidence status for this environment.

## Apply and run

The patch targets MIT `xv6-public` commit `eeb7b415dbcb12cc362d0783e41c3d1f44066b17`.

```sh
git clone https://github.com/mit-pdos/xv6-public.git xv6-public
cd xv6-public
git checkout eeb7b415dbcb12cc362d0783e41c3d1f44066b17
git apply /path/to/lab8_2401MC23/diffs/lab8_complete.diff
make TOOLPREFIX=i686-elf- QEMU=qemu-system-i386 qemu-nox CPUS=2
```

At the xv6 shell, run `vatest`, `memtest`, `vmprinttest`, and `lazytest`. Capture the terminal output for each run in `screenshots/` as `Q1_vatest.png`, `Q2_memtest.png`, `Q3_vmprinttest.png`, and `Q4_lazytest.png`.

## Evidence status

The changed C files passed a 32-bit GCC syntax check. This environment does not have GNU make, an `i686-elf` toolchain, or QEMU, so no xv6 build or runtime output was produced here. The screenshot folder intentionally contains capture instructions instead of fabricated QEMU evidence. The report marks runtime measurements as pending.
