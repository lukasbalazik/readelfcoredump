#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/procfs.h>
#include <linux/elf.h>


#ifdef ARCH32
	typedef Elf32_Phdr Elf_Phdr;
	typedef Elf32_Ehdr Elf_Ehdr;
	typedef Elf32_Nhdr Elf_Nhdr;
#else
	typedef Elf64_Phdr Elf_Phdr;
	typedef Elf64_Ehdr Elf_Ehdr;
	typedef Elf64_Nhdr Elf_Nhdr;
#endif


char file[1000];

int arch;

int get_arch(char *);
int is_elf(char *);

void parse_header(int, int);
void basic_info(struct elf_prstatus *);
void show_registers_32bit(struct elf_prstatus *);
void show_registers_64bit(struct elf_prstatus *);

#endif
