head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.25.47;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.43.14;	author MIKE;	state Exp;
branches;
next	;


desc
@Functions common to Sentry.exe and Install.exe
@


5.0
log
@Version 5.0
@
text
@/*
  INCLUDES
*/
#ifndef INSTALL
#include "sentry.h"
#include "common.h"
#else
#include "install.h"
#endif

/*
  CONSTANTS
*/

const char errmsg[ERR][38]=  /* Listing of all error messages */
{
      {"Cannot Locate Environment."},
      {"Environment Overflow - Not Modified."},
      {"Error Creating Backup Log File!"},
      {"Error Creating Log File!"},
      {"Error Creating Temp File!"},
      {"Error Opening Log File!"},
      {"Error Opening Message File!"},
      {"Error Opening Protected File!"},
      {"Error Opening Sentry.ins!"},
      {"Error Opening System Files!"},
      {"Error Opening Temp File!"},
      {"Error Reading Data Segment [Open]"},
      {"Please Run the INSTALL.EXE program."},
      {"Error Scanning Temp File!"},
      {"Error in Account Information!"},
      {"Error in Initialization Settings!"},
      {"Internal Screen Error [Reading]"},
      {"Internal Screen Error [Writing]"},
      {"Out of memory!"},
      {"Registration Error - Program Aborted!"},
      {"This account has expired."},
      {"Cannot Find LICENSE.TXT!"},
};

/*
  GLOBAL VARIABLES
*/

short int sum;   /* SuperUser Menu? Nope, not yet. */

/*
  FUNCTIONS
*/

int tsk(void)
/*
  tsk(void) is the function called when the user attempts to exit via
  CTRL-C or CTRL-BREAK. The attempt is logged, and the computer is locked
  up to prevent any further attempts.
*/
{
struct ffblk ffblk;
int x;
char tmp[MAX];
#ifndef INSTALL
  tolog("User Attempted to Exit.");
#endif
  flushall();
  fcloseall();
  strcpy(tmp,"");
  strcpy(ssm,"");
#ifndef INSTALL
  if (strlen(te))
  {
    strcpy(temp,te);
    strcat(temp,"\\");
    strcpy(tmp,temp);
  }
  strcat(tmp,"tmp*.$$$");
  x=findfirst(tmp,&ffblk,0); /* Delete all old temp files that */
  while (!x)                 /* May be hanging around */
  {
    sunlink(ffblk.ff_name);
    x=findnext(&ffblk);
  }
  strcpy(tmp,"");
  if (strlen(te))
    strcpy(tmp,temp);
  strcat(tmp,"tmp*.exe");
  x=findfirst(tmp,&ffblk,0);  /* Delete all old protected files */
  while (!x)                 /* that may be hanging around */
  {
    sunlink(ffblk.ff_name);
    x=findnext(&ffblk);
  }
  lockup();
  return(1);  /* Abort and lock up */
#else
  strcpy(temp,id);
  strcat(temp,ip);
  strcat(temp,"\\tmp*.$$$");
  x=findfirst(temp,&ffblk,0); /* Delete all old temp files that */
  while (!x)                 /* May be hanging around in */
  {                          /* the install path */
    sunlink(ffblk.ff_name);
    x=findnext(&ffblk);
  }
  strcpy(temp,sd);
  strcat(temp,sp);
  strcat(temp,"\\tmp*.$$$");
  x=findfirst(temp,&ffblk,0);  /* Delete all old temp files */
  while (!x)                 /* that may be hanging around */
  {                            /* in the start path */
    sunlink(ffblk.ff_name);
    x=findnext(&ffblk);
  }
  return(0); /* Abort and drop to DOS */
#endif
}

void error(int s)
/*
  error(char *s) handles all fatal errors within Sentry. It prints a
  copy of the message to screen and to the log file and proceeds to lock
  the user out of the computer.
  The parameter s contains the error message.
*/
{
  crwin(15,8,strlen(errmsg[s])+22,12,YELLOW,LIGHTRED,2,"SYSTEM ERROR");
  cprintf("\r\n   ");
  cprintf("%s",errmsg[s]);
  cprintf("\r\n");
#ifndef INSTALL
  fclose(logf);
  if ((logf=fopen(ilog,"a"))!=NULL)
    tolog((char*)errmsg[s]);
  lockup();
#else
  fin(1);
#endif
}

