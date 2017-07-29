# mpi-gdb

`mpi-gdb` is a simple utility that allows a user to open an `xterm` running a `gdb` instance attached to every MPI process in the world communicator. It also attempts to neatly lay-out the xterms on screen, though tweaking may be needed.

## Usage

To use this tool, just add the following line below your call to `MPI_Init()`:

    MPI_GDB_INIT();

Run your program in the usual way:

    mpirun -n 2 ./a.out

In this case, you will see two xterms appear, each running `gdb` attached to each MPI process running in the world communicator. Each `gdb` will automatically attempt to unwind the stack back to your code, at which point they can then be used as normal.

## How it works

The utility stops execution racing ahead of the `MPI_GDB_INIT()` call with a simple `sleep()` guard:

    while (start == 0)
      sleep(1);

On modern 64-bit Linux distros using `glibc`, the stack trace below the utility looks like this:

    #0  0x00007f5639cc97cd in nanosleep () from /lib64/libc.so.6
    #1  0x00007f5639cc971a in sleep () from /lib64/libc.so.6
    #2  0x0000000000401622 in mpigdb_init_func () at ../../mpi-gdb/mpi_gdb.h:80

`gdb` naively attempts to unwind the stack back to your code by automatically executing the following commands:

    finish
    finish
    set var start = 1
    finish

## Limitations

This code has been written for Linux on x86-based architectures. If the stack is different under `sleep()` on your architecture, the `-ex` arguments supplied to `gdb` will need to be modified as appropriate.

This utility will obviously not work across MPI instances running on different systems.

Although I haven't seen it happen myself, the `start` variable may be optimised out or otherwise made redundant.

## Disabling `mpi-gdb`

The utility can be disabled by adding the `NDEBUG` preprocessor directive, as is typical during a release build.
