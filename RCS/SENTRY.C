head	5.0;
access;
symbols;
locks
	MIKE:5.0;
comment	@ * @;


5.0
date	96.08.14.09.24.46;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.42.21;	author MIKE;	state Exp;
branches;
next	3.3;

3.3
date	95.12.18.18.14.15;	author MIKE;	state Exp;
branches;
next	3.2;

3.2
date	95.12.08.16.30.29;	author MIKE;	state Exp;
branches;
next	3.1;

3.1
date	95.11.30.18.39.42;	author MIKE;	state Exp;
branches;
next	3.0;

3.0
date	95.11.09.15.58.03;	author MIKE;	state Exp;
branches;
next	2.7;

2.7
date	95.10.26.18.04.41;	author MIKE;	state Exp;
branches;
next	2.6;

2.6
date	95.10.25.12.06.46;	author MIKE;	state Exp;
branches;
next	2.5;

2.5
date	95.10.10.16.54.35;	author MIKE;	state Rel;
branches;
next	2.3;

2.3
date	95.09.24.21.38.07;	author MIKE;	state Rel;
branches;
next	2.2;

2.2
date	95.09.08.13.15.13;	author MIKE;	state Rel;
branches;
next	2.0;

2.0
date	95.08.11.12.13.23;	author MIKE;	state Rel;
branches;
next	1.4;

1.4
date	95.08.08.17.31.39;	author MIKE;	state Rel;
branches;
next	1.0;

1.0
date	95.08.08.17.25.31;	author MIKE;	state Rel;
branches;
next	;


desc
@Restrict and Monitor access in DOS and Windows.
Initial Release (20 Jul 95).
@

5.0
log
@Version 5.0
@
text
@/*
  INCLUDES
*/
#ifdef __cplusplus
extern "C"
{
#endif
#include "sentry.h"
#ifdef __cplusplus
}
#endif

/*
  GLOBAL VARIABLES
*/

FILE *pass,*logf,*ini,*npas,*msg;
char na[MAX],lo[MAX],pa[MAX],ps[MAX],ti[MAX];
    /* login (x2), password (x2), and time stamps */
char xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX],xplen[MAX],xllen[MAX],lxplen[MAX],lxllen[MAX];
     /* Various messages, and log file messages */
char cp[MAX]; /* Change Password Key */
char envar[MAX]; /* Environment Variable */
char usr[MAX]; /* User name */
char pwd[MAX]; /* User's encrypted password */
char win[25]; /* Command line argument */
char ilog[128]; /* Path to the log file */
char ilbk[128]; /* Path to the backup log file */
char imsg[128]; /* Path to the message file */
char ins[128]; /* Path to Sentry.ins */
char inam[MAX]; /* Path to Sentry.exe */
char temp[132]; /* Temporary storage */
char bd[MAX];   /* conversion code */
char txt[MAXUSER][MAX]; /* Array of pointer to strings for menu items */
char tol[MAX];  /* String for printing to the log file */
char lp[MAX]; /* Login prompt */
char pp[MAX]; /* Password prompt */
char ssm[MAX]; /* Screen Saver Message */
char msc[80*25*2]; /* Array to hold initial screen */
char pec;  /* Password echo character */
char zex[MAXEXT]; /* Extension of ZULU file */
char te[MAXDRIVE+MAXPATH]; /* Drive & path of temp files */
char ze; /* ZULU encryption */

short int zm; /* ZULU mode */
short int min; /* Min Password/Pogin Length */
short int max; /* Max Password/Pogin Length */
short int maxtry; /* Max # of invalid tries to lockout */
short int un;  /* User Number */
short int wait; /* Wait time on invalid login */
short int sul; /* sul=1 -> logging in as SuperUser */
short int su; /* su=1 -> user has SuperUser access */
short int _bk; /* _bk=1 -> gin() input routine is exitable (ESC) */
short int bk; /* set by gin(): bk=1 -> input aborted (ESC) */
short int col; /* Colour 0/1 */
short int df; /* Date format */
short int tf,tb,hf,hb; /* Text and Highlighted Text Colours */
short int fla; /* Failed login attempts */
short int ntl; /* Number of failed login attempts to lockout */
short int ltl; /* Logins until Lockout */
short int cs; /* cs=1 -> case Insensitive */
short int wm;  /* Window mode (0=none, 1=on, 2=exploding) */
short int scrb;  /* seconds of idle time until screen saver */
short int rclf,rctop,rcri,rcbot,rcfrg,rcbak; /* backup window stats */
short int zze; /* ZULU encryption on/off */
short int hl; /* Help location (# of textfile block) */
short int llp; /* Last login Pause */
short int sdel; /* Secure Deletion 0/1 */
short int vwh; // View Highlighting 0/1
short int vwc; // View Highligiting Colour

int mlog; /* Max log file size (kb) */

/* Time Stamps */
long ut; /* Last login date */
long ed; /* Account Expiry Date */
long pe; /* Password Expiry Date */
long pel; /* Number of days a new password is good for */
long ae; /* Spare */
long ael; /* Number of days an account is good for */

struct date td;   /* Date */
struct time nw;   /* Time */
struct text_info sta; /* Startup video attributes */

typedef struct
{        /* structure to use for growing string types */
  char *b;          /* base of string */
  char *p;          /* current "head" of string */
  int  len;         /* length allocated */
  int  inc;         /* how much to grow by each time we fill up */
} estring;

extern unsigned _psp;

/*
  FUNCTIONS
*/

void setp(void)
/*
  setp(void) is the function called to input, verify and store a new
  password. This function is called directly when the users old password
  expires, and via cpass(void) when a user wishes to change their password.
  The variable un is set the the number (within the password file) of the
  user who is changing passwords. If the number is negative, then it is
  possible to abort the operation by pressing ESCAPE.
*/
{
short int err=1,x=0;
char tmp[MAX];
  if (un<0)
  {
    un*=-1;
    x=1;
  }
  while (err!=0)
  {
    err=0;
    tmpath(tol);
    if ((npas=fopen(tol,"wb"))==NULL)
      error(CRTMP);
    pass=ffwd(2,npas);
    guser(un);
    chop2(lo);
    chop2(ps);
    strcpy(tmp,ps);
    su=0;
    if (ps[strlen(ps)-1]==STAMP)
    {
      su=1;
      chop(tmp);
    }
    _bk=x;
    strncpy(pa,gin("\n\r\n\rNew Password:",0),max);
    if (!(bk && x))
    {
      if ((strlen(pa)>max) || (strlen(pa)<min))
        err=2;
      strcpy(temp,pa);
      strcpy(pa,penc(pa));
      temp[strlen(temp)+1]=0;
      temp[strlen(temp)]=STAMP;
      strcpy(temp,penc(temp));
      temp[strlen(temp)+1]=0;
      temp[strlen(temp)]=STAMP;
      _bk=x;
      strncpy(ps,gin("Verify Password:",0),max);
      if (!(bk && x))
      {
        strcpy(ps,penc(ps));
        if (!streq(pa,ps))
          err=3;
        else
          if (!(!streq(tmp,su?temp:pa) || x))
            err=1;
        switch (err)
        {
        case 1:
          cprintf("You cannot use the same password.\n\r");
          break;
        case 2:
          cprintf("Passwords must be between ");
          cprintf("%d",min);
          cprintf(" and ");
          cprintf("%d",max);
          cprintf(" characters.\n\r");
          break;
        case 3:
          cprintf("Password not verified!\n\r");
          break;
        }
      }
      else
      {
        if (su)
        {
          tmp[strlen(tmp)+1]=0;
          tmp[strlen(tmp)]=STAMP;
        }
        strcpy(pa,tmp);
        strcpy(temp,tmp);
      }
    }
    else
    {
      if (su)
      {
        tmp[strlen(tmp)+1]=0;
        tmp[strlen(tmp)]=STAMP;
      }
      strcpy(pa,tmp);
      strcpy(temp,tmp);
    }
    fprintf(npas,"%s\r\n",lo);
    strcat(lo,"'s password has been changed.");
    tolog(lo);
    fprintf(npas,"%s\r\n",su?temp:pa);
    if (pe)  /* If the password had an expiry date */
      pe=pel;     /* Expire it in the default number of days */
    pwr;
    fcd(pass,npas);
    if (!err)
    {
      sunlink(inam);
      rename(tol,inam);
    }
    else
      sunlink(tol);
  }
}

