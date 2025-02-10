#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>

void writeFile (char* filename)
{
	FILE* file = fopen (filename, "wt");

	int i = 0;
	while (!feof(file) && i < 2000)
	{
		for (int y = 0; y < 16; y++)
		{
			int x = rand();
			fprintf(file, "%d", x);		
		}
		fprintf(file, "\n");
		i++;
	}

	fclose(file);
}	

void int2char (char** data, int x)
{
	if (data && *data)
	{
		char* res = (char*)calloc(2, sizeof(char));		
		res[0] = res[1] = '0';

		int p = 0;
		if (x > 9)
		{
			p = 1;
		}

		int b2 = x;

		int P = p+1;
			for (int i = 0; i < P; i++)
		{
			int b1 = b2 % 10;
			b2 = (b2/10.0);
			res[1-i] = (char)(b1+'0');
		}
		*data = res;
	}
}

int char2int (char* data)
{
	int res = 0;
	int n = strlen(data);

	for (int i = 0; i < n; i++)
	{
		int c = (int)data[i]-'0';
		res += c * (int)pow(10, n-i-1);
	}
	return (res);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	char* def = "tmp";
	char* buf = (char*)calloc(10,sizeof(char));

	int n = 0;
	if (argc == 2)
	{
		n = char2int(argv[1]);
	}
	else
	{
		printf("N: ");
		scanf(" %d", &n);
		getchar();
	}

	if (n < 99)
	{
		for (int i = 0; i < n; i++)
		{
			char* tmp = buf;

			strcpy(buf, def);
			
			int2char(&tmp, i+1);

			strcat(buf, tmp);

			free(tmp);

			strcat(buf,".txt");

			writeFile(buf);
		}
	}
	return(0);
}
