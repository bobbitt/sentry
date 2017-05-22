head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.25.37;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.44.57;	author MIKE;	state Exp;
branches;
next	3.4;

3.4
date	95.12.29.17.21.47;	author MIKE;	state Exp;
branches;
next	3.3;

3.3
date	95.12.18.18.14.38;	author MIKE;	state Exp;
branches;
next	3.2;

3.2
date	95.12.08.16.31.53;	author MIKE;	state Exp;
branches;
next	3.1;

3.1
date	95.11.30.18.42.11;	author MIKE;	state Exp;
branches;
next	3.0;

3.0
date	95.11.09.16.00.12;	author MIKE;	state Exp;
branches;
next	;


desc
@Install program for Sentry.
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
#include "install.h"
#ifdef __cplusplus
}
#endif

/*
  GLOBAL VARIABLES
*/

FILE *fn,*ini,*npas;
char lo[MAX],temp[192],ssm[MAX],inam[MAX],t2[192],t3[192];
char sd[MAXDRIVE]; /* Start Drive */
char sp[MAXPATH];  /* Start Path */
char id[MAXDRIVE]; /* Install Drive */
char ip[MAXPATH];  /* Install Path */
char msc[80*25*2]; /* Array to hold initial screen */

short int df,bk,_bk=0;
short int sul,max,col,hb,rclf,rctop,rcri,rcbot,rcfrg,rcbak;
short int scrb=300; /* Screen Saver time */
short int wm=2;  /* Windowed Mode on (exploding) */
short int col=1; /* Colour on */
short int tf=15; /* Text Colour */
short int tb=1;  /* Text Background */
short int hf=7;  /* Highlighted Colour */
short int hb=10; /* Highlighted Background */
short int sdel=1; /* Secure Deletion on */
short int un;    /* Install/Uninstall */

struct date td;
struct time nw;
struct text_info sta; /* Startup video attributes */

/*
  FUNCTIONS
*/

void fin(short int ec)
/*
  fin(short int ec) is the function called to cleanly exit from Sentry,
  regardless of where execution currently is. It writes a final entry to
  the log, closes all files, and hides the log and password files.
  fin(short int ec) takes an integer parameter which is passed as the
  exit code on termination.
  fin(short int ec) is always the last function executed in Sentry.
*/
{
  flushall();
  fcloseall();
  crwin(1,1,79,24,WHITE,BLUE,0,"");
  gotoxy(1,24);
  /* Re-set startup video attributes */
/*  if (!puttext(1,1,80,25,msc))
    error(SCWR);*/
  window(sta.winleft,sta.wintop,sta.winright,sta.winbottom);
  textattr(sta.attribute);
  textmode(sta.currmode);
  gotoxy(sta.curx,sta.cury);
  exit(ec);
}

void sfile(void)
/*
  sfile() modifies the system files during the install. It adds a call
  to Sentry to the AUTOEXEC.BAT file. For DOS, it adds a switches
  command to CONFIG.SYS, and removes any break on commands. For Windows
  95, it adds a BootKeys command to the MSDOS.SYS file.
*/
{
  /* Add/Remove call to Sentry to AUTOEXEC.BAT */
  cprintf("\r\nUpdating %s...",AUTO);
  if ((ini=fopen(AUTO,"r"))==NULL)
  {
    if (un)
    {
      cprintf("\r\n");
      cprintf("%s",AUTO);
      cprintf(" not found...\r\n");
    }
    else
    {
      if ((ini=fopen(AUTO,"w"))==NULL)
        error(OPSYS);
      else
      {
        fprintf(ini,"@@%s%s%s\n",id,ip,SENTRY);
        fclose(ini);
      }
    }
  }
  else
  {
    tmpnam(lo);
    strcpy(temp,"c:\\");
    strcat(temp,lo);
    if ((npas=fopen(temp,"w"))==NULL)
      error(CRTMP);
    if (!un)  /* If in install mode add line */
    {
      if (strlen(id))
        fprintf(npas,"@@%s",id);
      else
        fprintf(npas,"@@%s",sd);
      if (ip[0]=='\\')
        fprintf(npas,"%s%s\n",ip,SENTRY);
      else
        fprintf(npas,"%s%s%s\n",sp,ip,SENTRY);
    }
    while((fgets(lo,MAX,ini))!=NULL)
    {
      /* Check to see if old call to Sentry exists */
      strcpy(t2,strlwr(lo));
      if (!(t2[strlen(t2)-8]=='\\' && t2[strlen(t2)-7]=='s' && t2[strlen(t2)-6]=='e' && t2[strlen(t2)-5]=='n' && t2[strlen(t2)-4]=='t' && t2[strlen(t2)-3]=='r' && t2[strlen(t2)-2]=='y'))
        fprintf(npas,"%s",lo);
    }
    fclose(npas);
    fclose(ini);
    sunlink(AUBK);
    rename(AUTO,AUBK);
    rename(temp,AUTO);
  }
  if (Win95())
  {
    /* Add/Remove BootKeys=0 to MSDOS.SYS */
    cprintf("\r\nUpdating %s...",MSDO);
    _rtl_chmod(MSDO,1,-FA_HIDDEN-FA_SYSTEM);
    _rtl_chmod(MSBK,1,-FA_HIDDEN-FA_SYSTEM);
    if ((ini=fopen(MSDO,"r"))==NULL)
      error(OPSYS);
    tmpnam(lo);
    strcpy(temp,"c:\\");
    strcat(temp,lo);
    if ((npas=fopen(temp,"w"))==NULL)
      error(CRTMP);
    while((fgets(lo,MAX,ini))!=NULL)
    {
      /* Check to make sure BootKeys command does not already exist */
      if (strncmp(lo,"BootKeys",8))
        fprintf(npas,"%s",lo);
      if ((!strncmp(lo,"[Options]",9)) && (!un))
        fprintf(npas,"BootKeys=0\n"); /* If in install mode add line */
    }
    fclose(npas);
    fclose(ini);
    sunlink(MSBK);
    rename(MSDO,MSBK);
    rename(temp,MSDO);
    _rtl_chmod(MSDO,1,FA_HIDDEN+FA_SYSTEM);
    _rtl_chmod(MSBK,1,FA_HIDDEN+FA_SYSTEM);
  }
  else
  {
    /* Add switches /n/f to CONFIG.SYS */
    cprintf("\r\nUpdating %s...",CONF);
    if ((ini=fopen(CONF,"r"))==NULL)
    {
      if (un)
      {
        cprintf("\r\n");
        cprintf("%s",CONF);
        cprintf(" not found...\r\n");
      }
      else
      {
        if ((ini=fopen(CONF,"w"))==NULL)
          error(OPSYS);
        else
        {
          fprintf(ini,"switches /n/f\n");
          fclose(ini);
        }
      }
    }
    else
    {
      tmpnam(lo);
      strcpy(temp,"c:\\");
      strcat(temp,lo);
      if ((npas=fopen(temp,"w"))==NULL)
        error(CRTMP);
      if (!un) /* If in install mode add line */
        fprintf(npas,"switches /n/f\n");
      while((fgets(lo,MAX,ini))!=NULL)
      {
        strcpy(t2,strlwr(lo));
        /* Turn all BREAK commands into BREAK=OFF */
        if (!strncmp(t2,"break",5))
          strcpy(lo,"break off\n");
        /* Check to make sure switches command does not already exist */
        if (strncmp(t2,"switches",8))
          fprintf(npas,"%s",lo);
      }
      fclose(npas);
      fclose(ini);
      sunlink(COBK);
      rename(CONF,COBK);
      rename(temp,CONF);
    }
  }
}

void secres(void)
/*
  secres() installs Sentry for Windows 3.x/Windows 95. It copies
  Sentry.grp and Sentry.pif to the Windows directory, and for Windows
  3.x it adds a restrictions section to PROGMAN.INI.
*/
{
short int x;
  if (Win95())
  {
    rename("sentry.pif","sentry.311");
    rename("sentry.w95","sentry.pif");
  }
  /* Get Windows Directory */
  bk=1;
  while (bk)
  {
    bk=0;
    if (un)
       cprintf("\r\n\r\nEnter * to skip the Windows uninstall.");
    strcpy(lo,gin("\r\n\r\nEnter Path to Windows Directory [c:\\Windows]:",1));
    if (!streq(lo,"*") || !un)
    {
      if (strlen(lo)==0)
        strcpy(lo,"c:\\Windows");
      strcpy(temp,lo);
      strcat(temp,"\\nul");
      if ((ini=fopen(temp,"r"))==NULL)
      {
        cprintf("\r\nDirectory does not exist.");
        bk=1;
      }
      fclose(ini);
    }
    else
      cprintf("\r\nSkipped...");
  }
  if (!streq(lo,"*") || !un)
  {
    strlwr(lo);
    fnsplit(lo,id,ip,temp,t2);
    strcat(ip,temp);
    strcat(ip,t2);
    if (streq(lo,"."))
    {
      strcpy(ip,sp);
      strcpy(id,sd);
      chop(ip);
    }
    strcpy(temp,ip);
    strcat(temp,"\\");
    /* Copy/Delete sentry.pif and sentry.grp to/from Windows directory */
    if (!(streq(sp,temp) && streq(sd,id)) || un)
    {
      if (!un)
      {
        strcpy(temp,"copy ");
        strcat(temp,sd);
        strcat(temp,sp);
      }
      else
      {
        strcpy(temp,id);
        strcat(temp,ip);
        strcat(temp,"\\");
      }
      strcat(temp,SENTRY);
      strcat(temp,".");
      strcpy(t2,temp);
      strcat(temp,"pif ");
      strcat(t2,"grp ");
      strcpy(lo,"");
      if (!un)
      {
        strcpy(lo,id);
        strcat(lo,ip);
        strcat(lo,">nul");
        strcat(t2,lo);
        strcat(temp,lo);
        system(temp);
        system(t2);
      }
      else
      {
        if ((ini=fopen(temp,"r"))!=NULL)
           sunlink(temp);
        fclose(ini);
        if ((ini=fopen(t2,"r"))!=NULL)
           sunlink(t2);
        fclose(ini);
      }
    }
    else
      cprintf("\r\n[Current directory - files not copied]");

/***** Install/Uninstall sentry.pif and sentry.grp files to Windows *****/

    /* Add/Remove [Restrictions] to PROGMAN.INI */
    if (!Win95())
    {
      x=1;
      strcpy(t2,id);
      strcat(t2,ip);
      strcat(t2,"\\");
      strcpy(t3,t2);
      strcat(t2,PROG);
      strcat(t3,PRBK);
      cprintf("\r\nUpdating %s...",t2);
      if ((ini=fopen(t2,"r"))==NULL)
      {
        if ((ini=fopen(t2,"w"))==NULL)
          error(OPSYS);
      }
      else
      {
        tmpnam(lo);
        strcpy(temp,id);
        strcat(temp,ip);
        strcat(temp,"\\");
        strcat(temp,lo);
        if ((npas=fopen(temp,"w"))==NULL)
          error(CRTMP);
        while((fgets(lo,MAX,ini))!=NULL)
        {
          /* Remove [Restrictions] section */
          if (lo[0]=='[')
            x=1;
          if (!strncmp(lo,"[Restrictions]",14))
            x=0;
          if (x)
            fprintf(npas,"%s",lo);
        }
        fclose(npas);
        fclose(ini);
        sunlink(t3);
        rename(t2,t3);
        rename(temp,t2);
        if ((ini=fopen(t2,"a"))==NULL)
          error(OPSYS);
      }
      if  (!un)
      {
        fprintf(ini,"\n[Restrictions]\n\n");
        cprintf("\r\n\r\nDo you want to be able to exit Windows? ");
        x=blch();
        if ((x=='y') || (x=='Y'))
        {
        	cprintf("Yes");
          fprintf(ini,"NoClose=0\n");
        }
        else
        {
        	cprintf("No");
          fprintf(ini,"NoClose=1\n");
        }
        cprintf("\r\n\r\nDo you want to be able create, move, copy,");
        cprintf("\r\ndelete or modify groups or icons? ");
        x=blch();
        if ((x=='y') || (x=='Y'))
        {
        	cprintf("Yes");
          fprintf(ini,"EditLevel=0\n");
        }
        else
        {
        	cprintf("No");
          fprintf(ini,"EditLevel=4\n");
        }
        cprintf("\r\n\r\nDo you want to be able to use");
        cprintf("\r\nthe Run command from the File menu? ");
        x=blch();
        if ((x=='y') || (x=='Y'))
        {
        	cprintf("Yes");
          fprintf(ini,"NoRun=0\n");
        }
        else
        {
        	cprintf("No");
          fprintf(ini,"NoRun=1\n");
        }
        cprintf("\r\n\r\nDo you want to be able to toggle Save Settings");
        cprintf("\r\nOn Exit from the Edit menu? ");
        x=blch();
        if ((x=='y') || (x=='Y'))
        {
        	cprintf("Yes");
          fprintf(ini,"NoSave=0\n");
        }
        else
        {
        	cprintf("No");
          fprintf(ini,"NoSave=1\n");
        }
        cprintf("\r\n\r\nDo you want to save changes to the Program");
        cprintf("\r\nManager, groups, icons and windows on exit? ");
        x=blch();
        if ((x=='y') || (x=='Y'))
        {
        	cprintf("Yes");
          fprintf(ini,"NoSaveSettings=0\n");
        }
        else
        {
        	cprintf("No");
          fprintf(ini,"NoSaveSettings=1\n");
        }
      }
      fclose(ini);
    }
  }
}

