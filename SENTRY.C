/*        
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

FILE *pass,*logf,*ini,*npas,*msg,*LANG;
char na[MAX],lo[MAX],pa[MAX],ps[MAX],ti[MAX];
    /* login (x2), password (x2), and time stamps */
char xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX],xplen[MAX],xllen[MAX],lxplen[MAX],lxllen[MAX];
     /* Various messages, and log file messages */
char cp[MAX]; /* Change Password Key */
char envar[MAX]; /* Environment Variable */
char usr[MAX]; /* User name */
char pwd[MAX]; /* User's encrypted password */
char win[MAX]; /* Command line argument */
char ilog[MAXDRIVE+MAXPATH]; /* Path to the log file */
char ilbk[MAXDRIVE+MAXPATH]; /* Path to the backup log file */
char imsg[MAXDRIVE+MAXPATH]; /* Path to the message file */
char ins[MAXDRIVE+MAXPATH]; /* Path to Sentry.ins */
char inam[MAX]; /* Path to Sentry.exe */
char temp[MAX2]; /* Temporary storage */
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
char SALT[4]; // crypt() Salt
char regto[30]; // Registered User
char regch[16]; // Checksum
char lang_name[10]; // Contains the name of the language file
char BUSY[22]; // "Please Wait...." banner

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
short int sl; // set_lang non-recursive flag
short int llp; /* Last login Pause */
short int sdel; /* Secure Deletion 0/1 */
short int vwh; // View Highlighting 0/1
short int vwc; // View Highligiting Colour
short int ctrl; // Disable CTRL-C
short int pecc; // Password echo character count
short int lang; // Language 0=English, 1=Spanish

int mlog; /* Max log file size (kb) */

/* Time Stamps */
long ut; /* Last login date */
long ed; /* Account Expiry Date */
long pe; /* Password Expiry Date */
long pel; /* Number of days a new password is good for */
long ae; /* Spare */
long ael; /* Number of days an account is good for */
long regno; // Registration Number
unsigned long CHECK; // Checksum Value

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
    cprintf("\r\n\r\n");
    strncpy(pa,gin(glstr(404),0),max);
//    strncpy(pa,gin("\n\r\n\rNew Password:",0),max);
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
      strncpy(ps,gin(glstr(20),0),max);
//      strncpy(ps,gin("Verify Password:",0),max);
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
          pstr(405);
          cprintf("\n\r");
//          cprintf("You cannot use the same password.\n\r");
          break;
        case 2:
      pstr(28);
//          cprintf("Passwords must be between ");
          cprintf(" %d ",min);
          pstr(522);
//          cprintf(" and ");
          cprintf(" %d ",max);
          pstr(206);
//          cprintf(" characters.\r\n");
          cprintf("\r\n");
          break;
        case 3:
          pstr(29);
          cprintf("\r\n");
//          cprintf("Password not verified!\n\r");
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
    fprintf(npas,"%s\r\n",su?temp:pa);
    strcpy(temp,glstr(408));
    if (lang==1) // Spanish
    {
      strcat(temp," ");
    }
    strcat(temp,lo);
    strcat(temp,glstr(409));
//    strcat(lo,"'s password has been changed.");
    tolog(temp);
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
    {
      sprintf(tol,"%s %02d/%02d/%02d ",glstr(410),td.da_day,td.da_mon,td.da_year);
//      sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_day,td.da_mon,td.da_year);
    }
    else
    {
      sprintf(tol,"%s %02d/%02d/%02d ",glstr(410),td.da_mon,td.da_day,td.da_year);
//      sprintf(tol,"Last login was on %02d/%02d/%02d at",td.da_mon,td.da_day,td.da_year);
    }
    strcat(tol,glstr(411));
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
          crwin(3,3,77,11,tf,tb,2,glstr(412));
//          crwin(3,3,77,11,tf,tb,2,"Message");
			 pstr(413);
          cprintf("\n\r");
//          cprintf("You have a message awaiting you.\n\r");
          fgets(ps,MAX,msg);
          chop(ps);
          pstr(414);
          cprintf(" %s\r\n",ps);
//          cprintf("FROM: %s\r\n",ps);
          fgets(lo,MAX,msg);
          tn=atol(lo);
          unixtodos(tn,&td,&nw);
          if (df)
            sprintf(pa,"%02d/%02d/%02d",td.da_day,td.da_mon,td.da_year);
          else
            sprintf(pa,"%02d/%02d/%02d",td.da_mon,td.da_day,td.da_year);
          sprintf(lp," %02d:%02d:%02d\n\r",nw.ti_hour,nw.ti_min,nw.ti_sec);
          strcat(pa,lp);
			 pstr(415);
          cprintf(" %s\r",pa);
