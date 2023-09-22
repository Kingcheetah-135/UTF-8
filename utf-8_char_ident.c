#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 5

int main (void)
{
	FILE *fp;
	unsigned int currentByte;
	char charString[BUF_SIZE];
	int bytes = 1;
	int num;

	if ((fp = fopen("test_file.txt", "r")) == NULL)
	{
		fprintf(stderr, "Unable to open test_file.txt");
		exit(EXIT_FAILURE);
	}

	while ((currentByte = fgetc(fp)) != EOF)
	{
		if (currentByte <= 127)
		{
			bytes = 1;// not the best maybe
			
		} else if (currentByte > 127 && currentByte <= 223)
		{
			bytes = 2;
			
		} else if (currentByte > 223 && currentByte <= 239)
		{
			bytes = 3;
			
		} else if (currentByte > 239 && currentByte <= 247)
		{
			bytes = 4;
		}

		num = snprintf(charString, BUF_SIZE - num, "%c", currentByte);
		
		while (bytes > 1) // check for bugs here
		{
			currentByte = fgetc(fp);
			num += snprintf(charString + num, BUF_SIZE, "%c", currentByte);
			--bytes;
		}

		num = 0;

		printf("%s", charString);
		
		if (strcmp(charString, "𐤃") == 0)
		{
			printf(" (Match found) ");
		}
	}

	fclose(fp);
	return 0;
}
