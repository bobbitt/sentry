head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.23.19;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.42.47;	author MIKE;	state Exp;
branches;
next	3.3;

3.3
date	95.12.18.18.16.14;	author MIKE;	state Exp;
branches;
next	3.2;

3.2
date	95.12.12.14.00.50;	author MIKE;	state Exp;
branches;
next	3.1;

3.1
date	95.11.30.18.41.38;	author MIKE;	state Exp;
branches;
next	3.0;

3.0
date	95.11.09.15.59.42;	author MIKE;	state Exp;
branches;
next	2.7;

2.7
date	95.10.26.18.05.02;	author MIKE;	state Exp;
branches;
next	2.6;

2.6
date	95.10.25.12.08.10;	author MIKE;	state Exp;
branches;
next	2.5;

2.5
date	95.10.10.16.56.30;	author MIKE;	state Exp;
branches;
next	;


desc
@Super.c contains primarily the SuperUser functions of Sentry.
@


5.0
log
@Version 5.0
@
text
@/*
  INCLUDES
*/
#include "sentry.h"

/*
  FUNCTIONS
*/

void suinit(void)
/*
  suinit() initializes the SuperUser menu options in the string txt[].
  This is done seperately from the super() function so that it can be
  performed as required. view() also uses the txt[] variable, so
  suinit() must be called after each call to view().
*/
{
  strcpy(txt[1],"1. User Maintenance Menu");
  strcpy(txt[2],"2. Log File Maintenance Menu");
  strcpy(txt[3],"3. System Maintenance Menu");
  strcpy(txt[4],"4. Sentry DOS Shell");
  strcpy(txt[SUOPT],"5. Exit");
  if (!puttext(1,1,80,25,msc))
    error(SCWR);
  crwin(10,8,48,17,tf,tb,2,"SuperUser Menu");
}

void super(void)
/*
  super() is the function called when a SuperUser logs in and wishes to
  invoke the SuperUser menu (CTRL-enter on login). super() allows the
  user to select an option in much the same way as view() except they can
  also select by option number. Control of the program is subsequently
  passed to the appropriate function.
*/
{
  short int x,y;
  char opt,sel=1;
  suinit();
  y=opt=0;
  while (1) /* This is iffy (but it works) */
  {
    hl=sel;
    clrscr();
    txb(tb);
    txc(tf);
    cprintf("\r\n");
    for(x=1;x<=SUOPT;x++)
    {
      if (sel==x)
      {
        txb(hb);
        txc(hf);
      }
      else
      {
        txb(tb);
        txc(tf);
      }
      cprintf("%s",txt[x]);
      cprintf("\r\n");
    }
    txb(tb);
    txc(tf);
    cprintf("\r\nOption: ");
    opt=blch();
    if (isdigit(opt))
    {
      if (((opt-'0')<=SUOPT) && ((opt-'0')!=0))
      {
        sel=opt-'0';
        opt=13;
      }
    }
    switch (opt)
    {
    case 'u':
    case 'U':
      sel=1;
      opt=13;
      break;
    case 'l':
    case 'L':
      sel=2;
      opt=13;
      break;
    case 's':
    case 'S':
      sel=3;
      opt=13;
      break;
    case 'd':
      sel=4;
      opt=13;
      break;
    case ESC:  /* Escape */
    case 'x':
      sel=SUOPT;
      opt=13;
      break;
    case 77:   /* Cursor Right/Down */
    case 80:
      if (sel<SUOPT)
        sel++;
      break;
    case 75:    /* Cursor Up/Left */
    case 72:
      if (sel>1)
        sel--;
      break;
    case 73:  /* Page Up */
      sel=1;
      break;
    case 81:   /* Page Down */
      sel=SUOPT;
      break;
    }
    hl=sel;
    if (opt==13)
    {
      switch (sel)
      {
      case 1:
        user();
        y=1;
        break;
      case 2:
        logm();
        y=1;
	      break;
      case 3:
        sys();
        y=1;
        break;
      case 4:
        sprintf(tol,"%s DOS Shell",SENTRY);
        crwin(4,6,50,10,tf,tb,2,tol);
	      dshell();
	      y=1;
        break;
      case SUOPT:
  	    su=sul=1;
	      if (!puttext(1,1,80,25,msc))
  	      error(SCWR);
	      fin(0);
	      break;
      }
    }
    if (y)
      suinit();
    y=opt=0;
  }
}
@


4.7
log
@*** empty log message ***
@
text
@d2 1
a2 1
  FUNCTIONS
d4 1
a5 1
void iset(void)
d7 1
a7 1130
  iset() is the function that allows the user to change the
  initialization settings.
*/
{
short int x,y,sel=1,tp=0;
char opt=0;
  for (x=0;x<INI;x++)
    strcpy(txt[x+1],is[x]);
  crwin(7,1,50,23,tf,tb,2,"Initialization Settings");
  x=INI;
  while (1)
  {
    txb(tb);
    txc(tf);
    clrscr();
    cprintf("\r\n");
    if (!tp)
      cprintf("\r\n");
    if (tp>0)
    {
      gotoxy(14,2);
      cprintf("MORE [Page Up ] ");
    }
    cprintf("\r\n");
    if (tp)
      cprintf("\r\n");
    for(y=tp;y<WIN0+tp;y++)
    {
      if (y<=x)
      {
        if (sel==(y % WIN0))
        {
          txb(hb);
          txc(hf);
        }
        else
        {
          txb(tb);
          txc(tf);
        }
        if (y)
          cprintf("%s\r\n",txt[y]);
      }
    }
    txb(tb);
    txc(tf);
    if (tp+WIN0<=x)
    {
      gotoxy(12,19);
      cprintf("MORE [Page Down ] ");
    }
    gotoxy(1,21);
    cprintf("Select a setting or ESC when finished: ");
    opt=blch();
    switch (opt)
    {
    case 13:
      iedit(sel+tp-1);
      crwin(7,1,50,23,tf,tb,2,"Initialization Settings");
      break;
    case 77:
    case 80:
      if ((sel<(WIN0-1)) && ((sel+tp)<x))
        sel++;
        else
        if ((sel+tp)<x)
        {
          tp+=WIN0;
          sel=0;
        }
      break;
    case 72:
    case 75:
      if ((sel>1) || ((sel>0) && (tp>0)))
        sel--;
        else
        if (tp>0)
        {
          tp-=WIN0;
          sel=WIN0-1;
        }
      break;
    case 73:
      if (tp>0)
      {
        tp-=WIN0;
        if (!sel)
          sel=1;
      }
      else
        sel=1;
      break;
    case 81:
      if ((tp+WIN0)<=x)
        tp+=WIN0;
        else
        sel=x-tp;
      if (!((sel+tp)<=x))
        sel=x-tp;
      break;
    case 27:
      x=-1;
      break;
    }
    if (x<0)
      break;
  }
}

void iedit(int set)
/*
  iedit() is called from iset(). It displays information about the
  selected initialization setting, and re-writes the new settings if
  they are changed.
*/
{
char cv[100];
short int tv,qu,x;
char cl[16][15]=
{
  {"Black"},
  {"Blue"},
  {"Green"},
  {"Cyan"},
  {"Red"},
  {"Magenta"},
  {"Brown"},
  {"Light Gray"},
  {"Dark Gray"},
  {"Light Blue"},
  {"Light Green"},
  {"Light Cyan"},
  {"Light Red"},
  {"Light Magenta"},
  {"Yellow"},
  {"White"}
};
  set+=2;
  ini=ffwd(1,NULL);
  if (zm)
  {
    fgets(cv,MAX,ini); /* Read version number */
    fgets(cv,MAX,ini); /* Read file extension */
    fgets(cv,MAX,ini); /* Read path to help and .ins files */
  }
  for (tv=0;tv<set;tv++) /* Read one more line, then start with ini settings */
    if (fgets(cv,MAX,ini)==NULL)
      error(INSET);
  fclose(ini);
  strcpy(temp,is[set-2]);
  crwin(3,3,73,21,tf,tb,2,temp);
  if (!wm)
    clrscr();
  cprintf("\r\n");
  qu=0;
  strcpy(tol,ins);
  strcat(tol,"\\sentry.ins");
  if ((ini=fopen(tol,"r"))==NULL)
    cprintf("\r\n\r\nNo Information Available.");
  else
  {
    for(x=0;x<(set-2);x++)
      while((fgets(lo,MAX,ini)!=NULL) && (lo[0]!=''))
      { /* Just keep readin' fella */
      }
     while((fgets(lo,MAX,ini)!=NULL) && (lo[0]!=''))
       cprintf("%s\r",lo); /* Read description */
  }
  fclose(ini);
  switch (set-1)
  {
  case 1:
  case 2:
  case 3:
    qu=1;
    break;
  case 14:
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
  case 22:
  case 23:
  case 24:
  case 25:
    qu=2;
    break;
  case 9:
    qu=3;
    break;
  case 10:
    qu=4;
    break;
  case 32:
  case 34:
    for(tv=0;tv<16;tv++)
    {
      txc(tf);
      cprintf("%d ",tv);
      txc(tv);
      cprintf("%s ",cl[tv]);
      for(x=0;x<(14-strlen(cl[tv])-tv/10);x++)
        cprintf(" ");
      if ((tv % 4)==3)
        cprintf("\r\n");
    }
    txc(tf);
    break;
  case 33:
  case 35:
    for(tv=0;tv<8;tv++)
    {
      txb(tb);
      cprintf("%d ",tv);
      txb(tv);
      cprintf("%s ",cl[tv]);
      for(x=0;x<(14-strlen(cl[tv])-tv/10);x++)
        cprintf(" ");
      if ((tv % 2)==1)
        cprintf("\r\n");
    }
    txb(tb);
    break;
  }
  cprintf("\r\n");
  strcpy(lo,"Default: ");
  /* Default Values */
  switch (set-1)
  {
  case 1:
    strcat(lo,"c:\\Sentry.Log");
    break;
  case 2:
    strcat(lo,"c:\\Backup.Log");
    break;
  case 3:
    strcat(lo,"c:\\Sentry.Msg");
    break;
  case 4:
    strcat(lo,"4");
    break;
  case 5:
    strcat(lo,"20");
    break;
  case 6:
    strcat(lo,"3");
    break;
  case 7:
    strcat(lo,"3");
    break;
  case 8:
    strcat(lo,"20");
    break;
  case 9:
    strcat(lo,"passwd");
    break;
  case 10:
    strcat(lo,"*");
    break;
  case 11:
    strcat(lo,"365");
    break;
  case 12:
    strcat(lo,"365");
    break;
  case 13:
    strcat(lo,"300");
    break;
  case 14:
    strcat(lo,"This is a Secure Terminal.");
    break;
  case 15:
    strcat(lo,"Login:");
    break;
  case 16:
    strcat(lo,"Password:");
    break;
  case 17:
    strcat(lo,"Invalid Login.");
    break;
  case 18:
    strcat(lo,"Invalid Login.");
    break;
  case 19:
    strcat(lo,"Invalid Login.");
    break;
  case 20:
    strcat(lo,"Invalid Login.");
    break;
  case 21:
    strcat(lo,"User entered the wrong password.");
    break;
  case 22:
    strcat(lo,"User entered the wrong login.");
    break;
  case 23:
    strcat(lo,"Invalid Password Length.");
    break;
  case 24:
    strcat(lo,"Invalid Login Length.");
    break;
  case 25:
    strcat(lo,"USER");
    break;
  case 26:
    strcat(lo,"1");
    break;
  case 27:
    strcat(lo,"1");
    break;
  case 28:
    strcat(lo,"1");
    break;
  case 29:
    strcat(lo,"0");
    break;
  case 30:
    strcat(lo,"2");
    break;
  case 31:
    strcat(lo,"1");
    break;
  case 32:
    strcat(lo,"15");
    break;
  case 33:
    strcat(lo,"1");
    break;
  case 34:
    strcat(lo,"1");
    break;
  case 35:
    strcat(lo,"7");
    break;
  case 36:
    strcat(lo,"10");
    break;
  case 37:
    strcat(lo,"1");
    break;
  case 38:
    strcat(lo,"0");
    break;
  }
  cprintf("%s",lo);
  cprintf("\r\n\r\nCurrent Value: %s\r\n",cv);
  _bk=1;
  tv=max;
  max=MAX;
  strcpy(cv,gin("New Value (ENTER Aborts):",1));
  max=tv;
  if (strlen(cv) && (!bk))
  {
    switch (qu)
    {
    case 0:  /*Number*/
      qu=0;
      for(tv=0;tv<strlen(cv);tv++)
        if (!isdigit(cv[tv]))
          qu++;
      if (qu)
      {
        cprintf("\r\nPlease enter a numeric value.\r\n\r\nPress any key to try again...\r\n");
        bk=blch();
      }
      qu=0;
      break;
    case 1:  /*Path*/
    case 2:  /*Multiple Word String*/
      break;
    case 3:  /*Single Word*/
      if (strchr(cv,' ')!=NULL)
      {
        cprintf("\r\nPlease enter a single word. (No spaces)\r\n\r\nPress any key to try again...\r\n");
        bk=blch();
      }
      break;
    case 4:
      if (strlen(cv)>1)
      {
        cprintf("\r\nPlease enter a single character only.\r\n\r\nPress any key to try again...\r\n");
        bk=blch();
      }
      break;
    }
  }
  if (strlen(cv) && (!bk))
  {
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(CRTMP);
    ini=ffwd(1,npas);
    if (zm)
    {       /* If it's a protected file, read and write the extra info */
      fgets(lo,MAX,ini);
      fputs(lo,npas);
      fgets(lo,MAX,ini);
      fputs(lo,npas);
      fgets(lo,MAX,ini);
      fputs(lo,npas);
    }
    for (tv=1;tv<(INI+2);tv++)
      if (fgets(lo,MAX,ini)==NULL)
        error(INSET);
      else
        if (tv==set)
          fprintf(npas,"%s\r\n",cv);
        else
          fprintf(npas,"%s",lo);
    sprintf(tol,"Setting Modified: %s --> %s",is[set-2],cv);
    tolog(tol);
    fcd(ini,npas);
    sunlink(inam);
    rename(temp,inam);
  }
  else
  {
    fclose(ini);
    sunlink(temp);
  }
}

void smsg(void)
{
short int x,y=0;
  x=view("Send A Message");
  if (x)
  {
    crwin(2,7,70,17,tf,tb,2,"Send Message(s)");
    if (!wm)
      clrscr();
    pass=ffwd(2,NULL);
    bk=0;
    while((fgets(lo,MAX,pass))!=NULL && (!streq(lo,DIV)) && (!bk))
    {
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y==x)
      {
        _bk=1;
        strcpy(pa,gin("\r\nMessage:\r\n>",1));
        if (bk)
          break;
        if ((msg=fopen(imsg,"a"))==NULL)
          error(OPMSG);
        chop2(lo);
        lo[strlen(lo)+1]=0;
        lo[strlen(lo)]='\n';
        fputs(lo,msg);
        sprintf(tol,"%s\n",usr);
        fputs(tol,msg);
        getdate(&td);
        gettime(&nw);
        sprintf(tol,"%lu\n",dostounix(&td,&nw));
        fputs(tol,msg);
        pa[strlen(pa)+1]=0;
        pa[strlen(pa)]='\n';
        fputs(pa,msg);
        chop(lo);
        strcpy(tol,usr);
        strcat(tol," sent a message to ");
        strcat(tol,lo);
        strcat(tol,".");
        tolog(tol);
      }
    }
    fclose(msg);
  }
}

int exffwd(int mk)
{
char ff[DIVLEN+2];
short int yz,zz;
  for(zz=0;zz<=DIVLEN;zz++)
    ff[zz]=0;
  mk++;
  while(mk)
  {
    yz=1;
    while(yz && !feof(npas))
    {
      for(zz=0;zz<DIVLEN-1;zz++)
        ff[zz]=ff[zz+1];
      ff[zz]=fgetc(npas);
      ff[zz+1]=0;
      yz=!streq(ff,DIV);
    }
    mk--;
  }
  return(yz);
}

void prf(void)
{
char cv[100],dr[MAXDRIVE],di[MAXDIR],fi[MAXFILE],ex[MAXEXT];
short int x,y;
  crwin(2,7,70,17,tf,tb,2,"Protect File(s)");
  if (!wm)
    clrscr();
  x=1;
  bk=0;
  cprintf("WARNING: Once a file is protected, it can NEVER be undone.");
  cprintf("\r\nMake sure you backup the file before protecting it,");
  cprintf("\r\nand test the protected file to ensure it works as planned.");
  while (x && !bk)
  {
    x=0;
    _bk=1;
    strcpy(cv,gin("\r\n\r\nEnter File to Protect:",1));
    if (!strlen(cv))
      bk=1;
    y=fnsplit(cv,dr,di,fi,ex);
    strupr(ex);
    if (!streq(ex,".EXE") && !streq(ex,".COM") && !streq(ex,".BAT"))
    {
      cprintf("\r\nFile must have EXE, COM or BAT extension.\r\n\r\n");
      x=1;
    }
    else
    {
      if ((npas=fopen(cv,"rb"))==NULL)
      {
        cprintf("\r\nPlease enter a valid path.\r\n\r\n");
        x=1;
      }
      else
      {
        if (!exffwd(1))
        {
          cprintf("\r\nThis file is already protected by Sentry.\r\n\r\n");
          x=1;

          fclose(npas);
          if ((npas=fopen(cv,"rb"))==NULL)
            error(OPPRF);
          exffwd(1);
          fgets(lo,MAX,npas);
          chop2(lo);
          chop(lo);
          fgets(temp,MAX,npas);
          fgets(temp,MAX,npas);
          ze=fgetc(npas);
          fclose(npas);
          if (strcmp(lo,ver)<0)
          {
            cprintf("\r\nThis file was protected by an older version of Sentry.");
            cprintf("\r\nDo you want to upgrade it? ");
            x=blch();
            if ((x=='y') || (x=='Y'))
            {
              tmpnam(temp);
              if (y & DIRECTORY)
              {
                strcpy(tol,temp);
                strcpy(temp,di);
                strcat(temp,tol);
              }
              if (y & DRIVE)
              {
                strcpy(tol,temp);
                strcpy(temp,dr);
                strcat(temp,tol);
              }
              if ((pass=fopen(temp,"wb"))==NULL)
                error(CRTMP);     /* Decrypt and dump original file */
              if ((npas=fopen(cv,"rb"))==NULL)
                error(OPPRF);
              exffwd(3);
              zze=-1;
              fcd(npas,pass);
              zze=0;
              sunlink(cv);
              rename(temp,cv);
              strcpy(tol,cv);
              strcat(tol," upgraded to version ");
              strcat(tol,ver);
              strcat(tol,".");
              tolog(tol);
              x=0;
            }
            else
              x=1;
          }
        }
      }
    fclose(npas);
    }
  }
  if (!bk)
  {
    tmpnam(temp);
    if (y & DIRECTORY)
    {
      strcpy(tol,temp);
      strcpy(temp,di);
      strcat(temp,tol);
    }
    if (y & DRIVE)
    {
      strcpy(tol,temp);
      strcpy(temp,dr);
      strcat(temp,tol);
    }
    if ((npas=fopen(temp,"wb"))==NULL)
      error(CRTMP);
    pass=ffwd(1,npas);
    if ((fgets(lo,MAX,pass))==NULL)
      error(INSET);
    chop2(lo);
    lo[strlen(lo)+1]=0;
    lo[strlen(lo)]='Z';
    fprintf(npas,"%s\r\n",lo);
    fprintf(npas,"%s\r\n",ex);
    y=fnsplit(inam,dr,di,fi,ex);
    fprintf(npas,"%s%s\r\n",dr,di);
    y=fnsplit(cv,dr,di,fi,ex);
    strupr(ex);
    ze=1+random(255);
    fprintf(npas,"%c\r\n",ze);
    fcd(pass,npas);
    if ((pass=fopen(cv,"rb"))==NULL)
      error(OPPRF);
    if ((npas=fopen(temp,"ab"))==NULL)
      error(OPTMP);
    zze=1;  /* Protected file encryption on */
    fcd(pass,npas);
    zze=0;  /* Protected file encryption off */
    x=1;  /* No error by default */
    if (streq(ex,".BAT"))
    {
      strcpy(lo,cv);
      cv[strlen(cv)-1]='E';
      cv[strlen(cv)-2]='X';
      cv[strlen(cv)-3]='E';
      if ((pass=fopen(cv,"r"))!=NULL)
      {
        cprintf("\r\nCreating ");
        cprintf("%s",strlwr(cv));
        cprintf(" would overwrite an existing file!\r\n");
        cprintf("\r\nIf you still wish to protect this file, you will need to");
        cprintf("\r\nrename that file so that it will not duplicate the name of");
        cprintf("\r\nany existing \".exe\" programs in that directory when");
        cprintf("\r\nprotected.\r\n");
        cprintf("\r\nPress any key to return to the SuperUser menu...");
        blch();
        x=0;  /* Set error condition */
        sunlink(temp);
      }
      else
        sunlink(lo);
    }
    if (x)  /* Don't process if there was an error */
    {
      sunlink(cv);
      strcpy(tol,"File Protected: ");
      strcat(tol,cv);
      tolog(tol);
      rename(temp,cv);
    }
  }
}

void idmp(void)
{
  crwin(2,7,70,17,tf,tb,2,"Export Initialization Settings");
  if (!wm)
    clrscr();
  if (zm)
    cprintf("\r\nCannot dump the Initialization Settings\r\nof a Protected File!");
  else
  {
    if ((npas=fopen("settings.","wb"))==NULL)
      error(CRTMP);
    pass=ffwd(1,NULL);
    fcd(pass,npas);
    _chmod("settings.",1,FA_HIDDEN);
    cprintf("\r\nInitialization Settings Exported...\r\n");
    cprintf("\r\nThe next time INSTALL.EXE is run, it will\r\n");
    cprintf("pick up and use these settings.");
  }
  cprintf("\r\n\r\nPress any key to return to the SuperUser menu...");
  blch();
}

