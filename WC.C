#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dir.h>

void error(char *s)
{
  cprintf("%s\r\n",s);
  exit(1);
}

long count(const char *s)
{
FILE *fd;
char line[240];
long cc=0;
  if ((fd=fopen(s,"r"))!=NULL)
  {
    while (fgets(line,240,fd)!=NULL)
      cc++;
  }
  fclose(fd);
  return cc;
}

void main(void)
{
struct text_info sta; /* Startup video attributes */
struct ffblk ffblk;
int x,f=0;
long c=0;
  gettextinfo(&sta);
  textcolor(WHITE);
  x=findfirst("*.h",&ffblk,0);
  while (!x)
  {
    c+=count(ffblk.ff_name);
    x=findnext(&ffblk);
    f++;
  }
  x=findfirst("*.c",&ffblk,0);
  while (!x)
  {
    c+=count(ffblk.ff_name);
    x=findnext(&ffblk);
    f++;
  }
  cprintf("\r\nTotal files: %d\r\nTotal lines: %lu\r\nAvg: %lu\r\n",f,c,c/f);
  textattr(sta.attribute);
  textmode(sta.currmode);
}
