#include <stdio.h>

int main(int argc, char * argv[])
{
	char buffer[10];
	
	FILE *ptr = fopen(argv[0],"r");
	fread(buffer,1,5,ptr);

	fclose(ptr);

	ptr = fopen(argv[0],"w");
	fwrite(buffer,1,5,ptr);

	fclose(ptr);
	

	
	
}