//          cprintf("DATE: %s\r",pa);
          fgets(pa,MAX,msg);
          cprintf("\r\n%s\r\n",pa);
          pstr(416);
//          cprintf("\r\n%s\r\n[D]elete, [R]eply, or any other to keep...",pa);
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
              cprintf("\r\n\r\n\r\n");
              pstr(417);
//              cprintf("\r\n\r\n\r\nNot a current user - cannot reply.\r\n");
              cprintf("\r\n\r\n");
              pstr(48);
//              Press any key to continue...
              cprintf("\r\n\r\n");
              blch();
            }
            else
              smsg();  /* Send the message */
            if ((msg=fopen(imsg,"r"))==NULL)  /* Reset message file */
              error(OPMSG);
            fseek(msg,tn,SEEK_SET);
            /* Change un back for subsequent operations */
            un=x;
            cprintf("\r\n\r\n");
            pstr(419);
            cprintf(" ");
//            cprintf("\r\n\r\nDo you want to delete the original? ");
            x=blch();
            yeah(x)
            {
              pstr(211);
//              cprintf("Yes");
              x='d';
            }
            else
            {
              pstr(213);
//              cprintf("No");
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
      sprintf(ti,"%d %s\n\r",fla,glstr(420));
//      sprintf(ti,"%d invalid login attempt(s) have occurred since your last login.\n\r",fla);
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
      strcpy(tol,glstr(408));
      if (lang==1) // Spanish
      {
        strcat(tol," ");
      }
      strcat(tol,na);
      strcat(tol,glstr(421));
//      sprintf(tol,"%s's password has expired.",na);
      tolog(tol);
      cprintf("\n\r");
      pstr(422);
      cprintf("\n\r");
//      cprintf("\n\rNOTE: Your password has expired. You must enter a\n\r");
//      cprintf("      new one to retain your access.\n\r");
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
//win95();
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
  /* Get current video attributes */
  gettextinfo(&sta);
  textmode(C80);
  if (!gettext(1,1,80,25,msc))
    error(SCRD);
  xt.ti_hour=0;
  xt.ti_min=0;
  xt.ti_sec=0;
  xt.ti_hund=0;

  // Language (0=English, 1=Spanish)

//  lang=0; // Set to English for test purposes
  lang=1; // Set to Spanish for test purposes

  set_lang(0); // Set language, don't prompt

  ini=ffwd(0,NULL); // Get registration info
  strcpy(SALT,gstr());
  regno=atol(gstr());
  strcpy(regto,gstr());
  strcpy(regch,gstr());
  CHECK=atol(gstr()); // Read Checksum, even if it's not there
  fclose(ini);      // Done
  nd=dostounix(&xd,&xt)-regno;
  ltoa(nd,bd,10);
  un=0;
  sum=0; /* Not on the SuperUser menu yet */
  zze=0; /* Encryption off */
  sul=0; /* user is not a SuperUser */
  _bk=0; /* gin() is non-breakable */
  zm=0; /* ZULU mode off */
  hl=0; /* No default help */
  sl=0; // Not in set_lang menu
  col=1; // Colour on by default
  scrb=300; // 5 Min screen saver time
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
int x;
  if (zm)  // Zulu-mode: Run protected file!
  {
    if ((logf=fopen(ilog,"a"))==NULL)
      error(CRLOG);
    sprintf(tol,"%s %s",inam,glstr(423));
//    sprintf(tol,"%s run in protected mode",inam);
    if (zm==2)
    {
      strcat(tol," ");
      strcat(tol,glstr(424));
//      strcat(tol," as a Windows program");
    }
    strcat(tol,".");
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
    strcpy(tol,"");
// May be causing the "pop-up" error
//    if (zm==2)
//      strcpy(tol,"start ");
    strcat(tol,temp);
    strcat(tol," ");
    strcat(tol,win);
    system(tol);
    x=1;
    if (zm==2)
    {
      crwin(5,5,66,21,tf,tb,2,glstr(426));
//      crwin(5,5,66,21,tf,tb,2,"Windows Protected Program");
        pstr(427);
        cprintf("\r\n\r\n");
        pstr(428);
//      cprintf("\r\nNOTE: Sentry needs to perform some cleanup operations after");
//      cprintf("\r\nthe protected file has finished execution. Sentry cannot");
//      cprintf("\r\ndetermine when Windows programs terminate, so Sentry will");
//      cprintf("\r\nremain active until you confirm that the protected file");
//      cprintf("\r\nhas finished execution.");
//      cprintf("\r\n\r\nPressing a key before the protected file has terminated");
//      cprintf("\r\nwill cause a DOS \"Sharing Violation\" and may compromise");
//      cprintf("\r\nthe security of your system.");
      while (x)
      {
        cprintf("\r\n\r\n");
        pstr(429);
//        cprintf("\r\n\r\nPress any key when the protected file has finished");
//        cprintf("\r\nexecution...");
        blch();
//printf("(%d) - %d %d %d %d %d %d",_rtl_chmod(temp,0,0),FA_RDONLY,FA_HIDDEN,FA_SYSTEM,FA_LABEL,FA_DIREC,FA_ARCH);
				x=0;
/*  Try to determine when the file is actually free
        if (_rtl_chmod(temp,0,0)==-1)
        {
printf("[%d]<%d>",errno,EACCES);
          if (errno==EACCES)
          {
            clrscr();
            cprintf("\r\n\r\nSentry has sensed that the protected file has not yet");
            cprintf("\r\ncompletely finished execution.");
            cprintf("\r\n\r\nSentry cannot \"clear up\" until the protected file has");
            cprintf("\r\nterminated completely.");
          }
          else
            x=0;
        }
*/
      }
    }
    crwin(1,1,79,24,tf,tb,0,"");
    gotoxy(1,24);
    sunlink(temp); // Wait until execution has finished!
    if ((logf=fopen(ilog,"a"))==NULL)
      error(CRLOG);
    tolog(glstr(430));
//    tolog("Execution Complete.");
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
      sprintf(tol,"%s %s",SENTRY,glstr(322));
//      sprintf(tol,"%s DOS Shell",SENTRY);
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
#if !USER
  shar(1); // Shareware warning
#endif
  flushall();
  fcloseall();
  _rtl_chmod(ilog,1,FA_HIDDEN);
  _rtl_chmod(ilbk,1,FA_HIDDEN);
  _rtl_chmod(imsg,1,FA_HIDDEN);
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
short int ta,vir; /* Type ahead */
int count;
long y;
//printf("Beginning Debug...\n");
//ta=win95();
//printf("Win95: %d",ta);
//exit(0);
  strcpy(inam,argv[0]);
  x=fnsplit(inam,te,temp,lo,na);
  if (x & DIRECTORY)
  {
    strcat(te,temp);
    strcpy(ins,te);
  }
  // ins contains path to Sentry installation
  init();
  vir=0; // No Virus Checking by Default
#if USER
  strcpy(temp,regto);
  y=regno;
  x=0;
  while (y>0)
  {
    x+=(short)(y-(y/10)*10);
    y/=10;
  }
  itoa(x,na,10);
  strcpy(pa,na);
  strcat(pa,regch);
  if (!streq(UNIXcrypt(temp,na),pa)) // Check Reginfo
  {
    itoa(x-1,na,10); // SALT-1 for Anti-Virus Versions
    strcpy(pa,na);
    strcat(pa,regch);
    if (!streq(UNIXcrypt(temp,na),pa))  // Re-Check
      error(REGER);
    else
    {
      vir=1; // Virus Checking On
    }
  }
#endif
  ini=ffwd(1-2*vir,NULL); // Anti-Virus Checksum (-1)
  strcpy(v,gstr());
  if ((v[strlen(v)-1]=='Z') || (v[strlen(v)-1]=='X')) // Zulu or X-Ray Mode
  {
    v[strlen(v)-1]=0;  // (Protected file)
    zm=1;
    if (v[strlen(v)-1]=='W')
    {
      v[strlen(v)-1]=0; // Strip Windows Tag
      zm=2;
    }
    strcpy(zex,gstr()); // Extension
    strcpy(ins,gstr()); // Path to Sentry files
    strcpy(temp,gstr()); // Encryption key
    ze=temp[0];
  }
  if (strcmp(v,ver)>0)
    warning(NEWI);
  if (strcmp(v,ver)<0)
    warning(OLDI);
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
  if ((argc>1) && x) // Has arguments and enabled with Windows
  {
    strcpy(win,argv[1]);
  	for (x=2;x<argc;x++)
    {
      strcat(win," ");
      strcat(win,argv[x]);
    }
  }
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
  ctrl=atoi(gstr());
  pecc=atoi(gstr());
  fclose(ini);
  txb(tb);
  if (ctrl)  // Disable CTRL-C, etc by running BREAK.SYS if present
  {
    strcpy(temp,ins);
    strcpy(na,ins);
    strcat(temp,BREAK);
    strcat(na,BRNEW);
    strcpy(pa,"lh ");
    strcat(pa,na);
    strcat(pa,">nul");
    if ((npas=fopen(temp,"rb"))!=NULL)
    {
//***** Do some sort of verification that BREAK.SYS is the expected file.
			fclose(npas);
  		rename(temp,na);
//***** This system() command causes all of Sentry to be loaded into memory!
      system(pa);
  		rename(na,temp);
    }
    fclose(npas);
  }
#if !USER
  shar(0);
#endif
  if (!wm)
    clrscr();

/*
crwin(4,4,76,20,tf,tb,2,"");
cprintf("\r\n");
pstr(524);
cprintf("\r\n");
pstr(525);
cprintf("\r\n");
pstr(526);
cprintf("\r\n");
pstr(527);
exit(0);
*/

  if (x)
  {
    crwin(4,4,76,9,tf,tb,2,"");
    txc(DEFTXTCOL);
    cprintf("����������Ŀ ");
    txc(AUCOL);
    strcpy(temp,glstr(436));
    for(y=strlen(temp);y<29;y++)
      strcat(temp," ");
    cprintf("%s",temp);
//    cprintf("PC Security System         ");
    txc(RGCOL);
    pstr(437);
//    cprintf("Registered to");
    txc(DEFTXTCOL);
    cprintf("\n\r�");
    txc(TICOL);
    cprintf("%s",SENTRY);
    cprintf(" ");
    cprintf("%s",ver);
    txc(DEFTXTCOL);
    cprintf("� ");
    txc(AUCOL);
    cprintf("Copyright (C) 1995-1999");
    cprintf("      ");
    txc(RGCOL);
    cprintf("%s",regto);
    txc(DEFTXTCOL);
    cprintf("\n\r������������ ");
    txc(AUCOL);
    cprintf("Cipher Logic Canada Inc.");
    txc(RGCOL);
    cprintf("     ");
    pstr(440);
//    cprintf("Registration #:");
    txc(AUCOL);
    cprintf("\n\r             ");
    cprintf(EMAIL);
    txc(RGCOL);
    cprintf("       %lu",regno);
  }
  txc(tf);
  crwin(4,11,76,21,tf,tb,2,"");
  cprintf("\n\r");
  if (!wm)
    cprintf("\n\r");
  if (!streq(cp,"*"))
  {
    pstr(442);
//    cprintf("Enter \"");
    cprintf("%s",cp);
    pstr(443);
    cprintf("\r\n\r\n");
//    cprintf("\" at the password prompt to set a new password.\n\r\n\r");
    strcpy(cp,penc(cp));
  }

  if (!ta)
    while(kbhit())
      blch();
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
      pstr(444);
      cprintf("\n\r");
      tolog(glstr(444));
//      cprintf("Exceeded maximum number of tries.\n\r");
//      tolog("Exceeded maximum number of tries.");
      ero=100;
    }
    if ((y!=su) && !err)
    {
      sprintf(tol,"%s %s",na,glstr(445));
//      sprintf(tol,"%s has been tampered with!!",na);
      tolog(tol);
    }
  }
  if (ero==100)
    lockup();
  sum=1; /* You are now "logged in" */
  stamp();
  if (getenvseg(&env_addr))  /* Do the environment setting */
  {
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
  }
  if (!su && sul)
  {
    sprintf(tol,"%s %s",na,glstr(446));
//    sprintf(tol,"%s does not have SuperUser access.",na);
    tolog(tol);
  }
  if (su && sul)
  {
    sprintf(tol,"%s %s",na,glstr(447));
//    sprintf(tol,"%s logged in as SuperUser.",na);
    tolog(tol);
    cprintf("\n\r   ");
    pstr(48);
//    Press any key to continue...
    cprintf("\n\r");
    x=blch();
    super();
  }
  else
  {
    sprintf(tol,"%s %s",na,glstr(449));
//    sprintf(tol,"%s logged in.",na);
    tolog(tol);
  }
  fin(0);
}
