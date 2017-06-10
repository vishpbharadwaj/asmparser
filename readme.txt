ASM Parser file which takes the assembly file of the OBJDUMP util in Linux as input and
outputs 0s and 1s to a file based on repetative x86 mnemonics.

1 -> implies there is no repetation of successive mnemonics
0 -> implies there is not

Objdump file:
objdump -D -Mintel [binary file] >> objdump.txt

To build:
make -f makefile

To run:
./asmparser [objdump file]
