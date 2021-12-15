#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct _direktorij* position;
typedef struct _direktorij
{
	char ime[100];
	position next;
	position child;
}direktorij;

typedef struct _stog* pozicija;
typedef struct _stog
{
	position el;
	pozicija next;
}stog;

int md(position, pozicija);
int print(position);
pozicija cd(position);
int push(position, pozicija);
position cdt(pozicija);
position find(position, int);
position stvori1(int);
pozicija stvori2(int);
int umetniPodatke(position);

int main()
{

	position root = NULL;
	root = stvori1(1);

	position current = root;
	pozicija stack = NULL;
	stack = stvori2(1);

	char zeljeniDirektorij='0';

	printf("Unesi ime root direktorija:\n");
	scanf("%s", root->ime);
	strcat(root->ime, "://");

	while (zeljeniDirektorij != 'i')
	{
		printf("Odaberi broj za ulazak u zeljeni direktorij:\n");
		printf("1 = md\n");
		printf("2 = print directory\n");
		printf("3 = cd\n");
		printf("4 = povratak u prethodni direktorij\n");
		printf("i = izlaz\n");
		printf("Zeljeni direktorij: ");
		scanf(" %c", &zeljeniDirektorij);
	}

	switch (zeljeniDirektorij)
	{

	case '1':
	{
		md(current, stack);
		break;
	}

	case '2': 
	{
		print(current);
		break;
	}
	
	case'3':
	{
		current = cd(current);
		break;
	}
		
	case '4':
	{
		printf("Izlaz\n");
		break;
	}
	default:
	{
		printf("Greska u odabiru!\n");
	}

	}
	
	return 0;
}

position cdt(pozicija stack)
{

	pozicija temp = NULL;
	position q = NULL;

	q = stvori1(1);

	temp = stack->next;
	q = temp->el;
	stack->next = temp->next;

	free(temp);
	return q;

}

int md(position current, pozicija stack)
{

	position q = NULL;

	if (current == NULL)
	{
		printf("Root direktorij ne postoji!\n");
		return -1;
	}

	q = stvori1(1);
	umetniPodatke(q);

	push(current, stack);
	
	if (current->child == NULL)
	{
		current->child = q;
		return 0;
	}

	current = current->child;

	while (current->next != NULL)
	{
		current = current->next;
	}

	q->next = current->next;
	current->next = q;

	return 0;

}

int print(position current)
{

	int brDirektorija = 0;
	
	if (current == NULL)
	{
		printf("Ne postoji root direktorij!\n");
		return -1;
	}

	print("Direktorij od %s:\n", current->ime);
	current = current->child;

	if (current == NULL)
	{
		return -1;
	}

	while (current != NULL)
	{
		printf(" %s\n", current->ime);
		current = current->next;
		brDirektorija++;
	}

	printf("Broj direktorija je %d\n", brDirektorija);

	return 0;

}

position cd(position current)
{

	position q = NULL;
	q = stvori1(1);

	char ime[20] = { 0 };

	printf("Zeljeni direktorij:\n");
	scanf("%s", ime);

	q = find(current, ime);

	return q;

}

position find(position p, char* ime)
{

	if (p == NULL)
	{
		printf("Greska!\n");
		return NULL;
	}

	p = p->child;

	while (p != NULL && strcmp(p->ime, ime) != 0)
	{
		p = p->next;
	}

	if (p == NULL)
	{
		printf("Zeljeni direktorij ne postoji!\n");
		return NULL;
	}

	else
	{
		printf("Pronadjen je direktorij %s\n", p->ime);
	}

	return p;
}

int umetniPodatke(position q)
{
	printf("Unesi ime direktorija:\n");
	scanf("%s", q->ime);

	return 0;
}

position stvori1(int n)
{

	position q;
	q = (position)malloc(n * sizeof(direktorij));

	if (q == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	q->next = NULL;
	q->child = NULL;

	return q;
}

pozicija stvori2(int n)
{

	pozicija q;
	q = (pozicija)malloc(n * sizeof(stog));

	if (q == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	q->el = NULL;
	q->next = NULL;

	return q;
}

int push(position current, pozicija stack)
{

	pozicija q = NULL;
	q = stvori2(1);

	q->el = current;
	q->next = stack->next;
	stack->next = q;

	return 0;
}