void secaud(void)
{
short int x,y;
  crwin(3,3,76,21,tf,tb,2,"Security Audit");
  if (!wm)
    clrscr();
  cprintf("\r\nSentry will now perform an audit of your system's security.");
  cprintf("\r\nYou will be informed of any potential weaknesses, and given");
  cprintf("\r\nan opportunity to update your settings.");
  y=0;
  cprintf("\r\n\r\nChecking System Settings...");
/* [System] Check for the following:
 - no "switches" line in config.sys
 - no "BootKeys" line in msdos.sys
 - no call to Sentry from the autoexec.bat file
 - a "break on" command in the config.sys file
*/
  /* Check for call to Sentry in AUTOEXEC.BAT */
  if ((pass=fopen(AUTO,"r"))==NULL)
  {
    y=1;
    cprintf("\r\n - Your AUTOEXEC.BAT file does not appear to exist.");
    /* The user will be asked if they want to add a call to Sentry */
    x=0;
  }
  else
  {
    x=0;
    while((fgets(lo,MAX,pass))!=NULL)
    {
      /* Check to see if call to Sentry exists */
      if ((lo[strlen(lo)-8]=='\\' && lo[strlen(lo)-7]=='s' && lo[strlen(lo)-6]=='e' && lo[strlen(lo)-5]=='n' && lo[strlen(lo)-4]=='t' && lo[strlen(lo)-3]=='r' && lo[strlen(lo)-2]=='y'))
         x=1; /* Ok, call exists */
    }
    fclose(pass);
  }
  if (!x)
  {
    y=1;
    cprintf("\r\n - There is no call to Sentry in your AUTOEXEC.BAT file.");
    /* Now prompt the user, and add such a call */
    cprintf("\r\n   Do you wish to add a call to Sentry to your AUTOEXEC.BAT? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
    {
      cprintf("Yes");
      if ((pass=fopen(AUTO,"r"))==NULL)
      {
        if ((pass=fopen(AUTO,"w"))==NULL)
          error(OPSYS);
        else
        {
          fclose(pass);
          if ((pass=fopen(AUTO,"r"))==NULL)
            error(OPSYS);
        }
      }
      tmpnam(lo);
      strcpy(temp,"c:\\");
      strcat(temp,lo);
      if ((npas=fopen(temp,"w"))==NULL)
        error(CRTMP);
      fprintf(npas,"@@%ssentry\n",te);
      while((fgets(lo,MAX,pass))!=NULL)
        fprintf(npas,"%s",lo);
      fclose(npas);
      fclose(pass);
      sunlink(AUBK);
      rename(AUTO,AUBK);
      rename(temp,AUTO);
    }
    else
      cprintf("No");
  }
  if (Win95())
  {
    /* Check for "BootKeys=0" in MSDOS.SYS */
    _chmod(MSDO,1,-FA_HIDDEN-FA_SYSTEM);
    _chmod(MSBK,1,-FA_HIDDEN-FA_SYSTEM);
    if ((pass=fopen(MSDO,"r"))==NULL)
    {
      y=1;
      cprintf("\r\n - Your MSDOS.SYS file does not appear to exist.");
    }
    else
    {
      x=0;
      while((fgets(lo,MAX,pass))!=NULL)
      {
        /* Check to see if BootKeys command already exists */
        if (!strncmp(lo,"BootKeys=0",10))
          x=1; /* Ok, call exists */
      }
    }
    fclose(pass);
    if (!x)
    {
      y=1;
      cprintf("\r\n - There is no \"BootKeys=0\" in your MSDOS.SYS file.");
      /* Prompt the user, and add such a call */
      cprintf("\r\n   Do you wish to add a \"BootKeys=0\" line to your MSDOS.SYS? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
      {
        cprintf("Yes");
        if ((pass=fopen(MSDO,"r"))==NULL)
        {
          if ((pass=fopen(MSDO,"w"))==NULL)
            error(OPSYS);
          else
          {
            fclose(pass);
            if ((pass=fopen(MSDO,"r"))==NULL)
              error(OPSYS);
          }
        }
        tmpnam(lo);
        strcpy(temp,"c:\\");
        strcat(temp,lo);
        if ((npas=fopen(temp,"w"))==NULL)
          error(CRTMP);
        while((fgets(lo,MAX,pass))!=NULL)
        {
          if (strncmp(lo,"BootKeys",8))
            fprintf(npas,"%s",lo);
          if (!strncmp(lo,"[Options]",9))
            fprintf(npas,"BootKeys=0\n");
        }
        fclose(npas);
        fclose(pass);
        sunlink(MSBK);
        rename(MSDO,MSBK);
        rename(temp,MSDO);
      }
      else
        cprintf("No");
    }
    _chmod(MSDO,1,FA_HIDDEN+FA_SYSTEM);
    _chmod(MSBK,1,FA_HIDDEN+FA_SYSTEM);
  }
  else
  {
    /* Check for "switches /n/f" in CONFIG.SYS */
    if ((pass=fopen(CONF,"r"))==NULL)
    {
      y=1;
      cprintf("\r\n - Your CONFIG.SYS file does not appear to exist.");
      /* User will be asked if they want to add a "switches" command */
      x=0;
    }
    else
    {
      x=0;
      while((fgets(lo,MAX,pass))!=NULL)
      {
        /* Check for break on commands */
        strupr(lo);
        if (!strncmp(lo,"BREAK",5) && (lo[strlen(lo)-3]=='O') && (lo[strlen(lo)-2]=='N'))
        {
          cprintf("\r\n - A \"break on\" command exists in your CONFIG.SYS file.");
          /* Now ask the user if they want to remove them */
          cprintf("\r\n   Do you wish to remove it? ");
          y=blch();
          if ((y=='y') || (y=='Y'))
          {
            cprintf("Yes");
            /* Now close the file, open it again, re-write it minus the break command */
            fclose(pass);
            if ((pass=fopen(CONF,"r"))==NULL)
            {
              if ((pass=fopen(CONF,"w"))==NULL)
                error(OPSYS);
              else
              {
                fclose(pass);
                if ((pass=fopen(CONF,"r"))==NULL)
                  error(OPSYS);
              }
            }
            tmpnam(lo);
            strcpy(temp,"c:\\");
            strcat(temp,lo);
            if ((npas=fopen(temp,"w"))==NULL)
              error(CRTMP);
            while((fgets(lo,MAX,pass))!=NULL)
            {
              strcpy(tol,lo);
              strupr(tol);
              if (!(!strncmp(tol,"BREAK",5) && (tol[strlen(tol)-3]=='O') && (tol[strlen(tol)-2]=='N')))
                fprintf(npas,"%s",lo);
            }
            fclose(npas);
            fclose(pass);
            sunlink(COBK);
            rename(CONF,COBK);
            rename(temp,CONF);
            if ((pass=fopen(CONF,"r"))==NULL)
              error(OPSYS);
          }
          else
            cprintf("No");
          y=1;
        }
        /* Check to make sure switches command exists */
        if (!strncmp(lo,"SWITCHES /N",11))
          x=1; /* Ok, switches exists */
      }
      fclose(pass);
    }
    if (!x)
    {
      y=1;
      cprintf("\r\n - There is no \"switches /n/f \" in your CONFIG.SYS file.");
      /* Prompt the user, and add such a call */
      cprintf("\r\n   Do you wish to add a \"switches /n/f\" line to your CONFIG.SYS? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
      {
        cprintf("Yes");
        if ((pass=fopen(CONF,"r"))==NULL)
        {
          if ((pass=fopen(CONF,"w"))==NULL)
            error(OPSYS);
          else
          {
            fclose(pass);
            if ((pass=fopen(CONF,"r"))==NULL)
              error(OPSYS);
          }
        }
        tmpnam(lo);
        strcpy(temp,"c:\\");
        strcat(temp,lo);
        if ((npas=fopen(temp,"w"))==NULL)
          error(CRTMP);
        fprintf(npas,"switches /n/f\n");
        while((fgets(lo,MAX,pass))!=NULL)
          fprintf(npas,"%s",lo);
        fclose(npas);
        fclose(pass);
        sunlink(COBK);
        rename(CONF,COBK);
        rename(temp,CONF);
      }
      else
        cprintf("No");
    }
  }
  if (!y)
    cprintf("OK");
  y=0;
  tmpath(temp);
  if ((npas=fopen(temp,"wb"))==NULL)
    error(CRTMP);
  pass=ffwd(1,npas);
  x=0;
  cprintf("\r\n\r\nChecking Initialization Settings...");
/*
 [Initialization Settings] Check for the following:
 - a short max or short min password length
 - a high or **low** number for maximum login attempts
 - a low number for wait delay
 - password echoing should be off or masked
 - a password expiry max of over 365 days
 - an unused account expiry max of over 365 days
 - a long wait for the screen saver (over 600)
 - case sensitivity is off
*/
  un=-2;
  while((fgets(lo,MAX,pass))!=NULL && (!streq(lo,DIV)))
  {
    un++;
    if ((un==MINP) && (atoi(lo)<4))
    {
      y=1;
      cprintf("\r\n - Your minimum password length is set to %d, which is low.",atoi(lo));
      cprintf("\r\n   Do you wish to raise it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        cprintf("\r\n\r\nEnter the new minimum length for passwords");
        strcpy(lo,gin(": ",1));
        strcat(lo,"\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==MAXP) && (atoi(lo)<10))
    {
      y=1;
      cprintf("\r\n - Your maximum password length is set to %d, which is low.",atoi(lo));
      cprintf("\r\n   Do you wish to raise it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        cprintf("\r\n\r\nEnter the new maximum length for passwords");
        strcpy(lo,gin(": ",1));
        strcat(lo,"\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==MAXI) && (atoi(lo)>5))
    {
      y=1;
      cprintf("\r\n - Your allowable invalid login attempts is set to %d, which is high.",atoi(lo));
      cprintf("\r\n   Do you wish to lower it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        cprintf("\r\n\r\nEnter the number of invalid login attempts before Sentry");
        cprintf("\r\nlocks up");
        strcpy(lo,gin(": ",1));
        strcat(lo,"\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==WAIT) && (atoi(lo)<3))
    {
      y=1;
      cprintf("\r\n - Your invalid login wait delay is set to %d seconds, which is low.",atoi(lo));
      cprintf("\r\n - Do you wish to raise it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        cprintf("\r\n\r\nEnter the number of seconds to delay when a login");
        cprintf("\r\nis incorrect");
        strcpy(lo,gin(": ",1));
        strcat(lo,"\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==PECH) && (lo[0]=='!'))
    {
      y=1;
      cprintf("\r\n - You have passwords echoed directly to the screen!",atoi(lo));
      cprintf("\r\n - Do you wish to echo *'s instead? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        strcpy(lo,"*\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==PEXP) && (atoi(lo)>365))
    {
      y=1;
      cprintf("\r\n - Your password expiry is set to %d days, which is high.",atoi(lo));
      cprintf("\r\n   Do you wish to lower it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        cprintf("\r\n\r\nEnter the number of days new passwords have before");
        cprintf("\r\nthey expire");
        strcpy(lo,gin(": ",1));
        strcat(lo,"\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==AEXP) && (atoi(lo)>365))
    {
      y=1;
      cprintf("\r\n - Your account expiry is set to %d days, which is high.",atoi(lo));
      cprintf("\r\n   Do you wish to lower it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        cprintf("\r\n\r\nEnter the number of days unused accounts have before");
        cprintf("\r\nthey expire");
        strcpy(lo,gin(": ",1));
        strcat(lo,"\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==SSAT) && (atoi(lo)>599))
    {
      y=1;
      cprintf("\r\n - Your screen saver activation time is %d seconds, which is high.",atoi(lo));
      cprintf("\r\n - Do you wish to lower it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        cprintf("\r\n\r\nEnter the number of seconds of inativity that may");
        cprintf("\r\npass before the screen saver is activated");
        strcpy(lo,gin(": ",1));
        strcat(lo,"\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    if ((un==CASE) && (atoi(lo)==1))
    {
      y=1;
      cprintf("\r\n - You have case sensitivity for login names turned off.",atoi(lo));
      cprintf("\r\n - Do you wish to turn it on? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        strcpy(lo,"0\r\n");
        x=1;
      }
      else
        cprintf("No");
    }
    fputs(lo,npas);
  }
  fputs(DIV,npas);
  if (!y)
    cprintf("OK");
  y=0;
  cprintf("\r\n\r\nChecking Account Structure...");
/*
 [Accounts] Check for the following:
 - accounts that have expired (should be deleted)
 - SuperUser accounts with a max inv log setting
 - Normal accounts with no max inv log setting
 - # of failed login attempts is exceeded
 - accounts with no expiry date
 - passwords with no expiry date
a8 143
  while(guser(1))
  {
    /**** Perform user security audit */
    getdate(&td);
    gettime(&nw);
    sul=0;
    if ((ed) && (ed<dostounix(&td,&nw)))
    {
      y=1;
      cprintf("\r\n\r\n User: ");
      cprintf("%s",lo);
      cprintf("\r\nThis account has expired.");
      cprintf("\r\n Do you wish to delete it? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        x=1;
        sul=1;
      }
      else
        cprintf("No");
    }
    if ((fla>ntl) && (!sul))
    {  /* # of failed login attempts exceeds allowable limit */
      y=1;
      cprintf("\r\n\r\n User: ");
      cprintf("%s",lo);
      cprintf("\r\nHas has exceeded his allowable maximum invalid login limit.");
      cprintf("\r\nThis account may have been the target of an attack.");
      cprintf("\r\n Do you wish to delete this account? ");
      maxtry=blch();
      if ((maxtry=='y') || (maxtry=='Y'))
      {
        cprintf("Yes");
        x=1;
        sul=1;
      }
      else
        cprintf("No");
    }
    if (!sul)
    {
      su=((ps[strlen(ps)-3]==STAMP)?1:0);
      if (su && ntl)
      { /* SuperUser accounts with a max inv log setting */
        y=1;
        cprintf("\r\n\r\n User: ");
        cprintf("%s",lo);
        cprintf("\r\nIs a SuperUser with a maximum invalid login setting.");
        cprintf("\r\nThis means if this account is repeatedly attacked, the");
        cprintf("\r\nSuperUser could be locked out!");
        cprintf("\r\n Do you wish to remove the maximum invalid login setting? ");
        maxtry=blch();
        if ((maxtry=='y') || (maxtry=='Y'))
        {
          cprintf("Yes");
          ntl=0;
          x=1;
        }
        else
          cprintf("No");
      }
      if (!su && !ntl)
      {  /* Normal accounts with no max inv log setting */
        y=1;
        cprintf("\r\n\r\n User: ");
        cprintf("%s",lo);
        cprintf("\r\nHas no maximum invalid login setting.");
        cprintf("\r\nThis means if this account can be repeatedly attacked");
        cprintf("\r\nwithout being locked out!");
        cprintf("\r\n Do you wish to add a maximum invalid login setting? ");
        maxtry=blch();
        if ((maxtry=='y') || (maxtry=='Y'))
        {
          cprintf("Yes");
          cprintf("\r\n\r\nEnter the number of sequential invalid logins before the");
          cprintf("\r\nuser's account is automatically expired");
          strcpy(na,gin(": ",1));
          ntl=atoi(na);
          x=1;
        }
        else
          cprintf("No");
      }
      if (ed==0)
      {  /* Account has no expiry date */
        y=1;
        cprintf("\r\n\r\n User: ");
        cprintf("%s",lo);
        cprintf("\r\nHas no expiry date on their account.");
        cprintf("\r\n Do you wish to add an expiry date? ");
        maxtry=blch();
        if ((maxtry=='y') || (maxtry=='Y'))
        {
          cprintf("Yes");
          pe=gdate();
          x=1;
        }
        else
          cprintf("No");
      }
      if (pe==0)
      {  /* Password has no expiry date */
        y=1;
        cprintf("\r\n\r\n User: ");
        cprintf("%s",lo);
        cprintf("\r\nHas no expiry date on their password.");
        cprintf("\r\n Do you wish to add an expiry date? ");
        maxtry=blch();
        if ((maxtry=='y') || (maxtry=='Y'))
        {
          cprintf("Yes");
          pe=gdate();
          x=1;
        }
        else
          cprintf("No");
      }
      fputs(lo,npas);
      fputs(ps,npas);
      pwr;
    }
  }
  fputs(DIV,npas);
  fcd(pass,npas);
  if (!y)
    cprintf("OK");
  if (x)        /* if a setting has been changed */
  {
    sunlink(inam);      /* make the temp file the new main file */
    rename(temp,inam);
  }
  else                   /* if no settings have been changed */
    sunlink(temp);     /* just delete the temp file */
  while(kbhit())
    blch();
  cprintf("\r\n\r\n Audit Complete.");
  strcpy(tol,"Security Audit Performed.");
  tolog(tol);
  su=sul=1;
  blch();
}
d20 3
a22 7
  strcpy(txt[3],"3. Edit Initialization Settings");
  strcpy(txt[4],"4. Send a Message to a User");
  strcpy(txt[5],"5. Protect a File");
  strcpy(txt[6],"6. Export Initialization Settings");
  strcpy(txt[7],"7. Sentry DOS Shell");
  strcpy(txt[8],"8. Security Audit");
  strcpy(txt[SUOPT],"9. Exit");
d25 1
a25 1
  crwin(10,6,48,19,tf,tb,2,"SuperUser Menu");
d41 1
a41 1
  while (1) /**** This is iffy (but it works) */
d69 5
a73 2
       sel=opt-'0';
       opt=13;
d78 1
d83 1
d87 2
a88 1
    case 'i':
d92 1
a92 2
    case 's':
    case 'm':
d96 1
a96 17
    case 'p':
      sel=5;
      opt=13;
      break;
    case 'e':
      sel=6;
      opt=13;
      break;
    case 'd':
      sel=7;
      opt=13;
      break;
    case 'a':
      sel=8;
      opt=13;
      break;
    case 27:  /* Escape */
d132 1
a132 1
        iset();
a135 12
       	smsg();
        y=1;
        break;
      case 5:
        prf();
        y=1;
        break;
      case 6:
      	idmp();
	      y=1;
 	      break;
      case 7:
a139 4
        break;
      case 8:
        secaud();
        y=1;
@


3.8
log
@*** empty log message ***
@
text
@a4 1142
void cpass(void)
/*
  cpass(void) is the function called when a user wishes to change his
  password. cpass(void) requires the user to enter their old password
  (as verification), and then calls setp(void) to set the new password.
*/
{
  short int err=1;
  while (err)
  {
    err=0;
    _bk=0;
    strcpy(pa,gin("\r\nOld Password:",0));
    strncpy(pa,pa,max);
    strcpy(temp,pa);
    temp[strlen(temp)+1]=0;
    temp[strlen(temp)]=STAMP;
    if ((strlen(pa)>max) || (strlen(pa)<min))
      err=2;
    strcpy(temp,penc(temp));
    strcpy(pa,penc(pa));
    pass=ffwd(2,NULL);
    if (!err)
      err=4;
    while((fgets(lo,MAX,pass))!=NULL)
    {
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      chop2(lo);
      chop2(ps);
      if (ps[strlen(ps)-1]==STAMP)
        chop(ps);
      if (err==4)
      {
        if (csck(na,lo))
        {
          err=0;
          strcpy(tol,na);
          strcat(tol," is changing passwords.");
          tolog(tol);
          if (strcmp(pa,ps))
          {
            if (strcmp(temp,ps))
              err=3;
          }
        }
      }
    }
    switch (err)
    {
    case 2:
      cprintf("%s",xplen);
      cprintf("\r\n");
      tolog(lxplen);
      sleep(wait);
      break;
    case 3:
      cprintf("%s",xpwd);
      cprintf("\r\n");
      tolog(lxpwd);
      sleep(wait);
      break;
    case 4:
      cprintf("%s",xlog);
      cprintf("\r\n");
      tolog(lxlog);
      sleep(wait);
      break;
    }
    fclose(pass);
  }
  un*=-1;
  setp();
}

short int view(char *ac)
/*
  view() displays a list of all current users in the password file.
  SuperUsers are denoted with a * to the right of their name. The cursor

  keys are used to highlight a user, and the enter key will select that
  user. The PAGE UP and PAGE DOWN keys can be used to show more screens
  if they are available.
  view() returns the ordinal value of the user selected (as per the
  password file) as an integer.
*/
{
  short int x,y,sel=1,tp=0;
  char opt=0;
  pass=ffwd(2,NULL);
  x=0;
  crwin(1,1,79,24,tf,tb,1,"User List");
  while(((fgets(lo,MAX,pass))!=NULL) && (!streq(lo,DIV)))
  {
    x++;
    if (x<MAXUSER)
    {
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      chop2(lo);
      chop2(ps);
      if (ps[strlen(ps)-1]==STAMP)
      {
        strcat(lo," *");
      }
      prd();
      strcpy(txt[x],lo);
      for(y=strlen(lo);y<LLST;y++)
        strcat(txt[x]," ");
      unixtodos(ut,&td,&nw);
      if (df)
        sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
        else
        sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,
            td.da_year);
      strcat(txt[x],lo);
      sprintf(lo," %02d:%02d:%02d",nw.ti_hour,nw.ti_min,
          nw.ti_sec);
      strcat(txt[x],lo);
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<AEST;y++)
        strcat(txt[x]," ");
      if (ed)
      {
        unixtodos(ed,&td,&nw);
        if (df)
          sprintf(lo,"%02d/%02d/%02d",td.da_day,
              td.da_mon,td.da_year);
          else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,
              td.da_day,td.da_year);
        strcat(txt[x],lo);
      }
      else
        strcat(txt[x]," * NONE *");
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<PEST;y++)
        strcat(txt[x]," ");
      if (pe)
      {
        unixtodos(pe,&td,&nw);
        if (df)
          sprintf(lo,"%02d/%02d/%02d",td.da_day,
              td.da_mon,td.da_year);
          else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,
              td.da_day,td.da_year);
        strcat(txt[x],lo);
      }
      else
        strcat(txt[x]," * NONE *");
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<ILST;y++)
        strcat(txt[x]," ");
      sprintf(lo,"%d",fla);
      strcat(txt[x],lo);
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<NLST;y++)
        strcat(txt[x]," ");
      if (ntl)
        sprintf(lo,"%d",ntl);
        else
        strcpy(lo,"X");
      strcat(txt[x],lo);
    }
    else
    {
      cprintf("Maximum number of users exceeded! (MAXUSER=");
      cprintf("%d",MAXUSER);
      cprintf(")");
    }
  }
  fclose(pass);
  while (1)
  {
    txb(tb);
    txc(tf);
    clrscr();
    cprintf("Current Users (ESC exits)\r\n");
    if (!tp)
      cprintf("\r\n");
    strcpy(lo,"");
    strcpy(pa,lo);
    for(y=strlen(pa);y<LLST;y++)
      strcat(lo," ");
    strcat(lo,"");
    strcpy(pa,lo);
    for(y=strlen(pa);y<AEST;y++)
      strcat(lo," ");
    strcat(lo,"Account");
    strcpy(pa,lo);
    for(y=strlen(pa);y<PEST;y++)
      strcat(lo," ");
    strcat(lo,"Password");
    strcpy(pa,lo);
    for(y=strlen(pa);y<ILST-2;y++)
      strcat(lo," ");
    strcat(lo,"Inv");
    strcpy(pa,lo);
    for(y=strlen(pa);y<NLST-2;y++)
      strcat(lo," ");
    strcat(lo,"Max");
    cprintf("%s",lo);
    cprintf("\r\n");
    strcpy(lo,"User Name");
    strcpy(pa,lo);
    for(y=strlen(pa);y<LLST;y++)
      strcat(lo," ");
    strcat(lo,"Last Login");
    strcpy(pa,lo);
    for(y=strlen(pa);y<AEST;y++)
      strcat(lo," ");
    strcat(lo,"Expiry");
    strcpy(pa,lo);
    for(y=strlen(pa);y<PEST;y++)
      strcat(lo," ");
    strcat(lo,"Expiry");
    strcpy(pa,lo);
    for(y=strlen(pa);y<ILST-2;y++)
      strcat(lo," ");
    strcat(lo,"Log");
    strcpy(pa,lo);
    for(y=strlen(pa);y<NLST-2;y++)
      strcat(lo," ");
    strcat(lo,"Inv Log");
    cprintf("%s",lo);
    cprintf("\r\n");
    for(y=0;y<(NLST+6);y++)
      cprintf("-");
    if (tp)
    {
      gotoxy(NLST+4,1);
      cprintf("");
    }
    cprintf("\r\n");
    if (tp)
      cprintf("\r\n\r\n\r\n");
    for(y=tp;y<WIND+tp;y++)
    {
      if (y<=x)
      {
        if (sel==(y % WIND))
        {
          txb(hb);
          txc(hf);
        }
        else
        {
          txb(tb);
          txc(tf);
        }
        if (y)
        {
          cprintf("%s",txt[y]);
          cprintf("\r\n");
        }
      }
    }
    txb(tb);
    txc(tf);
    if (tp+WIND<=x)
    {
      gotoxy(NLST+4,21);
      cprintf("");
    }
    gotoxy(1,22);
    cprintf("Select a user [");
    cprintf("%s",ac);
    cprintf("]: ");
    opt=blch();
    switch (opt)
    {
    case 13:
      return(sel+tp);
    case 77:
    case 80:
      if ((sel<(WIND-1)) && ((sel+tp)<x))
        sel++;
        else
        if ((sel+tp)<x)
        {
          tp+=WIND;
          sel=0;
        }
      break;
    case 72:
    case 75:
      if ((sel>1) || ((sel>0) && (tp>0)))
        sel--;
        else
        if (tp>0)
        {
          tp-=WIND;
          sel=WIND-1;
        }
      break;
    case 73:
      if (tp>0)
      {
        tp-=WIND;
        if (!sel)
          sel=1;
      }
      else
        sel=1;
      break;
    case 81:
      if ((tp+WIND)<=x)
        tp+=WIND;
        else
        sel=x-tp;
      if (!((sel+tp)<=x))
        sel=x-tp;
      break;
    case 27:
      return(0);
    }
  }
}

void cru(void)
/*
  cru() is the function used to create a new user. This function is
  called only from the SuperUser menu. All normal verifying is performed
  before the user information is saved.
*/
{
  short int err=1;
  char opt;
  sul=0;
  crwin(2,5,65,22,tf,tb,2,"Create A User");
  if (!wm)
    clrscr();
  while (err>0)
  {
    err=0;
    cprintf("\r\n\r\nCreate User.\r\n\r\n");
    _bk=1;
    strcpy(na,gin("Login:",1));
    strncpy(na,na,max);
    strcpy(temp,na);
    if (bk)
      break;
    if ((strlen(temp)>max) || (strlen(temp)<min))
      err=1;
    npas=ffwd(2,NULL);
    while((fgets(lo,MAX,npas))!=NULL)
    {
      fgets(ps,MAX,npas);
      fgets(ti,MAX,npas);
      chop2(lo);
      if (csck(temp,lo))
        if (err==0)
          err=4;
    }
    if (!err)
    {
      fclose(npas);
      tmpath(temp);
      if ((npas=fopen(temp,"wb"))==NULL)
        error("Error opening temp file!");
      pass=ffwd(3,npas);
      ed=ftell(npas);
      ed-=DIVLEN;
      fseek(npas,ed,SEEK_SET);
      _bk=1;
      strcpy(pa,gin("Password:",0));
      strncpy(pa,pa,max);
      if (bk)
      {
        unlink(temp);
        break;
      }
      if ((strlen(pa)>max) || (strlen(pa)<min))
        err=2;
      if (!err)
      {
        if (sul)
        {
          pa[strlen(pa)+1]=0;
          pa[strlen(pa)]=STAMP;
        }
        strcpy(pa,penc(pa));
        _bk=1;
        strcpy(ps,gin("Verify Password:",0));
        strncpy(ps,ps,max);
        if (bk)
        {
          unlink(temp);
          break;
        }
        if (sul)
        {
          ps[strlen(ps)+1]=0;
          ps[strlen(ps)]=STAMP;
        }
        strcpy(ps,penc(ps));
        if (strcmp(pa,ps))
          err=3;
        if (!err)
        {
          if (sul)
          {
            pa[strlen(pa)+1]=0;
            pa[strlen(pa)]=STAMP;
          }
          cprintf("Do you want this account to have an expiry date? ");
          opt=blch();
          if ((opt=='y') || (opt=='Y'))
            ed=gdate();
          else
            ed=0;
          cprintf("\r\nDo you want the password to have an expiry date? ");
          opt=blch();
          if ((opt=='y') || (opt=='Y'))
            pe=gdate();
          else
            pe=0;
          cprintf("\r\nDo you want to set the maximum number of invalid logins? ");
          opt=blch();
          if ((opt=='y') || (opt=='Y'))
            ntl=atoi(gin("\r\n\r\nHow many consecutive invalid logins\r\nbefore the account expires?",1));
          else
            ntl=ltl;
          cprintf("\r\n");
          ae=0; /**** Set new variable to 0 ****/
        }
      }
    }
    switch (err)
    {
    case 1:
      cprintf("Logins must be between ");
      cprintf("%d",min);
      cprintf(" and ");
      cprintf("%d",max);
      cprintf(" characters.\r\n");
      break;
    case 2:
      cprintf("Passwords must be between ");
      cprintf("%d",min);
      cprintf(" and ");
      cprintf("%d",max);
      cprintf(" characters.\r\n");
      break;
    case 3:
      cprintf("Password not verified!\r\n");
      break;
    case 4:
      cprintf("That user already exists!\r\n");
      break;
    }
    if (!err)
    {
      fprintf(npas,"%s\r\n",na);
      fprintf(npas,"%s\r\n",pa);
      strcpy(tol,"User ");
      strcat(tol,na);
      strcat(tol," Created.");
      tolog(tol);
      getdate(&td);
      gettime(&nw);
      ut=dostounix(&td,&nw);
      fla=0;
      pwr;
      fprintf(npas,"%s",DIV);
    }
    fcd(pass,npas);
    if (!err)
    {
      unlink(inam);
      rename(temp,inam);
    }
    else
      unlink(temp);
  }
}

void del(void)
/*
  del() is the function called to delete a user. It is called only from
  the SuperUser menu. It first calls view() so that the intended user
  can be selected. A check is performed to make sure that the last
  SuperUser listed in the password file is not being deleted.
*/
{
  short int x,y=0;
  char opt;
  x=view("Delete");
  if (x)
  {
    crwin(2,7,60,17,tf,tb,2,"Delete A User");
    if (!wm)
      clrscr();
    opt=0;
    pass=ffwd(2,NULL);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      fgets(ps,MAX,pass);
      if (ps[strlen(ps)-3]==STAMP)
        opt++;
      fgets(ti,MAX,pass);
    }
    fclose(pass);
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error("Error opening temp file!");
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      chop2(na);
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-3]==STAMP)
          cprintf("\r\nThis is a SuperUser!");
        if ((opt==1) && (ps[strlen(ps)-3]==STAMP))
        {
          cprintf("\r\n\r\nYou cannot delete this user, they are\r\n");
          cprintf("the last SuperUser!");
          cprintf("\r\n\r\nPress any key to return to the SuperUser menu...");
          opt=blch();
          opt=0;
        }
        else
        {
          cprintf("\r\n\r\nAre you sure you want to delete ");
          cprintf("%s",na);
          cprintf("? ");
          opt=blch();
        }
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          strcpy(tol,"User ");
          strcat(tol,na);
          strcat(tol," Deleted.");
          tolog(tol);
        }
      }
    }
    fcd(pass,npas);
    unlink(inam);
    rename(temp,inam);
  }
}

void toggle(void)
/*
  toggle() is the function called to toggle SuperUser status. It is
  called only from the SuperUser menu. It first calls view() so that the

  intended user can be selected. The user's password must be entered
  to replace the old password and access group. A check is performed so
  that SuperUser priviliges cannot be removed from the last SuperUser.
*/
{
  short int v,err=0,y=0;
  char opt;
  v=view("Toggle");
  if (v)
  {
    crwin(2,5,69,22,tf,tb,2,"Toggle SuperUser Status");
    if (!wm)
      clrscr();
    cprintf("\r\nNOTE: The user must re-enter their password to obtain or give up\r\n");
    cprintf("      SuperUser access.\r\n");
    cprintf("      You may override this by entering any other password, which\r\n");
    cprintf("      will be this user's password from now on.\r\n");
    opt=0;
    pass=ffwd(2,NULL);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      fgets(ps,MAX,pass);
      if (ps[strlen(ps)-3]==STAMP)
        opt++;
      fgets(ti,MAX,pass);
    }
    fclose(pass);
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error("Error opening temp file!");
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      chop2(na);
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=v)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        sul=0;
        if ((opt==1) && (ps[strlen(ps)-3]==STAMP))
        {
          cprintf("\r\nYou cannot remove SuperUser access from the last SuperUser!");
          cprintf("\r\n\r\nPress any key to return to the SuperUser menu...");
          opt=blch();
          opt=0;
        }
        else
        {
          cprintf("\r\n\r\nAre you sure you want to ");
          if (ps[strlen(ps)-3]==STAMP)
            cprintf("remove SuperUser access from");
            else
          {
            cprintf("grant SuperUser access to");
            sul=1;
          }
          cprintf(" ");
          cprintf("%s",na);
          cprintf("? ");
          opt=blch();
        }
        if ((opt=='y') || (opt=='Y'))
        {
          _bk=0;
          strcpy(pa,gin("\r\n\r\nPassword:",0));
          strncpy(pa,pa,max);
          if ((strlen(pa)>max) || (strlen(pa)<min))
          {
            cprintf("Passwords must be between ");
            cprintf("%d",min);
            cprintf(" and ");
            cprintf("%d",max);
            cprintf(" characters.\r\n");
            cprintf("\r\nPress any key to continue...");
            opt=blch();
            err=2;
          }
          if (!err)
          {
            if (sul)
            {
              pa[strlen(pa)+1]=0;
              pa[strlen(pa)]=STAMP;
            }
            strcpy(pa,penc(pa));
            _bk=0;
            strcpy(na,gin("Verify Password:",0));
            strncpy(na,na,max);
            if (sul)
            {
              na[strlen(na)+1]=0;
              na[strlen(na)]=STAMP;
            }
            strcpy(na,penc(na));
            if (strcmp(pa,na))
            {
              cprintf("Password not verified!\r\n");
              cprintf("\r\nPress any key to continue...");
              opt=blch();
              err=3;
            }
            if (!sul)
            {
              na[strlen(na)+2]=0;
              na[strlen(na)+1]='\n';
              na[strlen(na)]='\r';
            }
            else
            {
              na[strlen(na)+3]=0;
              na[strlen(na)+2]='\n';
              na[strlen(na)+1]='\r';
              na[strlen(na)]=STAMP;
            }
            if (!err)
            {
              strcpy(ps,na);
              strcpy(tol,"SuperUser Access ");
              if (sul)
                strcat(tol,"Granted to");
              else
                strcat(tol,"Revoked from");
              strcat(tol," user ");
              strcpy(na,lo);
              chop2(na);
              strcat(tol,na);
              strcat(tol,".");
              tolog(tol);
            }
          }
          if (err)
          {
            ps[strlen(ps)+2]=0;
            ps[strlen(ps)+1]='\n';
            ps[strlen(ps)+1]='\r';
          }
        }
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
    }
    fcd(pass,npas);
    unlink(inam);
    rename(temp,inam);
  }
}

void cex(void)
/*
  cex(void) creates an expiry date for an account. The account to be
  adjusted is selected via view(void). That account's current expiry
  settings are then shown, and the user is asked if they want to alter
  them. If they answer yes, the date new expiry is entered via
  gdate(void) and saved in the password file.
*/
{
  short int x;
  long zs;
  char opt;
  x=view("Change Accont Expiry");
  if (x)
  {
    crwin(2,5,65,22,tf,tb,2,"Account Expiry");
    if (!wm)
      clrscr();
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error("Error opening temp file!");
    pass=ffwd(2,npas);
    guser(x);
    strcpy(na,lo);
    chop2(na);
    if (ps[strlen(ps)-1]==STAMP)
      cprintf("\r\nThis is a SuperUser!\r\n");
    if (ed)
    {
      unixtodos(ed,&td,&nw);
      cprintf("\r\nCurrent expiry date is ");
      if (df)
        cprintf("%02d/%02d/%02d.\r\n",td.da_day,td.da_mon,td.da_year);
      else
        cprintf("%02d/%02d/%02d.\r\n",td.da_mon,td.da_day,td.da_year);
      getdate(&td);
      gettime(&nw);
      zs=dostounix(&td,&nw);
      if (zs>ed)
        cprintf("(This account has expired.)\r\n");
    }
    else
      cprintf("\r\nThis account has no expiry date.\r\n");
    cprintf("Do you want to change ");
    cprintf("%s",na);
    cprintf("'s expiry date? ");
    opt=blch();
    if ((opt!='y') && (opt!='Y'))
    {
      fputs(lo,npas);
      fputs(ps,npas);
      fputs(ti,npas);
    }
    else
    {
      ed=gdate();
      fputs(lo,npas);
      fputs(ps,npas);
      pwr;
      chop2(lo);
      if (ed)
      {
        unixtodos(ed,&td,&nw);
        strcpy(tol,"User ");
        strcat(tol,lo);
        strcat(tol," account expiry changed to ");
        if (df)
          sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
        strcat(tol,lo);
        strcat(tol,".");
      }
      else
      {
        strcpy(tol,"User ");
        strcat(tol,lo);
        strcat(tol," accout expiry removed.");
      }
      tolog(tol);
    }
    fcd(pass,npas);
    unlink(inam);
    rename(temp,inam);
  }
}

void pex(void)
/*
  pex(void) creates an expiry date for a password. The account to be
  adjusted is selected via view(void). That account's current password
  expiry settings are then shown, and the user is asked if they want to
  alter them. If they answer yes, the new expiry date is entered via
  gdate(void) and saved in the password file.
*/
{
  short int x;
  long zs;
  char opt;
  x=view("Change Password Expiry");
  if (x)
  {
    crwin(2,5,65,22,tf,tb,2,"Password Expiry");
    if (!wm)
      clrscr();
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error("Error opening temp file!");
    pass=ffwd(2,npas);
    guser(x);
    strcpy(na,lo);
    chop2(na);
    if (ps[strlen(ps)-1]==STAMP)
      cprintf("\r\nThis is a SuperUser!\r\n");
    if (pe)
    {
      unixtodos(pe,&td,&nw);
      cprintf("\r\nCurrent expiry date is ");
      if (df)
        cprintf("%02d/%02d/%02d.\r\n",td.da_day,td.da_mon,td.da_year);
      else
        cprintf("%02d/%02d/%02d.\r\n",td.da_mon,td.da_day,td.da_year);
      getdate(&td);
      gettime(&nw);
      zs=dostounix(&td,&nw);
      if (zs>pe)
        cprintf("(This password has expired.)\r\n");
    }
    else
      cprintf("\r\nThis password has no expiry date.\r\n");
    cprintf("Do you want to change %s's expiry date? ",na);
    opt=blch();
    if ((opt!='y') && (opt!='Y'))
    {
      fputs(lo,npas);
      fputs(ps,npas);
      fputs(ti,npas);
    }
    else
    {
      pe=gdate();
      fputs(lo,npas);
      fputs(ps,npas);
      pwr;
      chop2(lo);
      if (pe)
      {
        unixtodos(pe,&td,&nw);
        sprintf(tol,"User %s password expiry changed to ",lo);
        if (df)
          sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
        strcat(tol,lo);
        strcat(tol,".");
      }
      else
        sprintf(tol,"User %s password expiry removed.",lo);
      tolog(tol);
    }
    fcd(pass,npas);
    unlink(inam);
    rename(temp,inam);
  }
}

void vlog(char *tlf)
/*
  vlog() is called when the user wishes to view the log file. They can
  purge the log after viewing if desired.
*/
{
char dr[MAXDRIVE],di[MAXDIR],fi[MAXFILE],ex[MAXEXT];
short int m,x,c=0,vl;
  if (streq(tlf,ilog))
    tolog("Log File Viewed.");
  else
    tolog("Backup Log File Viewed.");
  fclose(logf);
  crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
  vl=VLBOT-VLTOP-VLCONST;
  cprintf("\r\n\r\nView for [O]ne or [A]ll users? ");
  m=blch();
  if (m=='O')
    m='o';
  if (m=='o')
  {
    m=view("View Log File");
    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
    pass=ffwd(2,NULL);
    for(x=1;x<m;x++)
    {
      fgets(lo,MAX,pass);
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
    }
    fgets(lo,MAX,pass);
    fgets(ps,MAX,pass);
    fgets(ti,MAX,pass);
    prd();
    chop2(lo);
  }
  else
  {
    strcpy(lo,"");
    m=0;
    clrscr();
  }
  if (!wm)
  {
    vl=VLFULL;
    clrscr();
  }
  if ((logf=fopen(tlf,"r"))==NULL)
  {
    if ((logf=fopen(tlf,"w"))==NULL)
      error("Error opening log file!");
    else
    {
      fclose(logf);
      if ((logf=fopen(tlf,"r"))==NULL)
      error("Error opening log file!");
    }
  }
  x=0;
  while((fgets(cp,MAX,logf))!=NULL)
  {
    chop(cp);
    fgets(temp,MAX,logf);
    if (!m || streq(lo,cp))
    {
      x++;
      if (strlen(temp)>SCRWIDTH)
        x++;
      cprintf("%s\r",temp);
      if (x>vl)
      {
        cprintf("\r\n  Press a key to continue...");
        c=blch();
        cprintf("\r\n");
        x=0;
      }
      if (c==27)
        break;
    }
  }
  fclose(logf);
  if (c!=27)
  {
    cprintf("\r\n  Press a key to continue...");
    c=blch();
    cprintf("\r\n");
  }
  cprintf("\r\n Would you like to clear ");
  if (m)
    cprintf("%s's log file [y/N]? ",lo);
  else
    cprintf("the log file [y/N]? ");
  c=blch();
  if ((c=='y') || (c=='Y'))
  {
    if (m)
    {
      if ((logf=fopen(tlf,"r"))==NULL)
        error("Error opening log file!");
      x=fnsplit(tlf,dr,di,fi,ex);
      tmpnam(temp);
      if (x & DIRECTORY)
      {
        strcpy(tol,temp);
        strcpy(temp,di);
        strcat(temp,tol);
      }
      if (x & DRIVE)
      {
        strcpy(tol,temp);
        strcpy(temp,dr);
        strcat(temp,tol);
      }
      if ((npas=fopen(temp,"w"))==NULL)
        error("Error opening temp file!");
      while((fgets(cp,MAX,logf))!=NULL)
      {
        chop(cp);
        fgets(na,MAX,logf);
        if (!streq(lo,cp))
          fprintf(npas,"%s\n%s",cp,na);
      }
      fclose(logf);
      fclose(npas);
      unlink(tlf);
      rename(temp,tlf);
    }
    else
    {
      if ((logf=fopen(tlf,"w"))==NULL)
        error("Error in creating log file!");
      fclose(logf);
    }
    if ((logf=fopen(ilog,"a"))==NULL)
      error("Error in creating log file!");
    cprintf("\r\n\r\n The log file has been cleared.\r\n");
    if (streq(tlf,ilog))
      tolog("Log File Viewed.");
    else
      tolog("Backup Log File Viewed.");
    fclose(logf);
    cprintf("\r\n  Press a key to continue...");
    c=blch();
  }
  if ((logf=fopen(ilog,"a"))==NULL)
    error("Error in creating log file!");
}

void mvlog(void)
{
  fclose(logf);
  if ((pass=fopen(ilbk,"a"))==NULL)
    error("Error in creating backup log file!");
  if ((logf=fopen(ilog,"r"))==NULL)
    error("Error opening log file!");
  while((fgets(cp,MAX,logf))!=NULL)
    fputs(cp,pass);
  fclose(pass);
  fclose(logf);
  if ((logf=fopen(ilog,"w"))==NULL)
    error("Error in creating log file!");
  tolog("Log File Moved to Backup.");
  crwin(2,10,65,14,tf,tb,2,"Backup Log File");
  if (!wm)
    clrscr();
  cprintf("\r\n\r\n     The log file has been moved to the backup file...\r\n");
  blch();
}

void alock(void)
/*
  alock(void) allows accounts to be locked out after a certain number of
  sequential invalid logins. alock(void) calls view(void) first so the
  proper account can be selected. It then prompts the user for a new
  "max invalid login" value.
*/
{
  short int x,y=0;
  char opt,ho[MAX];
  x=view("Max Inxalid Logins");
  if (x)
  {
    crwin(2,5,65,22,tf,tb,2,"Account Lock Out");
    if (!wm)
      clrscr();
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error("Error opening temp file!");
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      chop2(na);
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-1]==STAMP)
          cprintf("\r\nThis is a SuperUser!\r\n");
        prd();
        if (ntl)
          cprintf("\r\nThis account will currently lock up after %d invalid logins.\r\n",ntl);
        else
          cprintf("\r\nThis account has no limit on invalid logins.\r\n");
        cprintf("Do you want to change %s's invalid login setting? ",na);
        opt=blch();
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          x=0;
          while (x==0)
          {
            x=1;
            cprintf("\r\n\r\nEnter 'N' or '0' to assign unlimited invalid logins.");
            cprintf("\r\n\r\nEnter the number of sequential invalid logins before the");
            cprintf("\r\nuser's account is automatically expired");
            strcpy(ho,gin(": ",1));
            if ((streq(ho,"n")) || (streq(ho,"N")))
              ntl=0;
              else
            {
              ntl=atoi(ho);
            }
          }
          fputs(lo,npas);
          fputs(ps,npas);
          pwr;
          chop2(lo);
          if (ntl)
            sprintf(tol,"%s's invalid login setting is changed to %d.",lo,ntl);
            else
            sprintf(tol,"%s's invalid login setting removed.");
          tolog(tol);
        }
      }
    }
    fcd(pass,npas);
    unlink(inam);
    rename(temp,inam);
  }
}

d15 1
a15 1
  crwin(7,1,47,22,tf,tb,2,"Initialization Settings");
d27 2
a28 2
      gotoxy(30,2);
      cprintf("");
d55 2
a56 2
      gotoxy(30,20);
      cprintf("");
d58 2
a59 2
    gotoxy(1,20);
    cprintf("Select a setting: ");
d65 1
a65 1
      crwin(7,1,47,22,tf,tb,2,"Initialization Settings");
d146 7
a152 1
  for (tv=0;tv<set;tv++)
d154 1
a154 1
      error("Error in Initialization Settings!");
d165 11
a175 7
    error("Error opening Sentry.ins!");
  for(x=0;x<((set-2)*2);x++)
    while((fgets(lo,MAX,ini)!=NULL) && (!streq(lo,"\n")))
    { /* Just keep readin' fella */
    }
  while((fgets(lo,MAX,ini)!=NULL) && (!streq(lo,"\n")))
    cprintf("%s\r",lo); /* Read description */
d235 3
a237 1
  while((fgets(lo,MAX,ini)!=NULL) && (!streq(lo,"\n")))
d239 114
a352 2
    chop(lo);
    cprintf("%s",lo);   /* Read default setting line */
d354 1
a354 1
  fclose(ini);
d361 1
a361 1
  if ((strlen(cv)!=0) && (!bk))
d396 1
a396 1
  if ((strlen(cv)!=0) && (!bk))
d400 1
a400 1
      error("Error opening temp file!");
d402 9
d413 2
a414 2
        error("Error in Initialization Settings!");
        else
d417 1
a417 1
          else
d422 1
a422 1
    unlink(inam);
d428 1
a428 1
    unlink(temp);
d438 1
a438 1
    crwin(2,7,70,17,tf,tb,2,"Send A Message");
d442 2
a443 1
    while((fgets(lo,MAX,pass))!=NULL)
d450 1
d452 2
d455 1
a455 1
          error("Error Opening Message File.");
d481 23
d508 1
a508 1
  crwin(2,7,70,17,tf,tb,2,"Protect File");
d512 5
a516 1
  while (x)
d520 10
a529 4
    bk=0;
    strcpy(cv,gin("\r\nEnter File to Protect:",1));
    if (bk)
      x=0;
d532 1
a532 3
      y=fnsplit(cv,dr,di,fi,ex);
      strupr(ex);
      if (!streq(ex,".EXE") && !streq(ex,".COM") && !streq(ex,".BAT"))
d534 1
a534 1
        cprintf("\r\nFile must have EXE, COM or BAT extension.\r\n\r\n");
d538 2
a539 1
        if ((npas=fopen(cv,"r"))==NULL)
d541 1
a541 1
          cprintf("\r\nPlease enter a valid path.\r\n\r\n");
d543 52
d596 2
a597 1
      fclose(npas);
d616 1
a616 1
      error("Error opening temp file!");
d619 1
a619 1
      error("Error in Initialization Settings!");
d628 1
d630 1
a630 1
    fprintf(npas,"%c",ze);
d633 1
a633 1
      error("Error opening protected file!");
d635 1
a635 1
      error("Error opening temp file!");
d648 1
a648 1
        cprintf("\r\nCannot create protected file!\r\n");
d650 5
a654 1
        cprintf(" already exists and cannot be created!\r\n");
d658 1
a658 1
        unlink(temp);
d661 1
a661 1
        unlink(lo);
d665 1
a665 1
      unlink(cv);
d684 1
a684 1
      error("Error opening temp file!");
d696 586
d1296 3
a1298 1
  strcpy(txt[SUOPT],"7. Exit");
d1300 2
a1301 2
    error("Internal Screen Error. [Writing]");
  crwin(10,8,52,19,tf,tb,2,"SuperUser Menu");
d1317 1
a1317 1
  while (1) /**** This is iffy (but it works) ****/
d1319 1
d1375 8
d1405 1
d1407 1
d1417 1
a1417 1
        break;
d1423 1
a1423 1
        smsg();
d1431 3
a1433 165
        idmp();
        y=1;
        break;
      case SUOPT:
        su=sul=1;
        if (!puttext(1,1,80,25,msc))
          error("Internal Screen Error. [Writing]");
        fin(0);
        break;
      }
    if (y)
      suinit();
    y=opt=0;
  }
}

