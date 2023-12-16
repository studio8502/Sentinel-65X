# Sentinel 65X

This is a design for an 8/16-bit computer/games console, which uses
the 65816 CPU architecture (by WDC) and the VERA video system (by
Frank van den Hoef) as its core. It is not directly compatible with
any existing system, but porting from other 6502 and 65816 systems
which have a similar architecture should not prove difficult.

## Features

- Designed to minimize BOM and construction costs
- Intended to be a turnkey "fabrication ready" design which anyone
  can produce and sell for any purpose
- Fully open source hardware designs, released under the CERN OHL
  (permissive) V2
- 8MHz WDC W65C265S CPU (W65C816S compatible)
  - 16MB adress space
  - 8 timers
  - Multiple priority-encoded interrupts
  - Built-in GPIO
- 512KB of on-board static RAM
- 512KB of flash ROM
- RGB video output at 640x480
- Stereo audio output
- SD card slot
- Dual enhanced SNES-compatible controller ports
  - Supports SNES controllers & joysticks
  - Supports the SNES mouse and clones
  - Enhanced with I2C bus support for custom peripherals
- Cartridge/expansion port with full system bus, supporting ROM,
  RAM, and I/O expansions
- Amiga-inspired "clock port" which also serves as a debug port

## Software

At the present time, software for this design is nonexistent. The
intention is to implement a kernel and library to support assembly
and C programming for cross-development (using the Calypsi C toolchain),
and to eventually develop or port a suite of tools for on-device
programming to be put into the system ROM.

The planned kernel will be reminiscent of the architecture of MSX-DOS
2, but will support long file names and the FAT32 (and later ExFAT)
filesystem on SD cards.