void main(int argc,char* argv[])
/*
  main() is the main function for install. It starts up, prompts the
  user, takes the appropriate action, and shuts down.
*/
{
struct ffblk ffblk;
char scr[80*25*2];
short int tx,ty,rrl,rrt,rrb,rrr,rrk,rrf,spp=0;
int x,yz,zz,bp;
short int v48=1,v43=1,v37=1,v50=1;
char buf[BUFSZ+2],ff[DIVLEN+2],stg[MAX];
  ctrlbrk(tsk);
  /* Get current video attributes */
  gettextinfo(&sta);
  textmode(C80);
  if (!gettext(1,1,80,25,msc))
    error(SCRD);
  strlwr(argv[0]);
  x=fnsplit(argv[0],sd,sp,lo,temp);
  strcpy(ssm,"Sentry Install / Uninstall");
#if !USER
  shar(0);
#endif
  if ((ini=fopen("license.txt","r"))==NULL)
    error(LICEN);
  else
  {
    crwin(3,3,77,22,WHITE,BLUE,2,"License Agreement");
    x=0;
    while(fgets(temp,MAX,ini)!=NULL)
    {
      if (x>15)
      {
        cprintf("\r\n Press any key for more...");
        x=blch();
        clrscr();
        x=0;
      }
      cprintf("%s\r",temp); /* Read licensing info */
      x++;
    }
    cprintf("\r\n");
  }
  fclose(ini);
  x=0;
  cprintf("\r\nPress 'a' to accept the terms of this agreement, or");
  cprintf("\r\nPress 'x' to refuse. (Refusing Aborts the installation)");
  while ((x!='a') && (x!='A') && (x!='x') && (x!='X'))
    x=blch();
  if ((x=='x') || (x=='X'))
    fin(0);
  if (!puttext(1,1,80,25,msc))
    error(SCWR);
  crwin(3,2,77,7,WHITE,BLUE,2,"");
  textcolor(WHITE);
  cprintf("ÚÄÄÄÄÄÄÄÄÄÄ¿  ");
  textcolor(AUCOL);
  cprintf("NightShade Computing");
  textcolor(RGCOL);
  cprintf("       Registered to");
  textcolor(WHITE);
  cprintf("\r\n³");
  textcolor(TICOL);
  cprintf("%s ",SENTRY);
  cprintf("%s",ver);
  textcolor(WHITE);
  cprintf("³  ");
  textcolor(AUCOL);
  cprintf("Copyright (C) 1996,        ");
  textcolor(RGCOL);
  cprintf("%s",regto);
  textcolor(WHITE );
  cprintf("\r\nÀÄÄÄÄÄÄÄÄÄÄÙ  ");
  textcolor(AUCOL);
  cprintf("Michael A. Bobbitt");
  textcolor(RGCOL);
  cprintf("         Registration #: ");
  cprintf("%lu",regno);
  textcolor(AUCOL);
  cprintf("\r\n              [Mike.Bobbitt@@AcadiaU.CA]");
  crwin(3,9,77,24,WHITE,BLUE,2,"");
  bk=1;
  cprintf("NOTE: Installing or uninstalling %s deletes the INSTALL.EXE file!\r\n",SENTRY);
  cprintf("It is *STRONGLY* advised you make a backup of %s and related\r\n",SENTRY);
  cprintf("files before proceeding any further.\r\n");
  while (bk)
  {
    cprintf("\r\nEnter Path to Install %s (Enter * to Uninstall)\r\n\r\n",SENTRY);
    strcpy(lo,gin("Install Path [c:\\Sentry]:",1));
    un=0;
    if (streq(lo,"*"))
    {
      cprintf("\r\n**** Uninstalling %s ****\r\n",SENTRY);
      un=1;
      cprintf("\r\nUpdating your system files will remove any references to %s,",SENTRY);
      cprintf("\r\nso %s will no longer execute when your computer starts up.\r\n\r\n",SENTRY);
      cprintf("Files to be changed:\r\n * %s\r\n * %s\r\n",AUTO,Win95()?MSDO:CONF);
      cprintf("\r\nDo you wish to update your system files? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
      {
      	cprintf("No");
        sfile();
      }
      else
      	cprintf("No");
      /* Delete all files and remove directory */
      cprintf("\r\n\n\rDo you wish to delete %s from your hard drive? ",SENTRY);
      x=blch();
      if ((x=='y') || (x=='Y'))
      {
        cprintf("Yes");
        strcpy(temp,sd);
        strcat(temp,sp);
        strcat(temp,"\\*.*");
        x=findfirst(temp,&ffblk,0); /* Delete all files */
        while (!x)
        {
          sunlink(ffblk.ff_name);
          x=findnext(&ffblk);
        }
        system("cd \\");
        strcpy(temp,sd);
        strcat(temp,sp);
        chop(temp);
        rmdir(temp);
      }
      else
        cprintf("No");
      secres();
      cprintf("\r\n\r\n%s has been uninstalled.",SENTRY);
      cprintf("\r\n\r\nNOTE: You will have to remove the log file, backup log file,");
      cprintf("\r\n      and message files manually.");
      fin(0);
    }
    if (strlen(lo)==0)
      strcpy(lo,"c:\\Sentry");
    bk=!cpath(1,lo);
  }
  cprintf("\r\nInstalling to %s...",lo);
  x=fnsplit(lo,id,ip,temp,t2);
  strcat(ip,temp);
  strcat(ip,t2);
  if (streq(lo,"."))
  {
    strcpy(ip,sp);
    strcpy(id,sd);
    chop(ip);
  }
  strcpy(temp,ip);
  strcat(temp,"\\");
  strcpy(t2,temp);
  strcat(t2,"sentry.exe");
  if ((ini=fopen(t2,"r"))!=NULL)
  {
    cprintf("\r\n\r\nSentry is currently installed in this directory.");
    cprintf("\r\nDo you wish to overwrite it and continue installing? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
      cprintf("Yes");
    else
    {
      cprintf("No");
      fin(0);
    }
  }
  fclose(ini);
  if (!(streq(sp,temp) && streq(sd,id))) /* Copy files to new directory */
  {
    cprintf("\r\n\r\nCopying files...");
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
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,"copy ");
    strcat(temp,sd);
    strcat(temp,sp);
    strcpy(t2,temp);
    strcpy(t3," ");
    strcat(t3,id);
    strcat(t3,ip);
    strcat(t3,">nul");
    strcpy(temp,t2);
    strcat(temp,"sentry*.*");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
#if USER
    strcpy(temp,t2);
    strcat(temp,"sdel.exe");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
#endif
    strcpy(temp,t2);
    strcat(temp,"readme.com");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,t2);
    strcat(temp,"readme.txt");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,t2);
    strcat(temp,"whatsnew.txt");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,t2);
    strcat(temp,"license.txt");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,t2);
    strcat(temp,"history.txt");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,t2);
    strcat(temp,"qstart.txt");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,t2);
    strcat(temp,"file_id.diz");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
    strcpy(temp,t2);
    strcat(temp,"order.frm");
    strcat(temp,t3);
    system(temp);
    if (strlen(ssm))
    {
      cprintf("%c%c",DEL,SPIN[spp]);
      spp++;
      spp%=4;
    }
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
  else
    cprintf("\r\n[Current directory - files not copied]");
  if (ip[strlen(ip)-1]!='\\')
    strcat(ip,"\\");
  strcpy(inam,id);
  strcat(inam,ip);
  strcat(inam,"Sentry.exe");
  cprintf("\r\n\r\nScanning for %s Initialization Settings...\r\n",SENTRY);
  tmpnam(lo);
  strcpy(temp,id);
  strcat(temp,ip);
  strcat(temp,lo);
  if ((npas=fopen(temp,"wb"))==NULL)
    error(CRTMP);
  if ((fn=fopen(inam,"rb"))==NULL)
    error(RDOP);
  bp=0;
  for(zz=0;zz<=DIVLEN;zz++)
    ff[zz]=0;
  x=1;    // Used for determining something, later on
  argc=5; // Number of search iterations
  while(argc)
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
        for(zz=0;zz<=bp;zz++)
          fputc(buf[zz],npas);
        bp=-1;
      }
      bp++;
    }
    argc--;
  }
  for(zz=0;zz<bp;zz++)
    fputc(buf[zz],npas);
  fclose(fn);
  strcpy(stg,id);
  strcat(stg,ip);
  strcat(stg,"settings.");
  if (_rtl_chmod(stg,0,0)==-1)
  {
    strcpy(stg,sd);
    strcat(stg,sp);
    strcat(stg,"settings.");
  }
  zz=_rtl_chmod(stg,1,-FA_HIDDEN);
  zz=0;
  if ((fn=fopen(stg,"r"))!=NULL)
  {
    fgets(t3,MAX,fn);
    chop(t3);
    if (strcmp(t3,ver)<=0)
    {
      cprintf("\r\nFound Initialization Settings From a Previous Version!\r\n\r\nDo you wish to import them? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
      {
        cprintf("Yes");
        if (yz)
          fputs(DIV,npas);
        fprintf(npas,"%s\r\n",ver);
        x=bp=0;
        while((fgets(t2,MAX,fn))!=NULL)
        {
          x++;
          if ((strcmp(t3,"3.7")<0) && (x==2))    /* Add backup log file name */
          {
            bp++;
            bk=1;
            while (bk)
            {
              strcpy(lo,gin("\r\n\r\nEnter Path for Backup Log file [c:\\Backup.Log]:",1));
              if (strlen(lo)==0)
                strcpy(lo,"c:\\Backup.Log");
              bk=!cpath(0,lo);
            }
          	cprintf("\r\n\r\nPath is %s.",lo);
            fputs(lo,npas);
            fputs("\r\n",npas);
          }
          if ((strcmp(t3,"3.7")<0) && ((x-bp)==6) && (v37))
          {                                 /* Add backup log max size */
            v37=0;
            bp++;
            fputs("20\r\n",npas);
          }
          if ((strcmp(t3,"4.3")<0) && ((x+bp)==37) && (v43))
          {                                   /* Type-ahead and */
            v43=0;                            /* Clear screen */
            bp+=2;
            fputs("1\r\n0\r\n",npas);
          }
          if ((strcmp(t3,"4.8")<0) && ((x+bp)==39) && (v48))
          {                                   /* Last Login Pause */
            v48=0;
            bp++;
            fputs("0\r\n",npas);
          }
          if ((strcmp(t3,"5.0")<0) && ((x+bp)==40) && (v50))
          {                                   /* Secure Deletion */
            v50=0;                            // View Highlighting
            bp+=3;                            // View Highlighting Colour
            fputs("1\r\n1\r\n12\r\n",npas);
          }
          chop(t2);
          fputs(t2,npas);
          fputs("\r\n",npas);
        }
        x=0;
        zz=1;
        fclose(fn);
        sunlink(stg);
        strcpy(stg,sd);
        strcat(stg,sp);
        strcat(stg,"settings.");
        sunlink(stg);
        cprintf("\r\n\r\nSettings Imported.\r\n");
      }
      else
      {
        cprintf("No");
        x=1;
        cprintf("\r\n\r\nSettings not imported.\r\n");
      }
    }
  }
  _rtl_chmod(stg,1,FA_HIDDEN);
  if (x)
  {
    x=0;
    if (yz)
    /* No Initialization settings exist */
    {
      x=1;
      cprintf("\r\nCurrent Version Contains no Initialization Settings...\r\nUsing Defaults...");
      cprintf("\r\n\r\nNOTE: When you log in for the first time, use:\r\n\r\nLogin: %s\r\nPassword: %s\r\n\r\n",SENTRY,SENTRY);
      cprintf("Please note the capitalizations. This account should be\r\nremoved as soon as possible after use.");
      cprintf("\r\n\r\nPress any key to acknowledge...");
      blch();
    }
    else
    /* Initialization settings to be overwritten */
    {
      cprintf("\r\nInitialization Settings Already Exist in Current Version!\r\n\r\nOverwrite with Defaults? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
      {
        cprintf("Yes\r\n\r\nSettings Overwritten.");
        x=2;
      }
      else
      {
        cprintf("No\r\n\r\nSettings not overwritten.\r\n");
        x=0;
      }
    }
    if (x)
    /* Dump new settings */
    {
      bk=1;
      while (bk)
      {
        strcpy(lo,gin("\r\n\r\nEnter Path for Log file [c:\\Sentry.Log]:",1));
        if (strlen(lo)==0)
          strcpy(lo,"c:\\Sentry.Log");
        bk=!cpath(0,lo);
      }
    	cprintf("\r\nPath is %s.",lo);
      if (x!=2)
        fputs(DIV,npas);
      fputs(ver,npas);
      fputs("\r\n",npas);
      fputs(lo,npas);
      fputs("\r\n",npas);
      bk=1;
      while (bk)
      {
        strcpy(lo,gin("\r\n\r\nEnter Path for Backup Log file [c:\\Backup.Log]:",1));
        if (strlen(lo)==0)
          strcpy(lo,"c:\\Backup.Log");
        bk=!cpath(0,lo);
      }
     	cprintf("\r\nPath is %s.",lo);
      fputs(lo,npas);
      fputs("\r\n",npas);
      bk=1;
      while (bk)
      {
        strcpy(lo,gin("\r\n\r\nEnter Path for Message File [c:\\Sentry.Msg]:",1));
        if (strlen(lo)==0)
          strcpy(lo,"c:\\Sentry.Msg");
        bk=!cpath(0,lo);
      }
     	cprintf("\r\nPath is %s.\r\n",lo);
      fputs(lo,npas);
      /* DEFAULT INI SETTINGS HERE */
      fputs("\r\n4\r\n20\r\n3\r\n3\r\n20\r\npasswd\r\n*",npas);
      fputs("\r\n365\r\n0\r\n300\r\nThis is a Secure Terminal.\r\nLogin:\r\n",npas);
      fputs("Password:\r\nInvalid Login.\r\nInvalid Login.\r\nInvalid Login.",npas);
      fputs("\r\nInvalid Login.\r\nUser entered the wrong password.",npas);
      fputs("\r\nUser entered the wrong login.\r\nInvalid Password Length.",npas);
      fputs("\r\nInvalid Login Length.\r\nUSER\r\n1\r\n1\r\n1\r\n0\r\n2",npas);
      fputs("\r\n1\r\n15\r\n1\r\n1\r\n7\r\n10\r\n1\r\n0\r\n0\r\n1\r\n1\r\n12\r\n",npas);
      fputs(DIV,npas);
      fputs("Sentry\r\n",npas);
      fputs(SPAS,npas);
      fputc(STAMP,npas);
      fputs("\r\n0 0 0 0 10 0\r\n",npas);
      fputs(DIV,npas);
    }
  }
  fclose(npas);
  if (zz || x)
  {
  /* Replace Sentry.exe */
    sunlink(inam);
    rename(temp,inam);
  }
  else
  /* Aborted */
    sunlink(temp);
  cprintf("\r\nUpdating your system files will cause %s to execute automatically",SENTRY);
  cprintf("\r\nwhen your computer starts up.\r\n\r\n");
  cprintf("If this is an initial installation of %s, no protection will be\r\n",SENTRY);
  cprintf("available until you update your system files.\r\n\r\n");
  cprintf("Files to be changed:\r\n * %s\r\n * %s\r\n",AUTO,Win95()?MSDO:CONF);
  cprintf("\r\nDo you wish to update your system files? ");
  x=blch();
  if ((x=='y') || (x=='Y'))
  {
    cprintf("Yes");
    sfile();
  }
  else
  {
    cprintf("No\r\n\r\nYour system files have not been updated. If this is an initial\r\n");
    cprintf("installation of %s, no protection will be available until you\r\n",SENTRY);
    cprintf("manually modify your system files, or re-install %s.\r\n\r\n",SENTRY);
    cprintf("Instructions on manually securing your system can be found in\r\n");
    cprintf("section 3.0 of the %s documentation. To access documentation,\r\n",SENTRY);
    cprintf("go to the directory where %s has been installed, and enter\r\n",SENTRY);
    cprintf("\"readme\" (without quotation marks) at the prompt.");
    cprintf("\r\n\r\nPress any key to acknowledge...");
    blch();
  }
  cprintf("\r\n\r\nNOTE: For complete security, you must disable the use of");
  cprintf("\r\nbootdisks on your system. For information on how to perform");
  cprintf("\r\nthis procedure, see section 3.0 of the documentation. To access");
  cprintf("\r\nthe documentation, go to the directory where %s has been",SENTRY);
  cprintf("\r\ninstalled, and enter \"readme\" (without quotation marks) at");
  cprintf("\r\nthe prompt.");
  if (Win95())
    cprintf("\r\n\r\nDo you wish to use %s from within Windows 95? ",SENTRY);
  else
    cprintf("\r\n\r\nDo you wish to use %s with Windows? ",SENTRY);
  x=blch();
  if ((x=='y') || (x=='Y'))
  {
    cprintf("Yes");
    secres();
    cprintf("\r\n\r\n%s has been installed for use with Windows...\r\n",SENTRY);
    cprintf("To finish installing %s with Windows, please read section 6.0\r\n",SENTRY);
    cprintf("of the %s documentation. To access the documentation,\r\n",SENTRY);
    cprintf("go to the directory where %s has been installed, and enter\r\n",SENTRY);
    cprintf("\"readme\" (without quotation marks) at the prompt.\r\n");
  }
  else
  {
    cprintf("No\r\n\r\n%s has not been installed for use with Windows.\r\n\r\n",SENTRY);
    cprintf("Instructions on manually installing %s with Windows can be found\r\n",SENTRY);
    cprintf("in section 6.0 of the %s documentation. To access documentation,\r\n",SENTRY);
    cprintf("go to the directory where %s has been installed, and enter\r\n",SENTRY);
    cprintf("\"readme\" (without quotation marks) at the prompt.\r\n");
  }
  sunlink(argv[0]);
  strcpy(lo,id);
  strcat(lo,ip);
  strcat(lo,"install.exe");
  sunlink(lo);
  cprintf("\r\n\r\nPress any key to exit...");
  blch();
  fin(0);
}
@


4.7
log
@*** empty log message ***
@
text
@d9 1
a9 8
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <errno.h>
#include "common.h"
a14 114
  DEFINES
*/

#define tolog(x)
#define INSTALL

/*
  GLOBAL CONSTANTS
*/

#if !USER
#define SALT  "ZX"
#define SPAS  "Sentry~"
const long int regno=19960210L;
const char regto[20]="Shareware\0";
#endif
#if (USER==1)
#define SALT  "MB"
#define SPAS  "MBp74HGQk7hWE"
const long int regno=63239046L;
const char regto[20]="Michael A. Bobbitt\0";
#endif
#if (USER==2)
#define SALT  "DJ"
#define SPAS  "DJ2BUpmVM4/xU"
const long int regno=99408290L;
const char regto[20]="D.J. Houghton\0";
#endif
#if (USER==3)
#define SALT  "RC"
#define SPAS  "RCN.qL3UlDmIE"
const long int regno=99105327L;
const char regto[20]="Robert D. Coombs\0";
#endif
#if (USER==4)
#define SALT  "BJ"
#define SPAS  "BJG7i6maoJRE6"
const long int regno=99102696L;
const char regto[20]="Bret Jacobsen\0";
#endif
#if (USER==5)
#define SALT  "TH"
#define SPAS  "THUMM5Fi38.b."
const long int regno=99282463L;
const char regto[20]="Todd W. Harris\0";
#endif
#if (USER==6)
#define SALT  "JH"
#define SPAS  "JHeq9EbrDnJZc"
const long int regno=99082382L;
const char regto[20]="Jack Hill\0";
#endif
#if (USER==7)
#define SALT  "TB"
#define SPAS  "TBt5GcmDBdTIM"
const long int regno=99196107L;
const char regto[20]="Trevor Burry\0";
#endif
#if (USER==8)
#define SALT  "KS"
#define SPAS  "KSzw5mvqg3tZ2"
const long int regno=99286109L;
const char regto[20]="Keith Small\0";
#endif
#if (USER==9)
#define SALT  "FS"
#define SPAS  "FSq34W5yzSC0g"
const long int regno=30953671L;
const char regto[33]="First Southern Baptist Church\0";
#endif
#if (USER==10)
#define SALT  "LD"
#define SPAS  "LDFgRR47DRLiU"
const long int regno=99738162L;
const char regto[20]="L.D. Best\0";
#endif
#if (USER==11)
#define SALT  "W1"
#define SPAS  "W1bt9Cp6ks86g"
const long int regno=80962561L;
const char regto[20]="WMAC Lab - 1A\0";
#endif
#if (USER==12)
#define SALT  "W2"
#define SPAS  "W22zJjx1w8WP6"
const long int regno=80962562L;
const char regto[20]="WMAC Lab - 1B\0";
#endif
#if (USER==13)
#define SALT  "W3"
#define SPAS  "W3eLlfs4Umpyw"
const long int regno=80962563L;
const char regto[20]="WMAC Lab - 1C\0";
#endif
#if (USER==14)
#define SALT  "W4"
#define SPAS  "W4hZDKD7yDhfM"
const long int regno=80962654L;
const char regto[20]="WMAC Lab - 2A\0";
#endif
#if (USER==15)
#define SALT  "W5"
#define SPAS  "W5NaiytFlccf6"
const long int regno=80962655L;
const char regto[20]="WMAC Lab - 2B\0";
#endif
#if (USER==16)
#define SALT  "EK"
#define SPAS  "EKT090TtfEJU2"
const long int regno=30967923L;
const char regto[20]="Eric Keyes\0";
#endif

/*
d29 2
a30 2
short int wm=2;  /* Windowed Mode on */
short int col=1; /* Colur on */
d35 1
a42 38
  PROTOTYPE DECLARATIONS
*/

#ifdef __cplusplus
extern "C"
{
#endif
int tsk(void);
void error(int s);
char* gin(char *s,short int ech);
int Win95(void);
char blch(void);
void txb(short int tc);
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor,char *tt);
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor,char *tt);
#if !USER
void shar(int x);
#endif
void sunlink(const char *sul);
void fin(short int ec);
void sfile(void);
void secres(void);
void main();
short int _chmod(const char *filename,short int func,short int attrib);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
#include "common.c"
#ifdef __cplusplus
}
#endif

