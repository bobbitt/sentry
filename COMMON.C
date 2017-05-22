/*                                                   
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

const char errmsg[ERR][48];  /* Listing of all error messages */
//{
//      {"Cannot Locate Environment."},
//      {"Environment Overflow - Not Modified."},
//      {"Error Creating Backup Log File!"},
//      {"Error Creating Log File!"},
//      {"Error Creating Temp File!"},
//      {"Error Opening Log File!"},
//      {"Error Opening Message File!"},
//      {"Error Opening Protected File!"},
//      {"Error Opening Sentry.ins!"},
//      {"Error Opening System Files!"},
//      {"Error Opening Temp File!"},
//      {"Error Reading Data Segment [Open]"},
//      {"Please Run the INSTALL.EXE program."},
//      {"Error Scanning Temp File!"},
//      {"Error in Account Information!"},
//      {"Error in Initialization Settings!"},
//      {"Internal Screen Error [Reading]"},
//      {"Internal Screen Error [Writing]"},
//      {"Out of memory!"},
//      {"Registration Error - Program Aborted!"},
//      {"This account has expired."},
//      {"Cannot Find LICENSE.TXT!"},
//      {"The Initialization Settings Are Old!"},
//      {"The Initialization Settings Are New!"},
//      {"Executable Integrity Error!"},
//      {"Error Opening String File!"},
//};

/*
  GLOBAL VARIABLES
*/

short int sum;   /* SuperUser Menu? Nope, not yet. */
short int ext; // Extended character on input

char yes;  // Character used to respond to "yes" prompts
char no;  // Character used to respond to "no" prompts

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
  tolog(glstr(496));
//  tolog("User Attempted to Exit.");
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
  crwin(13,5,strlen(errmsg[s])+24,9,YELLOW,LIGHTRED,2,glstr(497));
//  crwin(13,5,strlen(errmsg[s])+24,9,YELLOW,LIGHTRED,2,"System Error");
  cprintf("\r\n   ");
  cprintf("%d",s);
  cprintf(": ");
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
  }
  crwin(13,5,strlen(errmsg[s])+24,9,YELLOW,LIGHTRED,2,glstr(498));
//  crwin(13,5,strlen(errmsg[s])+24,9,YELLOW,LIGHTRED,2,"WARNING!");
  cprintf("\r\n   ");
  cprintf("%d",s);
  cprintf(": ");
  cprintf("%s",errmsg[s]);
  cprintf("\r\n");
#ifndef INSTALL
  fclose(logf);
  if ((logf=fopen(ilog,"a"))!=NULL)
    tolog((char*)errmsg[s]);
#endif
  blch();
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
        cprintf("\r\n ");
        pstr(499);
        strncpy(am,gin(" ",0),max);
//        strncpy(am,gin("\r\n Enter Password: ",0),max);
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