void usrinit(void)
/*
  usrinit() initializes the User Maintenance menu options in the
  string txt[].
  This is done seperately from the user() function so that it can be
  performed as required. view() and super() also uses the txt[] variable, so
  usrinit() must be called after each call to view().
*/
{
  strcpy(txt[1],"1. Create User");
  strcpy(txt[2],"2. Delete User");
  strcpy(txt[3],"3. View All Users");
  strcpy(txt[4],"4. Toggle SuperUser Status");
  strcpy(txt[5],"5. Change Account Expiry Date");
  strcpy(txt[6],"6. Change Password Expiry Date");
  strcpy(txt[7],"7. Change Account Password");
  strcpy(txt[8],"8. Assign Max Number of Invalid Logins");
  strcpy(txt[USOPT],"9. Return to SuperUser Menu");
  if (!puttext(1,1,80,25,msc))
    error("Internal Screen Error. [Writing]");
  crwin(10,7,52,20,tf,tb,2,"User Maintenance Menu");
}

void user(void)
/*
  user() contains all User Maintenance otpions.
*/
{
  short int x,y;
  char opt,sel=1;
  usrinit();
  y=opt=0;
  while (1) /**** This is iffy (but it works) ****/
  {
    clrscr();
    txb(tb);
    txc(tf);
    cprintf("\r\n");
    for(x=1;x<=USOPT;x++)
    {
      if (sel==x)
      {
        txb(hb);
        txc(hf);
      }
      else
      {
        txb(tb);
        txc(tf);
      }
      cprintf("%s",txt[x]);
      cprintf("\r\n");
    }
    txb(tb);
    txc(tf);
    cprintf("\r\nOption: ");
    opt=blch();
    if (isdigit(opt))
    {
      sel=opt-'0';
      opt=13;
    }
    switch (opt)
    {
    case 'c':
      sel=1;
      opt=13;
      break;
    case 'd':
      sel=2;
      opt=13;
      break;
    case 'v':
      sel=3;
      opt=13;
      break;
    case 't':
      sel=4;
      opt=13;
      break;
    case 'a':
      sel=5;
      opt=13;
      break;
    case 'e':
      sel=6;
      opt=13;
      break;
    case 'p':
      sel=7;
      opt=13;
      break;
    case 'm':
    case 'l':
      sel=8;
      opt=13;
      break;
    case 27:  /* Escape */
    case 'r':
    case 's':
    case 'x':
      sel=USOPT;
      opt=13;
      break;
    case 77:   /* Cursor Right/Down */
    case 80:
      if (sel<USOPT)
        sel++;
      break;
    case 75:    /* Cursor Up/Left */
    case 72:
      if (sel>1)
        sel--;
      break;
    case 73:  /* Page Up */
      sel=1;
      break;
    case 81:   /* Page Down */
      sel=USOPT;
      break;
    }
    if (opt==13)
      switch (sel)
      {
      case 1:
        cru();
        y=1;
        break;
      case 2:
        del();
        y=1;
        break;
      case 3:
        tolog("User List Viewed.");
        view("View");
        y=1;
        break;
      case 4:
        toggle();
        y=1;
        break;
      case 5:
        cex();
        y=1;
        break;
      case 6:
        pex();
        y=1;
        break;
d1435 4
a1438 9
        un=view("Change Password")*-1;
        if (un)
        {
          crwin(2,5,65,22,tf,tb,2,"Change Password");
          if (!wm)
            clrscr();
          setp();
        }
        y=1;
d1441 1
a1441 1
        alock();
d1444 6
a1449 54
      case USOPT:
        su=sul=1;
        super();
        break;
      }
    if (y)
      usrinit();
    y=opt=0;
  }
}

void loginit(void)
/*
  loginit() initializes the Log File Maintenance menu options in the
  string txt[].
  This is done seperately from the user() function so that it can be
  performed as required. view() and super() also uses the txt[] variable, so
*/
{
  strcpy(txt[1],"1. View Primary Log File");
  strcpy(txt[2],"2. View Backup Log File");
  strcpy(txt[3],"3. Move Log File to Backup");
  strcpy(txt[LGOPT],"4. Return to SuperUser Menu");
  if (!puttext(1,1,80,25,msc))
    error("Internal Screen Error. [Writing]");
  crwin(10,10,52,18,tf,tb,2,"Log File Maintenance Menu");
}