void stamp(void)
/*
  stamp(void) is the function that places the time stamp on a user when
  they log in. It also displays the date and time of their last login,
  shows how many invalid logins have occurred since their last valid
  login, expires the account if their "max invalid login" setting
  has been exceeded and finally checks to see if their account and/or
  password has expired.
*/
{
short int x,y;
long tn;
char dr[MAXDRIVE],di[MAXDIR],fi[MAXFILE],ex[MAXEXT];
  if (un)
  {
    if (!puttext(1,1,80,25,msc))
      error(SCWR);
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(CRTMP);
    pass=ffwd(2,npas);
    guser(un);
    unixtodos(ut,&td,&nw);
    if (df)
      sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
    else
      sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
    sprintf(ti," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
    strcat(tol,ti);
    fputs(lo,npas);
    fputs(ps,npas);
    getdate(&td);
    gettime(&nw);
    if (ut<ael)  /* If the account has been inactive too long */
      ed=dostounix(&td,&nw);
    ut=dostounix(&td,&nw);
    if ((fla>=ntl) && (ntl>0)) /* If # failed login attempts > max */
      ed=ut;
    x=fla;
    fla=0;
    pwr;
    fla=x;
    fcd(pass,npas);
    sunlink(inam);
    rename(temp,inam);
    x=fnsplit(imsg,dr,di,fi,ex);
    tmpnam(temp);
    if (x & DIRECTORY)
    {
      strcpy(lo,temp);
      strcpy(temp,di);
      strcat(temp,lo);
    }
    if (x & DRIVE)
    {
      strcpy(lo,temp);
      strcpy(temp,dr);
      strcat(temp,lo);
    }
    if ((npas=fopen(temp,"w"))==NULL)
      error(CRTMP);
    if ((msg=fopen(imsg,"r"))!=NULL)
    {
      while((fgets(lo,MAX,msg))!=NULL)
      {
        chop(lo);
//        strupr(lo);
        if (csck(lo,na))
        {
          crwin(3,3,77,11,tf,tb,2,"Message");
          cprintf("You have a message awaiting you.\n\r");
          fgets(ps,MAX,msg);
          chop(ps);
          cprintf("FROM: %s\r\n",ps);
          fgets(lo,MAX,msg);
          tn=atol(lo);
          unixtodos(tn,&td,&nw);
          if (df)
            sprintf(pa,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
          else
            sprintf(pa,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
          sprintf(lp," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
          strcat(pa,lp);
          cprintf("DATE: %s\r",pa);
          fgets(pa,MAX,msg);
          cprintf("\r\n%s\r\n[D]elete, [R]eply, or any other to keep...",pa);
          x=blch();
          if ((x=='r') || (x=='R'))
          { /* Reply to the message */
            /* Set un to the SuperUser's user number */
            tn=ftell(msg);  /* Bookmark message file */
            fclose(msg);
            msg=ffwd(2,NULL);
            x=un;   /* Save un for current user */
            un=y=0;
            while((fgets(ti,MAX,msg))!=NULL && (!streq(ti,DIV)) && (!bk))
            {
//              strupr(ti);
              chop2(ti);
              y++;
              fgets(cp,MAX,msg);
              fgets(cp,MAX,msg);
              if (csck(ti,ps))
                un=y;
            }
            fclose(msg);
            if (!un)
            {
              cprintf("\r\n\r\n\r\nNot a current user - cannot reply.\r\n");
              cprintf("\r\nPress any key to continue...\r\n\r\n");
              blch();
            }
            else
              smsg();  /* Send the message */
            if ((msg=fopen(imsg,"r"))==NULL)  /* Reset message file */
              error(OPMSG);
            fseek(msg,tn,SEEK_SET);
            /* Change un back for subsequent operations */
            un=x;
            cprintf("\r\n\r\nDo you want to delete the original? ");
            x=blch();
            if ((x=='y') || (x=='Y'))
            {
              cprintf("Yes");
              x='d';
            }
            else
            {
              cprintf("No");
              x=0;
            }
          }
          if ((x!='d') && (x!='D'))
          {
            na[strlen(na)+1]=0;
            na[strlen(na)]='\n';
            fputs(na,npas);
            chop(na);
            ps[strlen(ps)+1]=0;
            ps[strlen(ps)]='\n';
            fputs(ps,npas);
            fputs(lo,npas);
            fputs(pa,npas);
          }
        }
        else
        {
          lo[strlen(lo)+1]=0;
          lo[strlen(lo)]='\n';
          fputs(lo,npas);
          fgets(ps,MAX,msg);
          fputs(ps,npas);
          fgets(ps,MAX,msg);
          fputs(ps,npas);
          fgets(ps,MAX,msg);
          fputs(ps,npas);
        }
      }
    }
    fclose(msg);
    fclose(npas);
    sunlink(imsg);
    rename(temp,imsg);
    y=4;
    if (strcmp(win,"") && !(su && sul) && !zm)
    /* Add 2 lines if it's running from windows, but not protected, and */
      y+=2;  /* not a SuperUser login */
    x=strlen(tol);
    if (fla)
    {
      sprintf(ti,"%d invalid login attempt(s) have occurred since your last login.\n\r",fla);
      y++;
      if (strlen(tol)<strlen(ti))
        x=strlen(ti);
    }
    if (su && sul) /* Add 2 lines to window if it's a SuperUser login */
      y+=2;
    crwin(8,12,14+x,12+y,tf,tb,2,"");
    if (!wm)
      clrscr();
    cprintf("\n\r   %s",tol);
    if (fla)
      cprintf("   %s",ti);
    if ((ut>=ed) && (ed))
      error(EXPIR);
    if ((ut>=pe) && (pe))
    {
      if (x<49)
        x=49;
      crwin(8,11,14+x,17+y,tf,tb,2,"");
      cprintf("\n\r   %s",tol);
      if (fla)
        cprintf("   %s",ti);
      sprintf(tol,"%s's Password has Expired.",na);
      tolog(tol);
      cprintf("\n\rNOTE: Your password has expired. You must enter a\n\r");
      cprintf("      new one to retain your access.\n\r");
      setp();
    }
  }
}

void badl(void)
/*
  badl(void) is the function called when an invalid login attempt is
  made. badl(void)  updates the invalid login counter for the
  appropriate account, prints the value of tol to the log, waits "wait"
  seconds and flushes the input buffer.
*/
{
  if (un)
  {
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(CRTMP);
    pass=ffwd(2,npas);
    guser(un);
    fla++;
    fputs(lo,npas);
    fputs(ps,npas);
    pwr;
    fcd(pass,npas);
    sunlink(inam);
    rename(temp,inam);
    un=0;
  }
  tolog(tol);
  sleep(wait);
  while(kbhit())
    blch();
}

void init(void)
/*
  init(void) is called on startup. It initializes and assigns values to
  some variables and then passes execution back to main(void).
*/
{
struct ffblk ffblk;
short int x;
long nd;
struct date xd;
struct time xt;
  ctrlbrk(tsk);
  getdate(&xd);
/*
Detect all active drives
  strcpy(drv,"");
  for(x='a';x<='z';x++)
  {
    temp[0]=x;
    temp[1]=0;
    strcat(temp,":\nul");
    if ((log=fopen(temp,"r"))!=NULL)
    {
      drv[strlen(drv)+1]=0;
      drv[strlen(drv)]=x;
      fclose(log);
    }
  }
printf("Drives: [%s]",drv);
*/
  x=findfirst("tmp*.$$$",&ffblk,0); /* Delete all old temp files that */
  while (!x)                 /* May be hanging around */
  {
    sunlink(ffblk.ff_name);
    x=findnext(&ffblk);
  }
  x=findfirst("tmp*.exe",&ffblk,0);  /* Delete all old protected files */
  while (!x)                 /* that may be hanging around */
  {
    sunlink(ffblk.ff_name);
    x=findnext(&ffblk);
  }
  strcpy(ssm,"");    /* Don't print Please Wait banner yet */
/*  for(x=1;x<=MAXUSER;x++) /* Allocate memory //
  {
    if ((txt[x]=(char*)malloc(MAX))==NULL)
      error(NOMEM);
    strcpy(txt[x],"");
  }
*/
  /* Get current video attributes */
  gettextinfo(&sta);
  textmode(C80);
  if (!gettext(1,1,80,25,msc))
    error(SCRD);
  xt.ti_hour=0;
  xt.ti_min=0;
  xt.ti_sec=0;
  xt.ti_hund=0;
  nd=dostounix(&xd,&xt)-regno;
  ltoa(nd,bd,10);
  un=0;
  sum=0; /* Not on the SuperUser menu yet */
  zze=0; /* Encryption off */
  sul=0; /* user is not a SuperUser */
  _bk=0; /* gin() is non-breakable */
  zm=0; /* ZULU mode off */
  hl=0; /* No default help */
  randomize();
}

void fin(short int ec)
/*
  fin(short int ec) is the function called to cleanly exit from Sentry,
  regardless of where execution currently is. It closes all files, and
  hides the log file and generally cleans up. fin(short int ec) takes an
  integer parameter which is passed as the exit code on termination.
  fin(short int ec) is always the last function executed in Sentry.
*/
{
#if !USER
  shar(1);
#endif
  flushall();
  fcloseall();
  _rtl_chmod(ilog,1,FA_HIDDEN);
  _rtl_chmod(ilbk,1,FA_HIDDEN);
  _rtl_chmod(imsg,1,FA_HIDDEN);
/*
  for(x=1;x<=MAXUSER;x++) /* De-allocate memory //
    free(txt[x]);
*/
  if (zm)
  {
    if ((logf=fopen(ilog,"a"))==NULL)
      error(CRLOG);
    sprintf(tol,"%s run in protected mode.",inam);
    tolog(tol);
    tmpath(temp);
    temp[strlen(temp)-1]=zex[strlen(zex)-1];
    temp[strlen(temp)-2]=zex[strlen(zex)-2];
    temp[strlen(temp)-3]=zex[strlen(zex)-3];
    if ((npas=fopen(temp,"wb"))==NULL)
      error(CRTMP);
    pass=ffwd(3,NULL);
    zze=-1;
    fcd(pass,npas);
    zze=0;
    fclose(logf);
    crwin(1,1,79,24,tf,tb,0,"");
    gotoxy(1,24);
    strcpy(tol,temp);
    strcat(tol," ");
    strcat(tol,win);
    system(tol);
    sunlink(temp);
    if ((logf=fopen(ilog,"a"))==NULL)
      error(CRLOG);
    tolog("Execution Complete.");
    tolog("-----------------------------");
    fclose(logf);
    /* Re-set startup video attributes */
    window(sta.winleft,sta.wintop,sta.winright,sta.winbottom);
    textattr(sta.attribute);
    textmode(sta.currmode);
    gotoxy(sta.curx,sta.cury);
    if (llp && !hl) /* But not if you're on a menu */
    {
      sleep(llp);
      clrscr();
    }
    exit(ec); /* Exit Protected File */
  }
  if (strcmp(win,""))
  {
    if (su && sul)
    {
      sprintf(tol,"%s DOS Shell",SENTRY);
      crwin(4,6,50,10,tf,tb,2,tol);
    }
    if ((logf=fopen(ilog,"a"))==NULL)
     error(CRLOG);
    dshell();
    tolog("-----------------------------");
    fclose(logf);
    /* Re-set startup video attributes */
    window(sta.winleft,sta.wintop,sta.winright,sta.winbottom);
    textattr(sta.attribute);
    textmode(sta.currmode);
    gotoxy(sta.curx,sta.cury);
    if (llp && !hl) /* But not if you're on a menu */
    {
      sleep(llp);
      clrscr();
    }
    exit(ec); /* Exit DOS Shell */
  }
  crwin(1,1,79,24,tf,tb,0,"");
  gotoxy(1,24);
  if ((logf=fopen(ilog,"a"))==NULL)
    error(CRLOG);
  tolog("-----------------------------");
  fclose(logf);
  /* Re-set startup video attributes */
  window(sta.winleft,sta.wintop,sta.winright,sta.winbottom);
  textattr(sta.attribute);
  textmode(sta.currmode);
  gotoxy(sta.curx,sta.cury);
  /* Last login pause? */
  if (llp && !hl) /* But not if you're on a menu */
  {
    sleep(llp);
    clrscr();
  }
  exit(ec);   /* Normal exit */
}

void main(short int argc,char *argv[])
/*
  main() is the starting function in Sentry. It checks the registration
  information, reads in all initialization settings, prints the startup
  information, prompts for the login and password and handles any errors
  that arise from there.
*/
{
unsigned env_addr,seglen;
char value[MAX],**env_var,v[DIVLEN+2];
short int err=1,ero=0,try=1,x,unn,lc,index;
short int ta; /* Type ahead */
int count;
long y;
  init();
  strcpy(inam,argv[0]);
  x=fnsplit(inam,te,temp,lo,na);
  if (x & DIRECTORY)
  {
    strcat(te,temp);
    strcpy(ins,te);
  }
#if USER
  strcpy(temp,regto);
  y=regno;
  x=0;
  while (y>0)
  {
    x+=y-(y/10)*10;
    y/=10;
  }
  itoa(x,na,10);
  strcpy(pa,na);
  strcat(pa,regch);
  if (strcmp(UNIXcrypt(temp,na),pa))
    error(REGER);
#endif
  ini=ffwd(1,NULL);
  strcpy(v,gstr());
  if ((v[strlen(v)-1]=='Z') || (v[strlen(v)-1]=='X'))
  {
    v[strlen(v)-1]=0;
    zm=1;
    strcpy(zex,gstr());
    strcpy(ins,gstr());
    strcpy(temp,gstr());
    ze=temp[0];
  }
  if (strcmp(v,ver)>0)
    cprintf("Warning! The Initialization Settings are from a newer version!\n\r");
  if (strcmp(v,ver)<0)
    cprintf("Warning! The Initialization Settings are from an older version!\n\r");
  strcpy(ilog,gstr());
  if ((logf=fopen(ilog,"a"))==NULL)
    error(CRLOG);
  strcpy(ilbk,gstr());
  strcpy(imsg,gstr());
  min=atoi(gstr());
  max=atoi(gstr());
  maxtry=atoi(gstr());
  if (max>MAX)
    max=MAX;
  if (min>MAX)
    min=MAX;
  wait=atoi(gstr());
  mlog=atoi(gstr());
  strcpy(cp,gstr());
  strcpy(ssm,gstr());
  pec=ssm[0];
  pel=atol(gstr());
  if (pel)
  {
    pel++;
    pel*=DAY2SEC;
    getdate(&td);
    gettime(&nw);
    pel+=dostounix(&td,&nw);
  }
  ael=atol(gstr());
  if (ael)
  {
    ael++;
    ael*=DAY2SEC;
    getdate(&td);
    gettime(&nw);
    ael=dostounix(&td,&nw)-ael;
  }
  scrb=atoi(gstr());
  strcpy(ssm,gstr());
  strcpy(lp,gstr());
  strcpy(pp,gstr());
  strcpy(xpwd,gstr());
  strcpy(xlog,gstr());
  strcpy(xplen,gstr());
  strcpy(xllen,gstr());
  strcpy(lxpwd,gstr());
  strcpy(lxlog,gstr());
  strcpy(lxplen,gstr());
  strcpy(lxllen,gstr());
  strcpy(envar,gstr());
  x=atoi(gstr());
  win[0]=0;
  if ((argc>1) && x)
    strcpy(win,argv[1]);
  x=atoi(gstr());
  df=atoi(gstr());
  cs=atoi(gstr());
  wm=atoi(gstr());
  col=atoi(gstr());
  if (!col)
     textmode(BW80);
  tf=atoi(gstr());
  tb=atoi(gstr());
  hf=atoi(gstr());
  hb=atoi(gstr());
  ltl=atoi(gstr());
  ta=atoi(gstr());
  if (atoi(gstr()))
  {
    clrscr();
    if (!gettext(1,1,80,25,msc))
      error(SCRD);
  }
  llp=atoi(gstr());
  sdel=atoi(gstr());
  vwh=atoi(gstr());
  vwc=atoi(gstr());
  fclose(ini);
  txb(tb);
#if !USER
  shar(0);
#endif
  if (!wm)
    clrscr();
  if (x)
  {
    crwin(4,4,76,9,tf,tb,2,"");
    txc(WHITE);
    cprintf("ÚÄÄÄÄÄÄÄÄÄÄ¿  ");
    txc(AUCOL);
    cprintf("NightShade Computing    ");
    txc(RGCOL);
    cprintf("   Registered to");
    txc(WHITE);
    cprintf("\n\r³");
    txc(TICOL);
    cprintf("%s",SENTRY);
    cprintf(" ");
    cprintf("%s",ver);
    txc(WHITE);
    cprintf("³  ");
    txc(AUCOL);
    cprintf("Copyright (C) 1995-1996    ");
    txc(RGCOL);
    cprintf("%s",regto);
    txc(WHITE );
    cprintf("\n\rÀÄÄÄÄÄÄÄÄÄÄÙ  ");
    txc(AUCOL);
    cprintf("Michael A. Bobbitt");
    txc(RGCOL);
    cprintf("         Registration #: ");
    cprintf("%lu",regno);
    txc(AUCOL);
    cprintf("\n\r              [Mike.Bobbitt@@AcadiaU.CA]");
  }
  txc(tf);
  crwin(4,11,76,21,tf,tb,2,"");
  cprintf("\n\r");
  if (!wm)
    cprintf("\n\r");
  cprintf("Enter \"");
  cprintf("%s",cp);
  cprintf("\" at the password prompt to set a new password.\n\r\n\r");
  strcpy(cp,penc(cp));
  if (!ta)
    while(kbhit())
      blch();
/*
while (strlen(na))
{
strncpy(na,gin("Enter a filename path:",1),max);
x=cpath(0,na);
cprintf("%d:[%s]\r\n",x,na);
}
strcpy(na,"Z");
while (strlen(na))
{
strncpy(na,gin("Enter a directory path:",1),max);
x=cpath(1,na);
cprintf("%d:[%s]\r\n",x,na);
}
strcpy(na,"Z");
*/
  _rtl_chmod(ilog,1,-FA_HIDDEN);
  _rtl_chmod(ilbk,1,-FA_HIDDEN);
  _rtl_chmod(imsg,1,-FA_HIDDEN);
  pass=ffwd(2,NULL);
  fclose(pass);
  while ((err!=0) && (ero<100))
  {
    err=0;
    try++;
    sul=0;
    strcpy(na,"");
    while (!strlen(na))
      strncpy(na,gin(lp,1),max);
    strcpy(usr,na);
    if ((strlen(na)>max) || (strlen(na)<min))
      err=1;
    strncpy(pa,gin(pp,0),max);
    lc=strlen(pa);
    if ((pec!='?') && (pec!='!'))
    {
      gotoxy(wherex()+strlen(pp)+lc+1,wherey()-1);
      for (y=0;y<=(max-lc);y++)
        cprintf("%c",pec);
      cprintf("\r\n");
    }
    strcpy(temp,pa);
    strcpy(pa,penc(pa));
    temp[strlen(temp)+1]=0;
    temp[strlen(temp)]=STAMP;
    strcpy(temp,penc(temp));
    if (streq(cp,pa))
    {
      fclose(pass);
      cpass();
      lc=strlen(pa);
      chop(temp);
    }
    strcpy(pwd,pa);
    pass=ffwd(2,NULL);
    if (!err)
      err=4;
    y=0;
    unn=0;
    while(((fgets(lo,MAX,pass))!=NULL) && (!streq(lo,DIV)))
    {
      unn++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      chop2(lo);
      chop2(ps);
      if (err==4)
      {
        if (csck(na,lo))
        {
          x=0;
          if (ps[strlen(ps)-1]==STAMP)
          {
            chop(ps);
            x=1;
          }
          err=0;
          y=x;
          un=unn;
          strcpy(usr,na);
          strcpy(pwd,pa);
          su=0;
          if (!streq(pa,ps))
          {
            if (!streq(temp,ps))
              err=3;
            else
              su=1;
          }
          if ((lc>max) || (lc<min))
            err=2;
        }
      }
    }
    fclose(pass);
    switch (err)
    {
    case 1:
      cprintf("%s\n\r",xllen);
      sprintf(tol,"%s: %s",na,lxllen);
      badl();
      break;
    case 2:
      cprintf("%s\n\r",xplen);
      sprintf(tol,"%s: %s",na,lxplen);
      badl();
      break;
    case 3:
      cprintf("%s\n\r",xpwd);
      sprintf(tol,"%s: %s",na,lxpwd);
      badl();
      break;
    case 4:
      cprintf("%s\n\r",xlog);
      sprintf(tol,"%s: %s",na,lxlog);
      badl();
      break;
    }
    if ((try>maxtry) && err)
    {
      cprintf("Exceeded maximum number of tries.\n\r");
      tolog("Exceeded maximum number of tries.");
      ero=100;
    }
    if ((y!=su) && !err)
    {
      sprintf(tol,"%s has been tampered with!!",na);
      tolog(tol);
    }
  }
  if (ero==100)
    lockup();
  sum=1; /* You are now "logged in" */
  stamp();
  if (!getenvseg(&env_addr))  /* Do the environment setting */
    error(NOENV);
  seglen=get_env_var(env_addr,&env_var,&count);
  index=get_env_index(envar,env_var);
  if (index == count)
    env_var[index+1] = (char *)NULL;
  strcpy(value,envar);
  strcat(value,"=");
  strcat(value,na);
  strupr(value);
  env_var[index] = value;
  put_env_var(env_addr, seglen, env_var);
  if (!su && sul)
  {
    sprintf(tol,"%s does not have SuperUser access.",na);
    tolog(tol);
  }
  if (su && sul)
  {
    sprintf(tol,"%s logged in as SuperUser.",na);
    tolog(tol);
    cprintf("\n\r   Press any key to continue...\n\r");
    x=blch();
    super();
  }
  else
  {
    sprintf(tol,"%s logged in.",na);
    tolog(tol);
  }
  fin(0);
}
@


4.7
log
@*** empty log message ***
@
text
@a8 11
/* If it's not the shareware version, include the encoding routine. */
#if USER
  #include "crypt.c"
#endif
#include "super.c"
#include "user.c"
#include "log.c"
#include "env.c"
#include "sys.c"
#include "common.c"

d14 83
d125 2
a127 2
    chop2(tmp);
    chop2(ps);
a194 1
    strcpy(lo,usr);
d279 2
a280 1
        if (streq(lo,na))
d285 2
a286 1
          cprintf("FROM: %s\r",ps);
d298 1
a298 1
          cprintf("\n\r%s\n\rPress 'd' to delete message...",pa);
d300 45
d351 2
d396 1
a396 1
    if ((ut>=ed) && (ed!=0))
d398 1
a398 1
    if ((ut>=pe) && (pe!=0))
d402 1
a402 1
      crwin(8,11,14+x,14+y,tf,tb,2,"");
d458 1
a458 1
/****
d474 1
a474 1
****/
d488 1
a488 1
  for(x=1;x<=MAXUSER;x++)
d490 1
a490 1
    if ((txt[x]=malloc(MAX))==NULL)
d494 1
d507 1
d530 7
a536 3
  _chmod(ilog,1,FA_HIDDEN);
  _chmod(ilbk,1,FA_HIDDEN);
  _chmod(imsg,1,FA_HIDDEN);
d571 6
a576 1
    exit(ec);
d595 6
a600 1
   exit(ec);
d613 7
a619 1
  exit(ec);
d631 1
a631 1
char value[MAX],**env_var,envar[MAX],v[DIVLEN+2];
d661 1
a661 1
  if (v[strlen(v)-1]=='Z')
d698 1
a698 2
    y=dostounix(&td,&nw);
    pel+=y;
d707 1
a707 2
    y=dostounix(&td,&nw);
    ael=y-ael;
d745 4
d774 1
a774 1
    cprintf("Copyright (C) 1996,        ");
d799 19
a817 3
  _chmod(ilog,1,-FA_HIDDEN);
  _chmod(ilbk,1,-FA_HIDDEN);
  _chmod(imsg,1,-FA_HIDDEN);
d825 3
a827 1
    strncpy(na,gin(lp,1),max);
d933 2
a934 2
  if ( !getenvseg(&env_addr))
    error (NOENV);
@


3.8
log
@*** empty log message ***
@
text
@d14 2
d19 1
d38 2
a39 1
  short int err=1,x=0;
d48 3
a50 3
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error("Error opening temp file!");
d53 2
a54 2
    strcpy(na,ps);
    chop2(na);
d56 1
a56 1
    sul=0;
d59 2
a60 2
      sul=1;
      chop(na);
d63 1
a63 2
    strcpy(pa,gin("\n\r\n\rNew Password:",0));
    strncpy(pa,pa,max);
d68 1
a68 5
      if (sul)
      {
        pa[strlen(pa)+1]=0;
        pa[strlen(pa)]=STAMP;
      }
d70 5
d76 1
a76 2
      strcpy(ps,gin("Verify Password:",0));
      strncpy(ps,ps,max);
a78 5
        if (sul)
        {
          ps[strlen(ps)+1]=0;
          ps[strlen(ps)]=STAMP;
        }
d80 1
a80 1
        if (strcmp(pa,ps))
d83 1
a83 1
          if (!(strcmp(na,ps) || x))
d103 9
a111 1
        strcpy(ps,na);
a113 2
      strcpy(ps,na);
    if (!sul)
d115 7
a121 10
      ps[strlen(ps)+2]=0;
      ps[strlen(ps)+1]='\n';
      ps[strlen(ps)]='\r';
    }
    else
    {
      ps[strlen(ps)+3]=0;
      ps[strlen(ps)+2]='\n';
      ps[strlen(ps)+1]='\r';
      ps[strlen(ps)]=STAMP;
d123 7
a129 7
    fputs(lo,npas);
    chop2(lo);
    sprintf(tol,"%s's password has been changed.",lo);
    tolog(tol);
    fputs(ps,npas);
    if (pe)
      pe=pel;
d134 2
a135 2
      unlink(inam);
      rename(temp,inam);
d138 1
a138 1
      unlink(temp);
d158 1
a158 1
      error("Internal Screen Error. [Writing]");
d161 1
a161 1
      error("Error opening temp file!");
d185 1
a185 1
    unlink(inam);
d202 1
a202 1
      error("Error opening temp file!");
d254 1
a254 1
    unlink(imsg);
d258 2
a259 1
      y+=2;
d268 1
a268 1
    if (su && sul)
d270 3
a272 1
    crwin(6,12,12+x,12+y,tf,tb,2,"");
d277 1
a277 1
      error("This account has expired.");
d282 1
a282 1
      crwin(6,11,12+x,14+y,tf,tb,2,"");
d307 1
a307 1
      error("Error opening temp file!");
d315 1
a315 1
    unlink(inam);
d331 1
d355 13
d369 1
d371 6
a376 1
      error("Out of memory!");
d378 1
a378 1
    error("Internal Screen Error. [Reading]");
d390 1
d414 1
a414 1
      error("Error in creating log file!");
d422 1
a422 1
      error("Error opening temp file!");
d434 1
a434 1
    unlink(temp);
d436 1
a436 1
      error("Error in creating log file!");
d440 5
d455 2
a456 21
     error("Error in creating log file!");
    sprintf(tol,"User entered the %s DOS Shell.",SENTRY);
    tolog(tol);
    fclose(logf);
    cprintf("\n\r  Type \"EXIT\" to leave the %s DOS Shell.\n\r",SENTRY);
    strcpy(tol,getenv("COMSPEC"));
    fnsplit(tol,cp,lo,na,pa);
    strcpy(tol,cp);
    strcat(tol,lo);
    strcpy(temp,"command ");
    strcat(temp,tol);
    strcat(temp," /k prompt [");
    strcat(temp,SENTRY);
    strcat(temp,"] $p$g");
    crwin(1,1,79,24,tf,tb,0,"");
    gotoxy(1,24);
    system(temp);
    if ((logf=fopen(ilog,"a"))==NULL)
      error("Error in creating log file!");
    sprintf(tol,"%s DOS Shell finished.",SENTRY);
    tolog(tol);
d459 6
a464 1
    exit(ec);
d469 1
a469 1
    error("Error in creating log file!");
d472 5
d491 1
d515 1
a515 1
    error("Registration Error - Program Aborted!");
d525 2
a526 1
    ze=fgetc(ini);
d534 1
a534 1
    error("Error in creating log file!");
d550 1
a550 1
  if (pel!=0)
d560 1
a560 1
  if (ael!=0)
d591 2
d598 7
a609 1
  crwin(4,4,76,9,tf,tb,2,"");
d614 1
d630 1
a630 1
    cprintf("Copyright (C) 1995,        ");
d641 1
a641 1
    cprintf("\n\r              [Mike.Bobbitt@@AcadiaU.Ca]");
d652 3
d665 1
a665 1
    strcpy(na,gin(lp,1));
a666 1
    strncpy(na,na,max);
d669 1
a669 2
    strcpy(pa,gin(pp,0));
    strncpy(pa,pa,max);
d671 7
d679 1
d683 8
a690 1
    strcpy(pa,penc(pa));
a715 9
          if (streq(cp,pa))
          {
            fclose(pass);
            cpass();
            fin(0);
            /****
              should go to stamp() and super() as appropriate
            ****/
          }
d717 1
d719 1
a719 1
          if (strcmp(pa,ps))
d721 1
a721 1
            if (strcmp(temp,ps))
d769 1
d772 1
a772 1
    error ("Cannot locate environment!");
@


3.3
log
@Protected files, export settings.
@
text
@d4 4
a7 1

d11 1
a11 1
	#include "crypt.c"
d15 3
a17 10

/*
  FUNCTIONS
*/

/* If it's the shareware version, use this for the "encoding" */
#if !USER
char* UNIXcrypt (char *pw, char *salt)
{
  return(pw);
a20 1
void lockup(void)
d22 1
a22 5
  lockup freezes computer operation by entering an endless loop that the

  user cannot break out of. This is done when a potantial security breach
  has been detected. The user must reset to exit the loop.
  The constant PROD must be true for lockup to occur.
a23 32
{
#if PROD
  short int y;
#endif
  getdate(&td);
  tolog("User Locked Out.");
  flushall();
  fcloseall();
  _chmod(ilog,1,FA_HIDDEN);
  _chmod(imsg,1,FA_HIDDEN);
#if USER
  strcpy(bd,UNIXcrypt(bd,SALT));
#endif
#if PROD
  y=0;
  while (1)
  {
#if USER
    if (y<(MAX-1))
    {
      pa[y]=getch();
      pa[y+1]=0;
      y++;
      if (streq(bd,pa))
        fin(9);
    }
#endif
  }
#else
  fin(1);
#endif
}
d25 1
a25 1
void error(char *s)
d27 6
a32 5
  error(char *s) handles all fatal errors within Sentry. It prints a
  copy of the message to screen and to the log file and proceeds to lock

  the user out of the computer.
  The parameter s contains the error message.
d35 2
a36 33
	crwin(15,8,strlen(s)+22,12,YELLOW,LIGHTRED,2,"SYSTEM ERROR");
	cprintf("\n\r   ");
	cprintf("%s",s);
	cprintf("\n\r");
  tolog(s);
  lockup();
}

int tsk(void)
/*
  tsk(void) is the function called when the user attempts to exit via
  CTRL-C or CTRL-BREAK. The attempt is logged, and the computer is locked
  up to prevent any further attempts.
*/
{
  tolog("User Attempted to Exit.");
  lockup();
  return(1);
}

char blch(void)
/*
  blch(void) is used at all input points instead of getch(). blch()
  allows the screen saver to activate at the designated times.
*/
{
char bin,scr[80*25*2];
long st,en;
int tx,ty;
  getdate(&td);
  gettime(&nw);
  st=dostounix(&td,&nw)+scrb;
  while (!kbhit())
d38 2
a39 48
    getdate(&td);
    gettime(&nw);
    en=dostounix(&td,&nw);
    if (en>st)
    {
      /*
        BLANK SCREEN
      */
      tx=wherex();
      ty=wherey();
      window(1,1,80,25);
      if (!gettext(1,1,80,25,scr))
        error("Internal Screen Error. [Reading]");
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
      bin=getch();
      /*
        RESTORE SCREEN
      */
      if (!puttext(1,1,80,25,scr))
				error("Internal Screen Error. [Writing]");
      window(rclf,rctop,rcri,rcbot);
      txb(rcbak);
      txc(rcfrg);
      gotoxy(tx,ty);
      getdate(&td);
      gettime(&nw);
      st=dostounix(&td,&nw)+scrb;
    }
d41 1
a41 61
  bin=getch();
  return(bin);
}

void prd(void)
{
  if (sscanf(ti,"%lu %lu %lu %d %d %lu",&ut,&ed,&pe,&fla,&ntl,&ae)!=6)
    error("Error in Account Information.");
}

void guser(int us)
{
short int u;
	for(u=1;u<us;u++)
	{
		fgets(lo,MAX,pass);
		fgets(ps,MAX,pass);
		fgets(ti,MAX,pass);
		fputs(lo,npas);
		fputs(ps,npas);
		fputs(ti,npas);
	}
	fgets(lo,MAX,pass);
	fgets(ps,MAX,pass);
	fgets(ti,MAX,pass);
	prd();
}

void tolog(char *s)
/*
  tolog(char *s) makes an entry to the log file. All output to the log
  file is routed through tolog(char *s). Each individual entry is
  stamped with the current time and date.
  The parameter s contains the message to write to the log.
*/
{
  getdate(&td);
  if (df)
    fprintf(log,"[%02d/%02d/%02d -",td.da_day,td.da_mon,td.da_year);
  else
    fprintf(log,"[%02d/%02d/%02d -",td.da_mon,td.da_day,td.da_year);
  gettime(&nw);
  fprintf(log," %02d:%02d:%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,s);
}

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
d43 11
a53 8
    gi[x]=0;
    ar[x]=0;
  }
  x=0;
  while (x<(MAX-1))
  {
    ar[x]=blch();
    if ((ar[x]==27) && _bk)
d55 2
a56 2
      bk=1;
      break;
d58 4
a61 1
    if ((ar[x]==13) || (ar[x]==10))
d63 12
a74 8
      gi[x]=0;
      if ((ar[x]==10) && ech)
        sul=1;
      break;
    }
    else
    {
      if (!((ar[x]<32) || (ar[x]>125)))
d76 8
a83 2
        if (ech || (pec=='!'))
          cprintf("%c",ar[x]);
d85 18
a102 10
          if (pec!='?')
            cprintf("%c",pec);
/****
      Enable code to return only up to max characters.
        if (x<max)
          gi[x]=ar[x];
        else
          gi[x]=0;
****/
        gi[x]=ar[x];
d105 1
a105 29
        x--;
    }
    if ((ar[x+1]==8) && (x>=0))
    {
      ar[x+1]=0;
      x--;
      cprintf("%c %c",8,8);
    }
    x++;
  }
  cprintf("\n\r");
  return(gi);
}

void txb(short int tc)
/*
  txb() handles text background colour changes. If col=0, no colour chang
es
  are permitted (Text is either highlighted or not).
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
d108 2
d111 3
a113 2
      textbackground(BLACK);
      textcolor(DFC);
a114 54
  }
}

char* penc(char *te)
/*
  penc() encodes passwords. If the password is over 8 characters long, th
en
  it is encoded in blocks of 8 characters. penc() also handles the SuperU
ser
  stamp.
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

long gdate(void)
/*
	gdate(void) is a function called when the user is expected to enter a
	date. The function prompts the user for the date, warns him if it falls
	in the past, and returns it in standard UNIX format as a long.
*/
{
  char ho[MAX],opt;
  long di,ck;
  struct date ld;
  struct time lt;
  short int x=0;
  getdate(&ld);
  lt.ti_hour=0;
  lt.ti_min=0;
  lt.ti_sec=1;
  lt.ti_hund=0;
  di=dostounix(&ld,&lt);
  lt.ti_sec=0;
  while (x==0)
  {
    x=1;
    cprintf("\n\r\n\rEnter 'N' at year prompt to assign no expiry date.");
    strcpy(ho,gin("\n\rEnter the year (4 digits): ",1));
    if ((streq(ho,"n")) || (streq(ho,"N")))
      ck=0;
d117 13
a129 136
      ld.da_year=atoi(ho);
      if (ld.da_year<100)
      {
        cprintf("\n\rYear must be 4 digits!");
        x=0;
      }
      else
      {
        strcpy(ho,gin("\n\rEnter the month (2 digits): ",
            1));
        ld.da_mon=atoi(ho);
        strcpy(ho,gin("\n\rEnter the day (2 digits): ",
            1));
        ld.da_day=atoi(ho);
        ck=dostounix(&ld,&lt);
      }
    }
    if (x && ck && (di>ck))
    {
      cprintf("\n\rThat date is in the past!");
      cprintf("\n\rAre you sure you want to use it? ");
      opt=blch();
      if ((opt!='y') && (opt!='Y'))
        x=0;
    }
  }
  return(ck);
}

void setp(void)
/*
  setp(void) is the function called to input, verify and store a new pass
word.
  This function is called directly when the users old password expires, a
nd
  via cpass(void) when a user wishes to change their password. The
  variable un is set the the number (within the password file) of the
  user who is changing passwords. If the number is negative, then it is
  possible to abort the operation by pressing ESCAPE.
*/
{
	short int err=1,x=0;
  if (un<0)
  {
    un*=-1;
    x=1;
  }
  while (err!=0)
  {
    err=0;
    tmpnam(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error("Error opening temp file!");
		pass=ffwd(2,npas);
		guser(un);
		strcpy(na,ps);
		chop2(na);
		chop2(ps);
		sul=0;
		if (ps[strlen(ps)-1]==STAMP)
		{
			sul=1;
			chop(na);
		}
		_bk=x;
		strcpy(pa,gin("\n\r\n\rNew Password:",0));
		strncpy(pa,pa,max);
		if (!(bk && x))
		{
			if ((strlen(pa)>max) || (strlen(pa)<min))
				err=2;
			if (sul)
			{
				pa[strlen(pa)+1]=0;
				pa[strlen(pa)]=STAMP;
			}
			strcpy(pa,penc(pa));
			_bk=x;
			strcpy(ps,gin("Verify Password:",0));
			strncpy(ps,ps,max);
			if (!(bk && x))
			{
				if (sul)
				{
					ps[strlen(ps)+1]=0;
					ps[strlen(ps)]=STAMP;
				}
				strcpy(ps,penc(ps));
				if (strcmp(pa,ps))
					err=3;
				else
					if (!(strcmp(na,ps) || x))
						err=1;
				switch (err)
				{
				case 1:
					cprintf("You cannot use the same password.\n\r");
					break;
				case 2:
					cprintf("Passwords must be between ");
					cprintf("%d",min);
					cprintf(" and ");
					cprintf("%d",max);
					cprintf(" characters.\n\r");
					break;
				case 3:
					cprintf("Password not verified!\n\r");
					break;
				}
			}
			else
				strcpy(ps,na);
		}
		else
			strcpy(ps,na);
		if (!sul)
		{
			ps[strlen(ps)+2]=0;
			ps[strlen(ps)+1]='\n';
			ps[strlen(ps)]='\r';
		}
		else
		{
			ps[strlen(ps)+3]=0;
			ps[strlen(ps)+2]='\n';
			ps[strlen(ps)+1]='\r';
			ps[strlen(ps)]=STAMP;
		}
		fputs(lo,npas);
		chop2(lo);
		sprintf(tol,"%s's password has been changed.",lo);
		tolog(tol);
		fputs(ps,npas);
		if (pe)
			pe=pel;
		pwr;
a140 9
char* gstr(void)
{
  char s[MAX];
  if ((fgets(s,MAX,ini))==NULL)
    error("Error in Initialization Settings!");
  chop2(s);
  return(s);
}

d156 3
a158 1
    tmpnam(temp);
d161 23
a183 23
		pass=ffwd(2,npas);
		guser(un);
		unixtodos(ut,&td,&nw);
		if (df)
			sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
		else
			sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
		sprintf(ti," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
		strcat(tol,ti);
		fputs(lo,npas);
		fputs(ps,npas);
		getdate(&td);
		gettime(&nw);
		if (ut<ael)  /* If the account has been inactive too long */
			ed=dostounix(&td,&nw);
		ut=dostounix(&td,&nw);
		if ((fla>=ntl) && (ntl>0)) /* If # failed login attempts > max */
			ed=ut;
		x=fla;
		fla=0;
		pwr;
		fla=x;
		fcd(pass,npas);
d185 15
a199 15
		rename(temp,inam);
		x=fnsplit(imsg,dr,di,fi,ex);
		tmpnam(temp);
		if (x & DIRECTORY)
		{
			strcpy(lo,temp);
			strcpy(temp,di);
			strcat(temp,lo);
		}
		if (x & DRIVE)
		{
			strcpy(lo,temp);
			strcpy(temp,dr);
			strcat(temp,lo);
		}
d209 1
a209 1
					crwin(3,3,77,11,tf,tb,2,"Message");
d251 1
a251 1
		fclose(msg);
d256 1
a256 1
		if (strcmp(win,"") && !(su && sul) && !zm)
d268 1
a268 1
		crwin(6,12,12+x,12+y,tf,tb,2,"");
d278 1
a278 1
			crwin(6,11,12+x,14+y,tf,tb,2,"");
d301 1
a301 1
    tmpnam(temp);
d304 6
a309 6
		pass=ffwd(2,npas);
		guser(un);
		fla++;
		fputs(lo,npas);
		fputs(ps,npas);
		pwr;
a320 225
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor,char *tt)
/*
  crwin() is the function used to create a window. If the variable wm==0,
  no windows are created.

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
          delay(120);
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
*/
{
  char scr[80*1*2];
  int x;
  if (!gettext(lf,bot+1,ri,bot+1,scr))
    error("Internal Screen Error. [Reading]");
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
    error("Internal Screen Error. [Writing]");
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

FILE* ffwd(int sp,FILE* dmp)
/*
  ffwd() scans the file for the "sp th" marker. If dmp is defined (file
  stream), then input is buffered and written out to dmp.
*/
{
int yz,zz,bp;
FILE* fn;
char buf[BUFSZ+2],ff[DIVLEN+2];
  if ((fn=fopen(inam,"rb"))==NULL)
    error("Error Reading Data Segment! [Open]");
  bp=0;
  for(zz=0;zz<=DIVLEN;zz++)
    ff[zz]=0;
  sp++;
  while(sp)
  {
    yz=1;
    while(yz && !feof(fn))
    {
      buf[bp]=fgetc(fn);
      for(zz=0;zz<DIVLEN-1;zz++)
        ff[zz]=ff[zz+1];
      ff[zz]=buf[bp];
      ff[zz+1]=0;
      yz=!streq(ff,DIV);
      if (bp==BUFSZ)
      {
        if (dmp)
          for(zz=0;zz<=bp;zz++)
            fputc(buf[zz],dmp);
        bp=-1;
      }
      bp++;
    }
    if (yz)
      error("Error Reading Data Segment! [Scan]");
    sp--;
  }
  if (dmp)
    for(zz=0;zz<bp;zz++)
      fputc(buf[zz],dmp);
  return(fn);
}

void fcd(FILE* fn,FILE* dmp)
/*
  fcd() closes file str while dumping any remaining information into
  dmp.
*/
{
int zz,bp;
char buf[BUFSZ+2];
  bp=0;
  while(!feof(fn))
  {
		buf[bp]=zenc(fgetc(fn));
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

#if !USER
void shar(void)
/*
  shar() displays a shareware window if the shareware version is being
  compiled.
*/
{
  crwin(10,5,67,10,YELLOW,LIGHTRED,2,"");
  cprintf("\n\r                UNREGISTERED VERSION!!\n\r");
	cprintf("     Please Register if you intend to use %s.\n\r",SENTRY);
  tolog("*********************************");
  tolog("* THIS IS AN UNREGISTERED COPY. *");
  tolog("*       PLEASE REGISTER.        *");
  tolog("*********************************");
  sleep(3);
}
#endif

d323 2
a324 2
	init(void) is called on startup. It initializes and assigns values to
	some variables and then passes execution back to main(void).
d327 4
a330 4
  short int x;
  long nd;
  struct date xd;
  struct time xt;
d360 3
a362 3
	ltoa(nd,bd,10);
	un=0;
	zze=0; /* Encryption off */
d378 3
d384 1
d386 3
a388 6
#if !USER
  shar();
#endif
	if (zm)
	{
    if ((log=fopen(ilog,"a"))==NULL)
d390 21
a410 22
		sprintf(tol,"%s run in protected mode.",inam);
		tolog(tol);
		tmpnam(temp);
		temp[strlen(temp)-1]=zex[strlen(zex)-1];
		temp[strlen(temp)-2]=zex[strlen(zex)-2];
		temp[strlen(temp)-3]=zex[strlen(zex)-3];
		if ((pass=fopen(temp,"wb"))==NULL)
			error("Error opening temp file!");
		pass=ffwd(3,NULL);
		zze=-1;
		fcd(pass,npas);
		zze=0;
		fclose(log);
		crwin(1,1,79,24,tf,tb,0,"");
		gotoxy(1,24);
		strcpy(tol,temp);
		strcat(tol," ");
		strcat(tol,win);

		system(tol);
		unlink(temp);
    if ((log=fopen(ilog,"a"))==NULL)
d412 5
a416 4
		tolog("Execution Complete.");
    fclose(log);
		exit(ec);
	}
d419 6
a424 6
		if (su && sul)
		{
			sprintf(tol,"%s DOS Shell",SENTRY);
			crwin(4,6,50,10,tf,tb,2,tol);
		}
    if ((log=fopen(ilog,"a"))==NULL)
d426 14
a439 13
		sprintf(tol,"User entered the %s DOS Shell.",SENTRY);
		tolog(tol);
    fclose(log);
		cprintf("\n\r  Type \"EXIT\" to leave the %s DOS Shell.\n\r",SENTRY);
    /****
      Gives entire path and filename when only path is required.

		sprintf(temp,"command %s /k prompt [%s] $p$g",getenv("COMSPEC"),SENTRY);
    ****/
		strcpy(temp,"command /k prompt [");
		strcat(temp,SENTRY);
		strcat(temp,"] $p$g");
		crwin(1,1,79,24,tf,tb,0,"");
d442 1
a442 1
    if ((log=fopen(ilog,"a"))==NULL)
d444 4
a447 3
		sprintf(tol,"%s DOS Shell finished.",SENTRY);
		tolog(tol);
    fclose(log);
d450 1
a450 1
	crwin(1,1,79,24,tf,tb,0,"");
d452 4
d467 5
a471 5
  unsigned env_addr,seglen;
  char value[MAX],**env_var,envar[MAX],v[DIVLEN+2];
  short int err=1,ero=0,try=1,x,unn,lc,index;
  int count;
  long y;
d474 6
d500 4
a503 3
		zm=1;
		strcpy(zex,gstr());
		ze=atoi(gstr());
d505 1
a505 1
	if (strcmp(v,ver)>0)
d510 3
d522 1
d546 1
a546 1
	scrb=atoi(gstr());
a574 3
  if ((log=fopen(ilog,"a"))==NULL)
    error("Error in creating log file!");
  tolog("-----------------------------");
d576 1
a576 1
  shar();
d578 1
a578 1
	crwin(5,4,75,19,tf,tb,2,"");
d586 1
a586 1
    cprintf("NightShade Computing");
d588 1
a588 1
    cprintf("       Registered to");
d612 4
a615 1
  cprintf("\n\r\n\r");
d621 1
d631 1
d648 1
a648 1
		while(((fgets(lo,MAX,pass))!=NULL) && (!streq(lo,DIV)))
d659 6
a664 6
					x=0;
					if (ps[strlen(ps)-1]==STAMP)
					{
						chop(ps);
						x=1;
					}
d672 4
a675 4
						fin(0);
						/****
							should go to stamp() and super() as appropriate
						****/
d677 1
a677 1
          strcpy(cp,na);
d683 1
a683 1
						else
d751 2
@


3.2
log
@Mini-mail system.
@
text
@d6 4
d11 1
d75 4
a78 2
  crwin(15,8,strlen(s)+22,12,YELLOW,LIGHTRED,2);
  cprintf("\n\r   %s\n\r",s);
d101 3
a103 3
  char bin,scr[80*25*2];
  long st,en;
  int tx,ty;
d124 1
a124 1
      getdate(&td);
d148 1
a148 1
        error("Internal Screen Error. [Writing]");
a164 4
/****  To preserve backward compatibility, enable this code.
  {
    if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
****/
d166 18
a183 8
/****
      else
    {
      fla=0;
      ntl=ltl;
    }
  }
***/
d323 3
a325 5
  gdate(void) is a function called when the user is expected to enter a d
ate.
  The function prompts the user for the date, warns him if it falls in th
e
  past, and returns it in standard UNIX format as a long.
d390 1
a390 1
  short int err=1,y,x=0;
a398 1
    y=0;
d402 83
a484 96
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      y++;
      fgets(ps,MAX,pass);
      strcpy(na,ps);
      chop2(na);
      fgets(ti,MAX,pass);
      prd();
      if (y!=un)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        chop2(ps);
        sul=0;
        if (ps[strlen(ps)-1]==STAMP)
        {
          sul=1;
          chop(na);
        }
        _bk=x;
				strcpy(pa,gin("\n\r\n\rNew Password:",0));
				strncpy(pa,pa,max);
        if (!(bk && x))
        {
          if ((strlen(pa)>max) || (strlen(pa)<min))
            err=2;
          if (sul)
          {
            pa[strlen(pa)+1]=0;
            pa[strlen(pa)]=STAMP;
          }
          strcpy(pa,penc(pa));
          _bk=x;
					strcpy(ps,gin("Verify Password:",0));
					strncpy(ps,ps,max);
          if (!(bk && x))
          {
            if (sul)
            {
              ps[strlen(ps)+1]=
                  0;
              ps[strlen(ps)]=STAMP;
            }
            strcpy(ps,penc(ps));
            if (strcmp(pa,ps))
              err=3;
              else
              if (!(strcmp(na,ps) || x))
                err=1;
            switch (err)
            {
            case 1:
              cprintf("You cannot use the same password.\n\r");
              break;
            case 2:
              cprintf("Passwords must be between %d and %d characters.\n\r",
                  min,max);
              break;
            case 3:
              cprintf("Password not verified!\n\r");
              break;
            }
          }
          else
            strcpy(ps,na);
        }
        else
          strcpy(ps,na);
        if (!sul)
        {
          ps[strlen(ps)+2]=0;
          ps[strlen(ps)+1]='\n';
          ps[strlen(ps)]='\r';
        }
        else
        {
          ps[strlen(ps)+3]=0;
          ps[strlen(ps)+2]='\n';
          ps[strlen(ps)+1]='\r';
          ps[strlen(ps)]=STAMP;
        }
        fputs(lo,npas);
        chop2(lo);
        sprintf(tol,"%s's password has been changed.",lo);
        tolog(tol);
        fputs(ps,npas);
        if (pe)
          pe=pel;
        pwr;
      }
    }
a495 184
char *endptr(p)
char *p;
{
  while (*p) p++;
  return p;
}

int get_env_index(char *var, char **env_var)
{
  /*
   * Find the index into the env_var array of the variable <var>.
      If not
   * found, returns the index of the terminating null entry
   */
  register int i;
  char *temp;
  MEMCHECK(temp = (char *)malloc(strlen(var)+2)) ;
  strcpy( temp, var);
  strupr(strcat(temp,"="));
  for( i = 0; env_var[i]; i++ ) {
    if(strstr(env_var[i], temp) == env_var[i]) break;
  }
  free(temp);
  return(i);
}


int getenvseg(unsigned *envseg )
{
  /*
   * Try to locate the parent environment and fill in the segment a
      ddress
   * This routine has some OS version dependencies
   * Returns  1  if environment found
   *      0  if environment not found
   */
  unsigned  ppsp;
  union REGS  regs;
  int status ;

  regs.x.ax = 0xD44D;           /* 4dos signature value */
  regs.x.bx = 0;
  int86(0x2F, &regs, &regs);        /* TSR multiplex interrput */
  ppsp   = regs.x.cx;           /* psp of immediate parent shell */

  if( regs.x.ax == 0x44dd && ppsp == *(unsigned far *)MK_FP(_psp,0x16) ) {
    /*
         * good, we are running 4dos - AND it is our parent
         * in this case we don't care about dos version
         */
    *envseg =  *(unsigned far *)MK_FP(ppsp,0x2C);
  } else {
    /*
         * Follow the pointers back to our parent psp and fro
        m there get the
         * parent environment segment address
         * With early command.com (pre 3.3) the lowest level
        shell did not fill
         * in the environment segment (it is 0) but we can st
        ill find the
         * environment since it always follows the lowest lev
        el shell directly
         */
    ppsp = *(unsigned far *)MK_FP(_psp,0x16);
    *envseg =  *(unsigned far *)MK_FP(ppsp,0x2C);
    if ((*envseg == 0) &&
        (_osmajor <= 2 || (_osmajor == 3 && _osminor <= 20))) {
      /*
             * we have the pre 3.3 master command.com -
           have to assume that the
             * environment segment directly follows the
           program segment
             * so get the length from the MCB and add i
          t to ppsp
             */
      *envseg = ppsp + *(unsigned far *)MK_FP(ppsp - 1,
          3) + 1;
    }
  }
  /*
     * Verify that the owner of the envseg matches the ppsp we got
      above
     * - just to be a little paranoid
     */
  if ( *(unsigned far *)MK_FP((*envseg)-1, 1) != ppsp) {
    *envseg = 0 ;   /* something wrong :-( */
    status  = 0;
  } else {
    status  = 1 ;
  }
  return(status);
}


unsigned get_env_var(unsigned env_addr, char ***env_var, int *count)
{
  /*
   * Copy the parent environment from the segment address given in
      env_addr, into
   * the memory block pointed to by env_blk.
   * Extract pointers to the start of each variable and build array
       env_var.
   * Return the length of the environment block, (bytes, always a m
      ultiple of 16)
   */
  static char *env_blk;
  unsigned i, len, offset;
  unsigned seglen;

  seglen = *(unsigned far *)MK_FP(env_addr - 1, 3) * 16;
  if ((env_blk = (char *)malloc(seglen)) == (char *)NULL)
    error ("Cannot allocate memory for environment block");

  movedata(env_addr, 0, _DS, (unsigned)&env_blk[0], seglen);
  /*
     * make one pass through, counting variables, and allocate spac
      e for the
     * env_var array.  Allow for two extra entries - one to add a n
      ew variable
     * and a terminating null.
     */
  i = 0;
  offset = 0;
  do
  {
    offset += strlen(env_blk+offset) + 1;
    i++;
  } while(*(env_blk+offset));
  MEMCHECK(*env_var = (char **)malloc((i+2)*sizeof(char **))) ;
  *count = i;

  /* load pointers to each of the strings in the array env_var[] */
        i = 0;
  offset = 0;
  do
  {
    len = strlen(env_blk+offset);
    (*env_var)[i] = env_blk+offset;
    offset += len+1;
    i++;
  } while(*(env_blk+offset));
  (*env_var)[i] = NULL;       /* terminate with an extra null */
  return (seglen);
}


void put_env_var(unsigned env_addr, unsigned seglen, char **env_var)
{
  /*
   * Copy the modified environment from the allocated data area, us
      ing the
   * env_var array of pointers, into the memory block pointed to by
       env_addr.
   */
  char  *var_addr;
  unsigned offset, len, i;
  unsigned zero = 0;
  /*
     * Cycle through once to test for environment overflow.  If ove
      rflow,
     * nothing is copied to the old environment block
     */
  for( i=0, offset=0, len=0; env_var[i]; offset+=len, i++)  {
    len = strlen(env_var[i]) + 1;
    if (offset+len >= seglen-2)   /* overflow */
      error("Environment overflow - not modified.");
  }
  /*
     * Now actually copy the strings
     */
  for( i=0, offset=0, len=0; env_var[i]; offset+=len, i++)  {
    len = strlen(env_var[i]) + 1;
    if (len == 1) {
      /* this entry was null - skip it */
      len = 0;
      continue;
    }
    var_addr = env_var[i];
    movedata(_DS, (unsigned)var_addr, env_addr, offset, len);
  }
  /* stuff a zero word at the end of the environment block */
  movedata(_DS, (unsigned)&zero, env_addr, offset, sizeof(unsigned));
}

d515 1
a515 1
short int y=0,x;
d517 1
d523 23
a545 38
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=un)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        prd();
        unixtodos(ut,&td,&nw);
        if (df)
          sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
          else
          sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
        sprintf(ti," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
        strcat(tol,ti);
        fputs(lo,npas);
        fputs(ps,npas);
        getdate(&td);
        gettime(&nw);
        if (ut<ael)  /* If the account has been inactive too long */
          ed=dostounix(&td,&nw);
        ut=dostounix(&td,&nw);
        if ((fla>=ntl) && (ntl>0)) /* If # failed login attempts > max */
          ed=ut;
        x=fla;
        fla=0;
        pwr;
        fla=x;
      }
    }
    fcd(pass,npas);
d547 15
a561 2
    rename(temp,inam);
    tmpnam(temp);
d571 1
a571 1
          crwin(3,3,77,11,tf,tb,2);
d587 1
a587 1
          x=getch();
a611 1
      fclose(msg);
d613 1
d618 1
a618 1
    if (strcmp(win,"") && !(su && sul))
d630 1
a630 1
    crwin(6,12,12+x,12+y,tf,tb,2);
d640 1
a640 1
      crwin(6,11,12+x,14+y,tf,tb,2);
a660 1
  short int y=0;
d666 6
a671 21
    pass=ffwd(2,npas);
    while((fgets(lo,MAX,pass))!=NULL)
    {
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=un)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        prd();
        fla++;
        fputs(lo,npas);
        fputs(ps,npas);
        pwr;
      }
    }
d683 1
a683 2
void crwin(short int lf,short int top,short int ri,short int bot,short int
frg,short int bak,short int bor)
d697 2
a698 1
          2 - Double Border
d728 1
a728 2
          wdr(cx-z*(ri-lf)/(bot-top),cy-z,cx+
              z*(ri-lf)/(bot-top),cy+z,bak,bor);
d733 1
a733 1
      wdr(lf,top,ri,bot,bak,bor);
d746 1
a746 2
void wdr(short int lf,short int top,short int ri,short int bot,short int
bak,short int bor)
d793 6
a798 1
  window(lf,bot+1,ri,bot+1);
d822 3
a824 3
  int yz,zz,bp;
  FILE* fn;
  char buf[BUFSZ+2],ff[DIVLEN+2];
d861 1
a861 1
void fcd(FILE* str,FILE* dmp)
d867 4
a870 2
  char c0;
  while(!feof(str))
d872 10
a881 3
    c0=fgetc(str);
    if (!feof(str))
      fputc(c0,dmp);
d883 4
a886 1
  fclose(str);
d897 1
a897 1
  crwin(10,5,67,10,YELLOW,LIGHTRED,2);
d899 1
a899 1
  cprintf("     Please Register if you intend to use Sentry.\n\r");
d910 2
a911 3
  init(void) is called on startup. It initializes and assigns values to s
ome
  variables and then passes execution back to main(void).
d947 6
a952 3
  ltoa(nd,bd,10);
  sul=0;
  _bk=0;
d972 31
d1005 5
a1009 2
    if (su && sul)
      crwin(4,6,50,10,tf,tb,2);
d1012 2
a1013 1
    tolog("User entered the Sentry DOS Shell.");
d1015 1
a1015 1
    cprintf("\n\r  Type \"EXIT\" to leave the Sentry DOS Shell.\n\r");
d1019 1
a1019 1
    sprintf(temp,"command %s /k prompt [Sentry] $p$g",getenv("COMSPEC"));
d1021 4
a1024 2
    strcpy(temp,"command /k prompt [Sentry] $p$g");
    crwin(1,1,79,24,tf,tb,0);
d1029 2
a1030 1
    tolog("Sentry DOS Shell finished.");
d1034 1
a1034 1
  crwin(1,1,79,24,tf,tb,0);
a1043 1

d1071 8
a1078 1
  if (strcmp(v,ver)>0)
d1115 1
a1115 1
  scrb=atoi(gstr());
d1150 1
a1150 1
  crwin(5,4,75,19,tf,tb,2);
d1198 2
a1199 2
		strcpy(na,gin(lp,1));
		strncpy(na,na,max);
d1203 1
a1203 1
		strncpy(pa,pa,max);
d1215 1
a1215 1
    while((fgets(lo,MAX,pass))!=NULL)
a1221 6
      x=0;
      if (ps[strlen(ps)-1]==STAMP)
      {
        chop(ps);
        x=1;
      }
d1226 6
d1239 4
a1242 1
            fin(0);
d1250 1
a1250 1
              else
@


3.1
log
@Password echo char & log DOS shell.
@
text
@d37 1
d70 1
a70 1
  crwin(15,10,strlen(s)+22,14,YELLOW,LIGHTRED,2);
d108 2
a109 2
              BLANK SCREEN
            */
d138 2
a139 2
              RESTORE SCREEN
            */
d155 18
d184 1
a184 1
    else
d187 1
a187 2
  fprintf(log," %02d:%02d:%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,
      s);
d192 7
a198 8
  gin() is the general input routine. It gets input from the keyboard and
  returns it the entered string. If ech is set to 1, the input is echoed
to
  the screen. If ech = 0, the output is echoed as *'s. If the user is
  logging in as a SuperUser, sul is set to 1.
  gin() takes a character pointer (the string to be displayed before inpu
t)
  and an integer (echo) for parameters.
d230 1
a230 1
				if (ech || (pec=='!'))
d232 5
a236 3
				else
					if (pec!='?')
						cprintf("%c",pec);
d239 1
a239 1
				else
d241 2
d336 1
a336 1
      else
a378 1
  long ut,ed,pe;
d400 1
a400 11
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
d417 2
a418 1
        strcpy(pa,gin("\n\r\n\rNew Password:",0));
d421 1
a421 2
          if ((strlen(pa)>max) || (strlen(pa)<
              min))
d430 2
a431 2
          strcpy(ps,gin("Verify Password:",
              0));
d480 1
a480 2
        sprintf(tol,"%s's password has been changed.",
            lo);
d485 1
a485 2
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,
            pe,fla,ntl);