void set_lang(short int ask)
/*
  set_lang() is activated when the user presses F3 at any prompt.
  It allows the user to switch to any of the available languages.
*/
{
char scr[80*25*2];
char lang_file[MAX];
short int tx,ty,rrl,rrt,rrb,rrr,rrk,rrf,tlang,fc;
  if (!sl)
  {
    sl=1;
    tlang=lang;

    // Set path to lang file
    strcpy(lang_file,ins);
    strcat(lang_file,"lang");

    if (ask)
    {
      /*
        SAVE SCREEN
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

      // Put up Window
      crwin(10,8,60,17,tf,tb,2,glstr(520));
      cprintf("\r\n\r\n  1. English\r\n  2. Espanol\r\n\r\n");
      pstr(520);
      cprintf(": ");
      lang=blch()-'1';

      fclose(LANG);

      if ((lang) && (lang!=1)) // Is it a valid language code?
        lang=tlang;           // If not, undo selection

      if ((LANG=fopen(lang_file,"w"))==NULL)  // Write Selection to file
        error(CRTMP);
      fprintf(LANG,"%d\n",lang);
      fclose(LANG);
    }
    else
    {
      fclose(LANG);

      if ((LANG=fopen(lang_file,"r"))==NULL)  // Open Language File
      {
        if ((LANG=fopen(lang_file,"w"))==NULL)  // If Not Present, Create
          error(CRTMP);
        fprintf(LANG,"0\n");
        fclose(LANG);
        if ((LANG=fopen(lang_file,"r"))==NULL) // Now Re-Open it
          error(OPTMP);
      }

      if ((fgets(lang_name,5,LANG))==NULL) // Read Language Code
        error(OPTMP);

      fclose(LANG);

      chop(lang_name);
      lang=atoi(lang_name); // Set lang variable
    }

    strcpy(lang_name,ins);
    strcat(lang_name,"string"); // Set default filename

    if (lang==1)  // Spanish
      strcat(lang_name,"es");

    fclose(LANG);

    if ((LANG=fopen(lang_name,"r"))==NULL)
      error(OPSTR);

#ifndef INSTALL
    for(fc=0;fc<ERR;fc++) // Load all error codes in
    {
      strcpy(errmsg[fc],glstr(fc+470));
    }
#endif

    // Load [Y]es and [N]o characters
    yes=glstr(211)[0];
    no=glstr(213)[0];

    strcpy(BUSY,glstr(374)); // Load Please Wait banner...

//    cprintf("\r\n Code for yes is: [%c] or [%c]",yes,yes+32);
//    cprintf("\r\n Code for no is:  [%c] or [%c]",no,no+32);
//    blch();

    if (ask)
    {
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
    sl=0;
  }
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
    if ((en>st) && (scrb))
    {
      if (sum<2)
        ssav();
      getdate(&td);
      gettime(&nw);
      st=dostounix(&td,&nw)+scrb;
    }
  }
  bin=getch();
//cprintf("[%c] (%d) ",bin,bin);
  if (!bin)  /* Must be an extended key */
  {
    ext=getch();
//cprintf("[%c] (%d) ",ext,ext);
    if (ext==59) /* F1 - Online Help */
    {
#ifndef INSTALL
      help();
#endif
    }
    if ((ext==60) && (sum<2))  /* F2 - Screen Saver */
      ssav();
    if (ext==61)    /* F3 - Language List */
    {
      set_lang(1);
    }
//    if (((ext<69) && (ext>60)) || (ext==71) || (ext==133) || (ext==134) || (ext==79) || (ext==82) || (ext==83))
//      bin=0;  /* Block out unused extended keys */
  }
  return(bin);
}

void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor,char *tt)
/*
  crwin() is the function used to create a window. It's action is
  dependant on the value of the variable wm:
    wm==0 : no windows (no longer supported)
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
  compiled. If a non-zero value is passed in, a message is
  also written to the log file.
*/
{
  crwin(10,5,67,11,YELLOW,LIGHTRED,2,"");
  cprintf("\r\n                 ");
  pstr(500);
  cprintf("\r\n  ");
  pstr(501);
  cprintf("\r\n     ");
  pstr(502);
  cprintf(" %s.\r\n",SENTRY);
//  cprintf("\r\n                 UNREGISTERED VERSION");
//  cprintf("\r\n The ShareWare Version Does Not Encrypt Passwords!");
//  cprintf("\r\n     Please Register if you intend to use %s.\r\n",SENTRY);
  if (x)
  {
    tolog("*********************************");
    tolog(glstr(503));
    tolog(glstr(504));
//    tolog("* THIS IS AN UNREGISTERED COPY. *");
//    tolog("*       PLEASE REGISTER.        *");
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
short int x,y;
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
      if (!((ar[x]<32) || (ar[x]>125))) // 126 is ~ for long file names, but we can't allow that, since it's the same as STAMP, which determines a superuser. (The user could add ~ to the end of their password and become a superuser)
      {
#ifndef INSTALL
        if (ech || (pec=='!'))
#endif
          cprintf("%c",ar[x]);
#ifndef INSTALL
        else
          if (pec!='?')
            for (y=0;y<pecc;y++)
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
      if (!ech && (pec!='!') && (pec!='?'))
        for (y=0;y<pecc;y++)
          cprintf("%c %c",DEL,DEL);
      else
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
    crwin(60,1,80,3,tf,tb,2,"");
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
      fputc((sdel-1)?random(256):0,fd);
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
//printf("regs.h.bl: %d - regs.h.bh: %d\n",regs.h.bl,regs.h.bh);
//exit(0);
//  return(((regs.h.bl==7) && (regs.h.bh==0))?1:0);
  // Anything in version 7 or higher is Win95
  return((regs.h.bl>=7)?1:0);
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
  if (_fullpath(ptmp,path,_MAX_PATH)==NULL)
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
                cprintf("\r\n");
                pstr(505);
                cprintf(" ");
//                cprintf("\r\nDirectory does not exist. Do you wish to create it? ");
                y=blch();
                yeah(y)
                {
                  pstr(211);
//                  cprintf("Yes");
                  z=!mkdir(path);
                  cprintf("\r\n");
                  if (!z)
                  {
                    pstr(507);
                    cprintf("\r\n");
//                    cprintf("\r\nInvalid directory.\r\n");
                  }
                  else
                  {
                    pstr(508);
//                    cprintf("\r\nDirectory created.");
                  }
                }
                else
                {
                  pstr(213);
//                  cprintf("No");
                  cprintf("\r\n\r\n");
                  pstr(510);
                  cprintf("\r\n");
//                  cprintf("\r\n\r\nDirectory not created.\r\n");
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
                    pstr(511);
                    cprintf("\r\n");
//                    cprintf("Invalid file name.\r\n");
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
            {
              cprintf("\r\n");
              pstr(512);
              cprintf("\r\n");
//              cprintf("\r\nInvalid Path.\r\n");
            }
            fclose(ini);
            break;
          case EACCES:
            cprintf("\r\n");
            pstr(513);
            cprintf("\r\n");
//            cprintf("\r\nPermission Denied.\r\n");
            z=0;
            break;
          default:
            cprintf("\r\n");
            pstr(514);
            cprintf(" %d\r\n",errno);
//            cprintf("\r\nDOS Error Number: %d\r\n",errno);
            z=0;
            break;
        }
      }
      else
      {
        if ((x & FA_DIREC) && !dir)
        {
          cprintf("\r\n%s ",path);
          pstr(515);
          cprintf("\r\n");
//          cprintf("\r\n%s is a directory. You must enter a file.\r\n",path);
          z=0;
        }
        if (x & FA_RDONLY)
        {
          cprintf("\r\n");
          pstr(509);
          cprintf(" %s ",path);
          pstr(516);
          cprintf("\r\n");
//          cprintf("\r\nNOTE: %s is read-only.\r\n",path);
          _rtl_chmod(path,1,-FA_RDONLY);
        }
        if (x & FA_HIDDEN)
        {
          cprintf("\r\n");
          pstr(509);
          cprintf(" %s ",path);
          pstr(517);
          cprintf("\r\n");
//          cprintf("\r\nNote: %s is hidden.",path);
          _rtl_chmod(path,1,-FA_HIDDEN);
        }
        if (x & FA_SYSTEM)
        {
          cprintf("\r\n");
          pstr(509);
          cprintf(" %s ",path);
          pstr(518);
          cprintf("\r\n");
//          cprintf("\r\n%s is a system file.\r\n",path);
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

void pstr(int line)
/*
  pstr() is called from all over.
  It prints the string contained on line "line" of file LANG.
  LANG contains the strings for a given language.
*/
{
#define PSTR_MAX	350 // also used below, maxlen of loaded string
char hold[PSTR_MAX];
short int hc; // Counter
short int width; // Width of string to print
short int split; // Location for word wrap
short int vsl; // Virtual String Length (length not wrapped)
short int tab; // # of chars to look back for a space
short int ttab; // Temporary track of tab
short int wx; // store and keep wherex()

  // **** Optimize: Don't rewind unless req'd data is behind you.
  rewind(LANG);

  // Read through file
  for (hc=0;hc<line;hc++)
  {
    fgets(hold,PSTR_MAX,LANG); // PSTR_MAX from above
  }
  chop(hold);

  wx=wherex()-1; // Current locataion
  vsl=strlen(hold)+wx;
  width=rcri-rclf; // Current Window width
  if (!width)
  {
    width=vsl;
  }
//  tab=width*.9; // Look back 10% of window width
  tab=10; // Look back 10 spaces

//printf("[strlen: %d - wherex: %d - vsl: %d - width: %d]\n",strlen(hold),wherex(),vsl,width);blch();

  while (vsl>width) // Word wrap required
  {
    split=0;
    hc=width*(vsl/width)-wx;

//printf("[hc: %d]",hc);blch();

    for(ttab=hc-tab;hc>ttab;hc--)
    // Scan for space nearest to end of string.
    {
      if ((!split) &&(hold[hc]==' '))
      {
        split=hc;
      }
    }

//printf("[split: %d]",split);blch();

    if (split)
    {
      hold[split]='\n';  // Convert Space to \n
      for(hc=strlen(hold)+1;hc>split;hc--) // Insert \r
      {
        hold[hc]=hold[hc-1];
      }
      hold[split+1]='\r';
    }
    vsl-=width;
  }

  cprintf("%s",hold);
}

char* glstr(int line)
/*
  glstr() is called from all over.
  It returns the string contained on line "line" of file LANG.
  LANG contains the strings for a given language.
*/
{
char hold[350]; // 350 also used below, maxlen of loaded string
short int hc; // Counter

  rewind(LANG);

  // Read through file
  for (hc=0;hc<line;hc++)
  {
    fgets(hold,350,LANG); // 350 from above
  }
  chop(hold);
  return(hold);
}

char* browse(short int ftype,int msg)
// Browse will display a menu of all files matching type ftype:

// 0=All Files
// 1=Executables (EXE, BAT or COM)
// 2=Settings file (settings)

// msg=input value for pstr() in window title
{
struct ffblk ffblk;
char cv[100],opt,sel,tdr[MAXPATH];
int x,y,z,msmax;
short int td; // Temp Drive

  bk=0; // No break (yet)
  td=getdisk();
  strcpy(tdr,"\\");  // Add \ to pathname
  getcurdir(0,tdr+1); // Load current dir into tdr+1

  browse: // Label to re-process menu when current dir is changed
  x=-1;
  sel=1;
  y=findfirst("*.*",&ffblk,FA_DIREC); // Get directories
  while (!y)
  {
    if (!(ffblk.ff_attrib ^ FA_DIREC))
    {
      if (x<MAXUSER)
      {
        x++;
        strcpy(txt[x],ffblk.ff_name);
        strcat(txt[x],"\\");
      }
    }
    y=findnext(&ffblk);
  }
  if (!ftype)
  {
    y=findfirst("*.*",&ffblk,0);
  }
  if (ftype==1)
  {
    y=findfirst("*.exe",&ffblk,0);
    while (!y)
    {
      if (x<MAXUSER)
      {
        x++;
        strcpy(txt[x],ffblk.ff_name);
      }
      y=findnext(&ffblk);
    }
    y=findfirst("*.com",&ffblk,0);
    while (!y)
    {
      if (x<MAXUSER)
      {
        x++;
        strcpy(txt[x],ffblk.ff_name);
      }
      y=findnext(&ffblk);
    }
    y=findfirst("*.bat",&ffblk,0);
  }
  if (ftype==2)
  {
    y=findfirst("settings",&ffblk,0);
  }
  while (!y)
  {
    if (x<MAXUSER)
    {
      x++;
      strcpy(txt[x],ffblk.ff_name);
    }
    y=findnext(&ffblk);
  }
  msmax=x; // Set the maximum number of menu items
  x=1; // Enter Loop
  while (x && !bk)
  {
    x=0; // Don't re-enter loop
    _bk=1; // Allow breaks
    crwin(2,1,50,24,tf,tb,2,glstr(msg));
//    crwin(2,1,50,24,tf,tb,2,"Protect A File");
    if (!wm)
      clrscr();
    // Show menu of items
    y=opt=z=0;
    while (!y)
    {
      txb(tb);
      txc(tf);
      clrscr();
      getcurdir(0,cv);
      cprintf("\r\n");
      pstr(196);
      cprintf(" %c:\\%s\r\n",getdisk()+'A',cv);
//      cprintf("\r\nFiles in: %c:\\%s\r\n",getdisk()+'A',cv);
      if (!z)
        cprintf("\r\n");
      if (z>0)
      {
        gotoxy(14,2);
        pstr(157);
        cprintf(" ");
//        cprintf("MORE [Page Up ] ");
      }
      cprintf("\r\n");
      if (z)
        cprintf("\r\n");
      for(y=z;y<WIN3+z;y++)
      {
        if (y<=msmax)
        {
          txb(tb);
          txc(tf);
          if (sel==(y % WIN3))
          {
            txb(hb);
            txc(hf);
          }
          if (y)
            cprintf("%s\r\n",txt[y]);
        }
      }
      txb(tb);
      txc(tf);
      y=0;
      if (z+WIN3<=msmax)
      {
        gotoxy(12,WIN3+5);
        pstr(158);
        cprintf(" ");
//        cprintf("MORE [Page Down ] ");
      }
      gotoxy(1,WIN3+7);
      pstr(197);
//      cprintf("Select a file to protect, D to change drive,");
//      cprintf("\r\nor ESC to quit.");
      opt=blch();
      switch (opt)
      {
			case 'D':
			case 'd':
        clrscr();
        cprintf("\r\n\r\n");
        pstr(198);
        cprintf(" ");
//        cprintf("\r\n\r\nChange to which drive [a-z]? ");
        bk=blch()-'a';
        setdisk(bk);
        bk=0;
        goto browse;
        break;
      case 13:
        y=1;
        bk=0;
        break;
      case 0:
        switch(ext)
        {
        case 77:
        case 80:
          if ((sel<(WIN3-1)) && ((sel+z)<msmax))
            sel++;
            else
            if ((sel+z)<msmax)
            {
              z+=WIN3;
              sel=0;
            }
          break;
        case 72:
        case 75:
          if ((sel>1) || ((sel>0) && (z>0)))
            sel--;
          else
            if (z>0)
            {
              z-=WIN3;
              sel=WIN3-1;
            }
          break;
        case 73:
          if (z>0)
          {
            z-=WIN3;
            if (!sel)
              sel=1;
          }
          else
            sel=1;
          break;
        case 81:
          if ((z+WIN3)<=msmax)
            z+=WIN3;
            else
            sel=msmax-z;
          if (!((sel+z)<=msmax))
            sel=msmax-z;
          break;
        }
        break;
      case ESC:
        y=1;
        bk=1;
        break;
      }
      opt=0;
    }
    if (!bk) // Didn't Escape from menu, process data
    {
      strcpy(cv,txt[sel+z]); // Copy selected filename to cv
  	   if (cv[strlen(cv)-1]=='\\') // is a directory
      {
      	chop(cv);
        if (chdir(cv))
        {
          crwin(2,5,70,18,tf,tb,2,glstr(msg));
//          crwin(2,5,70,18,tf,tb,2,"Protect A File");
          cprintf("\r\n\r\n");
          pstr(199);
//          cprintf("Could not change directory.");
        }
        else
        {
          goto browse;
        }
      }
      if (!strlen(cv)) // No string
        bk=1;
    }
  }
  setdisk(td); // Restore Original Drive
  chdir(tdr); // Restore Original Path
  return(cv);
}

char* penc(char *te)
/*
  penc() encodes passwords. If the password is over 8 characters long,
  then it is encoded in blocks of 8 characters. penc() also handles the
  SuperUser stamp.
  penc() takes the unencoded password as input, and returns the encoded
  password.
*/
{
int x=0,y;
char pret[MAX],p8[MAX];
  pret[0]=0;
  while (x<=strlen(te))
  {
    for(y=x;y<x+PMAX;y++)
      p8[y-x]=te[y];
    p8[y-x]=0;
    x+=PMAX;
    strcat(pret,UNIXcrypt(p8,SALT));
  }
  return(pret);
}

