head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.25.56;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.44.15;	author MIKE;	state Exp;
branches;
next	;


desc
@Functions that perform low-level sysetem jobs.
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

/* If it's the shareware version, use this for the "encoding" */
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
  if (!streq(ilog,""))
  {
    tolog("User Locked Out.");
    tolog("-----------------------------");
  }
  flushall();
  fcloseall();
  if (!streq(ilog,""))
    _rtl_chmod(ilog,1,FA_HIDDEN);
  _rtl_chmod(ilbk,1,FA_HIDDEN);
  _rtl_chmod(imsg,1,FA_HIDDEN);
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
  exit(1);
#endif
}

void prd(void)
{
  if (sscanf(ti,"%lu %lu %lu %d %d %lu",&ut,&ed,&pe,&fla,&ntl,&ae)!=6)
    error(ACINF);
  /*
    ut=   last login date
    ed=   account expiry date
    pe=   password expiry date
    fla=  # of failed login attempts
    ntl=  max invalid login attempts
    ae=   spare
  */
}

short int guser(short int us)
{
short int u;
  if (!us)
    return(0);
  for(u=1;u<us;u++)
  {
    fgets(lo,MAX,pass);
    fgets(ps,MAX,pass);
    fgets(ti,MAX,pass);
    if (!strcmp(lo,DIV))
      return(0);
    if (npas)
    {
      fputs(lo,npas);
      fputs(ps,npas);
      fputs(ti,npas);
    }
  }
  fgets(lo,MAX,pass);
  fgets(ps,MAX,pass);
  fgets(ti,MAX,pass);
  if (!strcmp(lo,DIV))
    return(0);
  prd();
  return(1);
}

char* tmpath(char *t)
{
char tmt[MAX];
  strcpy(tmt,t);
  tmpnam(tmt);
  strcpy(t,te);
  strcat(t,tmt);
  return(t);
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
  fprintf(logf,"%s\n[",usr);
  if (df)
    fprintf(logf,"%02d/%02d/%02d -",td.da_day,td.da_mon,td.da_year);
  else
    fprintf(logf,"%02d/%02d/%02d -",td.da_mon,td.da_day,td.da_year);
  gettime(&nw);
  fprintf(logf," %02d:%02d:%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,s);
  if ((ftell(logf)/1024)>(mlog-1))
    dlog();
}

void dlog(void)
{
FILE *log2;
char dr[MAXDRIVE],di[MAXDIR],fi[MAXFILE],ex[MAXEXT],t2[MAX],t3[MAX];
int fl,x;
  fclose(logf);
  if ((log2=fopen(ilbk,"a"))==NULL)
    error(CRBKL);
  if ((logf=fopen(ilog,"r"))==NULL)
    error(OPLOG);
  fl=1;
  while((fgets(lo,MAX,logf))!=NULL)
  {
    fputs(lo,log2);
    if ((ftell(logf)/1024)>(mlog/2) && fl) 
    {
      fl=0;
      fclose(log2);
      x=fnsplit(imsg,dr,di,fi,ex);
      tmpnam(t2);
      if (x & DIRECTORY)
      {
        strcpy(t3,t2);
        strcpy(t2,di);
        strcat(t2,t3);
      }
      if (x & DRIVE)
      {
        strcpy(t3,t2);
        strcpy(t2,dr);
        strcat(t2,t3);
      }
      if ((log2=fopen(t2,"w"))==NULL)
        error(CRTMP);
    }
  }
  fclose(log2);
  fclose(logf);
  sunlink(ilog);
  rename(t2,ilog);
  if ((logf=fopen(ilog,"a"))==NULL)
    error(CRLOG);
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

long gdate(void)
/*
  gdate(void) is a function called when the user is expected to enter a
  date. The function prompts the user for the date, warns him if it falls
  in the past, and returns it in standard UNIX format as a long.
*/
{
char ho[MAX],opt;
long ck,di;
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
    cprintf("\r\n\r\nEnter 'N' at year prompt to assign no expiry date.");
    strcpy(ho,gin("\r\nEnter the year (4 digits): ",1));
    if ((streq(ho,"n")) || (streq(ho,"N")))
      ck=0;
    else
    {
      ld.da_year=atoi(ho);
      if (ld.da_year<100)
      {
        cprintf("\r\nYear must be 4 digits!");
        x=0;
      }
      else
      {
        strcpy(ho,gin("\r\nEnter the month (2 digits): ",
            1));
        ld.da_mon=atoi(ho);
        strcpy(ho,gin("\r\nEnter the day (2 digits): ",
            1));
        ld.da_day=atoi(ho);
        ck=dostounix(&ld,&lt);
      }
    }
    if (x && ck && (di>ck))
    {
      cprintf("\r\nThat date is in the past!");
      cprintf("\r\nAre you sure you want to use it? ");
      opt=blch();
      if ((opt!='y') && (opt!='Y'))
      {
        cprintf("Yes");
        x=0;
      }
      else
        cprintf("No");
    }
  }
  return(ck);
}

FILE* ffwd(int sp,FILE* dmp)
/*
  ffwd() scans the file for the "sp th" marker. If dmp is defined (file
  stream), then input is buffered and written out to dmp.
*/
{
char scr[80*25*2];
short int tx,ty,rrl,rrt,rrb,rrr,rrk,rrf,spp=0;
int yz,zz,bp;
FILE* fn;
char buf[BUFSZ+2],ff[DIVLEN+2];
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
  if ((fn=fopen(inam,"rb"))==NULL)
    error(RDOP);
  bp=0;
  for(zz=0;zz<=DIVLEN;zz++)
    ff[zz]=0;
  sp+=4;
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
        if (strlen(ssm))
        {
          cprintf("%c%c",DEL,SPIN[spp]);
          spp++;
          spp%=4;
        }
        if (dmp)
          for(zz=0;zz<=bp;zz++)
            fputc(buf[zz],dmp);
        bp=-1;
      }
      bp++;
    }
    if (yz)
      error(RDSC);
    sp--;
  }
  if (dmp)
    for(zz=0;zz<bp;zz++)
      fputc(buf[zz],dmp);
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
  return(fn);
}