d622 2
a623 1
  do  {
d633 2
a634 1
  do  {
d702 2
a703 2
  short int y=0,x;
  long ut,ed,pe;
d723 1
a723 12
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
d726 1
a726 2
          sprintf(tol,"Last login was on %02d/%02d/%02d at",
              td.da_day,td.da_mon,td.da_year);
d728 2
a729 4
          sprintf(tol,"Last login was on %02d/%02d/%02d at",
              td.da_mon,td.da_day,td.da_year);
        sprintf(ti," %02d:%02d:%02d\n\r",nw.ti_hour,
            nw.ti_min,nw.ti_sec);
d735 2
d738 1
a738 1
        if ((fla>=ntl) && (ntl>0))
d740 4
a743 2
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,
            pe,0,ntl);
d749 56
d811 1
a811 2
      sprintf(ti,"%d invalid login attempt(s) have occurred since your last login.\n\r",
          fla);
a849 1
  long ut,ed,pe;
d869 1
a869 12
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
d873 1
a873 2
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,
            pe,fla,ntl);
d1110 17
a1147 1

d1155 1
d1163 4
a1166 4
		if ((log=fopen(ilog,"a"))==NULL)
		 error("Error in creating log file!");
		tolog("User entered the Sentry DOS Shell.");
		fclose(log);
d1168 5
d1176 5
a1180 5
		system(temp);
		if ((log=fopen(ilog,"a"))==NULL)
		 error("Error in creating log file!");
		tolog("Sentry DOS Shell finished.");
		fclose(log);
d1226 1
d1235 23
a1257 10
	strcpy(cp,gstr());
	strcpy(ssm,gstr());
	pec=ssm[0];
	pel=atol(gstr());
  pel++;
  getdate(&td);
  gettime(&nw);
  y=dostounix(&td,&nw);
  pel*=86400L;
  pel+=y;
d1301 1
a1301 1
		cprintf("NightShade Computing");
d1303 1
a1303 1
		cprintf("       Registered to");
d1307 2
a1308 1
    cprintf("Sentry ");
d1313 1
a1313 1
		cprintf("Copyright (C) 1995,        ");
d1319 1
a1319 1
		cprintf("Michael A. Bobbitt");
d1321 1
a1321 1
		cprintf("         Registration #: ");
d1324 1
a1324 1
		cprintf("\n\r              [Mike.Bobbitt@@AcadiaU.Ca]");
d1333 1
d1341 2
a1342 1
    strcpy(na,gin(lp,1));
d1346 1
d1384 1
@


3.0
log
@Sentry V3.0
Hardcoded ini and pwd files.
Exploding windows.
Other minor changes.
@
text
@d12 1
d23 1
d30 1
a30 1
short int y;
d64 1
d89 2
a90 1
  NO DESCRIPTION
d93 3
a95 3
char bin,scr[80*25*2];
long st,en;
int tx,ty;
d107 2
a108 2
        BLANK SCREEN
      */
d137 2
a138 2
        RESTORE SCREEN
      */
d165 1
a165 1
  else
