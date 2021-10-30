#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct person* position;
struct person {
	char name[30];
	char surname[30];
	int year;
	position next;

};

int InsertAtTheBeginning(position p);
int Print(position p);
int InsertAtTheEnd(position p);
int SearchBySurname(position p);
int Delete(position p);


int main()
{
	struct person head;
	head.next = NULL;
	char option;

	printf("Unesi p za unos na pocetak, i za ispis, k za unos na kraj,t za trazenje po prezimenu i b za brisanje elementa:\n");
	scanf("%c", &option);

	if (option == 'p')
		InsertAtTheBeginning(&head);
	
	else if (option == 'i')
		Print(head.next);
	
	else if (option == 'k')
		InsertAtTheEnd(&head);
	
	else if (option == 't')
		SearchBySurname(head.next);
	
	else if (option == 'b')
		Delete(&head);
	
	else
		printf("Greska!\n");
	

	return 0;
}

int InsertAtTheBeginning(position p)
{
	position q = NULL;
	q = (position)malloc(sizeof(struct person));

	if (q == NULL)
	{
		printf("Greska, memorija nije alocirana!\n");
		return 1;
	}

	printf("Ime osobe: ");
	scanf("%s", q->name);
	printf("Prezime osobe: ");
	scanf("%s", q->surname);
	printf("Godine: ");
	scanf("%d", &q->year);

	q->next = p->next;
	p->next = q;
	
	return 0;
}

int InsertAtTheEnd(position p)
{
	while (p->next != NULL)
	{
		p = p->next;
	}

	position q = NULL;
	q = (position)malloc(sizeof(struct person));

	if (q == NULL)
	{
		printf("Greska, memorija nije alocirana!\n");
		return 1;
	}

	printf("Ime osobe: ");
	scanf("%s", q->name);
	printf("Prezime osobe: ");
	scanf("%s", q->surname);
	printf("Godine: ");
	scanf("%d", &q->year);

	q->next = p->next;
	p->next = q;

	return 0;
}

int SearchBySurname(position p)
{
	char surn[50];
	printf("Prezime trazene osobe: ");
	scanf(" %s", &surn);

	while (p != NULL && strcmp(surn, p->surname) != 0)
	{
		p = p->next;
	}

	if (p == NULL)
		printf("Greska,takva osoba ne postoji!\n");
	else
		printf("Adresa osobe koju trazis je %d.\n", p);
	
	return 0;
}

int Delete(position p)
{
	position prev = NULL;
	char surn[50];

	printf("Unesi prezime osobe koju zelisi izbrisati s liste: ");
	scanf(" %s", &surn);

	while (p->next != NULL && strcmp(surn, p->surname) != 0)
	{
		prev = p;
		p = p->next;
	}

	if (prev != NULL && strcmp(surn, p->surname) == 0)
	{
		p = prev->next;
		prev->next = p->next;
		free(p);
	}

	return 0;
}