void warning(int s)
/*
  warning(char *s) handles all non-fatal errors within Sentry. It prints a
  copy of the message to screen and to the log file.
  It does not lock the user out of the computer.
  The parameter s contains the error message.
*/
{
char scr[80*25*2];
short int tx,ty,rrl,rrt,rrb,rrr,rrk,rrf;
  tx=wherex();
  ty=wherey();
  rrl=rclf;
  rrt=rctop;
  rrb=rcbot;
  rrr=rcri;
  rrf=rcfrg;
  rrk=rcbak;
  if (!gettext(1,1,80,25,scr))
    error(SCRD);
  crwin(15,8,strlen(errmsg[s])+22,12,YELLOW,LIGHTRED,2,"WARNING!");
  cprintf("\r\n   ");
  cprintf("%s",errmsg[s]);
  cprintf("\r\n");
#ifndef INSTALL
  fclose(logf);
  if ((logf=fopen(ilog,"a"))!=NULL)
    tolog((char*)errmsg[s]);
#endif
blch();
  if (!puttext(1,1,80,25,scr))
    error(SCWR);
  rclf=rrl;
  rctop=rrt;
  rcbot=rrb;
  rcri=rrr;
  rcfrg=rrf;
  rcbak=rrk;
  window(rrl,rrt,rrr,rrb);
  txb(rrk);
  txc(rrf);
  gotoxy(tx,ty);
}


void ssav(void)
/*
  ssav() is the actual screen saver. It blanks the screen, displays the
  text stored in ssm in random locations on the screen, and restores
  when a key is pressed.
*/
{
char scr[80*25*2];
#ifndef INSTALL
char am[MAX];
int ld;
#endif
long st,en;
short int tx,ty,tm,rrl,rrt,rrb,rrr,rrk,rrf;
  /*
    BLANK SCREEN
  */
  tx=wherex();
  ty=wherey();
  rrl=rclf;
  rrt=rctop;
  rrb=rcbot;
  rrr=rcri;
  rrf=rcfrg;
  rrk=rcbak;
  if (!gettext(1,1,80,25,scr))
    error(SCRD);
  tm=0;
  while (!tm)
  {
    window(1,1,80,25);
    tm=1;
    txb(BLACK);
    clrscr();
    getdate(&td);
    gettime(&nw);
    st=dostounix(&td,&nw)+5;
    while (!kbhit())
    {
      getdate(&td);
      gettime(&nw);
      en=dostounix(&td,&nw);
      if (en>st)
      {
        clrscr();
        gotoxy(random(79-strlen(ssm)),random(24));
        txc(random(15));
        cprintf("%s",ssm);
        getdate(&td);
        gettime(&nw);
        st=dostounix(&td,&nw)+15;
      }
    }
    getch();
#ifndef INSTALL
    if (sum)
    /* Prompt for password */
    {
      sum=2; /* No recursive calls please! */
      crwin(10,11,29+max,15,tf,tb,2,"");
      while (tm==1)
      {
        clrscr();
        strncpy(am,gin("\r\n Enter Password: ",0),max);
        if ((pec!='?') && (pec!='!'))
        {
          gotoxy(wherex()+17+strlen(am)+1,wherey()-1);
          for (ld=0;ld<=(max-strlen(am));ld++)
            cprintf("%c",pec);
          cprintf("\r\n");
        }
        if (strlen(am)==0)
          tm=0;
        strcpy(am,penc(am));
        if (streq(pwd,am))
          tm=-1;
      }
      sum=1; /* Back to normal */
    }
#endif
  }
  /*
    RESTORE SCREEN
  */
  if (!puttext(1,1,80,25,scr))
    error(SCWR);
  rclf=rrl;
  rctop=rrt;
  rcbot=rrb;
  rcri=rrr;
  rcfrg=rrf;
  rcbak=rrk;
  window(rrl,rrt,rrr,rrb);
  txb(rrk);
  txc(rrf);
  gotoxy(tx,ty);
}

