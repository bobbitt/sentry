#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include "crypt.c"

/*
Creation file contains:

SALT
Registration #
Registered To

bd infile outfile
*/

char sa[4],st[31];
int fo;
long re;
FILE *in,*out;
struct date da;
struct time ti;

void main(int argc,char *agrv[]);
void bd(void);
void su(void);
void rezz(void);
void autol(void);

void bd(void)
{
int y,z;
long reg,dd;
	cprintf("\n\r Reg#: ");
  scanf("%lu",&reg);
  cprintf("\n\r Days: ");
  scanf("%d",&y);
	getdate(&da);
	ti.ti_min=0;
	ti.ti_hour=0;
	ti.ti_hund=0;
	ti.ti_sec=0;
	for(z=0;z<y;z++)
	{
		dd=dostounix(&da,&ti);
		re=dd-reg;
		ltoa(re,st,10);
		strcpy(st,UNIXcrypt(st,sa));
		if (fo)
			fprintf(out,"\n[%02d/%02d/%02d]  %lu  --  %s\n",da.da_year,da.da_mon,da.da_day,re,st);
		else
			cprintf("\n\r[%02d/%02d/%02d]  %lu  --  %s\r\n",da.da_year,da.da_mon,da.da_day,re,st);
		dd+=86400L;
		unixtodos(dd,&da,&ti);
	}
}

void su(void)
{
	strcpy(st,UNIXcrypt("Sentry~",sa));
	if (fo)
		fprintf(out,"\n%s",st);
	else
		cprintf("\n\r%s\n\r",st);
}

void rezz(void)
{
int x;
long y;
char temp[50],na[50];
 	cprintf("\n\r Reg To: ");
  gets(temp);
  gets(temp);
  cprintf("\n\r Reg#: ");
  scanf("%lu",&y);
	x=0;
	while (y>0)
	{
		x+=y-(y/10)*10;
		y/=10;
	}
	itoa(x,na,10);
	if (fo)
		fprintf(out,"%s",UNIXcrypt(temp,na));
	else
		cprintf("%s",UNIXcrypt(temp,na));
}

void autol(void)
{
long reg,tr;
int x,y;
char nam[81],nsa[5],rch[31];
  while (fscanf(in,"%s\n",&sa)!=EOF)
  {
	  fscanf(in,"%lu\n",&reg);
    fgets(nam,80,in);
    nam[strlen(nam)-1]=0;
  	x=0;
    tr=reg;
	  while (tr>0)
  	{
	  	x+=tr-(tr/10)*10;
		  tr/=10;
  	}
    itoa(x,nsa,10);
    strcpy(rch,UNIXcrypt(nam,nsa));
    for(y=2;y<strlen(rch);y++)
      rch[y-2]=rch[y];
    rch[y-2]=0;
    fprintf(out,"Registered To: %s\n",nam);
    fprintf(out,"Registration Number: %lu\n",reg);
    fprintf(out,"Registration Code: %s%s\n",rch,sa);
    itoa(x-1,nsa,10);
    strcpy(rch,UNIXcrypt(nam,nsa));
    for(y=2;y<strlen(rch);y++)
      rch[y-2]=rch[y];
    rch[y-2]=0;
    fprintf(out,"AV Registration Code: %s%s\n\n",rch,sa);
  }
}

void main(int argc,char *argv[])
{
int x;
	fo=0;
  switch (argc)
  {
  	case 2:
	  	if ((out=fopen(argv[1],"a"))==NULL)
		  {
			  cprintf("File error [%s].\n\r",argv[1]);
  			exit(1);
	  	}
      fo=1;
      break;
    case 3:
	  	if ((in=fopen(argv[1],"r"))==NULL)
		  {
			  cprintf("File error [%s].\n\r",argv[1]);
  			exit(1);
	  	}
	  	if ((out=fopen(argv[2],"a"))==NULL)
		  {
			  cprintf("File error [%s].\n\r",argv[2]);
  			exit(1);
	  	}
      fo=2;
      break;
    default:
  		fo=0;
      break;
  }
  if (fo<2)
  {
   	cprintf("\n\r\n\r Salt: ");
    scanf("%s",&sa);
  	cprintf("\n\r\n\r1. SU\n\r2. BD\n\r3. RE\n\r");
	  x=getch();
    	if (x=='1')
		  su();
      if (x=='2')
        bd();
	    if (x=='3')
		    rezz();
  }
  else
    autol();
  fclose(in);
  fclose(out);
}