d168 2
a169 1
  fprintf(log," %02d:%02d:%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,s);
d175 2
a176 1
  returns it the entered string. If ech is set to 1, the input is echoed to
d179 2
a180 1
  gin() takes a character pointer (the string to be displayed before input)
d184 2
a185 2
short int x;
char gi[MAX],ar[MAX];
d213 1
a213 1
        if (ech)
d215 3
a217 2
        else
          cprintf("*");
d220 1
a220 1
        else
a237 10
void txc(short int tc)
/*
  txc() handles text colour changes. If col=0, no colour changes are
  permitted.
*/
{
  if (col)
    textcolor(tc);
}

d240 2
a241 1
  txb() handles text background colour changes. If col=0, no colour changes
d247 1
a247 1
  else
d264 4
a267 2
  penc() encodes passwords. If the password is over 8 characters long, then
  it is encoded in blocks of 8 characters. penc() also handles the SuperUser
d273 2
a274 2
int x=0,y;
char pret[MAX],p8[MAX];
d289 4
a292 2
  gdate(void) is a function called when the user is expected to enter a date.
  The function prompts the user for the date, warns him if it falls in the
d296 5
a300 5
char ho[MAX],opt;
long di,ck;
struct date ld;
struct time lt;
short int x=0;
d315 1
a315 1
    else
d325 2
a326 1
        strcpy(ho,gin("\n\rEnter the month (2 digits): ",1));
d328 2
a329 1
        strcpy(ho,gin("\n\rEnter the day (2 digits): ",1));
d348 4
a351 2
  setp(void) is the function called to input, verify and store a new password.
  This function is called directly when the users old password expires, and
d358 2
a359 2
long ut,ed,pe;
short int err=1,y,x=0;
d380 2
a381 1
      if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
d385 1
a385 1
        else
d410 2
a411 1
          if ((strlen(pa)>max) || (strlen(pa)<min))
d420 2
a421 1
          strcpy(ps,gin("Verify Password:",0));
d426 2
a427 1
              ps[strlen(ps)+1]=0;
d433 1
a433 1
            else
d442 2
a443 1
              cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
d470 2
a471 1
        sprintf(tol,"%s's password has been changed.",lo);
d476 2
a477 1
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
d500 5
a504 4
/*
 * Find the index into the env_var array of the variable <var>.  If not
 * found, returns the index of the terminating null entry
 */
d520 7
a526 6
/*
 * Try to locate the parent environment and fill in the segment address
 * This routine has some OS version dependencies
 * Returns  1  if environment found
 *      0  if environment not found
 */
d538 3
a540 3
     * good, we are running 4dos - AND it is our parent
     * in this case we don't care about dos version
     */
d544 10
a553 6
     * Follow the pointers back to our parent psp and from there get the
     * parent environment segment address
     * With early command.com (pre 3.3) the lowest level shell did not fill
     * in the environment segment (it is 0) but we can still find the
     * environment since it always follows the lowest level shell directly
     */
d557 1
a557 1
      (_osmajor <= 2 || (_osmajor == 3 && _osminor <= 20))) {
d559 9
a567 5
       * we have the pre 3.3 master command.com - have to assume that the
       * environment segment directly follows the program segment
       * so get the length from the MCB and add it to ppsp
       */
      *envseg = ppsp + *(unsigned far *)MK_FP(ppsp - 1, 3) + 1;
d571 4
a574 3
   * Verify that the owner of the envseg matches the ppsp we got above
   * - just to be a little paranoid
   */
d587 9
a595 6
/*
 * Copy the parent environment from the segment address given in env_addr, into
 * the memory block pointed to by env_blk.
 * Extract pointers to the start of each variable and build array env_var.
 * Return the length of the environment block, (bytes, always a multiple of 16)
 */
d606 8
a613 5
   * make one pass through, counting variables, and allocate space for the
   * env_var array.  Allow for two extra entries - one to add a new variable
   * and a terminating null.
   */
  i = 0;  offset = 0;
d622 2
a623 1
  i = 0;  offset = 0;
d637 6
a642 4
/*
 * Copy the modified environment from the allocated data area, using the
 * env_var array of pointers, into the memory block pointed to by env_addr.
 */
d647 4
a650 3
   * Cycle through once to test for environment overflow.  If overflow,
   * nothing is copied to the old environment block
   */
d657 2
a658 2
   * Now actually copy the strings
   */
d675 1
a675 1
char s[MAX];
d692 2
a693 2
short int y=0,x;
long ut,ed,pe;
d713 2
a714 1
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
d716 2
a717 1
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
d719 1
a719 1
          else
d727 7
a733 4
          sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
        sprintf(ti," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
d742 2
a743 1
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,0,ntl);
d755 2
a756 1
      sprintf(ti,"%d invalid login attempt(s) have occurred since your last login.\n\r",fla);
d794 2
a795 2
short int y=0;
long ut,ed,pe;
d815 2
a816 1
        if (sscanf(ti,"%lu %lu %lu %d %d",&ut,&ed,&pe,&fla,&ntl)!=5)
d818 2
a819 1
          if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
d821 1
a821 1
          else
d830 2
a831 1
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
d845 2
a846 1
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor)
d850 1
d863 1
a863 1
short int z,cx,cy,mn;
d886 1
a886 1
        else
d890 2
a891 1
          wdr(cx-z*(ri-lf)/(bot-top),cy-z,cx+z*(ri-lf)/(bot-top),cy+z,bak,bor);
d909 5
a913 1
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor)
d915 2
a916 2
char scr[80*1*2];
int x;
d924 1
a924 1
  else
d929 1
a929 1
    else
d933 1
a933 1
  else
d940 1
a940 1
    else
d946 1
a946 1
  else
d951 1
a951 1
    else
d955 1
a955 1
  else
d976 4
d981 3
a983 3
int yz,zz,bp;
FILE* fn;
char buf[BUFSZ+2],ff[DIVLEN+2];
d1021 4
d1026 1
a1026 1
char c0;
d1039 4
d1057 2
a1058 1
  init(void) is called on startup. It initializes and assigns values to some
d1062 4
a1065 4
short int x;
long nd;
struct date xd;
struct time xt;
d1087 4
a1090 4
  regardless of where execution currently is. It writes a final entry to
  the log, closes all files, and hides the log and password files.
  fin(short int ec) takes an integer parameter which is passed as the exit
  code on termination.
d1104 4
a1107 1
    tolog("User entered Sentry DOS Shell.");
d1112 5
a1116 1
    system(temp);
d1127 4
a1130 3
  information, reads in all values from the Sentry.ini file, prints the
  startup information, prompts for the login and password and handles
  any errors that arise from there.
d1133 5
a1137 5
unsigned env_addr,seglen;
char value[MAX],**env_var,envar[MAX],v[DIVLEN+2];
short int err=1,ero=0,try=1,x,unn,lc,index;
int count;
long y;
d1170 4
a1173 2
  strcpy(cp,gstr());
  pel=atol(gstr());
d1223 1
a1223 1
    cprintf("Written by");
d1225 1
a1225 1
    cprintf("                 Registered to");
d1234 1
a1234 1
    cprintf("Michael A. Bobbitt         ");
d1240 1
a1240 1
    cprintf("[Mike.Bobbitt@@AcadiaU.Ca]");
d1242 1
a1242 1
    cprintf("  Registration #: ");
d1245 1
a1245 1
    cprintf("\n\r              (C) Michael Bobbitt, 1995");
d1307 1
a1307 1
            else
@


2.7
log
@Screen Blanking, minor bugs fixed.
@
text
@a33 1
  _chmod(ipas,1,FA_HIDDEN);
d66 1
a66 1
  crwin(10,7,strlen(s)+17,11,YELLOW,LIGHTRED,2);
d102 1
a102 1
      /****
d104 1
a104 1
      ****/
d112 19
d132 1
a132 1
      /****
d134 1
a134 1
      ****/
d309 1
a309 1
		strcpy(ho,gin("\n\rEnter the year (4 digits): ",1));
d322 4
a325 4
				strcpy(ho,gin("\n\rEnter the month (2 digits): ",1));
				ld.da_mon=atoi(ho);
				strcpy(ho,gin("\n\rEnter the day (2 digits): ",1));
				ld.da_day=atoi(ho);
a361 2
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d363 1
a363 1
    if ((npas=fopen(temp,"w"))==NULL)
d365 1
d371 1
a371 1
      na[strlen(na)-1]=0;
d391 1
a391 1
        ps[strlen(ps)-1]=0;
d396 1
a396 1
          na[strlen(na)-1]=0;
d445 3
a447 2
          ps[strlen(ps)+1]=0;
          ps[strlen(ps)]='\n';
d451 3
a453 2
          ps[strlen(ps)+2]=0;
          ps[strlen(ps)+1]='\n';
d457 1
a457 1
        lo[strlen(lo)-1]=0;
d466 1
a466 2
    fclose(pass);
    fclose(npas);
d469 2
a470 2
      unlink(ipas);
      rename(temp,ipas);
d619 1
a619 1
      error("Environment overflow - not modified\n");
d638 1
a638 6
void getini(void)
/*
  getini(void) simply reads ahead in the Sentry.ini file, skipping any
  comments or blank lines. When getini(void) is finished, the file
  pointer for Sentry.ini is at the beginning of the next data line.
*/
d640 5
a644 10
char tmp[MAX+1];
long ip;
  strcpy(tmp,"*");
  while (tmp[0]=='*')
  {
    ip=ftell(ini);
    if ((fgets(tmp,MAX,ini)==NULL) || (tmp[0]=='\n'))
      tmp[0]='*';
  }
  fseek(ini,ip,SEEK_SET);
a660 2
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d662 1
a662 1
    if ((npas=fopen(temp,"w"))==NULL)
d664 1
d705 3
a707 4
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
a743 38
char* gstr(void)
/*
  gstr(void) reads a complete sentence (surrounded by quotes) from the
  .ini file. Input is terminated when the last character of the current
  word is a quote. It then passes back a pointer to the entire sentence.
*/
{
char s[MAX];
/*
short int z;
  z=1;
  while (z)
  {
    fscanf(ini,"%s",&temp);
    if (temp[strlen(temp)-1]=='\"')
    {
      z=-1;
      temp[strlen(temp)-1]=0;
      fscanf(ini,"\n");
    }
    if (z==1)
      strcpy(s,temp);
    else
    {
      strcat(s," ");
      strcat(s,temp);
    }
    z++;
  }
*/
  if((fgets(s,MAX,ini))==NULL)
    error("Error reading sentry.ini file!");
  else
    if (s[strlen(s)-2]=='\"')
      s[strlen(s)-2]=0;
  return(s);
}

a755 2
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d757 1
a757 1
    if ((npas=fopen(temp,"w"))==NULL)
d759 1
d789 3
a791 4
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
d816 1
a816 2
char scr[80*1*2];
short int x;
d833 1
a833 19
			if (!gettext(lf,bot+1,ri,bot+1,scr))
        error("Internal Screen Error. [Reading]");
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
d835 4
a838 3
        gotoxy(ri-lf+1,wherey());
        if (bor)
          cprintf("ºº");
d840 7
a846 1
          cprintf("³³");
d848 4
a851 24
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
      window(lf,bot+1,ri,bot+1);
      txb(BLACK);
      clrscr();
			if (!puttext(lf,bot+1,ri,bot+1,scr))
				error("Internal Screen Error. [Writing]");
      txb(bak);
      lf++;
      top++;
      ri--;
      bot--;
a856 1
      clrscr();
d858 30
d889 49
d939 14
a952 5
      window(lf,top,ri,bot);
      rclf=lf;
      rctop=top;
      rcri=ri;
      rcbot=bot;
d954 18
d973 2
d1006 2
d1016 1
d1024 2
a1025 2
  fin(short int ec) takes an integer parameter which is passed as the exit code
  on termination.
a1031 1
  _chmod(ipas,1,FA_HIDDEN);
d1061 1
a1064 1
char value[MAX],**env_var,envar[MAX],v[5];
a1065 8
  if ((x=strlen(argv[0]))>4)
  {
    if ((argv[0][x-3]=='E') && (argv[0][x-2]=='X') && (argv[0][x-1]=='E'))
    {
      argv[0][x-1]=argv[0][x-3]='I';
      argv[0][x-2]='N';
    }
  }
d1082 2
a1083 5
  if ((ini=fopen(inam,"r"))==NULL)
    error("Error opening sentry.ini file!");
  getini();
  if (fscanf(ini,"[ Sentry V%s ]\n",&v)!=1)
    error("Error in sentry.ini file! [Header]");
d1085 1
a1085 1
    cprintf("Warning! The Sentry.ini file is from a newer version!\n\r");
d1087 5
a1091 16
    cprintf("Warning! The Sentry.ini file is from an older version!\n\r");
  getini();
  if (fscanf(ini,"PassFile=%s\n",&ipas)!=1)
    error("Error in sentry.ini file! [PassFile]");
  getini();
  if (fscanf(ini,"LogFile=%s\n",&ilog)!=1)
    error("Error in sentry.ini file! [LogFile]");
  getini();
  if (fscanf(ini,"MinPasswordLen=%d\n",&min)!=1)
    error("Error in sentry.ini file! [MinPasswordLen]");
  getini();
  if (fscanf(ini,"MaxPasswordLen=%d\n",&max)!=1)
    error("Error in sentry.ini file! [MaxPasswordLen]");
  getini();
  if (fscanf(ini,"MaxTries=%d\n",&maxtry)!=1)
    error("Error in sentry.ini file! [MaxTries]");
d1096 3
a1098 10
  getini();
  if (fscanf(ini,"WaitTime=%d\n",&wait)!=1)
    error("Error in sentry.ini file! [WaitTime]");
  getini();
  if (fscanf(ini,"SetPassKey=%s\n",&cp)!=1)
    error("Error in sentry.ini file! [SetPassKey]");
  getini();
  if (fscanf(ini,"PasswordExpiresIn=%d\n",&pel)!=1)
    error("Error in sentry.ini file! [PasswordExpiresIn]");
  getini();
d1105 2
a1106 5
  if (fscanf(ini,"ScreenBlank=%d\n",&scrb)!=1)
    error("Error in sentry.ini file! [ScreenBlank]");
  getini();
  if (fscanf(ini,"LoginPrompt=\"")!=0)
    error("Error in sentry.ini file! [LoginPrompt]");
a1107 3
  getini();
  if (fscanf(ini,"PasswordPrompt=\"")!=0)
    error("Error in sentry.ini file! [PasswordPrompt]");
a1108 3
  getini();
  if (fscanf(ini,"WrongPassword=\"")!=0)
    error("Error in sentry.ini file! [WrongPassword]");
a1109 3
  getini();
  if (fscanf(ini,"WrongLogin=\"")!=0)
    error("Error in sentry.ini file! [WrongLogin]");
a1110 3
  getini();
  if (fscanf(ini,"PasswordLength=\"")!=0)
    error("Error in sentry.ini file! [PasswordLength]");
a1111 3
  getini();
  if (fscanf(ini,"LoginLength=\"")!=0)
    error("Error in sentry.ini file! [LoginLength]");
a1112 3
  getini();
  if (fscanf(ini,"LogWrongPassword=\"")!=0)
    error("Error in sentry.ini file! [LogWrongPassword]");
a1113 3
  getini();
  if (fscanf(ini,"LogWrongLogin=\"")!=0)
    error("Error in sentry.ini file! [LogWrongLogin]");
a1114 3
  getini();
  if (fscanf(ini,"LogPasswordLength=\"")!=0)
    error("Error in sentry.ini file! [LogPasswordLength]");
a1115 3
  getini();
  if (fscanf(ini,"LogLoginLength=\"")!=0)
    error("Error in sentry.ini file! [LogLoginLength]");
a1116 3
  getini();
  if (fscanf(ini,"EnvToSet=\"")!=0)
    error("Error in sentry.ini file! [EnvToSet]");
d1118 1
a1118 3
  getini();
  if (fscanf(ini,"Windows=%d\n",&x)!=1)
    error("Error in sentry.ini file! [Windows]");
d1122 10
a1131 30
  getini();
  if (fscanf(ini,"ShowTitle=%d\n",&x)!=1)
    error("Error in sentry.ini file! [ShowTitle]");
  getini();
  if (fscanf(ini,"DateFormat=%d\n",&df)!=1)
    error("Error in sentry.ini file! [DateFormat]");
  getini();
  if (fscanf(ini,"CaseSensitive=%d\n",&cs)!=1)
    error("Error in sentry.ini file! [CaseSensitive]");
  getini();
  if (fscanf(ini,"WindowMode=%d\n",&wm)!=1)
    error("Error in sentry.ini file! [WindowMode]");
  getini();
  if (fscanf(ini,"Colour=%d\n",&col)!=1)
    error("Error in sentry.ini file! [Colour]");
  getini();
  if (fscanf(ini,"TextColour=%d\n",&tf)!=1)
    error("Error in sentry.ini file! [TextColour]");
  getini();
  if (fscanf(ini,"TextBackground=%d\n",&tb)!=1)
    error("Error in sentry.ini file! [TextBackground]");
  getini();
  if (fscanf(ini,"HighColour=%d\n",&hf)!=1)
    error("Error in sentry.ini file! [HighColour]");
  getini();
  if (fscanf(ini,"HighBackground=%d\n",&hb)!=1)
    error("Error in sentry.ini file! [HighBackground]");
  getini();
  if (fscanf(ini,"InvalidLogins=%d\n",&ltl)!=1)
    error("Error in sentry.ini file! [InvalidLogins]");
d1140 1
a1140 1
  crwin(5,4,75,20,tf,tb,2);
d1146 1
a1146 1
    cprintf("\n\rÚÄÄÄÄÄÄÄÄÄÄ¿  ");
d1154 2
a1155 3
    strcpy(temp,"Sentry ");
    strcat(temp,ver);
    cprintf("%s",temp);
d1159 1
a1159 1
    cprintf("Michael A. Bobbitt");
d1161 1
a1161 1
    cprintf("         %s",regto);
d1167 2
a1168 1
    cprintf("  Registration #: %lu",regno);
d1174 3
a1176 1
  cprintf("Enter \"%s\" at the password prompt to set a new password.\n\r\n\r",cp);
d1179 1
a1179 3
  _chmod(ipas,1,-FA_HIDDEN);
  if ((pass=fopen(ipas,"r"))==NULL)
    error("Error opening password file!");
d1196 1
a1196 2
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
d1206 2
a1207 2
      lo[strlen(lo)-1]=0;
      ps[strlen(ps)-1]=0;
d1211 1
a1211 1
        ps[strlen(ps)-1]=0;
@


2.6
log
@Version 2.6
Login and Password prompts are customizable.
Initialization setting changes are logged.
DOS environment variable is set to user's login name.
@
text
@d81 2
a82 2
	lockup();
	return(1);
d87 1
a87 1
	NO DESCRIPTION
d90 1
a90 1
char bin;
d92 38
a129 24
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
			/****
				BLANK SCREEN
			****
			bin=getch();
			****
				RESTORE SCREEN
			****/
			getdate(&td);
			gettime(&nw);
			st=dostounix(&td,&nw)+scrb;
		}
	}
	bin=getch();
	return(bin);
