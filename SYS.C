/*
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
#else
#include "crypt.c"
#endif

void lockup(void)
/*
  lockup freezes computer operation by entering an endless loop that the
  user cannot break out of. This is done when a potantial security breach
  has been detected. The user must reset to exit the loop.
  The constant DEBUG must be true for lockup to occur.
*/
{
#if !DEBUG
  short int y;
#endif
  getdate(&td);
  if (!streq(ilog,""))
  {
    tolog(glstr(363));
//    tolog("User Locked Out.");
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
#if !DEBUG
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

#if DEBUG
    crwin(2,1,77,17,WINBAKCOL,WINTXTCOL,2,"");
    cprintf("%s\n[ %02d:%02d:%02d] %s\n",usr,nw.ti_hour,nw.ti_min,nw.ti_sec,s);
    blch();
#endif

  fprintf(logf," %02d:%02d:%02d] %s\n",nw.ti_hour,nw.ti_min,nw.ti_sec,s);
  if ((ftell(logf)/1024)>(mlog-1))
    dlog();
}

void dlog(void)
// Dumps log to backup (automated)
// Called by tolog.
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
    cprintf("\r\n\r\n");
    pstr(365);
//    cprintf("\r\n\r\nEnter 'N' at year prompt to assign no expiry date.");
    cprintf("\r\n");
    strcpy(ho,gin(glstr(366),1));
//    strcpy(ho,gin("\r\nEnter the year (4 digits): ",1));
    if ((streq(ho,"n")) || (streq(ho,"N")))
      ck=0;
    else
    {
      ld.da_year=atoi(ho);
      if (ld.da_year<100)
      {
        cprintf("\r\n");
        pstr(367);
//        cprintf("\r\nYear must be 4 digits!");
        x=0;
      }
      else
      {
        cprintf("\r\n");
        strcpy(ho,gin(glstr(368),1));
//        strcpy(ho,gin("\r\nEnter the month (2 digits): ",1));
        ld.da_mon=atoi(ho);
        cprintf("\r\n");
        strcpy(ho,gin(glstr(369),1));
//        strcpy(ho,gin("\r\nEnter the day (2 digits): ",1));
        ld.da_day=atoi(ho);
        ck=dostounix(&ld,&lt);
      }
    }
    if (x && ck && (di>ck))
    {
        cprintf("\r\n");
        pstr(370);
        cprintf("\r\n");
        pstr(371);
        cprintf(" ");
//      cprintf("\r\nThat date is in the past!");
//      cprintf("\r\nAre you sure you want to use it? ");
      opt=blch();
      yeah(opt)
      {
        pstr(211);
//        cprintf("Yes");
        x=0;
      }
      else
      {
        pstr(213);
//        cprintf("No");
      }
    }
  }
  return(ck);
}

