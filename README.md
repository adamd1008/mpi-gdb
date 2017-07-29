# mpi-gdb

`mpi-gdb` is a simple utility that allows a user to open an `xterm` running a `gdb` instance attached to every MPI process in the world communicator. It also attempts to neatly lay-out the xterms on screen, though tweaking may be needed.

## Usage

To use this tool, just add the following line below your call to `MPI_Init()`:

    MPI_GDB_INIT();

Run your program in the usual way:

    mpirun -n 2 ./a.out

In this case, you will see two xterms appear, each attached to each MPI process running in the world communicator.

GDB can attach before any code executes after the `MPI_GDB_INIT()` call because of a sleep guard. On modern 64-bit Linux distros, the stack trace below the utility looks like this:

    #0  0x00007f5639cc97cd in nanosleep () from /lib64/libc.so.6
    #1  0x00007f5639cc971a in sleep () from /lib64/libc.so.6
    #2  0x0000000000401622 in mpigdb_init_func () at ../../mpi-gdb/mpi_gdb.h:80

GDB naively attempts to unwind the stack back to your code by automatically executing the following commands:

    finish
    finish
    set var start = 1
    finish

GDB can then be used as normal.

As noted above, this may not work on archiotectures other than x86-based. Tweak as appropriate.

## Disabling `mpi-gdb`

The utility can be disabled by adding the `NDEBUG` preprocessor directive, as is typical during a release build.

