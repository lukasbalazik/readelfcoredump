#include "init.h"

int main (int argc, char **arg)
{
	int fd;

	if (argc < 2) {
		printf("\nUsage: elf2inf <core>\n");
		return 0;
	}

	fd = open(arg[1], O_RDONLY);

	if (fd < 0) {
		perror("open");
		return 0;
	}

	if (!read(fd, file, sizeof(file))) {
		perror("Error Reading the ELF Header");
		return 0;
	}

	if ((arch = get_arch(file)) < 0) {
		printf("Unknown ARCH");
		return 0;
	}


	if (!is_elf(file)) {
		printf("\nWrong Format\n\n");
		return 0;
	}
	
	parse_header(fd, arch);

	return 0;
}
