### NAME
ioperm - start another program with access to I/O ports

### SYNOPSIS
Usage: `ioperm <your-program> [<your-program-args>]`

### DESCRIPTION
This program is like `sudo`; it grants extra permissions to a program. Use
`ioperm` when you have a program (e.g. Wine) that crashes on an `inb`, `outb`,
`inw`, `outw`, `ind`, or `outd` instruction. These x86 instructions are used for
direct access to various bits of hardware including serial ports, parallel
ports, joysticks, and the system speaker.
