#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
	int el;
	pozicija desno;
	pozicija lijevo;
}stablo;

struct _lista;
typedef struct _lista* pozicijaL;
typedef struct _lista
{
	int elem;
	pozicijaL next;
}lista;

int inOrder(pozicija p, pozicijaL head);
pozicija stvoriP(pozicija p);
pozicija insert(pozicija p, int elem);
pozicija replace(pozicija p);
int sum(pozicija p);
pozicija random(pozicija p);
int umetniK(pozicijaL head, int br);
pozicijaL nadjiZ(pozicijaL head);
int umetni(pozicijaL head, int br);
int ispisUDat(pozicijaL q1, pozicijaL q2, pozicijaL q3, char* datoteka);


int main()
{
	
	pozicija root = NULL;
	pozicijaL head1 = NULL, head2 = NULL, head3 = NULL;

	char name[50] = "zad9.txt";

	root = stvoriP(root);

	head1 = (pozicijaL)malloc(sizeof(lista));
	head1->next = NULL;

	head2= (pozicijaL)malloc(sizeof(lista));
	head2->next = NULL;

	head3 = (pozicijaL)malloc(sizeof(lista));
	head3->next = NULL;

	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 11);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 7);

	inOrder(root, head1);

	root = replace(root);

	inOrder(root, head2);

	root = stvoriP(root);
	
	root = random(root);

	inOrder(root, head3);

	ispisUDat(head1->next, head2->next, head3->next, name);

	return 0;

}

pozicija stvoriP(pozicija p)
{
	if (p != NULL)
	{
		p->lijevo = stvoriP(p->lijevo);
		p->desno = stvoriP(p->desno);
		free(p);
	}

	return NULL;
}

int inOrder(pozicija p, pozicijaL head)
{
	if (p == NULL)
		return 0;

	inOrder(p->lijevo, head);

	umetniK(head, p->el);

	inOrder(p->desno, head);

	return 0;

}

pozicija insert(pozicija p, int elem)
{
	if (p == NULL)
	{
		p = (pozicija)mallc(sizeof(stablo));

		p->el = elem;
		p->lijevo = NULL;
		p->desno = NULL;

	}

	else if (elem >= p->el)
	{
		p->lijevo = insert(p->lijevo, elem);
	}

	else if(elem <=p->el)
	{
		p->desno = insert(p->desno, elem);
	}

	return p;

}

int suma(pozicija p)
{
	int zbr=0;

	if (p == NULL)
		return zbr;

	if (p->lijevo != NULL)
		zbr += p->lijevo->el + suma(p->lijevo);

	if (p->desno != NULL)
		zbr += p->desno->el + suma(p->desno);

	return zbr;
}

pozicija replace(pozicija p)
{
	if (p!= NULL)
	{
		p->el = suma(p);
		p->lijevo = replace(p->lijevo);
		p->desno = replace(p->desno);
	}

	return p;
}

pozicija random(pozicija p)
{
	int i = 0, broj = 0;

	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		broj = (rand() % (90 - 10 + 1)) + 10;
		p = insert(p, broj);
	}

	return p;
}

int umetniK(pozicijaL head, int br)
{
	pozicijaL zadnji = NULL;
	zadnji = nadjiZ(head);
	umetni(zadnji, br);

	return 0;
}

pozicijaL nadjiZ(pozicijaL head)
{
	while (head->next != NULL)
		head = head->next;

	return head;
}

int umetni(pozicijaL head, int br)
{
	pozicijaL prvi = NULL;
	prvi = (pozicijaL)malloc(sizeof(lista));

	if (prvi == NULL)
		return -1;
	
	prvi->elem = br;
	prvi->next = head->next;
	head->next = prvi;

	return 0;
}
 
int ispisUDat(pozicijaL q1, pozicijaL q2, pozicijaL q3, char* datoteka)
{
	FILE* fp = NULL;
	fp = fopen(datoteka, "w");

	if (fp == NULL)
	{
		printf("Datoteka se ne moze otvoriti!");
		return -1;
	}

	while (q1 != NULL)
	{
		fprintf(fp, "%d\t", q1->elem);
		q1 = q1->next;
	}

	fprintf(fp, "\n");

	while (q2!=NULL)
	{
		fprintf(fp, "%d\t", q2->elem);
		q2 = q2->next;
	}

	fprintf(fp, "\n");

	while (q3!=NULL)
	{
		fprintf(fp, "%d\t", q3->elem);
		q3 = q3->next;
	}

	fclose(fp);

	return 0;
}