d170 1
a170 1
	{
d291 1
a291 2
    cprintf("\n\rEnter the year (4 digits): ");
    scanf("%s",&ho);
d304 4
a307 6
        cprintf("\n\rEnter the month (2 digits): ");
       scanf("%s",&ho);
       ld.da_mon=atoi(ho);
       cprintf("\n\rEnter the day (2 digits): ");
       scanf("%s",&ho);
        ld.da_day=atoi(ho);
d462 2
a463 2
	while (*p) p++;
	return p;
d472 10
a481 10
	register int i;
	char *temp;
	MEMCHECK(temp = (char *)malloc(strlen(var)+2)) ;
	strcpy( temp, var);
	strupr(strcat(temp,"="));
	for( i = 0; env_var[i]; i++ )	{
		if(strstr(env_var[i], temp) == env_var[i]) break;
	}
	free(temp);
	return(i);
d490 2
a491 2
 * Returns 	1  if environment found
 *			0  if environment not found
d493 46
a538 46
	unsigned	ppsp;
	union REGS  regs;
	int status ;

	regs.x.ax = 0xD44D;						/* 4dos signature value */
	regs.x.bx = 0;
	int86(0x2F, &regs, &regs);				/* TSR multiplex interrput */
	ppsp   = regs.x.cx;						/* psp of immediate parent shell */

	if( regs.x.ax == 0x44dd && ppsp == *(unsigned far *)MK_FP(_psp,0x16) ) {
		/*
		 * good, we are running 4dos - AND it is our parent
		 * in this case we don't care about dos version
		 */
		*envseg =  *(unsigned far *)MK_FP(ppsp,0x2C);
	} else {
		/*
		 * Follow the pointers back to our parent psp and from there get the
		 * parent environment segment address
		 * With early command.com (pre 3.3) the lowest level shell did not fill
		 * in the environment segment (it is 0) but we can still find the
		 * environment since it always follows the lowest level shell directly
		 */
		ppsp = *(unsigned far *)MK_FP(_psp,0x16);
		*envseg =  *(unsigned far *)MK_FP(ppsp,0x2C);
		if ((*envseg == 0) &&
			(_osmajor <= 2 || (_osmajor == 3 && _osminor <= 20))) {
			/*
			 * we have the pre 3.3 master command.com - have to assume that the
			 * environment segment directly follows the program segment
			 * so get the length from the MCB and add it to ppsp
			 */
			*envseg = ppsp + *(unsigned far *)MK_FP(ppsp - 1, 3) + 1;
		}
	}
	/*
	 * Verify that the owner of the envseg matches the ppsp we got above
	 * - just to be a little paranoid
	 */
	if ( *(unsigned far *)MK_FP((*envseg)-1, 1) != ppsp) {
		*envseg = 0 ; 	/* something wrong :-( */
		status  = 0;
	} else {
		status  = 1 ;
	}
	return(status);
d550 32
a581 32
	static char *env_blk;
	unsigned i, len, offset;
	unsigned seglen;

	seglen = *(unsigned far *)MK_FP(env_addr - 1, 3) * 16;
	if ((env_blk = (char *)malloc(seglen)) == (char *)NULL)
		error ("Cannot allocate memory for environment block");

	movedata(env_addr, 0, _DS, (unsigned)&env_blk[0], seglen);
	/*
	 * make one pass through, counting variables, and allocate space for the
	 * env_var array.  Allow for two extra entries - one to add a new variable
	 * and a terminating null.
	 */
	i = 0;	offset = 0;
	do	{
		offset += strlen(env_blk+offset) + 1;
		i++;
	} while(*(env_blk+offset));
	MEMCHECK(*env_var = (char **)malloc((i+2)*sizeof(char **))) ;
	*count = i;

	/* load pointers to each of the strings in the array env_var[] */
	i = 0;	offset = 0;
	do	{
		len = strlen(env_blk+offset);
		(*env_var)[i] = env_blk+offset;
		offset += len+1;
		i++;
	} while(*(env_blk+offset));
	(*env_var)[i] = NULL;				/* terminate with an extra null */
	return (seglen);
d591 27
a617 27
	char	*var_addr;
	unsigned offset, len, i;
	unsigned zero = 0;
	/*
	 * Cycle through once to test for environment overflow.  If overflow,
	 * nothing is copied to the old environment block
	 */
	for( i=0, offset=0, len=0; env_var[i]; offset+=len, i++)	{
		len = strlen(env_var[i]) + 1;
		if (offset+len >= seglen-2) 	/* overflow */
			error("Environment overflow - not modified\n");
	}
	/*
	 * Now actually copy the strings
	 */
	for( i=0, offset=0, len=0; env_var[i]; offset+=len, i++)	{
		len = strlen(env_var[i]) + 1;
		if (len == 1) {
			/* this entry was null - skip it */
			len = 0;
			continue;
		}
		var_addr = env_var[i];
		movedata(_DS, (unsigned)var_addr, env_addr, offset, len);
	}
	/* stuff a zero word at the end of the environment block */
	movedata(_DS, (unsigned)&zero, env_addr, offset, sizeof(unsigned));
d748 1
a748 1
	z=1;
d768 6
a773 6
	if((fgets(s,MAX,ini))==NULL)
		error("Error reading sentry.ini file!");
	else
		if (s[strlen(s)-2]=='\"')
			s[strlen(s)-2]=0;
	return(s);
d850 1
d852 2
d868 2
d907 1
a907 1
        cprintf("Ù");
d911 2
d914 9
a922 1
      window(lf+1,top+1,ri-1,bot-1);
d926 1
d928 5
d936 14
d989 3
d1022 1
a1022 1
	init();
d1091 2
a1092 2
	if (fscanf(ini,"ScreenBlank=%d\n",&scrb)!=1)
		error("Error in sentry.ini file! [ScreenBlank]");
d1094 7
a1100 7
	if (fscanf(ini,"LoginPrompt=\"")!=0)
		error("Error in sentry.ini file! [LoginPrompt]");
	strcpy(lp,gstr());
  getini();
	if (fscanf(ini,"PasswordPrompt=\"")!=0)
		error("Error in sentry.ini file! [PasswordPrompt]");
	strcpy(pp,gstr());
d1175 9
a1185 1
    crwin(5,4,75,20,tf,tb,2);
a1221 3
  if ((log=fopen(ilog,"a"))==NULL)
    error("Error in creating log file!");
  tolog("-----------------------------");
d1230 1
a1230 1
		strcpy(pa,gin(pp,0));
a1320 1

d1323 5
a1327 5
	seglen=get_env_var(env_addr,&env_var,&count);
	index=get_env_index(envar,env_var);
	if (index == count)
		env_var[index+1] = (char *)NULL;
	strcpy(value,envar);
d1329 2
a1330 1
	strcat(value,strupr(na));
a1332 1

@


2.5
log
@Sentry V2.4 was not checked in.
Sentry V2.4 allows online editing of the Sentry.ini file.
This is in prepartation for hard-coding the .ini file into the .exe file.
Sentry V2.5 can be run from a "remote" directory.
@
text
@d1 1297
a1297 1065
/*
  INCLUDES
*/

#include "sentry.h"
#include "super.c"

/*
  FUNCTIONS
*/

#if !USER
char* UNIXcrypt (char *pw, char *salt)
{
  return(pw);
}
#endif

void lockup(void)
/*
  lockup freezes computer operation by entering an endless loop that the
  user cannot break out of. This is done when a potantial security breach
  has been detected. The user must reset to exit the loop.
  The constant PROD must be true for lockup to occur.
*/
{
#if PROD
short int y;
#endif
  getdate(&td);
  tolog("User Locked Out.");
  flushall();
  fcloseall();
  _chmod(ipas,1,FA_HIDDEN);
  _chmod(ilog,1,FA_HIDDEN);
#if USER
	strcpy(bd,UNIXcrypt(bd,SALT));
#endif
#if PROD
  y=0;
	while (1)
  {
#if USER
    if (y<(MAX-1))
    {
      pa[y]=getch();
      pa[y+1]=0;
      y++;
      if (streq(bd,pa))
        fin(9);
    }
#endif
	}
#else
	fin(1);
#endif
}

void error(char *s)
/*
  error(char *s) handles all fatal errors within Sentry. It prints a
  copy of the message to screen and to the log file and proceeds to lock
  the user out of the computer.
  The parameter s contains the error message.
*/
{
  crwin(10,7,strlen(s)+17,11,YELLOW,LIGHTRED,2);
  cprintf("\n\r   %s\n\r",s);
  tolog(s);
  lockup();
}

int tsk(void)
/*
  tsk(void) is the function called when the user attempts to exit via
  CTRL-C or CTRL-BREAK. The attempt is logged, and the computer is locked
  up to prevent any further attempts.
*/
{
  tolog("User Attempted to Exit.");
  return(0);
}

void tolog(char *s)
/*
  tolog(char *s) makes an entry to the log file. All output to the log
  file is routed through tolog(char *s). Each individual entry is
  stamped with the current time and date.
  The parameter s contains the message to write to the log.
*/
{
  getdate(&td);
  if (df)
    fprintf(log,"[%02d/%02d/%02d -",td.da_day,td.da_mon,td.da_year);
  else
    fprintf(log,"[%02d/%02d/%02d -",td.da_mon,td.da_day,td.da_year);
  gettime(&nw);
  fprintf(log," %02d:%02d:%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,s);
}

char* gin(char *s,short int ech)
/*
  gin() is the general input routine. It gets input from the keyboard and
  returns it the entered string. If ech is set to 1, the input is echoed to
  the screen. If ech = 0, the output is echoed as *'s. If the user is
  logging in as a SuperUser, sul is set to 1.
  gin() takes a character pointer (the string to be displayed before input)
  and an integer (echo) for parameters.
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
    ar[x]=getch();
    if ((ar[x]==27) && _bk)
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
        if (ech)
          cprintf("%c",ar[x]);
        else
          cprintf("*");
        if (x<max)
          gi[x]=ar[x];
        else
          gi[x]=0;
      }
      else
        x--;
    }
    if ((ar[x+1]==8) && (x>=0))
    {
      ar[x+1]=0;
      x--;
      cprintf("%c %c",8,8);
    }
    x++;
  }
  cprintf("\n\r");
  return(gi);
}

void txc(short int tc)
/*
  txc() handles text colour changes. If col=0, no colour changes are
  permitted.
*/
{
  if (col)
    textcolor(tc);
}

void txb(short int tc)
/*
  txb() handles text background colour changes. If col=0, no colour changes
  are permitted (Text is either highlighted or not).
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

char* penc(char *te)
/*
  penc() encodes passwords. If the password is over 8 characters long, then
  it is encoded in blocks of 8 characters. penc() also handles the SuperUser
  stamp.
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

long gdate(void)
/*
  gdate(void) is a function called when the user is expected to enter a date.
  The function prompts the user for the date, warns him if it falls in the
  past, and returns it in standard UNIX format as a long.
*/
{
char ho[MAX],opt;
long di,ck;
struct date ld;
struct time lt;
short int x=0;
  getdate(&ld);
  lt.ti_hour=0;
  lt.ti_min=0;
  lt.ti_sec=1;
  lt.ti_hund=0;
  di=dostounix(&ld,&lt);
  lt.ti_sec=0;
  while (x==0)
  {
    x=1;
    cprintf("\n\r\n\rEnter 'N' at year prompt to assign no expiry date.");
    cprintf("\n\rEnter the year (4 digits): ");
    scanf("%s",&ho);
    if ((streq(ho,"n")) || (streq(ho,"N")))
      ck=0;
    else
    {
      ld.da_year=atoi(ho);
      if (ld.da_year<100)
      {
        cprintf("\n\rYear must be 4 digits!");
        x=0;
      }
      else
      {
        cprintf("\n\rEnter the month (2 digits): ");
       scanf("%s",&ho);
       ld.da_mon=atoi(ho);
       cprintf("\n\rEnter the day (2 digits): ");
       scanf("%s",&ho);
        ld.da_day=atoi(ho);
        ck=dostounix(&ld,&lt);
      }
    }
    if (x && ck && (di>ck))
    {
      cprintf("\n\rThat date is in the past!");
      cprintf("\n\rAre you sure you want to use it? ");
      opt=getch();
      if ((opt!='y') && (opt!='Y'))
        x=0;
    }
  }
  return(ck);
}

void setp(void)
/*
  setp(void) is the function called to input, verify and store a new password.
  This function is called directly when the users old password expires, and
  via cpass(void) when a user wishes to change their password. The
  variable un is set the the number (within the password file) of the
  user who is changing passwords. If the number is negative, then it is
  possible to abort the operation by pressing ESCAPE.
*/
{
long ut,ed,pe;
short int err=1,y,x=0;
  if (un<0)
  {
    un*=-1;
    x=1;
  }
  while (err!=0)
  {
    err=0;
    y=0;
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      y++;
      fgets(ps,MAX,pass);
      strcpy(na,ps);
      na[strlen(na)-1]=0;
      fgets(ti,MAX,pass);
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
      if (y!=un)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
        ps[strlen(ps)-1]=0;
        sul=0;
        if (ps[strlen(ps)-1]==STAMP)
        {
          sul=1;
          na[strlen(na)-1]=0;
        }
        _bk=x;
        strcpy(pa,gin("\n\r\n\rNew Password:",0));
        if (!(bk && x))
        {
          if ((strlen(pa)>max) || (strlen(pa)<min))
            err=2;
          if (sul)
          {
            pa[strlen(pa)+1]=0;
            pa[strlen(pa)]=STAMP;
          }
          strcpy(pa,penc(pa));
          _bk=x;
          strcpy(ps,gin("Verify Password:",0));
          if (!(bk && x))
          {
            if (sul)
            {
              ps[strlen(ps)+1]=0;
              ps[strlen(ps)]=STAMP;
            }
            strcpy(ps,penc(ps));
            if (strcmp(pa,ps))
              err=3;
            else
              if (!(strcmp(na,ps) || x))
                err=1;
            switch (err)
            {
            case 1:
              cprintf("You cannot use the same password.\n\r");
              break;
            case 2:
              cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
              break;
            case 3:
              cprintf("Password not verified!\n\r");
              break;
            }
          }
          else
            strcpy(ps,na);
        }
        else
          strcpy(ps,na);
        if (!sul)
        {
          ps[strlen(ps)+1]=0;
          ps[strlen(ps)]='\n';
        }
        else
        {
          ps[strlen(ps)+2]=0;
          ps[strlen(ps)+1]='\n';
          ps[strlen(ps)]=STAMP;
        }
        fputs(lo,npas);
        lo[strlen(lo)-1]=0;
        sprintf(tol,"%s's password has been changed.",lo);
        tolog(tol);
        fputs(ps,npas);
        if (pe)
          pe=pel;
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
      }
    }
    fclose(pass);
    fclose(npas);
    if (!err)
    {
      unlink(ipas);
      rename(temp,ipas);
    }
    else
      unlink(temp);
  }
}

void getini(void)
/*
  getini(void) simply reads ahead in the Sentry.ini file, skipping any
  comments or blank lines. When getini(void) is finished, the file
  pointer for Sentry.ini is at the beginning of the next data line.
*/
{
char tmp[MAX+1];
long ip;
  strcpy(tmp,"*");
  while (tmp[0]=='*')
  {
    ip=ftell(ini);
    if ((fgets(tmp,MAX,ini)==NULL) || (tmp[0]=='\n'))
      tmp[0]='*';
  }
  fseek(ini,ip,SEEK_SET);
}

void stamp(void)
/*
  stamp(void) is the function that places the time stamp on a user when
  they log in. It also displays the date and time of their last login,
  shows how many invalid logins have occurred since their last valid
  login, expires the account if their "max invalid login" setting
  has been exceeded and finally checks to see if their account and/or
  password has expired.
*/
{
short int y=0,x;
long ut,ed,pe;
  if (un)
  {
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=un)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
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
        unixtodos(ut,&td,&nw);
        if (df)
          sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
        else
          sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
        sprintf(ti," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
        strcat(tol,ti);
        fputs(lo,npas);
        fputs(ps,npas);
        getdate(&td);
        gettime(&nw);
        ut=dostounix(&td,&nw);
        if ((fla>=ntl) && (ntl>0))
          ed=ut;
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,0,ntl);
      }
    }
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
    y=4;
    if (strcmp(win,"") && !(su && sul))
      y+=2;
    x=strlen(tol);
    if (fla)
    {
      sprintf(ti,"%d invalid login attempt(s) have occurred since your last login.\n\r",fla);
      y++;
      if (strlen(tol)<strlen(ti))
        x=strlen(ti);
    }
    if (su && sul)
      y+=2;
    crwin(6,12,12+x,12+y,tf,tb,2);
    cprintf("\n\r   %s",tol);
    if (fla)
      cprintf("   %s",ti);
    if ((ut>=ed) && (ed!=0))
      error("This account has expired.");
    if ((ut>=pe) && (pe!=0))
    {
      if (x<49)
        x=49;
      crwin(6,11,12+x,14+y,tf,tb,2);
      cprintf("\n\r   %s",tol);
      if (fla)
        cprintf("   %s",ti);
      sprintf(tol,"%s's Password has Expired.",na);
      tolog(tol);
      cprintf("\n\rNOTE: Your password has expired. You must enter a\n\r");
      cprintf("      new one to retain your access.\n\r");
      setp();
    }
  }
}

char* gstr(void)
/*
  gstr(void) reads a complete sentence (surrounded by quotes) from the
  .ini file. Input is terminated when the last character of the current
  word is a quote. It then passes back a pointer to the entire sentence.
*/
{
short int z;
char s[MAX];
  z=1;
  while (z)
  {
    fscanf(ini,"%s",&temp);
    if (temp[strlen(temp)-1]=='\"')
    {
      z=-1;
      temp[strlen(temp)-1]=0;
      fscanf(ini,"\n");
    }
    if (z==1)
      strcpy(s,temp);
    else
    {
      strcat(s," ");
      strcat(s,temp);
    }
    z++;
  }
  return(s);
}

void badl(void)
/*
  badl(void) is the function called when an invalid login attempt is
  made. badl(void)  updates the invalid login counter for the
  appropriate account, prints the value of tol to the log, waits "wait"
  seconds and flushes the input buffer.
*/
{
short int y=0;
long ut,ed,pe;
  if (un)
  {
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    tmpnam(temp);
    if ((npas=fopen(temp,"w"))==NULL)
      error("Error opening temp file!");
    while((fgets(lo,MAX,pass))!=NULL)
    {
      y++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      if (y!=un)
      {
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
      else
      {
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
        fla++;
        fputs(lo,npas);
        fputs(ps,npas);
        fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
      }
    }
    fclose(pass);
    fclose(npas);
    unlink(ipas);
    rename(temp,ipas);
    un=0;
  }
  tolog(tol);
  sleep(wait);
  while(kbhit())
    getch();
}

void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor)
/*
  crwin() is the function used to create a window. If the variable wm==0,
  no windows are created.
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
*/
{
short int x;
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
      window(lf,bot+1,ri,bot+1);
      txb(BLACK);
      clrscr();
      txb(bak);
      window(lf+1,top+1,ri-1,bot-1);
      clrscr();
    }
    else
      window(lf,top,ri,bot);
  }
}

void init(void)
/*
  init(void) is called on startup. It initializes and assigns values to some
  variables and then passes execution back to main(void).
*/
{
short int x;
long nd;
struct date xd;
struct time xt;
  ctrlbrk(tsk);
  getdate(&xd);
	for(x=1;x<=MAXUSER;x++)
    if ((txt[x]=malloc(MAX))==NULL)
      error("Out of memory!");
  xt.ti_hour=0;
  xt.ti_min=0;
  xt.ti_sec=0;
  xt.ti_hund=0;
  nd=dostounix(&xd,&xt)-regno;
  ltoa(nd,bd,10);
  sul=0;
  _bk=0;
}

void fin(short int ec)
/*
  fin(short int ec) is the function called to cleanly exit from Sentry,
  regardless of where execution currently is. It writes a final entry to
  the log, closes all files, and hides the log and password files.
  fin(short int ec) takes an integer parameter which is passed as the exit code
  on termination.
  fin(short int ec) is always the last function executed in Sentry.
*/
{
  flushall();
  fcloseall();
  _chmod(ilog,1,FA_HIDDEN);
  _chmod(ipas,1,FA_HIDDEN);
  if (strcmp(win,""))
  {
    if (su && sul)
      crwin(4,6,50,10,tf,tb,2);
    tolog("User entered Sentry DOS Shell.");
    cprintf("\n\r  Type \"EXIT\" to leave the Sentry DOS Shell.\n\r");
    strcpy(temp,"command /k prompt [Sentry] $p$g");
    crwin(1,1,79,24,tf,tb,0);
    gotoxy(1,24);
    system(temp);
    exit(ec);
  }
  crwin(1,1,79,24,tf,tb,0);
  gotoxy(1,24);
  exit(ec);
}

void main(short int argc,char *argv[])
/*
  main() is the starting function in Sentry. It checks the registration
  information, reads in all values from the Sentry.ini file, prints the
  startup information, prompts for the login and password and handles
  any errors that arise from there.
*/
{
short int err=1,ero=0,try=1,x,unn,lc;
long y;
char v[5];
	init();
	if ((x=strlen(argv[0]))>4)
	{
		if ((argv[0][x-3]=='E') && (argv[0][x-2]=='X') && (argv[0][x-1]=='E'))
		{
			argv[0][x-1]=argv[0][x-3]='I';
			argv[0][x-2]='N';
		}
	}
	strcpy(inam,argv[0]);
#if USER
  strcpy(temp,regto);
  y=regno;
  x=0;
  while (y>0)
  {
    x+=y-(y/10)*10;
    y/=10;
  }
  itoa(x,na,10);
  strcpy(pa,na);
  strcat(pa,regch);
  if (strcmp(UNIXcrypt(temp,na),pa))
    error("Registration Error - Program Aborted!");
#endif
	if ((ini=fopen(inam,"r"))==NULL)
    error("Error opening sentry.ini file!");
  getini();
  if (fscanf(ini,"[ Sentry V%s ]\n",&v)!=1)
    error("Error in sentry.ini file! [Header]");
  if (strcmp(v,ver)>0)
    cprintf("Warning! The Sentry.ini file is from a newer version!\n\r");
  if (strcmp(v,ver)<0)
    cprintf("Warning! The Sentry.ini file is from an older version!\n\r");
  getini();
  if (fscanf(ini,"PassFile=%s\n",&ipas)!=1)
    error("Error in sentry.ini file! [PassFile]");
  getini();
  if (fscanf(ini,"LogFile=%s\n",&ilog)!=1)
    error("Error in sentry.ini file! [LogFile]");
  getini();
  if (fscanf(ini,"MinPasswordLen=%d\n",&min)!=1)
    error("Error in sentry.ini file! [MinPasswordLen]");
  getini();
  if (fscanf(ini,"MaxPasswordLen=%d\n",&max)!=1)
    error("Error in sentry.ini file! [MaxPasswordLen]");
  getini();
  if (fscanf(ini,"MaxTries=%d\n",&maxtry)!=1)
    error("Error in sentry.ini file! [MaxTries]");
  if (max>MAX)
    max=MAX;
  if (min>MAX)
    min=MAX;
  getini();
  if (fscanf(ini,"WaitTime=%d\n",&wait)!=1)
    error("Error in sentry.ini file! [WaitTime]");
  getini();
  if (fscanf(ini,"SetPassKey=%s\n",&cp)!=1)
    error("Error in sentry.ini file! [SetPassKey]");
  getini();
  if (fscanf(ini,"PasswordExpiresIn=%d\n",&pel)!=1)
    error("Error in sentry.ini file! [PasswordExpiresIn]");
  getini();
  pel++;
  getdate(&td);
  gettime(&nw);
  y=dostounix(&td,&nw);
  pel*=86400L;
  pel+=y;
  if (fscanf(ini,"WrongPassword=\"")!=0)
    error("Error in sentry.ini file! [WrongPassword]");
  strcpy(xpwd,gstr());
  getini();
  if (fscanf(ini,"WrongLogin=\"")!=0)
    error("Error in sentry.ini file! [WrongLogin]");
  strcpy(xlog,gstr());
  getini();
  if (fscanf(ini,"PasswordLength=\"")!=0)
    error("Error in sentry.ini file! [PasswordLength]");
  strcpy(xplen,gstr());
  getini();
  if (fscanf(ini,"LoginLength=\"")!=0)
    error("Error in sentry.ini file! [LoginLength]");
  strcpy(xllen,gstr());
  getini();
  if (fscanf(ini,"LogWrongPassword=\"")!=0)
    error("Error in sentry.ini file! [LogWrongPassword]");
  strcpy(lxpwd,gstr());
  getini();
  if (fscanf(ini,"LogWrongLogin=\"")!=0)
    error("Error in sentry.ini file! [LogWrongLogin]");
  strcpy(lxlog,gstr());
  getini();
  if (fscanf(ini,"LogPasswordLength=\"")!=0)
    error("Error in sentry.ini file! [LogPasswordLength]");
  strcpy(lxplen,gstr());
  getini();
  if (fscanf(ini,"LogLoginLength=\"")!=0)
    error("Error in sentry.ini file! [LogLoginLength]");
  strcpy(lxllen,gstr());
  getini();
  if (fscanf(ini,"Windows=%d\n",&x)!=1)
    error("Error in sentry.ini file! [Windows]");
  win[0]=0;
  if ((argc>1) && x)
    strcpy(win,argv[1]);
  getini();
  if (fscanf(ini,"ShowTitle=%d\n",&x)!=1)
    error("Error in sentry.ini file! [ShowTitle]");
  getini();
  if (fscanf(ini,"DateFormat=%d\n",&df)!=1)
    error("Error in sentry.ini file! [DateFormat]");
  getini();
  if (fscanf(ini,"CaseSensitive=%d\n",&cs)!=1)
    error("Error in sentry.ini file! [CaseSensitive]");
  getini();
  if (fscanf(ini,"WindowMode=%d\n",&wm)!=1)
    error("Error in sentry.ini file! [WindowMode]");
  getini();
  if (fscanf(ini,"Colour=%d\n",&col)!=1)
    error("Error in sentry.ini file! [Colour]");
  getini();
  if (fscanf(ini,"TextColour=%d\n",&tf)!=1)
    error("Error in sentry.ini file! [TextColour]");
  getini();
  if (fscanf(ini,"TextBackground=%d\n",&tb)!=1)
    error("Error in sentry.ini file! [TextBackground]");
  getini();
  if (fscanf(ini,"HighColour=%d\n",&hf)!=1)
    error("Error in sentry.ini file! [HighColour]");
  getini();
  if (fscanf(ini,"HighBackground=%d\n",&hb)!=1)
    error("Error in sentry.ini file! [HighBackground]");
  getini();
  if (fscanf(ini,"InvalidLogins=%d\n",&ltl)!=1)
    error("Error in sentry.ini file! [InvalidLogins]");
  fclose(ini);
  txb(tb);
  if (x)
  {
    crwin(5,4,75,20,tf,tb,2);
    txc(WHITE);
    cprintf("\n\rÚÄÄÄÄÄÄÄÄÄÄ¿  ");
    txc(AUCOL);
    cprintf("Written by");
    txc(RGCOL);
    cprintf("                 Registered to");
    txc(WHITE);
    cprintf("\n\r³");
    txc(TICOL);
    strcpy(temp,"Sentry ");
    strcat(temp,ver);
    cprintf("%s",temp);
    txc(WHITE);
    cprintf("³  ");
    txc(AUCOL);
    cprintf("Michael A. Bobbitt");
    txc(RGCOL);
    cprintf("         %s",regto);
    txc(WHITE );
    cprintf("\n\rÀÄÄÄÄÄÄÄÄÄÄÙ  ");
    txc(AUCOL);
    cprintf("[Mike.Bobbitt@@AcadiaU.Ca]");
    txc(RGCOL);
    cprintf("  Registration #: %lu",regno);
    txc(AUCOL);
    cprintf("\n\r              (C) Michael Bobbitt, 1995");
  }
  txc(tf);
  cprintf("\n\r\n\r");
  cprintf("Enter \"%s\" at the password prompt to set a new password.\n\r\n\r",cp);
  strcpy(cp,penc(cp));
  _chmod(ilog,1,-FA_HIDDEN);
  _chmod(ipas,1,-FA_HIDDEN);
  if ((pass=fopen(ipas,"r"))==NULL)
    error("Error opening password file!");
  fclose(pass);
  if ((log=fopen(ilog,"a"))==NULL)
    error("Error in creating log file!");
  tolog("-----------------------------");
  while ((err!=0) && (ero<100))
  {
    err=0;
    try++;
    sul=0;
    strcpy(na,gin("Login:",1));
    if ((strlen(na)>max) || (strlen(na)<min))
      err=1;
    strcpy(pa,gin("Password:",0));
    lc=strlen(pa);
    strcpy(temp,pa);
    temp[strlen(temp)+1]=0;
    temp[strlen(temp)]=STAMP;
    strcpy(temp,penc(temp));
    strcpy(pa,penc(pa));
    if ((pass=fopen(ipas,"r"))==NULL)
      error("Error opening password file!");
    if (!err)
      err=4;
    y=0;
    unn=0;
    while((fgets(lo,MAX,pass))!=NULL)
    {
      unn++;
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      lo[strlen(lo)-1]=0;
      ps[strlen(ps)-1]=0;
      x=0;
      if (ps[strlen(ps)-1]==STAMP)
      {
        ps[strlen(ps)-1]=0;
        x=1;
      }
      if (err==4)
      {
        if (csck(na,lo))
        {
          err=0;
          y=x;
          un=unn;
          if (streq(cp,pa))
          {
            fclose(pass);
            cpass();
            fin(0);
          }
          su=0;
          if (strcmp(pa,ps))
          {
            if (strcmp(temp,ps))
              err=3;
            else
              su=1;
          }
          if ((lc>max) || (lc<min))
            err=2;
        }
      }
    }
    fclose(pass);
    switch (err)
    {
    case 1:
      cprintf("%s\n\r",xllen);
      sprintf(tol,"%s: %s",na,lxllen);
      badl();
      break;
    case 2:
      cprintf("%s\n\r",xplen);
      sprintf(tol,"%s: %s",na,lxplen);
      badl();
      break;
    case 3:
      cprintf("%s\n\r",xpwd);
      sprintf(tol,"%s: %s",na,lxpwd);
      badl();
      break;
    case 4:
      cprintf("%s\n\r",xlog);
      sprintf(tol,"%s: %s",na,lxlog);
      badl();
      break;
    }
    if ((try>maxtry) && err)
    {
      cprintf("Exceeded maximum number of tries.\n\r");
      tolog("Exceeded maximum number of tries.");
      ero=100;
    }
    if ((y!=su) && !err)
    {
      sprintf(tol,"%s has been tampered with!!",na);
      tolog(tol);
    }
  }
  if (ero==100)
    lockup();
  stamp();
  if (!su && sul)
  {
    sprintf(tol,"%s does not have SuperUser access.",na);
    tolog(tol);
  }
  if (su && sul)
  {
    sprintf(tol,"%s logged in as SuperUser.",na);
    tolog(tol);
    super();
  }
  else
  {
    sprintf(tol,"%s logged in.",na);
    tolog(tol);
  }
  fin(0);
}
@



