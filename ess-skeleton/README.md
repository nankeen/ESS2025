# ESS2025

The recommended way to use this is with STM32CubeIDE.
Alternatively if you are more comfortable with the terminal, you can use the provided Makefile.

The following instructions are _only_ for compiling without STM32CubeIDE.

## Requirements

+ [Open On-Chip-Debugger](https://openocd.org/) - for flashing and debugging the firmware
+ ARM GNU compiler toolchain - for GCC and GDB

### Installation with Homebrew

```bash
brew install arm-none-eabi-gcc open-ocd
```

## Building

```bash
make
```

## Flashing

```bash
make flash
```

## Debugging

The following command will start the on-chip-debugger and run an instance of GDB server.

```bash
make debug
```

This will connect to GDB server instance.

```bash
arm-none-eabi-gdb -q -ex "target extended-remote :3333" build/stm32f411_project.elf
```
