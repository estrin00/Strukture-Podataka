#define _CRT_NO_SECURE_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char grad[50];
	int stanovnici;
	position next;
}lista;

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
	char drzava[50];
	position lista;
	pozicija lijevo;
	pozicija desno;
}stablo;

pozicija stvoriElUStablu(pozicija);
pozicija procitajDrzave(pozicija, char*);
pozicija unosStabla(pozicija, char*, char*);
pozicija nadiDrzavu(pozicija, char*);
int inorder(pozicija);
int stvoriListu(position, char*, int);
position procitajGradove(position, char*);
int ispisListe(position);
position stvoriElListe(position);
int ispis(position, int);

int main()
{

	pozicija root = NULL;
	pozicija current = NULL;

	char datoteka[50] = "drzave.txt";
	char drzava[50] = { 0 };
	int a = 0;
	int br;

	root = stvoriElUStablu(root);
	root = procitajDrzave(root, datoteka);

	inorder(root);

	printf("Upisi broj 1 za odabir drzave, a 2 za izlaz iz petlje.\n");

	while (1)
	{
		scanf("%d", &a);
		
		switch (a)
		{
			case '1':
				printf("Odaberi drzavu: ");
				scanf(" %s", drzava);
				current = nadiDrzavu(root, drzava);

				if (current == NULL)
				{
					printf("Odabrana drzava ne postoji u datoteci!\n");
					return 0;
				}

				printf("Gradovi s brojem stanovnika vecih od unesenih / upisi br: ");
				scanf("%d", &br);

				ispis(current->lista, br);
				
				break;

			case '2':
				printf("Izlaz iz petlje.\n");
				break;
		}

		break;
	}

	return 0;
}

position stvoriElUListi(position p)
{

	p = (position)malloc(sizeof(lista));

	if (p == NULL)
	{
		printf("Greska u alociranju memorije");
		return NULL;
	}

	strcpy(p->grad, "");
	p->stanovnici = 0;
	p->next = NULL;

	return p;
}

pozicija stvoriElUStablu(pozicija p)
{
	p = (pozicija)malloc(sizeof(stablo));

	if (p == NULL)
	{
		printf("Greska u alociranju memorije.");
		return -1;
	}

	p->lijevo = NULL;
	p->desno = NULL;
	p->lista = NULL;

	strcpy(p->drzava, "");

	return p;
}

pozicija procitajDrzave(pozicija p, char* datoteka)
{

	FILE* fp = NULL;

	char drzava[50] = { 0 };
	char drzDat[50] = { 0 };

	fp = fopen(datoteka, "r");

	if (fp == NULL)
	{
		printf("Ne moze otvoriti datoteku!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s\n", drzava, drzDat);
		p = unosStabla(p, drzava, drzDat);
	}

	fclose(fp);

	return p;
}

pozicija unosStabla(pozicija p, char* drzava, char* drzDat)
{

	if (p == NULL)
	{
		p = stvoriElUStablu(p);

		strcpy(p->drzava, drzava);

		p->lista = NULL;
		p->lista = procitajGradove(p->lista, drzDat);

	}

	else if (strcmp(p->drzava, drzava) > 0)
		p->lijevo = unosStabla(p->lijevo, drzava, drzDat);

	else if (strcmp(p->drzava, drzava) < 0)
		p->desno = unosStabla(p->desno, drzava, drzDat);

	return p;
}

//149 linija kod nje stala

position procitajGradove(position p, char* datoteka)
{

	FILE* fp = NULL;
	char grad[50] = { 0 };
	int stanovnici = 0;

	p = stvoriElUListi(p);

	fp = fopen(datoteka, "r");

	if (fp == NULL)
	{
		printf("Ne moze otvoriti datoteku!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d", grad, &stanovnici);
		stvoriListu(p, grad, stanovnici);
	}

	fclose(fp);

	return p;
}

int stvoriListu(position p, char* grad, int stanovnici)
{

	position q = NULL;

	q = stvoriElListe(p);

	strcpy(q->grad, grad);

	q->stanovnici = stanovnici;
	
		while (p->next != NULL)
		{
			if (q->stanovnici < p->next->stanovnici)
				break;

			else if (q->stanovnici == p->next->stanovnici)
			{
				if (strcmp(q->grad, p->next->grad) < 0)
					break;

				else if (strcmp(q->grad, p->next->grad) > 0)
				{
					p = p->next;
					continue;
				}
			}
			p = p->next;
		}

		q->next = p->next;
		p->next = q;

		return 0;
}

int inorder(pozicija p)
{

	if (p == NULL)
		return 0;

	else
	{
		inorder(p->lijevo);

		printf("%s:\n", p->drzava);

		ispisListe(p->lista);

		inorder(p->desno);

	}

	return 0;
}

int ispisListe(position p)
{

	if (p == NULL)
		return 0;

	else
	{
		p = p->next;

		while (p != NULL)
		{
			printf(" %s-%d ", p->grad, p->stanovnici);
			p = p->next;
		}

	}

	return 0;

}

pozicija nadiDrzavu(pozicija p, char* drzava)
{

	if (p == NULL)
		return NULL;

	else if (strcmp(drzava, p->drzava) == 0)
		return p;

	else if (strcmp(drzava, p->drzava) > 0)
		return nadiDrzavu(p->desno, drzava);

	return nadiDrzavu(p->lijevo, drzava);
}

int ispis(position p, int br)
{

	while (p != NULL)
	{
		if (br < p->stanovnici)
			printf("%s ~ %d ", p->grad, p->stanovnici);

		p = p->next;
	}

	return 0;
}