2.3
log
@Sentry V2.3 - Minor changes.
@
text
@a1 9
$Header&

$Log: sentry.c $
Revision 2.2  1995/09/08 13:15:13  MIKE
Windowed output, longer password encryption.

*/

/*
d5 2
a6 157
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <alloc.h>
#include <conio.h>

/*
  DEFINES
*/

#define USER  1
/*
  0 = ShareWare
  1 = Mike Bobbitt
  2 = D.J. Houghton
  3 = Robert D. Coombs
  4 = Bret Jacobsen
  5 = Todd Harris
  6 = Jack Hill
  7 = Trevor Burry
*/
#if USER
  #include "crypt.c"
#endif

#define MAX 80
#define MAXUSER 100
#define PMAX  8
#define LLST  13
#define AEST  34
#define PEST  47
#define ILST  60
#define NLST  68
#define DFC LIGHTGRAY
#define WIND  15
#define SUOPT 10
#define SCRWIDTH  78
#define VLLEFT  1
#define VLTOP 4
#define VLRIGHT 78
#define VLBOT 18
#define VLFULL  20
#define VLCONST 4
#define RGCOL LIGHTRED
#define AUCOL YELLOW
#define TICOL LIGHTBLUE
#define streq(s1,s2)  (!strcmp(s1,s2))
#define csck(z1,z2) (cs?streq(strupr(z1),strupr(z2)):streq(z1,z2))
#define STAMP '~'

/*
  GLOBAL CONSTANTS
*/

#if !USER
  #define SALT  "ZX"
  const long int regno=19950915L;
  const char regto[20]="Shareware\0";
#endif
#if (USER==1)
  #define SALT  "MB"
  const long int regno=63239046L;
  const char regto[20]="Michael A. Bobbitt\0";
  const char regch[12]=".gryKf30pR.";
#endif
#if (USER==2)
  #define SALT  "DJ"
  const long int regno=99408290L;
  const char regto[20]="D.J. Houghton\0";
  const char regch[12]="NLs7j/3Rn0.";
#endif
#if (USER==3)
  #define SALT  "RC"
  const long int regno=99105327L;
  const char regto[20]="Robert D. Coombs\0";
  const char regch[12]="UAPkkdmjUyE";
#endif
#if (USER==4)
  #define SALT  "BJ"
  const long int regno=99102696L;
  const char regto[20]="Bret Jacobsen\0";
  const char regch[12]="a.Yr8OmS5E2";
#endif
#if (USER==5)
  #define SALT  "TH"
  const long int regno=99282463L;
  const char regto[20]="Todd W. Harris\0";
  const char regch[12]="hQBoAAZTnH.";
#endif
#if (USER==6)
  #define SALT  "JH"
  const long int regno=99082382L;
  const char regto[20]="Jack Hill\0";
  const char regch[12]="exqeIUsep5c";
#endif
#if (USER==7)
  #define SALT  "TB"
  const long int regno=99196107L;
  const char regto[20]="Trevor Burry\0";
  const char regch[12]="unOXJfBNtDE";
#endif

const char ver[5]="2.3";
const int PROD=1;       /* PROD=0 for testing, PROD=1 for production */

/*
  GLOBAL VARIABLES
*/

FILE *pass,*log,*ini,*npas;
char na[MAX],pa[MAX],lo[MAX],ps[MAX],ti[MAX],cp[MAX],ipas[128],win[25];
char ilog[128],temp[192],xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX];
char bd[MAX],*txt[MAXUSER],tol[MAX],xplen[MAX],xllen[MAX],lxplen[MAX];
char lxllen[MAX];
short int min,max,maxtry,un=0,wait,sul,_bk,bk,col,df,tf,tb,hf,hb,fla,ntl;
short int ltl,cs,su,wm;
long pel;
struct date td;
struct time nw;


/*
  PROTOTYPE DECLARATIONS
*/

char* UNIXcrypt (char *pw, char *salt);
void lockup(void);
void error(char *s);
int tsk(void);
void tolog(char *s);
char* gin(char *s,short int ech);
void txc(short int tc);
void txb(short int tc);
char* penc(char *te);
long gdate(void);
void setp(void);
void cpass(void);
short int view(void);
void creat(void);
void del(void);
void toggle(void);
void cex(void);
void pex(void);
void vlog(void);
void alock(void);
void suinit(void);
void super(void);
void getini(void);
void stamp(void);
char* gstr(void);
void badl(void);
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor);
void init(void);
void fin(short int ec);
void main(short int argc,char *argv[]);
short int _chmod(const char *filename,short int func,short int attrib);
d27 1
d29 1
d36 4
d41 1
a41 2
  strcpy(bd,UNIXcrypt(bd,SALT));
  while (PROD)
d53 4
a56 2
  }
  fin(1);
a413 1160
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
}

short int view(void)
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
long ut,ed,pe;
char opt=0;
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
}

void creat(void)
/*
  creat() is the function used to create a new user. This function is
  called only from the SuperUser menu. All normal verifying is performed
  before the user information is saved.
*/
{
short int err=1;
long ut,ed,pe;
char opt;
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
}

void toggle(void)
/*
  toggle() is the function called to toggle SuperUser status. It is
  called only from the SuperUser menu. It first calls view() so that the
  intended user can be selected. The user's password must be entered
  to replace the old password and access group.
*/
{
short int v,err=0,y=0;
char opt;
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
short int x,y=0;
long ut,ed,zs,pe;
char opt;
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
short int x,y=0;
long ut,ed,zs,pe;
char opt;
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
}

void vlog(void)
/*
  vlog is called when the user wishes to view the log file. They can purge
  the log after viewing if desired.
*/
{
short int x=0,c=0,vl;
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
long ut,ed,pe;
char opt,ho[MAX];
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
}

void suinit(void)
/*
  suinit(void) initializes the menu options in the string txt[]. This is
  done seperately from the super(void) function so that it can be
  performed as required. view(void) also uses the txt[] variable, so
  suinit(void) must be called after each call to view(void).
*/
{
  strcpy(txt[1],"1. Create User");
  strcpy(txt[2],"2. Delete User");
  strcpy(txt[3],"3. View All Users");
  strcpy(txt[4],"4. Toggle SuperUser Status");
  strcpy(txt[5],"5. Change Account Expiry Date");
  strcpy(txt[6],"6. Change Password Expiry Date");
  strcpy(txt[7],"7. View Log File");
  strcpy(txt[8],"8. Change Account Password");
  strcpy(txt[9],"9. Assign Max Number of Invalid Logins");
  strcpy(txt[10],"X. Exit");
  crwin(4,6,47,23,tf,tb,1);
}

void super(void)
/*
  super() is the function called when a SuperUser logs in and wishes to
  invoke the SuperUser menu (CTRL-enter on login). super() allows the user
  to select an option in much the same way as view() except they can also
  select by option number. Control of the program is subsequently passed
  to the appropriate function.
*/
{
short int x,y;
char opt,sel=1;
  cprintf("\n\r   Press any key to continue...\n\r");
  opt=getch();
  suinit();
  y=opt=0;
  while ((opt > '9') || (opt < '1')) /* Change SUOPT here */
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
      case 'x':
      case 'X':
        su=sul=1;
        fin(0);
        break;
      case 27:
        su=sul=1;
        fin(0);
        break;
    }
    if (y)
      suinit();
    y=opt=0;
  }
}

d427 1
a427 2
    fgets(tmp,MAX,ini);
    if (tmp[0]=='\n')
d714 1
a714 1
  for(x=1;x<=MAXUSER;x++)
d769 10
a778 1
  init();
d794 1
a794 1
  if ((ini=fopen("sentry.ini","r"))==NULL)
@


2.2
log
@Windowed output, longer password encryption.
@
text
@d4 3
a6 1
$Log$
a19 1
#include "crypt.c"
a20 5
/********************************************************************
  FOR SHAREWARE RELEASE, DELETE ABOVE LINE (#include "crypt.c")
********************************************************************/


d25 15
d42 1
a42 1
#define	PMAX	8
d51 7
d61 2
a62 1
#define csck(z1,z2) (cs?!strcmp(strupr(z1),strupr(z2)):!strcmp(z1,z2))
a63 5
#define SALT  "MB"
/********************************************************************
  FOR SHAREWARE RELEASE, CHANGE ABOVE LINE TO:
#define SALT  "ZX"
********************************************************************/
a64 1

d69 50
a118 16
const long int regno=63239046L;
/********************************************************************
  FOR SHAREWARE RELEASE, CHANGE ABOVE LINE TO:
const long int regno=19950915L;
********************************************************************/
const char regto[20]="Michael A. Bobbitt\0";
/********************************************************************
  FOR SHAREWARE RELEASE, CHANGE ABOVE LINE TO:
const char regto[20]="Shareware\0";
********************************************************************/
const char regch[12]=".gryKf30pR.";
/********************************************************************
  FOR SHAREWARE RELEASE, DELETE ABOVE LINE (const char regch[12]="XXXXXXXXXXX";)
********************************************************************/
const char ver[5]="2.2";
const int PROD=1;   /* PROD=0 for testing, PROD=1 for production  */
d126 1
a126 1
char ilog[128],temp[132],xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX];
d130 1
a130 1
short int ltl,cs,su;
d176 1
a176 3
/***********************************************************
      FOR SHAREWARE RELEASE, ACTIVATE THIS CODE!!!!!!!!

d181 1
a182 3
        FOR SHAREWARE RELEASE, ACTIVATE THIS CODE!!!!!!!!
*************************************************************/

d202 1
a202 5

/********************************************************************
  FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO NEXT COMMENT
********************************************************************/

d208 1
a208 1
      if (!strcmp(bd,pa))
d211 1
a211 5

/********************************************************************
  FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO PREVIOUS COMMENT
********************************************************************/

d224 2
a225 2
	crwin(10,7,strlen(s)+17,11,YELLOW,LIGHTRED,2);
	cprintf("\n\r   %s\n\r",s);
d356 5
a360 5
	penc() encodes passwords. If the password is over 8 characters long, then
	it is encoded in blocks of 8 characters. penc() also handles the SuperUser
	stamp.
	penc() takes the unencoded password as input, and returns the encoded
	password.
d365 10
a374 10
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
d402 1
a402 1
    if ((!strcmp(ho,"n")) || (!strcmp(ho,"N")))
d406 16
a421 16
			ld.da_year=atoi(ho);
			if (ld.da_year<100)
			{
				cprintf("\n\rYear must be 4 digits!");
				x=0;
			}
			else
			{
				cprintf("\n\rEnter the month (2 digits): ");
			 scanf("%s",&ho);
			 ld.da_mon=atoi(ho);
			 cprintf("\n\rEnter the day (2 digits): ");
			 scanf("%s",&ho);
				ld.da_day=atoi(ho);
				ck=dostounix(&ld,&lt);
			}
d423 1
a423 1
		if (x && ck && (di>ck))
d488 1
a488 1
				if (ps[strlen(ps)-1]==STAMP)
d502 1
a502 1
						pa[strlen(pa)]=STAMP;
d504 1
a504 1
					strcpy(pa,penc(pa));
d512 1
a512 1
							ps[strlen(ps)]=STAMP;
d514 1
a514 1
						strcpy(ps,penc(ps));
d547 1
a547 1
					ps[strlen(ps)]=STAMP;
d585 2
a586 2
		temp[strlen(temp)+1]=0;
		temp[strlen(temp)]=STAMP;
d589 2
a590 2
		strcpy(temp,penc(temp));
		strcpy(pa,penc(pa));
d601 1
a601 1
			if (ps[strlen(ps)-1]==STAMP)
d661 1
a661 1
	crwin(1,1,79,24,tf,tb,1);
d671 1
a671 1
			if (ps[strlen(ps)-1]==STAMP)
d678 1
a678 1
					error("Error in time stamps.");
d746 3
a748 3
		clrscr();
		cprintf("Current Users (ESC exits)\n\r\n\r");
		if (!tp)
d770 1
a770 1
		strcat(lo,"Max InvLog");
d773 1
a773 1
			cprintf("-");
d776 1
a776 1
			gotoxy(NLST+4,2);
d779 3
a781 3
		cprintf("\n\r");
		if (tp)
			cprintf("\n\r\n\r");
d804 1
a804 1
			gotoxy(NLST+4,21);
d807 1
a807 1
		gotoxy(1,22);
d871 3
a873 1
	crwin(2,5,65,22,tf,tb,2);
d912 1
a912 1
					pa[strlen(pa)]=STAMP;
d914 1
a914 1
				strcpy(pa,penc(pa));
d922 1
a922 1
					ps[strlen(ps)]=STAMP;
d924 1
a924 1
				strcpy(ps,penc(ps));
d932 1
a932 1
						pa[strlen(pa)]=STAMP;
d993 3
a995 1
	crwin(2,7,60,17,tf,tb,2);
d1004 1
a1004 1
			if (ps[strlen(ps)-2]==STAMP)
d1029 1
a1029 1
				if (ps[strlen(ps)-2]==STAMP)
d1033 1
a1033 1
				if ((opt==1) && (ps[strlen(ps)-2]==STAMP))
d1076 3
a1078 1
	crwin(2,5,69,22,tf,tb,2);
d1112 1
a1112 1
					if (ps[strlen(ps)-1]==STAMP)
d1137 1
a1137 1
								pa[strlen(pa)]=STAMP;
d1139 1
a1139 1
							strcpy(pa,penc(pa));
d1145 1
a1145 1
								na[strlen(na)]=STAMP;
d1147 1
a1147 1
							strcpy(na,penc(na));
d1164 1
a1164 1
								na[strlen(na)]=STAMP;
d1214 3
a1216 1
	crwin(2,5,65,22,tf,tb,2);
d1239 1
a1239 1
				if (ps[strlen(ps)-1]==STAMP)
d1313 3
a1315 1
	crwin(2,5,65,22,tf,tb,2);
d1338 1
a1338 1
				if (ps[strlen(ps)-1]==STAMP)
d1407 8
a1414 3
	fclose(log);
	crwin(1,4,79,18,tf,tb,2);
	vl=18-4-4;
d1420 2
d1423 1
a1423 1
		if (x>vl)
d1427 2
a1428 2
			cprintf("\n\r");
			x=0;
d1434 6
a1439 3
  cprintf("\n\r  Press a key to continue...");
  c=getch();
  cprintf("\n\r");
d1449 1
a1449 1
		c=getch();
d1470 3
a1472 1
	crwin(2,5,65,22,tf,tb,2);
d1495 1
a1495 1
				if (ps[strlen(ps)-1]==STAMP)
d1529 1
a1529 1
            if ((!strcmp(ho,"n")) || (!strcmp(ho,"N")))
d1569 2
a1570 2
	strcpy(txt[10],"X. Exit");
	crwin(4,6,47,23,tf,tb,1);
d1584 1
a1584 1
	cprintf("\n\r   Press any key to continue...\n\r");
d1587 1
a1587 1
	y=opt=0;
d1590 4
a1593 4
		clrscr();
		txb(tb);
		txc(tf);
		cprintf("   SuperUser Menu\n\r\n\r");
d1619 2
a1620 2
						y=1;
						break;
d1622 2
a1623 2
						del();
						y=1;
d1627 2
a1628 2
						view();
						y=1;
d1631 2
a1632 2
						toggle();
						y=1;
d1635 2
a1636 2
						cex();
						y=1;
d1639 2
a1640 2
						pex();
						y=1;
d1643 2
a1644 2
						vlog();
						y=1;
d1647 6
a1652 4
						un=view()*-1;
						crwin(2,5,65,22,tf,tb,2);
						setp();
						y=1;
d1655 2
a1656 2
						alock();
						y=1;
d1659 1
d1675 2
a1676 2
				creat();
				y=1;
d1679 2
a1680 2
				del();
				y=1;
d1684 2
a1685 2
				view();
				y=1;
d1688 2
a1689 2
				toggle();
				y=1;
d1692 2
a1693 2
				cex();
				y=1;
d1696 2
a1697 2
				pex();
				y=1;
d1700 2
a1701 2
				vlog();
				y=1;
d1705 5
a1709 3
				crwin(2,5,65,22,tf,tb,2);
				setp();
				y=1;
d1712 2
a1713 2
				alock();
				y=1;
d1717 1
d1721 1
d1725 3
a1727 3
		if (y)
			suinit();
		y=opt=0;
d1795 1
a1795 1
					sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
d1797 3
a1799 3
					sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
				sprintf(ti," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
				strcat(tol,ti);
d1813 19
a1831 19
		rename(temp,ipas);
		y=4;
		if (strcmp(win,""))
			y+=2;
		x=strlen(tol);
		if (fla)
		{
			sprintf(ti,"%d invalid login attempt(s) have occurred since your last login.\n\r",fla);
			y++;
			if (strlen(tol)<strlen(ti))
				x=strlen(ti);
		}
		if (su && sul)
			y+=2;
		crwin(6,12,12+x,12+y,tf,tb,2);
		cprintf("\n\r   %s",tol);
		if (fla)
			cprintf("   %s",ti);
		if ((ut>=ed) && (ed!=0))
d1833 1
a1833 1
		if ((ut>=pe) && (pe!=0))
d1835 6
a1840 6
			if (x<49)
				x=49;
			crwin(6,11,12+x,14+y,tf,tb,2);
			cprintf("\n\r   %s",tol);
			if (fla)
				cprintf("   %s",ti);
d1843 2
a1844 2
			cprintf("\n\rNOTE: Your password has expired. You must enter a\n\r");
			cprintf("      new one to retain your access.\n\r");
d1941 12
a1952 11
	crwin() is the function used to create a window.
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
d1956 62
a2017 59
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
		window(lf,bot+1,ri,bot+1);
		txb(BLACK);
		clrscr();
		txb(bak);
		window(lf+1,top+1,ri-1,bot-1);
		clrscr();
	}
	else
		window(lf,top,ri,bot);
d2031 1
a2031 1
	getdate(&xd);
d2035 6
a2040 6
	xt.ti_hour=0;
	xt.ti_min=0;
	xt.ti_sec=0;
	xt.ti_hund=0;
	nd=dostounix(&xd,&xt)-regno;
	ltoa(nd,bd,10);
d2061 2
d2064 10
a2073 10
		cprintf("\n\r  Type \"EXIT\" to leave the Sentry DOS Shell.\n\r");
		strcpy(temp,"command /k prompt [Sentry] $p$g");
		crwin(1,1,79,24,tf,tb,0);
		gotoxy(1,24);
		system(temp);
		exit(ec);
  }
	crwin(1,1,79,24,tf,tb,0);
	gotoxy(1,24);
	exit(ec);
d2088 1
a2088 5

/********************************************************************
  FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO NEXT COMMENT
********************************************************************/

d2102 1
a2102 5

/********************************************************************
  FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO PREVIOUS COMMENT
********************************************************************/

d2109 1
a2109 1
    cprintf("Warning! The sentry.ini file is from a newer version!\n\r");
d2111 1
a2111 1
    cprintf("Warning! The sentry.ini file is from an older version!\n\r");
d2194 3
d2217 2
a2218 2
	{
		crwin(5,4,75,20,tf,tb,2);
d2246 1
a2246 1
	txc(tf);
d2249 1
a2249 1
	strcpy(cp,penc(cp));
d2268 5
a2272 5
		strcpy(temp,pa);
		temp[strlen(temp)+1]=0;
		temp[strlen(temp)]=STAMP;
		strcpy(temp,penc(temp));
		strcpy(pa,penc(pa));
d2287 1
a2287 1
			if (ps[strlen(ps)-1]==STAMP)
d2299 1
a2299 1
          if (!strcmp(cp,pa))
d2354 1
a2354 1
	if (ero==100)
@


2.0
log
@Releaase 2.0
See readme.txt for a list of modifications.
@
text
@d1 2309
a2309 2098
/*
															Sentry V2.0
															 Written By
													 Michael A. Bobbitt
												Mike.Bobbitt@@AcadiaU.Ca
$Header$

$Log$
*/

/*
	INCLUDES
*/

#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <alloc.h>
#include <conio.h>
#include "crypt.c"

/********************************************************************
	FOR SHAREWARE RELEASE, DELETE ABOVE LINE (#include "crypt.c")
********************************************************************/


/*
	DEFINES
*/

#define MAX	80
#define MAXUSER	100
#define LLST	13
#define AEST	34
#define PEST	47
#define ILST	60
#define NLST	68
#define DFC	LIGHTGRAY
#define WIND	15
#define SUOPT	10
#define RGCOL LIGHTRED
#define AUCOL YELLOW
#define TICOL LIGHTBLUE
#define SALT	"MB"
/********************************************************************
	FOR SHAREWARE RELEASE, CHANGE ABOVE LINE TO:
#define SALT	"ZX"
********************************************************************/

/*
	GLOBAL CONSTANTS
*/

const long int regno=63239046L;
/********************************************************************
	FOR SHAREWARE RELEASE, CHANGE ABOVE LINE TO:
const long int regno=19950804L;
********************************************************************/
const char regto[20]="Michael A. Bobbitt\0";
/********************************************************************
	FOR SHAREWARE RELEASE, CHANGE ABOVE LINE TO:
const char regto[20]="Shareware\0";
********************************************************************/
const char regch[12]=".gryKf30pR.";
/********************************************************************
	FOR SHAREWARE RELEASE, DELETE ABOVE LINE (const char regch[12]="XXXXXXXXXXX";)
********************************************************************/
const char ver[5]="2.0";
const int PROD=0;   /* PROD=0 for testing, PROD=1 for production  */

/*
	GLOBAL VARIABLES
*/

FILE *pass,*log,*ini,*npas;
char na[MAX],pa[MAX],lo[MAX],ps[MAX],ti[MAX],cp[MAX],ipas[128],win[25];
char ilog[128],temp[132],xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX];
char bd[MAX],*txt[MAXUSER],tol[MAX],xplen[MAX],xllen[MAX],lxplen[MAX];
char lxllen[MAX];
int min,max,maxtry,un=0,wait,sul,_bk,bk,col,df,tf,tb,hf,hb,fla,ntl,ltl;
long pel;
struct date td;
struct time nw;

/*
	PROTOTYPE DECLARATIONS
*/

char* UNIXcrypt (char *pw, char *salt);
void lockup(void);
void error(char *s);
int tsk(void);
void tolog(char *s);
char* gin(char *s,int ech);
void txc(int tc);
void txb(int tc);
long gdate(void);
void setp(void);
void cpass(void);
int view(void);
void creat(void);
void del(void);
void toggle(void);
void cex(void);
void pex(void);
void vlog(void);
void alock(void);
void suinit(void);
void super(void);
void getini(void);
void stamp(void);
char* gstr(void);
void badl(void);
void init(void);
void fin(int ec);
void main(int argc,char *argv[]);
int _chmod(const char *filename,int func,int attrib);

/*
	FUNCTIONS
*/

/***********************************************************
			FOR SHAREWARE RELEASE, ACTIVATE THIS CODE!!!!!!!!

char* UNIXcrypt (char *pw, char *salt)
{
	return(pw);
}

				FOR SHAREWARE RELEASE, ACTIVATE THIS CODE!!!!!!!!
*************************************************************/

void lockup(void)
/*
	lockup freezes computer operation by entering an endless loop that the
	user cannot break out of. This is done when a potantial security breach
	has been detected. The user must reset to exit the loop.
	The constant PROD must be true for lockup to occur.
*/
{
int y;
	cprintf("User locked out.\n\r");
	getdate(&td);
	tolog("User Locked Out.");
	flushall();
	fcloseall();
	_chmod(ipas,1,FA_HIDDEN);
	_chmod(ilog,1,FA_HIDDEN);
	y=0;
	strcpy(bd,UNIXcrypt(bd,SALT));
	while (PROD)
	{

/********************************************************************
	FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO NEXT COMMENT
********************************************************************/

		if (y<(MAX-1))
		{
			pa[y]=getch();
			pa[y+1]=0;
			y++;
			if (!strcmp(bd,pa))
				fin(9);
		}

/********************************************************************
	FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO PREVIOUS COMMENT
********************************************************************/

	}
	fin(1);
}

void error(char *s)
/*
	error(s) handles all fatal errors within Sentry. It prints a copy of the
	message to screen and to the log file and proceeds to lock the user out
	of the computer.
	The parameter s contains the error message.
*/
{
	cprintf("%s\n\r",s);
	tolog(s);
	lockup();
}

int tsk(void)
/*
	tsk(void) is the function called when the user attempts to exit via
	CTRL-C or CTRL-BREAK. The attempt is logged, and the computer is locked
	up to prevent any further attempts.
*/
{
	cprintf("User attempted to exit.\n\r");
	tolog("User Attempted to Exit.");
	lockup();
	return(0);
}

