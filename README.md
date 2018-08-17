# ReadElf

ReadElf is program for reading coredumps and printing coredump condition like state of registers


### Directory tree

* [src] - readelf source
* [coredumps] - testing coredumps (32 and 64 bits)
* [test_dump_programs] - testing programs for coredump (32 and 64 bits)

### Installation

Makefile will create two binary files readelf32 and readelf64 

```sh
$ make
```

### Usage

Use readelf32 for 32bits coredumps and readelf64 for 64bits coredumps

```sh
$ ./readelf32 coredumps/dump32
Arch: 32BIT
phoff: 52
Headers count: 16
NOTE Offset 564
1 - 1
Program Received 11
Pending Signals 0
Hold Signals 9307194136390
PID of the process 5958
PPID of the process 29634

ORIG_EAX: 0x0000000000000000

EBX:    0xffffffff00000063
ECX:    0x000000230804841b
EDX:    0xffeaa8c000010206
ESI:    0x000000010000002b
EDI:    0x0000007c00000005
EDP:    0x45524f4300000003
EAX:    0x0000520000000000
DS:     0x0000000000400600
ES:     0x0000087700001746
FS:     0x000073c200001746
GS:     0x0000323374736574
EIP:    0x2020206120202061
CS:     0x0000000000000061
FLAGS:  0x0000000000000000
ESP:    0x0000000000000000
SS:     0x0000000000000000
```

Create coredump with:

```sh
# ulimit -c unlimited
```