void fcd(FILE* fn,FILE* dmp)
/*
  fcd() closes file fn while dumping any remaining information into
  dmp.
*/
{
char scr[80*25*2];
short int tx,ty,rrl,rrt,rrb,rrr,rrk,rrf,spp=0;
int zz,bp;
char buf[BUFSZ+2];
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
  bp=0;
  while(!feof(fn))
  {
    buf[bp]=zenc(fgetc(fn));
    if (feof(fn))
      bp--;
    if (bp==BUFSZ)
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
      for(zz=0;zz<=bp;zz++)
        fputc(buf[zz],dmp);
      bp=-1;
    }
    bp++;
  }
  for(zz=0;zz<bp;zz++) // Flush Buffer
    fputc(buf[zz],dmp);
  fclose(fn);
  fclose(dmp);
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

char* gstr(void)
{
  char s[MAX];
  if ((fgets(s,MAX,ini))==NULL)
    error(INSET);
  chop2(s);
  return(s);
}

void help(void)
{
FILE *hlf;
char scr[80*25*2],hf[MAX],hd[MAX];
short int x,tx,ty,rrl,rrr,rrt,rrb,rrf,rrk;
  if (hl>=0)
  {
    hl=-hl;
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
    crwin(3,5,77,20,tf,tb,2,"Online Help");
    if (hl)
    {
      strcpy(hf,ins);
      strcat(hf,"\\");
      strcat(hf,SENTRY);
      strcat(hf,".hlp");
      if ((hlf=fopen(hf,"r"))==NULL)
        cprintf("\r\n\r\n  Error Opening %s Help Information!\r\n",SENTRY);
      else
      {
        for(x=0;x<((-hl)-1);x++)
          while((fgets(hd,MAX,hlf)!=NULL) && (hd[0]!=''))
          { /* Just keep readin' fella */
          }
        x=0;
        while((fgets(hd,MAX,hlf)!=NULL) && (hd[0]!=''))
        {
          if (x>11)
          {
            cprintf("\r\n Press any key for more help...");
            x=blch();
            if (x==ESC)
              break;
            else
            {
              clrscr();
              x=0;
            }
          }
          cprintf("%s\r",hd); /* Read help info */
          x++;
        }
        cprintf("\r\n");
      }
      fclose(hlf);
    }
    else
      cprintf("\r\n\r\n  No help available in this context.\r\n");
    if (x!=ESC)
    {
      cprintf("\r\nPress any key to return...");
      blch();
    }
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
    hl=-hl;
  }
}