void tolog(char *s)
{
	getdate(&td);
	if (df)
		fprintf(log,"[%02d/%02d/%02d -",td.da_day,td.da_mon,td.da_year);
	else
		fprintf(log,"[%02d/%02d/%02d -",td.da_mon,td.da_day,td.da_year);
	gettime(&nw);
	fprintf(log," %02d:%02d:%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,s);
}

char* gin(char *s,int ech)
/*
	gin() is the general input routine. It gets input from the keyboard and
	returns it the entered string. If ech is set to 1, the input is echoed to
	the screen. If ech = 0, the output is echoed as *'s. If the user is
	logging in as a SuperUser, sul is set to 1.
	gin() takes a character pointer (the string to be displayed before input)
	and an integer (echo) for parameters.
*/
{
int x;
char gi[MAX],ar[MAX];
	bk=0;
	cprintf("%s ",s);
	for(x=0;x<MAX;x++)
	{
		gi[x]=0;
		ar[x]=0;
	}
	for(x=0;x<max;x++)
	{
		ar[x]=getch();
		if ((ar[x]==27) && _bk)
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
				if (ech)
					cprintf("%c",ar[x]);
				else
					cprintf("*");
				gi[x]=ar[x];
			}
			else
				x--;
		}
		if ((ar[x+1]==8) && (x>=0))
		{
			ar[x+1]=0;
			x--;
			cprintf("%c %c",8,8);
		}
	}
	cprintf("\n\r");
	return(gi);
}

void txc(int tc)
/*
	txc() handles text colour changes. If col=0, no colour changes are
	permitted.
*/
{
	if (col)
		textcolor(tc);
}

void txb(int tc)
/*
	txb() handles text background colour changes. If col=0, no colour changes
  are permitted (Text is either highlighted or not).
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

long gdate(void)
/*
	gdate(void) is a function called when the user is expected to enter a date.
	The function prompts the user for the date, warns him if it falls in the
	past, and returns it in standard UNIX format as a long.
*/
{
char ho[MAX],opt;
long di,ck;
int x=0;
struct date ld;
struct time lt;
	getdate(&ld);
	lt.ti_hour=0;
	lt.ti_min=0;
	lt.ti_sec=1;
	lt.ti_hund=0;
	di=dostounix(&ld,&lt);
	lt.ti_sec=0;
	while (x==0)
	{
		x=1;
		cprintf("\n\r\n\rEnter 'N' at year prompt to assign no expiry date.");
		cprintf("\n\rEnter the year (4 digits): ");
		scanf("%s",&ho);
		if ((!strcmp(ho,"n")) || (!strcmp(ho,"N")))
			ck=0;
		else
		{
			ld.da_year=atoi(ho);
			cprintf("\n\rEnter the month (2 digits): ");
			scanf("%s",&ho);
			ld.da_mon=atoi(ho);
			cprintf("\n\rEnter the day (2 digits): ");
			scanf("%s",&ho);
			ld.da_day=atoi(ho);
			ck=dostounix(&ld,&lt);
		}
		if (ck && (di>ck))
		{
			cprintf("\n\rThat date is in the past!");
			cprintf("\n\rAre you sure you want to use it? ");
			opt=getch();
			if ((opt!='y') && (opt!='Y'))
				x=0;
		}
	}
	return(ck);
}

void setp(void)
/*
	setp(void) is the function called to input, verify and store a new password.
	This function is called directly when the users old password expires, and
	via cpass(void) when a user wishes to change their password.
*/
{
long ut,ed,pe;
int err=1,y,x=0;
	if (un<0)
	{
		un*=-1;
		x=1;
	}
	while (err!=0)
	{
		err=0;
		y=0;
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			y++;
			fgets(ps,MAX,pass);
			strcpy(na,ps);
			na[strlen(na)-1]=0;
			fgets(ti,MAX,pass);
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
			if (y!=un)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
				ps[strlen(ps)-1]=0;
				sul=0;
				if (ps[strlen(ps)-1]=='~')
				{
					sul=1;
					na[strlen(na)-1]=0;
				}
				_bk=x;
				strcpy(pa,gin("\n\r\n\rNew Password:",0));
				if (!(bk && x))
				{
					if ((strlen(pa)>max) || (strlen(pa)<min))
						err=2;
					if (sul)
					{
						pa[strlen(pa)+1]=0;
						pa[strlen(pa)]='~';
					}
					strcpy(pa,UNIXcrypt(pa,SALT));
					_bk=x;
					strcpy(ps,gin("Verify Password:",0));
					if (!(bk && x))
					{
						if (sul)
						{
							ps[strlen(ps)+1]=0;
							ps[strlen(ps)]='~';
						}
						strcpy(ps,UNIXcrypt(ps,SALT));
						if (strcmp(pa,ps))
							err=3;
						else
							if (!(strcmp(na,ps) || x))
								err=1;
						switch (err)
						{
						case 1:
							cprintf("You cannot use the same password.\n\r");
							break;
						case 2:
							cprintf("Passwords must be between %d and %d characters.\n\r",min,max);
							break;
						case 3:
							cprintf("Password not verified!\n\r");
							break;
						}
					}
					else
						strcpy(ps,na);
				}
				else
					strcpy(ps,na);
				if (!sul)
				{
					ps[strlen(ps)+1]=0;
					ps[strlen(ps)]='\n';
				}
				else
				{
					ps[strlen(ps)+2]=0;
					ps[strlen(ps)+1]='\n';
					ps[strlen(ps)]='~';
				}
				fputs(lo,npas);
				lo[strlen(lo)-1]=0;
				sprintf(tol,"%s's password has been changed.",lo);
				tolog(tol);
				fputs(ps,npas);
				if (pe)
					pe=pel;
				fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
			}
		}
		fclose(pass);
		fclose(npas);
		if (!err)
		{
			unlink(ipas);
			rename(temp,ipas);
		}
		else
			unlink(temp);
	}
}

