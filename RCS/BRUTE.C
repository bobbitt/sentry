head	1.1;
access;
symbols;
locks;
comment	@ * @;


1.1
date	95.08.09.11.09.43;	author MIKE;	state Exp;
branches;
next	;


desc
@Brute Force Password Checker.
@


1.1
log
@Initial revision
@
text
@#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include "crypt.c"

#define MAXLEN	15

const char str[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

FILE *log;
unsigned long rd,sd;
unsigned int LEN,tc[MAXLEN],su[MAXLEN],max,min;
char te[MAXLEN+1],nut[14],salt[3];
struct date da;
struct time ti;

int tsk(void);
int incr(int c);
void main(void);

int tsk(void)
/*
	tsk(void) is the function called when the user attempts to exit via
	CTRL-C or CTRL-BREAK. The attempt is logged, and the computer is locked
	up to prevent any further attempts.
*/
{
int x;
unsigned long ut;
	fclose(log);
	if ((log=fopen("brute.brk","w"))==NULL)
	{
		printf("\nERROR opening brute.brk\n");
		exit(1);
	}
	getdate(&da);
	gettime(&ti);
	ut=dostounix(&da,&ti);
	ut-=sd;
	ut+=rd;
	fprintf(log,"%d\n%d\n",LEN,min);
	fprintf(log,"%lu\n",ut);
	fprintf(log,"%s\n",nut);
	fprintf(log,"%s\n",te);
	for(x=0;x<LEN;x++)
		fprintf(log,"%d\n",tc[x]);
	fclose(log);
	exit(1);
	return(0);
}

int incr(int c)
{
	if (c==LEN)
		return(0);
	tc[c]++;
	te[c]=str[tc[c]];
	if (tc[c]==max)
	{
		tc[c]=0;
		te[c]=str[0];
		if (kbhit())
			printf("\n%s",te);
		return(incr(c+1));
	}
	return(1);
}

void main(void)
{
unsigned int x;
signed int g=1;
	ctrlbrk(tsk);
	rd=0;
	for(x=0;x<LEN;x++)
		su[x]=0;
	if ((log=fopen("brute.brk","r"))==NULL)
	{
		printf("\nWhat is the estimated length? ");
		scanf("%d",&LEN);
		printf("\nWhat is the minimum length? ");
		scanf("%d",&min);
		te[LEN+1]=0;
		printf("\nEncrypted? ");
		scanf("%s",&nut);
	}
	else
	{
		fscanf(log,"%d\n",&LEN);
		fscanf(log,"%d\n",&min);
		fscanf(log,"%lu\n",&rd);
		fscanf(log,"%s\n",&nut);
		fscanf(log,"%s\n",&te);
		for(x=0;x<LEN;x++)
			fscanf(log,"%d\n",&su[x]);
	}
	fclose(log);
	if ((log=fopen("brute.log","w"))==NULL)
	{
		printf("\nERROR opening brute.log\n");
		exit(1);
	}
	strncpy(salt,nut,2);
	max=strlen(str);
	getdate(&da);
	gettime(&ti);
	sd=dostounix(&da,&ti);
	printf("\nSearch started at %d:%d:%d.%d on %d/%d/%d.",ti.ti_hour,ti.ti_min,ti.ti_sec,ti.ti_hund,da.da_day,da.da_mon,da.da_year);
	fprintf(log,"\nSearch started at %d:%d:%d.%d on %d/%d/%d.",ti.ti_hour,ti.ti_min,ti.ti_sec,ti.ti_hund,da.da_day,da.da_mon,da.da_year);
	while(LEN>min)
	{
		printf("\nChecking length %d...",LEN);
		fprintf(log,"\nChecking length %d...",LEN);
		for(x=0;x<LEN;x++)
		{
			tc[x]=su[x];
			te[x]=str[tc[x]];
		}
		while(incr(0))
		{
			if (!strcmp(nut,UNIXcrypt(te,salt)))
			{
				printf("\n*** FOUND: %s",te);
				fprintf(log,"\n*** FOUND: %s",te);
				min=LEN;
				break;
			}
		}
		g=(abs(g)+1)*(-g/abs(g));
		LEN+=g;
	}
	getdate(&da);
	gettime(&ti);
	printf("\nSearch ended at %d:%d:%d.%d on %d/%d/%d.",ti.ti_hour,ti.ti_min,ti.ti_sec,ti.ti_hund,da.da_day,da.da_mon,da.da_year);
	fprintf(log,"\nSearch ended at %d:%d:%d.%d on %d/%d/%d.",ti.ti_hour,ti.ti_min,ti.ti_sec,ti.ti_hund,da.da_day,da.da_mon,da.da_year);
}
@
