#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
	int el;
	pozicija desno;
	pozicija lijevo;
}stablo;

pozicija unos(pozicija, int);
void print(pozicija);
pozicija Min(pozicija);
pozicija Max(pozicija);
pozicija izbrisi(pozicija, int);
pozicija pronadji(pozicija);

int main()
{

	pozicija root = NULL;
	pozicija trazeni = NULL;

	char zeljenaOpcija = '0';
	int x = 0;

	while (zeljenaOpcija != 'i')
	{
		printf("Odabir funkcije:\n");
		printf("1 - unos\n");
		printf("2 - print\n");
		printf("3 - izbrisi\n");
		printf("4 - pronadji\n");

		printf("Zeljena funkcija: ");
		scanf(" %c",&zeljenaOpcija);

		switch (zeljenaOpcija)
		{
		case '1':
		{
			printf("Broj za unos:\n");
			scanf(" %d", &x);
			root = unos(root, x);
			break;
		}

		case'2':
		{
			if (root == NULL)
				printf("Stablo je prazno!\n");
			else
				print(root);
			break;
		}

		case'3':
		{
			printf("Broj koji se brise:\n");
			scanf(" %d", &x);
			root = izbrisi(root, x);
			break;
		}

		case'4':
		{
			printf("Broji koji se trazi:\n");
			scanf(" %d", &x);
			trazeni = pronadji(root, x);
			if (trazeni != NULL)
				printf("Trazeni element %d se nalazi na adresi %x.\n", trazeni->el, trazeni);
			else
				printf("Trazeni broj %d se ne moze pronaci!\n",x);
			break;
		}

		case'i':
		{
			printf("Izlaz!\n");
			break;
		}

		default:
		{
			printf("Pogresna opcija!\n");
		}

		}

	}

	return 0;

}
pozicija unos(pozicija p, int x)
{
	if (p == NULL)
	{
		p = (pozicija)malloc(sizeof(stablo));
		if (p)
		{
			p->el = x;
			p->lijevo = NULL;
			p->desno = NULL;
		}
		else if (p->el < x)
			p->desno = unos(p->desno, x);
		else if (p->el > x)
			p->lijevo = unos(p->lijevo, x);
		else
			printf("x vec postoji u stablu!\n");

		return p;
	}
}

void print(pozicija p)
{
	if (p != NULL)
	{
		print(p->lijevo);
		printf(" %d", p->el);
		print(p->desno);
	}
}

pozicija Min(pozicija p)
{
	if (p == NULL)
		return p;

	else if (p->lijevo == NULL)
		return p;

	else
		return Min(p->lijevo);
}

pozicija Max(pozicija p)
{

	if (p != NULL)
	{
		while (p->desno != NULL)
			p = p->desno;
	}

	return p;
}

pozicija pronadji(pozicija p, int x)
{
	if (p == NULL)
		return NULL;

	else
		if (p->el > x)
			return pronadji(p->lijevo, x);

		else if (p->el < x)
			return pronadji(p->desno, x);

		else
			return p;

}

pozicija izbrisi(pozicija p, int x)
{
	
	pozicija temp;

	if (p == NULL)
		printf("x nije pronadjen!\n");

	else if (p->el > x)
		p->lijevo = izbrisi(p->lijevo, x);

	else if (p->el < x)
		p->desno = izbrisi(p->desno, x);

	else
	{
		if (p->lijevo != NULL && p->desno != NULL)
		{
			temp = Min(p->desno);
			p->el = temp->el;
			p->desno = izbrisi(p->desno, temp->el);
			p->el = temp->el;
			p->lijevo = izbrisi(p->lijevo, p->el);
		}
		
		else
		{
			temp = p;
			if (p->lijevo == NULL)
				p = p->desno;
			else
				p = p->lijevo;
			free(temp);
		}

	}

	return p;
}
