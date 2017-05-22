head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.23.27;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	;


desc
@@


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
  if (streq(tlf,ilog))
    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
  else
    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Backup Log File");
  vl=VLBOT-VLTOP-VLCONST;
  cprintf("\r\n\r\nView for [O]ne or [A]ll users? ");
  m=blch();
  if (m!=ESC)
  {
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
//      strupr(lo);
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
        error(OPLOG);
      else
      {
        fclose(logf);
        if ((logf=fopen(tlf,"r"))==NULL)
        error(OPLOG);
      }
    }
    x=0;
    while((fgets(cp,MAX,logf))!=NULL)
    {
      chop(cp);
//      strupr(cp);
      fgets(temp,MAX,logf);
      if (!m || csck(lo,cp))
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
        if (c==ESC)
          break;
      }
    }
    fclose(logf);
    if (c!=ESC)
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
      cprintf("Yes");
      if (m)
      {
        if ((logf=fopen(tlf,"r"))==NULL)
          error(OPLOG);
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
          error(OPTMP);
        while((fgets(cp,MAX,logf))!=NULL)
        {
          chop(cp);
//          strupr(cp);
          fgets(na,MAX,logf);
          if (!csck(lo,cp))
            fprintf(npas,"%s\n%s",cp,na);
        }
        fclose(logf);
        fclose(npas);
        sunlink(tlf);
        rename(temp,tlf);
      }
      else
      {
        if ((logf=fopen(tlf,"w"))==NULL)
          error(CRLOG);
        fclose(logf);
      }
      if ((logf=fopen(ilog,"a"))==NULL)
        error(CRLOG);
      cprintf("\r\n\r\n The log file has been cleared.\r\n");
      if (streq(tlf,ilog))
        tolog("Log File Viewed.");
      else
        tolog("Backup Log File Viewed.");
      fclose(logf);
      cprintf("\r\n  Press a key to continue...");
      c=blch();
    }
    else
      cprintf("No");

  }
  if ((logf=fopen(ilog,"a"))==NULL)
    error(CRLOG);
}

void mvlog(void)
/*
  mvlog() moves the current log file to the backup log file.
*/
{
int x;
  crwin(2,10,69,14,tf,tb,2,"Backup Log File");
  if (!wm)
    clrscr();
  cprintf("\r\n Do you want to move the log file to the backup file? ");
  x=blch();
  if ((x=='Y') || (x=='y'))
  {
    cprintf("Yes");
    fclose(logf);
    if ((pass=fopen(ilbk,"a"))==NULL)
      error(CRBKL);
    if ((logf=fopen(ilog,"r"))==NULL)
      error(OPLOG);
    while((fgets(cp,MAX,logf))!=NULL)
      fputs(cp,pass);
    fclose(pass);
    fclose(logf);
    if ((logf=fopen(ilog,"w"))==NULL)
      error(CRLOG);
    tolog("Log File Moved to Backup.");
    cprintf("\r\n\r\n The log file has been moved to the backup file...(Press a key)\r\n");
    blch();
  }
  else
    cprintf("No");
}

void loginit(void)
/*
  loginit() initializes the Log File Maintenance menu options in the
  string txt[].
  This is done seperately from the logm() function so that it can be
  performed as required. user() and super() also uses the txt[]
  variable.
*/
{
  strcpy(txt[1],"1. View Primary Log File");
  strcpy(txt[2],"2. View Backup Log File");
  strcpy(txt[3],"3. Move Log File to Backup");
  strcpy(txt[LGOPT],"4. Return to SuperUser Menu");
  if (!puttext(1,1,80,25,msc))
    error(SCWR);
  crwin(10,10,52,18,tf,tb,2,"Log File Maintenance Menu");
}

