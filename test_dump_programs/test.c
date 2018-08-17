#include <stdio.h>

int main()
{
	int i=0;
	int x[2];
	printf("%p\n",main);
	while (1){
		x[i] = 'a';
		i++;
	}
	return 0;
}
