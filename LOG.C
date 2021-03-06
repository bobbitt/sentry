/*
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
  fclose(logf); // Close log file first.
  if (streq(tlf,ilog))
  {
    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,glstr(452));
//    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
  }
  else
  {
    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,glstr(453));
//    crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Backup Log File");
  }
  vl=VLBOT-VLTOP-VLCONST;
  cprintf("\r\n\r\n");
  pstr(454);
  cprintf(" ");
//  cprintf("\r\n\r\nView for [O]ne or [A]ll users? ");
  m=blch();
  if (m!=ESC)
  {
    if (m=='O')
      m='o';
    if (m=='o')
    {
      strcpy(tol,glstr(452));
      m=view(tol);
//      m=view(glstr(452));
//      m=view("View Log File");
      crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,glstr(452));
//      crwin(VLLEFT,VLTOP,VLRIGHT,VLBOT,tf,tb,2,"View Log File");
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
      fgets(temp,MAX2,logf);
      if (!m || csck(lo,cp))
      {
        x++;
        if (strlen(temp)>SCRWIDTH)
          x++;
        cprintf("%s",temp);
        cprintf("\r");
        if (x>vl)
        {
          cprintf("\r\n  ");
          pstr(48);
//          cprintf("\r\n  Press a key to continue...");
          c=blch();
          cprintf("\r\n");
          x=0;
        }
        if (c==ESC)
          break;
      }
    }
    fclose(logf);
    if ((logf=fopen(ilog,"a"))==NULL)
      error(CRLOG);
    if (m)
    {
      strcpy(tol,lo);
      strcat(tol,"'s ");
    }
    else
      strcpy(tol,"");
    if (streq(tlf,ilog))
    {
      strcat(tol,glstr(450));
//      strcat(tol,"Log File Viewed.");
    }
    else
    {
      strcat(tol,glstr(451));
//      strcat(tol,"Backup Log File Viewed.");
    }
    tolog(tol);
    fclose(logf);
    if (c!=ESC)
    {
      cprintf("\r\n  ");
      pstr(48);
//      cprintf("\r\n  Press a key to continue...");
      c=blch();
      cprintf("\r\n");
    }
    cprintf("\r\n ");
    pstr(455);
    cprintf(" ");
//    cprintf("\r\n Would you like to clear ");
    if (m)
    {
      cprintf("%s%s ",lo,glstr(456));
//      cprintf("%s's log file? [y/N]? ",lo);
    }
    else
    {
      cprintf("%s ",glstr(457)); // **** DOES NOT TRANSLATE PROPERLY IN SPANISH
//      cprintf("the log file [y/N]? ");
    }
    c=blch();
    yeah(c)
    {
      pstr(211);
//      cprintf("Yes");
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
      cprintf("\r\n\r\n ");
      pstr(459);
      cprintf("\r\n");
//      cprintf("\r\n\r\n The log file has been cleared.\r\n");
      if ((logf=fopen(ilog,"a"))==NULL)
        error(CRLOG);
      if (m)
      {
        strcpy(tol,lo);
        strcat(tol,"'s ");
      }
      else
        strcpy(tol,"");
      if (streq(tlf,ilog))
      {
        strcat(tol,glstr(459));
//        strcat(tol,"Log File Cleared.");
      }
      else
      {
        strcat(tol,glstr(460));
//        strcat(tol,"Backup Log File Cleared.");
      }
      tolog(tol);
      fclose(logf);
      cprintf("\r\n  ");
      pstr(48);
//      cprintf("\r\n  Press a key to continue...");
      c=blch();
    }
    else
    {
      pstr(213);
//      cprintf("No");
    }
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
  crwin(2,10,69,14,tf,tb,2,glstr(458));
//  crwin(2,10,69,14,tf,tb,2,"Backup Log File");
  if (!wm)
    clrscr();
  cprintf("\r\n ");
  pstr(461);
  cprintf(" ");
//  cprintf("\r\n Do you want to move the log file to the backup file? ");
  x=blch();
  yeah(x)
  {
    pstr(211);
//    cprintf("Yes");
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
    tolog(glstr(462));
//    tolog("Log File Moved to Backup.");
    cprintf("\r\n\r\n ");
    pstr(463);
    cprintf("\r\n");
//    cprintf("\r\n\r\n The log file has been moved to the backup file...(Press a key)\r\n");
    blch();
  }
  else
  {
    pstr(213);
//    cprintf("No");
  }
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
  strcpy(txt[1],glstr(464));
  strcpy(txt[2],glstr(465));
  strcpy(txt[3],glstr(466));
  strcpy(txt[LGOPT],glstr(467));
//  strcpy(txt[1],"1. View Primary Log File");
//  strcpy(txt[2],"2. View Backup Log File");
//  strcpy(txt[3],"3. Move Log File to Backup");
//  strcpy(txt[LGOPT],"4. Return to SuperUser Menu");
  if (!puttext(1,1,80,25,msc))
    error(SCWR);
  crwin(10,10,52,18,tf,tb,2,glstr(468));
//  crwin(10,10,52,18,tf,tb,2,"Log File Maintenance Menu");
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
    cprintf("\r\n");
    pstr(92);
    cprintf(" ");
//    cprintf("\r\nOption: ");
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
    case 0:
      switch(ext)
      {
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