FILE* ffwd(int sp,FILE* dmp)
// DON'T FORGET TO UPDATE exffwd() IF REQUIRED!
/*
  ffwd() scans the file for the "sp th" marker. If dmp is defined (file
  stream), then input is buffered and written out to dmp.
  If sp is negative, make it positive and perform an initial
  "anti-virus" check.
*/
{
char scr[80*25*2];
short int tx,ty,rrl,rrt,rrb,rrr,rrk,rrf,spp=0,vc=0,spc=0;
int yz,zz,bp;
unsigned long chk=0; // Checksum of executable
FILE* fn;
char buf[BUFSZ+2],ff[DIVLEN+2];
  if (sp<0)  // Anti-Virus Checking?
  {
    sp*=-1;
    vc=1;    // Yep
  }
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
  if ((fn=fopen(inam,"rb"))==NULL)
    error(RDOP);
  bp=0;
  for(zz=0;zz<=DIVLEN;zz++)
    ff[zz]=0;
  sp+=5; // Skip "dummy" occurances of the divider
  spc=5; // End of checksum "dummy" occurances
  while(sp)
  {
    yz=1;
    while(yz && !feof(fn))
    {
      buf[bp]=fgetc(fn);   // Read char
      if (vc && yz) // Checksum until marker found
        chk+=buf[bp];
      for(zz=0;zz<DIVLEN-1;zz++)
        ff[zz]=ff[zz+1];  // Update search buffer
      ff[zz]=buf[bp];
      ff[zz+1]=0;
      yz=!streq(ff,DIV);  // Check search buffer against divider
      if (bp==BUFSZ)      // Buffer full
      {
        if (strlen(ssm))
        {
          cprintf("%c%c",DEL,SPIN[spp]);
          spp++;
          spp%=4;
        }
        if (dmp)
          for(zz=0;zz<=bp;zz++)    // Flush buffer
            fputc(buf[zz],dmp);
        bp=-1;
      }
      bp++;
    }
    if (vc && (spc==1)) // Evaluate Checksum
    {
      for(zz=0;zz<DIVLEN;zz++)
        chk-=ff[zz];  // Backup checksum counter
// DEBUG LINE
// cprintf("Found at:[chk:%lu][CHECK:%lu][@:%ld]-[%d]\r\n",chk,CHECK,ftell(fn),DIVLEN); exit(0);
// DEBUG LINE

// **** WARNING!!! Anti-Virus has stopped working, so it is commented out!
//      if (chk!=CHECK) // Invalid Checksum - Possible Virus!
//        error(CHKS);
//      else // Checksum OK
//      {
// **** WARNING!!! Anti-Virus has stopped working, so it is commented out!
        crwin(20,1,60,3,LIGHTGREEN,GREEN,2,"");
        txc(YELLOW);
        pstr(523);
//        cprintf(" *** Executable Integrity Verified ***");
        txc(tf);
// **** WARNING!!! Anti-Virus has stopped working, so it is commented out!
//      }
// **** WARNING!!! Anti-Virus has stopped working, so it is commented out!
      vc=0; // Stop checksum after first marker is found
    }
    if (yz)
      error(RDSC);
    sp--;
    spc--;
  }
  if (dmp)
    for(zz=0;zz<bp;zz++)  // Flush buffer
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
  crwin(60,1,80,3,tf,tb,2,"");
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
    crwin(3,5,77,20,tf,tb,2,glstr(375));
//    crwin(3,5,77,20,tf,tb,2,"Online Help");
    if (hl)
    {
      strcpy(hf,ins);
      strcat(hf,"\\");
      strcat(hf,SENTRY);
      strcat(hf,glstr(376));
//      strcat(hf,".hlp");
      if ((hlf=fopen(hf,"r"))==NULL)
      {
        cprintf("\r\n\r\n  ");
        pstr(377);
        cprintf("\r\n");
//        cprintf("\r\n\r\n  Error Opening %s Help Information!\r\n",SENTRY);
      }
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
            cprintf("\r\n ");
            pstr(378);
//            cprintf("\r\n Press any key for more help...");
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
    {
      cprintf("\r\n\r\n  ");
      pstr(379);
      cprintf("\r\n  ");
      pstr(381);
      cprintf("\r\n  ");
      pstr(382);
      cprintf("\r\n");
//      cprintf("\r\n\r\n  No help available in this context.\r\n");
    }
    if (x!=ESC)
    {
      cprintf("\r\n");
      pstr(380);
//      cprintf("\r\nPress any key to return...");
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
    sprintf(tol,"%s %s",SENTRY,glstr(322));
//    sprintf(tol,"%s DOS Shell",SENTRY);
    crwin(4,6,70,10,tf,tb,2,tol);
    cprintf("\r\n  ");
    pstr(383);
    cprintf("\r\n");
//    cprintf("\r\n  Cannot enter DOS Shells recursively. (Press a key)\r\n");
    blch();
  }
  else
  {
//    sprintf(tol,"%s %s %s.",glstr(384),SENTRY,glstr(322));
    strcpy(tol,glstr(384));
    strcat(tol," ");
    strcat(tol,SENTRY);
    strcat(tol," ");
    strcat(tol,glstr(322));
    strcat(tol,".");
//    sprintf(tol,"User entered the %s DOS Shell.",SENTRY);
    tolog(tol);
    fclose(logf);
    cprintf("\n\r  ");
    pstr(323);
    cprintf(" %s %s.\n\r",SENTRY,glstr(322));
//    cprintf("\n\r  Type \"EXIT\" to leave the %s DOS Shell.\n\r",SENTRY);
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
    if (!getenvseg(&env_addr))  // Clear SHELL
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"SHELL=");
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  // Set SHELL=ON to avoid recursion
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"SHELL=ON");
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  // Clear PROMPT
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"PROMPT=");
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  // Set PROMPT=[SENTRY] %PROMPT /
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
    sprintf(tol,glstr(388));
//    sprintf(tol,"%s DOS Shell finished.",SENTRY);
    tolog(tol);
/*
    if (!getenvseg(&env_addr))  // Restore PROMPT
      error(NOENV);
    seglen=get_env_var(env_addr,&env_var,&count);
    index=get_env_index(envar,env_var);
    if (index == count)
      env_var[index+1] = (char *)NULL;
    strcpy(value,"PROMPT=");
    strcat(value,lo);
    env_var[index] = value;
    put_env_var(env_addr, seglen, env_var);
    if (!getenvseg(&env_addr))  // Clear SHELL
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