void dshell(void)
{
//unsigned env_addr,seglen;
//char value[MAX],**env_var;
//int count;
//short int index;
	strcpy(tol,getenv("SHELL"));
  strupr(tol);
  if (streq(tol,"ON"))
  {
    sprintf(tol,"%s DOS Shell",SENTRY);
    crwin(4,6,70,10,tf,tb,2,tol);
    cprintf("\r\n  Cannot enter DOS Shells recursively. (Press a key)\r\n");
    blch();
  }
  else
  {
    sprintf(tol,"User entered the %s DOS Shell.",SENTRY);
    tolog(tol);
    fclose(logf);
    cprintf("\n\r  Type \"EXIT\" to leave the %s DOS Shell.\n\r",SENTRY);
    strcpy(tol,getenv("COMSPEC"));
    strcpy(lo,getenv("PROMPT"));
/*
    fnsplit(tol,cp,lo,na,pa);
    strcpy(tol,cp);
    strcat(tol,lo);
    cpath(1,tol);
    strcpy(temp,"command ");
    strcat(temp,tol);
    strcat(temp," /k prompt [");
    strcat(temp,SENTRY);
    strcat(temp,"] $p$g");
*/
/*
    if (!getenvseg(&env_addr))  /* Clear SHELL /
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"SHELL=");
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  /* Set SHELL=ON to avoid recursion /
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"SHELL=ON");
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  /* Clear PROMPT /
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"PROMPT=");
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  /* Set PROMPT=[SENTRY] %PROMPT /
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"PROMPT=[Sentry] ");
    strcat(value,lo);
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
*/
    crwin(1,1,79,24,tf,tb,0,"");
    gotoxy(1,24);
//  system(temp);
    system(tol);
    if ((logf=fopen(ilog,"a"))==NULL)
      error(CRLOG);
    sprintf(tol,"%s DOS Shell finished.",SENTRY);
    tolog(tol);
/*
    if (!getenvseg(&env_addr))  /* Restore PROMPT /
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"PROMPT=");
    strcat(value,lo);
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  /* Clear SHELL /
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"SHELL=");
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
*/    
  }
}

unsigned long rai(int r)
{
int rr;
long ans=1;
  for(rr=1;rr<=r;rr++)
    ans*=2;
  return(ans);
}
@


4.7
log
@*** empty log message ***
@
text
@d2 5
d38 3
a40 3
    _chmod(ilog,1,FA_HIDDEN);
  _chmod(ilbk,1,FA_HIDDEN);
  _chmod(imsg,1,FA_HIDDEN);
d254 2
d257 3
d289 1
a289 1
    cprintf(" Please Wait....");
d296 1
a296 1
  sp++;
d369 1
a369 1
  cprintf(" Please Wait....");
d387 1
a387 1
  for(zz=0;zz<bp;zz++)
d436 3
a438 1
      strcat(hf,"\\sentry.hlp");
d440 1
a440 1
        cprintf("\r\n\r\n  Error Opening Sentry Help Information!\r\n");
d454 1
a454 1
            if (x==27)
d471 1
a471 1
    if (x!=27)
d494 110
a603 20
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
    error(CRLOG);
  sprintf(tol,"%s DOS Shell finished.",SENTRY);
  tolog(tol);
@


3.8
log
@*** empty log message ***
@
text
@d26 1
d28 2
a58 30
void error(char *s)
/*
  error(char *s) handles all fatal errors within Sentry. It prints a
  copy of the message to screen and to the log file and proceeds to lock
  the user out of the computer.
  The parameter s contains the error message.
*/
{
  crwin(15,8,strlen(s)+22,12,YELLOW,LIGHTRED,2,"SYSTEM ERROR");
  cprintf("\n\r   ");
  cprintf("%s",s);
  cprintf("\n\r");
  fclose(logf);
  if ((logf=fopen(ilog,"a"))!=NULL)
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

d62 9
a70 1
    error("Error in Account Information.");
d73 1
a73 1
void guser(int us)
d76 2
d83 8
a90 3
    fputs(lo,npas);
    fputs(ps,npas);
    fputs(ti,npas);
d95 2
d98 1
d138 1
a138 1
    error("Error in creating backup log file!");
d140 1
a140 1
    error("Error opening log file!");
d164 1
a164 1
        error("Error opening temp file!");
d169 1
a169 1
  unlink(ilog);
d172 1
a172 70
    error("Error in creating log file!");
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
  {
    gi[x]=0;
    ar[x]=0;
  }
  x=0;
  while (x<(MAX-1))
  {
    ar[x]=blch();
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
        if (ech || (pec=='!'))
          cprintf("%c",ar[x]);
        else
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
d184 2
a185 2
  int x=0,y;
  char pret[MAX],p8[MAX];
d205 5
a209 5
  char ho[MAX],opt;
  long di,ck;
  struct date ld;
  struct time lt;
  short int x=0;
d220 2
a221 2
    cprintf("\n\r\n\rEnter 'N' at year prompt to assign no expiry date.");
    strcpy(ho,gin("\n\rEnter the year (4 digits): ",1));
d229 1
a229 1
        cprintf("\n\rYear must be 4 digits!");
d234 1
a234 1
        strcpy(ho,gin("\n\rEnter the month (2 digits): ",
d237 1
a237 1
        strcpy(ho,gin("\n\rEnter the day (2 digits): ",
d245 2
a246 2
      cprintf("\n\rThat date is in the past!");
      cprintf("\n\rAre you sure you want to use it? ");
d261 2
d266 15
d282 1
a282 1
    error("Error Reading Data Segment! [Open]");
d300 6
d314 1
a314 1
      error("Error Reading Data Segment! [Scan]");
d320 15
d340 1
a340 1
  fcd() closes file str while dumping any remaining information into
d344 2
d348 12
d368 3
d381 12
d399 1
a399 1
    error("Error in Initialization Settings!");
d404 99
@
