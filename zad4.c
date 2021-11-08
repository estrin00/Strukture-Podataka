#include<stdio.h>
#include<string.h>

#define MAXSIZE (1024)

typedef struct polinom* pozicija;
struct polinom {
	int potencija;
	int koeficijent;
	pozicija next;
};

int unos(pozicija,pozicija);
int zbroj(pozicija, pozicija, pozicija);
int umnozak(pozicija, pozicija, pozicija);
void ispis(pozicija);

int main()
{
	struct polinom head1;
	struct polinom head2;
	struct polinom headZbr;
	struct polinom headUmn;

	head1.next = NULL;
	head2.next = NULL;
	headZbr.next = NULL;
	headUmn.next = NULL;

	unos(&head1,&head2);
	zbroj(&head1,&head2,&headZbr);
	umnozak(&head1,&head2,&headUmn);
	ispis(&headZbr);
	ispis(&headUmn);
	return 0;
}

int unos(pozicija p1, pozicija p2)
{

	FILE* dat = NULL;
	dat = fopen("polinomi.txt", "r");
	if (dat == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return 1;
	}


	char buffer[MAXSIZE] = { 0 };
	int brojac;


	fgets(buffer, MAXSIZE, stdin);
	while (strlen(buffer) > 0)
	{
		sscanf(buffer, "%d %d %n", &p1->koeficijent, &p1->potencija, &brojac);
	}

	fgets(buffer, MAXSIZE, stdin);
	while (strlen(buffer) > 0)
	{
		sscanf(buffer, "%d %d %n", &p2->koeficijent, &p2->potencija, &brojac);
	}

	fclose(dat);
	return 0;
}

int zbroj(pozicija p1, pozicija p2, pozicija p)
{
	while (p1->next != NULL && p2->next != NULL)
	{
		pozicija q = NULL;
		q = (pozicija)malloc(sizeof(struct polinom));
		
		if (q == NULL)
		{
			printf("Greska u alociranju memorije!\n");
			return 1;
		}

		q->next = NULL;

		if (p1->next->potencija > p2->next->potencija)
		{
			q->potencija = p1->next->potencija;
			q->koeficijent = p1->next->koeficijent;
			p1 = p1->next;
		}

		else if (p1->next->potencija < p2->next->potencija)
		{
			q->potencija = p2->next->potencija;
			q->koeficijent = p2->next->koeficijent;
			p2 = p2->next;
		}

		else
		{
			q->potencija = p1->next->potencija;
			q->koeficijent = (p1->next->koeficijent + p2->next->koeficijent);
			p1 = p1->next;
			p2 = p2->next;
		}
		p->next = q;
		p2 = p2->next;
	}

	pozicija temp;

	if (p1->next == NULL)
		temp = p2->next;
	else
		temp = p1->next;

	while (temp != NULL)
	{
		pozicija q = NULL;
		q = (pozicija)malloc(sizeof(struct polinom));

		if (q == NULL)
		{
			printf("Greska u alokaciji memorije!\n");
			return 1;
		}

		q->next = NULL;
		q->eksponent = temp->eksponent;
		q->koeficijent = temp->koeficijent;

		p->next = q;
		p = q;

		temp = temp->next;
	}
	return 0;

}

int umnozak(pozicija p1, pozicija p2, pozicija p)
{

	p1=p1->next;
	p2=p2->next;
	
	struct polinom pol;

	pozicija q=NULL;
	q=(pozicija)malloc(sizeof(polinom));
	
	if(q==NULL)
	{
		printf("Greska u alokaciji memorije!");
		return -1;
	}

	q->next=NULL;
	pol.next=q;

	while(p1!=NULL)
	{
		while(p2!=NULL)
		{
			q->potencija=p1->potencija + p2->potencija;
			q->koeficijent=(p1->koeficijent)*(p2->koeficijent);

			zbroj(&pol,p,p);
			p2=p2->next;
		}

		pozicija pocetakP2;
		p2=pocetakP2;
		p1=p1->next;
	}

	return 0;

}

void ispis(pozicija p)
{
	while(p!=NULL)
	{
		printf("%d %d\n",p->koeficijent,p->potencija);
		p=p->next;
	}
}