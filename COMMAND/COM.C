#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

#define BUFSZ 8192
#define MAX 80

FILE* file1,*file2;
char temp[MAX],command_com[MAX],file_name[MAX];
int file_name_length;

void error(char *s);
FILE* scan_file(FILE* dmp);
void close_file(FILE* fn,FILE* dmp);
void main (void);

void error(char *s)
{
	unlink(temp);
	printf("%s\n",s);
	exit(1);
}

FILE* scan_file(FILE* dmp)
{
int yz,zz,bp,sp;
FILE* fn;
char buf[BUFSZ+2],ff[20];
  if ((fn=fopen(command_com,"rb"))==NULL)
		error("Error Opening COMMAND.COM!");
  bp=0;
  for(zz=0;zz<=file_name_length;zz++)
    ff[zz]=0;
	sp=1;
  while(sp)
  {
    yz=1;
    while(yz && !feof(fn))
    {
			buf[bp]=fgetc(fn);
      for(zz=0;zz<file_name_length-1;zz++)
        ff[zz]=ff[zz+1];
      ff[zz]=buf[bp];
      ff[zz+1]=0;
			yz=strcmp(ff,file_name);
			if (bp==BUFSZ)
			{
				for(zz=0;zz<=bp;zz++)
					fputc(buf[zz],dmp);
        bp=-1;
      }
      bp++;
		}
    if (yz)
			error("Cannot locate marker!");
		else
			if (bp>file_name_length)
				bp-=file_name_length;
			else
				error("Buffer underflow");
    sp--;
  }
	for(zz=0;zz<bp;zz++)
		fputc(buf[zz],dmp);
  return(fn);
}

void close_file(FILE* fn,FILE* dmp)
{
int zz,bp;
char buf[BUFSZ+2];
  bp=0;
  while(!feof(fn))
  {
		buf[bp]=fgetc(fn);
    if (feof(fn))
      bp--;
    if (bp==BUFSZ)
    {
      for(zz=0;zz<=bp;zz++)
        fputc(buf[zz],dmp);
      bp=-1;
    }
    bp++;
  }
  if (dmp)
    for(zz=0;zz<bp;zz++)
      fputc(buf[zz],dmp);
  fclose(fn);
  fclose(dmp);
}

void main (void)
{
int z;
char ca[MAX];
/****
	strcpy(file_name,"CONFIG.SYS");
	file_name_length=strlen(file_name);
	strcpy(command_com,"command.com");
  tmpnam(temp);
  if ((file2=fopen(temp,"wb"))==NULL)
    error("Error opening temp file!");
	file1=scan_file(file2);
	z=1;
	while(z)
	{
	printf("Enter a filename to replace CONFIG.SYS:");
	scanf("%s",&ca);
		z=strlen(ca)-10;
		if (z)
			printf("\nMust be 6 characters with a 3 character extension!\n\n");
	}
	strupr(ca);
	fputs(ca,file2);
	close_file(file1,file2);
	unlink(command_com);
	rename(temp,command_com);
****/
	z=1;
	strcpy(file_name,"AUTOEXEC.BAT");
	file_name_length=strlen(file_name);
	strcpy(command_com,"command.com");
	tmpnam(temp);
  if ((file2=fopen(temp,"wb"))==NULL)
    error("Error opening temp file!");
	file1=scan_file(file2);
	while(z)
	{
		printf("Enter a filename to replace AUTOEXEC.BAT:");
		scanf("%s",&ca);
		z=strlen(ca)-12;
		if (z)
			printf("\nMust be 8 characters with a 3 character extension!\n\n");
	}
	strupr(ca);
	fputs(ca,file2);
	close_file(file1,file2);
	unlink(command_com);
	rename(temp,command_com);
}