char blch(void)
/*
  blch(void) is used at all input points instead of getch(). blch()
  allows the screen saver to activate at the designated times, in
  addition to filtering out selected extended keys.
*/
{
unsigned char bin;
long st,en;
  getdate(&td);
  gettime(&nw);
  st=dostounix(&td,&nw)+scrb;
  while (!kbhit())
  {
    getdate(&td);
    gettime(&nw);
    en=dostounix(&td,&nw);
    if (en>st)
    {
      if (sum<2)
        ssav();
      getdate(&td);
      gettime(&nw);
      st=dostounix(&td,&nw)+scrb;
    }
  }
  bin=getch();
  if (!bin)  /* Must be an extended key */
  {
    bin=getch();
    if (bin==59) /* F1 - Online Help */
    {
#ifndef INSTALL
      help();
#endif
      bin=0;
    }
    if ((bin==60) && (sum<2))  /* F2 - Screen Saver */
    {
      ssav();
      bin=0;
    }
    if (((bin<69) && (bin>60)) || (bin==71) || (bin==133) || (bin==134) || (bin==79) || (bin==82) || (bin==83))
      bin=0;  /* Block out unused extended keys */
  }
  return(bin);
}

void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor,char *tt)
/*
  crwin() is the function used to create a window. It's action is
  dependant on the value of the variable wm:
    wm==0 : no windows
    wm==1 : normal windows
    wm==2 : "exploding" windows

  lf is the left hand edge.
  top is the location of the top.
  ri is the right hand edge.
  bot is the location of the bottom.
  frg is the foreground colour.
  bak is the background colour.
  bor is the border status:
          0 - No border
          1 - Single Border
          2 - Double Border
  tt is the window title
*/
{
  short int z,cx,cy,mn;
  rcfrg=frg;
  rcbak=bak;
  if (wm)
  {
    if (lf<1)
      lf=1;
    if (top<1)
      top=1;
    if (ri>80)
      ri=80;
    if (bot>25)
      bot=25;
    txc(frg);
    txb(bak);
    if (bor)
    {
      if (wm==2)
      {
        cx=(lf+ri)/2;
        cy=(top+bot)/2;
        if ((ri-lf)>(bot-top))
          mn=(bot-top)/2;
          else
          mn=(ri-lf)/2;
        for(z=1;z<=mn;z++)
        {
          wdr(cx-z*(ri-lf)/(bot-top),cy-z,cx+z*(ri-lf)/(bot-top),cy+z,bak,bor,"");
          clrscr();
          delay(WIN_DELAY);
        }
      }
      wdr(lf,top,ri,bot,bak,bor,tt);
    }
    else
    {
      window(lf,top,ri,bot);
      rclf=lf;
      rctop=top;
      rcri=ri;
      rcbot=bot;
    }
  }
}

void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor,char *tt)
/*
  wdr() actually draws the window on the screen.
  For exploding windows, wdr() is called multiple times.
*/
{
  char scr[80*1*2];
  int x;
  if (!gettext(lf,bot+1,ri,bot+1,scr))
    error(SCRD);
  window(lf,top,ri,bot+1);
  clrscr();
  bor--;
  if (bor)
    cprintf("É");
    else
    cprintf("Ú");
  for(x=1;x<(ri-lf);x++)
    if (bor)
      cprintf("Í");
      else
      cprintf("Ä");
  if (bor)
    cprintf("»º");
    else
    cprintf("¿³");
  for(x=1;x<(bot-top-1);x++)
  {
    gotoxy(ri-lf+1,wherey());
    if (bor)
      cprintf("ºº");
      else
      cprintf("³³");
  }
  gotoxy(ri-lf+1,wherey());
  if (bor)
    cprintf("ºÈ");
    else
    cprintf("³À");
  for(x=1;x<(ri-lf);x++)
    if (bor)
      cprintf("Í");
      else
      cprintf("Ä");
  if (bor)
    cprintf("¼");
    else
    cprintf("Ù");
  if (strlen(tt))
  {
    gotoxy((ri-lf-strlen(tt))/2-1,1);
    cprintf(" %s ",tt);
  }
  window(lf,bot+1,ri,bot+1);
  txb(BLACK);
  clrscr();
  if (!puttext(lf,bot+1,ri,bot+1,scr))
    error(SCWR);
  txb(bak);
  lf++;
  top++;
  ri--;
  bot--;
  window(lf,top,ri,bot);
  rclf=lf;
  rctop=top;
  rcri=ri;
  rcbot=bot;
  clrscr();
}

