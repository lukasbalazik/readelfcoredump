#include "init.h"

int get_arch(char *file)
{
	if (file[EI_CLASS] == 0x01) {
		printf("\nArch: 32BIT\n");
		return 1;
	}
	if (file[EI_CLASS] == 0x02) {
		printf("\nArch: 64BIT\n");
		return 2;
	}
	
	return -1;
}

int is_elf(char *file)
{
	if ((file[0] != 0x7f) || (file[1] != 'E') ||
		(file[2] != 'L') || (file[3] != 'F')) {
		return 0;
	}
	return 1;
}

void parse_header(int fd, int arch)
{
	char *p = NULL;

	int size;
	int i=0;


	Elf_Ehdr *elfh;
	Elf_Phdr *elfphdr;

	elfh = (Elf_Ehdr *) file;

	size = elfh->e_phnum * elfh->e_phentsize;
	p = malloc(size);

	printf("phoff: %d\n", (int)elfh->e_phoff);

	lseek(fd, elfh->e_phoff, SEEK_SET); 

	if (read(fd, p, size) != size) {
		printf("\nCannot read Program Header");
		goto cl;
	}
	elfphdr = (Elf_Phdr *)p;
	printf("Headers count: %d\n", elfh->e_phnum);

	for (i = 0; i < elfh->e_phnum; i++) {
		if (elfphdr->p_type == PT_NOTE) {
			unsigned char *pdata;
			Elf_Nhdr *not;
			int pad;

			pdata = malloc(elfphdr->p_filesz);
			lseek(fd, elfphdr->p_offset, SEEK_SET);
			printf("NOTE Offset %d\n", (int)elfphdr->p_offset);
			read(fd, pdata, elfphdr->p_filesz);
			not = (Elf_Nhdr *) pdata;
			pad  = 4 - (not->n_namesz % 4); 
			printf("%d - %d", not->n_type, NT_PRSTATUS);
			if (not->n_type == NT_PRSTATUS) {
				struct elf_prstatus *prs;
				prs = (struct elf_prstatus *)(pdata + sizeof(*not) + not->n_namesz + pad);
			
				basic_info(prs);

				if (arch == 1)
					show_registers_32bit(prs);
				else
					show_registers_64bit(prs);

				pdata = pdata + sizeof(*not) + not->n_namesz + pad + sizeof(struct elf_prstatus);
			}
			not = (Elf_Nhdr *)pdata;
			if (not->n_type == NT_PRPSINFO) {
				struct elf_prpsinfo *prs;
				printf("\n\nNT_PRPSINF\n");
				pad  = 4 - (not->n_namesz % 4);
				prs = (struct elf_prpsinfo *)(pdata + sizeof(*not) + not->n_namesz + pad);
				printf("\nName of the Exe %s", prs->pr_fname);
			} 
		}
		elfphdr++;
	}
	free(p);	  
	printf("\n\n");

	cl:   
	    close(fd);
}

void basic_info(struct elf_prstatus *prs)
{
	printf("\nProgram Received %d", prs->pr_cursig);
	printf("\nPending Signals %lu", prs->pr_sigpend);
	printf("\nHold Signals %lu", prs->pr_sighold);
	printf("\nPID of the process %d", prs->pr_pid);
	printf("\nPPID of the process %d\n", prs->pr_ppid);

}

void show_registers_64bit(struct elf_prstatus *prs) 
{
	printf("\nORIG_RAX: 0x%016llx", prs->pr_reg[15]);
	printf("\nFS_BASE: 0x%016llx", prs->pr_reg[21]);
	printf("\nGS_BASE: 0x%016llx\n", prs->pr_reg[22]);
	printf("\nR15: \t0x%016llx", prs->pr_reg[0]);
	printf("\nR14: \t0x%016llx", prs->pr_reg[1]);
	printf("\nR13: \t0x%016llx", prs->pr_reg[2]);
	printf("\nR12: \t0x%016llx", prs->pr_reg[3]);
	printf("\nRBP: \t0x%016llx", prs->pr_reg[4]);
	printf("\nRBX: \t0x%016llx", prs->pr_reg[5]);
	printf("\nR11: \t0x%016llx", prs->pr_reg[6]);
	printf("\nR10: \t0x%016llx", prs->pr_reg[7]);
	printf("\nR9: \t0x%016llx", prs->pr_reg[8]);
	printf("\nR8: \t0x%016llx", prs->pr_reg[9]);
	printf("\nRAX: \t0x%016llx", prs->pr_reg[10]);
	printf("\nRCX: \t0x%016llx", prs->pr_reg[11]);
	printf("\nRDX: \t0x%016llx", prs->pr_reg[12]);
	printf("\nRSI: \t0x%016llx", prs->pr_reg[13]);
	printf("\nRDI: \t0x%016llx", prs->pr_reg[14]);
	printf("\nRIP: \t0x%016llx", prs->pr_reg[16]);
	printf("\nCS: \t0x%016llx", prs->pr_reg[17]);
	printf("\nFLAGS:\t0x%016llx", prs->pr_reg[18]);
	printf("\nRSP: \t0x%016llx", prs->pr_reg[19]);
	printf("\nSS: \t0x%016llx", prs->pr_reg[20]);
	printf("\nDS: \t0x%016llx", prs->pr_reg[23]);
	printf("\nES: \t0x%016llx", prs->pr_reg[24]);
	printf("\nFS: \t0x%016llx", prs->pr_reg[25]);
	printf("\nGS: \t0x%016llx", prs->pr_reg[26]);
}

void show_registers_32bit(struct elf_prstatus *prs) 
{
	printf("\nORIG_EAX: 0x%016llx\n", prs->pr_reg[11]);
	printf("\nEBX: \t0x%016llx", prs->pr_reg[0]);
	printf("\nECX: \t0x%016llx", prs->pr_reg[1]);
	printf("\nEDX: \t0x%016llx", prs->pr_reg[2]);
	printf("\nESI: \t0x%016llx", prs->pr_reg[3]);
	printf("\nEDI: \t0x%016llx", prs->pr_reg[4]);
	printf("\nEDP: \t0x%016llx", prs->pr_reg[5]);
	printf("\nEAX: \t0x%016llx", prs->pr_reg[6]);
	printf("\nDS: \t0x%016llx", prs->pr_reg[7]);
	printf("\nES: \t0x%016llx", prs->pr_reg[8]);
	printf("\nFS: \t0x%016llx", prs->pr_reg[9]);
	printf("\nGS: \t0x%016llx", prs->pr_reg[10]);
	printf("\nEIP: \t0x%016llx", prs->pr_reg[12]);
	printf("\nCS: \t0x%016llx", prs->pr_reg[13]);
	printf("\nFLAGS: \t0x%016llx", prs->pr_reg[14]);
	printf("\nESP: \t0x%016llx", prs->pr_reg[15]);
	printf("\nSS: \t0x%016llx", prs->pr_reg[16]);
}
