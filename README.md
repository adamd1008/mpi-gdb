# mpi-gdb

`mpi-gdb` is a simple utility that allows a user to open an `xterm` running a
`gdb` instance attached to every MPI process in the world communicator. It also
attempts to neatly lay-out the xterms on screen, though tweaking may be needed.

## Prerequisites

This tool requires the following packages to be installed:

- `openmpi`
- `openmpi-devel` or `openmpi-dev`
- `xterm`

You can modify the code to use whatever MPI library or terminal emulator, but
note that the arguments given to `execlp()` will likely be wrong.

The header include may need to be changed, depending on your distribution.

## Usage

To use this tool, add the following line after your call to `MPI_Init()`:

    MPI_GDB_INIT();

Run your program in the usual way:

    mpirun -n 2 ./a.out

In this case, you will see two xterms appear, each running `gdb` attached to
each MPI process running in the world communicator. Each `gdb` will
automatically attempt to unwind the stack back to your code, at which point
they can then be used as normal.

## How it works

The utility stops execution racing ahead of the `MPI_GDB_INIT()` call with a
simple `usleep()` guard:

    while (start == 0)
      usleep(10000);

`gdb` stops execution at it, so that it can unwind the stack back to your code
by automatically executing the following commands:

    break mpi_gdb.h:109
    continue
    set var start = 1
    finish

## Disabling `mpi-gdb`

The utility is automatically disabled by adding the `NDEBUG` preprocessor
directive, as is typical during a release build.

## Troubleshooting

If you see:

```
No source file named mpi_gdb.h.
Make breakpoint pending on future shared library load? (y or [n])
```

or if GDB loops forever, never hitting the breakpoint, you have probably built
a release version of your MPI application without debug information.

Please raise any issues not mentioned here.