void txb(short int tc)
/*
  txb() handles text background colour changes. If col=0, no colour
  changes are permitted (Text is either highlighted or not).
*/
{
  if (col)
    textbackground(tc);
    else
  {
    if (tc==hb)
    {
      textbackground(DFC);
      textcolor(BLACK);
    }
    else
    {
      textbackground(BLACK);
      textcolor(DFC);
    }
  }
}

#if !USER
void shar(int x)
/*
  shar() displays a shareware window if the shareware version is being
  compiled.
*/
{
  crwin(10,5,67,11,YELLOW,LIGHTRED,2,"");
  cprintf("\r\n                 UNREGISTERED VERSION");
  cprintf("\r\n  The ShareWare Version Does Not Encode Passwords!");
  cprintf("\r\n     Please Register if you intend to use %s.\r\n",SENTRY);
  if (x)
  {
    tolog("*********************************");
    tolog("* THIS IS AN UNREGISTERED COPY. *");
    tolog("*       PLEASE REGISTER.        *");
    tolog("*********************************");
  }
  sleep(3);
}
#endif

char* gin(char *s,short int ech)
/*
  gin() is the general input routine. It gets input from the keyboard
  and returns it the entered string. If ech is set to 1, the input is
  echoed to the screen. If ech = 0, the output is echoed as per the
  initialization settings. If the user is logging in as a SuperUser, sul
  is set to 1.
  gin() takes a character pointer (the string to be displayed before
  input) and an integer (echo) for parameters.
*/
{
short int x;
char gi[MAX],ar[MAX];
  bk=0;
  cprintf("%s ",s);
  for(x=0;x<MAX;x++)
  {
    gi[x]=0;
    ar[x]=0;
  }
  x=0;
  while (x<(MAX-1))
  {
    ar[x]=blch();
    if ((ar[x]==ESC) && _bk)
    {
      bk=1;
      break;
    }
    if ((ar[x]==13) || (ar[x]==10))
    {
      gi[x]=0;
      if ((ar[x]==10) && ech)
        sul=1;
      break;
    }
    else
    {
      if (!((ar[x]<32) || (ar[x]>125)))
      {
#ifndef INSTALL
        if (ech || (pec=='!'))
#endif
          cprintf("%c",ar[x]);
#ifndef INSTALL
        else
          if (pec!='?')
            cprintf("%c",pec);
#endif
        gi[x]=ar[x];
      }
      else
        x--;
    }
    if ((ar[x+1]==DEL) && (x>=0))
    {
      ar[x+1]=0;
      x--;
      cprintf("%c %c",DEL,DEL);
    }
    x++;
  }
  cprintf("\r\n");
  return(gi);
}

void sunl(const char *sul)
/*
  sunl() is the routine that performs a secure unlink of all files
  deleted by Sentry. To delete a file securely, sunl() finds the length
  of the file, overwrites the entire file with random characters, and
  then deletes it. Recovering the file will only salvage the random
  characters.
  sunl() is only called if sdel!=0.
*/
{
char scr[80*25*2];
short int tx,ty,rrl,rrt,rrb,rrr,rrk,rrf,spp=0;
FILE *fd;
long c,cc;
  if (strlen(ssm))
  {
    tx=wherex();
    ty=wherey();
    rrl=rclf;
    rrt=rctop;
    rrb=rcbot;
    rrr=rcri;
    rrf=rcfrg;
    rrk=rcbak;
    if (!gettext(1,1,80,25,scr))
      error(SCRD);
    crwin(61,1,80,3,tf,tb,2,"");
    cprintf(BUSY);
  }
  if ((fd=fopen(sul,"rb"))!=NULL)
  {
    if (fseek(fd,0L,SEEK_END))
      error(SCTMP);
    c=ftell(fd);
    fclose(fd);
    if ((fd=fopen(sul,"wb"))==NULL)
      error(CRTMP);
    for(cc=0;cc<=c;cc++)
    {
      fputc(random(256),fd);
      if (((cc%BUFSZ)==0) && (strlen(ssm)))
      {
        cprintf("%c%c",DEL,SPIN[spp]);
        spp++;
        spp%=4;
      }
    }
  }
  fclose(fd);
  unlink(sul);
  if (strlen(ssm))
  {
    if (!puttext(1,1,80,25,scr))
      error(SCWR);
    rclf=rrl;
    rctop=rrt;
    rcbot=rrb;
    rcri=rrr;
    rcfrg=rrf;
    rcbak=rrk;
    window(rrl,rrt,rrr,rrb);
    txb(rrk);
    txc(rrf);
    gotoxy(tx,ty);
  }
}