void logm(void)
/*
  logm() contains all Log File Maintenance otpions.
*/
{
  short int x,y;
  char opt,sel=1;
  loginit();
  y=opt=0;
  while (1) /* This is iffy (but it works) */
  {
    hl=sel+20;
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
      if (((opt-'0')<=LGOPT) && ((opt-'0')!=0))
      {
        sel=opt-'0';
        opt=13;
      }
    }
    switch (opt)
    {
    case 'U': /* Quick jump to user menu */
      user();
      break;
    case 'S': /* Quick jump to system file menu */
      sys();
      break;
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
    case ESC:  /* Escape */
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
    }
    hl=sel+20;
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
    if (y)
      loginit();
    y=opt=0;
  }
}
@


4.7
log
@*** empty log message ***
@
text
@d1 9
d23 4
a26 1
  crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
d30 1
a30 3
  if (m=='O')
    m='o';
  if (m=='o')
d32 3
a34 4
    m=view("View Log File");
    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
    pass=ffwd(2,NULL);
    for(x=1;x<m;x++)
d36 9
d48 3
a51 22
    fgets(lo,MAX,pass);
    fgets(ps,MAX,pass);
    fgets(ti,MAX,pass);
    prd();
    chop2(lo);
    strupr(lo);
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
      error(OPLOG);
d54 8
a61 3
      fclose(logf);
      if ((logf=fopen(tlf,"r"))==NULL)
      error(OPLOG);
d63 1
a63 8
  }
  x=0;
  while((fgets(cp,MAX,logf))!=NULL)
  {
    chop(cp);
    strupr(cp);
    fgets(temp,MAX,logf);
    if (!m || streq(lo,cp))
d65 3
a67 5
      x++;
      if (strlen(temp)>SCRWIDTH)
        x++;
      cprintf("%s\r",temp);
      if (x>vl)
d69 3
a71 4
        cprintf("\r\n  Press a key to continue...");
        c=blch();
        cprintf("\r\n");
        x=0;
a72 2
      if (c==27)
        break;
d74 2
a75 17
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
d77 18
a94 25
      if ((logf=fopen(tlf,"r"))==NULL)
        error(OPLOG);
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
        error(OPTMP);
      while((fgets(cp,MAX,logf))!=NULL)
      {
        chop(cp);
        strupr(cp);
        fgets(na,MAX,logf);
        if (!streq(lo,cp))
          fprintf(npas,"%s\n%s",cp,na);
d96 7
a102 4
      fclose(logf);
      fclose(npas);
      sunlink(tlf);
      rename(temp,tlf);
d104 3
d108 3
d112 41
a152 1
      if ((logf=fopen(tlf,"w"))==NULL)
d154 5
d160 2
a162 5
    if ((logf=fopen(ilog,"a"))==NULL)
      error(CRLOG);
    cprintf("\r\n\r\n The log file has been cleared.\r\n");
    if (streq(tlf,ilog))
      tolog("Log File Viewed.");
d164 2
a165 4
      tolog("Backup Log File Viewed.");
    fclose(logf);
    cprintf("\r\n  Press a key to continue...");
    c=blch();
d172 3
d176 2
a177 13
  fclose(logf);
  if ((pass=fopen(ilbk,"a"))==NULL)
    error(CRBKL);
  if ((logf=fopen(ilog,"r"))==NULL)
    error(OPLOG);
  while((fgets(cp,MAX,logf))!=NULL)
    fputs(cp,pass);
  fclose(pass);
  fclose(logf);
  if ((logf=fopen(ilog,"w"))==NULL)
    error(CRLOG);
  tolog("Log File Moved to Backup.");
  crwin(2,10,65,14,tf,tb,2,"Backup Log File");
d180 22
a201 2
  cprintf("\r\n\r\n     The log file has been moved to the backup file...\r\n");
  blch();
d208 3
a210 2
  This is done seperately from the user() function so that it can be
  performed as required. view() and super() also uses the txt[] variable, so
d224 1
a224 1
  logm() contains all User Maintenance otpions.
d231 1
a231 1
  while (1) /**** This is iffy (but it works) */
d259 5
a263 2
      sel=opt-'0';
      opt=13;
d267 6
d285 1
a285 1
    case 27:  /* Escape */
@