/*
d61 2
a62 2
  if (!puttext(1,1,80,25,msc))
    error(SCWR);
d71 6
d94 1
a94 1
        fprintf(ini,"@@%s%ssentry\n",id,ip);
d113 1
a113 1
        fprintf(npas,"%ssentry\n",ip);
d115 1
a115 1
        fprintf(npas,"%s%ssentry\n",sp,ip);
d120 2
a121 1
      if (!(lo[strlen(lo)-8]=='\\' && lo[strlen(lo)-7]=='s' && lo[strlen(lo)-6]=='e' && lo[strlen(lo)-5]=='n' && lo[strlen(lo)-4]=='t' && lo[strlen(lo)-3]=='r' && lo[strlen(lo)-2]=='y'))
d134 2
a135 2
    _chmod(MSDO,1,-FA_HIDDEN-FA_SYSTEM);
    _chmod(MSBK,1,-FA_HIDDEN-FA_SYSTEM);
d156 2
a157 2
    _chmod(MSDO,1,FA_HIDDEN+FA_SYSTEM);
    _chmod(MSBK,1,FA_HIDDEN+FA_SYSTEM);
d193 1
d195 1
a195 1
        if (!(strncmp(lo,"break",5) && strncmp(lo,"BREAK",5)))
d198 1
a198 1
        if (strncmp(lo,"switches",8) && strncmp(lo,"SWITCHES",8))
d211 5
d218 5
d250 1
a250 1
    x=fnsplit(lo,id,ip,temp,t2);
d265 1
a266 2
      if (!un)
      {
d276 2
a277 1
      strcat(temp,"sentry.");
d305 1
a305 3
    /*****
    Install/Uninstall sentry.pif and sentry.grp files to Windows
    *****/