int Win95(void)
/*
  Win95() determines if Windows 95 is being run or not. It calls int 21h
  (function 06h) to check the DOS version. If it is 7.0, Windows 95 is
  currently active.
  Win95() returns nonzero if Windows 95 is active, otherwise zero.
*/
{
union REGS regs;
  regs.h.ah=0x33;
  regs.h.al=0x06;
  intdos(&regs,&regs);
  return(((regs.h.bl==7) && (regs.h.bh==0))?1:0);
}

int cpath(int dir,char *path)
/*
  cpath() checks the path given by the variable path to ensure it is
  valid. It also makes all paths absolute.
    dir==1 if path is a directory
    dir==0 if path is a file
  cpath() returns zero if the path is invalid, nonzero if it is a valid path
*/
{
int x,y,z=2;
//char dr[MAXDRIVE],di[MAXDIR],fi[MAXFILE],ex[MAXEXT],ptmp2[_MAX_PATH];
char ptmp[_MAX_PATH];
  if (!strlen(path))
    z=0;
//cprintf("Starting: [%s]\r\n",path);
  if (_fullpath(ptmp,path,_MAX_PATH) == NULL)
    z=0;
  else
    strcpy(path,ptmp);
//cprintf("_fullpath: [%s]\r\n",path);
/*  while (z>1)
  {
    z=1;
    x=fnsplit(path,dr,di,fi,ex);
    if (dir)
    {
      strcat(di,fi);
      strcat(di,ex);
      strcpy(fi,"");
      strcpy(ex,"");
    }
    if (!strlen(dr))
    {
      dr[2]=0;
      dr[0]=getdisk()+'a';
      dr[1]=':';
    }
    strlwr(dr);
    // Drive is now available VERIFIED
//cprintf("Drive: [%s]\r\n",dr);
	  strcpy(path,dr);
    strcat(path,di);
    strcat(path,fi);
    strcat(path,ex);
*/
//cprintf("Path (Pass1): [%s]\r\n",path);
      strcpy(ptmp,path);
      x=_rtl_chmod(path,0,0);
      if (x==-1)
      {
        switch(errno)
        {
          case ENOENT:
            if (dir)
            {
              if (ptmp[strlen(ptmp)-1]!='\\')
                strcat(ptmp,"\\");
              strcat(ptmp,"nul");
            }
            if ((ini=fopen(ptmp,"r"))==NULL)
            {
              if (dir)
              {
                cprintf("\r\nDirectory does not exist. Do you wish to create it? ");
                y=blch();
                if ((y=='y') || (y=='Y'))
                {
                  cprintf("Yes");
                  z=!mkdir(path);
                  if (!z)
                    cprintf("\r\nInvalid directory.\r\n");
                  else
                    cprintf("\r\nDirectory created.");
                }
                else
                {
                  cprintf("No");
                  cprintf("\r\n\r\nDirectory not created.\r\n");
                  z=0;
                }
              }
              else
              {
                if (z)
                {
                  fclose(ini);
                  if ((ini=fopen(ptmp,"a"))==NULL)
                  {
                    cprintf("Invalid file name.\r\n");
                    z=0;
                  }
                  else
                  {
                    fseek(ini,0L,SEEK_END);
                    if (!ftell(ini))
                      sunlink(ptmp);
                  }
                  fclose(ini);
                }
              }
            }
            else
              cprintf("\r\nInvalid Path.\r\n");
            fclose(ini);
            break;
          case EACCES:
            cprintf("\r\nPermission Denied.\r\n");
            z=0;
            break;
          default:
            cprintf("\r\nDOS Error Number: %d\r\n",errno);
            z=0;
            break;
        }
      }
      else
      {
        if ((x & FA_DIREC) && !dir)
        {
          cprintf("\r\n%s is a directory. You must enter a file.\r\n",path);
          z=0;
        }
        if (x & FA_RDONLY)
        {
          cprintf("\r\nNOTE: %s is read-only.\r\n",path);
          _rtl_chmod(path,1,-FA_RDONLY);
        }
        if (x & FA_HIDDEN)
        {
          cprintf("\r\nNote: %s is hidden.",path);
          _rtl_chmod(path,1,-FA_HIDDEN);
        }
        if (x & FA_SYSTEM)
        {
          cprintf("\r\n%s is a system file.\r\n",path);
          z=0;
        }
    }
/*
    if (!strlen(di))
      strcpy(di,".");
    x=getdisk();
    strcpy(path,"\\");
    getcurdir(0,ptmp);
    strcat(path,ptmp);
    setdisk(dr[0]-'a');
    strcpy(ptmp2,"\\");
    getcurdir(0,ptmp);
    strcat(ptmp2,ptmp);
    if (!chdir(di))
    {
      getcurdir(0,di);
      chdir(ptmp2);
    }
    else
    {
      strcpy(ptmp,path);
      strcat(ptmp,"\\");
      strcpy(di,ptmp);
      if (!mkdir(di))
      {
        z=2; // Invalid path, may not exist - recalculate
//cprintf("Recalculating: [%s]\r\n",di);
        rmdir(di);
      }
    }
    setdisk(x);
    chdir(path);
    strcpy(path,dr);
    if (z<2)
      strcat(path,"\\");
    strcat(path,di);
    if (!dir)
    {
      if (strlen(di))
        strcat(path,"\\");
      strcat(path,fi);
      strcat(path,ex);
    }
  }
*/
    strlwr(path);
    // Path is now available
//cprintf("Path (Pass2): [%s]\r\n",path);
  return(z);
}
@


