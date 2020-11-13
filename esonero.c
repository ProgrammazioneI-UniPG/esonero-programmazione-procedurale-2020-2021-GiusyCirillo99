#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 128
#define MAXCHAR 128
#define RETURN '\n'

// prepara l'immissione della chiave
void immissione(char *p, int l)
{
	char *ret;
	char buffer[SIZE+2];

	do
	{
// azzeramento di tutti i vettori
		for(int i=0; i<SIZE+2; i++)
		{
			buffer[i]='\0';
		}

		printf ("%s\n","Start string");
		if ((fgets (buffer, SIZE, stdin) != NULL))
		{

// Elimino il carattere RETURN dalla stringa letta

			if ((ret=strchr(buffer, RETURN)) != NULL)
			{
				ret[0]='\0';
			}
		}
		printf ("%s\n","End string");
	}
	while (strlen(buffer) < l);
	memcpy (p, buffer, SIZE+2);
}

// genera una chiave random
void generazione(char *p, int l)
{
	int i;

	for(i=0; i<l; i++)
	{
		p[i] = rand() % MAXCHAR;
	}
}

// cripta la stringa m con la chiave k, mettendo il risultato in s
void xorwise(char *s, char *m, char *k, int len)
{
	int i;

	for (i=0; i<len; i++)
	{
		s[i] = m[i] ^ k[i];
	}
}

void print_array(char *p, int len)
{
	int i;

	for(i=0; i<len; i++)
	{
		printf ("<%c>\n",p[i]);
	}
	printf("\n");
}

int main ()
{
	FILE *fp;
	char m[SIZE+2];
	char k[SIZE+2];
	char m1[SIZE+2];
	char m2[SIZE+2];
	char *ret;
	int len;
	int scelta;

// azzeramento di tutti i vettori
	for(int i=0; i<SIZE+2; i++)
	{
		m[i]=k[i]=m1[i]=m2[i]='\0';
	}

	srand((unsigned)time(NULL));

	if ((fp=fopen ("test.txt", "r")) == NULL)
	{
		perror ("File not exists!");
		return (-1);
	}

	if ((fgets (m, SIZE, fp) != NULL))
	{

// Elimino il carattere RETURN dalla stringa letta

		if ((ret=strchr(m, RETURN)) != NULL)
		{
			ret[0]=0;
		}

		if ((len=strlen(m)) > SIZE)
		{
			perror ("String too long!");
			return (-3);
		}
	}
	else
	{
		perror ("Read string error!");
		return (-2);
	}

// In questo punto la stringa m ha meno di SIZE caratteri ed è ben formata

	do
	{
		printf ("Scelta:\n");
		printf ("   1- Immettere chiave di almeno %d caratteri\n", len);
		printf ("   2- Generazione casuale della chiave\n");

// il %*c serve per buttar via il \n alla fine dell'input

		scanf ("%d%*c", &scelta);
	}
	while ((scelta < 1) || (scelta > 2));

	switch (scelta)
	{
		case 1:
			printf ("Immissione di chiave di almeno %d caratteri\n", len);
			immissione(k, len);
			break;
		case 2:
			printf ("Generazione casuale della chiave\n");
			generazione(k, len);
			break;
	}

	xorwise(m1,m,k,len);
	xorwise(m2,m1,k,len);

	printf("\n");
//	printf("%s\n", "Stringa da criptare");
//	print_array(m, len);
//	printf("%s\n", "Chiave");
//	print_array(k, len);
//	printf("%s\n", "Stringa criptata");
//	print_array(m1, len);
//	printf("%s\n", "Stringa decriptata");
//	print_array(m2, len);

//	printf("\n");
//	printf("\n");
//	printf("\n");

	printf("%s\n", "Stringa da criptare");
	printf("%s\n", m);
	printf("%s\n", "Stringa decriptata");
	printf("%s\n", m2);

	fclose (fp);
	return (0);
}
