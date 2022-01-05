// 10 a)
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
	char grad[50];
	int stanovnici;
	pozicija lijevo;
	pozicija desno;
}stablo;

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char drzava[50];
	pozicija stablo;
	position next;
}lista;

int procitajDrzave(position, char*);
int sortiraniUnosListe(position p, char*, char*);
pozicija stvoriStablo(pozicija, char*, int);
void print(pozicija);
int inorder(pozicija);
int ioIspisVeceg(pozicija, int);
position stvoriElUListi(position);
position nadiDrz(position, char*);
pozicija procitajGradove(pozicija, char*);

int main()
{

	position head = NULL;
	position p = NULL;

	char datoteka[50] = "drzave.txt";
	int a = 0, br=0;
	char drzava[50] = { 0 };

	head = stvoriElUListi(head);
	p = stvoriElUListi(p);

	procitajDrzave(head, datoteka);

	print(head->next);

	printf("Upisi broj 1 za izabrati drzavu, a broj 2 za izaci iz petlje:\n");

	while(1)
	{
		scanf("%d", &a);
		switch (a)
		{
			case '1':
				printf("Izaberi drzavu: ");
				scanf(" %s", drzava);

				p = nadiDrz(head, drzava);

				if (p == NULL)
				{
					printf("Drzava ne postoji u datoteci!\n");
					return -1;
				}

				printf("Gradovi s brojem stanovnika vecih od unesenih / upisi br: ");
				scanf("%d", &br);

				ioIspisVeceg(p->stablo, br);

				break;

			case '2':
				printf("Odabrali sete izlaz iz petlje!\n");
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
		printf("Greska pri alociranju!\n");
		return -1;
	}

	strcpy(p->drzava, "");

	p->next = NULL;
	p->stablo = NULL;

}

int procitajDrzave(position p, char* datoteka)
{

	FILE* fp = NULL;

	char imeDrzave[50] = { 0 };
	char drzDat[50] = { 0 };

	fp = fopen(datoteka, "r");
	if (fp == NULL)
	{
		printf("Ne moze otvoriti datoteku!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp," %s %s\n", imeDrzave, drzDat);
		sortiraniUnosListe(p, imeDrzave, drzDat);
	}

	fclose(fp);

	return 0;
}

int sortiraniUnosListe(position p, char* imeDrzave, char* drzDat)
{

	position q = NULL;
	q = (position)malloc(sizeof(lista));
	
	if (q == NULL)
	{
		printf("Greska u alociranju memorije!\n");
		return -1;
	}

	char temp[50] = { 0 };

	strcpy(q->drzava, imeDrzave);

	q->stablo = NULL;
	q->stablo = procitajGradove(q->stablo, drzDat);

	strcpy(temp, imeDrzave);

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;

			break;
		}

		else if (strcmp(temp, p->next->drzava) < 0)
		{
			q->next = p->next;
			p->next = q;

			break;
		}

		p = p->next;
	}

	return 0;
}

pozicija procitajGradove(pozicija root, char* drzDat)
{

	FILE* fp = NULL;
	char grad[50] = { 0 };
	int brStanovnika = 0;

	fp = fopen(drzDat, "r");

	if (fp == NULL)
	{
		printf("Ne moze otvoriti datoteku!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d\n", grad, &brStanovnika);
		root = stvoriStablo(root, grad, brStanovnika);
	}

	fclose(fp);

	return root;
}

pozicija stvoriStablo(pozicija p, char* grad, int stanovnici)
{

	if (p == NULL)
	{
		p = (pozicija)malloc(sizeof(stablo));

		if (p == NULL)
		{
			printf("Greska u alociranju!\n");
			return NULL;
		}

		strcpy(p->grad, grad);

		p->stanovnici = stanovnici;
		p->lijevo = NULL;
		p->desno = NULL;

	}

	else if (stanovnici == p->stanovnici)
	{
		if (strcmp(grad, p->grad) < 0)
			p->lijevo = stvoriStablo(p->lijevo, grad, stanovnici);
		else if (strcmp(grad, p->grad) > 0)
			p->desno = stvoriStablo(p->desno, grad, stanovnici);
	}

	else 
	{
		if (stanovnici < p->stanovnici)
			p->lijevo = stvoriStablo(p->lijevo, grad, stanovnici);

		else if (stanovnici > p->stanovnici)
			p->desno = stvoriStablo(p->desno, grad, stanovnici);

	}

	return p;

}

void print(position p)
{
	while (p != NULL)
	{
		printf("%s", p->drzava);
		inorder(p->stablo);
		p = p->next;
	}
}

int inorder(pozicija p)
{

	if (p == NULL)
	{
		return 0;
	}
		

	inorder(p->lijevo);
	printf("%s %d ", p->grad, p->stanovnici);
	inorder(p->desno);

	return 0;

}

position nadiDrzavu(position p, char* drzava)
{

	while (p->next != NULL && strcmp(drzava, p->drzava) != 0)
		p = p->next;

	return p;
}

int ioIspisVeceg(pozicija p, int br)
{

	if (p == NULL)
	{
		return 0;
	}

	ioIspisVeceg(p->lijevo, br);

	if (br < p->stanovnici)
		printf("%s %d\n", p->grad, p->stanovnici);

	ioIspisVeceg(p->desno, br);

	return 0;
}