void logm(void)
/*
  logm() contains all User Maintenance otpions.
*/
{
  short int x,y;
  char opt,sel=1;
  loginit();
  y=opt=0;
  while (1) /**** This is iffy (but it works) ****/
  {
    clrscr();
    txb(tb);
    txc(tf);
    cprintf("\r\n");
    for(x=1;x<=LGOPT;x++)
    {
      if (sel==x)
      {
        txb(hb);
        txc(hf);
      }
      else
      {
        txb(tb);
        txc(tf);
a1450 49
      cprintf("%s",txt[x]);
      cprintf("\r\n");
    }
    txb(tb);
    txc(tf);
    cprintf("\r\nOption: ");
    opt=blch();
    if (isdigit(opt))
    {
      sel=opt-'0';
      opt=13;
    }
    switch (opt)
    {
    case 'v':
      sel=1;
      opt=13;
      break;
    case 'b':
      sel=2;
      opt=13;
      break;
    case 'm':
      sel=3;
      opt=13;
      break;
    case 27:  /* Escape */
    case 'r':
    case 's':
    case 'x':
      sel=LGOPT;
      opt=13;
      break;
    case 77:   /* Cursor Right/Down */
    case 80:
      if (sel<LGOPT)
        sel++;
      break;
    case 75:    /* Cursor Up/Left */
    case 72:
      if (sel>1)
        sel--;
      break;
    case 73:  /* Page Up */
      sel=1;
      break;
    case 81:   /* Page Down */
      sel=LGOPT;
      break;
a1451 20
    if (opt==13)
      switch (sel)
      {
      case 1:
        vlog(ilog);
        y=1;
        break;
      case 2:
        vlog(ilbk);
        y=1;
        break;
      case 3:
        mvlog();
        y=1;
        break;
      case LGOPT:
        su=sul=1;
        super();
        break;
      }
d1453 1
a1453 1
      loginit();
@


3.3
log
@Protected files, export settings.
@
text
@d2 1
a2 1
	FUNCTIONS
d17 2
a18 2
		strcpy(pa,gin("\n\rOld Password:",0));
		strncpy(pa,pa,max);
d42 2
a43 2
          sprintf(tol,"%s is changing passwords.",
              na);
d56 2
a57 1
      cprintf("%s\n\r",xplen);
d62 2
a63 1
      cprintf("%s\n\r",xpwd);
d68 2
a69 1
      cprintf("%s\n\r",xlog);
d80 1
a80 1
short int view(void)
d96 2
a97 2
	crwin(1,1,79,24,tf,tb,1,"User List");
	while(((fgets(lo,MAX,pass))!=NULL) && (!streq(lo,DIV)))
d109 2
a110 2
			}
			prd();
d116 1
a116 2
        sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,
            td.da_year);
d171 5
a175 2
      cprintf("Maximum number of users exceeded! (MAXUSER=%d)",
          MAXUSER);
d183 1
a183 1
		cprintf("Current Users (ESC exits)\n\r");
d185 2
a186 2
      cprintf("\n\r");
		strcpy(lo,"");
d190 1
a190 1
		strcat(lo,"");
d194 1
a194 1
		strcat(lo,"Account");
d198 1
a198 1
		strcat(lo,"Password");
d202 1
a202 1
		strcat(lo,"Inv");
d206 3
a208 2
		strcat(lo,"Max");
    cprintf("%s\n\r",lo);
d217 1
a217 1
		strcat(lo,"Expiry");
d221 1
a221 1
		strcat(lo,"Expiry");
d225 1
a225 1
		strcat(lo,"Log");
d229 3
a231 2
		strcat(lo,"Inv Log");
    cprintf("%s\n\r",lo);
d234 3
a236 3
		if (tp)
		{
			gotoxy(NLST+4,1);
d239 1
a239 1
    cprintf("\n\r");
d241 1
a241 1
			cprintf("\n\r\n\r\n\r");
d257 4
a260 1
          cprintf("%s\n\r",txt[y]);
d271 3
a273 1
    cprintf("Select a user: ");
d335 1
a335 1
	crwin(2,5,65,22,tf,tb,2,"Create A User");
d341 1
a341 1
    cprintf("\n\r\n\rCreate User.\n\r\n\r");
d343 2
a344 2
		strcpy(na,gin("Login:",1));
		strncpy(na,na,max);
d362 8
a369 8
			fclose(npas);
			tmpnam(temp);
			if ((npas=fopen(temp,"wb"))==NULL)
				error("Error opening temp file!");
			pass=ffwd(3,npas);
			ed=ftell(npas);
			ed-=DIVLEN;
			fseek(npas,ed,SEEK_SET);
d372 6
a377 6
			strncpy(pa,pa,max);
			if (bk)
			{
				unlink(temp);
				break;
			}
d390 6
a395 6
				strncpy(ps,ps,max);
				if (bk)
				{
					unlink(temp);
					break;
				}
d415 1
a415 1
					else
d417 1
a417 1
          cprintf("\n\rDo you want the password to have an expiry date? ");
d421 1
a421 1
					else
d423 1
a423 1
					cprintf("\n\rDo you want to set the maximum number of invalid logins? ");
d426 5
a430 5
						ntl=atoi(gin("\n\r\n\rHow many consecutive invalid logins\n\rbefore the account expires?",1));
					else
						ntl=ltl;
					cprintf("\n\r");
					ae=0; /**** Set new variable to 0 ****/
d437 5
a441 2
      cprintf("Logins must be between %d and %d characters.\n\r",
          min,max);
d444 5
a448 2
      cprintf("Passwords must be between %d and %d characters.\n\r",
          min,max);
d451 1
a451 1
      cprintf("Password not verified!\n\r");
d454 1
a454 1
      cprintf("That user already exists!\n\r");
d459 5
a463 3
			fprintf(npas,"%s\r\n",na);
			fprintf(npas,"%s\r\n",pa);
      sprintf(tol,"User %s Created.",na);
d470 10
a479 10
			fprintf(npas,"%s",DIV);
		}
		fcd(pass,npas);
		if (!err)
		{
			unlink(inam);
			rename(temp,inam);
		}
		else
			unlink(temp);
d493 1
a493 1
  x=view();
d496 1
a496 1
		crwin(2,7,60,17,tf,tb,2,"Delete A User");
d509 1
a509 1
    tmpnam(temp);
d529 1
a529 1
          cprintf("\n\rThis is a SuperUser!");
d532 3
a534 3
					cprintf("\n\r\n\rYou cannot delete this user, they are\n\r");
					cprintf("the last SuperUser!");
          cprintf("\n\r\n\rPress any key to return to the SuperUser menu...");
d540 3
a542 2
          cprintf("\n\r\n\rAre you sure you want to delete %s? ",
              na);
d553 3
a555 1
          sprintf(tol,"User %s Deleted.",na);
d560 1
a560 1
		fcd(pass,npas);
d578 1
a578 1
  v=view();
d581 1
a581 1
		crwin(2,5,69,22,tf,tb,2,"Toggle SuperUser Status");
d584 140
a723 134
		cprintf("\n\rNOTE: The user must re-enter their password to obtain or give up\n\r");
    cprintf("      SuperUser access.\n\r");
    cprintf("      You may override this by entering any other password, which\n\r");
    cprintf("      will be this user's password from now on.\n\r");
		opt=0;
		pass=ffwd(2,NULL);
		while((fgets(lo,MAX,pass))!=NULL)
		{
			fgets(ps,MAX,pass);
			if (ps[strlen(ps)-3]==STAMP)
				opt++;
			fgets(ti,MAX,pass);
		}
		fclose(pass);
		tmpnam(temp);
		if ((npas=fopen(temp,"wb"))==NULL)
			error("Error opening temp file!");
		pass=ffwd(2,npas);
		while((fgets(lo,MAX,pass))!=NULL)
		{
			strcpy(na,lo);
			chop2(na);
			y++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			if (y!=v)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
				sul=0;
				if ((opt==1) && (ps[strlen(ps)-3]==STAMP))
				{
					cprintf("\n\rYou cannot remove SuperUser access from the last SuperUser!");
					cprintf("\n\r\n\rPress any key to return to the SuperUser menu...");
					opt=blch();
					opt=0;
				}
				else
				{
					cprintf("\n\r\n\rAre you sure you want to ");
					if (ps[strlen(ps)-3]==STAMP)
						cprintf("remove SuperUser access from");
						else
					{
						cprintf("grant SuperUser access to");
						sul=1;
					}
					cprintf(" %s? ",na);
					opt=blch();
				}
				if ((opt=='y') || (opt=='Y'))
				{
					_bk=0;
					strcpy(pa,gin("\n\r\n\rPassword:",0));
					strncpy(pa,pa,max);
					if ((strlen(pa)>max) || (strlen(pa)<min))
					{
						cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
						cprintf("\n\rPress any key to continue...");
						opt=blch();
						err=2;
					}
					if (!err)
					{
						if (sul)
						{
							pa[strlen(pa)+1]=0;
							pa[strlen(pa)]=STAMP;
						}
						strcpy(pa,penc(pa));
						_bk=0;
						strcpy(na,gin("Verify Password:",0));
						strncpy(na,na,max);
						if (sul)
						{
							na[strlen(na)+1]=0;
							na[strlen(na)]=STAMP;
						}
						strcpy(na,penc(na));
						if (strcmp(pa,na))
						{
							cprintf("Password not verified!\n\r");
							cprintf("\n\rPress any key to continue...");
							opt=blch();
							err=3;
						}
						if (!sul)
						{
							na[strlen(na)+2]=0;
							na[strlen(na)+1]='\n';
							na[strlen(na)]='\r';
						}
						else
						{
							na[strlen(na)+3]=0;
							na[strlen(na)+2]='\n';
							na[strlen(na)+1]='\r';
							na[strlen(na)]=STAMP;
						}
						if (!err)
						{
							strcpy(ps,na);
							strcpy(tol,"SuperUser Access ");
							if (sul)
								strcat(tol,"Granted to");
							else
								strcat(tol,"Revoked from");
							strcat(tol," user ");
							strcpy(na,lo);
							chop2(na);
							strcat(tol,na);
							strcat(tol,".");
							tolog(tol);
						}
					}
					if (err)
					{
						ps[strlen(ps)+2]=0;
						ps[strlen(ps)+1]='\n';
						ps[strlen(ps)+1]='\r';
					}
				}
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
		}
		fcd(pass,npas);
		unlink(inam);
		rename(temp,inam);
d736 2
a737 2
	short int x;
	long zs;
d739 1
a739 1
  x=view();
d742 1
a742 1
		crwin(2,5,65,22,tf,tb,2,"Account Expiry");
d745 1
a745 1
    tmpnam(temp);
d748 61
a808 53
		pass=ffwd(2,npas);
		guser(x);
		strcpy(na,lo);
		chop2(na);
		if (ps[strlen(ps)-1]==STAMP)
			cprintf("\n\rThis is a SuperUser!\n\r");
		if (ed)
		{
			unixtodos(ed,&td,&nw);
			cprintf("\n\rCurrent expiry date is ");
			if (df)
				cprintf("%02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
			else
				cprintf("%02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
			getdate(&td);
			gettime(&nw);
			zs=dostounix(&td,&nw);
			if (zs>ed)
				cprintf("(This account has expired.)\n\r");
		}
		else
			cprintf("\n\rThis account has no expiry date.\n\r");
		cprintf("Do you want to change %s's expiry date? ",na);
		opt=blch();
		if ((opt!='y') && (opt!='Y'))
		{
			fputs(lo,npas);
			fputs(ps,npas);
			fputs(ti,npas);
		}
		else
		{
			ed=gdate();
			fputs(lo,npas);
			fputs(ps,npas);
			pwr;
			chop2(lo);
			if (ed)
			{
				unixtodos(ed,&td,&nw);
				sprintf(tol,"User %s account expiry changed to ",lo);
				if (df)
					sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
				else
					sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
				strcat(tol,lo);
				strcat(tol,".");
			}
			else
				sprintf(tol,"User %s account expiry removed.",lo);
			tolog(tol);
		}
		fcd(pass,npas);
d823 2
a824 2
	short int x;
	long zs;
d826 1
a826 1
  x=view();
d829 1
a829 1
		crwin(2,5,65,22,tf,tb,2,"Password Expiry");
d832 1
a832 1
    tmpnam(temp);
d835 53
a887 53
		pass=ffwd(2,npas);
		guser(x);
		strcpy(na,lo);
		chop2(na);
		if (ps[strlen(ps)-1]==STAMP)
			cprintf("\n\rThis is a SuperUser!\n\r");
		if (pe)
		{
			unixtodos(pe,&td,&nw);
			cprintf("\n\rCurrent expiry date is ");
			if (df)
				cprintf("%02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
			else
				cprintf("%02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
			getdate(&td);
			gettime(&nw);
			zs=dostounix(&td,&nw);
			if (zs>pe)
				cprintf("(This password has expired.)\n\r");
		}
		else
			cprintf("\n\rThis password has no expiry date.\n\r");
		cprintf("Do you want to change %s's expiry date? ",na);
		opt=blch();
		if ((opt!='y') && (opt!='Y'))
		{
			fputs(lo,npas);
			fputs(ps,npas);
			fputs(ti,npas);
		}
		else
		{
			pe=gdate();
			fputs(lo,npas);
			fputs(ps,npas);
			pwr;
			chop2(lo);
			if (pe)
			{
				unixtodos(pe,&td,&nw);
				sprintf(tol,"User %s password expiry changed to ",lo);
				if (df)
					sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
				else
					sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
				strcat(tol,lo);
				strcat(tol,".");
			}
			else
				sprintf(tol,"User %s password expiry removed.",lo);
			tolog(tol);
		}
		fcd(pass,npas);
d893 1
a893 1
void vlog(void)
d895 2
a896 2
	vlog is called when the user wishes to view the log file. They can
	purge the log after viewing if desired.
d899 8
a906 4
  short int x=0,c=0,vl;
  tolog("Log File Viewed.");
  fclose(log);
	crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
d908 27
d940 13
a952 3
  if ((log=fopen(ilog,"r"))==NULL)
    error("Error opening log file!");
  while((fgets(temp,MAX,log))!=NULL)
d954 4
a957 2
    x++;
    if (strlen(temp)>SCRWIDTH)
d959 12
a970 7
    cprintf("%s\r",temp);
    if (x>vl)
    {
      cprintf("\n\r  Press a key to continue...");
      c=blch();
      cprintf("\n\r");
      x=0;
a971 2
    if (c==27)
      break;
d973 1
a973 1
  fclose(log);
d976 1
a976 1
    cprintf("\n\r  Press a key to continue...");
d978 1
a978 1
    cprintf("\n\r");
d980 5
a984 1
  cprintf("\n\r Would you like to clear the log file [y/N]? ");
d988 39
a1026 1
    if ((log=fopen(ilog,"w"))==NULL)
d1028 7
a1034 3
    cprintf("\n\r\n\r The log file has been cleared.\n\r");
    tolog("Log File Cleared.");
    cprintf("\n\r  Press a key to continue...");
d1037 23
a1059 5
  else
  {
    if ((log=fopen(ilog,"a"))==NULL)
      error("Error in creating log file!");
  }
d1072 1
a1072 1
  x=view();
d1075 1
a1075 1
		crwin(2,5,65,22,tf,tb,2,"Account Lock Out");
d1078 1
a1078 1
    tmpnam(temp);
d1098 2
a1099 2
					cprintf("\n\rThis is a SuperUser!\n\r");
				prd();
d1101 4
a1104 4
					cprintf("\n\rThis account will currently lock up after %d invalid logins.\n\r",ntl);
				else
					cprintf("\n\rThis account has no limit on invalid logins.\n\r");
				cprintf("Do you want to change %s's invalid login setting? ",na);
d1118 3
a1120 3
            cprintf("\n\r\n\rEnter 'N' or '0' to assign unlimited invalid logins.");
            cprintf("\n\r\n\rEnter the number of sequential invalid logins before the");
            cprintf("\n\ruser's account is automatically expired");
d1122 1
a1122 1
						if ((streq(ho,"n")) || (streq(ho,"N")))
d1134 1
a1134 1
						sprintf(tol,"%s's invalid login setting is changed to %d.",lo,ntl);
d1141 1
a1141 1
		fcd(pass,npas);
d1157 1
a1157 1
	crwin(7,1,47,22,tf,tb,2,"Initialization Settings");
d1164 1
a1164 1
		cprintf("\n\r");
d1166 1
a1166 1
      cprintf("\n\r");
d1169 1
a1169 1
			gotoxy(30,2);
d1172 1
a1172 1
    cprintf("\n\r");
d1174 1
a1174 1
      cprintf("\n\r\n\r");
d1190 1
a1190 1
          cprintf("%s\n\r",txt[y]);
d1197 1
a1197 1
			gotoxy(30,20);
d1200 1
a1200 1
		gotoxy(1,20);
d1207 1
a1207 1
			crwin(7,1,47,22,tf,tb,2,"Initialization Settings");
d1266 20
a1285 1
int tv,qu;
d1291 3
a1293 3
	fclose(ini);
	strcpy(temp,is[set-2]);
	crwin(3,3,73,21,tf,tb,2,temp);
d1296 1
a1296 1
	cprintf("\n\r");
d1298 10
d1311 2
a1312 7
    cprintf("This contains the location of the log file. The log file\n\r");
    cprintf("should be kept somewhere safe, tucked away from prying eyes.\n\r");
		cprintf("NOTE: You should change the name of the file from %s.log to some\n\r",SENTRY);
    cprintf("other, inconspicuous name. Potential intruders will search for the\n\r");
		cprintf("%s.log file. You can hide it under misleading names such as\n\r",SENTRY);
    cprintf("file_id.diz, chklist.ms, warm.com etc etc.\n\r\n\r");
		cprintf("Default: c:\\%s.log",SENTRY);
d1315 13
a1327 21
	case 2:
		cprintf("This contains the location of the message file. The message\n\r");
		cprintf("file should be kept somewhere safe, tucked away from prying eyes.\n\r");
		cprintf("NOTE: You should change the name of the file from %s.msg to some\n\r",SENTRY);
    cprintf("other, inconspicuous name. Potential intruders will search for the\n\r");
		cprintf("%s.msg file. You can hide it under misleading names such as\n\r",SENTRY);
    cprintf("file_id.diz, chklist.ms, warm.com etc etc.\n\r\n\r");
		cprintf("Default: c:\\%s.msg",SENTRY);
    qu=1;
    break;
	case 3:
    cprintf("Sets the minimum length for passwords and logins.\n\r");
    cprintf("NOTE: A value of 4 should be the absolute minimum for\n\r");
    cprintf("MinPasswordLen. A value of 5 or 6 would be even better. Short\n\r");
    cprintf("passwords are much easier to stumble across since less attempts\n\r");
    cprintf("have to be made before it is guessed.\n\r\n\r");
    cprintf("Default: 4");
    break;
	case 4:
    cprintf("Sets the maximum length for passwords and logins.\n\r\n\r");
    cprintf("Default: 20");
d1329 1
a1329 20
	case 5:
    cprintf("Sets the maximum times a user can attempt to log in before being\n\r");
    cprintf("locked out.\n\r");
    cprintf("NOTE: This should not be set too high. It is very rare for a\n\r");
    cprintf("legitimate user to botch a login attempt 3 times in a row. A\n\r");
    cprintf("potential intruder will usually have to make many attempts before\n\r");
    cprintf("getting anywhere. Setting MaxTries to around 3 will slow him down\n\r");
    cprintf("greatly, as he will have to reset after 3 failed attempts.\n\r\n\r");
    cprintf("Default: 3");
    break;
	case 6:
    cprintf("Sets the delay in seconds to wait after the user fails to log in.\n\r");
    cprintf("NOTE: Setting the WaitTime to 3 or above greatly slows any\n\r");
    cprintf("methodical attempt to guess or discover passwords. It offers little\n\r");
    cprintf("inconvenience to the end users while providing added security.\n\r\n\r");
    cprintf("Default: 3");
    break;
	case 7:
    cprintf("Sets the \"key\" to enter as a password to change passwords.\n\r\n\r");
    cprintf("Default: passwd");
a1330 20
		break;
	case 8:
		cprintf("Sets the character to be echoed to the screen when the password\n\r");
		cprintf("is being entered.\n\r");
		cprintf("Enter '?' to display no character.\n\r");
		cprintf("Enter '!' to display the actual character (not recommended).\n\r\n\r");
		cprintf("Default: *");
		qu=4;
		break;
	case 9:
    cprintf("Sets the number of days a password is good before it expires.\n\r");
		cprintf("This is the default value used whenever a password is changed.\n\r");
		cprintf("Individual passwords can be set to expire on the SuperUser menu.\n\r");
		cprintf("NOTE: It is a good idea to have this set to between 180 and 365.\n\r");
		cprintf("Anything over a year is a security risk due to age.\n\r");
    cprintf("Anything under half a year is a risk because people will tend to\n\r");
    cprintf("forget their passwords and start writing them down. This setting\n\r");
		cprintf("should depend on how busy your system generally is.\n\r");
		cprintf("0 = Never expire passwords.\n\r\n\r");
    cprintf("Default: 365");
d1332 2
a1333 10
	case 10:
		cprintf("Sets the number of days an unused account is good before it expires.\n\r");
		cprintf("This is the default value used whenever an account is created.\n\r");
		cprintf("Individual accounts can be set to expire on the SuperUser menu.\n\r");
		cprintf("NOTE: This setting should depend on the level of activity on your\n\r");
		cprintf("system. Active systems can afford to have a lower setting than\n\r");
		cprintf("generally inactive settings. You should also take into consideration\n\r");
		cprintf("the probability of an intruder using an old account.\n\r");
		cprintf("0 = Never expire unused accounts.\n\r\n\r");
    cprintf("Default: 365");
d1335 14
a1348 4
	case 11:
    cprintf("This sets the amount of idle time (in seconds) that may pass before\n\r");
    cprintf("the screen saver is activated.\n\r\n\r");
    cprintf("Default: 300");
d1350 14
a1363 5
	case 12:
    cprintf("This is the message that is displayed randomly on the screen when\n\r");
    cprintf("the scren saver is active.\n\r\n\r");
    cprintf("Default: This is a Secure Terminal.");
    qu=2;
d1365 6
a1370 201
	case 13:
    cprintf("This sets the value of the prompt that is displayed when the user is\n\r");
    cprintf("expected to enter their login name. Modifying this allows you\n\r");
    cprintf("to customize your environment as you see fit.\n\r\n\r");
    cprintf("Default: Login:");
    qu=2;
    break;
	case 14:
    cprintf("This sets the value of the prompt that is displayed when the user is\n\r");
    cprintf("expected to enter their password. Modifying this allows you\n\r");
    cprintf("to customize your environment as you see fit.\n\r\n\r");
    cprintf("Default: Password:");
    qu=2;
    break;
	case 15:
    cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
    cprintf("password.\n\r");
    cprintf("NOTE: It is a good idea to keep the wrong password and wrong login\n\r");
    cprintf("messages the same. Otherwise, a potential intruder will know when he\n\r");
		cprintf("has foind an account (IE: If %s responds with \"Invalid\n\r",SENTRY);
    cprintf("Password\", he knows the login was correct). Keeping the two the same\n\r");
    cprintf("prevents an attacker from knowing if he even has the correct login.\n\r\n\r");
    cprintf("Default: Invalid Login.");
    qu=2;
    break;
	case 16:
    cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
    cprintf("login.\n\r");
    cprintf("NOTE: It is a good idea to keep the wrong password and wrong login\n\r");
    cprintf("messages the same. Otherwise, a potential intruder will know when he\n\r");
		cprintf("has foind an account (IE: If %s responds with \"Invalid\n\r",SENTRY);
    cprintf("Password\", he knows the login was correct). Keeping the two the same\n\r");
    cprintf("prevents an attacker from knowing if he even has the correct login.\n\r\n\r");
    cprintf("Default: Invalid Login.");
    qu=2;
    break;
	case 17:
    cprintf("This sets the message to be displayed when a user enters a password\n\r");
    cprintf("of invalid length.\n\r");
    cprintf("NOTE: It is wise to keep the wrong password length, wrong login\n\r");
    cprintf("length, wrong password and wrong login messages the same. This will\n\r");
    cprintf("prevent a potential attacker from knowing the max and min settings\n\r");
    cprintf("for passwords or logins on your system. (Knowing the length of a\n\r");
    cprintf("password can greatly decrease the amount of time required to\n\r");
    cprintf("crack it).\n\r\n\r");
    cprintf("Default: Invalid Login.");
    qu=2;
    break;
	case 18:
    cprintf("This sets the message to be displayed when a user enters a login of\n\r");
    cprintf("invalid length.\n\r\n\r");
    cprintf("NOTE: It is wise to keep the wrong password length, wrong login\n\r");
    cprintf("length, wrong password and wrong login messages the same. This will\n\r");
    cprintf("prevent a potential attacker from knowing the max and min settings\n\r");
    cprintf("for passwords or logins on your system. (Knowing the length of a\n\r");
    cprintf("password can greatly decrease the amount of time required to\n\r");
    cprintf("crack it).\n\r\n\r");
    cprintf("Default: Invalid Login.");
    qu=2;
    break;
	case 19:
    cprintf("This sets the message to be saved to the log file when a user enters\n\r");
    cprintf("the wrong password.\n\r\n\r");
    cprintf("Default: User entered the wrong password.");
    qu=2;
    break;
	case 20:
    cprintf("This sets the message to be saved to the log file when a user enters\n\r");
    cprintf("the wrong login.\n\r");
    cprintf("NOTE: This message should be descriptive, since the SuperUser will\n\r");
    cprintf("use it to determine what sort of activities have been happening.\n\r\n\r");
    cprintf("Default: User entered the wrong login.");
    qu=2;
    break;
	case 21:
    cprintf("This sets the message to be saved to the log file when a user enters\n\r");
    cprintf("a password of invalid length.\n\r\n\r");
    cprintf("Default: Invalid Password Length.");
    qu=2;
    break;
	case 22:
    cprintf("This sets the message to be saved to the log file when a user enters\n\r");
    cprintf("a login of invalid length.\n\r\n\r");
    cprintf("Default: Invalid Login Length.");
    qu=2;
    break;
	case 23:
    cprintf("This sets the environment variable used to store the user's login\n\r");
    cprintf("name after a successful login.\n\r");
    cprintf("NOTE: The environment variable USER is used by many networks, such\n\r");
		cprintf("Novell. By using this setting, %s can be used in conjunction\n\r",SENTRY);
    cprintf("with these networks.\n\r\n\r");
    cprintf("Default: USER");
    qu=2;
    break;
	case 24:
		cprintf("The Windows flag is set if you wish to run %s from Windows.\n\r",SENTRY);
		cprintf("Technically, this allows %s to open up a DOS shell after a\n\r",SENTRY);
    cprintf("successful login. Setting this option to 1 has no effect on normal\n\r");
    cprintf("use, and is not a security risk.\n\r");
    cprintf("(0=Do Not Run In Windows, 1=Run In Windows)\n\r\n\r");
    cprintf("Default: 1");
    break;
	case 25:
    cprintf("This determines if the intro screen is displayed or not. You may\n\r");
    cprintf("choose not to display the title information if you don't want users\n\r");
    cprintf("to know what program you are using. On the other hand, the\n\r");
    cprintf("registration information sould be displayed for authenticity's\n\r");
    cprintf("sake. I have added this option because security comes before all\n\r");
    cprintf("else.\n\r");
    cprintf("(0=Not Displayed, 1=Displayed)\n\r\n\r");
    cprintf("Default: 1");
    break;
	case 26:
    cprintf("This will allow you to have dates displayed in different formats.\n\r");
    cprintf("Some people prefer different formats than others, so this will allow\n\r");
    cprintf("you to define the way dates are displayed.\n\r");
    cprintf("(0=MM/DD/YYYY, 1=DD/MM/YYYY)\n\r\n\r");
    cprintf("Default: 1");
    break;
	case 27:
		cprintf("This sets the case sensitivity. If \"Case Insensitive\" is selected,\n\r");
		strcpy(temp,SENTRY);
		cprintf("\"%s\" \"",strupr(temp));
		strcpy(temp,SENTRY);
		cprintf("%s\" and \"%s\" are all treated as the same at\n\r",strlwr(temp),SENTRY);
    cprintf("the login prompt. If case sensitivity is enabled, the three are all\n\r");
    cprintf("treated as different logins.\n\r");
    cprintf("(0=Case Sensitive, 1=Case Insensitive)\n\r");
    cprintf("NOTE: Using \"Case Insensitive\" reduces the number of allowable\n\r");
    cprintf("logins, and increases the probability of an attacker getting a\n\r");
    cprintf("correct login. Still, some people find it easier to work with Case\n\r");
    cprintf("Sensitivity off.\n\r");
    cprintf("Default: 0");
    break;
	case 28:
		cprintf("This allows you to use %s in a \"windowed\" mode (not to be\n\r",SENTRY);
    cprintf("confused with MicroSoft Windows). If the windowed mode is\n\r");
    cprintf("undesirable, you can choose not to use it.\n\r");
    cprintf("(0=Regular Mode, 1=Normal Windowed Mode, 2=Exploding Windowed Mode)\n\r\n\r");
    cprintf("Default: 2");
    break;
	case 29:
		cprintf("This determines if colour will be displayed by %s or not. Some\n\r",SENTRY);
    cprintf("laptop users may wish to use the black and white setting for better\n\r");
    cprintf("readability.\n\r");
    cprintf("(0=Black and White, 1=Colour)\n\r\n\r");
    cprintf("Default: 1");
    break;
	case 30:
    cprintf("You can set TextColour to the value of the colour you wish normal\n\r");
    cprintf("text to appear in. Colour values are shown in the chart below.\n\r\n\r");
    cprintf("COLOURS:\n\r");
    cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
    cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
    cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
    cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
    cprintf("Default: 15");
    break;
	case 31:
    cprintf("You can set TextBackground to the value of the colour you wish\n\r");
    cprintf("normal text to have as a background. Colour values are shown in the\n\r");
    cprintf("chart below.\n\r\n\r");
    cprintf("COLOURS:\n\r");
    cprintf("0 Black 4 Red\n\r");
    cprintf("1 Blue  5 Magenta\n\r");
    cprintf("2 Green 6 Brown\n\r");
    cprintf("3 Cyan  7 Light Gray\n\r\n\r");
    cprintf("Default: 1");
    break;
	case 32:
    cprintf("You can set HighColour to the value of the colour you wish\n\r");
    cprintf("highlighted text to appear in. Colour values are shown in the\n\r");
    cprintf("chart below.\n\r\n\r");
    cprintf("COLOURS:\n\r");
    cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
    cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
    cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
    cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
    cprintf("Default: 1");
    break;
	case 33:
    cprintf("You can set HighBackground to the value of the colour you wish\n\r");
    cprintf("highlighted text to have as a background. Colour values are shown\n\r");
    cprintf("in the chart below.\n\r\n\r");
    cprintf("COLOURS:\n\r");
    cprintf("0 Black 4 Red\n\r");
    cprintf("1 Blue  5 Magenta\n\r");
    cprintf("2 Green 6 Brown\n\r");
    cprintf("3 Cyan  7 Light Gray\n\r\n\r");
    cprintf("Default: 7");
    break;
	case 34:
    cprintf("This sets the default number of consecutive invalid logins possible\n\r");
    cprintf("before an account is locked out. Only a SuperUser can subsequently\n\r");
    cprintf("unlock an account.\n\r\n\r");
    cprintf("Default: 10");
    break;
  default:
    cprintf("No information available.");
    break;
d1372 2
a1373 1
  cprintf("\n\r\n\rCurrent Value: %s\n\r\n\r",cv);
d1390 1
a1390 1
        cprintf("\n\rPlease enter a numeric value.\n\r\n\rPress any key to try again...\n\r");
d1395 1
a1395 13
		case 1:  /*Path*/
			if ((ini=fopen(cv,"r"))==NULL)
			{
				fclose(ini);
				if ((ini=fopen(cv,"a"))==NULL)
				{
					cprintf("\n\rPlease enter a valid path.\n\r\n\rPress any key to try again...\n\r");
					bk=blch();
				}
				unlink(cv);
			}
      fclose(ini);
      break;
d1401 8
a1408 1
        cprintf("\n\rPlease enter a single word. (No spaces)\n\r\n\rPress any key to try again...\n\r");
d1411 1
a1411 8
			break;
		case 4:
			if (strlen(cv)>1)
			{
				cprintf("\n\rPlease enter a single character only.\n\r\n\rPress any key to try again...\n\r");
				bk=blch();
			}
			break;
d1416 1
a1416 1
    tmpnam(temp);
d1444 4
a1447 4
	x=view();
	if (x)
	{
		crwin(2,7,70,17,tf,tb,2,"Send A Message");
d1450 1
a1450 1
		pass=ffwd(2,NULL);
d1456 1
a1456 1
			if (y==x)
d1458 12
a1469 8
				strcpy(pa,gin("\n\rMessage:\n\r>",1));
				if ((msg=fopen(imsg,"a"))==NULL)
					error("Error Opening Message File.");
				chop2(lo);
				lo[strlen(lo)+1]=0;
				lo[strlen(lo)]='\n';
				fputs(lo,msg);
				sprintf(tol,"%s\n",cp);
d1471 13
a1483 14
				getdate(&td);
				gettime(&nw);
				sprintf(tol,"%lu\n",dostounix(&td,&nw));
				fputs(tol,msg);
				pa[strlen(pa)+1]=0;
				pa[strlen(pa)]='\n';
				fputs(pa,msg);
				chop(lo);
				sprintf(tol,"%s sent a message to %s.",cp,lo);
				tolog(tol);
			}
		}
		fclose(msg);
	}
d1490 97
a1586 77
	crwin(2,7,70,17,tf,tb,2,"Protect File");
	if (!wm)
		clrscr();
	x=1;
	while (x)
	{
		x=0;
		_bk=1;
		bk=0;
		strcpy(cv,gin("\n\rEnter File to Protect:",1));
		if (bk)
			x=0;
		else
		{
			y=fnsplit(cv,dr,di,fi,ex);
			strupr(ex);
			if (!streq(ex,".EXE") && !streq(ex,".COM") && !streq(ex,".BAT"))
			{
				cprintf("\n\rFile must have EXE, COM or BAT extension.\n\r\n\r");
				x=1;
			}
			else
				if ((npas=fopen(cv,"r"))==NULL)
				{
					cprintf("\n\rPlease enter a valid path.\n\r\n\r");
					x=1;
				}
			fclose(npas);
		}
	}
	if (!bk)
	{
		tmpnam(temp);
		if (y & DIRECTORY)
		{
			strcpy(tol,temp);
			strcpy(temp,di);
			strcat(temp,tol);
		}
		if (y & DRIVE)
		{
			strcpy(tol,temp);
			strcpy(temp,dr);
			strcat(temp,tol);
		}
		if ((npas=fopen(temp,"wb"))==NULL)
			error("Error opening temp file!");
		pass=ffwd(1,npas);
		if ((fgets(lo,MAX,pass))==NULL)
			error("Error in Initialization Settings!");
		chop2(lo);
		lo[strlen(lo)+1]=0;
		lo[strlen(lo)]='Z';
		fprintf(npas,"%s\r\n",lo);
		fprintf(npas,"%s\r\n",ex);
		ze=random(256);
		fprintf(npas,"%d\r\n",ze);
		fcd(pass,npas);
		if ((pass=fopen(cv,"rb"))==NULL)
			error("Error opening protected file!");
		if ((npas=fopen(temp,"ab"))==NULL)
			error("Error opening temp file!");
		zze=1;
		fcd(pass,npas);
		zze=0;
		unlink(cv);
		sprintf(tol,"File Protected: %s",cv);
		tolog(tol);
		if (streq(ex,".BAT"))
		{
			cv[strlen(cv)-1]='E';
			cv[strlen(cv)-2]='X';
			cv[strlen(cv)-3]='E';
			unlink(cv);
		}
		rename(temp,cv);
	}
d1591 18
a1608 18
	crwin(2,7,70,17,tf,tb,2,"Export Initialization Settings");
	if (!wm)
		clrscr();
	if (zm)
		cprintf("\n\rCannot dump the Initialization Settings\n\rof a Protected File!");
	else
	{
		if ((npas=fopen("settings.","wb"))==NULL)
			error("Error opening temp file!");
		pass=ffwd(1,NULL);
		fcd(pass,npas);
		_chmod("settings.",1,FA_HIDDEN);
		cprintf("\n\rInitialization Settings Exported...\n\r");
		cprintf("\n\rThe next time INSTALL.EXE is run, it will\n\r");
		cprintf("pick up and use these settings.");
	}
	cprintf("\n\r\n\rPress any key to return to the SuperUser menu...");
	blch();
d1613 4
a1616 5
  suinit(void) initializes the menu options in the string txt[]. This is

  done seperately from the super(void) function so that it can be
  performed as required. view(void) also uses the txt[] variable, so
  suinit(void) must be called after each call to view(void).
d1619 10
a1628 15
	strcpy(txt[1],"1. Create User");
	strcpy(txt[2],"2. Delete User");
	strcpy(txt[3],"3. View All Users");
	strcpy(txt[4],"4. Toggle SuperUser Status");
	strcpy(txt[5],"5. Change Account Expiry Date");
	strcpy(txt[6],"6. Change Password Expiry Date");
	strcpy(txt[7],"7. View Log File");
	strcpy(txt[8],"8. Change Account Password");
	strcpy(txt[9],"9. Assign Max Number of Invalid Logins");
	strcpy(txt[10],"10. Edit Initialization Settings");
	strcpy(txt[11],"11. Send a Message to a User");
	strcpy(txt[12],"12. Protect a File");
	strcpy(txt[13],"13. Export Initialization Settings");
	strcpy(txt[SUOPT],"14. Exit");
	crwin(10,4,52,23,tf,tb,2,"SuperUser Menu");
d1634 4
a1637 4
	invoke the SuperUser menu (CTRL-enter on login). super() allows the
	user to select an option in much the same way as view() except they can
	also select by option number. Control of the program is subsequently
	passed to the appropriate function.
a1641 2
  cprintf("\n\r   Press any key to continue...\n\r");
  opt=blch();
d1643 2
a1644 3
	y=opt=0;
	strcpy(temp,"");
	while (1) /**** This is iffy (but it works) ****/
d1649 1
a1649 1
		cprintf("\n\r");
d1662 2
a1663 1
      cprintf("%s\n\r",txt[x]);
d1667 7
a1673 18
    cprintf("\n\rOption: ");
		opt=blch();
		if (isdigit(opt))
		{
			temp[strlen(temp)+1]=0;
			temp[strlen(temp)]=opt;
			x=atoi(temp);
			if ((x<=SUOPT) && (x>0))
			{
				sel=x;
				if (x>9)
					strcpy(temp,"");
			}
			else
				strcpy(temp,"");
		}
		else
			strcpy(temp,"");
d1676 31
a1706 33
		case 'c':
			sel=1;
			break;
		case 'd':
			sel=2;
			break;
		case 'v':
			sel=3;
			break;
		case 't':
			sel=4;
			break;
		case 'l':
			sel=7;
			break;
		case 'i':
			sel=10;
			break;
		case 'm':
			sel=11;
			break;
		case 'p':
			sel=12;
			break;
		case 'e':
			sel=13;
			break;
		case 27:  /* Escape */
			opt='\n';
		case 'x':
			sel=SUOPT;
			break;
		case 77:   /* Cursor Right/Down */
d1711 1
a1711 1
		case 75:    /* Cursor Up/Left */
d1716 1
a1716 1
		case 73:  /* Page Up */
d1719 1
a1719 1
		case 81:   /* Page Down */
d1721 164
a1884 3
			break;
		case 13:
			strcpy(temp,"");
d1887 94
a1980 66
			case 1:
				cru();
				y=1;
				break;
			case 2:
				del();
				y=1;
				break;
			case 3:
				tolog("User List Viewed.");
				view();
				y=1;
				break;
			case 4:
				toggle();
				y=1;
				break;
			case 5:
				cex();
				y=1;
				break;
			case 6:
				pex();
				y=1;
				break;
			case 7:
				vlog();
				y=1;
				break;
			case 8:
				un=view()*-1;
				if (un)
				{
					crwin(2,5,65,22,tf,tb,2,"Change Password");
					if (!wm)
						clrscr();
					setp();
				}
				y=1;
				break;
			case 9:
				alock();
				y=1;
				break;
			case 10:
				iset();
				y=1;
				break;
			case 11:
				smsg();
				y=1;
				break;
			case 12:
				prf();
				y=1;
				break;
			case 13:
				idmp();
				y=1;
				break;
			case SUOPT:
				su=sul=1;
				if (!puttext(1,1,80,25,msc))
					error("Internal Screen Error. [Writing]");
				fin(0);
				break;
d1982 48
d2032 20
d2053 1
a2053 1
      suinit();
@


3.2
log
@Mini-mail system.
@
text
@d1 4
d93 2
a94 2
  crwin(1,1,79,24,tf,tb,1);
  while((fgets(lo,MAX,pass))!=NULL)
d323 1
a323 1
  crwin(2,5,65,22,tf,tb,2);
d350 8
a357 3
      fclose(npas);
      if ((npas=fopen(inam,"a"))==NULL)
        error("Error Reading Data Segment! [Append]");
d362 4
a365 1
        break;
d380 4
a383 1
          break;
d441 2
a442 2
      fprintf(npas,"%s\n",na);
      fprintf(npas,"%s\n",pa);
d450 10
a459 2
    }
    fclose(npas);
d476 1
a476 1
    crwin(2,7,60,17,tf,tb,2);
d512 2
a513 1
          cprintf("\n\rYou cannot delete this user, they are the last SuperUser!");
d537 1
a537 1
    fcd(pass,npas);
d558 1
a558 1
    crwin(2,5,69,22,tf,tb,2);
d561 1
a561 1
    cprintf("NOTE: The user must re-enter their password to obtain or give up\n\r");
d565 130
a694 159
    cprintf("\n\r\n\rIS THIS OK? ");
    opt=blch();
    if ((opt=='y') || (opt=='Y'))
    {
      opt=0;
      pass=ffwd(2,NULL);
      while((fgets(lo,MAX,pass))!=NULL)
      {
        fgets(ps,MAX,pass);
        if (ps[strlen(ps)-3]==STAMP)
          opt++;
        fgets(ti,MAX,pass);
      }
      fclose(pass);
      tmpnam(temp);
      if ((npas=fopen(temp,"wb"))==NULL)
        error("Error opening temp file!");
      pass=ffwd(2,npas);
      while((fgets(lo,MAX,pass))!=NULL)
      {
        strcpy(na,lo);
        chop2(na);
        y++;
        fgets(ps,MAX,pass);
        fgets(ti,MAX,pass);
        if (y!=v)
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          sul=0;
          if ((opt==1) && (ps[strlen(ps)-3]==STAMP))
          {
            cprintf("\n\rYou cannot remove SuperUser access from the last SuperUser!");
            cprintf("\n\r\n\rPress any key to return to the SuperUser menu...");
            opt=blch();
            opt=0;
          }
          else
          {
            cprintf("\n\r\n\rAre you sure you want to ");
            if (ps[strlen(ps)-3]==STAMP)
              cprintf("remove SuperUser access from");
              else
            {
              cprintf("grant SuperUser access to");
              sul=1;
            }
            cprintf(" %s? ",na);
            opt=blch();
          }
          if ((opt=='y') || (opt=='Y'))
          {
            _bk=0;
						strcpy(pa,gin("\n\r\n\rPassword:",0));
						strncpy(pa,pa,max);
            if ((strlen(pa)>max) || (strlen(pa)<
                min))
            {
              cprintf("Passwords must be between %d and %d characters.\n\r",
                  min,max);
              cprintf("\n\rPress any key to continue...");
              opt=blch();
              err=2;
            }
            if (!err)
            {
              if (sul)
              {
                pa[strlen(pa)+1]=
                    0;
                pa[strlen(pa)]=
                    STAMP;
              }
              strcpy(pa,penc(pa));
              _bk=0;
							strcpy(na,gin("Verify Password:",0));
							strncpy(na,na,max);
              if (sul)
              {
                na[strlen(na)+1]=
                    0;
                na[strlen(na)]=
                    STAMP;
              }
              strcpy(na,penc(na));
              if (strcmp(pa,na))
              {
                cprintf("Password not verified!\n\r");
                cprintf("\n\rPress any key to continue...");
                opt=blch();
                err=3;
              }
              if (!sul)
              {
                na[strlen(na)+2]=
                    0;
                na[strlen(na)+1]=
                    '\n';
                na[strlen(na)]=
                    '\r';
              }
              else
              {
                na[strlen(na)+3]=
                    0;
                na[strlen(na)+2]=
                    '\n';
                na[strlen(na)+1]=
                    '\r';
                na[strlen(na)]=
                    STAMP;
              }
              if (!err)
              {
                strcpy(ps,
                    na);
                strcpy(tol,
                    "SuperUser Access ");
                if (sul)
/* code folded from here */
  strcat(tol,
      "Granted to");
  else
  strcat(tol,"Revoked from");
/* unfolding */
                strcat(tol," user ");
                strcpy(na,
                    lo);
                chop2(na);
                strcat(tol,
                    na);
                strcat(tol,
                    ".");
                tolog(tol);
              }
            }
            if (err)
            {
              ps[strlen(ps)+2]=
                  0;
              ps[strlen(ps)+1]=
                  '\n';
              ps[strlen(ps)+1]=
                  '\r';
            }
          }
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
      }
      fcd(pass,npas);
      unlink(inam);
      rename(temp,inam);
    }
d707 1
a707 1
  short int x,y=0;
d713 1
a713 1
    crwin(2,5,65,22,tf,tb,2);
d719 53
a771 76
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      chop2(na);
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-1]==STAMP)
					cprintf("\n\rThis is a SuperUser!\n\r");
				prd();
        if (ed)
        {
          unixtodos(ed,&td,&nw);
          if (df)
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",
                td.da_day,td.da_mon,td.da_year);
            else
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",
                td.da_mon,td.da_day,td.da_year);
          getdate(&td);
          gettime(&nw);
          zs=dostounix(&td,&nw);
          if (zs>ed)
            cprintf("(This account has expired.)\n\r");
        }
        else
          cprintf("This account has no expiry date.\n\r");
        cprintf("Do you want to change %s's expiry date? ",
            na);
        opt=blch();
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          ed=gdate();
          fputs(lo,npas);
          fputs(ps,npas);
          pwr;
          chop2(lo);
          if (ed)
          {
            unixtodos(ed,&td,&nw);
            sprintf(tol,"User %s account expiry changed to ",
                lo);
            if (df)
              sprintf(lo,"%02d/%02d/%02d",
                  td.da_day,td.da_mon,
                  td.da_year);
              else
              sprintf(lo,"%02d/%02d/%02d",
                  td.da_mon,td.da_day,
                  td.da_year);
            strcat(tol,lo);
            strcat(tol,".");
          }
          else
            sprintf(tol,"User %s account expiry removed.",
                lo);
          tolog(tol);
        }
      }
    }
    fcd(pass,npas);
