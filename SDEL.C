#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dir.h>

#define WWW "http:/\/www.cipherlogic.on.ca"

void error(char *s)
{  
  cprintf("%s\r\n",s);
  exit(1);
}

void sunlink(const char *sul)
{
FILE *fd;
long c,cc;
  if ((fd=fopen(sul,"rb"))!=NULL)
  {
    if (fseek(fd,0L,SEEK_END))
      error("Error Scanning Temp File!");
    c=ftell(fd);
    fclose(fd);
    if ((fd=fopen(sul,"wb"))==NULL)
      error("Error Creating Temp File!");
    for(cc=0;cc<=c;cc++)
      fputc(random(256),fd);
  }
  fclose(fd);
  unlink(sul);
}

void main(int argc, char *argv[])
{
struct text_info sta; /* Startup video attributes */
struct ffblk ffblk;
int x;
  randomize();
  gettextinfo(&sta);
  textcolor(WHITE);
  if (argc<2)
  {
    cprintf("\r\nSDEL V1.0 - Secure Delete\r\n");
    cprintf("\r\nCopyright (C) 1995-1999 Cipher Logic Canada Inc.");
    cprintf("\r\nWritten by Michael A. Bobbitt for Sentry.\r\n");
    cprintf("\r\nIf you do not have all of Sentry, you can download it from:");
    cprintf("\r\n");
    cprintf(WWW);
    cprintf("\r\n");
    cprintf("\r\nA file deleted with sdel cannot be undeleted.");
    cprintf("\r\nThis makes sdel useful for disposing of sensitive or confidential files.\r\n");
    cprintf("\r\nUSAGE: sdel filename1 [filename2] [filename3] ...");
    cprintf("\r\nDOS wildcards can be used with any file name.");
    cprintf("\r\n\r\nEXAMPLE: sdel *.bak ..\\user.* d:\\sal??96.doc\r\n");
    exit(1);
  }
  while (argc>1)
  {
    x=findfirst(argv[argc-1],&ffblk,0);
    while (!x)
    {
      sunlink(ffblk.ff_name); 
      x=findnext(&ffblk);
    }
    argc--;
  }
  textattr(sta.attribute);
  textmode(sta.currmode);
}
