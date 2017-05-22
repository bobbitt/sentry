#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include "crypt.c"

#define MAXLEN	15

const char str[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

FILE *logf;
unsigned long rd,sd;
unsigned int LEN,tc[MAXLEN],su[MAXLEN],max,min,bk=0;
char te[MAXLEN+1],nut[14],salt[3];
struct date da;
struct time ti;

int tsk(void);
int incr(int c);
void main(void);

char *UNIXcrypt (char *pw, char *salt);
void ctrlbrk(int (*handler)(void));

int tsk(void)
/*
	tsk(void) is the function called when the user attempts to exit via
	CTRL-C or CTRL-BREAK.
*/
{
int x;
unsigned long ut;
	printf("Break\n");
	fclose(logf);
   if (bk)
   {
     if ((logf=fopen("brute.brk","w"))==NULL)
     {
	    printf("\nERROR opening brute.brk\n");
		 exit(1);
  	  }
	  getdate(&da);
	  gettime(&ti);
	  ut=dostounix(&da,&ti);
     ut-=sd;
	  ut+=rd;
	  fprintf(logf,"%d\n%d\n",LEN,min);
	  fprintf(logf,"%lu\n",ut);
	  fprintf(logf,"%s\n",nut);
	  fprintf(logf,"%s\n",te);
	  for(x=0;x<LEN;x++)
	    fprintf(logf,"%d\n",tc[x]);
	  fclose(logf);
   }
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
// Check for input
		if (kbhit())
			printf("\n%s",te);
// Check for input
		return(incr(c+1));
	}
	return(1);
}

void main(void)
{
unsigned int x;
signed int g=1;
char tt[80];
  setcbrk(1);
  ctrlbrk(tsk);
  rd=0;
  for(x=0;x<LEN;x++)
  	su[x]=0;
  if ((logf=fopen("brute.brk","r"))==NULL)
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
  	fscanf(logf,"%d\n",&LEN);
  	fscanf(logf,"%d\n",&min);
  	fscanf(logf,"%lu\n",&rd);
  	fscanf(logf,"%s\n",&nut);
  	fscanf(logf,"%s\n",&te);
  	for(x=0;x<LEN;x++)
  		fscanf(logf,"%d\n",&su[x]);
  }
  fclose(logf);
  if ((logf=fopen("brute.log","w"))==NULL)
  {
  	printf("\nERROR opening brute.log\n");
  	exit(1);
  }
  strncpy(salt,nut,2);
  max=strlen(str);
  getdate(&da);
  gettime(&ti);
  sd=dostounix(&da,&ti);
  sprintf(tt,"\nSearch started at %02d:%02d:%02d.%02d on %02d/%02d/%02d for [%s].\n",ti.ti_hour,ti.ti_min,ti.ti_sec,ti.ti_hund,da.da_day,da.da_mon,da.da_year,nut);
  printf("%s",tt);
  fprintf(logf,"%s",tt);
  bk=1;
  while(LEN>=min)
  {
  	printf("\nChecking length %d...",LEN);
  	fprintf(logf,"\nChecking length %d...",LEN);
  	for(x=0;x<LEN;x++)
  	{
  		tc[x]=su[x];
  		te[x]=str[tc[x]];
  	}
  	while(incr(0))
  	{
  		if (!strcmp(nut,UNIXcrypt(te,salt)))
  		{
  			sprintf(tt,"\n*** FOUND: [%s] = [%s]\n",nut,te);
         printf("%s",tt);
  			fprintf(logf,"%s",tt);
			min=LEN;
			break;
		}
	}
	g=(abs(g)+1)*(-g/abs(g));
	LEN+=g;
  }
  getdate(&da);
  gettime(&ti);
  rd+=(dostounix(&da,&ti)-sd);
  sprintf(tt,"\nSearch ended at %02d:%02d:%02d.%02d on %02d/%02d/%02d.\n",ti.ti_hour,ti.ti_min,ti.ti_sec,ti.ti_hund,da.da_day,da.da_mon,da.da_year);
  printf("%s",tt);
  fprintf(logf,"%s",tt);
  sprintf(tt,"\nSearch took %lu seconds total.",rd);
  printf("%s",tt);
  fprintf(logf,"%s",tt);
}