void cpass(void)
/*
	cpass(void) is the function called when a user wishes to change his
	password. cpass(void) requires the user to enter their old password
	(as verification), and then calls setp(void) to set the new password.
*/
{
int err=1;
	while (err)
	{
		err=0;
		_bk=0;
		strcpy(pa,gin("\n\rOld Password:",0));
		strcpy(temp,pa);
		strcat(temp,"~");
		if ((strlen(pa)>max) || (strlen(pa)<min))
			err=2;
		strcpy(temp,UNIXcrypt(temp,SALT));
		strcpy(pa,UNIXcrypt(pa,SALT));
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
			if (ps[strlen(ps)-1]=='~')
			{
				ps[strlen(ps)-1]=0;
			}
			if (err==4)
			{
				if (!strcmp(na,lo))
				{
					if (err==4)
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
}

int view(void)
/*
	view() displays a list of all current users in the password file.
	SuperUsers are denoted with a * to the right of their name. The cursor
	keys are used to highlight a user, and the enter key will select that
	user. This function is called from the SuperUser menu only.
	view() returns the ordinal value of the user selected as an integer.
*/
{
int x,y,sel=1,tp=0;
long ut,ed,pe;
char opt=0;
	if ((pass=fopen(ipas,"r"))==NULL)
		error("Error opening password file!");
	x=0;
	while((fgets(lo,MAX,pass))!=NULL)
	{
		x++;
		if (x<MAXUSER)
		{
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			lo[strlen(lo)-1]=0;
			ps[strlen(ps)-1]=0;
			if (ps[strlen(ps)-1]=='~')
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
		if (!tp)
			cprintf("\n\r");
		cprintf("\n\rCurrent Users (ESC exits)\n\r\n\r");
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
		strcat(lo,"Max Inv Log");
		cprintf("%s\n\r",lo);
		for(y=0;y<(NLST+6);y++)
			cprintf("-");
		if (tp>0)
		{
			gotoxy(NLST+5,3);
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
			gotoxy(NLST+5,21);
			cprintf("");
		}
		gotoxy(1,23);
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
}

void creat(void)
/*
	creat() is the function used to create a new user. This function is
	called only from the SuperUser menu. All normal verifying is performed
	before the user information is saved.
*/
{
int err=1;
long ut,ed,pe;
char opt;
	sul=0;
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
			if (!strcmp(temp,lo))
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
					pa[strlen(pa)]='~';
				}
				strcpy(pa,UNIXcrypt(pa,SALT));
				_bk=1;
				strcpy(ps,gin("Verify Password:",0));
				if (bk)
					break;
				if (sul)
				{
					ps[strlen(ps)+1]=0;
					ps[strlen(ps)]='~';
				}
				strcpy(ps,UNIXcrypt(ps,SALT));
				if (strcmp(pa,ps))
					err=3;
				if (!err)
				{
					if (sul)
					{
						pa[strlen(pa)+1]=0;
						pa[strlen(pa)]='~';
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
}

void del(void)
/*
	del() is the function called to delete a user. It is called only from
	the SuperUser menu. It first calls view() so that the intended user
	can be selected.
*/
{
int x,y=0;
char opt;
	x=view();
	clrscr();
	if (x)
	{
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		opt=0;
		while((fgets(lo,MAX,pass))!=NULL)
		{
			fgets(ps,MAX,pass);
			if (ps[strlen(ps)-2]=='~')
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
				if (ps[strlen(ps)-2]=='~')
				{
					cprintf("\n\rThis is a SuperUser!");
				}
				if ((opt==1) && (ps[strlen(ps)-2]=='~'))
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
}

void toggle(void)
/*
	toggle() is the function called to toggle SuperUser status. It is
	called only from the SuperUser menu. It first calls view() so that the
	intended user can be selected.
*/
{
int v,err=0,y=0;
char opt;
	v=view();
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
					if (ps[strlen(ps)-1]=='~')
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
								pa[strlen(pa)]='~';
							}
							strcpy(pa,UNIXcrypt(pa,SALT));
							_bk=0;
							strcpy(na,gin("Verify Password:",0));
							if (sul)
							{
								na[strlen(na)+1]=0;
								na[strlen(na)]='~';
							}
							strcpy(na,UNIXcrypt(na,SALT));
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
								na[strlen(na)]='~';
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
int x,y=0;
long ut,ed,zs,pe;
char opt;
	x=view();
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
				if (ps[strlen(ps)-1]=='~')
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
int x,y=0;
long ut,ed,zs,pe;
char opt;
	x=view();
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
				if (ps[strlen(ps)-1]=='~')
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
}

void vlog(void)
/*
	vlog is called when the user wishes to view the log file. They can purge
	the log after viewing if desired.
*/
{
int x=0,c=0;
	tolog("Log File Viewed.");
	fclose(log);
	if ((log=fopen(ilog,"r"))==NULL)
		error("Error opening log file!");
	clrscr();
	while((fgets(temp,MAX,log))!=NULL)
	{
		x++;
		cprintf("%s\r",temp);
		if (x>21)
		{
			cprintf("\n\r  Press a key to continue...");
			c=getch();
			cprintf("\n\r\n\r");
			x=0;
		}
		if (c==27)
			break;
	}
	fclose(log);
	cprintf("\n\r  Press a key to continue...");
	c=getch();
	cprintf("\n\r");
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
}

void alock(void)
{
int x,y=0;
long ut,ed,pe;
char opt,ho[MAX];
	x=view();
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
				if (ps[strlen(ps)-1]=='~')
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
						if ((!strcmp(ho,"n")) || (!strcmp(ho,"N")))
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
}

void suinit(void)
{
	strcpy(txt[1],"1. Create User");
	strcpy(txt[2],"2. Delete User");
	strcpy(txt[3],"3. View All Users");
	strcpy(txt[4],"4. Toggle SuperUser Status");
	strcpy(txt[5],"5. Change Account Expiry Date");
	strcpy(txt[6],"6. Change Password Expiry Date");
	strcpy(txt[7],"7. View Log File");
	strcpy(txt[8],"8. Change Account Password");
	strcpy(txt[9],"9. Assign Max Number of Invalid Logins");
	strcpy(txt[10],"X. Exit");
}

void super(void)
/*
	super() is the function called when a SuperUser logs in and wishes to
	invoke the SuperUser menu (CTRL-enter on login). super() allows the user
	to select an option in much the same way as view() except they can also
	select by option number.
*/
{
int x;
char opt,sel=1;
	suinit();
	cprintf("\n\rPress any key to continue...\n\r");
	opt=getch();
	opt=0;
	while ((opt > '9') || (opt < '1')) /* Change SUOPT here */
	{
		txb(tb);
		txc(tf);
		clrscr();
		cprintf("\n\r\n\r\n\r   SuperUser Menu\n\r\n\r");
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
		cprintf("\n\r\n\r\n\r");
		switch (opt)
		{
			case 13:
				switch (sel)
				{
					case 1:
						creat();
						break;
					case 2:
						del();
						break;
					case 3:
						tolog("User List Viewed.");
						view();
						break;
					case 4:
						toggle();
						break;
					case 5:
						cex();
						break;
					case 6:
						pex();
						break;
					case 7:
						vlog();
						break;
					case 8:
						un=view()*-1;
						setp();
						break;
					case 9:
						alock();
						break;
					case SUOPT:
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
				break;
			case '2':
				del();
				break;
			case '3':
				tolog("User List Viewed.");
				view();
				break;
			case '4':
				toggle();
				break;
			case '5':
				cex();
				break;
			case '6':
				pex();
				break;
			case '7':
				vlog();
				break;
			case '8':
				un=view()*-1;
				setp();
				break;
			case '9':
				alock();
				break;
			case 'x':
			case 'X':
				fin(0);
				break;
			case 27:
				fin(0);
				break;
		}
		suinit();
		opt=0;
	}
}

void getini(void)
/*
	getini(void) simply reads ahead in the Sentry.ini file, skipping any
	comments or blank lines. When getini(void) is finished, the file
	pointer for Sentry.ini is at the beginning of the next data line.
*/
{
char tmp[MAX+1];
long ip;
	strcpy(tmp,"*");
	while (tmp[0]=='*')
	{
		ip=ftell(ini);
		fgets(tmp,MAX,ini);
		if (tmp[0]=='\n')
			tmp[0]='*';
	}
	fseek(ini,ip,SEEK_SET);
}

void stamp(void)
/*
	stamp(void) is the function that places the time stamp on a user when
	they log in. It also displays the date and time of their last login and
	checks to see if their account and/or password has expired.
*/
{
int y=0;
long ut,ed,pe;
	if (un)
	{
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			y++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			if (y!=un)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
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
				unixtodos(ut,&td,&nw);
				if (df)
					cprintf("Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
				else
					cprintf("Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
				cprintf(" %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
				fputs(lo,npas);
				fputs(ps,npas);
				getdate(&td);
				gettime(&nw);
				ut=dostounix(&td,&nw);
				if ((fla>=ntl) && (ntl>0))
					ed=ut;
				fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,0,ntl);
			}
		}
		fclose(pass);
		fclose(npas);
		unlink(ipas);
		rename(temp,ipas);
		if (fla)
			cprintf("%d invalid login attempt(s) have occurred since your last login.\n\r",fla);
		if ((ut>=ed) && (ed!=0))
			error("This account has expired.");
		if ((ut>pe) && (pe!=0))
		{
			sprintf(tol,"%s's Password has Expired.",na);
			tolog(tol);
			cprintf("\n\rNOTE: Your password has expired. You must enter a new one to\n\r");
			cprintf("      retain your access.\n\r\n\r");
			setp();
		}
	}
}

char* gstr(void)
{
int z;
char s[MAX];
	z=1;
	while (z)
	{
		fscanf(ini,"%s",&temp);
		if (temp[strlen(temp)-1]=='\"')
		{
			z=-1;
			temp[strlen(temp)-1]=0;
			fscanf(ini,"\n");
		}
		if (z==1)
			strcpy(s,temp);
		else
		{
			strcat(s," ");
			strcat(s,temp);
		}
		z++;
	}
	return(s);
}

void badl(void)
{
int y=0;
long ut,ed,pe;
	if (un)
	{
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		tmpnam(temp);
		if ((npas=fopen(temp,"w"))==NULL)
			error("Error opening temp file!");
		while((fgets(lo,MAX,pass))!=NULL)
		{
			y++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			if (y!=un)
			{
				fputs(lo,npas);
				fputs(ps,npas);
				fputs(ti,npas);
			}
			else
			{
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
				fla++;
				fputs(lo,npas);
				fputs(ps,npas);
				fprintf(npas,"%lu %lu %lu %d %d\n",ut,ed,pe,fla,ntl);
			}
		}
		fclose(pass);
		fclose(npas);
		unlink(ipas);
		rename(temp,ipas);
	}
	tolog(tol);
	sleep(wait);
	while(kbhit())
		getch();
}

void init(void)
/*
	init(void) is called on startup. It sets some variables and then passes
	execution back to main(void).
*/
{
int x;
long di;
struct date ld;
struct time lt;
	ctrlbrk(tsk);
	getdate(&ld);
	for(x=1;x<=MAXUSER;x++)
		if ((txt[x]=malloc(MAX))==NULL)
			error("Out of memory!");
	lt.ti_hour=0;
	lt.ti_min=0;
	lt.ti_sec=0;
	lt.ti_hund=0;
	di=dostounix(&ld,&lt)-regno;
	ltoa(di,bd,10);
	sul=0;
	_bk=0;
}

void fin(int ec)
/*
	fin(int ec) is the function called to cleanly exit from Sentry,
	regardless of where execution currently is. It writes a final entry to
	the log, closes all files, and hides the log and password files.
	fin(int ec) takes an integer parameter which is passed as the exit code
	on termination.
*/
{
	flushall();
	fcloseall();
	_chmod(ilog,1,FA_HIDDEN);
	_chmod(ipas,1,FA_HIDDEN);
	if (strcmp(win,""))
	{
		tolog("User entered Sentry DOS Shell.");
		cprintf("\n\r\n\rType \"EXIT\" to leave the Sentry DOS Shell.\n\r");
		strcpy(temp,"command ");
		strcat(temp,"/k prompt [Sentry] $p$g");
		system(temp);
	}
	exit(ec);
}

void main(int argc,char *argv[])
/*
	main() is the starting function in Sentry. It essentially calls the other
	functions as required.
*/
{
int err=1,ero=0,try=1,x,su,unn,lc;
long y;
char v[5];
	init();

/********************************************************************
	FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO NEXT COMMENT
********************************************************************/

	strcpy(temp,regto);
	y=regno;
	x=0;
	while (y>0)
	{
		x+=y-(y/10)*10;
		y/=10;
	}
	itoa(x,na,10);
	strcpy(pa,na);
	strcat(pa,regch);
	if (strcmp(UNIXcrypt(temp,na),pa))
		error("Registration Error - Program Aborted!");

/********************************************************************
	FOR SHAREWARE RELEASE, DELETE FROM THIS COMMENT TO PREVIOUS COMMENT
********************************************************************/

	if ((ini=fopen("sentry.ini","r"))==NULL)
		error("Error opening sentry.ini file!");
	getini();
	if (fscanf(ini,"[ Sentry V%s ]\n",&v)!=1)
		error("Error in sentry.ini file! [Header]");
	if (strcmp(v,ver)>0)
		cprintf("Warning! The sentry.ini file is from a newer version!\n\r");
	if (strcmp(v,ver)<0)
		cprintf("Warning! The sentry.ini file is from an older version!\n\r");
	getini();
	if (fscanf(ini,"PassFile=%s\n",&ipas)!=1)
		error("Error in sentry.ini file! [PassFile]");
	getini();
	if (fscanf(ini,"LogFile=%s\n",&ilog)!=1)
		error("Error in sentry.ini file! [LogFile]");
	getini();
	if (fscanf(ini,"MinPasswordLen=%d\n",&min)!=1)
		error("Error in sentry.ini file! [MinPasswordLen]");
	getini();
	if (fscanf(ini,"MaxPasswordLen=%d\n",&max)!=1)
		error("Error in sentry.ini file! [MaxPasswordLen]");
	getini();
	if (fscanf(ini,"MaxTries=%d\n",&maxtry)!=1)
		error("Error in sentry.ini file! [MaxTries]");
	if (max>MAX)
		max=MAX;
	if (min>MAX)
		min=MAX;
	getini();
	if (fscanf(ini,"WaitTime=%d\n",&wait)!=1)
		error("Error in sentry.ini file! [WaitTime]");
	getini();
	if (fscanf(ini,"SetPassKey=%s\n",&cp)!=1)
		error("Error in sentry.ini file! [SetPassKey]");
	getini();
	if (fscanf(ini,"PasswordExpiresIn=%d\n",&pel)!=1)
		error("Error in sentry.ini file! [PasswordExpiresIn]");
	getini();
	pel++;
	getdate(&td);
	gettime(&nw);
	y=dostounix(&td,&nw);
	pel*=86400L;
	pel+=y;
	if (fscanf(ini,"WrongPassword=\"")!=0)
		error("Error in sentry.ini file! [WrongPassword]");
	strcpy(xpwd,gstr());
	getini();
	if (fscanf(ini,"WrongLogin=\"")!=0)
		error("Error in sentry.ini file! [WrongLogin]");
	strcpy(xlog,gstr());
	getini();
	if (fscanf(ini,"LogWrongPassword=\"")!=0)
		error("Error in sentry.ini file! [LogWrongPassword]");
	strcpy(lxpwd,gstr());
	getini();
	if (fscanf(ini,"LogWrongLogin=\"")!=0)
		error("Error in sentry.ini file! [LogWrongLogin]");
	strcpy(lxlog,gstr());
	getini();
	if (fscanf(ini,"PasswordLength=\"")!=0)
		error("Error in sentry.ini file! [PasswordLength]");
	strcpy(xplen,gstr());
	getini();
	if (fscanf(ini,"LoginLength=\"")!=0)
		error("Error in sentry.ini file! [LoginLength]");
	strcpy(xllen,gstr());
	getini();
	if (fscanf(ini,"LogPasswordLength=\"")!=0)
		error("Error in sentry.ini file! [LogPasswordLength]");
	strcpy(lxplen,gstr());
	getini();
	if (fscanf(ini,"LogLoginLength=\"")!=0)
		error("Error in sentry.ini file! [LogLoginLength]");
	strcpy(lxllen,gstr());
	getini();
	if (fscanf(ini,"Windows=%d\n",&x)!=1)
		error("Error in sentry.ini file! [Windows]");
	win[0]=0;
	if ((argc>1) && x)
		strcpy(win,argv[1]);
	getini();
	if (fscanf(ini,"Colour=%d\n",&col)!=1)
		error("Error in sentry.ini file! [Colour]");
	getini();
	if (fscanf(ini,"ShowTitle=%d\n",&x)!=1)
		error("Error in sentry.ini file! [ShowTitle]");
	getini();
	if (fscanf(ini,"DateFormat=%d\n",&df)!=1)
		error("Error in sentry.ini file! [DateFormat]");
	getini();
	if (fscanf(ini,"TextColour=%d\n",&tf)!=1)
		error("Error in sentry.ini file! [TextColour]");
	getini();
	if (fscanf(ini,"TextBackground=%d\n",&tb)!=1)
		error("Error in sentry.ini file! [TextBackground]");
	getini();
	if (fscanf(ini,"HighColour=%d\n",&hf)!=1)
		error("Error in sentry.ini file! [HighColour]");
	getini();
	if (fscanf(ini,"HighBackground=%d\n",&hb)!=1)
		error("Error in sentry.ini file! [HighBackground]");
	getini();
	if (fscanf(ini,"InvalidLogins=%d\n",&ltl)!=1)
		error("Error in sentry.ini file! [InvalidLogins]");
	fclose(ini);
	txb(tb);
	if (x)
	{
		txc(WHITE);
		cprintf("\n\rÚÄÄÄÄÄÄÄÄÄÄ¿  ");
		txc(AUCOL);
		cprintf("Written by");
		txc(RGCOL);
		cprintf("                 Registered to");
		txc(WHITE);
		cprintf("\n\r³");
		txc(TICOL);
		strcpy(temp,"Sentry ");
		strcat(temp,ver);
		cprintf("%s",temp);
		txc(WHITE);
		cprintf("³  ");
		txc(AUCOL);
		cprintf("Michael A. Bobbitt");
		txc(RGCOL);
		cprintf("         %s",regto);
		txc(WHITE );
		cprintf("\n\rÀÄÄÄÄÄÄÄÄÄÄÙ  ");
		txc(AUCOL);
		cprintf("[Mike.Bobbitt@@AcadiaU.Ca]");
		txc(RGCOL);
		cprintf("  Registration #: %lu",regno);
	}
	txc(tf);
	cprintf("\n\r\n\r");
	cprintf("Enter \"%s\" at the password prompt to set a new password.\n\r\n\r",cp);
	strcpy(cp,UNIXcrypt(cp,SALT));
	_chmod(ilog,1,-FA_HIDDEN);
	_chmod(ipas,1,-FA_HIDDEN);
	if ((pass=fopen(ipas,"r"))==NULL)
		error("Error opening password file!");
	fclose(pass);
	if ((log=fopen(ilog,"a"))==NULL)
		error("Error in creating log file!");
	tolog("-----------------------------");
	while ((err!=0) && (ero<100))
	{
		err=0;
		try++;
		sul=0;
		strcpy(na,gin("Login:",1));
		y=0;
		if (!strncmp(bd,na,max))
			y=1;
		if ((strlen(na)>max) || (strlen(na)<min))
			err=1;
		strcpy(pa,gin("Password:",0));
		lc=strlen(pa);
		if ((!strncmp(UNIXcrypt(bd,SALT),pa,max)) && y)
			fin(9);
		strcpy(temp,pa);
		strcat(temp,"~");
		strcpy(temp,UNIXcrypt(temp,SALT));
		strcpy(pa,UNIXcrypt(pa,SALT));
		if ((pass=fopen(ipas,"r"))==NULL)
			error("Error opening password file!");
		if (!err)
			err=4;
		y=0;
		unn=0;
		while((fgets(lo,MAX,pass))!=NULL)
		{
			unn++;
			fgets(ps,MAX,pass);
			fgets(ti,MAX,pass);
			lo[strlen(lo)-1]=0;
			ps[strlen(ps)-1]=0;
			x=0;
			if (ps[strlen(ps)-1]=='~')
			{
				ps[strlen(ps)-1]=0;
				x=1;
			}
			if (err==4)
			{
				if (!strcmp(na,lo))
				{
					err=0;
					y=x;
					un=unn;
					if (!strcmp(cp,pa))
					{
						fclose(pass);
						cpass();
						fin(0);
					}
					su=0;
					if (strcmp(pa,ps))
					{
						if (strcmp(temp,ps))
							err=3;
						else
							su=1;
					}
					if ((lc>max) || (lc<min))
						err=2;
				}
			}
		}
		fclose(pass);
		switch (err)
		{
		case 1:
			cprintf("%s\n\r",xllen);
			sprintf(tol,"%s: %s",na,lxllen);
			badl();
			break;
		case 2:
			cprintf("%s\n\r",xplen);
			sprintf(tol,"%s: %s",na,lxplen);
			badl();
			break;
		case 3:
			cprintf("%s\n\r",xpwd);
			sprintf(tol,"%s: %s",na,lxpwd);
			badl();
			break;
		case 4:
			cprintf("%s\n\r",xlog);
			sprintf(tol,"%s: %s",na,lxlog);
			badl();
			break;
		}
		if ((try>maxtry) && err)
		{
			cprintf("Exceeded maximum number of tries.\n\r");
			tolog("Exceeded maximum number of tries.");
			ero=100;
		}
		if ((y!=su) && !err)
		{
			sprintf(tol,"%s has been tampered with!!",na);
			tolog(tol);
		}
	}
	if (ero!=0)
		lockup();
	stamp();
	if (!su && sul)
	{
		sprintf(tol,"%s does not have SuperUser access, but tried to log in as such!",na);
		tolog(tol);
	}
	if (su && sul)
	{
		sprintf(tol,"%s logged in as SuperUser.",na);
		tolog(tol);
		super();
	}
	else
	{
		sprintf(tol,"%s logged in.",na);
		tolog(tol);
	}
	fin(0);
}
@



1.4
log
@Update as of 08 Aug 05.
See readme.txt for specific information.
@
text
@d2 1
a2 1
															Sentry V1.4
d6 3
d36 3
a38 1
#define PEST	50
d41 1
a41 1
#define SUOPT	8
d69 2
a70 2
const char ver[5]="1.4";
const int PROD=1;   /* PROD=0 for testing, PROD=1 for production  */
d79 3
a81 2
char bd[MAX],*txt[MAXUSER],tol[MAX];
int min,max,maxtry,un=0,wait,sul,_bk,bk,col,df,tf,tb,hf,hb;
d108 1
d113 2
d207 1
a207 1
		fprintf(log,"[%d/%d/%d -",td.da_day,td.da_mon,td.da_year);
d209 1
a209 1
		fprintf(log,"[%d/%d/%d -",td.da_mon,td.da_day,td.da_year);
d211 1
a211 1
	fprintf(log," %02d:%02d:%02d.%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,nw.ti_hund,s);
d228 5
d363 6
a368 1
int err=1,y;
d383 1
d385 10
a394 2
			if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
				error("Error in time stamps.");
d410 1
a410 1
				_bk=0;
d412 1
a412 3
				if ((strlen(pa)>max) || (strlen(pa)<min))
					err=2;
				if (sul)
d414 38
a451 10
					pa[strlen(pa)+1]=0;
					pa[strlen(pa)]='~';
				}
				strcpy(pa,UNIXcrypt(pa,SALT));
				_bk=0;
				strcpy(ps,gin("Verify Password:",0));
				if (sul)
				{
					ps[strlen(ps)+1]=0;
					ps[strlen(ps)]='~';
a452 3
				strcpy(ps,UNIXcrypt(ps,SALT));
				if (strcmp(pa,ps))
					err=3;
d454 1
a454 19
					if (!strcmp(na,ps))
						err=1;
				if (sul)
				{
					pa[strlen(pa)+1]=0;
					pa[strlen(pa)]='~';
				}
				switch (err)
				{
				case 1:
					cprintf("You cannot use the same password.\n\r");
					break;
				case 2:
					cprintf("Passwords must be from %d to %d characters.\n\r",min,max);
					break;
				case 3:
					cprintf("Password not verified!\n\r");
					break;
				}
d467 3
d473 1
a473 1
				fprintf(npas,"%lu %lu %lu\n",ut,ed,pe);
d540 2
a541 3
			cprintf("Passwords must be from %d to %d characters.\n\r",min,max);
			sprintf(tol,"Passwords must be from %d to %d characters.",min,max);
			tolog(tol);
d557 1
d589 10
a598 2
			if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
				error("Error in time stamps.");
d604 1
a604 1
				sprintf(lo,"%d/%d/%d",td.da_day,td.da_mon,td.da_year);
d606 1
a606 1
				sprintf(lo,"%d/%d/%d",td.da_mon,td.da_day,td.da_year);
d617 1
a617 1
					sprintf(lo,"%d/%d/%d",td.da_day,td.da_mon,td.da_year);
d619 1
a619 1
					sprintf(lo,"%d/%d/%d",td.da_mon,td.da_day,td.da_year);
d631 1
a631 1
					sprintf(lo,"%d/%d/%d",td.da_day,td.da_mon,td.da_year);
d633 1
a633 1
					sprintf(lo,"%d/%d/%d",td.da_mon,td.da_day,td.da_year);
d638 13
d676 9
a684 1
		strcat(lo,"Passwd Expiry");
d686 1
a686 1
		for(y=0;y<(PEST+13);y++)
d690 1
a690 1
			gotoxy(PEST+15,4);
d695 1
a695 1
			cprintf("\n\r");
d716 1
a716 1
		if (tp+WIND<x)
d718 1
a718 1
			gotoxy(PEST+15,21);
a785 1
	tolog("Create User");
d865 1
a865 1
			cprintf("Logins must be from %d to %d characters.\n\r",min,max);
d868 1
a868 1
			cprintf("Passwords must be from %d to %d characters.\n\r",min,max);
d879 1
a879 1
			sprintf(tol,"  * User %s Created.",na);
d886 3
a888 1
			fprintf(pass,"%lu %lu %lu\n",ut,ed,pe);
a903 1
	tolog("Delete User.");
d909 11
d938 2
a939 1
				if (ps[strlen(ps)-1]=='~')
d941 13
a953 2
				cprintf("\n\r\n\rAre you sure you want to delete %s? ",na);
				opt=getch();
d962 1
a962 1
					sprintf(tol,"  * User %s Deleted.",na);
a983 1
	tolog("Toggle SuperUser Status.");
d1033 1
a1033 1
							cprintf("Passwords must be from %d to %d characters.\n\r",min,max);
d1075 1
a1075 1
								strcpy(tol,"  * SuperUser Access ");
d1088 5
a1119 1
	tolog("Change Expity Date.");
d1145 10
a1154 2
				if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
					error("Error in time stamps.");
d1159 1
a1159 1
						cprintf("Current expiry date is %d/%d/%d.\n\r",td.da_day,td.da_mon,td.da_year);
d1161 1
a1161 1
						cprintf("Current expiry date is %d/%d/%d.\n\r",td.da_mon,td.da_day,td.da_year);
d1183 1
a1183 1
					fprintf(npas,"%lu %lu %lu\n",ut,ed,pe);
d1186 1
a1186 1
					sprintf(tol,"  * User %s account expiry changed to ",lo);
d1188 1
a1188 1
						sprintf(lo,"%d/%d/%d",td.da_day,td.da_mon,td.da_year);
d1190 1
a1190 1
						sprintf(lo,"%d/%d/%d",td.da_mon,td.da_day,td.da_year);
a1216 1
	tolog("Password Expiry Date.");
d1242 10
a1251 2
				if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
					error("Error in time stamps.");
d1256 1
a1256 1
						cprintf("Current expiry date is %d/%d/%d.\n\r",td.da_day,td.da_mon,td.da_year);
d1258 1
a1258 1
						cprintf("Current expiry date is %d/%d/%d.\n\r",td.da_mon,td.da_day,td.da_year);
d1280 1
a1280 1
					fprintf(npas,"%lu %lu %lu\n",ut,ed,pe);
d1283 1
a1283 1
					sprintf(tol,"  * User %s password expiry changed to ",lo);
d1285 1
a1285 1
						sprintf(lo,"%d/%d/%d",td.da_day,td.da_mon,td.da_year);
d1287 1
a1287 1
						sprintf(lo,"%d/%d/%d",td.da_mon,td.da_day,td.da_year);
d1349 86
d1440 1
a1440 1
	strcpy(txt[4],"4. Toggle SuperUser status");
d1443 4
a1446 2
	strcpy(txt[7],"7. View log file");
	strcpy(txt[8],"8. Exit");
d1463 1
a1463 1
	while ((opt > '8') || (opt < '1')) /* Change SUOPT here */
d1515 7
d1559 9
a1567 1
			case '8': /* change SUOPT here */
d1628 10
a1637 2
				if (sscanf(ti,"%lu %lu %lu",&ut,&ed,&pe)!=3)
					error("Error in time stamps.");
d1640 1
a1640 1
					cprintf("Last login was on %d/%d/%d at",td.da_day,td.da_mon,td.da_year);
d1642 1
a1642 1
					cprintf("Last login was on %d/%d/%d at",td.da_mon,td.da_day,td.da_year);
d1649 3
a1651 1
				fprintf(npas,"%lu %lu %lu\n",ut,ed,pe);
d1658 3
a1660 1
		if ((ut>ed) && (ed!=0))
d1664 2
a1665 1
			tolog("User's Password has Expired.");
d1673 77
a1783 1
	tolog("User Finished.");
d1805 1
a1805 1
int err=1,ero=0,try=1,x,su,unn;
d1876 1
a1876 1
	if (fscanf(ini,"WrongPassword=\"%s",&xpwd)==0)
d1878 1
a1878 13
	x=1;
	while (x)
	{
		fscanf(ini,"%s",&temp);
		if (temp[strlen(temp)-1]=='\"')
		{
			x=0;
			temp[strlen(temp)-1]=0;
			fscanf(ini,"\n");
		}
		strcat(xpwd," ");
		strcat(xpwd,temp);
	}
d1880 1
a1880 1
	if (fscanf(ini,"WrongLogin=\"%s",&xlog)==0)
d1882 1
a1882 13
	x=1;
	while (x)
	{
		fscanf(ini,"%s",&temp);
		if (temp[strlen(temp)-1]=='\"')
		{
			x=0;
			temp[strlen(temp)-1]=0;
			fscanf(ini,"\n");
		}
		strcat(xlog," ");
		strcat(xlog,temp);
	}
d1884 1
a1884 1
	if (fscanf(ini,"LogWrongPassword=\"%s",&lxpwd)==0)
d1886 1
a1886 13
	x=1;
	while (x)
	{
		fscanf(ini,"%s",&temp);
		if (temp[strlen(temp)-1]=='\"')
		{
			x=0;
			temp[strlen(temp)-1]=0;
			fscanf(ini,"\n");
		}
		strcat(lxpwd," ");
		strcat(lxpwd,temp);
	}
d1888 1
a1888 1
	if (fscanf(ini,"LogWrongLogin=\"%s",&lxlog)==0)
d1890 17
a1906 13
	x=1;
	while (x)
	{
		fscanf(ini,"%s",&temp);
		if (temp[strlen(temp)-1]=='\"')
		{
			x=0;
			temp[strlen(temp)-1]=0;
			fscanf(ini,"\n");
		}
		strcat(lxlog," ");
		strcat(lxlog,temp);
	}
d1934 3
d1977 1
a1977 1
	tolog("Log Started.");
d1982 1
a1988 2
		sprintf(tol,"LOGIN:     %s",na);
		tolog(tol);
d1990 1
a1994 2
		if ((strlen(pa)>max) || (strlen(pa)<min))
			err=2;
d2020 2
a2021 4
					if (err==4)
						err=0;
					if (x)
						y=1;
a2022 2
					sprintf(tol,"Found %s in password file.",na);
					tolog(tol);
d2037 2
a2042 6
		if ((try>maxtry) && err)
		{
			cprintf("Exceeded maximum number of tries.\n\r");
			tolog("Exceeded maximum number of tries.");
			ero=100;
		}
d2046 3
a2048 6
			cprintf("Logins must be from %d to %d characters.\n\r",min,max);
			sprintf(tol,"Logins must be from %d to %d characters.",min,max);
			tolog(tol);
			sleep(wait);
			while(kbhit())
				getch();
d2051 3
a2053 6
			cprintf("Passwords must be from %d to %d characters.\n\r",min,max);
			sprintf(tol,"Passwords must be from %d to %d characters.",min,max);
			tolog(tol);
			sleep(wait);
			while(kbhit())
				getch();
d2057 2
a2058 4
			tolog(lxpwd);
			sleep(wait);
			while(kbhit())
				getch();
d2062 2
a2063 4
			tolog(lxlog);
			sleep(wait);
			while(kbhit())
				getch();
d2066 6
d2073 4
a2076 1
			tolog("This user has been tampered with!!");
d2081 5
d2088 2
a2089 1
		tolog("SuperUser Logged In...");
d2091 5
@


1.0
log
@Initial revision
@
text
@d2 1
a2 1
															Sentry V1.0
d20 5
d31 5
d37 3
d41 4
a44 2
#define DFC	LIGHTGRAY
#define WIND	15
d51 4
d56 4
d61 4
a64 1
const char ver[4]="1.0";
d74 2
a75 2
char bd[MAX];
int min,max,maxtry,un=0,wait,sul,_bk,bk,col;
d88 1
d102 1
a108 1

d115 11
d137 3
a139 7
	fprintf(log,"User locked out at %d/%d/%d -",td.da_day,td.da_mon,td.da_year);
	gettime(&nw);
	fprintf(log," %02d:%02d:%02d.%02d\n",nw.ti_hour,nw.ti_min,nw.ti_sec,nw.ti_hund);
	fclose(pass);
	fclose(npas);
	fclose(ini);
	fclose(log);
d146 18
a163 5
		pa[y]=getch();
		pa[y+1]=0;
		y++;
		if (!strcmp(bd,pa))
			fin(9);
d177 1
a177 1
	fprintf(log,"%s\n",s);
d189 1
a189 1
	fprintf(log,"User attempted to exit.\n");
d194 11
d236 1
a236 1
			if (ech)
d238 1
a238 2
				if (!((ar[x]<32) || (ar[x]>125)))
				{
a239 2
					gi[x]=ar[x];
				}
d241 2
a242 7
					x--;
				if ((ar[x+1]==8) && (x>=0))
				{
					ar[x+1]=0;
					x-=1;
					cprintf("%c %c",8,8);
				}
a244 6
			{
				cprintf("*");
				gi[x]=ar[x];
			}
			if (ar[x]==8)
			{
d246 6
a251 7
				cprintf("%c %c",8,8);
				if (x>=0)
				{
					x--;
					cprintf("%c %c",8,8);
				}
			}
d278 1
a278 1
		if (tc==BLACK)
d280 2
a281 2
			textbackground(tc);
			textcolor(DFC);
d285 2
a286 2
			textbackground(DFC);
			textcolor(BLACK);
d375 1
d377 1
a377 1
				if (ps[13]=='~')
d380 1
a380 1
					na[13]=0;
d435 2
a436 1
				pe=pel;
d481 1
a481 1
			if (ps[13]=='~')
d483 1
a483 1
				ps[13]=0;
d491 2
a492 1
					fprintf(log,"%s is changing passwords.\n",na);
d505 2
a506 1
			fprintf(log,"Passwords must be from %d to %d characters.\n",min,max);
d511 1
a511 1
			fprintf(log,"%s\n",lxpwd);
d516 1
a516 1
			fprintf(log,"%s\n",lxlog);
d535 2
a536 4
char *txt[MAXUSER],opt=0;
	for(x=1;x<=MAXUSER;x++)
		if ((txt[x]=malloc(MAX))==NULL)
			error("Out of memory!");
d549 1
a549 1
			if (ps[13]=='~')
d553 2
d556 38
d601 2
a602 2
		txb(BLACK);
		txc(WHITE);
d604 27
a630 1
		cprintf("\n\r\n\rCurrent Users (ESC exits)\n\r\n\r");
d633 1
a633 1
			if (y<x)
d637 2
a638 2
					txb(RED);
					txc(YELLOW);
d642 2
a643 2
					txb(BLACK);
					txc(WHITE);
d649 9
a657 3
		txb(BLACK);
		txc(WHITE);
		cprintf("\n\rSelect a user: ");
d662 1
a662 1
				return(sel);
d665 1
a665 1
				if ((sel<(WIND-1)) && ((sel+tp)<(x-1)))
d668 1
a668 1
				if ((sel+tp)<(x-1))
d687 1
d689 3
d696 1
a696 1
				if ((tp+WIND)<x)
d700 2
a701 2
				if (!((sel+tp)<=(x-1)))
					sel=x-tp-1;
d721 1
d744 1
a744 10
		fclose(pass);
		if ((pass=fopen(ipas,"a"))==NULL)
			error("Error opening password file!");
		_bk=1;
		strcpy(pa,gin("Password:",0));
		if (bk)
			break;
		if ((strlen(pa)>max) || (strlen(pa)<min))
			err=2;
		if (sul)
d746 51
a796 2
			pa[strlen(pa)+1]=0;
			pa[strlen(pa)]='~';
a797 31
		strcpy(pa,UNIXcrypt(pa,SALT));
		_bk=1;
		strcpy(ps,gin("Verify Password:",0));
		if (bk)
			break;
		if (sul)
		{
			ps[strlen(ps)+1]=0;
			ps[strlen(ps)]='~';
		}
		strcpy(ps,UNIXcrypt(ps,SALT));
		if (strcmp(pa,ps))
			err=3;
		if (sul)
		{
			pa[strlen(pa)+1]=0;
			pa[strlen(pa)]='~';
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
d815 2
d838 2
d862 3
a864 3
				if (ps[13]=='~')
					cprintf("\n\rThis is a SuperUser!\n\r");
				cprintf("Are you sure you want to delete %s? ",na);
d872 5
d893 1
a893 1
int v,err,y=0;
d896 2
d928 1
d931 1
a931 1
					if (ps[13]=='~')
a944 10
							err=2;
						if (sul)
						{
							pa[strlen(pa)+1]=0;
							pa[strlen(pa)]='~';
						}
						strcpy(pa,UNIXcrypt(pa,SALT));
						_bk=0;
						strcpy(ps,gin("Verify Password:",0));
						if (sul)
a945 14
							ps[strlen(ps)+1]=0;
							ps[strlen(ps)]='~';
						}
						strcpy(ps,UNIXcrypt(ps,SALT));
						if (strcmp(pa,ps))
							err=3;
						if (sul)
						{
							pa[strlen(pa)+1]=0;
							pa[strlen(pa)]='~';
						}
						switch (err)
						{
						case 2:
d947 3
a949 4
							break;
						case 3:
							cprintf("Password not verified!\n\r");
							break;
d951 1
a951 1
						if (!sul)
d953 47
a999 2
							ps[strlen(ps)+1]=0;
							ps[strlen(ps)]='\n';
a1000 6
						else
						{
							ps[strlen(ps)+2]=0;
							ps[strlen(ps)+1]='\n';
							ps[strlen(ps)]='~';
						}
d1028 1
d1052 1
a1052 1
				if (ps[13]=='~')
d1059 4
a1062 1
					cprintf("Current expiry date is %d/%d/%d.\n\r",td.da_day,td.da_mon,td.da_year);
d1085 10
d1118 1
d1142 1
a1142 1
				if (ps[13]=='~')
d1149 4
a1152 1
					cprintf("Current expiry date is %d/%d/%d.\n\r",td.da_day,td.da_mon,td.da_year);
d1175 10
d1196 4
d1202 1
d1232 1
d1243 12
d1265 1
a1265 12
char *txt[SUOPT];
	for(x=1;x<=SUOPT;x++)
		if ((txt[x]=malloc(MAX))==NULL)
			error("Out of memory!");
	strcpy(txt[1],"1. Create User");
	strcpy(txt[2],"2. Delete User");
	strcpy(txt[3],"3. View All Users");
	strcpy(txt[4],"4. Toggle SuperUser status");
	strcpy(txt[5],"5. Change Account Expiry Date");
	strcpy(txt[6],"6. Change Password Expiry Date");
	strcpy(txt[7],"7. View log file");
	strcpy(txt[8],"8. Exit");
d1271 2
a1272 2
		txb(BLACK);
		txc(WHITE);
d1279 2
a1280 2
				txb(RED);
				txc(YELLOW);
d1284 2
a1285 2
				txb(BLACK);
				txc(WHITE);
d1289 2
a1290 2
		txb(BLACK);
		txc(WHITE);
d1306 1
d1343 1
d1365 1
d1422 4
a1425 1
				cprintf("Last login was on %d/%d/%d at",td.da_day,td.da_mon,td.da_year);
d1443 1
d1457 1
d1463 3
d1485 3
a1489 8
	getdate(&td);
	fprintf(log,"User finished at %d/%d/%d -",td.da_day,td.da_mon,td.da_year);
	gettime(&nw);
	fprintf(log," %02d:%02d:%02d.%02d\n",nw.ti_hour,nw.ti_min,nw.ti_sec,nw.ti_hund);
	fclose(pass);
	fclose(npas);
	fclose(ini);
	fclose(log);
d1492 2
a1493 1
		cprintf("\n\r\n\rType \"EXIT\" to leave the Sentry DOS shell.\n\r");
d1511 5
d1529 5
d1653 15
d1669 1
d1674 1
a1674 1
		txc(YELLOW);
d1676 1
a1676 1
		txc(LIGHTRED);
d1680 1
a1680 1
		txc(LIGHTBLUE);
d1686 1
a1686 1
		txc(YELLOW);
d1688 1
a1688 1
		txc(LIGHTRED);
d1690 1
a1690 1
		txc(WHITE);
d1692 1
a1692 1
		txc(YELLOW);
d1694 1
a1694 1
		txc(LIGHTRED);
d1697 1
a1697 1
	txc(WHITE);
d1708 1
a1708 4
	getdate(&td);
	fprintf(log,"Log started at %d/%d/%d -",td.da_day,td.da_mon,td.da_year);
	gettime(&nw);
	fprintf(log," %02d:%02d:%02d.%02d\n",nw.ti_hour,nw.ti_min,nw.ti_sec,nw.ti_hund);
d1719 2
a1720 1
		fprintf(log,"LOGIN:     %s\n",na);
a1729 4
/**
		Do I want to print passwords to the log?
		fprintf(log,"PASSWORD:  %s\n",pa);
**/
d1744 1
a1744 1
			if (ps[13]=='~')
d1746 1
a1746 1
				ps[13]=0;
d1758 2
a1759 1
					fprintf(log,"Found %s in password file.\n",na);
d1781 1
a1781 1
			fprintf(log,"Exceeded maximum number of tries.\n");
d1788 2
a1789 1
			fprintf(log,"Logins must be from %d to %d characters.\n",min,max);
d1791 2
d1796 2
a1797 1
			fprintf(log,"Passwords must be from %d to %d characters.\n",min,max);
d1799 2
d1804 1
a1804 1
			fprintf(log,"%s\n",lxpwd);
d1806 2
d1811 1
a1811 1
			fprintf(log,"%s\n",lxlog);
d1813 2
d1818 1
a1818 1
			fprintf(log,"This user has been tampered with!!\n");
d1825 1
a1825 1
		fprintf(log,"SuperUser Logged In...\n");
@