4.7
log
@*** empty log message ***
@
text
@d2 46
d139 45
d185 5
d285 2
a286 1
  allows the screen saver to activate at the designated times.
d289 1
a289 1
char bin;
d332 5
a336 2
  crwin() is the function used to create a window. If the variable wm==0,
  no windows are created.
d399 1
d536 1
a536 1
    if ((ar[x]==27) && _bk)
a560 7
/*
Enable code to return only up to max characters.
        if (x<max)
          gi[x]=ar[x];
        else
          gi[x]=0;
*/
d578 9
a586 1
void sunlink(const char *sul)
d605 1
a605 1
    cprintf(" Please Wait....");
d646 6
d658 187
@


3.8
log
@*** empty log message ***
@
text
@d5 88
d96 4
d101 1
a101 1
int tx,ty;
d107 6
a112 1
  window(1,1,80,25);
d114 3
a116 7
    error("Internal Screen Error. [Reading]");
  txb(BLACK);
  clrscr();
  getdate(&td);
  gettime(&nw);
  st=dostounix(&td,&nw)+5;
  while (!kbhit())
d118 4
d124 2
a125 2
    en=dostounix(&td,&nw);
    if (en>st)
a126 4
      clrscr();
      gotoxy(random(79-strlen(ssm)),random(24));
      txc(random(15));
      cprintf("%s",ssm);
d129 37
a165 1
      st=dostounix(&td,&nw)+15;
d167 1
a168 1
  getch();
d173 10
a182 4
    error("Internal Screen Error. [Writing]");
  window(rclf,rctop,rcri,rcbot);
  txb(rcbak);
  txc(rcfrg);
a193 1
int tx,ty;
d204 2
a205 1
      ssav();
d212 1
a212 1
  if (!bin)
d215 8
a222 1
    if (bin==60)
d227 2
d304 1
a304 1
    error("Internal Screen Error. [Reading]");
d352 1
a352 1
    error("Internal Screen Error. [Writing]");
d396 4
a399 3
  crwin(10,5,67,10,YELLOW,LIGHTRED,2,"");
  cprintf("\n\r                UNREGISTERED VERSION!!\n\r");
  cprintf("     Please Register if you intend to use %s.\n\r",SENTRY);
d410 141
@