d308 1
a308 9
    x=1;
    strcpy(t2,id);
    strcat(t2,ip);
    strcat(t2,"\\");
    strcpy(t3,t2);
    strcat(t2,PROG);
    strcat(t3,PRBK);
    cprintf("\r\nUpdating %s...",t2);
    if ((ini=fopen(t2,"r"))==NULL)
d310 41
a350 13
      if ((ini=fopen(t2,"w"))==NULL)
        error(OPSYS);
    }
    else
    {
      tmpnam(lo);
      strcpy(temp,id);
      strcat(temp,ip);
      strcat(temp,"\\");
      strcat(temp,lo);
      if ((npas=fopen(temp,"w"))==NULL)
        error(CRTMP);
      while((fgets(lo,MAX,ini))!=NULL)
d352 65
a416 7
        /* Remove [Restrictions] section */
        if (lo[0]=='[')
          x=1;
        if (!strncmp(lo,"[Restrictions]",14))
          x=0;
        if (x)
          fprintf(npas,"%s",lo);
a417 1
      fclose(npas);
a418 43
      sunlink(t3);
      rename(t2,t3);
      rename(temp,t2);
      if ((ini=fopen(t2,"a"))==NULL)
        error(OPSYS);
    }
    if (!un)
    {
      fprintf(ini,"\n[Restrictions]\n\n");
      cprintf("\r\n\r\nDo you want to be able to exit Windows? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
        fprintf(ini,"NoClose=0\n");
      else
        fprintf(ini,"NoClose=1\n");
      cprintf("\r\n\r\nDo you want to be able create, move, copy,");
      cprintf("\r\ndelete or modify groups or icons? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
        fprintf(ini,"EditLevel=0\n");
      else
        fprintf(ini,"EditLevel=4\n");
      cprintf("\r\n\r\nDo you want to be able to use");
      cprintf("\r\nthe Run command from the File menu? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
        fprintf(ini,"NoRun=0\n");
      else
        fprintf(ini,"NoRun=1\n");
      cprintf("\r\n\r\nDo you want to be able to toggle Save Settings");
      cprintf("\r\nOn Exit from the Edit menu? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
        fprintf(ini,"NoSave=0\n");
      else
        fprintf(ini,"NoSave=1\n");
      cprintf("\r\n\r\nDo you want to save changes to the Program");
      cprintf("\r\nManager, groups, icons and windows on exit? ");
      x=blch();
      if ((x=='y') || (x=='Y'))
        fprintf(ini,"NoSaveSettings=0\n");
      else
        fprintf(ini,"NoSaveSettings=1\n");
a419 1
    fclose(ini);
d425 2
a426 4
  main() is the starting function in Sentry. It checks the registration
  information, reads in all values from the Sentry.ini file, prints the
  startup information, prompts for the login and password and handles
  any errors that arise from there.
d433 1
a433 1
short int v43,v37;
d462 1
a462 1
      cprintf("%s\r",temp); /* Read help info */
d487 1
a487 1
  cprintf("Sentry ");
d506 2
a507 2
  cprintf("NOTE: Installing or uninstalling Sentry deletes the INSTALL.EXE file!\r\n");
  cprintf("It is *STRONGLY* advised you make a backup of Sentry and related\r\n");
d511 1
a511 1
    cprintf("\r\nEnter Path to Install Sentry (Enter * to Uninstall)\r\n\r\n");
d516 1
a516 1
      cprintf("\r\n**** Uninstalling Sentry ****\r\n");
d518 2
a519 2
      cprintf("\r\nUpdating your system files will remove any references to Sentry,");
      cprintf("\r\nso Sentry will no longer execute when your computer starts up.\r\n\r\n");
d524 2
d527 3
d531 1
a531 1
      cprintf("\r\n\n\rDo you wish to delete Sentry from your hard drive? ");
d535 1
d551 2
d554 1
a554 1
      cprintf("\r\n\r\nSentry has been uninstalled.");
d561 1
a561 54
    strcpy(temp,lo);
    x=_chmod(lo,0,0);
    if (x==-1)
    switch(errno)
    {
      case ENOENT:
        cprintf("\r\nInvalid Path.\r\n");
        strcat(temp,"\\nul");
        bk=1;
        if ((ini=fopen(temp,"r"))==NULL)
        {
          cprintf("\r\nDirectory does not exist. Do you wish to create it? ");
          bp=blch();
          if ((bp=='y') || (bp=='Y'))
          {
            bk=mkdir(lo);
            if (bk)
              cprintf("\r\nInvalid directory.\r\n");
            else
              cprintf("\r\nDirectory created.");
          }
          else
          {
            cprintf("\r\n\r\nDirectory not created - files not copied.\r\n");
            strcpy(lo,sd);
            strcat(lo,sp);
          }
        }
        fclose(ini);
        break;
      case EACCES:
        cprintf("\r\nPermission Denied.\r\n");
        bk=1;
        break;
      default:
        cprintf("\r\nError number: %d\r\n", errno);
        bk=1;
        break;
    }
    else
    {
      if (x & FA_RDONLY)
      {
        cprintf("\r\n%s is read-only.\r\n",lo);
        bk=1;
      }
      if (x & FA_HIDDEN)
        cprintf("\r\nNote: %s is hidden.",lo);
      if (x & FA_SYSTEM)
      {
        cprintf("\r\n%s is a system file.\r\n",lo);
        bk=1;
      }
    }
d563 1
a563 1
  strlwr(lo);
d575 16
d607 1
a607 1
      cprintf(" Please Wait....");
d627 7
d635 3
d644 2
d743 2
a744 1
  strcat(ip,"\\");
d748 1
a748 1
  cprintf("\r\n\r\nScanning for Sentry Initialization Settings...\r\n");
d760 2
a761 2
  argc=2;
  x=1;
d789 7
a795 1
  _chmod(stg,1,-FA_HIDDEN);
d799 3
a801 3
    cprintf("\r\nFound Initialization Settings From a Previous Version!\r\n\r\nDo you wish to import them? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
d803 3
a805 8
      if (yz)
        fputs(DIV,npas);
      fgets(t3,MAX,fn);
      chop(t3);
      fprintf(npas,"%s\r\n",ver);
      v43=v37=1;
      x=bp=0;
      while((fgets(t2,MAX,fn))!=NULL)
d807 6
a812 2
        x++;
        if ((strcmp(t3,"3.7")<0) && (x==2))    /* Add backup log file name */
d814 2
a815 3
          bp++;
          bk=1;
          while (bk)
d817 3
a819 4
            strcpy(lo,gin("\r\n\r\nEnter Path for Backup Log file [c:\\Backup.Log]:",1));
            if (strlen(lo)==0)
              strcpy(lo,"c:\\Backup.Log");
            if ((ini=fopen(lo,"r"))==NULL)
d821 4
a824 7
              fclose(ini);
              if ((ini=fopen(lo,"a"))==NULL)
              {
                cprintf("\r\nPlease enter a valid path.\r\n\r\n");
                bk=1;
              }
              sunlink(lo);
d826 15
a840 1
            fclose(ini);
d842 14
a855 1
          fputs(lo,npas);
d858 16
a873 30
        if ((strcmp(t3,"3.7")<0) && ((x-bp)==6) && (v37))
        {                                 /* Add backup log max size */
          v37=0;
          bp++;
          fputs("20\r\n",npas);
        }
        if ((strcmp(t3,"4.3")<0) && ((x+bp)==37) && (v43))
        {                                   /* Type-ahead and */
          v43=0;                            /* Clear screen */
          bp+=2;
          fputs("1\r\n0\r\n",npas);
        }
        chop(t2);
        fputs(t2,npas);
        fputs("\r\n",npas);
      }
      x=0;
      zz=1;
      fclose(fn);
      sunlink(stg);
      strcpy(stg,sd);
      strcat(stg,sp);
      strcat(stg,"settings.");
      sunlink(stg);
      cprintf("\r\n\r\nSettings Imported.\r\n");
    }
    else
    {
      x=1;
      cprintf("\r\n\r\nSettings not imported.\r\n");
d876 1
a876 1
  _chmod(stg,1,FA_HIDDEN);
d885 1
a885 1
      cprintf("\r\n\r\nNOTE: When you log in for the first time, use:\r\n\r\nLogin: Sentry\r\nPassword: Sentry\r\n\r\n");
d897 1
a897 1
        cprintf("\r\n\r\nSettings Overwritten.");
d902 1
a902 1
        cprintf("\r\n\r\nSettings not overwritten.\r\n");
d915 1
a915 11
        if ((ini=fopen(lo,"r"))==NULL)
        {
          fclose(ini);
          if ((ini=fopen(lo,"a"))==NULL)
          {
            cprintf("\r\nPlease enter a valid path.\r\n\r\n");
            bk=1;
          }
          sunlink(lo);
        }
        fclose(ini);
d917 1
d930 1
a930 11
        if ((ini=fopen(lo,"r"))==NULL)
        {
          fclose(ini);
          if ((ini=fopen(lo,"a"))==NULL)
          {
            cprintf("\r\nPlease enter a valid path.\r\n\r\n");
            bk=1;
          }
          sunlink(lo);
        }
        fclose(ini);
d932 1
d938 1
a938 1
        strcpy(lo,gin("\r\nEnter Path for Message File [c:\\Sentry.Msg]:",1));
d941 1
a941 11
        if ((ini=fopen(lo,"r"))==NULL)
        {
          fclose(ini);
          if ((ini=fopen(lo,"a"))==NULL)
          {
            cprintf("\r\nPlease enter a valid path.\r\n\r\n");
            bk=1;
          }
          sunlink(lo);
        }
        fclose(ini);
d943 1
d945 1
d952 1
a952 1
      fputs("\r\n1\r\n15\r\n1\r\n1\r\n7\r\n10\r\n1\r\n0\r\n",npas);
d971 1
a971 1
  cprintf("\r\nUpdating your system files will cause Sentry to execute automatically");
d973 1
a973 1
  cprintf("If this is an initial installation of Sentry, no protection will be\r\n");
d979 2
d982 1
d985 3
a987 3
    cprintf("\r\n\r\nYour system files have not been updated. If this is an initial\r\n");
    cprintf("installation of Sentry, no protection will be available until you\r\n");
    cprintf("manually modify your system files, or re-install Sentry.\r\n\r\n");
d989 5
a993 3
    cprintf("section 3.0 of the Sentry documentation. To access documentation,\r\n");
    cprintf("go to the directory where Sentry has been installed, and enter\r\n");
    cprintf("\"readme\"(without quotation marks)at the prompt.");
d995 6
d1002 1
a1002 1
    cprintf("\r\n\r\nDo you wish to use Sentry from within Windows 95? ");
d1004 1
a1004 1
    cprintf("\r\n\r\nDo you wish to use Sentry with Windows? ");
d1008 1
d1010 4
a1013 4
    cprintf("\r\n\r\nSentry has been installed for use with Windows...\r\n");
    cprintf("To finish installing Sentry with Windows, please read section 6.0\r\n");
    cprintf("of the Sentry documentation. To access the documentation,\r\n");
    cprintf("go to the directory where Sentry has been installed, and enter\r\n");
d1018 4
a1021 4
    cprintf("\r\n\r\nSentry has not been installed for use with Windows.\r\n\r\n");
    cprintf("Instructions on manually installing Sentry with Windows can be found\r\n");
    cprintf("in section 6.0 of the Sentry documentation. To access documentation,\r\n");
    cprintf("go to the directory where Sentry has been installed, and enter\r\n");
d1030 1
a1030 1
  x=blch();
@


3.8
log
@*** empty log message ***
@
text
@d15 1
a24 8
#define AUTO  "c:\\autoexec.bat"
#define CONF  "c:\\config.sys"
#define MSDO  "c:\\msdos.sys"
#define PROG  "progman.ini"
#define AUBK  "c:\\autoexec.sen"
#define COBK  "c:\\config.sen"
#define MSBK  "c:\\msdos.sen"
#define PRBK  "progman.sen"
d26 1
d35 1
a35 1
const long int regno=19960120L;
d113 1
a113 1
const long int regno=08962563L;
d128 6
d141 6
d150 1
a150 1
short int wm=2; /* Windowed Mode on */
d153 2
a154 2
short int tb=1; /* Text Background */
short int hf=7; /* Highlighted Colour */
d156 2
d160 1
d170 2
a171 1
void error(char *s);
d181 1
d183 2
a190 1

d204 1
a204 1
void error(char *s)
d206 6
a211 4
  error(char *s) handles all fatal errors within Sentry. It prints a
  copy of the message to screen and to the log file and proceeds to lock
  the user out of the computer.
  The parameter s contains the error message.
d214 12
a225 3
  crwin(15,10,strlen(s)+22,14,YELLOW,LIGHTRED,2,"System Error");
  cprintf("\n\r   %s\n\r",s);
  fin(1);
d228 1
a228 1
int Win95(void)
d230 128
a357 5
union REGS regs;
  regs.h.ah=0x33;
  regs.h.al=0x06;
  intdos(&regs,&regs);
  return(((regs.h.bl==7) && (regs.h.bh==0))?1:0);
d360 1
a360 10
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
d362 4
a365 5
  short int x;
  char gi[MAX],ar[MAX];
  bk=0;
  cprintf("%s ",s);
  for(x=0;x<MAX;x++)
d367 19
a385 2
    gi[x]=0;
    ar[x]=0;
d387 1
a387 2
  x=0;
  while (x<(MAX-1))
d389 14
a402 2
    ar[x]=blch();
    if ((ar[x]==27) && _bk)
d404 37
a440 2
      bk=1;
      break;
d442 17
a458 1
    if ((ar[x]==13) || (ar[x]==10))
d460 2
a461 4
      gi[x]=0;
      if ((ar[x]==10) && ech)
        sul=1;
      break;
d465 8
a472 1
      if (!((ar[x]<32) || (ar[x]>125)))
d474 7
a480 18
/**
      Enable code to turn echoing on/off
        if (ech || (pec=='!'))
**/
          cprintf("%c",ar[x]);
/**
        else
          if (pec!='?')
            cprintf("%c",pec);
**/
/**
      Enable code to return only up to max characters.
        if (x<max)
          gi[x]=ar[x];
        else
          gi[x]=0;
**/
        gi[x]=ar[x];
d482 7
a488 2
      else
        x--;
d490 1
a490 1
    if ((ar[x+1]==8) && (x>=0))
d492 35
a526 3
      ar[x+1]=0;
      x--;
      cprintf("%c %c",8,8);
d528 1
a528 1
    x++;
a529 19
  cprintf("\n\r");
  return(gi);
}

void fin(short int ec)
/*
  fin(short int ec) is the function called to cleanly exit from Sentry,
  regardless of where execution currently is. It writes a final entry to
  the log, closes all files, and hides the log and password files.
  fin(short int ec) takes an integer parameter which is passed as the
  exit code on termination.
  fin(short int ec) is always the last function executed in Sentry.
*/
{
  flushall();
  fcloseall();
  crwin(1,1,79,24,WHITE,BLUE,0,"");
  gotoxy(1,24);
  exit(ec);
d540 3
d544 11
a554 2
char buf[BUFSZ+2],ff[DIVLEN+2],id[MAXDRIVE],ip[MAXPATH],sd[MAXDRIVE];
char sp[MAXPATH];
d558 31
a588 3
  strlwr(argv[0]);
  x=fnsplit(argv[0],sd,sp,lo,temp);
  crwin(3,3,77,8,WHITE,BLUE,2,"");
d596 1
a596 1
  cprintf("\n\r³");
d603 1
a603 1
  cprintf("Copyright (C) 1995,        ");
d607 1
a607 1
  cprintf("\n\rÀÄÄÄÄÄÄÄÄÄÄÙ  ");
d614 2
a615 2
  cprintf("\n\r              [Mike.Bobbitt@@AcadiaU.Ca]");
  crwin(3,10,77,21,WHITE,BLUE,2,"");
d617 3
d622 40
a661 1
    strcpy(lo,gin("\n\rEnter Path to Install Sentry [c:\\Sentry]:",1));
d665 39
a703 2
    strcat(temp,"\\nul");
    if ((ini=fopen(temp,"r"))==NULL)
d705 4
a708 9
      cprintf("\n\rDirectory does not exist. Do you wish to create it? ");
      bp=blch();
      if ((bp=='y') || (bp=='Y'))
      {
        bk=mkdir(lo);
        if (bk)
          cprintf("\n\rInvalid directory.");
        else
          cprintf("\n\rDirectory created.");
d710 3
a712 1
      else
d714 2
a715 3
        cprintf("\n\rAborted.");
        strcpy(lo,sd);
        strcat(lo,sp);
a717 1
    fclose(ini);
d731 1
a731 1
  if (!(streq(sp,temp) && streq(sd,id)))
d733 22
d758 88
a845 4
    strcat(temp,"*.* ");
    strcat(temp,id);
    strcat(temp,ip);
    strcat(temp,">nul");
d847 21
d870 1
a870 1
    cprintf("\n\r[Current directory - files not copied]");
d875 1
a875 1
  cprintf("\n\r\n\rScanning for Sentry Initialization Settings...\n\r");
d881 1
a881 1
    error("Error opening temp file!");
d883 1
a883 1
    error("Error Reading Data Segment! [Open]");
d913 4
a916 1
  _chmod("settings.",1,-FA_HIDDEN);
d918 1
a918 1
  if ((fn=fopen("settings.","r"))!=NULL)
d920 1
a920 1
    cprintf("\n\rFound Initialization Settings From a Previous Version!\n\r\n\rDo you wish to import them? ");
a923 1
      cprintf("\n\r\n\rImporting Settings...\n\r");
d928 3
a930 5
      strcpy(t2,t3);
      if (strcmp(t3,"3.7")<0)
        strcpy(t2,ver);
      fprintf(npas,"%s\r\n",t2);
      x=0;
d936 1
d940 1
a940 1
            strcpy(lo,gin("\n\r\n\rEnter Path for Backup Log file [c:\\Backup.Log]:",1));
d948 1
a948 1
                cprintf("\n\rPlease enter a valid path.\n\r\n\r");
d951 1
a951 1
              unlink(lo);
d958 12
a969 2
        if ((strcmp(t3,"3.7")<0) && (x==7))    /* Add backup log max size */
          fputs("100\r\n",npas);
d977 6
a982 1
      unlink("settings.");
d987 1
a987 1
      cprintf("\n\r\n\rAborted.");
d990 1
a990 1
  _chmod("settings.",1,FA_HIDDEN);
d998 5
a1002 1
      cprintf("\n\rCurrent Version Contains no Initialization Settings...\n\rUsing Defaults...");
d1007 1
a1007 1
      cprintf("\n\rInitialization Settings Already Exist in Current Version!\n\r\n\rOverwrite with Defaults? ");
d1011 1
a1011 1
        cprintf("\n\rOverwriting...\n\r");
d1016 1
a1016 1
        cprintf("\n\rAborted.\n\r");
d1026 1
a1026 1
        strcpy(lo,gin("\n\r\n\rEnter Path for Log file [c:\\Sentry.Log]:",1));
d1034 1
a1034 1
            cprintf("\n\rPlease enter a valid path.\n\r\n\r");
d1037 1
a1037 1
          unlink(lo);
d1050 1
a1050 1
        strcpy(lo,gin("\n\r\n\rEnter Path for Backup Log file [c:\\Backup.Log]:",1));
d1058 1
a1058 1
            cprintf("\n\rPlease enter a valid path.\n\r\n\r");
d1061 1
a1061 1
          unlink(lo);
d1070 1
a1070 1
        strcpy(lo,gin("\n\rEnter Path for Message File [c:\\Sentry.Msg]:",1));
d1078 1
a1078 1
            cprintf("\n\rPlease enter a valid path.\n\r\n\r");
d1081 1
a1081 1
          unlink(lo);
d1086 1
a1086 1
      fputs("\r\n4\r\n20\r\n3\r\n3\r\n100\r\npasswd\r\n*",npas);
d1092 1
a1092 1
      fputs("\r\n1\r\n15\r\n1\r\n1\r\n7\r\n10\r\n",npas);
d1105 1
a1105 1
    unlink(inam);
d1110 7
a1116 5
    unlink(temp);
  cprintf("\n\rUpdating your system files will cause Sentry to execute");
  cprintf("\n\rautomatically when your computer starts up.\n\r");
  cprintf("Files to be changed:\n\r * %s\n\r * %s\n\r",AUTO,Win95()?MSDO:CONF);
  cprintf("\n\rDo you wish to update your system files? ");
d1119 2
d1122 7
a1128 91
    /* Add call to Sentry to AUTOEXEC.BAT */
    cprintf("\n\rUpdating %s...",AUTO);
    if ((ini=fopen(AUTO,"r"))==NULL)
      if ((ini=fopen(AUTO,"w"))==NULL)
        error("Error Opening System Files!");
      else
      {
        fprintf(ini,"@@%s%ssentry\n",id,ip);
        fclose(ini);
      }
    else
    {
      tmpnam(lo);
      strcpy(temp,"c:\\");
      strcat(temp,lo);
      if ((npas=fopen(temp,"w"))==NULL)
        error("Error opening temp file!");
      fprintf(npas,"@@%s%ssentry\n",id,ip);
      while((fgets(lo,MAX,ini))!=NULL)
      {
        /* Check to see if old call to Sentry exists */
        if (!(lo[strlen(lo)-8]=='\\' && lo[strlen(lo)-7]=='s' && lo[strlen(lo)-6]=='e' && lo[strlen(lo)-5]=='n' && lo[strlen(lo)-4]=='t' && lo[strlen(lo)-3]=='r' && lo[strlen(lo)-2]=='y'))
          fprintf(npas,"%s",lo);
      }
      fclose(npas);
      fclose(ini);
      unlink(AUBK);
      rename(AUTO,AUBK);
      rename(temp,AUTO);
    }
    if (Win95())
    {
      /* Add BootKeys=0 to MSDOS.SYS */
      cprintf("\n\rUpdating %s...",MSDO);
      _chmod(MSDO,1,-FA_HIDDEN-FA_SYSTEM);
      if ((ini=fopen(MSDO,"r"))==NULL)
        error("Error Opening System Files!");
      tmpnam(lo);
      strcpy(temp,"c:\\");
      strcat(temp,lo);
      if ((npas=fopen(temp,"w"))==NULL)
        error("Error opening temp file!");
      while((fgets(lo,MAX,ini))!=NULL)
      {
        /* Check to make sure BootKeys command does not already exist */
        if (strncmp(lo,"BootKeys",8))
          fprintf(npas,"%s",lo);
      }
      fprintf(npas,"BootKeys=0\n");
      fclose(npas);
      fclose(ini);
      unlink(MSBK);
      rename(MSDO,MSBK);
      rename(temp,MSDO);
      _chmod(MSDO,1,FA_HIDDEN+FA_SYSTEM);
    }
    else
    {
      /* Add switches /n/f to CONFIG.SYS */
      cprintf("\n\rUpdating %s...",CONF);
      if ((ini=fopen(CONF,"r"))==NULL)
        if ((ini=fopen(CONF,"w"))==NULL)
          error("Error Opening System Files!");
        else
        {
          fprintf(ini,"switches /n/f\n");
          fclose(ini);
        }
      else
      {
        tmpnam(lo);
        strcpy(temp,"c:\\");
        strcat(temp,lo);
        if ((npas=fopen(temp,"w"))==NULL)
          error("Error opening temp file!");
        fprintf(npas,"switches /n/f\n");
        while((fgets(lo,MAX,ini))!=NULL)
        {
          /* Check to make sure switches command does not already exist */
          if (!(strncmp(lo,"break",5) && strncmp(lo,"BREAK",5)))
            strcpy(lo,"break off\n");
          if (strncmp(lo,"switches",8) && strncmp(lo,"SWITCHES",8))
            fprintf(npas,"%s",lo);
        }
        fclose(npas);
        fclose(ini);
        unlink(COBK);
        rename(CONF,COBK);
        rename(temp,CONF);
      }
    }
a1129 2
  else
    cprintf("\n\rAborted.");
d1131 1
a1131 1
    cprintf("\n\r\n\rDo you wish to use Sentry from within Windows 95? ");
d1133 1
a1133 1
    cprintf("\n\r\n\rDo you wish to use Sentry with Windows? ");
d1137 6
a1142 132
    cprintf("\n\r\n\rSetting up for use with Windows...");
    /* Get Windows Directory */
    bk=1;
    while (bk)
    {
      bk=0;
      strcpy(lo,gin("\n\r\n\rEnter Path to Windows Directory [c:\\Windows]:",1));
      if (strlen(lo)==0)
        strcpy(lo,"c:\\Windows");
      strcpy(temp,lo);
      strcat(temp,"\\nul");
      if ((ini=fopen(temp,"r"))==NULL)
      {
        cprintf("\n\rDirectory does not exist.");
        bk=1;
      }
      fclose(ini);
    }
    strlwr(lo);
    x=fnsplit(lo,id,ip,temp,t2);
    strcat(ip,temp);
    strcat(ip,t2);
    if (streq(lo,"."))
    {
      strcpy(ip,sp);
      strcpy(id,sd);
      chop(ip);
    }
    strcpy(temp,ip);
    strcat(temp,"\\");
    /* Copy sentry.pif and sentry.grp to Windows directory */
    if (!(streq(sp,temp) && streq(sd,id)))
    {
      strcpy(temp,"copy ");
      strcat(temp,sd);
      strcat(temp,sp);
      strcat(temp,"sentry.");
      strcpy(t2,temp);
      strcat(temp,"pif ");
      strcat(t2,"grp ");
      strcpy(lo,id);
      strcat(lo,ip);
      strcat(lo,">nul");
      strcat(t2,lo);
      strcat(temp,lo);
      system(temp);
      system(t2);
    }
    else
      cprintf("\n\r[Current directory - files not copied]");

    /****
    Install sentry.pif and sentry.grp files
    ****/

    /* Add [Restrictions] to PROGMAN.INI */
    x=1;
    strcpy(t2,id);
    strcat(t2,ip);
    strcat(t2,"\\");
    strcpy(t3,t2);
    strcat(t2,PROG);
    strcat(t3,PRBK);
    cprintf("\n\rUpdating %s...",t2);
    if ((ini=fopen(t2,"r"))==NULL)
    {
      if ((ini=fopen(t2,"w"))==NULL)
        error("Error Opening System Files!");
    }
    else
    {
      tmpnam(lo);
      strcpy(temp,id);
      strcat(temp,ip);
      strcat(temp,"\\");
      strcat(temp,lo);
      if ((npas=fopen(temp,"w"))==NULL)
        error("Error opening temp file!");
      while((fgets(lo,MAX,ini))!=NULL)
      {
        /* Remove [Restrictions] section */
        if (lo[0]=='[')
          x=1;
        if (!strncmp(lo,"[Restrictions]",14))
          x=0;
        if (x)
          fprintf(npas,"%s",lo);
      }
      fclose(npas);
      fclose(ini);
      unlink(t3);
      rename(t2,t3);
      rename(temp,t2);
      if ((ini=fopen(t2,"a"))==NULL)
        error("Error Opening System Files!");
    }
    fprintf(ini,"\n[Restrictions]\n\n");
    cprintf("\n\r\n\rDo you want to be able to exit Windows? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
      fprintf(ini,"NoClose=0\n");
    else
      fprintf(ini,"NoClose=1\n");
    cprintf("\n\r\n\rDo you want to be able create, move, copy,");
    cprintf("\n\rdelete or modify groups or icons? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
      fprintf(ini,"EditLevel=0\n");
    else
      fprintf(ini,"EditLevel=4\n");
    cprintf("\n\r\n\rDo you want to be able to use");
    cprintf("\n\rthe Run command from the File menu? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
      fprintf(ini,"NoRun=0\n");
    else
      fprintf(ini,"NoRun=1\n");
    cprintf("\n\r\n\rDo you want to be able to toggle Save Settings");
    cprintf("\n\rOn Exit from the Edit menu? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
      fprintf(ini,"NoSave=0\n");
    else
      fprintf(ini,"NoSave=1\n");
    cprintf("\n\r\n\rDo you want to save changes to the Program");
    cprintf("\n\rManager, groups, icons and windows on exit? ");
    x=blch();
    if ((x=='y') || (x=='Y'))
      fprintf(ini,"NoSaveSettings=0\n");
    else
      fprintf(ini,"NoSaveSettings=1\n");
    fclose(ini);
d1145 8
a1152 2
    cprintf("\n\rAborted.");
  unlink(argv[0]);
d1156 3
a1158 1
  unlink(lo);
@


3.4
log
@Improved install program.
@
text
@d5 4
d15 4
a23 31
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
  8 = Keith Small
  9 = First Southern Baptist Church
 10 = L.D. Best
*/
#define AUCOL YELLOW /* Text colour used for author info */
#define BUFSZ 8192  /* Size of disk buffer */
#define DFC LIGHTGRAY /* Default text colour */
#define DIV "*NS*\r\n" /* Divider for data segments */
#define DIVLEN 6
#define MAX 90
#define MAXUSER 100
#define MEMCHECK(x)   if ((x) == NULL) error("Out of memory!")
#define PROD 1       /* PROD=0 for testing, PROD=1 for production */
#define RGCOL LIGHTRED /* Text colour used for registration info */
#define SCRWIDTH 78
#define STAMP '~'  /* SuperUser stamp */
#define TICOL LIGHTGREEN  /* Text colour used for title */
#define chop(x) (x)[strlen(x)-1]=0
#define chop2(x) (x)[strlen(x)-2]=0
#define csck(z1,z2) (cs?streq(strupr(z1),strupr(z2)):streq(z1,z2))
#define streq(s1,s2) (!strcmp(s1,s2))
d32 1
d41 1
a41 1
const long int regno=19951105L;
d104 30
a133 2

const char ver[5]="3.4";
d143 7
a149 1
short int scrb=300;
d157 4
d162 1
d165 3
a167 2
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor);
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor);
d169 1
a169 1
void shar(void);
d174 4
d179 8
d200 1
a200 1
  crwin(15,10,strlen(s)+22,14,YELLOW,LIGHTRED,2);
a213 66
char blch(void)
/*
  NO DESCRIPTION
*/
{
  char bin,scr[80*25*2];
  long st,en;
  int tx,ty;
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
      /*
        BLANK SCREEN
      */
      tx=wherex();
      ty=wherey();
      window(1,1,80,25);
      if (!gettext(1,1,80,25,scr))
        error("Internal Screen Error. [Reading]");
      textbackground(BLACK);
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
          textcolor(random(15));
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
      textbackground(rcbak);
      textcolor(rcfrg);
      gotoxy(tx,ty);
      getdate(&td);
      gettime(&nw);
      st=dostounix(&td,&nw)+scrb;
    }
  }
  bin=getch();
  return(bin);
}

a287 130
void crwin(short int lf,short int top,short int ri,short int bot,short int
frg,short int bak,short int bor)
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
  textcolor(frg);
  textbackground(bak);
  if (bor)
  {
    cx=(lf+ri)/2;
    cy=(top+bot)/2;
    if ((ri-lf)>(bot-top))
      mn=(bot-top)/2;
      else
      mn=(ri-lf)/2;
    for(z=1;z<=mn;z++)
    {
      wdr(cx-z*(ri-lf)/(bot-top),cy-z,cx+z*(ri-lf)/(bot-
          top),cy+z,bak,bor);
      clrscr();
      delay(80);
    }
    wdr(lf,top,ri,bot,bak,bor);
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

void wdr(short int lf,short int top,short int ri,short int bot,short int
bak,short int bor)
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
  window(lf,bot+1,ri,bot+1);
  textbackground(BLACK);
  clrscr();
  if (!puttext(lf,bot+1,ri,bot+1,scr))
    error("Internal Screen Error. [Writing]");
  textbackground(bak);
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

#if !USER
void shar(void)
{
  crwin(10,5,67,10,YELLOW,LIGHTRED,2);
  cprintf("\n\r                UNREGISTERED VERSION!!\n\r");
  cprintf("     Please Register if you intend to use Sentry.\n\r");
  sleep(3);
}
#endif

d300 1
a300 1
  crwin(1,1,79,24,WHITE,BLUE,0);
d313 1
a313 1
int x,yz,zz,bp,ni;
d317 1
a317 1
  shar();
d321 1
a321 1
  crwin(3,3,77,8,WHITE,BLUE,2);
d348 2
a349 2
	crwin(3,10,77,21,WHITE,BLUE,2);
	bk=1;
d419 1
a419 1
  ni=2;
d421 1
a421 1
  while(ni)
d440 1
a440 1
    ni--;
d453 1
a453 1
      cprintf("\n\r\n\rImporting Settings...");
d456 8
a463 1
      while((fgets(lo,MAX,fn))!=NULL)
d465 29
a493 2
        chop(lo);
        fprintf(npas,"%s\r\n",lo);
d562 20
d598 1
a598 1
      fputs("\r\n4\r\n20\r\n3\r\n3\r\npasswd\r\n*",npas);
d625 1
d632 28
a659 28
		if ((ini=fopen(AUTO,"r"))==NULL)
			if ((ini=fopen(AUTO,"w"))==NULL)
				error("Error Opening System Files!");
			else
			{
				fprintf(ini,"@@%s%ssentry\n",id,ip);
				fclose(ini);
			}
		else
		{
			tmpnam(lo);
			strcpy(temp,"c:\\");
			strcat(temp,lo);
			if ((npas=fopen(temp,"w"))==NULL)
				error("Error opening temp file!");
			fprintf(npas,"@@%s%ssentry\n",id,ip);
			while((fgets(lo,MAX,ini))!=NULL)
			{
				/* Check to see if old call to Sentry exists */
				if (!(lo[strlen(lo)-8]=='\\' && lo[strlen(lo)-7]=='s' && lo[strlen(lo)-6]=='e' && lo[strlen(lo)-5]=='n' && lo[strlen(lo)-4]=='t' && lo[strlen(lo)-3]=='r' && lo[strlen(lo)-2]=='y'))
					fprintf(npas,"%s",lo);
			}
			fclose(npas);
			fclose(ini);
			unlink(AUBK);
			rename(AUTO,AUBK);
			rename(temp,AUTO);
		}
a661 1
      cprintf("\n\r\n\rMaking changes for Windows 95...");
d674 1
a674 1
				/* Check to make sure BootKeys command does not already exist */
d688 1
a688 1
			/* Add switches /n/f to CONFIG.SYS */
d690 30
a719 30
			if ((ini=fopen(CONF,"r"))==NULL)
				if ((ini=fopen(CONF,"w"))==NULL)
					error("Error Opening System Files!");
				else
				{
					fprintf(ini,"switches /n/f\n");
					fclose(ini);
				}
			else
			{
				tmpnam(lo);
				strcpy(temp,"c:\\");
				strcat(temp,lo);
				if ((npas=fopen(temp,"w"))==NULL)
					error("Error opening temp file!");
				fprintf(npas,"switches /n/f\n");
				while((fgets(lo,MAX,ini))!=NULL)
				{
					/* Check to make sure switches command does not already exist */
					if (!(strncmp(lo,"break",5) && strncmp(lo,"BREAK",5)))
						strcpy(lo,"break off\n");
					if (strncmp(lo,"switches",8) && strncmp(lo,"SWITCHES",8))
						fprintf(npas,"%s",lo);
				}
				fclose(npas);
				fclose(ini);
				unlink(COBK);
				rename(CONF,COBK);
				rename(temp,CONF);
			}
d724 3
a726 3
  x='y';
  if (!Win95())
  {
d728 1
a728 2
    x=blch();
  }
d732 49
a780 49
		/* Get Windows Directory */
		bk=1;
		while (bk)
		{
			bk=0;
			strcpy(lo,gin("\n\r\n\rEnter Path to Windows Directory [c:\\Windows]:",1));
			if (strlen(lo)==0)
				strcpy(lo,"c:\\Windows");
			strcpy(temp,lo);
			strcat(temp,"\\nul");
			if ((ini=fopen(temp,"r"))==NULL)
			{
				cprintf("\n\rDirectory does not exist.");
				bk=1;
			}
			fclose(ini);
		}
		strlwr(lo);
		x=fnsplit(lo,id,ip,temp,t2);
		strcat(ip,temp);
		strcat(ip,t2);
		if (streq(lo,"."))
		{
			strcpy(ip,sp);
			strcpy(id,sd);
			chop(ip);
		}
		strcpy(temp,ip);
		strcat(temp,"\\");
		/* Copy sentry.pif and sentry.grp to Windows directory */
		if (!(streq(sp,temp) && streq(sd,id)))
		{
			strcpy(temp,"copy ");
			strcat(temp,sd);
			strcat(temp,sp);
			strcat(temp,"sentry.");
			strcpy(t2,temp);
			strcat(temp,"pif ");
			strcat(t2,"grp ");
			strcpy(lo,id);
			strcat(lo,ip);
			strcat(lo,">nul");
			strcat(t2,lo);
			strcat(temp,lo);
			system(temp);
			system(t2);
		}
		else
			cprintf("\n\r[Current directory - files not copied]");
d783 1
a783 1
		Install sentry.pif and sentry.grp files
d786 78
a863 78
		/* Add [Restrictions] to PROGMAN.INI */
		x=1;
		strcpy(t2,id);
		strcat(t2,ip);
		strcat(t2,"\\");
		strcpy(t3,t2);
		strcat(t2,PROG);
		strcat(t3,PRBK);
		cprintf("\n\rUpdating %s...",t2);
		if ((ini=fopen(t2,"r"))==NULL)
		{
			if ((ini=fopen(t2,"w"))==NULL)
				error("Error Opening System Files!");
		}
		else
		{
			tmpnam(lo);
			strcpy(temp,id);
			strcat(temp,ip);
			strcat(temp,"\\");
			strcat(temp,lo);
			if ((npas=fopen(temp,"w"))==NULL)
				error("Error opening temp file!");
			while((fgets(lo,MAX,ini))!=NULL)
			{
				/* Remove [Restrictions] section */
				if (lo[0]=='[')
					x=1;
				if (!strncmp(lo,"[Restrictions]",14))
					x=0;
				if (x)
					fprintf(npas,"%s",lo);
			}
			fclose(npas);
			fclose(ini);
			unlink(t3);
			rename(t2,t3);
			rename(temp,t2);
			if ((ini=fopen(t2,"a"))==NULL)
				error("Error Opening System Files!");
		}
		fprintf(ini,"\n[Restrictions]\n\n");
		cprintf("\n\r\n\rDo you want to be able to exit Windows? ");
		x=blch();
		if ((x=='y') || (x=='Y'))
			fprintf(ini,"NoClose=0\n");
		else
			fprintf(ini,"NoClose=1\n");
		cprintf("\n\r\n\rDo you want to be able create, move, copy,");
		cprintf("\n\rdelete or modify groups or icons? ");
		x=blch();
		if ((x=='y') || (x=='Y'))
			fprintf(ini,"EditLevel=0\n");
		else
			fprintf(ini,"EditLevel=4\n");
		cprintf("\n\r\n\rDo you want to be able to use");
		cprintf("\n\rthe Run command from the File menu? ");
		x=blch();
		if ((x=='y') || (x=='Y'))
			fprintf(ini,"NoRun=0\n");
		else
			fprintf(ini,"NoRun=1\n");
		cprintf("\n\r\n\rDo you want to be able to toggle Save Settings");
		cprintf("\n\rOn Exit from the Edit menu? ");
		x=blch();
		if ((x=='y') || (x=='Y'))
			fprintf(ini,"NoSave=0\n");
		else
			fprintf(ini,"NoSave=1\n");
		cprintf("\n\r\n\rDo you want to save changes to the Program");
		cprintf("\n\rManager, groups, icons and windows on exit? ");
		x=blch();
		if ((x=='y') || (x=='Y'))
			fprintf(ini,"NoSaveSettings=0\n");
		else
			fprintf(ini,"NoSaveSettings=1\n");
		fclose(ini);
	}
@


3.3
log
@Protected files, export settings.
@
text
@d9 1
d28 1
d47 8
d120 6
d127 1
a127 1
const char ver[5]="3.3";
d130 1
a130 1
	GLOBAL VARIABLES
d134 4
a137 2
char lo[MAX],temp[192],ssm[MAX],inam[MAX];
short int df,bk,_bk,sul,max,col,hb,rclf,rctop,rcri,rcbot,rcfrg,rcbak,scrb;
d146 1
d148 2
a149 5
char* gstr(void);
void crwin(short int lf,short int top,short int ri,short int bot,short int
frg,short int bak,short int bor);
void wdr(short int lf,short int top,short int ri,short int bot,short int
bak,short int bor);
a165 1

d175 1
a175 1
char* gstr(void)
d177 5
a181 5
  char s[MAX];
  if ((fgets(s,MAX,ini))==NULL)
    error("Error in Initialization Settings!");
  chop2(s);
  return(s);
d203 2
a204 2
              BLANK SCREEN
            */
d233 2
a234 2
              RESTORE SCREEN
            */
d252 7
a258 8
  gin() is the general input routine. It gets input from the keyboard and
  returns it the entered string. If ech is set to 1, the input is echoed
to
  the screen. If ech = 0, the output is echoed as *'s. If the user is
  logging in as a SuperUser, sul is set to 1.
  gin() takes a character pointer (the string to be displayed before inpu
t)
  and an integer (echo) for parameters.
d290 4
a293 1
        if (ech)
d295 7
a301 2
          else
          cprintf("*");
d304 1
a304 1
          else
d306 2
d459 2
a460 2
	fin(short int ec) takes an integer parameter which is passed as the
	exit code on termination.
d479 3
a481 2
int x,yz,zz,bp,sp;
char buf[BUFSZ+2],ff[DIVLEN+2];
d485 3
a487 2
  strcpy(inam,"SENTRY.EXE");
  crwin(4,4,76,19,WHITE,BLUE,2);
d514 64
a577 2
	cprintf("\n\r\n\rScanning for Sentry Initialization Settings...\n\r");
	tmpnam(temp);
d585 3
a587 2
  sp=2;
  while(sp)
d600 2
a601 2
				for(zz=0;zz<=bp;zz++)
					fputc(buf[zz],npas);
d606 1
a606 1
    sp--;
d608 9
a616 9
	for(zz=0;zz<bp;zz++)
		fputc(buf[zz],npas);
	fclose(fn);
	_chmod("settings.",1,-FA_HIDDEN);
	zz=0;
	if ((fn=fopen("settings.","r"))!=NULL)
	{
		cprintf("\n\r\n\rFound Initialization Settings From a Previous Version!\n\r\n\rDo you wish to import them?");
    x=getch();
d618 230
d849 7
a855 3
			if (yz)
				fputs(DIV,npas);
			while((fgets(lo,MAX,fn))!=NULL)
d857 2
a858 2
				chop(lo);
				fprintf(npas,"%s\r\n",lo);
d860 11
a870 4
			x=0;
			zz=1;
			fclose(fn);
			unlink("settings.");
d872 20
d893 16
a908 8
			x=1;
	}
	_chmod("settings.",1,FA_HIDDEN);
	if (x)
	{
		x=0;
		if (yz)
		/* No Initialization settings exist */
d910 2
a911 2
			x=1;
			cprintf("\n\r\n\rCurrent Version Contains no Initialization Settings...\n\rUsing Defaults...");
a913 1
		/* Initialization settings to be overwritten */
d915 8
a922 8
			cprintf("\n\r\n\rInitialization Settings Already Exist in Current Version!\n\r\n\rOverwrite with Defaults?");
			x=getch();
			if ((x=='y') || (x=='Y'))
			{
				cprintf("\n\rOverwriting...\n\r");
				x=2;
			}
			else
d924 7
a930 2
				cprintf("\n\rAborted.\n\r");
				x=0;
d932 7
d940 36
a975 28
		if (x)
	 /* Dump new settings */
		{
			if (x!=2)
				fputs(DIV,npas);
			fputs(ver,npas);
			fputs("\r\nc:\\Sentry.Log\r\nc:\\Sentry.Msg\r\n4\r\n20\r\n3\r\n3\r\npasswd\r\n*",npas);
			fputs("\r\n365\r\n0\r\n300\r\nThis is a Secure Terminal.\r\nLogin:\r\n",npas);
			fputs("Password:\r\nInvalid Login.\r\nInvalid Login.\r\nInvalid Login.",npas);
			fputs("\r\nInvalid Login.\r\nUser entered the wrong password.",npas);
			fputs("\r\nUser entered the wrong login.\r\nInvalid Password Length.",npas);
			fputs("\r\nInvalid Login Length.\r\nUSER\r\n1\r\n1\r\n1\r\n0\r\n2",npas);
			fputs("\r\n1\r\n15\r\n1\r\n1\r\n7\r\n10\r\n",npas);
			fputs(DIV,npas);
			fputs("Sentry\r\n",npas);
			fputs(SPAS,npas);
			fputc(STAMP,npas);
			fputs("\r\n0 0 0 0 10 0\r\n",npas);
			fputs(DIV,npas);
		}
	}
	if (zz || x)
	{
		fclose(npas);
		unlink(inam);
		rename(temp,inam);
		unlink(argv[0]);
		fin(0);
d978 7
a984 6
  /* Cancel */
  {
    fclose(npas);
    unlink(temp);
    fin(1);
  }
@


3.2
log
@Mini-mail system.
@
text
@a60 1
const char regch[12]=".gryKf30pR.";
a66 1
const char regch[12]="NLs7j/3Rn0.";
a72 1
const char regch[12]="UAPkkdmjUyE";
a78 1
const char regch[12]="a.Yr8OmS5E2";
a84 1
const char regch[12]="hQBoAAZTnH.";
a90 1
const char regch[12]="exqeIUsep5c";
a96 1
const char regch[12]="unOXJfBNtDE";
a102 1
const char regch[12]="DKTv9Jw88Lg";
a108 1
const char regch[12]="MAtboxrE1yw";
d111 1
a111 1
const char ver[5]="3.2";
d114 1
a114 1
  GLOBAL VARIABLES
d118 1
a118 1
char ilog[128],temp[192],ssm[MAX],inam[MAX];
a433 1

d435 2
a436 3
  fin(short int ec) takes an integer parameter which is passed as the exi
t
  code on termination.
a441 1
  _chmod(ilog,1,FA_HIDDEN);
d447 1
a447 1
void main()
d455 2
a456 2
  int x,yz,zz,bp,sp;
  char buf[BUFSZ+2],ff[DIVLEN+2];
d488 2
a489 2
  cprintf("\n\r\n\rScanning for Sentry Initialization Settings...\n\r");
  tmpnam(temp);
d511 2
a512 3
        if (npas)
          for(zz=0;zz<=bp;zz++)
            fputc(buf[zz],npas);
d519 8
a526 15
  if (npas)
    for(zz=0;zz<bp;zz++)
      fputc(buf[zz],npas);
  fclose(fn);
  x=0;
  if (yz)
  /* No Initialization settings exist */
  {
    x=1;
    cprintf("\n\r\n\rNo Initialization Settings Found...\n\rUsing Defaults...");
  }
  else
  /* Initialization settings to be overwritten */
  {
    cprintf("\n\r\n\rInitialization Settings Already Exist!\n\r\n\rOVERWRITE?");
d529 60
a588 14
    {
      cprintf("\n\rOverwriting...\n\r");
      x=2;
    }
    else
    {
      cprintf("\n\rAborted.\n\r");
      x=0;
    }
  }
  if (x)
  /* Dump new settings */
  {
    if (x!=2)
d590 10
a599 19
		fputs(ver,npas);
		fputs("\r\nc:\\Sentry.Log\r\nc:\\Sentry.Msg\r\n4\r\n20\r\n3\r\n3\r\npasswd\r\n*",npas);
		fputs("\r\n365\r\n0\r\n300\r\nThis is a Secure Terminal.\r\nLogin:\r\n",npas);
		fputs("Password:\r\nInvalid Login.\r\nInvalid Login.\r\nInvalid Login.",npas);
		fputs("\r\nInvalid Login.\r\nUser entered the wrong password.",npas);
		fputs("\r\nUser entered the wrong login.\r\nInvalid Password Length.",npas);
		fputs("\r\nInvalid Login Length.\r\nUSER\r\n1\r\n1\r\n1\r\n0\r\n2",npas);
		fputs("\r\n1\r\n15\r\n1\r\n1\r\n7\r\n10\r\n",npas);
    fputs(DIV,npas);
    fputs("Sentry\r\n",npas);
    fputs(SPAS,npas);
    fputc(STAMP,npas);
		fputs("\r\n0 0 0 0 10 0\r\n",npas);
    fclose(npas);
    unlink(inam);
    rename(temp,inam);
    unlink("install.exe");
    fin(0);
  }
@


3.1
log
@Password echo char & log DOS shell.
@
text
@a32 1
#define INI 31   /* Number of initialization settings */
d120 1
a120 1
const char ver[5]="3.1";
d565 2
a566 2
		fputs("\r\nc:\\Sentry.Log\r\n4\r\n20\r\n3\r\n3\r\npasswd\r\n*",npas);
		fputs("\r\n365\r\n300\r\nThis is a Secure Terminal.\r\nLogin:\r\n",npas);
d576 1
a576 1
    fputs("\r\n0 0 0 0 10\r\n",npas);
@


3.0
log
@Initial release of install program.
@
text
@d1 591
a591 569
/*
  INCLUDES
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

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
  8 = Keith Small
*/
#define AUCOL YELLOW /* Text colour used for author info */
#define BUFSZ 8192  /* Size of disk buffer */
#define DELIM '~'
#define DFC LIGHTGRAY /* Default text colour */
#define DIV "*NS*\r\n" /* Divider for data segments */
#define DIVLEN 6
#define INI 31   /* Number of initialization settings */
#define MAX 80
#define MAXUSER 100
#define MEMCHECK(x)   if ((x) == NULL) error("Out of memory!")
#define PMAX 8
#define PROD 1       /* PROD=0 for testing, PROD=1 for production */
#define RGCOL LIGHTRED /* Text colour used for registration info */
#define SCRWIDTH 78
#define STAMP '~'  /* SuperUser stamp */
#define TICOL LIGHTGREEN  /* Text colour used for title */
#define chop(x) (x)[strlen(x)-1]=0
#define chop2(x) (x)[strlen(x)-2]=0
#define csck(z1,z2) (cs?streq(strupr(z1),strupr(z2)):streq(z1,z2))
#define streq(s1,s2) (!strcmp(s1,s2))

/*
  GLOBAL CONSTANTS
*/

#if !USER
  #define SALT  "ZX"
  #define SPAS  "Sentry~"
  const long int regno=19951105L;
  const char regto[20]="Shareware\0";
#endif
#if (USER==1)
  #define SALT  "MB"
  #define SPAS  "MBp74HGQk7hWE"
  const long int regno=63239046L;
  const char regto[20]="Michael A. Bobbitt\0";
  const char regch[12]=".gryKf30pR.";
#endif
#if (USER==2)
  #define SALT  "DJ"
  #define SPAS  "DJ2BUpmVM4/xU"
  const long int regno=99408290L;
  const char regto[20]="D.J. Houghton\0";
  const char regch[12]="NLs7j/3Rn0.";
#endif
#if (USER==3)
  #define SALT  "RC"
  #define SPAS  "RCN.qL3UlDmIE"
  const long int regno=99105327L;
  const char regto[20]="Robert D. Coombs\0";
  const char regch[12]="UAPkkdmjUyE";
#endif
#if (USER==4)
  #define SALT  "BJ"
  #define SPAS  "BJG7i6maoJRE6"
  const long int regno=99102696L;
  const char regto[20]="Bret Jacobsen\0";
  const char regch[12]="a.Yr8OmS5E2";
#endif
#if (USER==5)
  #define SALT  "TH"
  #define SPAS  "THUMM5Fi38.b."
  const long int regno=99282463L;
  const char regto[20]="Todd W. Harris\0";
  const char regch[12]="hQBoAAZTnH.";
#endif
#if (USER==6)
  #define SALT  "JH"
  #define SPAS  "JHeq9EbrDnJZc"
  const long int regno=99082382L;
  const char regto[20]="Jack Hill\0";
  const char regch[12]="exqeIUsep5c";
#endif
#if (USER==7)
  #define SALT  "TB"
  #define SPAS  "TBt5GcmDBdTIM"
  const long int regno=99196107L;
  const char regto[20]="Trevor Burry\0";
  const char regch[12]="unOXJfBNtDE";
#endif
#if (USER==8)
  #define SALT  "KS"
  #define SPAS  "KSzw5mvqg3tZ2"
  const long int regno=99286109L;
  const char regto[20]="Keith Small\0";
  const char regch[12]="DKTv9Jw88Lg";
#endif

const char ver[5]="3.0";

/*
  GLOBAL VARIABLES
*/

FILE *fn,*ini,*npas;
char ilog[128],temp[192],ssm[MAX],inam[MAX];
short int df,bk,_bk,sul,max,col,hb,rclf,rctop,rcri,rcbot,rcfrg,rcbak,scrb;
struct date td;
struct time nw;

/*
  PROTOTYPE DECLARATIONS
*/

void error(char *s);
char blch(void);
char* gstr(void);
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor);
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor);
#if !USER
void shar(void);
#endif
void fin(short int ec);
void main();
short int _chmod(const char *filename,short int func,short int attrib);


/*
  FUNCTIONS
*/

void error(char *s)
/*
  error(char *s) handles all fatal errors within Sentry. It prints a
  copy of the message to screen and to the log file and proceeds to lock
  the user out of the computer.
  The parameter s contains the error message.
*/
{
  crwin(15,10,strlen(s)+22,14,YELLOW,LIGHTRED,2);
  cprintf("\n\r   %s\n\r",s);
	fin(1);
}

char* gstr(void)
{
char s[MAX];
  if ((fgets(s,MAX,ini))==NULL)
    error("Error in Initialization Settings!");
  chop2(s);
  return(s);
}

char blch(void)
/*
  NO DESCRIPTION
*/
{
char bin,scr[80*25*2];
long st,en;
int tx,ty;
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
      /*
        BLANK SCREEN
      */
      tx=wherex();
      ty=wherey();
      window(1,1,80,25);
      if (!gettext(1,1,80,25,scr))
        error("Internal Screen Error. [Reading]");
      textbackground(BLACK);
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
          textcolor(random(15));
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
      textbackground(rcbak);
      textcolor(rcfrg);
      gotoxy(tx,ty);
      getdate(&td);
      gettime(&nw);
      st=dostounix(&td,&nw)+scrb;
    }
  }
  bin=getch();
  return(bin);
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
  textcolor(frg);
  textbackground(bak);
  if (bor)
  {
    cx=(lf+ri)/2;
    cy=(top+bot)/2;
    if ((ri-lf)>(bot-top))
      mn=(bot-top)/2;
    else
      mn=(ri-lf)/2;
    for(z=1;z<=mn;z++)
    {
      wdr(cx-z*(ri-lf)/(bot-top),cy-z,cx+z*(ri-lf)/(bot-top),cy+z,bak,bor);
      clrscr();
      delay(120);
    }
    wdr(lf,top,ri,bot,bak,bor);
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

void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor)
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
  window(lf,bot+1,ri,bot+1);
  textbackground(BLACK);
  clrscr();
  if (!puttext(lf,bot+1,ri,bot+1,scr))
    error("Internal Screen Error. [Writing]");
  textbackground(bak);
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

#if !USER
void shar(void)
{
  crwin(10,5,67,10,YELLOW,LIGHTRED,2);
  cprintf("\n\r                UNREGISTERED VERSION!!\n\r");
  cprintf("     Please Register if you intend to use Sentry.\n\r");
  sleep(3);
}
#endif

void fin(short int ec)
/*
  fin(short int ec) is the function called to cleanly exit from Sentry,
  regardless of where execution currently is. It writes a final entry to
  the log, closes all files, and hides the log and password files.
  fin(short int ec) takes an integer parameter which is passed as the exit
  code on termination.
  fin(short int ec) is always the last function executed in Sentry.
*/
{
  flushall();
  fcloseall();
  _chmod(ilog,1,FA_HIDDEN);
  crwin(1,1,79,24,WHITE,BLUE,0);
  gotoxy(1,24);
  exit(ec);
}

void main()
/*
  main() is the starting function in Sentry. It checks the registration
  information, reads in all values from the Sentry.ini file, prints the
  startup information, prompts for the login and password and handles
  any errors that arise from there.
*/
{
int x,yz,zz,bp,sp;
char buf[BUFSZ+2],ff[DIVLEN+2];
#if !USER
	shar();
#endif
  strcpy(inam,"SENTRY.EXE");
  crwin(5,4,75,19,WHITE,BLUE,2);
  textcolor(WHITE);
  cprintf("ÚÄÄÄÄÄÄÄÄÄÄ¿  ");
  textcolor(AUCOL);
  cprintf("Written by");
  textcolor(RGCOL);
  cprintf("                 Registered to");
  textcolor(WHITE);
  cprintf("\n\r³");
  textcolor(TICOL);
  cprintf("Sentry ");
  cprintf("%s",ver);
  textcolor(WHITE);
  cprintf("³  ");
  textcolor(AUCOL);
  cprintf("Michael A. Bobbitt         ");
  textcolor(RGCOL);
  cprintf("%s",regto);
  textcolor(WHITE );
  cprintf("\n\rÀÄÄÄÄÄÄÄÄÄÄÙ  ");
  textcolor(AUCOL);
  cprintf("[Mike.Bobbitt@@AcadiaU.Ca]");
  textcolor(RGCOL);
  cprintf("  Registration #: ");
  cprintf("%lu",regno);
  textcolor(AUCOL);
  cprintf("\n\r              (C) Michael Bobbitt, 1995");
  cprintf("\n\r\n\rScanning for Sentry Initialization Settings...\n\r");
  tmpnam(temp);
  if ((npas=fopen(temp,"wb"))==NULL)
    error("Error opening temp file!");
  if ((fn=fopen(inam,"rb"))==NULL)
    error("Error Reading Data Segment! [Open]");
  bp=0;
  for(zz=0;zz<=DIVLEN;zz++)
    ff[zz]=0;
	sp=2;
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
        if (npas)
          for(zz=0;zz<=bp;zz++)
            fputc(buf[zz],npas);
        bp=-1;
      }
      bp++;
    }
    sp--;
  }
  if (npas)
    for(zz=0;zz<bp;zz++)
      fputc(buf[zz],npas);
	fclose(fn);
  x=0;
	if (yz)
  /* No Initialization settings exist */
  {
    x=1;
    cprintf("\n\r\n\rNo Initialization Settings Found...\n\rUsing Defaults...");
  }
  else
  /* Initialization settings to be overwritten */
  {
    cprintf("\n\r\n\rInitialization Settings Already Exist!\n\r\n\rOVERWRITE?");
    x=getch();
    if ((x=='y') || (x=='Y'))
    {
      cprintf("\n\rOverwriting...\n\r");
      x=2;
    }
    else
    {
      cprintf("\n\rAborted.\n\r");
      x=0;
    }
  }
  if (x)
  /* Dump new settings */
  {
    if (x!=2)
      fputs(DIV,npas);
    fputs("3.0\r\nc:\\Sentry.log\r\n4\r\n20\r\n3\r\n3\r\npasswd\r\n365\r\n300\r\nThis is a Secure Terminal.\r\nLogin:\r\nPassword:\r\nInvalid Login.\r\nInvalid Login.\r\nInvalid Login.\r\nInvalid Login.\r\nUser entered the wrong password.",npas);
    fputs("\r\nUser entered the wrong login.\r\nInvalid Password Length.\r\nInvalid Login Length.\r\nUSER\r\n1\r\n1\r\n1\r\n0\r\n2\r\n1\r\n15\r\n1\r\n1\r\n7\r\n10\r\n",npas);
    fputs(DIV,npas);
    fputs("Sentry\r\n",npas);
    fputs(SPAS,npas);
    fputc(STAMP,npas);
    fputs("\r\n0 0 0 0 10\r\n",npas);
    fclose(npas);
    unlink(inam);
    rename(temp,inam);
    unlink("install.exe");
    fin(0);
  }
  else
  /* Cancel */
  {
    fclose(npas);
    unlink(temp);
    fin(1);
  }
}@