d786 1
a786 1
  short int x,y=0;
d792 1
a792 1
    crwin(2,5,65,22,tf,tb,2);
d798 53
a850 76
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      chop2(na);
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-1]==STAMP)
					cprintf("\n\rThis is a SuperUser!\n\r");
				prd();
        if (pe)
        {
          unixtodos(pe,&td,&nw);
          if (df)
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",
                td.da_day,td.da_mon,td.da_year);
            else
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",
                td.da_mon,td.da_day,td.da_year);
          getdate(&td);
          gettime(&nw);
          zs=dostounix(&td,&nw);
          if (zs>pe)
            cprintf("(This password has expired.)\n\r");
        }
        else
          cprintf("This password has no expiry date.\n\r");
        cprintf("Do you want to change %s's expiry date? ",
            na);
        opt=blch();
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          pe=gdate();
          fputs(lo,npas);
          fputs(ps,npas);
          pwr;
          chop2(lo);
          if (pe)
          {
            unixtodos(pe,&td,&nw);
            sprintf(tol,"User %s password expiry changed to ",
                lo);
            if (df)
              sprintf(lo,"%02d/%02d/%02d",
                  td.da_day,td.da_mon,
                  td.da_year);
              else
              sprintf(lo,"%02d/%02d/%02d",
                  td.da_mon,td.da_day,
                  td.da_year);
            strcat(tol,lo);
            strcat(tol,".");
          }
          else
            sprintf(tol,"User %s password expiry removed.",
                lo);
          tolog(tol);
        }
      }
    }
    fcd(pass,npas);
d858 2
a859 3
  vlog is called when the user wishes to view the log file. They can purg
e
  the log after viewing if desired.
d865 1
a865 1
  crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2);
a917 1

d928 1
a928 1
    crwin(2,5,65,22,tf,tb,2);
d954 4
a957 5
					cprintf("This account will currently lock up after %d invalid logins.\n\r",ntl);
          else
          cprintf("This account has no limit on invalid logins.\n\r");
        cprintf("Do you want to change %s's invalid login setting? ",
            na);
d994 1
a994 1
    fcd(pass,npas);
d1006 2
a1007 2
  short int x,y,sel=1,tp=0;
  char opt=0;
d1010 1
a1010 1
  crwin(7,1,47,24,tf,tb,2);
d1017 1
a1017 1
    cprintf("Current Settings (ESC exits)\n\r\n\r");
d1022 1
a1022 1
      gotoxy(30,2);
d1050 1
a1050 1
      gotoxy(30,21);
d1053 1
a1053 1
    gotoxy(1,22);
d1060 1
a1060 1
      crwin(7,1,47,24,tf,tb,1);
d1118 2
a1119 2
  char cv[100];
  int tv,qu;
d1125 3
a1127 2
  fclose(ini);
  crwin(3,2,73,22,tf,tb,2);
d1130 1
a1130 1
  cprintf("%s\n\r\n\r",is[set-2]);
d1137 1
a1137 1
    cprintf("NOTE: You should change the name of the file from Sentry.log to some\n\r");
d1139 1
a1139 1
    cprintf("Sentry.log file. You can hide it under misleading names such as\n\r");
d1141 1
a1141 1
    cprintf("Default: c:\\Sentry.log");
d1147 1
a1147 1
		cprintf("NOTE: You should change the name of the file from Sentry.msg to some\n\r");
d1149 1
a1149 1
		cprintf("Sentry.msg file. You can hide it under misleading names such as\n\r");
d1151 1
a1151 1
		cprintf("Default: c:\\Sentry.msg");
d1249 1
a1249 1
    cprintf("has foind an account (IE: If Sentry responds with \"Invalid\n\r");
d1260 1
a1260 1
    cprintf("has foind an account (IE: If Sentry responds with \"Invalid\n\r");
d1320 1
a1320 1
    cprintf("Novell. By using this setting, Sentry can be used in conjunction\n\r");
d1326 2
a1327 2
    cprintf("The Windows flag is set if you wish to run Sentry from Windows.\n\r");
    cprintf("Technically, this allows Sentry to open up a DOS shell after a\n\r");
d1351 5
a1355 2
    cprintf("This sets the case sensitivity. If \"Case Insensitive\" is selected,\n\r");
		cprintf("\"SENTRY\" \"sentry\" and \"Sentry\" are all treated as the same at\n\r");
d1366 1
a1366 1
    cprintf("This allows you to use Sentry in a \"windowed\" mode (not to be\n\r");
d1373 1
a1373 1
    cprintf("This determines if colour will be displayed by Sentry or not. Some\n\r");
d1518 1
a1518 1
		crwin(2,7,70,17,tf,tb,2);
d1532 3
d1536 1
a1536 1
				sprintf(tol,"%s\n\r",cp);
d1540 1
a1540 1
				sprintf(tol,"%lu\n\r",dostounix(&td,&nw));
d1545 3
d1554 105
d1668 15
a1682 13
  strcpy(txt[1],"1. Create User");
  strcpy(txt[2],"2. Delete User");
  strcpy(txt[3],"3. View All Users");
  strcpy(txt[4],"4. Toggle SuperUser Status");
  strcpy(txt[5],"5. Change Account Expiry Date");
  strcpy(txt[6],"6. Change Password Expiry Date");
  strcpy(txt[7],"7. View Log File");
  strcpy(txt[8],"8. Change Account Password");
  strcpy(txt[9],"9. Assign Max Number of Invalid Logins");
	strcpy(txt[10],"0. Edit Initialization Settings");
	strcpy(txt[11],"M. Send a Message to a User");
	strcpy(txt[12],"X. Exit");
	crwin(11,5,52,22,tf,tb,2);
d1688 4
a1691 6
  invoke the SuperUser menu (CTRL-enter on login). super() allows the use
r
  to select an option in much the same way as view() except they can also
  select by option number. Control of the program is subsequently passed

  to the appropriate function.
d1699 3
a1701 2
  y=opt=0;
  while ((opt > '0') || (opt < '1')) /* Change SUOPT here */
d1706 1
a1706 1
    cprintf("   SuperUser Menu\n\r\n\r");
d1724 17
a1740 1
    opt=blch();
d1743 33
a1775 64
    case 13:
      switch (sel)
      {
      case 1:
        cru();
        y=1;
        break;
      case 2:
        del();
        y=1;
        break;
      case 3:
        tolog("User List Viewed.");
        view();
        y=1;
        break;
      case 4:
        toggle();
        y=1;
        break;
      case 5:
        cex();
        y=1;
        break;
      case 6:
        pex();
        y=1;
        break;
      case 7:
        vlog();
        y=1;
        break;
      case 8:
        un=view()*-1;
        if (un)
        {
          crwin(2,5,65,22,tf,tb,2);
          if (!wm)
            clrscr();
          setp();
        }
        y=1;
        break;
      case 9:
        alock();
        y=1;
        break;
      case 10:
        iset();
        y=1;
				break;
			case 11:
				smsg();
				y=1;
				break;
      case SUOPT:
        su=sul=1;
        if (!puttext(1,1,80,25,msc))
          error("Internal Screen Error. [Writing]");
        fin(0);
        break;
      }
      break;
    case 77:
d1780 1
a1780 1
    case 75:
d1785 1
a1785 49
    case '1':
      cru();
      y=1;
      break;
    case '2':
      del();
      y=1;
      break;
    case '3':
      tolog("User List Viewed.");
      view();
      y=1;
      break;
    case '4':
      toggle();
      y=1;
      break;
    case '5':
      cex();
      y=1;
      break;
    case '6':
      pex();
      y=1;
      break;
    case '7':
      vlog();
      y=1;
      break;
    case '8':
      un=view()*-1;
      if (un)
      {
        crwin(2,5,65,22,tf,tb,2);
        if (!wm)
          clrscr();
        setp();
      }
      y=1;
      break;
    case '9':
      alock();
      y=1;
      break;
    case '0':
      iset();
      y=1;
      break;
    case 73:
d1788 1
a1788 1
    case 81:
d1791 71
a1861 11
		case 'm':
			smsg();
			y=1;
			break;
    case 'x':
    case 'X':
    case 27:
      su=sul=1;
      if (!puttext(1,1,80,25,msc))
        error("Internal Screen Error. [Writing]");
      fin(0);
@


3.1
log
@Password echo char & log DOS shell.
@
text
@d13 2
a14 1
    strcpy(pa,gin("\n\rOld Password:",0));
a85 1
  long ut,ed,pe;
d102 2
a103 12
      }
      if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,
          &ntl)!=5)
      {
        if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
          error("Error in time stamps.");
          else
        {
          fla=0;
          ntl=ltl;
        }
      }
d174 1
a174 1
    cprintf("Current Users (ESC exits)\n\r\n\r");
d177 22
d207 1
a207 1
    strcat(lo,"Acct Expiry");
d211 1
a211 1
    strcat(lo,"Passwd Exp");
d215 1
a215 1
    strcat(lo,"Inv Log");
d219 1
a219 1
    strcat(lo,"Max InvLog");
d223 3
a225 3
    if (tp>0)
    {
      gotoxy(NLST+4,2);
d230 1
a230 1
      cprintf("\n\r\n\r");
a312 1

a316 1
  long ut,ed,pe;
d327 2
a328 1
    strcpy(na,gin("Login:",1));
d334 2
a335 2
    pass=ffwd(2,NULL);
    while((fgets(lo,MAX,pass))!=NULL)
d337 2
a338 2
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
d346 2
a347 2
      fclose(pass);
      if ((pass=fopen(inam,"a"))==NULL)
d351 2
a352 1
      if (bk)
d366 2
a367 1
        if (bk)
d388 1
a388 1
            else
d394 1
a394 1
            else
d396 8
a403 1
          cprintf("\n\r");
d426 2
a427 2
      fprintf(pass,"%s\n",na);
      fprintf(pass,"%s\n",pa);
d434 1
a434 2
      ntl=ltl;
      fprintf(pass,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
d436 1
a436 1
    fclose(pass);
d598 2
a599 2
            strcpy(pa,gin("\n\r\n\rPassword:",
                0));
d620 2
a621 2
              strcpy(na,gin("Verify Password:",
                  0));
d713 1
a713 1
  long ut,ed,zs,pe;
d741 2
a742 13
          cprintf("\n\rThis is a SuperUser!\n\r");
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,
            &pe,&fla,&ntl)!=5)
        {
          if (sscanf(ti,"%lu %lu %lu",&ut,&
              ed,&pe)!=3)
            error("Error in time stamps.");
            else
          {
            fla=0;
            ntl=ltl;
          }
        }
d774 1
a774 2
          fprintf(npas,"%lu %lu %lu %d %d\n",
              ut,ed,pe,fla,ntl);
d815 1
a815 1
  long ut,ed,zs,pe;
d843 2
a844 13
          cprintf("\n\rThis is a SuperUser!\n\r");
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,
            &pe,&fla,&ntl)!=5)
        {
          if (sscanf(ti,"%lu %lu %lu",&ut,&
              ed,&pe)!=3)
            error("Error in time stamps.");
            else
          {
            fla=0;
            ntl=ltl;
          }
        }
d876 1
a876 2
          fprintf(npas,"%lu %lu %lu %d %d\n",
              ut,ed,pe,fla,ntl);
a976 1
  long ut,ed,pe;
d1004 2
a1005 13
          cprintf("\n\rThis is a SuperUser!\n\r");
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,
            &pe,&fla,&ntl)!=5)
        {
          if (sscanf(ti,"%lu %lu %lu",&ut,&
              ed,&pe)!=3)
            error("Error in time stamps.");
            else
          {
            fla=0;
            ntl=ltl;
          }
        }
d1007 1
a1007 2
          cprintf("This account will currently lock up after %d invalid logins.\n\r",
              ntl);
d1029 1
a1029 2
            if ((streq(ho,"n")) || (streq(ho,
                "N")))
d1038 1
a1038 2
          fprintf(npas,"%lu %lu %lu %d %d\n",
              ut,ed,pe,fla,ntl);
d1041 1
a1041 2
            sprintf(tol,"%s's invalid login setting is changed to %d.",
                lo,ntl);
d1197 11
a1207 1
  case 2:
d1215 1
a1215 1
  case 3:
d1219 1
a1219 1
  case 4:
d1229 1
a1229 1
  case 5:
d1236 1
a1236 1
  case 6:
d1241 1
a1241 1
	case 7:
d1249 1
a1249 1
	case 8:
d1251 4
a1254 2
    cprintf("NOTE: It is a good idea to have PasswordExpiresIn set to between 180\n\r");
    cprintf("and 365. Anything over a year is a security risk due to age.\n\r");
d1257 13
a1269 1
    cprintf("should depend on how busy your system generally is.\n\r\n\r");
d1272 1
a1272 1
	case 9:
d1277 1
a1277 1
	case 10:
d1283 1
a1283 1
	case 11:
d1290 1
a1290 1
	case 12:
d1297 1
a1297 1
	case 13:
d1308 1
a1308 1
	case 14:
d1319 1
a1319 1
	case 15:
d1331 1
a1331 1
	case 16:
d1343 1
a1343 1
	case 17:
d1349 1
a1349 1
	case 18:
d1357 1
a1357 1
	case 19:
d1363 1
a1363 1
	case 20:
d1369 1
a1369 1
	case 21:
d1378 1
a1378 1
	case 22:
d1386 1
a1386 1
	case 23:
d1396 1
a1396 1
	case 24:
d1403 1
a1403 1
	case 25:
d1405 1
a1405 1
    cprintf("\"Sentry\" \"sentry\" and \"SENTRY\" are all treated as the same at\n\r");
d1415 1
a1415 1
	case 26:
d1422 1
a1422 1
	case 27:
d1429 1
a1429 1
	case 28:
d1439 1
a1439 1
	case 29:
d1450 1
a1450 1
	case 30:
d1461 1
a1461 1
	case 31:
d1472 1
a1472 1
	case 32:
d1504 11
a1514 6
    case 1:  /*Path*/
      if ((ini=fopen(cv,"r"))==NULL)
      {
        cprintf("\n\rPlease enter a valid path.\n\r\n\rPress any key to try again...\n\r");
        bk=blch();
      }
d1562 36
d1616 4
a1619 3
  strcpy(txt[10],"0. Edit Initialization settings");
  strcpy(txt[11],"X. Exit");
  crwin(11,6,52,22,tf,tb,2);
d1715 5
a1719 1
        break;
d1791 5
a1795 1
      break;
@


3.0
log
@Sentry V3.0
Hardcoded ini and pwd files.
Exploding windows.
Other minor changes.
@
text
@d8 1
a8 1
short int err=1;
d37 2
a38 1
          sprintf(tol,"%s is changing passwords.",na);
d76 1
d84 3
a86 3
short int x,y,sel=1,tp=0;
long ut,ed,pe;
char opt=0;
d103 2
a104 1
      if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
d108 1
a108 1
        else
d119 5
a123 3
        sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
      else
        sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
d125 2
a126 1
      sprintf(lo," %02d:%02d:%02d",nw.ti_hour,nw.ti_min,nw.ti_sec);
d135 5
a139 3
          sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
d151 5
a155 3
          sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
d170 1
a170 1
      else
d175 2
a176 1
      cprintf("Maximum number of users exceeded! (MAXUSER=%d)",MAXUSER);
d249 6
a254 6
      case 13:
        return(sel+tp);
      case 77:
      case 80:
        if ((sel<(WIND-1)) && ((sel+tp)<x))
          sel++;
d261 5
a265 5
        break;
      case 72:
      case 75:
        if ((sel>1) || ((sel>0) && (tp>0)))
          sel--;
d272 6
a277 9
        break;
      case 73:
        if (tp>0)
        {
          tp-=WIND;
          if (!sel)
            sel=1;
        }
        else
d279 14
a292 11
        break;
      case 81:
        if ((tp+WIND)<=x)
          tp+=WIND;
        else
          sel=x-tp;
        if (!((sel+tp)<=x))
          sel=x-tp;
        break;
      case 27:
        return(0);
d297 1
a297 1
void creat(void)
d299 1
a299 1
  creat() is the function used to create a new user. This function is
d301 1
d305 3
a307 3
short int err=1;
long ut,ed,pe;
char opt;
d375 1
a375 1
          else
d381 1
a381 1
          else
d390 2
a391 1
      cprintf("Logins must be between %d and %d characters.\n\r",min,max);
d394 2
a395 1
      cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
d429 2
a430 2
short int x,y=0;
char opt;
d477 2
a478 1
          cprintf("\n\r\n\rAre you sure you want to delete %s? ",na);
d504 1
d506 2
a507 1
  to replace the old password and access group.
d510 2
a511 2
short int v,err=0,y=0;
char opt;
d568 1
a568 1
            else
d579 4
a582 2
            strcpy(pa,gin("\n\r\n\rPassword:",0));
            if ((strlen(pa)>max) || (strlen(pa)<min))
d584 2
a585 1
              cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
d594 4
a597 2
                pa[strlen(pa)+1]=0;
                pa[strlen(pa)]=STAMP;
d601 2
a602 1
              strcpy(na,gin("Verify Password:",0));
d605 4
a608 2
                na[strlen(na)+1]=0;
                na[strlen(na)]=STAMP;
d620 6
a625 3
                na[strlen(na)+2]=0;
                na[strlen(na)+1]='\n';
                na[strlen(na)]='\r';
d629 8
a636 4
                na[strlen(na)+3]=0;
                na[strlen(na)+2]='\n';
                na[strlen(na)+1]='\r';
                na[strlen(na)]=STAMP;
d640 4
a643 2
                strcpy(ps,na);
                strcpy(tol,"SuperUser Access ");
d645 6
a650 3
                  strcat(tol,"Granted to");
                else
                  strcat(tol,"Revoked from");
d652 2
a653 1
                strcpy(na,lo);
d655 4
a658 2
                strcat(tol,na);
                strcat(tol,".");
d664 6
a669 3
              ps[strlen(ps)+2]=0;
              ps[strlen(ps)+1]='\n';
              ps[strlen(ps)+1]='\r';
d693 3
a695 3
short int x,y=0;
long ut,ed,zs,pe;
char opt;
d723 2
a724 1
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
d726 2
a727 1
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
d729 1
a729 1
          else
d739 5
a743 3
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
          else
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
d752 2
a753 1
        cprintf("Do you want to change %s's expiry date? ",na);
d766 2
a767 1
          fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
d772 2
a773 1
            sprintf(tol,"User %s account expiry changed to ",lo);
d775 7
a781 3
              sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
            else
              sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
d786 2
a787 1
            sprintf(tol,"User %s account expiry removed.",lo);
d807 3
a809 3
short int x,y=0;
long ut,ed,zs,pe;
char opt;
d837 2
a838 1
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
d840 2
a841 1
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
d843 1
a843 1
          else
d853 5
a857 3
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
          else
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
d866 2
a867 1
        cprintf("Do you want to change %s's expiry date? ",na);
d880 2
a881 1
          fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
d886 2
a887 1
            sprintf(tol,"User %s password expiry changed to ",lo);
d889 7
a895 3
              sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
            else
              sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
d900 2
a901 1
            sprintf(tol,"User %s password expiry removed.",lo);
d914 2
a915 1
  vlog is called when the user wishes to view the log file. They can purge
d919 1
a919 1
short int x=0,c=0,vl;
d975 1
d981 3
a983 3
short int x,y=0;
long ut,ed,pe;
char opt,ho[MAX];
d1011 2
a1012 1
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
d1014 2
a1015 1
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
d1017 1
a1017 1
          else
d1024 3
a1026 2
          cprintf("This account will currently lock up after %d invalid logins.\n\r",ntl);
        else
d1028 2
a1029 1
        cprintf("Do you want to change %s's invalid login setting? ",na);
d1047 2
a1048 1
            if ((streq(ho,"n")) || (streq(ho,"N")))
d1050 1
a1050 1
            else
d1057 2
a1058 1
          fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
d1061 3
a1063 2
            sprintf(tol,"%s's invalid login setting is changed to %d.",lo,ntl);
          else
d1076 4
d1081 2
a1082 2
short int x,y,sel=1,tp=0;
char opt=0;
d1133 8
a1140 8
      case 13:
        iedit(sel+tp-1);
        crwin(7,1,47,24,tf,tb,1);
        break;
      case 77:
      case 80:
        if ((sel<(WIN0-1)) && ((sel+tp)<x))
          sel++;
d1147 5
a1151 5
        break;
      case 72:
      case 75:
        if ((sel>1) || ((sel>0) && (tp>0)))
          sel--;
d1158 6
a1163 9
        break;
      case 73:
        if (tp>0)
        {
          tp-=WIN0;
          if (!sel)
            sel=1;
        }
        else
d1165 15
a1179 12
        break;
      case 81:
        if ((tp+WIN0)<=x)
          tp+=WIN0;
        else
          sel=x-tp;
        if (!((sel+tp)<=x))
          sel=x-tp;
        break;
      case 27:
        x=-1;
        break;
d1187 5
d1193 2
a1194 2
char cv[100];
int tv,qu;
d1208 270
a1477 262
    case 1:
      cprintf("This contains the location of the log file. The log file\n\r");
      cprintf("should be kept somewhere safe, tucked away from prying eyes.\n\r");
      cprintf("NOTE: You should change the name of the file from Sentry.log to some\n\r");
      cprintf("other, inconspicuous name. Potential intruders will search for the\n\r");
      cprintf("Sentry.log file. You can hide it under misleading names such as\n\r");
      cprintf("file_id.diz, chklist.ms, warm.com etc etc.\n\r\n\r");
      cprintf("Default: c:\\Sentry.log");
      qu=1;
      break;
    case 2:
      cprintf("Sets the minimum length for passwords and logins.\n\r");
      cprintf("NOTE: A value of 4 should be the absolute minimum for\n\r");
      cprintf("MinPasswordLen. A value of 5 or 6 would be even better. Short\n\r");
      cprintf("passwords are much easier to stumble across since less attempts\n\r");
      cprintf("have to be made before it is guessed.\n\r\n\r");
      cprintf("Default: 4");
      break;
    case 3:
      cprintf("Sets the maximum length for passwords and logins.\n\r\n\r");
      cprintf("Default: 20");
      break;
    case 4:
      cprintf("Sets the maximum times a user can attempt to log in before being\n\r");
      cprintf("locked out.\n\r");
      cprintf("NOTE: This should not be set too high. It is very rare for a\n\r");
      cprintf("legitimate user to botch a login attempt 3 times in a row. A\n\r");
      cprintf("potential intruder will usually have to make many attempts before\n\r");
      cprintf("getting anywhere. Setting MaxTries to around 3 will slow him down\n\r");
      cprintf("greatly, as he will have to reset after 3 failed attempts.\n\r\n\r");
      cprintf("Default: 3");
      break;
    case 5:
      cprintf("Sets the delay in seconds to wait after the user fails to log in.\n\r");
      cprintf("NOTE: Setting the WaitTime to 3 or above greatly slows any\n\r");
      cprintf("methodical attempt to guess or discover passwords. It offers little\n\r");
      cprintf("inconvenience to the end users while providing added security.\n\r\n\r");
      cprintf("Default: 3");
      break;
    case 6:
      cprintf("Sets the \"key\" to enter as a password to change passwords.\n\r\n\r");
      cprintf("Default: passwd");
      qu=3;
      break;
    case 7:
      cprintf("Sets the number of days a password is good before it expires.\n\r");
      cprintf("NOTE: It is a good idea to have PasswordExpiresIn set to between 180\n\r");
      cprintf("and 365. Anything over a year is a security risk due to age.\n\r");
      cprintf("Anything under half a year is a risk because people will tend to\n\r");
      cprintf("forget their passwords and start writing them down. This setting\n\r");
      cprintf("should depend on how busy your system generally is.\n\r\n\r");
      cprintf("Default: 365");
      break;
    case 8:
      cprintf("This sets the amount of idle time (in seconds) that may pass before\n\r");
      cprintf("the screen saver is activated.\n\r\n\r");
      cprintf("Default: 300");
      break;
    case 9:
      cprintf("This is the message that is displayed randomly on the screen when\n\r");
      cprintf("the scren saver is active.\n\r\n\r");
      cprintf("Default: This is a Secure Terminal.");
      qu=2;
      break;
    case 10:
      cprintf("This sets the value of the prompt that is displayed when the user is\n\r");
      cprintf("expected to enter their login name. Modifying this allows you\n\r");
      cprintf("to customize your environment as you see fit.\n\r\n\r");
      cprintf("Default: Login:");
      qu=2;
      break;
    case 11:
      cprintf("This sets the value of the prompt that is displayed when the user is\n\r");
      cprintf("expected to enter their password. Modifying this allows you\n\r");
      cprintf("to customize your environment as you see fit.\n\r\n\r");
      cprintf("Default: Password:");
      qu=2;
      break;
    case 12:
      cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
      cprintf("password.\n\r");
      cprintf("NOTE: It is a good idea to keep the wrong password and wrong login\n\r");
      cprintf("messages the same. Otherwise, a potential intruder will know when he\n\r");
      cprintf("has foind an account (IE: If Sentry responds with \"Invalid\n\r");
      cprintf("Password\", he knows the login was correct). Keeping the two the same\n\r");
      cprintf("prevents an attacker from knowing if he even has the correct login.\n\r\n\r");
      cprintf("Default: Invalid Login.");
      qu=2;
      break;
    case 13:
      cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
      cprintf("login.\n\r");
      cprintf("NOTE: It is a good idea to keep the wrong password and wrong login\n\r");
      cprintf("messages the same. Otherwise, a potential intruder will know when he\n\r");
      cprintf("has foind an account (IE: If Sentry responds with \"Invalid\n\r");
      cprintf("Password\", he knows the login was correct). Keeping the two the same\n\r");
      cprintf("prevents an attacker from knowing if he even has the correct login.\n\r\n\r");
      cprintf("Default: Invalid Login.");
      qu=2;
      break;
    case 14:
      cprintf("This sets the message to be displayed when a user enters a password\n\r");
      cprintf("of invalid length.\n\r");
      cprintf("NOTE: It is wise to keep the wrong password length, wrong login\n\r");
      cprintf("length, wrong password and wrong login messages the same. This will\n\r");
      cprintf("prevent a potential attacker from knowing the max and min settings\n\r");
      cprintf("for passwords or logins on your system. (Knowing the length of a\n\r");
      cprintf("password can greatly decrease the amount of time required to\n\r");
      cprintf("crack it).\n\r\n\r");
      cprintf("Default: Invalid Login.");
      qu=2;
      break;
    case 15:
      cprintf("This sets the message to be displayed when a user enters a login of\n\r");
      cprintf("invalid length.\n\r\n\r");
      cprintf("NOTE: It is wise to keep the wrong password length, wrong login\n\r");
      cprintf("length, wrong password and wrong login messages the same. This will\n\r");
      cprintf("prevent a potential attacker from knowing the max and min settings\n\r");
      cprintf("for passwords or logins on your system. (Knowing the length of a\n\r");
      cprintf("password can greatly decrease the amount of time required to\n\r");
      cprintf("crack it).\n\r\n\r");
      cprintf("Default: Invalid Login.");
      qu=2;
      break;
    case 16:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("the wrong password.\n\r\n\r");
      cprintf("Default: User entered the wrong password.");
      qu=2;
      break;
    case 17:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("the wrong login.\n\r");
      cprintf("NOTE: This message should be descriptive, since the SuperUser will\n\r");
      cprintf("use it to determine what sort of activities have been happening.\n\r\n\r");
      cprintf("Default: User entered the wrong login.");
      qu=2;
      break;
    case 18:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("a password of invalid length.\n\r\n\r");
      cprintf("Default: Invalid Password Length.");
      qu=2;
      break;
    case 19:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("a login of invalid length.\n\r\n\r");
      cprintf("Default: Invalid Login Length.");
      qu=2;
      break;
    case 20:
      cprintf("This sets the environment variable used to store the user's login\n\r");
      cprintf("name after a successful login.\n\r");
      cprintf("NOTE: The environment variable USER is used by many networks, such\n\r");
      cprintf("Novell. By using this setting, Sentry can be used in conjunction\n\r");
      cprintf("with these networks.\n\r\n\r");
      cprintf("Default: USER");
      qu=2;
      break;
    case 21:
      cprintf("The Windows flag is set if you wish to run Sentry from Windows.\n\r");
      cprintf("Technically, this allows Sentry to open up a DOS shell after a\n\r");
      cprintf("successful login. Setting this option to 1 has no effect on normal\n\r");
      cprintf("use, and is not a security risk.\n\r");
      cprintf("(0=Do Not Run In Windows, 1=Run In Windows)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 22:
      cprintf("This determines if the intro screen is displayed or not. You may\n\r");
      cprintf("choose not to display the title information if you don't want users\n\r");
      cprintf("to know what program you are using. On the other hand, the\n\r");
      cprintf("registration information sould be displayed for authenticity's\n\r");
      cprintf("sake. I have added this option because security comes before all\n\r");
      cprintf("else.\n\r");
      cprintf("(0=Not Displayed, 1=Displayed)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 23:
      cprintf("This will allow you to have dates displayed in different formats.\n\r");
      cprintf("Some people prefer different formats than others, so this will allow\n\r");
      cprintf("you to define the way dates are displayed.\n\r");
      cprintf("(0=MM/DD/YYYY, 1=DD/MM/YYYY)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 24:
      cprintf("This sets the case sensitivity. If \"Case Insensitive\" is selected,\n\r");
      cprintf("\"Sentry\" \"sentry\" and \"SENTRY\" are all treated as the same at\n\r");
      cprintf("the login prompt. If case sensitivity is enabled, the three are all\n\r");
      cprintf("treated as different logins.\n\r");
      cprintf("(0=Case Sensitive, 1=Case Insensitive)\n\r");
      cprintf("NOTE: Using \"Case Insensitive\" reduces the number of allowable\n\r");
      cprintf("logins, and increases the probability of an attacker getting a\n\r");
      cprintf("correct login. Still, some people find it easier to work with Case\n\r");
      cprintf("Sensitivity off.\n\r");
      cprintf("Default: 0");
      break;
    case 25:
      cprintf("This allows you to use Sentry in a \"windowed\" mode (not to be\n\r");
      cprintf("confused with MicroSoft Windows). If the windowed mode is\n\r");
      cprintf("undesirable, you can choose not to use it.\n\r");
      cprintf("(0=Regular Mode, 1=Normal Windowed Mode, 2=Exploding Windowed Mode)\n\r\n\r");
      cprintf("Default: 2");
      break;
    case 26:
      cprintf("This determines if colour will be displayed by Sentry or not. Some\n\r");
      cprintf("laptop users may wish to use the black and white setting for better\n\r");
      cprintf("readability.\n\r");
      cprintf("(0=Black and White, 1=Colour)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 27:
      cprintf("You can set TextColour to the value of the colour you wish normal\n\r");
      cprintf("text to appear in. Colour values are shown in the chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
     cprintf("Default: 15");
      break;
    case 28:
      cprintf("You can set TextBackground to the value of the colour you wish\n\r");
      cprintf("normal text to have as a background. Colour values are shown in the\n\r");
      cprintf("chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red\n\r");
      cprintf("1 Blue  5 Magenta\n\r");
      cprintf("2 Green 6 Brown\n\r");
      cprintf("3 Cyan  7 Light Gray\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 29:
      cprintf("You can set HighColour to the value of the colour you wish\n\r");
      cprintf("highlighted text to appear in. Colour values are shown in the\n\r");
      cprintf("chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 30:
      cprintf("You can set HighBackground to the value of the colour you wish\n\r");
      cprintf("highlighted text to have as a background. Colour values are shown\n\r");
      cprintf("in the chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red\n\r");
      cprintf("1 Blue  5 Magenta\n\r");
      cprintf("2 Green 6 Brown\n\r");
      cprintf("3 Cyan  7 Light Gray\n\r\n\r");
      cprintf("Default: 7");
      break;
    case 31:
      cprintf("This sets the default number of consecutive invalid logins possible\n\r");
      cprintf("before an account is locked out. Only a SuperUser can subsequently\n\r");
      cprintf("unlock an account.\n\r\n\r");
      cprintf("Default: 10");
      break;
    default:
      cprintf("No information available.");
      break;
d1489 4
a1492 4
      case 0:  /*Number*/
        qu=0;
        for(tv=0;tv<strlen(cv);tv++)
          if (!isdigit(cv[tv]))
d1494 31
a1524 24
          if (qu)
          {
            cprintf("\n\rPlease enter a numeric value.\n\r\n\rPress any key to try again...\n\r");
            bk=blch();
          }
          qu=0;
        break;
      case 1:  /*Path*/
        if ((ini=fopen(cv,"r"))==NULL)
        {
          cprintf("\n\rPlease enter a valid path.\n\r\n\rPress any key to try again...\n\r");
          bk=blch();
        }
        fclose(ini);
        break;
      case 2:  /*Multiple Word String*/
        break;
      case 3:  /*Single Word*/
        if (strchr(cv,' ')!=NULL)
        {
          cprintf("\n\rPlease enter a single word. (No spaces)\n\r\n\rPress any key to try again...\n\r");
          bk=blch();
        }
        break;
d1536 1
a1536 1
      else
d1539 1
a1539 1
        else
d1557 1
d1580 2
a1581 1
  invoke the SuperUser menu (CTRL-enter on login). super() allows the user
d1584 1
d1588 2
a1589 2
short int x,y;
char opt,sel=1;
d1620 5
a1624 71
      case 13:
        switch (sel)
        {
          case 1:
            creat();
            y=1;
            break;
          case 2:
            del();
            y=1;
            break;
          case 3:
            tolog("User List Viewed.");
            view();
            y=1;
            break;
          case 4:
            toggle();
            y=1;
            break;
          case 5:
            cex();
            y=1;
            break;
          case 6:
            pex();
            y=1;
            break;
          case 7:
            vlog();
            y=1;
            break;
          case 8:
            un=view()*-1;
            if (un)
            {
              crwin(2,5,65,22,tf,tb,2);
              if (!wm)
                clrscr();
              setp();
            }
            y=1;
            break;
          case 9:
            alock();
            y=1;
            break;
          case 10:
            iset();
            y=1;
            break;
          case SUOPT:
            su=sul=1;
            if (!puttext(1,1,80,25,msc))
              error("Internal Screen Error. [Writing]");
            fin(0);
            break;
        }
        break;
      case 77:
      case 80:
        if (sel<SUOPT)
          sel++;
        break;
      case 75:
      case 72:
        if (sel>1)
          sel--;
        break;
      case '1':
        creat();
d1627 1
a1627 1
      case '2':
d1631 1
a1631 1
      case '3':
d1636 1
a1636 1
      case '4':
d1640 1
a1640 1
      case '5':
d1644 1
a1644 1
      case '6':
d1648 1
a1648 1
      case '7':
d1652 1
a1652 1
      case '8':
d1663 1
a1663 1
      case '9':
d1667 1
a1667 1
      case '0':
d1671 1
a1671 9
      case 73:
        sel=1;
        break;
      case 81:
        sel=SUOPT;
        break;
      case 'x':
      case 'X':
      case 27:
d1677 74
@


2.7
log
@Screen blanking, minor bugs fixed.
@
text
@d21 1
a21 2
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d28 2
a29 2
      lo[strlen(lo)-1]=0;
      ps[strlen(ps)-1]=0;
d31 1
a31 3
      {
        ps[strlen(ps)-1]=0;
      }
d85 1
a85 2
  if ((pass=fopen(ipas,"r"))==NULL)
    error("Error opening password file!");
d95 2
a96 2
      lo[strlen(lo)-1]=0;
      ps[strlen(ps)-1]=0;
d311 1
a311 2
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d316 1
a316 1
      lo[strlen(lo)-1]=0;
d324 2
a325 2
      if ((pass=fopen(ipas,"a"))==NULL)
        error("Error opening password file!");
d392 2
a395 2
      fprintf(pass,"%s\n",na);
      fprintf(pass,"%s\n",pa);
d420 3
a422 5
		crwin(2,7,60,17,tf,tb,2);
		if (!wm)
			clrscr();
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d424 1
d428 1
a428 1
      if (ps[strlen(ps)-2]==STAMP)
a432 2
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d434 1
a434 1
    if ((npas=fopen(temp,"w"))==NULL)
d436 1
d440 1
a440 1
      na[strlen(na)-1]=0;
d452 1
a452 2
        if (ps[strlen(ps)-2]==STAMP)
        {
d454 1
a454 2
        }
        if ((opt==1) && (ps[strlen(ps)-2]==STAMP))
d479 3
a481 4
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
d498 3
a500 3
		crwin(2,5,69,22,tf,tb,2);
		if (!wm)
			clrscr();
d509 10
a518 2
      if ((pass=fopen(ipas,"r"))==NULL)
        error("Error opening password file!");
d520 1
a520 1
      if ((npas=fopen(temp,"w"))==NULL)
d522 1
d526 1
a526 1
        na[strlen(na)-1]=0;
a537 1
          ps[strlen(ps)-1]=0;
d539 7
a545 3
          cprintf("\n\r\n\rAre you sure you want to ");
          if (ps[strlen(ps)-1]==STAMP)
            cprintf("remove SuperUser access from");
d548 10
a557 2
            cprintf("grant SuperUser access to");
            sul=1;
a558 2
          cprintf(" %s? ",na);
          opt=blch();
d595 3
a597 2
                na[strlen(na)+1]=0;
                na[strlen(na)]='\n';
d601 3
a603 2
                na[strlen(na)+2]=0;
                na[strlen(na)+1]='\n';
d616 1
a616 1
                na[strlen(na)-1]=0;
d624 3
a626 2
              ps[strlen(ps)+1]=0;
              ps[strlen(ps)]='\n';
d634 3
a636 4
      fclose(pass);
      fclose(npas);
      unlink(ipas);
      rename(temp,ipas);
d656 3
a658 5
		crwin(2,5,65,22,tf,tb,2);
		if (!wm)
			clrscr();
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d660 1
a660 1
    if ((npas=fopen(temp,"w"))==NULL)
d662 1
d666 1
a666 1
      na[strlen(na)-1]=0;
d719 12
a730 5
          lo[strlen(lo)-1]=0;
          unixtodos(ed,&td,&nw);
          sprintf(tol,"User %s account expiry changed to ",lo);
          if (df)
            sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
d732 1
a732 3
            sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
          strcat(tol,lo);
          strcat(tol,".");
d737 3
a739 4
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
d758 3
a760 5
		crwin(2,5,65,22,tf,tb,2);
		if (!wm)
			clrscr();
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d762 1
a762 1
    if ((npas=fopen(temp,"w"))==NULL)
d764 1
d768 1
a768 1
      na[strlen(na)-1]=0;
d821 12
a832 5
          lo[strlen(lo)-1]=0;
          unixtodos(pe,&td,&nw);
          sprintf(tol,"User %s password expiry changed to ",lo);
          if (df)
            sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
d834 1
a834 3
            sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
          strcat(tol,lo);
          strcat(tol,".");
d839 3
a841 4
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
d918 3
a920 5
		crwin(2,5,65,22,tf,tb,2);
		if (!wm)
			clrscr();
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d922 1
a922 1
    if ((npas=fopen(temp,"w"))==NULL)
d924 1
d928 1
a928 1
      na[strlen(na)-1]=0;
d971 3
a973 3
            cprintf("\n\rEnter the number of sequential invalid logins before the");
            cprintf("\n\ruser's account is automatically expired: ");
            scanf("%s",&ho);
d984 5
a988 2
          lo[strlen(lo)-1]=0;
          sprintf(tol,"%s's invalid login setting is changed to %d.",lo,ntl);
d993 3
a995 4
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
d1004 2
a1005 2
    strcpy(txt[x+1],is[x][0]);
  crwin(7,1,47,24,tf,tb,1);
d1108 1
a1108 1
char cv[100],ia[35];
d1110 5
a1114 17
  strcpy(ia,is[set][1]);
  if ((ini=fopen(inam,"r"))==NULL)
    error("Error opening Sentry.ini file!");
  strcpy(lo,"");
  getini();
  while ((!streq(ia,lo)) && (fgets(lo,MAX,ini)!=NULL))
  {
    if (!strncmp(ia,lo,strlen(ia)-1))
    {
      for(tv=0;tv<(strlen(lo)-strlen(ia)-2);tv++)
        cv[tv]=lo[tv+strlen(ia)+1];
      cv[tv]=0;
      strcpy(lo,ia);
    }
    else
      getini();
  }
d1119 1
a1119 1
  cprintf("%s\n\r(%s)\n\r\n\r",is[set][0],is[set][1]);
d1121 1
a1121 1
  switch (set+1)
d1124 1
a1124 1
      cprintf("This contains the location of the password file. The password file\n\r");
d1126 1
a1126 1
      cprintf("NOTE: You should change the name of the file from Sentry.pwd to some\n\r");
d1128 1
a1128 1
      cprintf("Sentry.pwd file. You can hide it under misleading names such as\n\r");
d1130 1
a1130 1
      cprintf("Default: c:\\Sentry\\Sentry.pwd");
a1133 6
      cprintf("This contains the location of the log file. The log file\n\r");
      cprintf("should also be hidden away in the same manner described above.\n\r\n\r");
      cprintf("Default: c:\\Sentry\\Sentry.log");
      qu=1;
      break;
    case 3:
d1141 1
a1141 1
    case 4:
d1145 1
a1145 1
    case 5:
d1155 1
a1155 1
    case 6:
d1162 1
a1162 1
    case 7:
d1167 1
a1167 1
    case 8:
d1176 5
d1182 4
a1185 3
      cprintf("This sets the amount of time (in seconds) that may pass before the\n\r");
      cprintf("screen saver is activated.\n\r\n\r");
      cprintf("Default: 300");
d1191 1
a1191 1
      cprintf("Default: \"Login:\"");
d1198 1
a1198 1
      cprintf("Default: \"Password:\"");
d1204 6
a1209 6
      cprintf("NOTE: It is a good idea to keep WrongPassword and WrongLogin the\n\r");
      cprintf("same. Otherwise, a potential intruder will know when he has found\n\r");
      cprintf("an account (IE: If Sentry responds with \"Invalid Password\" he\n\r");
      cprintf("knows the login was correct). Keeping the two the same prevents an\n\r");
      cprintf("attacker from knowing if he even has the correct login.\n\r\n\r");
      cprintf("Default: \"Invalid Login.\"");
d1214 7
a1220 2
      cprintf("login.\n\r\n\r");
      cprintf("Default: \"Invalid Login.\"");
d1226 7
a1232 6
      cprintf("NOTE: It is also wise to keep PasswordLength and LoginLength the\n\r");
      cprintf("same as WrongPassword and WrongLogin. This will prevent a potential\n\r");
      cprintf("attacker from knowing how long a password or login is set to be on\n\r");
      cprintf("your system. (Knowing the length of a password can greatly decrease\n\r");
      cprintf("the amount of time required to crack it).\n\r\n\r");
      cprintf("Default: \"Invalid Login.\"");
d1238 7
a1244 1
      cprintf("Default: \"Invalid Login.\"");
d1250 1
a1250 1
      cprintf("Default: \"User entered the wrong password.\"");
d1255 4
a1258 2
      cprintf("the wrong login.\n\r\n\r");
      cprintf("Default: \"User entered the wrong login.\"");
d1264 1
a1264 1
      cprintf("Default: \"Invalid Password Length.\"");
d1270 1
a1270 1
      cprintf("Default: \"Invalid Login Length.\"");
d1274 6
a1279 3
      cprintf("This sets the environment variable used to store the user's login name\n\r");
      cprintf("after a successful login.\n\r\n\r");
      cprintf("Default: \"USER\"");
d1323 2
a1324 2
      cprintf("(0=Regular Mode, 1=Windowed Mode)\n\r\n\r");
      cprintf("Default: 1");
d1348 4
a1351 4
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
d1370 4
a1373 4
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
d1416 1
a1416 5
      case 2:  /*Quote delimited string*/
        if (cv[0]!='\"')
          strcpy(cv,strcat(strcpy(temp,"\""),cv));
        if (cv[strlen(cv)-1]!='\"')
          strcat(cv,"\"");
a1428 3
    strcpy(cv,strcat(strcat(strcat(strcpy(temp,ia),"="),cv),"\n"));
    if ((ini=fopen(inam,"r"))==NULL)
      error("Error opening Sentry.ini file!");
d1430 1
a1430 1
    if ((npas=fopen(temp,"w"))==NULL)
d1432 4
a1435 11
    strcpy(lo,"");
    while (fgets(lo,MAX,ini)!=NULL)
    {
      if (!strncmp(ia,lo,strlen(ia)-1))
      {
        fprintf(npas,"%s",cv);
        strcpy(na,cv);
        na[strlen(na)-1]=0;
        sprintf(tol,"Setting Modified: %s",na);
        tolog(tol);
      }
d1437 7
a1443 4
        fprintf(npas,"%s",lo);
    }
    fclose(ini);
    fclose(npas);
a1449 1
    fclose(npas);
d1473 1
a1473 1
  crwin(4,6,47,23,tf,tb,1);
d1550 8
a1557 8
						un=view()*-1;
						if (un)
						{
							crwin(2,5,65,22,tf,tb,2);
							if (!wm)
								clrscr();
							setp();
						}
d1570 2
d1617 7
a1623 7
				if (un)
				{
					crwin(2,5,65,22,tf,tb,2);
					if (!wm)
						clrscr();
					setp();
				}
d1634 6
d1644 2
@


2.6
log
@Version 2.6
Login and Password prompts are customizable.
Initialization setting changes are logged.
DOS environment veriable is set to user's login name.
@
text
@d3 3
a5 3
	cpass(void) is the function called when a user wishes to change his
	password. cpass(void) requires the user to enter their old password
	(as verification), and then calls setp(void) to set the new password.
d9 63
a71 63
	while (err)
	{
		err=0;
		_bk=0;
		strcpy(pa,gin("\n\rOld Password:",0));
		strcpy(temp,pa);
		temp[strlen(temp)+1]=0;
		temp[strlen(temp)]=STAMP;
		if ((strlen(pa)>max) || (strlen(pa)<min))
			err=2;
		strcpy(temp,penc(temp));
		strcpy(pa,penc(pa));
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		if (!err)
			err=4;
		while((fgets(lo,MAX,pass))!=NULL)
		{
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			lo[strlen(lo)-1]=0;
			ps[strlen(ps)-1]=0;
			if (ps[strlen(ps)-1]==STAMP)
			{
				ps[strlen(ps)-1]=0;
			}
			if (err==4)
			{
				if (csck(na,lo))
				{
					err=0;
					sprintf(tol,"%s is changing passwords.",na);
					tolog(tol);
					if (strcmp(pa,ps))
					{
						if (strcmp(temp,ps))
							err=3;
					}
				}
			}
		}
		switch (err)
		{
		case 2:
			cprintf("%s\n\r",xplen);
			tolog(lxplen);
			sleep(wait);
			break;
		case 3:
			cprintf("%s\n\r",xpwd);
			tolog(lxpwd);
			sleep(wait);
			break;
		case 4:
			cprintf("%s\n\r",xlog);
			tolog(lxlog);
			sleep(wait);
			break;
		}
		fclose(pass);
	}
	un*=-1;
	setp();
d76 7
a82 7
	view() displays a list of all current users in the password file.
	SuperUsers are denoted with a * to the right of their name. The cursor
	keys are used to highlight a user, and the enter key will select that
	user. The PAGE UP and PAGE DOWN keys can be used to show more screens
	if they are available.
	view() returns the ordinal value of the user selected (as per the
	password file) as an integer.
d88 200
a287 200
	if ((pass=fopen(ipas,"r"))==NULL)
		error("Error opening password file!");
	x=0;
	crwin(1,1,79,24,tf,tb,1);
	while((fgets(lo,MAX,pass))!=NULL)
	{
		x++;
		if (x<MAXUSER)
		{
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			lo[strlen(lo)-1]=0;
			ps[strlen(ps)-1]=0;
			if (ps[strlen(ps)-1]==STAMP)
			{
				strcat(lo," *");
			}
			if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
			{
				if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
					error("Error in time stamps.");
				else
				{
					fla=0;
					ntl=ltl;
				}
			}
			strcpy(txt[x],lo);
			for(y=strlen(lo);y<LLST;y++)
				strcat(txt[x]," ");
			unixtodos(ut,&td,&nw);
			if (df)
				sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
			else
				sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
			strcat(txt[x],lo);
			sprintf(lo," %02d:%02d:%02d",nw.ti_hour,nw.ti_min,nw.ti_sec);
			strcat(txt[x],lo);
			strcpy(lo,txt[x]);
			for(y=strlen(lo);y<AEST;y++)
				strcat(txt[x]," ");
			if (ed)
			{
				unixtodos(ed,&td,&nw);
				if (df)
					sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
				else
					sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
				strcat(txt[x],lo);
			}
			else
				strcat(txt[x]," * NONE *");
			strcpy(lo,txt[x]);
			for(y=strlen(lo);y<PEST;y++)
				strcat(txt[x]," ");
			if (pe)
			{
				unixtodos(pe,&td,&nw);
				if (df)
					sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
				else
					sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
				strcat(txt[x],lo);
			}
			else
				strcat(txt[x]," * NONE *");
			strcpy(lo,txt[x]);
			for(y=strlen(lo);y<ILST;y++)
				strcat(txt[x]," ");
			sprintf(lo,"%d",fla);
			strcat(txt[x],lo);
			strcpy(lo,txt[x]);
			for(y=strlen(lo);y<NLST;y++)
				strcat(txt[x]," ");
			if (ntl)
				sprintf(lo,"%d",ntl);
			else
				strcpy(lo,"X");
			strcat(txt[x],lo);
		}
		else
			cprintf("Maximum number of users exceeded! (MAXUSER=%d)",MAXUSER);
	}
	fclose(pass);
	while (1)
	{
		txb(tb);
		txc(tf);
		clrscr();
		cprintf("Current Users (ESC exits)\n\r\n\r");
		if (!tp)
			cprintf("\n\r");
		strcpy(lo,"User Name");
		strcpy(pa,lo);
		for(y=strlen(pa);y<LLST;y++)
			strcat(lo," ");
		strcat(lo,"Last Login");
		strcpy(pa,lo);
		for(y=strlen(pa);y<AEST;y++)
			strcat(lo," ");
		strcat(lo,"Acct Expiry");
		strcpy(pa,lo);
		for(y=strlen(pa);y<PEST;y++)
			strcat(lo," ");
		strcat(lo,"Passwd Exp");
		strcpy(pa,lo);
		for(y=strlen(pa);y<ILST-2;y++)
			strcat(lo," ");
		strcat(lo,"Inv Log");
		strcpy(pa,lo);
		for(y=strlen(pa);y<NLST-2;y++)
			strcat(lo," ");
		strcat(lo,"Max InvLog");
		cprintf("%s\n\r",lo);
		for(y=0;y<(NLST+6);y++)
			cprintf("-");
		if (tp>0)
		{
			gotoxy(NLST+4,2);
			cprintf("");
		}
		cprintf("\n\r");
		if (tp)
			cprintf("\n\r\n\r");
		for(y=tp;y<WIND+tp;y++)
		{
			if (y<=x)
			{
				if (sel==(y % WIND))
				{
					txb(hb);
					txc(hf);
				}
				else
				{
					txb(tb);
					txc(tf);
				}
				if (y)
					cprintf("%s\n\r",txt[y]);
			}
		}
		txb(tb);
		txc(tf);
		if (tp+WIND<=x)
		{
			gotoxy(NLST+4,21);
			cprintf("");
		}
		gotoxy(1,22);
		cprintf("Select a user: ");
		opt=blch();
		switch (opt)
		{
			case 13:
				return(sel+tp);
			case 77:
			case 80:
				if ((sel<(WIND-1)) && ((sel+tp)<x))
					sel++;
				else
				if ((sel+tp)<x)
				{
					tp+=WIND;
					sel=0;
				}
				break;
			case 72:
			case 75:
				if ((sel>1) || ((sel>0) && (tp>0)))
					sel--;
				else
				if (tp>0)
				{
					tp-=WIND;
					sel=WIND-1;
				}
				break;
			case 73:
				if (tp>0)
				{
					tp-=WIND;
					if (!sel)
						sel=1;
				}
				else
					sel=1;
				break;
			case 81:
				if ((tp+WIND)<=x)
					tp+=WIND;
				else
					sel=x-tp;
				if (!((sel+tp)<=x))
					sel=x-tp;
				break;
			case 27:
				return(0);
		}
	}
d292 3
a294 3
	creat() is the function used to create a new user. This function is
	called only from the SuperUser menu. All normal verifying is performed
	before the user information is saved.
d300 110
a409 110
	sul=0;
	crwin(2,5,65,22,tf,tb,2);
	if (!wm)
		clrscr();
	while (err>0)
	{
		err=0;
		cprintf("\n\r\n\rCreate User.\n\r\n\r");
		_bk=1;
		strcpy(na,gin("Login:",1));
		strcpy(temp,na);
		if (bk)
			break;
		if ((strlen(temp)>max) || (strlen(temp)<min))
			err=1;
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			lo[strlen(lo)-1]=0;
			if (csck(temp,lo))
				if (err==0)
					err=4;
		}
		if (!err)
		{
			fclose(pass);
			if ((pass=fopen(ipas,"a"))==NULL)
				error("Error opening password file!");
			_bk=1;
			strcpy(pa,gin("Password:",0));
			if (bk)
				break;
			if ((strlen(pa)>max) || (strlen(pa)<min))
				err=2;
			if (!err)
			{
				if (sul)
				{
					pa[strlen(pa)+1]=0;
					pa[strlen(pa)]=STAMP;
				}
				strcpy(pa,penc(pa));
				_bk=1;
				strcpy(ps,gin("Verify Password:",0));
				if (bk)
					break;
				if (sul)
				{
					ps[strlen(ps)+1]=0;
					ps[strlen(ps)]=STAMP;
				}
				strcpy(ps,penc(ps));
				if (strcmp(pa,ps))
					err=3;
				if (!err)
				{
					if (sul)
					{
						pa[strlen(pa)+1]=0;
						pa[strlen(pa)]=STAMP;
					}
					cprintf("Do you want this account to have an expiry date? ");
					opt=blch();
					if ((opt=='y') || (opt=='Y'))
						ed=gdate();
					else
						ed=0;
					cprintf("\n\rDo you want the password to have an expiry date? ");
					opt=blch();
					if ((opt=='y') || (opt=='Y'))
						pe=gdate();
					else
						pe=0;
					cprintf("\n\r");
				}
			}
		}
		switch (err)
		{
		case 1:
			cprintf("Logins must be between %d and %d characters.\n\r",min,max);
			break;
		case 2:
			cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
			break;
		case 3:
			cprintf("Password not verified!\n\r");
			break;
		case 4:
			cprintf("That user already exists!\n\r");
			break;
		}
		if (!err)
		{
			sprintf(tol,"User %s Created.",na);
			tolog(tol);
			fprintf(pass,"%s\n",na);
			fprintf(pass,"%s\n",pa);
			getdate(&td);
			gettime(&nw);
			ut=dostounix(&td,&nw);
			fla=0;
			ntl=ltl;
			fprintf(pass,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
		}
		fclose(pass);
	}
d414 4
a417 4
	del() is the function called to delete a user. It is called only from
	the SuperUser menu. It first calls view() so that the intended user
	can be selected. A check is performed to make sure that the last
	SuperUser listed in the password file is not being deleted.
d422 71
a492 71
	x=view();
	crwin(2,7,60,17,tf,tb,2);
	if (!wm)
		clrscr();
	if (x)
	{
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		opt=0;
		while((fgets(lo,MAX,pass))!=NULL)
		{
			fgets(ps,MAX,pass);
			if (ps[strlen(ps)-2]==STAMP)
				opt++;
			fgets(ti,MAX,pass);
		}
		fclose(pass);
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			strcpy(na,lo);
			na[strlen(na)-1]=0;
			y++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			if (y!=x)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
				if (ps[strlen(ps)-2]==STAMP)
				{
					cprintf("\n\rThis is a SuperUser!");
				}
				if ((opt==1) && (ps[strlen(ps)-2]==STAMP))
				{
					cprintf("\n\rYou cannot delete this user, they are the last SuperUser!");
					cprintf("\n\r\n\rPress any key to return to the SuperUser menu...");
					opt=blch();
					opt=0;
				}
				else
				{
					cprintf("\n\r\n\rAre you sure you want to delete %s? ",na);
					opt=blch();
				}
				if ((opt!='y') && (opt!='Y'))
				{
					fputs(lo,npas);
					fputs(ps,npas);
					fputs(ti,npas);
				}
				else
				{
					sprintf(tol,"User %s Deleted.",na);
					tolog(tol);
				}
			}
		}
		fclose(pass);
		fclose(npas);
		unlink(ipas);
		rename(temp,ipas);
	}
d497 4
a500 4
	toggle() is the function called to toggle SuperUser status. It is
	called only from the SuperUser menu. It first calls view() so that the
	intended user can be selected. The user's password must be entered
	to replace the old password and access group.
d505 124
a628 124
	v=view();
	crwin(2,5,69,22,tf,tb,2);
	if (!wm)
		clrscr();
	if (v)
	{
		cprintf("NOTE: The user must re-enter their password to obtain or give up\n\r");
		cprintf("      SuperUser access.\n\r");
		cprintf("      You may override this by entering any other password, which\n\r");
		cprintf("      will be this user's password from now on.\n\r");
		cprintf("\n\r\n\rIS THIS OK? ");
		opt=blch();
		if ((opt=='y') || (opt=='Y'))
		{
			if ((pass=fopen(ipas,"r"))==NULL)
				error("Error opening password file!");
			tmpnam(temp);
			if ((npas=fopen(temp,"w"))==NULL)
				error("Error opening temp file!");
			while((fgets(lo,MAX,pass))!=NULL)
			{
				strcpy(na,lo);
				na[strlen(na)-1]=0;
				y++;
				fgets(ps,MAX,pass);
				fgets(ti,MAX,pass);
				if (y!=v)
				{
					fputs(lo,npas);
					fputs(ps,npas);
					fputs(ti,npas);
				}
				else
				{
					ps[strlen(ps)-1]=0;
					sul=0;
					cprintf("\n\r\n\rAre you sure you want to ");
					if (ps[strlen(ps)-1]==STAMP)
						cprintf("remove SuperUser access from");
					else
					{
						cprintf("grant SuperUser access to");
						sul=1;
					}
					cprintf(" %s? ",na);
					opt=blch();
					if ((opt=='y') || (opt=='Y'))
					{
						_bk=0;
						strcpy(pa,gin("\n\r\n\rPassword:",0));
						if ((strlen(pa)>max) || (strlen(pa)<min))
						{
							cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
							cprintf("\n\rPress any key to continue...");
							opt=blch();
							err=2;
						}
						if (!err)
						{
							if (sul)
							{
								pa[strlen(pa)+1]=0;
								pa[strlen(pa)]=STAMP;
							}
							strcpy(pa,penc(pa));
							_bk=0;
							strcpy(na,gin("Verify Password:",0));
							if (sul)
							{
								na[strlen(na)+1]=0;
								na[strlen(na)]=STAMP;
							}
							strcpy(na,penc(na));
							if (strcmp(pa,na))
							{
								cprintf("Password not verified!\n\r");
								cprintf("\n\rPress any key to continue...");
								opt=blch();
								err=3;
							}
							if (!sul)
							{
								na[strlen(na)+1]=0;
								na[strlen(na)]='\n';
							}
							else
							{
								na[strlen(na)+2]=0;
								na[strlen(na)+1]='\n';
								na[strlen(na)]=STAMP;
							}
							if (!err)
							{
								strcpy(ps,na);
								strcpy(tol,"SuperUser Access ");
								if (sul)
									strcat(tol,"Granted to");
								else
									strcat(tol,"Revoked from");
								strcat(tol," user ");
								strcpy(na,lo);
								na[strlen(na)-1]=0;
								strcat(tol,na);
								strcat(tol,".");
								tolog(tol);
							}
						}
						if (err)
						{
							ps[strlen(ps)+1]=0;
							ps[strlen(ps)]='\n';
						}
					}
					fputs(lo,npas);
					fputs(ps,npas);
					fputs(ti,npas);
				}
			}
			fclose(pass);
			fclose(npas);
			unlink(ipas);
			rename(temp,ipas);
		}
	}
d633 5
a637 5
	cex(void) creates an expiry date for an account. The account to be
	adjusted is selected via view(void). That account's current expiry
	settings are then shown, and the user is asked if they want to alter
	them. If they answer yes, the date new expiry is entered via
	gdate(void) and saved in the password file.
d643 85
a727 85
	x=view();
	crwin(2,5,65,22,tf,tb,2);
	if (!wm)
		clrscr();
	if (x)
	{
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			strcpy(na,lo);
			na[strlen(na)-1]=0;
			y++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			if (y!=x)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
				if (ps[strlen(ps)-1]==STAMP)
					cprintf("\n\rThis is a SuperUser!\n\r");
				if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
				{
					if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
						error("Error in time stamps.");
					else
					{
						fla=0;
						ntl=ltl;
					}
				}
				if (ed)
				{
					unixtodos(ed,&td,&nw);
					if (df)
						cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
					else
						cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
					getdate(&td);
					gettime(&nw);
					zs=dostounix(&td,&nw);
					if (zs>ed)
						cprintf("(This account has expired.)\n\r");
				}
				else
					cprintf("This account has no expiry date.\n\r");
				cprintf("Do you want to change %s's expiry date? ",na);
				opt=blch();
				if ((opt!='y') && (opt!='Y'))
				{
					fputs(lo,npas);
					fputs(ps,npas);
					fputs(ti,npas);
				}
				else
				{
					ed=gdate();
					fputs(lo,npas);
					fputs(ps,npas);
					fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
					lo[strlen(lo)-1]=0;
					unixtodos(ed,&td,&nw);
					sprintf(tol,"User %s account expiry changed to ",lo);
					if (df)
						sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
					else
						sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
					strcat(tol,lo);
					strcat(tol,".");
					tolog(tol);
				}
			}
		}
		fclose(pass);
		fclose(npas);
		unlink(ipas);
		rename(temp,ipas);
	}
d732 5
a736 5
	pex(void) creates an expiry date for a password. The account to be
	adjusted is selected via view(void). That account's current password
	expiry settings are then shown, and the user is asked if they want to
	alter them. If they answer yes, the new expiry date is entered via
	gdate(void) and saved in the password file.
d742 85
a826 85
	x=view();
	crwin(2,5,65,22,tf,tb,2);
	if (!wm)
		clrscr();
	if (x)
	{
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			strcpy(na,lo);
			na[strlen(na)-1]=0;
			y++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			if (y!=x)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
				if (ps[strlen(ps)-1]==STAMP)
					cprintf("\n\rThis is a SuperUser!\n\r");
				if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
				{
					if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
						error("Error in time stamps.");
					else
					{
						fla=0;
						ntl=ltl;
					}
				}
				if (pe)
				{
					unixtodos(pe,&td,&nw);
					if (df)
						cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
					else
						cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
					getdate(&td);
					gettime(&nw);
					zs=dostounix(&td,&nw);
					if (zs>pe)
						cprintf("(This password has expired.)\n\r");
				}
				else
					cprintf("This password has no expiry date.\n\r");
				cprintf("Do you want to change %s's expiry date? ",na);
				opt=blch();
				if ((opt!='y') && (opt!='Y'))
				{
					fputs(lo,npas);
					fputs(ps,npas);
					fputs(ti,npas);
				}
				else
				{
					pe=gdate();
					fputs(lo,npas);
					fputs(ps,npas);
					fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
					lo[strlen(lo)-1]=0;
					unixtodos(pe,&td,&nw);
					sprintf(tol,"User %s password expiry changed to ",lo);
					if (df)
						sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
					else
						sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
					strcat(tol,lo);
					strcat(tol,".");
					tolog(tol);
				}
			}
		}
		fclose(pass);
		fclose(npas);
		unlink(ipas);
		rename(temp,ipas);
	}
d831 2
a832 2
	vlog is called when the user wishes to view the log file. They can purge
	the log after viewing if desired.
d836 50
a885 50
	tolog("Log File Viewed.");
	fclose(log);
	crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2);
	vl=VLBOT-VLTOP-VLCONST;
	if (!wm)
	{
		vl=VLFULL;
		clrscr();
	}
	if ((log=fopen(ilog,"r"))==NULL)
		error("Error opening log file!");
	while((fgets(temp,MAX,log))!=NULL)
	{
		x++;
		if (strlen(temp)>SCRWIDTH)
			x++;
		cprintf("%s\r",temp);
		if (x>vl)
		{
			cprintf("\n\r  Press a key to continue...");
			c=blch();
			cprintf("\n\r");
			x=0;
		}
		if (c==27)
			break;
	}
	fclose(log);
	if (c!=27)
	{
		cprintf("\n\r  Press a key to continue...");
		c=blch();
		cprintf("\n\r");
	}
	cprintf("\n\r Would you like to clear the log file [y/N]? ");
	c=blch();
	if ((c=='y') || (c=='Y'))
	{
		if ((log=fopen(ilog,"w"))==NULL)
			error("Error in creating log file!");
		cprintf("\n\r\n\r The log file has been cleared.\n\r");
		tolog("Log File Cleared.");
		cprintf("\n\r  Press a key to continue...");
		c=blch();
	}
	else
	{
		if ((log=fopen(ilog,"a"))==NULL)
			error("Error in creating log file!");
	}
d890 4
a893 4
	alock(void) allows accounts to be locked out after a certain number of
	sequential invalid logins. alock(void) calls view(void) first so the
	proper account can be selected. It then prompts the user for a new
	"max invalid login" value.
d899 81
a979 81
	x=view();
	crwin(2,5,65,22,tf,tb,2);
	if (!wm)
		clrscr();
	if (x)
	{
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			strcpy(na,lo);
			na[strlen(na)-1]=0;
			y++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			if (y!=x)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
				if (ps[strlen(ps)-1]==STAMP)
					cprintf("\n\rThis is a SuperUser!\n\r");
				if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
				{
					if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
						error("Error in time stamps.");
					else
					{
						fla=0;
						ntl=ltl;
					}
				}
				if (ntl)
					cprintf("This account will currently lock up after %d invalid logins.\n\r",ntl);
				else
					cprintf("This account has no limit on invalid logins.\n\r");
				cprintf("Do you want to change %s's invalid login setting? ",na);
				opt=blch();
				if ((opt!='y') && (opt!='Y'))
				{
					fputs(lo,npas);
					fputs(ps,npas);
					fputs(ti,npas);
				}
				else
				{
					x=0;
					while (x==0)
					{
						x=1;
						cprintf("\n\r\n\rEnter 'N' or '0' to assign unlimited invalid logins.");
						cprintf("\n\rEnter the number of sequential invalid logins before the");
						cprintf("\n\ruser's account is automatically expired: ");
						scanf("%s",&ho);
						if ((streq(ho,"n")) || (streq(ho,"N")))
							ntl=0;
						else
						{
							ntl=atoi(ho);
						}
					}
					fputs(lo,npas);
					fputs(ps,npas);
					fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
					lo[strlen(lo)-1]=0;
					sprintf(tol,"%s's invalid login setting is changed to %d.",lo,ntl);
					tolog(tol);
				}
			}
		}
		fclose(pass);
		fclose(npas);
		unlink(ipas);
		rename(temp,ipas);
	}
d986 101
a1086 101
	for (x=0;x<INI;x++)
		strcpy(txt[x+1],is[x][0]);
	crwin(7,1,47,24,tf,tb,1);
	x=INI;
	while (1)
	{
		txb(tb);
		txc(tf);
		clrscr();
		cprintf("Current Settings (ESC exits)\n\r\n\r");
		if (!tp)
			cprintf("\n\r");
		if (tp>0)
		{
			gotoxy(30,2);
			cprintf("");
		}
		cprintf("\n\r");
		if (tp)
			cprintf("\n\r\n\r");
		for(y=tp;y<WIN0+tp;y++)
		{
			if (y<=x)
			{
				if (sel==(y % WIN0))
				{
					txb(hb);
					txc(hf);
				}
				else
				{
					txb(tb);
					txc(tf);
				}
				if (y)
					cprintf("%s\n\r",txt[y]);
			}
		}
		txb(tb);
		txc(tf);
		if (tp+WIN0<=x)
		{
			gotoxy(30,21);
			cprintf("");
		}
		gotoxy(1,22);
		cprintf("Select a setting: ");
		opt=blch();
		switch (opt)
		{
			case 13:
				iedit(sel+tp-1);
				crwin(7,1,47,24,tf,tb,1);
				break;
			case 77:
			case 80:
				if ((sel<(WIN0-1)) && ((sel+tp)<x))
					sel++;
				else
				if ((sel+tp)<x)
				{
					tp+=WIN0;
					sel=0;
				}
				break;
			case 72:
			case 75:
				if ((sel>1) || ((sel>0) && (tp>0)))
					sel--;
				else
				if (tp>0)
				{
					tp-=WIN0;
					sel=WIN0-1;
				}
				break;
			case 73:
				if (tp>0)
				{
					tp-=WIN0;
					if (!sel)
						sel=1;
				}
				else
					sel=1;
				break;
			case 81:
				if ((tp+WIN0)<=x)
					tp+=WIN0;
				else
					sel=x-tp;
				if (!((sel+tp)<=x))
					sel=x-tp;
				break;
			case 27:
				x=-1;
				break;
		}
		if (x<0)
			break;
	}
d1093 349
a1441 349
	strcpy(ia,is[set][1]);
	if ((ini=fopen(inam,"r"))==NULL)
		error("Error opening Sentry.ini file!");
	strcpy(lo,"");
	getini();
	while ((!streq(ia,lo)) && (fgets(lo,MAX,ini)!=NULL))
	{
		if (!strncmp(ia,lo,strlen(ia)-1))
		{
			for(tv=0;tv<(strlen(lo)-strlen(ia)-2);tv++)
				cv[tv]=lo[tv+strlen(ia)+1];
			cv[tv]=0;
			strcpy(lo,ia);
		}
		else
			getini();
	}
	fclose(ini);
	crwin(3,2,73,22,tf,tb,2);
	if (!wm)
		clrscr();
	cprintf("%s\n\r(%s)\n\r\n\r",is[set][0],is[set][1]);
	qu=0;
	switch (set+1)
	{
		case 1:
			cprintf("This contains the location of the password file. The password file\n\r");
			cprintf("should be kept somewhere safe, tucked away from prying eyes.\n\r");
			cprintf("NOTE: You should change the name of the file from Sentry.pwd to some\n\r");
			cprintf("other, inconspicuous name. Potential intruders will search for the\n\r");
			cprintf("Sentry.pwd file. You can hide it under misleading names such as\n\r");
			cprintf("file_id.diz, chklist.ms, warm.com etc etc.\n\r\n\r");
			cprintf("Default: c:\\Sentry\\Sentry.pwd");
			qu=1;
			break;
		case 2:
			cprintf("This contains the location of the log file. The log file\n\r");
			cprintf("should also be hidden away in the same manner described above.\n\r\n\r");
			cprintf("Default: c:\\Sentry\\Sentry.log");
			qu=1;
			break;
		case 3:
			cprintf("Sets the minimum length for passwords and logins.\n\r");
			cprintf("NOTE: A value of 4 should be the absolute minimum for\n\r");
			cprintf("MinPasswordLen. A value of 5 or 6 would be even better. Short\n\r");
			cprintf("passwords are much easier to stumble across since less attempts\n\r");
			cprintf("have to be made before it is guessed.\n\r\n\r");
			cprintf("Default: 4");
			break;
		case 4:
			cprintf("Sets the maximum length for passwords and logins.\n\r\n\r");
			cprintf("Default: 20");
			break;
		case 5:
			cprintf("Sets the maximum times a user can attempt to log in before being\n\r");
			cprintf("locked out.\n\r");
			cprintf("NOTE: This should not be set too high. It is very rare for a\n\r");
			cprintf("legitimate user to botch a login attempt 3 times in a row. A\n\r");
			cprintf("potential intruder will usually have to make many attempts before\n\r");
			cprintf("getting anywhere. Setting MaxTries to around 3 will slow him down\n\r");
			cprintf("greatly, as he will have to reset after 3 failed attempts.\n\r\n\r");
			cprintf("Default: 3");
			break;
		case 6:
			cprintf("Sets the delay in seconds to wait after the user fails to log in.\n\r");
			cprintf("NOTE: Setting the WaitTime to 3 or above greatly slows any\n\r");
			cprintf("methodical attempt to guess or discover passwords. It offers little\n\r");
			cprintf("inconvenience to the end users while providing added security.\n\r\n\r");
			cprintf("Default: 3");
			break;
		case 7:
			cprintf("Sets the \"key\" to enter as a password to change passwords.\n\r\n\r");
			cprintf("Default: passwd");
			qu=3;
			break;
		case 8:
			cprintf("Sets the number of days a password is good before it expires.\n\r");
			cprintf("NOTE: It is a good idea to have PasswordExpiresIn set to between 180\n\r");
			cprintf("and 365. Anything over a year is a security risk due to age.\n\r");
			cprintf("Anything under half a year is a risk because people will tend to\n\r");
			cprintf("forget their passwords and start writing them down. This setting\n\r");
			cprintf("should depend on how busy your system generally is.\n\r\n\r");
			cprintf("Default: 365");
			break;
		case 9:
			cprintf("This sets the amount of time (in seconds) that may pass before the\n\r");
			cprintf("screen saver is activated.\n\r\n\r");
			cprintf("Default: 300");
			break;
		case 10:
			cprintf("This sets the value of the prompt that is displayed when the user is\n\r");
			cprintf("expected to enter their login name. Modifying this allows you\n\r");
			cprintf("to customize your environment as you see fit.\n\r\n\r");
			cprintf("Default: \"Login:\"");
			qu=2;
			break;
		case 11:
			cprintf("This sets the value of the prompt that is displayed when the user is\n\r");
			cprintf("expected to enter their password. Modifying this allows you\n\r");
			cprintf("to customize your environment as you see fit.\n\r\n\r");
			cprintf("Default: \"Password:\"");
			qu=2;
			break;
		case 12:
			cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
			cprintf("password.\n\r");
			cprintf("NOTE: It is a good idea to keep WrongPassword and WrongLogin the\n\r");
			cprintf("same. Otherwise, a potential intruder will know when he has found\n\r");
			cprintf("an account (IE: If Sentry responds with \"Invalid Password\" he\n\r");
			cprintf("knows the login was correct). Keeping the two the same prevents an\n\r");
			cprintf("attacker from knowing if he even has the correct login.\n\r\n\r");
			cprintf("Default: \"Invalid Login.\"");
			qu=2;
			break;
		case 13:
			cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
			cprintf("login.\n\r\n\r");
			cprintf("Default: \"Invalid Login.\"");
			qu=2;
			break;
		case 14:
			cprintf("This sets the message to be displayed when a user enters a password\n\r");
			cprintf("of invalid length.\n\r");
			cprintf("NOTE: It is also wise to keep PasswordLength and LoginLength the\n\r");
			cprintf("same as WrongPassword and WrongLogin. This will prevent a potential\n\r");
			cprintf("attacker from knowing how long a password or login is set to be on\n\r");
			cprintf("your system. (Knowing the length of a password can greatly decrease\n\r");
			cprintf("the amount of time required to crack it).\n\r\n\r");
			cprintf("Default: \"Invalid Login.\"");
			qu=2;
			break;
		case 15:
			cprintf("This sets the message to be displayed when a user enters a login of\n\r");
			cprintf("invalid length.\n\r\n\r");
			cprintf("Default: \"Invalid Login.\"");
			qu=2;
			break;
		case 16:
			cprintf("This sets the message to be saved to the log file when a user enters\n\r");
			cprintf("the wrong password.\n\r\n\r");
			cprintf("Default: \"User entered the wrong password.\"");
			qu=2;
			break;
		case 17:
			cprintf("This sets the message to be saved to the log file when a user enters\n\r");
			cprintf("the wrong login.\n\r\n\r");
			cprintf("Default: \"User entered the wrong login.\"");
			qu=2;
			break;
		case 18:
			cprintf("This sets the message to be saved to the log file when a user enters\n\r");
			cprintf("a password of invalid length.\n\r\n\r");
			cprintf("Default: \"Invalid Password Length.\"");
			qu=2;
			break;
		case 19:
			cprintf("This sets the message to be saved to the log file when a user enters\n\r");
			cprintf("a login of invalid length.\n\r\n\r");
			cprintf("Default: \"Invalid Login Length.\"");
			qu=2;
			break;
		case 20:
			cprintf("This sets the environment variable used to store the user's login name\n\r");
			cprintf("after a successful login.\n\r\n\r");
			cprintf("Default: \"USER\"");
			qu=2;
			break;
		case 21:
			cprintf("The Windows flag is set if you wish to run Sentry from Windows.\n\r");
			cprintf("Technically, this allows Sentry to open up a DOS shell after a\n\r");
			cprintf("successful login. Setting this option to 1 has no effect on normal\n\r");
			cprintf("use, and is not a security risk.\n\r");
			cprintf("(0=Do Not Run In Windows, 1=Run In Windows)\n\r\n\r");
			cprintf("Default: 1");
			break;
		case 22:
			cprintf("This determines if the intro screen is displayed or not. You may\n\r");
			cprintf("choose not to display the title information if you don't want users\n\r");
			cprintf("to know what program you are using. On the other hand, the\n\r");
			cprintf("registration information sould be displayed for authenticity's\n\r");
			cprintf("sake. I have added this option because security comes before all\n\r");
			cprintf("else.\n\r");
			cprintf("(0=Not Displayed, 1=Displayed)\n\r\n\r");
			cprintf("Default: 1");
			break;
		case 23:
			cprintf("This will allow you to have dates displayed in different formats.\n\r");
			cprintf("Some people prefer different formats than others, so this will allow\n\r");
			cprintf("you to define the way dates are displayed.\n\r");
			cprintf("(0=MM/DD/YYYY, 1=DD/MM/YYYY)\n\r\n\r");
			cprintf("Default: 1");
			break;
		case 24:
			cprintf("This sets the case sensitivity. If \"Case Insensitive\" is selected,\n\r");
			cprintf("\"Sentry\" \"sentry\" and \"SENTRY\" are all treated as the same at\n\r");
			cprintf("the login prompt. If case sensitivity is enabled, the three are all\n\r");
			cprintf("treated as different logins.\n\r");
			cprintf("(0=Case Sensitive, 1=Case Insensitive)\n\r");
			cprintf("NOTE: Using \"Case Insensitive\" reduces the number of allowable\n\r");
			cprintf("logins, and increases the probability of an attacker getting a\n\r");
			cprintf("correct login. Still, some people find it easier to work with Case\n\r");
			cprintf("Sensitivity off.\n\r");
			cprintf("Default: 0");
			break;
		case 25:
			cprintf("This allows you to use Sentry in a \"windowed\" mode (not to be\n\r");
			cprintf("confused with MicroSoft Windows). If the windowed mode is\n\r");
			cprintf("undesirable, you can choose not to use it.\n\r");
			cprintf("(0=Regular Mode, 1=Windowed Mode)\n\r\n\r");
			cprintf("Default: 1");
			break;
		case 26:
			cprintf("This determines if colour will be displayed by Sentry or not. Some\n\r");
			cprintf("laptop users may wish to use the black and white setting for better\n\r");
			cprintf("readability.\n\r");
			cprintf("(0=Black and White, 1=Colour)\n\r\n\r");
			cprintf("Default: 1");
			break;
		case 27:
			cprintf("You can set TextColour to the value of the colour you wish normal\n\r");
			cprintf("text to appear in. Colour values are shown in the chart below.\n\r\n\r");
			cprintf("COLOURS:\n\r");
			cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
			cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
			cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
			cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
		 cprintf("Default: 15");
			break;
		case 28:
			cprintf("You can set TextBackground to the value of the colour you wish\n\r");
			cprintf("normal text to have as a background. Colour values are shown in the\n\r");
			cprintf("chart below.\n\r\n\r");
			cprintf("COLOURS:\n\r");
			cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
			cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
			cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
			cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
			cprintf("Default: 1");
			break;
		case 29:
			cprintf("You can set TextColour to the value of the colour you wish\n\r");
			cprintf("highlighted text to appear in. Colour values are shown in the\n\r");
			cprintf("chart below.\n\r\n\r");
			cprintf("COLOURS:\n\r");
			cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
			cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
			cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
			cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
			cprintf("Default: 14");
			break;
		case 30:
			cprintf("You can set HighBackground to the value of the colour you wish\n\r");
			cprintf("highlighted text to have as a background. Colour values are shown\n\r");
			cprintf("in the chart below.\n\r\n\r");
			cprintf("COLOURS:\n\r");
			cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
			cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
			cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
			cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
			cprintf("Default: 4");
			break;
		case 31:
			cprintf("This sets the default number of consecutive invalid logins possible\n\r");
			cprintf("before an account is locked out. Only a SuperUser can subsequently\n\r");
			cprintf("unlock an account.\n\r\n\r");
			cprintf("Default: 10");
			break;
		default:
			cprintf("No information available.");
			break;
	}
	cprintf("\n\r\n\rCurrent Value: %s\n\r\n\r",cv);
	_bk=1;
	tv=max;
	max=MAX;
	strcpy(cv,gin("New Value (ENTER Aborts):",1));
	max=tv;
	if ((strlen(cv)!=0) && (!bk))
	{
		switch (qu)
		{
			case 0:  /*Number*/
				qu=0;
				for(tv=0;tv<strlen(cv);tv++)
					if (!isdigit(cv[tv]))
					qu++;
					if (qu)
					{
						cprintf("\n\rPlease enter a numeric value.\n\r\n\rPress any key to try again...\n\r");
						bk=blch();
					}
					qu=0;
				break;
			case 1:  /*Path*/
				if ((ini=fopen(cv,"r"))==NULL)
				{
					cprintf("\n\rPlease enter a valid path.\n\r\n\rPress any key to try again...\n\r");
					bk=blch();
				}
				fclose(ini);
				break;
			case 2:  /*Quote delimited string*/
				if (cv[0]!='\"')
					strcpy(cv,strcat(strcpy(temp,"\""),cv));
				if (cv[strlen(cv)-1]!='\"')
					strcat(cv,"\"");
				break;
			case 3:  /*Single Word*/
				if (strchr(cv,' ')!=NULL)
				{
					cprintf("\n\rPlease enter a single word. (No spaces)\n\r\n\rPress any key to try again...\n\r");
					bk=blch();
				}
				break;
		}
	}
	if ((strlen(cv)!=0) && (!bk))
	{
		strcpy(cv,strcat(strcat(strcat(strcpy(temp,ia),"="),cv),"\n"));
		if ((ini=fopen(inam,"r"))==NULL)
			error("Error opening Sentry.ini file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		strcpy(lo,"");
		while (fgets(lo,MAX,ini)!=NULL)
		{
			if (!strncmp(ia,lo,strlen(ia)-1))
			{
				fprintf(npas,"%s",cv);
				strcpy(na,cv);
				na[strlen(na)-1]=0;
				sprintf(tol,"Setting Modified: %s",na);
				tolog(tol);
			}
			else
				fprintf(npas,"%s",lo);
		}
		fclose(ini);
		fclose(npas);
		unlink(inam);
		rename(temp,inam);
	}
	else
	{
		fclose(ini);
		fclose(npas);
		unlink(temp);
	}
d1446 4
a1449 4
	suinit(void) initializes the menu options in the string txt[]. This is
	done seperately from the super(void) function so that it can be
	performed as required. view(void) also uses the txt[] variable, so
	suinit(void) must be called after each call to view(void).
d1452 12
a1463 12
	strcpy(txt[1],"1. Create User");
	strcpy(txt[2],"2. Delete User");
	strcpy(txt[3],"3. View All Users");
	strcpy(txt[4],"4. Toggle SuperUser Status");
	strcpy(txt[5],"5. Change Account Expiry Date");
	strcpy(txt[6],"6. Change Password Expiry Date");
	strcpy(txt[7],"7. View Log File");
	strcpy(txt[8],"8. Change Account Password");
	strcpy(txt[9],"9. Assign Max Number of Invalid Logins");
	strcpy(txt[10],"0. Edit Initialization settings");
	strcpy(txt[11],"X. Exit");
	crwin(4,6,47,23,tf,tb,1);
d1468 5
a1472 5
	super() is the function called when a SuperUser logs in and wishes to
	invoke the SuperUser menu (CTRL-enter on login). super() allows the user
	to select an option in much the same way as view() except they can also
	select by option number. Control of the program is subsequently passed
	to the appropriate function.
d1477 63
a1539 63
	cprintf("\n\r   Press any key to continue...\n\r");
	opt=blch();
	suinit();
	y=opt=0;
	while ((opt > '0') || (opt < '1')) /* Change SUOPT here */
	{
		clrscr();
		txb(tb);
		txc(tf);
		cprintf("   SuperUser Menu\n\r\n\r");
		for(x=1;x<=SUOPT;x++)
		{
			if (sel==x)
			{
				txb(hb);
				txc(hf);
			}
			else
			{
				txb(tb);
				txc(tf);
			}
			cprintf("%s\n\r",txt[x]);
		}
		txb(tb);
		txc(tf);
		cprintf("\n\rOption: ");
		opt=blch();
		switch (opt)
		{
			case 13:
				switch (sel)
				{
					case 1:
						creat();
						y=1;
						break;
					case 2:
						del();
						y=1;
						break;
					case 3:
						tolog("User List Viewed.");
						view();
						y=1;
						break;
					case 4:
						toggle();
						y=1;
						break;
					case 5:
						cex();
						y=1;
						break;
					case 6:
						pex();
						y=1;
						break;
					case 7:
						vlog();
						y=1;
						break;
					case 8:
d1541 92
a1632 86
						crwin(2,5,65,22,tf,tb,2);
						if (!wm)
							clrscr();
						setp();
						y=1;
						break;
					case 9:
						alock();
						y=1;
						break;
					case 10:
						iset();
						y=1;
						break;
					case SUOPT:
						su=sul=1;
						fin(0);
						break;
				}
				break;
			case 77:
			case 80:
				if (sel<SUOPT)
					sel++;
				break;
			case 75:
			case 72:
				if (sel>1)
					sel--;
				break;
			case '1':
				creat();
				y=1;
				break;
			case '2':
				del();
				y=1;
				break;
			case '3':
				tolog("User List Viewed.");
				view();
				y=1;
				break;
			case '4':
				toggle();
				y=1;
				break;
			case '5':
				cex();
				y=1;
				break;
			case '6':
				pex();
				y=1;
				break;
			case '7':
				vlog();
				y=1;
				break;
			case '8':
				un=view()*-1;
				crwin(2,5,65,22,tf,tb,2);
				if (!wm)
					clrscr();
				setp();
				y=1;
				break;
			case '9':
				alock();
				y=1;
				break;
			case '0':
				iset();
				y=1;
				break;
			case 'x':
			case 'X':
			case 27:
				su=sul=1;
				fin(0);
				break;
		}
		if (y)
			suinit();
		y=opt=0;
	}
@


2.5
log
@Super.c for Sentry V2.5.
@
text
@d3 3
a5 3
  cpass(void) is the function called when a user wishes to change his
  password. cpass(void) requires the user to enter their old password
  (as verification), and then calls setp(void) to set the new password.
d9 63
a71 63
  while (err)
  {
    err=0;
    _bk=0;
    strcpy(pa,gin("\n\rOld Password:",0));
    strcpy(temp,pa);
    temp[strlen(temp)+1]=0;
    temp[strlen(temp)]=STAMP;
    if ((strlen(pa)>max) || (strlen(pa)<min))
      err=2;
    strcpy(temp,penc(temp));
    strcpy(pa,penc(pa));
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    if (!err)
      err=4;
    while((fgets(lo,MAX,pass))!=NULL)
    {
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      lo[strlen(lo)-1]=0;
      ps[strlen(ps)-1]=0;
      if (ps[strlen(ps)-1]==STAMP)
      {
        ps[strlen(ps)-1]=0;
      }
      if (err==4)
      {
        if (csck(na,lo))
        {
          err=0;
          sprintf(tol,"%s is changing passwords.",na);
          tolog(tol);
          if (strcmp(pa,ps))
          {
            if (strcmp(temp,ps))
              err=3;
          }
        }
      }
    }
    switch (err)
    {
    case 2:
      cprintf("%s\n\r",xplen);
      tolog(lxplen);
      sleep(wait);
      break;
    case 3:
      cprintf("%s\n\r",xpwd);
      tolog(lxpwd);
      sleep(wait);
      break;
    case 4:
      cprintf("%s\n\r",xlog);
      tolog(lxlog);
      sleep(wait);
      break;
    }
    fclose(pass);
  }
  un*=-1;
  setp();
d76 7
a82 7
  view() displays a list of all current users in the password file.
  SuperUsers are denoted with a * to the right of their name. The cursor
  keys are used to highlight a user, and the enter key will select that
  user. The PAGE UP and PAGE DOWN keys can be used to show more screens
  if they are available.
  view() returns the ordinal value of the user selected (as per the
  password file) as an integer.
d88 200
a287 200
  if ((pass=fopen(ipas,"r"))==NULL)
    error("Error opening password file!");
  x=0;
  crwin(1,1,79,24,tf,tb,1);
  while((fgets(lo,MAX,pass))!=NULL)
  {
    x++;
    if (x<MAXUSER)
    {
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      lo[strlen(lo)-1]=0;
      ps[strlen(ps)-1]=0;
      if (ps[strlen(ps)-1]==STAMP)
      {
        strcat(lo," *");
      }
      if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
      {
        if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
          error("Error in time stamps.");
        else
        {
          fla=0;
          ntl=ltl;
        }
      }
      strcpy(txt[x],lo);
      for(y=strlen(lo);y<LLST;y++)
        strcat(txt[x]," ");
      unixtodos(ut,&td,&nw);
      if (df)
        sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
      else
        sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
      strcat(txt[x],lo);
      sprintf(lo," %02d:%02d:%02d",nw.ti_hour,nw.ti_min,nw.ti_sec);
      strcat(txt[x],lo);
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<AEST;y++)
        strcat(txt[x]," ");
      if (ed)
      {
        unixtodos(ed,&td,&nw);
        if (df)
          sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
        strcat(txt[x],lo);
      }
      else
        strcat(txt[x]," * NONE *");
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<PEST;y++)
        strcat(txt[x]," ");
      if (pe)
      {
        unixtodos(pe,&td,&nw);
        if (df)
          sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
        strcat(txt[x],lo);
      }
      else
        strcat(txt[x]," * NONE *");
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<ILST;y++)
        strcat(txt[x]," ");
      sprintf(lo,"%d",fla);
      strcat(txt[x],lo);
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<NLST;y++)
        strcat(txt[x]," ");
      if (ntl)
        sprintf(lo,"%d",ntl);
      else
        strcpy(lo,"X");
      strcat(txt[x],lo);
    }
    else
      cprintf("Maximum number of users exceeded! (MAXUSER=%d)",MAXUSER);
  }
  fclose(pass);
  while (1)
  {
    txb(tb);
    txc(tf);
    clrscr();
    cprintf("Current Users (ESC exits)\n\r\n\r");
    if (!tp)
      cprintf("\n\r");
    strcpy(lo,"User Name");
    strcpy(pa,lo);
    for(y=strlen(pa);y<LLST;y++)
      strcat(lo," ");
    strcat(lo,"Last Login");
    strcpy(pa,lo);
    for(y=strlen(pa);y<AEST;y++)
      strcat(lo," ");
    strcat(lo,"Acct Expiry");
    strcpy(pa,lo);
    for(y=strlen(pa);y<PEST;y++)
      strcat(lo," ");
    strcat(lo,"Passwd Exp");
    strcpy(pa,lo);
    for(y=strlen(pa);y<ILST-2;y++)
      strcat(lo," ");
    strcat(lo,"Inv Log");
    strcpy(pa,lo);
    for(y=strlen(pa);y<NLST-2;y++)
      strcat(lo," ");
    strcat(lo,"Max InvLog");
    cprintf("%s\n\r",lo);
    for(y=0;y<(NLST+6);y++)
      cprintf("-");
    if (tp>0)
    {
      gotoxy(NLST+4,2);
      cprintf("");
    }
    cprintf("\n\r");
    if (tp)
      cprintf("\n\r\n\r");
    for(y=tp;y<WIND+tp;y++)
    {
      if (y<=x)
      {
        if (sel==(y % WIND))
        {
          txb(hb);
          txc(hf);
        }
        else
        {
          txb(tb);
          txc(tf);
        }
        if (y)
          cprintf("%s\n\r",txt[y]);
      }
    }
    txb(tb);
    txc(tf);
    if (tp+WIND<=x)
    {
      gotoxy(NLST+4,21);
      cprintf("");
    }
    gotoxy(1,22);
    cprintf("Select a user: ");
    opt=getch();
    switch (opt)
    {
      case 13:
        return(sel+tp);
      case 77:
      case 80:
        if ((sel<(WIND-1)) && ((sel+tp)<x))
          sel++;
        else
        if ((sel+tp)<x)
        {
          tp+=WIND;
          sel=0;
        }
        break;
      case 72:
      case 75:
        if ((sel>1) || ((sel>0) && (tp>0)))
          sel--;
        else
        if (tp>0)
        {
          tp-=WIND;
          sel=WIND-1;
        }
        break;
      case 73:
        if (tp>0)
        {
          tp-=WIND;
          if (!sel)
            sel=1;
        }
        else
          sel=1;
        break;
      case 81:
        if ((tp+WIND)<=x)
          tp+=WIND;
        else
          sel=x-tp;
        if (!((sel+tp)<=x))
          sel=x-tp;
        break;
      case 27:
        return(0);
    }
  }
d292 3
a294 3
  creat() is the function used to create a new user. This function is
  called only from the SuperUser menu. All normal verifying is performed
  before the user information is saved.
d300 110
a409 110
  sul=0;
  crwin(2,5,65,22,tf,tb,2);
  if (!wm)
    clrscr();
  while (err>0)
  {
    err=0;
    cprintf("\n\r\n\rCreate User.\n\r\n\r");
    _bk=1;
    strcpy(na,gin("Login:",1));
    strcpy(temp,na);
    if (bk)
      break;
    if ((strlen(temp)>max) || (strlen(temp)<min))
      err=1;
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      lo[strlen(lo)-1]=0;
      if (csck(temp,lo))
        if (err==0)
          err=4;
    }
    if (!err)
    {
      fclose(pass);
      if ((pass=fopen(ipas,"a"))==NULL)
        error("Error opening password file!");
      _bk=1;
      strcpy(pa,gin("Password:",0));
      if (bk)
        break;
      if ((strlen(pa)>max) || (strlen(pa)<min))
        err=2;
      if (!err)
      {
        if (sul)
        {
          pa[strlen(pa)+1]=0;
          pa[strlen(pa)]=STAMP;
        }
        strcpy(pa,penc(pa));
        _bk=1;
        strcpy(ps,gin("Verify Password:",0));
        if (bk)
          break;
        if (sul)
        {
          ps[strlen(ps)+1]=0;
          ps[strlen(ps)]=STAMP;
        }
        strcpy(ps,penc(ps));
        if (strcmp(pa,ps))
          err=3;
        if (!err)
        {
          if (sul)
          {
            pa[strlen(pa)+1]=0;
            pa[strlen(pa)]=STAMP;
          }
          cprintf("Do you want this account to have an expiry date? ");
          opt=getch();
          if ((opt=='y') || (opt=='Y'))
            ed=gdate();
          else
            ed=0;
          cprintf("\n\rDo you want the password to have an expiry date? ");
          opt=getch();
          if ((opt=='y') || (opt=='Y'))
            pe=gdate();
          else
            pe=0;
          cprintf("\n\r");
        }
      }
    }
    switch (err)
    {
    case 1:
      cprintf("Logins must be between %d and %d characters.\n\r",min,max);
      break;
    case 2:
      cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
      break;
    case 3:
      cprintf("Password not verified!\n\r");
      break;
    case 4:
      cprintf("That user already exists!\n\r");
      break;
    }
    if (!err)
    {
      sprintf(tol,"User %s Created.",na);
      tolog(tol);
      fprintf(pass,"%s\n",na);
      fprintf(pass,"%s\n",pa);
      getdate(&td);
      gettime(&nw);
      ut=dostounix(&td,&nw);
      fla=0;
      ntl=ltl;
      fprintf(pass,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
    }
    fclose(pass);
  }
d414 4
a417 4
  del() is the function called to delete a user. It is called only from
  the SuperUser menu. It first calls view() so that the intended user
  can be selected. A check is performed to make sure that the last
  SuperUser listed in the password file is not being deleted.
d422 71
a492 71
  x=view();
  crwin(2,7,60,17,tf,tb,2);
  if (!wm)
    clrscr();
  if (x)
  {
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    opt=0;
    while((fgets(lo,MAX,pass))!=NULL)
    {
      fgets(ps,MAX,pass);
      if (ps[strlen(ps)-2]==STAMP)
        opt++;
      fgets(ti,MAX,pass);
    }
    fclose(pass);
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      na[strlen(na)-1]=0;
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-2]==STAMP)
        {
          cprintf("\n\rThis is a SuperUser!");
        }
        if ((opt==1) && (ps[strlen(ps)-2]==STAMP))
        {
          cprintf("\n\rYou cannot delete this user, they are the last SuperUser!");
          cprintf("\n\r\n\rPress any key to return to the SuperUser menu...");
          opt=getch();
          opt=0;
        }
        else
        {
          cprintf("\n\r\n\rAre you sure you want to delete %s? ",na);
          opt=getch();
        }
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          sprintf(tol,"User %s Deleted.",na);
          tolog(tol);
        }
      }
    }
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
  }
d497 4
a500 4
  toggle() is the function called to toggle SuperUser status. It is
  called only from the SuperUser menu. It first calls view() so that the
  intended user can be selected. The user's password must be entered
  to replace the old password and access group.
d505 124
a628 124
  v=view();
  crwin(2,5,69,22,tf,tb,2);
  if (!wm)
    clrscr();
  if (v)
  {
    cprintf("NOTE: The user must re-enter their password to obtain or give up\n\r");
    cprintf("      SuperUser access.\n\r");
    cprintf("      You may override this by entering any other password, which\n\r");
    cprintf("      will be this user's password from now on.\n\r");
    cprintf("\n\r\n\rIS THIS OK? ");
    opt=getch();
    if ((opt=='y') || (opt=='Y'))
    {
      if ((pass=fopen(ipas,"r"))==NULL)
        error("Error opening password file!");
      tmpnam(temp);
      if ((npas=fopen(temp,"w"))==NULL)
        error("Error opening temp file!");
      while((fgets(lo,MAX,pass))!=NULL)
      {
        strcpy(na,lo);
        na[strlen(na)-1]=0;
        y++;
        fgets(ps,MAX,pass);
        fgets(ti,MAX,pass);
        if (y!=v)
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          ps[strlen(ps)-1]=0;
          sul=0;
          cprintf("\n\r\n\rAre you sure you want to ");
          if (ps[strlen(ps)-1]==STAMP)
            cprintf("remove SuperUser access from");
          else
          {
            cprintf("grant SuperUser access to");
            sul=1;
          }
          cprintf(" %s? ",na);
          opt=getch();
          if ((opt=='y') || (opt=='Y'))
          {
            _bk=0;
            strcpy(pa,gin("\n\r\n\rPassword:",0));
            if ((strlen(pa)>max) || (strlen(pa)<min))
            {
              cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
              cprintf("\n\rPress any key to continue...");
              opt=getch();
              err=2;
            }
            if (!err)
            {
              if (sul)
              {
                pa[strlen(pa)+1]=0;
                pa[strlen(pa)]=STAMP;
              }
              strcpy(pa,penc(pa));
              _bk=0;
              strcpy(na,gin("Verify Password:",0));
              if (sul)
              {
                na[strlen(na)+1]=0;
                na[strlen(na)]=STAMP;
              }
              strcpy(na,penc(na));
              if (strcmp(pa,na))
              {
                cprintf("Password not verified!\n\r");
                cprintf("\n\rPress any key to continue...");
                opt=getch();
                err=3;
              }
              if (!sul)
              {
                na[strlen(na)+1]=0;
                na[strlen(na)]='\n';
              }
              else
              {
                na[strlen(na)+2]=0;
                na[strlen(na)+1]='\n';
                na[strlen(na)]=STAMP;
              }
              if (!err)
              {
                strcpy(ps,na);
                strcpy(tol,"SuperUser Access ");
                if (sul)
                  strcat(tol,"Granted to");
                else
                  strcat(tol,"Revoked from");
                strcat(tol," user ");
                strcpy(na,lo);
                na[strlen(na)-1]=0;
                strcat(tol,na);
                strcat(tol,".");
                tolog(tol);
              }
            }
            if (err)
            {
              ps[strlen(ps)+1]=0;
              ps[strlen(ps)]='\n';
            }
          }
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
      }
      fclose(pass);
      fclose(npas);
      unlink(ipas);
      rename(temp,ipas);
    }
  }
d633 5
a637 5
  cex(void) creates an expiry date for an account. The account to be
  adjusted is selected via view(void). That account's current expiry
  settings are then shown, and the user is asked if they want to alter
  them. If they answer yes, the date new expiry is entered via
  gdate(void) and saved in the password file.
d643 85
a727 85
  x=view();
  crwin(2,5,65,22,tf,tb,2);
  if (!wm)
    clrscr();
  if (x)
  {
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      na[strlen(na)-1]=0;
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-1]==STAMP)
          cprintf("\n\rThis is a SuperUser!\n\r");
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
        {
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
            error("Error in time stamps.");
          else
          {
            fla=0;
            ntl=ltl;
          }
        }
        if (ed)
        {
          unixtodos(ed,&td,&nw);
          if (df)
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
          else
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
          getdate(&td);
          gettime(&nw);
          zs=dostounix(&td,&nw);
          if (zs>ed)
            cprintf("(This account has expired.)\n\r");
        }
        else
          cprintf("This account has no expiry date.\n\r");
        cprintf("Do you want to change %s's expiry date? ",na);
        opt=getch();
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          ed=gdate();
          fputs(lo,npas);
          fputs(ps,npas);
          fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
          lo[strlen(lo)-1]=0;
          unixtodos(ed,&td,&nw);
          sprintf(tol,"User %s account expiry changed to ",lo);
          if (df)
            sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
          else
            sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
          strcat(tol,lo);
          strcat(tol,".");
          tolog(tol);
        }
      }
    }
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
  }
d732 5
a736 5
  pex(void) creates an expiry date for a password. The account to be
  adjusted is selected via view(void). That account's current password
  expiry settings are then shown, and the user is asked if they want to
  alter them. If they answer yes, the new expiry date is entered via
  gdate(void) and saved in the password file.
d742 85
a826 85
  x=view();
  crwin(2,5,65,22,tf,tb,2);
  if (!wm)
    clrscr();
  if (x)
  {
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      na[strlen(na)-1]=0;
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-1]==STAMP)
          cprintf("\n\rThis is a SuperUser!\n\r");
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
        {
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
            error("Error in time stamps.");
          else
          {
            fla=0;
            ntl=ltl;
          }
        }
        if (pe)
        {
          unixtodos(pe,&td,&nw);
          if (df)
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_day,td.da_mon,td.da_year);
          else
            cprintf("Current expiry date is %02d/%02d/%02d.\n\r",td.da_mon,td.da_day,td.da_year);
          getdate(&td);
          gettime(&nw);
          zs=dostounix(&td,&nw);
          if (zs>pe)
            cprintf("(This password has expired.)\n\r");
        }
        else
          cprintf("This password has no expiry date.\n\r");
        cprintf("Do you want to change %s's expiry date? ",na);
        opt=getch();
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          pe=gdate();
          fputs(lo,npas);
          fputs(ps,npas);
          fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
          lo[strlen(lo)-1]=0;
          unixtodos(pe,&td,&nw);
          sprintf(tol,"User %s password expiry changed to ",lo);
          if (df)
            sprintf(lo,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
          else
            sprintf(lo,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
          strcat(tol,lo);
          strcat(tol,".");
          tolog(tol);
        }
      }
    }
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
  }
d831 2
a832 2
  vlog is called when the user wishes to view the log file. They can purge
  the log after viewing if desired.
d836 50
a885 50
  tolog("Log File Viewed.");
  fclose(log);
  crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2);
  vl=VLBOT-VLTOP-VLCONST;
  if (!wm)
  {
    vl=VLFULL;
    clrscr();
  }
  if ((log=fopen(ilog,"r"))==NULL)
    error("Error opening log file!");
  while((fgets(temp,MAX,log))!=NULL)
  {
    x++;
    if (strlen(temp)>SCRWIDTH)
      x++;
    cprintf("%s\r",temp);
    if (x>vl)
    {
      cprintf("\n\r  Press a key to continue...");
      c=getch();
      cprintf("\n\r");
      x=0;
    }
    if (c==27)
      break;
  }
  fclose(log);
  if (c!=27)
  {
    cprintf("\n\r  Press a key to continue...");
    c=getch();
    cprintf("\n\r");
  }
  cprintf("\n\r Would you like to clear the log file [y/N]? ");
  c=getch();
  if ((c=='y') || (c=='Y'))
  {
    if ((log=fopen(ilog,"w"))==NULL)
      error("Error in creating log file!");
    cprintf("\n\r\n\r The log file has been cleared.\n\r");
    tolog("Log File Cleared.");
    cprintf("\n\r  Press a key to continue...");
    c=getch();
  }
  else
  {
    if ((log=fopen(ilog,"a"))==NULL)
      error("Error in creating log file!");
  }
d890 4
a893 4
  alock(void) allows accounts to be locked out after a certain number of
  sequential invalid logins. alock(void) calls view(void) first so the
  proper account can be selected. It then prompts the user for a new
  "max invalid login" value.
d899 81
a979 81
  x=view();
  crwin(2,5,65,22,tf,tb,2);
  if (!wm)
    clrscr();
  if (x)
  {
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      strcpy(na,lo);
      na[strlen(na)-1]=0;
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=x)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        if (ps[strlen(ps)-1]==STAMP)
          cprintf("\n\rThis is a SuperUser!\n\r");
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
        {
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
            error("Error in time stamps.");
          else
          {
            fla=0;
            ntl=ltl;
          }
        }
        if (ntl)
          cprintf("This account will currently lock up after %d invalid logins.\n\r",ntl);
        else
          cprintf("This account has no limit on invalid logins.\n\r");
        cprintf("Do you want to change %s's invalid login setting? ",na);
        opt=getch();
        if ((opt!='y') && (opt!='Y'))
        {
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          x=0;
          while (x==0)
          {
            x=1;
            cprintf("\n\r\n\rEnter 'N' or '0' to assign unlimited invalid logins.");
            cprintf("\n\rEnter the number of sequential invalid logins before the");
            cprintf("\n\ruser's account is automatically expired: ");
            scanf("%s",&ho);
            if ((streq(ho,"n")) || (streq(ho,"N")))
              ntl=0;
            else
            {
              ntl=atoi(ho);
            }
          }
          fputs(lo,npas);
          fputs(ps,npas);
          fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
          lo[strlen(lo)-1]=0;
          sprintf(tol,"%s's invalid login setting is changed to %d.",lo,ntl);
          tolog(tol);
        }
      }
    }
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
  }
d986 101
a1086 101
  for (x=0;x<INI;x++)
    strcpy(txt[x+1],is[x][0]);
  crwin(7,1,47,24,tf,tb,1);
  x=INI;
  while (1)
  {
    txb(tb);
    txc(tf);
    clrscr();
    cprintf("Current Settings (ESC exits)\n\r\n\r");
    if (!tp)
      cprintf("\n\r");
    if (tp>0)
    {
      gotoxy(30,2);
      cprintf("");
    }
    cprintf("\n\r");
    if (tp)
      cprintf("\n\r\n\r");
    for(y=tp;y<WIND+tp;y++)
    {
      if (y<=x)
      {
        if (sel==(y % WIND))
        {
          txb(hb);
          txc(hf);
        }
        else
        {
          txb(tb);
          txc(tf);
        }
        if (y)
          cprintf("%s\n\r",txt[y]);
      }
    }
    txb(tb);
    txc(tf);
    if (tp+WIND<=x)
    {
      gotoxy(30,21);
      cprintf("");
    }
    gotoxy(1,22);
    cprintf("Select a setting: ");
    opt=getch();
    switch (opt)
    {
      case 13:
        iedit(sel+tp-1);
        crwin(7,1,47,24,tf,tb,1);
        break;
      case 77:
      case 80:
        if ((sel<(WIND-1)) && ((sel+tp)<x))
          sel++;
        else
        if ((sel+tp)<x)
        {
          tp+=WIND;
          sel=0;
        }
        break;
      case 72:
      case 75:
        if ((sel>1) || ((sel>0) && (tp>0)))
          sel--;
        else
        if (tp>0)
        {
          tp-=WIND;
          sel=WIND-1;
        }
        break;
      case 73:
        if (tp>0)
        {
          tp-=WIND;
          if (!sel)
            sel=1;
        }
        else
          sel=1;
        break;
      case 81:
        if ((tp+WIND)<=x)
          tp+=WIND;
        else
          sel=x-tp;
        if (!((sel+tp)<=x))
          sel=x-tp;
        break;
      case 27:
        x=-1;
        break;
    }
    if (x<0)
      break;
  }
d1093 1
a1093 1
  strcpy(ia,is[set][1]);
d1097 1
a1097 1
  getini();
d1099 1
a1099 1
  {
d1101 1
a1101 1
    {
d1104 1
a1104 1
      cv[tv]=0;
d1106 8
a1113 8
    }
    else
      getini();
  }
  fclose(ini);
  crwin(3,2,73,22,tf,tb,2);
  if (!wm)
    clrscr();
d1116 9
a1124 9
  switch (set+1)
  {
    case 1:
      cprintf("This contains the location of the password file. The password file\n\r");
      cprintf("should be kept somewhere safe, tucked away from prying eyes.\n\r");
      cprintf("NOTE: You should change the name of the file from Sentry.pwd to some\n\r");
      cprintf("other, inconspicuous name. Potential intruders will search for the\n\r");
      cprintf("Sentry.pwd file. You can hide it under misleading names such as\n\r");
      cprintf("file_id.diz, chklist.ms, warm.com etc etc.\n\r\n\r");
d1128 3
a1130 3
    case 2:
      cprintf("This contains the location of the log file. The log file\n\r");
      cprintf("should also be hidden away in the same manner described above.\n\r\n\r");
d1133 32
a1164 32
      break;
    case 3:
      cprintf("Sets the minimum length for passwords and logins.\n\r");
      cprintf("NOTE: A value of 4 should be the absolute minimum for\n\r");
      cprintf("MinPasswordLen. A value of 5 or 6 would be even better. Short\n\r");
      cprintf("passwords are much easier to stumble across since less attempts\n\r");
      cprintf("have to be made before it is guessed.\n\r\n\r");
      cprintf("Default: 4");
      break;
    case 4:
      cprintf("Sets the maximum length for passwords and logins.\n\r\n\r");
      cprintf("Default: 20");
      break;
    case 5:
      cprintf("Sets the maximum times a user can attempt to log in before being\n\r");
      cprintf("locked out.\n\r");
      cprintf("NOTE: This should not be set too high. It is very rare for a\n\r");
      cprintf("legitimate user to botch a login attempt 3 times in a row. A\n\r");
      cprintf("potential intruder will usually have to make many attempts before\n\r");
      cprintf("getting anywhere. Setting MaxTries to around 3 will slow him down\n\r");
      cprintf("greatly, as he will have to reset after 3 failed attempts.\n\r\n\r");
      cprintf("Default: 3");
      break;
    case 6:
      cprintf("Sets the delay in seconds to wait after the user fails to log in.\n\r");
      cprintf("NOTE: Setting the WaitTime to 3 or above greatly slows any\n\r");
      cprintf("methodical attempt to guess or discover passwords. It offers little\n\r");
      cprintf("inconvenience to the end users while providing added security.\n\r\n\r");
      cprintf("Default: 3");
      break;
    case 7:
      cprintf("Sets the \"key\" to enter as a password to change passwords.\n\r\n\r");
d1167 37
a1203 18
      break;
    case 8:
      cprintf("Sets the number of days a password is good before it expires.\n\r");
      cprintf("NOTE: It is a good idea to have PasswordExpiresIn set to between 180\n\r");
      cprintf("and 365. Anything over a year is a security risk due to age.\n\r");
      cprintf("Anything under half a year is a risk because people will tend to\n\r");
      cprintf("forget their passwords and start writing them down. This setting\n\r");
      cprintf("should depend on how busy your system generally is.\n\r\n\r");
      cprintf("Default: 365");
      break;
    case 9:
      cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
      cprintf("password.\n\r");
      cprintf("NOTE: It is a good idea to keep WrongPassword and WrongLogin the\n\r");
      cprintf("same. Otherwise, a potential intruder will know when he has found\n\r");
      cprintf("an account (IE: If Sentry responds with \"Invalid Password\" he\n\r");
      cprintf("knows the login was correct). Keeping the two the same prevents an\n\r");
      cprintf("attacker from knowing if he even has the correct login.\n\r\n\r");
d1206 4
a1209 4
      break;
    case 10:
      cprintf("This sets the message to be displayed when a user enters the wrong\n\r");
      cprintf("login.\n\r\n\r");
d1212 9
a1220 9
      break;
    case 11:
      cprintf("This sets the message to be displayed when a user enters a password\n\r");
      cprintf("of invalid length.\n\r");
      cprintf("NOTE: It is also wise to keep PasswordLength and LoginLength the\n\r");
      cprintf("same as WrongPassword and WrongLogin. This will prevent a potential\n\r");
      cprintf("attacker from knowing how long a password or login is set to be on\n\r");
      cprintf("your system. (Knowing the length of a password can greatly decrease\n\r");
      cprintf("the amount of time required to crack it).\n\r\n\r");
d1223 4
a1226 4
      break;
    case 12:
      cprintf("This sets the message to be displayed when a user enters a login of\n\r");
      cprintf("invalid length.\n\r\n\r");
d1229 4
a1232 4
      break;
    case 13:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("the wrong password.\n\r\n\r");
d1235 4
a1238 4
      break;
    case 14:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("the wrong login.\n\r\n\r");
d1241 4
a1244 4
      break;
    case 15:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("a password of invalid length.\n\r\n\r");
d1247 4
a1250 4
      break;
    case 16:
      cprintf("This sets the message to be saved to the log file when a user enters\n\r");
      cprintf("a login of invalid length.\n\r\n\r");
d1253 77
a1329 71
      break;
    case 17:
      cprintf("The Windows flag is set if you wish to run Sentry from Windows.\n\r");
      cprintf("Technically, this allows Sentry to open up a DOS shell after a\n\r");
      cprintf("successful login. Setting this option to 1 has no effect on normal\n\r");
      cprintf("use, and is not a security risk.\n\r");
      cprintf("(0=Do Not Run In Windows, 1=Run In Windows)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 18:
      cprintf("This determines if the intro screen is displayed or not. You may\n\r");
      cprintf("choose not to display the title information if you don't want users\n\r");
      cprintf("to know what program you are using. On the other hand, the\n\r");
      cprintf("registration information sould be displayed for authenticity's\n\r");
      cprintf("sake. I have added this option because security comes before all\n\r");
      cprintf("else.\n\r");
      cprintf("(0=Not Displayed, 1=Displayed)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 19:
      cprintf("This will allow you to have dates displayed in different formats.\n\r");
      cprintf("Some people prefer different formats than others, so this will allow\n\r");
      cprintf("you to define the way dates are displayed.\n\r");
      cprintf("(0=MM/DD/YYYY, 1=DD/MM/YYYY)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 20:
      cprintf("This sets the case sensitivity. If \"Case Insensitive\" is selected,\n\r");
      cprintf("\"Sentry\" \"sentry\" and \"SENTRY\" are all treated as the same at\n\r");
      cprintf("the login prompt. If case sensitivity is enabled, the three are all\n\r");
      cprintf("treated as different logins.\n\r");
      cprintf("(0=Case Sensitive, 1=Case Insensitive)\n\r");
      cprintf("NOTE: Using \"Case Insensitive\" reduces the number of allowable\n\r");
      cprintf("logins, and increases the probability of an attacker getting a\n\r");
      cprintf("correct login. Still, some people find it easier to work with Case\n\r");
      cprintf("Sensitivity off.\n\r");
      cprintf("Default: 0");
      break;
    case 21:
      cprintf("This allows you to use Sentry in a \"windowed\" mode (not to be\n\r");
      cprintf("confused with MicroSoft Windows). If the windowed mode is\n\r");
      cprintf("undesirable, you can choose not to use it.\n\r");
      cprintf("(0=Regular Mode, 1=Windowed Mode)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 22:
      cprintf("This determines if colour will be displayed by Sentry or not. Some\n\r");
      cprintf("laptop users may wish to use the black and white setting for better\n\r");
      cprintf("readability.\n\r");
      cprintf("(0=Black and White, 1=Colour)\n\r\n\r");
      cprintf("Default: 1");
      break;
    case 23:
      cprintf("You can set TextColour to the value of the colour you wish normal\n\r");
      cprintf("text to appear in. Colour values are shown in the chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
     cprintf("Default: 15");
      break;
    case 24:
      cprintf("You can set TextBackground to the value of the colour you wish\n\r");
      cprintf("normal text to have as a background. Colour values are shown in the\n\r");
      cprintf("chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
d1331 33
a1363 33
      break;
    case 25:
      cprintf("You can set TextColour to the value of the colour you wish\n\r");
      cprintf("highlighted text to appear in. Colour values are shown in the\n\r");
      cprintf("chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
      cprintf("Default: 14");
      break;
    case 26:
      cprintf("You can set HighBackground to the value of the colour you wish\n\r");
      cprintf("highlighted text to have as a background. Colour values are shown\n\r");
      cprintf("in the chart below.\n\r\n\r");
      cprintf("COLOURS:\n\r");
      cprintf("0 Black 4 Red        8 Dark Gray    12 Light Red\n\r");
      cprintf("1 Blue  5 Magenta    9 Light Blue   13 Light Magenta\n\r");
      cprintf("2 Green 6 Brown      10 Light Green 14 Yellow\n\r");
      cprintf("3 Cyan  7 Light Gray 11 Light Cyan  15 White\n\r\n\r");
      cprintf("Default: 4");
      break;
    case 27:
      cprintf("This sets the default number of consecutive invalid logins possible\n\r");
      cprintf("before an account is locked out. Only a SuperUser can subsequently\n\r");
      cprintf("unlock an account.\n\r\n\r");
      cprintf("Default: 10");
      break;
    default:
      cprintf("No information available.");
      break;
  }
d1382 1
a1382 1
						bk=getch();
d1390 1
a1390 1
					bk=getch();
d1404 1
a1404 1
					bk=getch();
d1414 3
a1416 3
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
d1421 1
d1423 5
d1432 1
a1432 1
    fclose(npas);
d1446 4
a1449 4
  suinit(void) initializes the menu options in the string txt[]. This is
  done seperately from the super(void) function so that it can be
  performed as required. view(void) also uses the txt[] variable, so
  suinit(void) must be called after each call to view(void).
d1452 12
a1463 12
  strcpy(txt[1],"1. Create User");
  strcpy(txt[2],"2. Delete User");
  strcpy(txt[3],"3. View All Users");
  strcpy(txt[4],"4. Toggle SuperUser Status");
  strcpy(txt[5],"5. Change Account Expiry Date");
  strcpy(txt[6],"6. Change Password Expiry Date");
  strcpy(txt[7],"7. View Log File");
  strcpy(txt[8],"8. Change Account Password");
  strcpy(txt[9],"9. Assign Max Number of Invalid Logins");
  strcpy(txt[10],"0. Edit Initialization settings");
  strcpy(txt[11],"X. Exit");
  crwin(4,6,47,23,tf,tb,1);
d1468 5
a1472 5
  super() is the function called when a SuperUser logs in and wishes to
  invoke the SuperUser menu (CTRL-enter on login). super() allows the user
  to select an option in much the same way as view() except they can also
  select by option number. Control of the program is subsequently passed
  to the appropriate function.
d1477 150
a1626 150
  cprintf("\n\r   Press any key to continue...\n\r");
  opt=getch();
  suinit();
  y=opt=0;
  while ((opt > '0') || (opt < '1')) /* Change SUOPT here */
  {
    clrscr();
    txb(tb);
    txc(tf);
    cprintf("   SuperUser Menu\n\r\n\r");
    for(x=1;x<=SUOPT;x++)
    {
      if (sel==x)
      {
        txb(hb);
        txc(hf);
      }
      else
      {
        txb(tb);
        txc(tf);
      }
      cprintf("%s\n\r",txt[x]);
    }
    txb(tb);
    txc(tf);
    cprintf("\n\rOption: ");
    opt=getch();
    switch (opt)
    {
      case 13:
        switch (sel)
        {
          case 1:
            creat();
            y=1;
            break;
          case 2:
            del();
            y=1;
            break;
          case 3:
            tolog("User List Viewed.");
            view();
            y=1;
            break;
          case 4:
            toggle();
            y=1;
            break;
          case 5:
            cex();
            y=1;
            break;
          case 6:
            pex();
            y=1;
            break;
          case 7:
            vlog();
            y=1;
            break;
          case 8:
            un=view()*-1;
            crwin(2,5,65,22,tf,tb,2);
            if (!wm)
              clrscr();
            setp();
            y=1;
            break;
          case 9:
            alock();
            y=1;
            break;
          case 10:
            iset();
            y=1;
            break;
          case SUOPT:
            su=sul=1;
            fin(0);
            break;
        }
        break;
      case 77:
      case 80:
        if (sel<SUOPT)
          sel++;
        break;
      case 75:
      case 72:
        if (sel>1)
          sel--;
        break;
      case '1':
        creat();
        y=1;
        break;
      case '2':
        del();
        y=1;
        break;
      case '3':
        tolog("User List Viewed.");
        view();
        y=1;
        break;
      case '4':
        toggle();
        y=1;
        break;
      case '5':
        cex();
        y=1;
        break;
      case '6':
        pex();
        y=1;
        break;
      case '7':
        vlog();
        y=1;
        break;
      case '8':
        un=view()*-1;
        crwin(2,5,65,22,tf,tb,2);
        if (!wm)
          clrscr();
        setp();
        y=1;
        break;
      case '9':
        alock();
        y=1;
        break;
      case '0':
        iset();
        y=1;
        break;
      case 'x':
      case 'X':
      case 27:
        su=sul=1;
        fin(0);
        break;
    }
    if (y)
      suinit();
    y=opt=0;
  }
@
