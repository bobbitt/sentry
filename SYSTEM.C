/*
  INCLUDES
*/
#include "sentry.h"

/*
  GLOBAL CONSTANTS
*/

const char is[INI][58]; /* Listing of all initialization settings */
//      {"Location of the Log File"},
//      {"Location of the Backup Log File"},
//      {"Location of the Message File"},
//      {"Minimum Password Length"},
//      {"Maximum Password Length"},
//      {"Maximum Invalid Tries"},
//      {"Wait Time After an Invalid Login"},
//      {"Max Log File Size"},
//      {"Key to Change Password"},
//      {"Password Echo Character"},
//      {"Days Until Passwords Expire"},
//      {"Days Until Accounts Expire"},
//      {"Screen Saver Activation Time"},
//      {"Screen Saver Message"},
//      {"Login Prompt"},
//      {"Password Prompt"},
//      {"Wrong Password Message"},
//      {"Wrong Login Message"},
//      {"Bad Password Length Message"},
//      {"Bad Login Length Message"},
//      {"Wrong Password Log Message"},
//      {"Wrong Login Log Message"},
//      {"Bad Password Length Log Message"},
//      {"Bad Login Length Log Message"},
//      {"Environment Variable"},
//      {"Enable Sentry with Windows"},
//      {"Show Title"},
//      {"Date Format"},
//      {"Case Sensitivity"},
//      {"Windowed Mode"},
//      {"Enable Colour"},
//      {"Text Colour"},
//      {"Text Background"},
//      {"Highlighted Text Colour"},
//      {"Highlighted Text Background"},
//      {"Maximum Invalid Logins"},
//      {"Type Ahead"},
//      {"Clear Screen"},
//      {"Last Login Pause"},
//      {"Secure Deletion"},
//      {"View Highlighting"},
//      {"View Highlighting Colour"},
//      {"Disable CTRL-C"},
//      {"Password Echo Count"},

/*
  FUNCTIONS
*/

void iset(void)
/*
  iset() is the function that allows the user to change the
  initialization settings.
*/
{
short int x,y,sel=1,tp=0;
char opt=0;
  for (x=0;x<INI;x++)
    strcpy(txt[x+1],is[x]);
  crwin(7,1,65,WIN0+9,tf,tb,2,glstr(156));
//  crwin(7,1,50,WIN0+9,tf,tb,2,"Initialization Settings");
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
      pstr(157);
      cprintf(" ");
//      cprintf("MORE [Page Up ]");
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
      gotoxy(12,WIN0+5);
      pstr(158);
      cprintf(" ");
//      cprintf("MORE [Page Down ] ");
    }
    gotoxy(1,WIN0+7);
    pstr(159);
    cprintf(" ");
//    cprintf("Select a setting or ESC when finished: ");
    opt=blch();
    switch (opt)
    {
    case 13:
      iedit(sel+tp-1);
      crwin(7,1,50,WIN0+9,tf,tb,2,glstr(156));
//      crwin(7,1,50,WIN0+9,tf,tb,2,"Initialization Settings");
      break;
    case 0:
      switch(ext)
      {
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
      }
      break;
    case ESC:
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
char cl[16][15];
//  {"Black"},
//  {"Blue"},
//  {"Green"},
//  {"Cyan"},
//  {"Red"},
//  {"Magenta"},
//  {"Brown"},
//  {"Light Gray"},
//  {"Dark Gray"},
//  {"Light Blue"},
//  {"Light Green"},
//  {"Light Cyan"},
//  {"Light Red"},
//  {"Light Magenta"},
//  {"Yellow"},
//  {"White"}

  for(tv=0;tv<16;tv++) // Load colour text into list
  {
    strcpy(cl[tv],glstr(tv+140));
  }

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
  qu=0; // Check for number by default
  strcpy(tol,ins);
  strcat(tol,glstr(519));
//  strcat(tol,"\\sentry.ins");
  if ((ini=fopen(tol,"r"))==NULL)
  {
    cprintf("\r\n\r\n");
    pstr(160);
//    cprintf("\r\n\r\nNo Information Available.");
  }
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
  switch (set-2)
  {
  case LLOG:
  case LBKL:
  case LMSG:
    qu=1;
    break;
  case SMSG:
  case LOGP:
  case PASP:
  case WPMS:
  case WLMS:
  case BPLM:
  case BLLM:
  case WPLM:
  case WLLM:
  case BPLL:
  case BLLL:
  case ENVV:
    qu=2;
    break;
  case PKEY:
    qu=3;
    break;
  case PECH:
    qu=4;
    break;
  case TEXC:
  case HTXC:
  case VHGC:
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
  case HTXB:
    txc(hf);
  case TEXB:
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
    txc(tf);
    break;
  }
  cprintf("\r\n");
  strcpy(lo,glstr(161));
  strcat(lo," ");
//  strcpy(lo,"Default: ");
  /* Default Values */
  switch (set-2)
  {
  case LLOG:
    strcat(lo,glstr(162));
//    strcat(lo,"c:\\Sentry.Log");
    break;
  case LBKL:
    strcat(lo,glstr(163));
//    strcat(lo,"c:\\Backup.Log");
    break;
  case LMSG:
    strcat(lo,glstr(164));
//    strcat(lo,"c:\\Sentry.Msg");
    break;
  case MINP:
    strcat(lo,"4");
    break;
  case MAXP:
    strcat(lo,"20");
    break;
  case MAXI:
    strcat(lo,"3");
    break;
  case WAIT:
    strcat(lo,"3");
    break;
  case MAXL:
    strcat(lo,"20");
    break;
  case PKEY:
    strcat(lo,glstr(165));
//    strcat(lo,"passwd");
    break;
  case PECH:
    strcat(lo,"*");
    break;
  case PEXP:
    strcat(lo,"365");
    break;
  case AEXP:
    strcat(lo,"365");
    break;
  case SSAT:
    strcat(lo,"300");
    break;
  case SMSG:
    strcat(lo,glstr(168));
//    strcat(lo,"This is a Secure Terminal.");
    break;
  case LOGP:
    strcat(lo,glstr(19));
//    strcat(lo,"Login:");
    break;
  case PASP:
    strcat(lo,glstr(47));
//    strcat(lo,"Password:");
    break;
  case WPMS:
    strcat(lo,glstr(170));
//    strcat(lo,"Invalid Login.");
    break;
  case WLMS:
    strcat(lo,glstr(170));
//    strcat(lo,"Invalid Login.");
    break;
  case BPLM:
    strcat(lo,glstr(170));
//    strcat(lo,"Invalid Login.");
    break;
  case BLLM:
    strcat(lo,glstr(170));
//    strcat(lo,"Invalid Login.");
    break;
  case WPLM:
    strcat(lo,glstr(171));
//    strcat(lo,"User entered the wrong password.");
    break;
  case WLLM:
    strcat(lo,glstr(172));
//    strcat(lo,"User entered the wrong login.");
    break;
  case BPLL:
    strcat(lo,glstr(173));
//    strcat(lo,"Invalid Password Length.");
    break;
  case BLLL:
    strcat(lo,glstr(174));
//    strcat(lo,"Invalid Login Length.");
    break;
  case ENVV:
    strcat(lo,glstr(175));
//    strcat(lo,"USER");
    break;
  case SWIN:
    strcat(lo,"1");
    break;
  case TITL:
    strcat(lo,"1");
    break;
  case DATE:
    strcat(lo,"1");
    break;
  case CASE:
    strcat(lo,"0");
    break;
  case WINM:
    strcat(lo,"2");
    break;
  case COLR:
    strcat(lo,"1");
    break;
  case TEXC:
    strcat(lo,"15");
    break;
  case TEXB:
    strcat(lo,"1");
    break;
  case HTXC:
    strcat(lo,"1");
    break;
  case HTXB:
    strcat(lo,"7");
    break;
  case MXIL:
    strcat(lo,"10");
    break;
  case TYPE:
    strcat(lo,"1");
    break;
  case CLRS:
    strcat(lo,"0");
    break;
  case LLPA:
    strcat(lo,"0");
    break;
  case SDEL:
    strcat(lo,"1");
    break;
  case VHGH:
  	strcat(lo,"1");
    break;
  case VHGC:
    strcat(lo,"12");
    break;
  case CTRL:
    strcat(lo,"1");
    break;
  case PECC:
    strcat(lo,"3");
    break;
  }
  cprintf("%s",lo);
  cprintf("\r\n\r\n");
  pstr(176);
  cprintf(" %s\r\n",cv);
//  cprintf("\r\n\r\nCurrent Value: %s\r\n",cv);
  _bk=1;
  tv=max;
  max=MAX;
  strcpy(cv,gin(glstr(177),1));
//  strcpy(cv,gin("New Value (ENTER Aborts):",1));
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
        cprintf("\r\n");
        pstr(178);
        cprintf("\r\n\r\n");
        pstr(179);
        cprintf("\r\n");
//        cprintf("\r\nPlease enter a numeric value.\r\n\r\nSetting not changed...\r\n");
        bk=blch();
      }
      qu=0;
      break;
    case 1:  /*Path*/
      if (!cpath(0,cv))
      {
        cprintf("\r\n[%s] ",lo);
        pstr(180);
        cprintf("\r\n\r\n");
        pstr(179);
        cprintf("\r\n");
//        cprintf("\r\n[%s] is not a valid path.\r\n\r\nSetting not changed...\r\n",lo);
        bk=blch();
      }
      break;
    case 2:  /*Multiple Word String*/
      break;
    case 3:  /*Single Word*/
      if (strchr(cv,' ')!=NULL)
      {
        cprintf("\r\n");
        pstr(182);
        cprintf("\r\n\r\n");
        pstr(179);
        cprintf("\r\n");
//        cprintf("\r\nPlease enter a single word. (No spaces)\r\n\r\nSetting not changed...\r\n");
        bk=blch();
      }
      break;
    case 4:
      if (strlen(cv)>1)
      {
        cprintf("\r\n");
        pstr(184);
        cprintf("\r\n\r\n");
        pstr(179);
        cprintf("\r\n");
//        cprintf("\r\nPlease enter a single character only.\r\n\r\nSetting not changed...\r\n");
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
      fgets(lo,MAX,ini); /* Read version number */
      fputs(lo,npas);
      fgets(lo,MAX,ini); /* Read extension */
      fputs(lo,npas);
      fgets(lo,MAX,ini); /* Read path to help and .ins files */
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
    switch (set-2)
    {
      case LLOG:
        if (!streq(ilog,cv))
        {
          strcpy(cp,"copy ");
          strcat(cp,ilog);
          strcat(cp," ");
          strcat(cp,cv);
          strcat(cp,">nul");
          fclose(logf);
          system(cp);
          sunlink(ilog);
          strcpy(ilog,cv);
          if ((logf=fopen(ilog,"a"))==NULL)
            error(CRLOG);
        }
        break;
      case LBKL:
        if (!streq(ilbk,cv))
        {
          strcpy(cp,"copy ");
          strcat(cp,ilbk);
          strcat(cp," ");
          strcat(cp,cv);
          strcat(cp,">nul");
          system(cp);
          sunlink(ilbk);
        }
        strcpy(ilbk,cv);
        break;
      case LMSG:
        if (!streq(imsg,cv))
        {
          strcpy(cp,"copy ");
          strcat(cp,imsg);
          strcat(cp," ");
          strcat(cp,cv);
          strcat(cp,">nul");
          system(cp);
          sunlink(imsg);
        }
        strcpy(imsg,cv);
        break;
      case MAXL:
        mlog=atoi(cv);
        break;
      case PECH:
        pec=cv[0];
        break;
      case PEXP:
        pel=atol(cv);
        if (pel)
        {
          pel++;
          pel*=DAY2SEC;
          getdate(&td);
          gettime(&nw);
          pel+=dostounix(&td,&nw);
        }
        break;
      case AEXP:
        ael=atol(cv);
        if (ael)
        {
          ael++;
          ael*=DAY2SEC;
          getdate(&td);
          gettime(&nw);
          ael=dostounix(&td,&nw)-ael;
        }
        break;
      case SSAT:
        scrb=atoi(cv);
        break;
      case SMSG:
        strcpy(ssm,cv);
        break;
      case ENVV:
        strcpy(envar,cv);
        break;
      case DATE:
        df=atoi(cv);
        break;
      case CASE:
        cs=atoi(cv);
        break;
      case WINM:
        wm=atoi(cv);
        break;
      case COLR:
        col=atoi(cv);
        if (!col)
           textmode(BW80);
        break;
      case TEXC:
        tf=atoi(cv);
        break;
      case TEXB:
        tb=atoi(cv);
        break;
      case HTXC:
        hf=atoi(cv);
        break;
      case HTXB:
        hb=atoi(cv);
        break;
      case MXIL:
        ltl=atoi(cv);
        break;
      case LLPA:
        llp=atoi(cv);
        break;
      case SDEL:
        sdel=atoi(cv);
        break;
      case VHGH:
        vwh=atoi(cv);
        break;
      case VHGC:
        vwc=atoi(cv);
        break;
      case CTRL:
        ctrl=atoi(cv);
        break;
      case PECC:
        pecc=atoi(cv);
        break;
    }
    sprintf(tol,"%s %s --> %s",glstr(188),is[set-2],cv);
//    sprintf(tol,"Setting Modified: %s --> %s",is[set-2],cv);
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
  if (!un)
  {
    strcpy(tol,glstr(189));
    x=view(tol);
//    x=view(glstr(189));
//    x=view("Send A Message");
  }
  else
    x=un;
  if (x)
  {
    crwin(2,7,70,12,tf,tb,2,glstr(190));
//    crwin(2,7,70,12,tf,tb,2,"Send Message(s)");
    if (!wm)
      clrscr();
    pass=ffwd(2,NULL);
    bk=0;
    while((fgets(ti,MAX,pass))!=NULL && (!streq(ti,DIV)) && (!bk))
    {
      y++;
      fgets(cp,MAX,pass);
      fgets(cp,MAX,pass);
      if (y==x)
      {
        _bk=1;
        cprintf("\r\n");
        pstr(191);
        strcpy(lp,gin("\r\n>",1));
//        strcpy(lp,gin("\r\nMessage:\r\n>",1));
        if (bk)
          break;
        if ((msg=fopen(imsg,"a"))==NULL)
          error(OPMSG);
        chop2(ti);
        ti[strlen(ti)+1]=0;
        ti[strlen(ti)]='\n';
        fputs(ti,msg);
        sprintf(cp,"%s\n",usr);
        fputs(cp,msg);
        getdate(&td);
        gettime(&nw);
        sprintf(cp,"%lu\n",dostounix(&td,&nw));
        fputs(cp,msg);
        lp[strlen(lp)+1]=0;
        lp[strlen(lp)]='\n';
        fputs(lp,msg);
        chop(ti);
        strcpy(cp,usr);
        strcat(cp," ");
        strcat(cp,glstr(192));
        strcat(cp," ");
//        strcat(cp," sent a message to ");
        strcat(cp,ti);
        strcat(cp,".");
        tolog(cp);
      }
    }
    fclose(pass);
    fclose(msg);
  }
}

int exffwd(int mk)
// Apparently acts like ffwd, except reads from the npas file handle
// (Which can be the file of your choice, not just sentry.exe)
// Returns 0 if a marker is found.
{
char ff[DIVLEN+2];
short int yz,zz;
  for(zz=0;zz<=DIVLEN;zz++)
    ff[zz]=0;
  mk+=5;
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
char cv[100],dr[MAXDRIVE],di[MAXDIR],fi[MAXFILE],ex[MAXEXT],opt,sel,tdr[MAXPATH];
int x,y;
short int td; // Temp Drive
  crwin(2,7,70,17,tf,tb,2,glstr(193));
//  crwin(2,7,70,17,tf,tb,2,"Protect A File");
  if (!wm)
    clrscr();
  cprintf("\r\n\r\n");
  pstr(194);
  cprintf("\r\n");
  pstr(195);

//  cprintf("\r\n\r\nWARNING: Once a file is protected, it can NEVER be undone.");
//  cprintf("\r\nMake sure you backup the file before protecting it,");
//  cprintf("\r\nand test the protected file to ensure it works as planned.");

  cprintf("\r\n\r\n");
  pstr(48);
//  Press any key to continue...
  blch();

  strcpy(cv,browse(1,193)); // Browse for executables, use "Protect A File" title

  y=fnsplit(cv,dr,di,fi,ex);
  strupr(ex);
  if (!streq(ex,".EXE") && !streq(ex,".COM") && !streq(ex,".BAT"))
  {
    cprintf("\r\n");
    pstr(200);
    cprintf("\r\n\r\n");
//    cprintf("\r\nFile must have EXE, COM or BAT extension.\r\n\r\n");
    x=1;
  }
  else
  {
    if ((npas=fopen(cv,"rb"))==NULL)
    {
      cprintf("\r\n");
      pstr(201);
      cprintf("\r\n\r\n");
//      cprintf("\r\nPlease enter a valid path.\r\n\r\n");
      x=1;
    }
    else
    {
      if (!exffwd(1))
      {
        cprintf("\r\n");
        pstr(202);
        cprintf(" %s.\r\n",SENTRY);
//        cprintf("\r\nThis file is already protected by %s.\r\n",SENTRY);
        fclose(npas);
        if ((npas=fopen(cv,"rb"))==NULL)
          error(OPPRF);
        exffwd(1);
        fgets(lo,MAX,npas);
        chop2(lo);
        x=lo[strlen(lo)-1];
        chop(lo);
        fgets(temp,MAX,npas);
        fgets(temp,MAX,npas);
        ze=fgetc(npas);
        fclose(npas);
        if (!USER && (x=='Z'))
        {
          cprintf("\r\n");
          pstr(204);
          cprintf(" %s ",SENTRY);
          pstr(205);
//          cprintf("\r\nShareware versions of %s cannot upgrade files protected",SENTRY);
//          cprintf("\r\nby a registered version.");
          strcpy(lo,"999");
        }
        x=1;
        if (strncmp(lo,ver,3)<1)
        {
          cprintf("\r\n");
          pstr(207);
//          cprintf("\r\nThis file is protected by the current, or an earlier version of");
          cprintf(" %s.",SENTRY);
          cprintf("\r\n\r\n");
          pstr(208);
//          cprintf("\r\nUpgrading reconfigures the initialization settings.  The account");
//          cprintf("\r\nstructure and initialization settings will be copied exactly from");
//          cprintf("\r\nthis version of Sentry being used to upgrade the file.");
          cprintf("\r\n\r\n");
          pstr(209);
//          cprintf("\r\n\r\nIf you choose to upgrade, you will need to modify the");
//          cprintf("\r\ninitialization settings and users to match your desired setup.");
//          cprintf("\r\n\r\nDo you want to upgrade %s? ",cv);
          cprintf("\r\n\r\n");
          pstr(210);
          cprintf(" %s? ",cv);
//          cprintf("\r\n\r\nDo you want to upgrade %s? ",cv);
          x=blch();
          yeah(x)
          {
            pstr(211);
//            cprintf("Yes");
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
            strcat(tol," ");
            strcat(tol,glstr(212));
//            strcat(tol," upgraded to version ");
            strcat(tol,ver);
            strcat(tol,".");
            tolog(tol);
            x=0;
          }
          else
          {
            pstr(213);
//            cprintf("No");
            x=1;
            bk=1;
          }
        }
      }
    }
    fclose(npas);
  }
  if (!bk)
  {
    x=1;  /* No error by default */
    ze=0;
    cprintf("\r\n\r\n");
    pstr(203);
    cprintf(" %s ",cv);
    pstr(214);
//    cprintf("\r\n\r\nIs %s a [W]indows or [D]os based program? ",cv);
    while ((ze!='w') && (ze!='W') && (ze!='d') && (ze!='D') && (ze!=ESC))
      ze=blch();
    if (ze!=ESC)
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
      if ((ze=='w') || (ze=='W'))
      {
        if (Win95()) // Windows 95 Program
        {
          lo[strlen(lo)]='W';  // Windows Program
          lo[strlen(lo)+1]=0;
          x=1; // No Error
        }
        else
        {
          cprintf("\r\n\r\n");
          pstr(215);
//          cprintf("\r\n\r\nCannot protect Windows programs!");
          x=0; // Set error condition
        }
      }
#if !USER
      lo[strlen(lo)]='X';  /* Set X-ray mode - Shareware */
#else
      lo[strlen(lo)]='Z';  /* Set Zulu mode - Registered */
#endif
      fprintf(npas,"%s\r\n",lo); // Mode
      fprintf(npas,"%s\r\n",ex); // Extension
      y=fnsplit(inam,dr,di,fi,ex);
      fprintf(npas,"%s%s\r\n",dr,di); // Location of original Sentry
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
      if (streq(ex,".BAT"))
      {
        strcpy(lo,cv);
        cv[strlen(cv)-1]='E';
        cv[strlen(cv)-2]='X';
        cv[strlen(cv)-3]='E';
        if ((pass=fopen(cv,"r"))!=NULL)
        {
          cprintf("\r\n");
          pstr(216);
//          cprintf("\r\nCreating ");
          cprintf(" %s ",strlwr(cv));
          pstr(217);
          cprintf("\r\n");
//          cprintf(" would overwrite an existing file!\r\n");
  	       cprintf("\r\n");
          pstr(218);
//          cprintf("\r\nIf you still wish to protect this file, you will need to");
//          cprintf("\r\nrename that file so that it will not duplicate the name of");
//          cprintf("\r\nany existing \".exe\" programs in that directory when");
//          cprintf("\r\nprotected.\r\n");
     		cprintf("\r\n\r\n");
         pstr(36);
//          cprintf("\r\nPress any key to return to the SuperUser menu...");
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
        strcpy(tol,glstr(219));
        strcat(tol," ");
//        strcpy(tol,"File Protected: ");
        strcat(tol,cv);
        tolog(tol);
        rename(temp,cv);
      }
      else
      {
        // If there was an error, it's on screen, so wait for the user
        // to acknowledge.
        cprintf("\r\n");
        pstr(48);
        blch();
      }
    }
  }
}

void idmp(void)
{
  crwin(2,7,70,17,tf,tb,2,glstr(220));
//  crwin(2,7,70,17,tf,tb,2,"Export Initialization Settings");
  if (!wm)
    clrscr();
  if (zm)
  {
    cprintf("\r\n");
    pstr(221);
//    cprintf("\r\nCannot dump the Initialization Settings\r\nof a Protected File!");
  }
  else
  {
    if ((npas=fopen("settings.","wb"))==NULL)
      error(CRTMP);
    pass=ffwd(0,NULL);
    fcd(pass,npas);
// Don't hide settings any more    
//    _rtl_chmod("settings.",1,FA_HIDDEN);
    cprintf("\r\n");
    pstr(223);
    cprintf("\r\n");
//    cprintf("\r\nInitialization Settings Exported...\r\n");
    cprintf("\r\n");
    pstr(224);
//    cprintf("\r\nThe next time INSTALL.EXE is run, it will\r\n");
//    cprintf("pick up and use these settings.");
  }
  cprintf("\r\n\r\n");
  pstr(36);
//  cprintf("\r\n\r\nPress any key to return to the SuperUser menu...");
  blch();
}

void iimp(void)
{
char cv[100];
short int x=1;
//  crwin(2,7,70,17,tf,tb,2,"Import Initialization Settings");
  if (!wm)
    clrscr();
  if (zm)
  {
    crwin(2,7,70,17,tf,tb,2,glstr(67));
    cprintf("\r\n");
    pstr(68);
//    cprintf("\r\nCannot import Initialization Settings with a Protected File!");
  }
  else
  {
    strcpy(cv,browse(2,67)); // Browse for executables, use "Protect A File" title
    tmpath(temp);
    crwin(2,7,72,17,tf,tb,2,glstr(67));
    if ((ini=fopen(cv,"rb"))==NULL)
    {
      cprintf("\r\n\r\n");
      pstr(78); // No initialization settings to import!
      x=0;
    }
    if (x)
    {
      if ((npas=fopen(temp,"wb"))==NULL)
        error(CRTMP);
      pass=ffwd(0,npas);
      while(fgets(cp,MAX,ini)!=NULL)
      {
        fputs(cp,npas);
      }

  		fclose(ini);
      fclose(npas);
      fclose(pass);

      sunlink(inam);      /* make the temp file the new main file */
      rename(temp,inam);

      cprintf("\r\n");
      pstr(69);
      cprintf("\r\n");
//    cprintf("\r\nInitialization Settings Imported...\r\n");
      cprintf("\r\n");
      pstr(71);
//    cprintf("\r\nThe next time Sentry is run, it will\r\n");
//    cprintf("pick up and use these settings.");
      cprintf("\r\n\r\n");
      pstr(166); // Sentry must now exit to avoid corruption.
      cprintf("\r\n\r\n");
      pstr(48); // Press any key to continue...
      blch();
      fin(0);
    }
    else
    {
      sunlink(temp);     /* just delete the temp file */
    }
  }

//  unlink("settings."); // Remove Settings File

  cprintf("\r\n\r\n");
  pstr(36);
//  cprintf("\r\n\r\nPress any key to return to the SuperUser menu...");
  blch();
}

void secaud(unsigned long options)
{
short int x,y,c=0;
  crwin(3,3,76,21,tf,tb,2,glstr(226));
//  crwin(3,3,76,21,tf,tb,2,"Security Audit");
  if (!wm)
    clrscr();
  cprintf("\r\n%s",SENTRY);
  pstr(227);
  cprintf("\r\n");
  pstr(228);
//  cprintf("\r\n%s will now perform an audit of your system's security.",SENTRY);
//  cprintf("\r\nYou will be informed of any potential weaknesses, and given");
//  cprintf("\r\nan opportunity to update your settings.");
  y=0;
  cprintf("\r\n\r\n");
  pstr(229);
//  cprintf("\r\n\r\nChecking System Settings...");
/* [System] Check for the following:
 - a call to Sentry in AUTOEXEC.BAT
 - no "switches" line in config.sys
 - no "BootKeys" line in msdos.sys
 - no call to Sentry from the autoexec.bat file
 - a "break on" command in the config.sys file
*/
  if (biton(options,c))
  {
    /* Check for call to Sentry in AUTOEXEC.BAT */
    if ((pass=fopen(AUTO,"r"))==NULL)
    {
      y=1;
      cprintf("\r\n ");
      pstr(231);
//      cprintf("\r\n - Your AUTOEXEC.BAT file does not appear to exist.");
      /* The user will be asked if they want to add a call to Sentry */
      x=0;
    }
    else
    {
      x=0;
      while((fgets(lo,MAX,pass))!=NULL)
      {
        /* Check to see if call to Sentry exists */
        strcpy(lo,strlwr(lo));
        if ((lo[strlen(lo)-8]=='\\' && lo[strlen(lo)-7]=='s' && lo[strlen(lo)-6]=='e' && lo[strlen(lo)-5]=='n' && lo[strlen(lo)-4]=='t' && lo[strlen(lo)-3]=='r' && lo[strlen(lo)-2]=='y'))
           x=1; /* Ok, call exists */
      }
      fclose(pass);
    }
    if (!x)
    {
      y=1;
      cprintf("\r\n ");
      pstr(232);
      cprintf(" %s ",SENTRY);
      pstr(230);
//      cprintf("\r\n - There is no call to %s in your AUTOEXEC.BAT file.",SENTRY);
      /* Now prompt the user, and add such a call */
      cprintf("\r\n   ");
      pstr(233);
      cprintf(" %s ",SENTRY);
      pstr(234);
      cprintf(" ");
//      cprintf("\r\n   Do you wish to add a call to %s to your AUTOEXEC.BAT? ",SENTRY);
      x=blch();
      yeah(x)
      {
        pstr(211);
//        cprintf("Yes");
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
        fprintf(npas,"@%s%s\n",te,SENTRY);
        while((fgets(lo,MAX,pass))!=NULL)
          fprintf(npas,"%s",lo);
        fclose(npas);
        fclose(pass);
        sunlink(AUBK);
        rename(AUTO,AUBK);
        rename(temp,AUTO);
      }
      else
      {
        pstr(213);
//        cprintf("No");
		}
    }
  }
  c++;
  if (biton(options,c))
  {
    if (Win95())
    {
      /* Check for "BootKeys=0" in MSDOS.SYS */
      _rtl_chmod(MSDO,1,-FA_HIDDEN-FA_SYSTEM);
      _rtl_chmod(MSBK,1,-FA_HIDDEN-FA_SYSTEM);
      if ((pass=fopen(MSDO,"r"))==NULL)
      {
        y=1;
        cprintf("\r\n ");
        pstr(236);
//        cprintf("\r\n - Your MSDOS.SYS file does not appear to exist.");
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
        cprintf("\r\n ");
        pstr(238);
//        cprintf("\r\n - There is no \"BootKeys=0\" in your MSDOS.SYS file.");
        /* Prompt the user, and add such a call */
        cprintf("\r\n   ");
        pstr(239);
        cprintf(" ");
//        cprintf("\r\n   Do you wish to add a \"BootKeys=0\" line to your MSDOS.SYS? ");
        x=blch();
        yeah(x)
        {
          pstr(211);
//          cprintf("Yes");
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
        {
          pstr(213);
//          cprintf("No");
        }
      }
      _rtl_chmod(MSDO,1,FA_HIDDEN+FA_SYSTEM);
      _rtl_chmod(MSBK,1,FA_HIDDEN+FA_SYSTEM);
    }
    else
    {
      /* Check for "switches /n/f" in CONFIG.SYS */
      if ((pass=fopen(CONF,"r"))==NULL)
      {
        y=1;
        cprintf("\r\n ");
        pstr(243);
//        cprintf("\r\n - Your CONFIG.SYS file does not appear to exist.");
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
            cprintf("\r\n ");
            pstr(245);
//            cprintf("\r\n - A \"break on\" command exists in your CONFIG.SYS file.");
            /* Now ask the user if they want to remove them */
            cprintf("\r\n   ");
            pstr(246);
            cprintf(" ");
//            cprintf("\r\n   Do you wish to remove it? ");
            y=blch();
            yeah(y)
            {
              pstr(211);
//              cprintf("Yes");
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
            {
              pstr(213);
//              cprintf("No");
            }
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
        cprintf("\r\n ");
        pstr(249);
//        cprintf("\r\n - There is no \"switches /n/f \" in your CONFIG.SYS file.");
        /* Prompt the user, and add such a call */
        cprintf("\r\n   ");
        pstr(250);
        cprintf(" ");
//        cprintf("\r\n   Do you wish to add a \"switches /n/f\" line to your CONFIG.SYS? ");
        x=blch();
        yeah(x)
        {
          pstr(211);
//          cprintf("Yes");
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
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
  }
  if (!y)
    cprintf("OK");
  y=0;
  tmpath(temp);
  if ((npas=fopen(temp,"wb"))==NULL)
    error(CRTMP);
  pass=ffwd(1,npas);
  if (zm)
  {       /* If it's a protected file, read and write the extra info */
    fgets(lo,MAX,pass); /* Read version number */
    fputs(lo,npas);
    fgets(lo,MAX,pass); /* Read extension */
    fputs(lo,npas);
    fgets(lo,MAX,pass); /* Read path to help and .ins files */
    fputs(lo,npas);
  }
  x=0;
  cprintf("\r\n\r\n");
  pstr(252);
//  cprintf("\r\n\r\nChecking Initialization Settings...");
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
 - Secure Deletion is off
*/
  un=-2;
  c++;
  while((fgets(lo,MAX,pass))!=NULL && (!streq(lo,DIV)))
  {
    un++;
    if (biton(options,c))
    {
      if ((un==MINP) && (atoi(lo)<4))
      {
        y=1;
        cprintf("\r\n ");
        pstr(253);
        cprintf(" %d",atoi(lo));
        pstr(251);
//        cprintf("\r\n - Your minimum password length is set to %d, which is low.",atoi(lo));
        cprintf("\r\n   ");
        pstr(254);
        cprintf(" ");
//        cprintf("\r\n   Do you wish to raise it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          cprintf("\r\n\r\n");
          pstr(255);
//          cprintf("\r\n\r\nEnter the new minimum length for passwords");
          strcpy(lo,gin(": ",1));
          strcat(lo,"\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
			}
      }
    }
    if (biton(options,c+1))
    {
      if ((un==MAXP) && (atoi(lo)<10))
      {
        y=1;
        cprintf("\r\n ");
        pstr(256);
        cprintf(" %d",atoi(lo));
        pstr(251);
//        cprintf("\r\n - Your maximum password length is set to %d, which is low.",atoi(lo));
        cprintf("\r\n   ");
        pstr(254);
        cprintf(" ");
//        cprintf("\r\n   Do you wish to raise it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          cprintf("\r\n\r\n");
          pstr(257);
//          cprintf("\r\n\r\nEnter the new maximum length for passwords");
          strcpy(lo,gin(": ",1));
          strcat(lo,"\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+2))
    {
      if ((un==MAXI) && (atoi(lo)>5))
      {
        y=1;
        cprintf("\r\n ");
        pstr(258);
        cprintf(" %d",atoi(lo));
        pstr(259);
//        cprintf("\r\n - Your allowable invalid login attempts is set to %d, which is high.",atoi(lo));
        cprintf("\r\n   ");
        pstr(260);
        cprintf(" ");
//        cprintf("\r\n   Do you wish to lower it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          cprintf("\r\n\r\n");
          pstr(261);
          cprintf(" %s ",SENTRY);
          pstr(262);
//          cprintf("\r\n\r\nEnter the number of invalid login attempts before %s",SENTRY);
//          cprintf("\r\nlocks up");
          strcpy(lo,gin(": ",1));
          strcat(lo,"\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+3))
    {
      if ((un==WAIT) && (atoi(lo)<3))
      {
        y=1;
        cprintf("\r\n ");
        pstr(263);
        cprintf(" %d ",atoi(lo));
        pstr(248);
        pstr(251);
//        cprintf("\r\n - Your invalid login wait delay is set to %d seconds, which is low.",atoi(lo));
        cprintf("\r\n   ");
        pstr(254);
        cprintf(" ");
//        cprintf("\r\n - Do you wish to raise it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          cprintf("\r\n\r\n");
          pstr(265);
//          cprintf("\r\n\r\nEnter the number of seconds to delay when a login");
//          cprintf("\r\nis incorrect");
          strcpy(lo,gin(": ",1));
          strcat(lo,"\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+4))
    {
      if ((un==PECH) && (lo[0]=='!'))
      {
        y=1;
        cprintf("\r\n ");
        pstr(266);
//        cprintf("\r\n - You have passwords echoed directly to the screen!",atoi(lo));
        cprintf("\r\n   ");
        pstr(267);
        cprintf(" ");
//        cprintf("\r\n - Do you wish to echo *'s instead? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          strcpy(lo,"*\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
		  }
      }
    }
    if (biton(options,c+5))
    {
      if ((un==PEXP) && (atoi(lo)>365))
      {
        y=1;
        cprintf("\r\n ");
        pstr(268);
        cprintf(" %d ",atoi(lo));
        pstr(247);
        pstr(259);
//        cprintf("\r\n - Your password expiry is set to %d days, which is high.",atoi(lo));
        cprintf("\r\n   ");
        pstr(260);
        cprintf(" ");
//        cprintf("\r\n   Do you wish to lower it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          cprintf("\r\n\r\n");
          pstr(269);
//          cprintf("\r\n\r\nEnter the number of days new passwords have before");
//          cprintf("\r\nthey expire");
          strcpy(lo,gin(": ",1));
          strcat(lo,"\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
		  }
      }
    }
    if (biton(options,c+6))
    {
      if ((un==AEXP) && (atoi(lo)>365))
      {
        y=1;
        cprintf("\r\n ");
        pstr(270);
        cprintf(" %d ",atoi(lo));
        pstr(247);
        pstr(259);
//        cprintf("\r\n - Your account expiry is set to %d days, which is high.",atoi(lo));
        cprintf("\r\n   ");
        pstr(260);
        cprintf(" ");
//        cprintf("\r\n   Do you wish to lower it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          cprintf("\r\n\r\n");
          pstr(271);
 //         cprintf("\r\n\r\nEnter the number of days unused accounts have before");
//          cprintf("\r\nthey expire");
          strcpy(lo,gin(": ",1));
          strcat(lo,"\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+7))
    {
      if ((un==SSAT) && (atoi(lo)>599))
      {
        y=1;
        cprintf("\r\n ");
        pstr(272);
        cprintf(" %d ",atoi(lo));
        pstr(248);
        pstr(259);
//        cprintf("\r\n - Your screen saver activation time is %d seconds, which is high.",atoi(lo));
        cprintf("\r\n   ");
        pstr(260);
        cprintf(" ");
//        cprintf("\r\n - Do you wish to lower it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
			 pstr(274);
//          cprintf("\r\n\r\nEnter the number of seconds of inactivity that may");
//          cprintf("\r\npass before the screen saver is activated");
          strcpy(lo,gin(": ",1));
          strcat(lo,"\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+8))
    {
      if ((un==CASE) && (atoi(lo)==1))
      {
        y=1;
        cprintf("\r\n ");
        pstr(275);
//        cprintf("\r\n - You have case sensitivity for login names turned off.",atoi(lo));
        cprintf("\r\n   ");
        pstr(276);
        cprintf(" ");
//        cprintf("\r\n - Do you wish to turn it on? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          strcpy(lo,"0\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+9))
    {
      if ((un==SDEL) && (atoi(lo)==0))
      {
        y=1;
        cprintf("\r\n ");
        pstr(277);
//        cprintf("\r\n - You have secure deletion turned off.",atoi(lo));
        cprintf("\r\n   ");
        pstr(276);
        cprintf(" ");
//        cprintf("\r\n - Do you wish to turn it on? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          strcpy(lo,"1\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+10))
    {
      if ((un==CTRL) && (atoi(lo)==0))
      {
        y=1;
        cprintf("\r\n ");
        pstr(278);
//        cprintf("\r\n - CTRL-C is currently enabled.",atoi(lo));
        cprintf("\r\n   ");
        pstr(279);
        cprintf(" ");
//        cprintf("\r\n - Do you wish to disable it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          strcpy(lo,"1\r\n");
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    fputs(lo,npas);
  }
  fputs(DIV,npas);
  if (!y)
    cprintf("OK");
  y=0;
  cprintf("\r\n\r\n");
  pstr(280);
//  cprintf("\r\n\r\nChecking Account Structure...");
/*
 [Accounts] Check for the following:
 - accounts that have expired (should be deleted)
 - SuperUser accounts with a max inv log setting
 - Normal accounts with no max inv log setting
 - # of failed login attempts is exceeded
 - accounts with no expiry date
 - passwords with no expiry date
*/
  c+=11;
  while(guser(1))
  {
    /* Perform user security audit */
    getdate(&td);
    gettime(&nw);
    sul=0;
    if (biton(options,c))
    {
      if ((ed) && (ed<dostounix(&td,&nw)))
      {
        y=1;
        cprintf("\r\n\r\n ");
        pstr(281);
        cprintf(" ");
//        cprintf("\r\n\r\n User: ");
        cprintf("%s",lo);
        cprintf("\r\n");
        pstr(57);
//        cprintf("\r\nThis account has expired.");
        cprintf("\r\n ");
        pstr(283);
        cprintf(" ");
//        cprintf("\r\n Do you wish to delete it? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          x=1;
          sul=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (biton(options,c+1))
    {
      if ((fla>ntl) && (!sul))
      {  /* # of failed login attempts exceeds allowable limit */
        y=1;
        cprintf("\r\n\r\n ");
        pstr(281);
        cprintf(" ");
//        cprintf("\r\n\r\n User: ");
        cprintf("%s",lo);
        cprintf("\r\n");
        pstr(284);
        cprintf("\r\n");
        pstr(285);
        cprintf("\r\n");
        pstr(286);
        cprintf(" ");
//        cprintf("\r\nHas has exceeded his allowable maximum invalid login limit.");
//        cprintf("\r\nThis account may have been the target of an attack.");
//        cprintf("\r\n Do you wish to delete this account? ");
        maxtry=blch();
        yeah(maxtry)
        {
          pstr(211);
//          cprintf("Yes");
          x=1;
          sul=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
        }
      }
    }
    if (!sul)
    {
      su=((ps[strlen(ps)-3]==STAMP)?1:0);
      if (biton(options,c+2))
      {
        if (su && ntl)
        { /* SuperUser accounts with a max inv log setting */
          y=1;
          cprintf("\r\n\r\n ");
          pstr(281);
          cprintf(" ");
//          cprintf("\r\n\r\n User: ");
          cprintf("%s",lo);
          cprintf("\r\n");
          pstr(287);
          cprintf("\r\n");
          pstr(288);
          cprintf("\r\n");
          pstr(289);
          cprintf(" ");
//          cprintf("\r\nIs a SuperUser with a maximum invalid login setting.");
//          cprintf("\r\nThis means if this account is repeatedly attacked, the");
//          cprintf("\r\nSuperUser could be locked out!");
//          cprintf("\r\n Do you wish to remove the maximum invalid login setting? ");
          maxtry=blch();
          yeah(maxtry)
          {
            pstr(211);
//            cprintf("Yes");
            ntl=0;
            x=1;
          }
          else
          {
            pstr(213);
//            cprintf("No");
          }
        }
      }
      if (biton(options,c+3))
      {
        if (!su && !ntl)
        {  /* Normal accounts with no max inv log setting */
          y=1;
          cprintf("\r\n\r\n ");
          pstr(281);
          cprintf(" ");
//          cprintf("\r\n\r\n User: ");
          cprintf("%s",lo);
          cprintf("\r\n");
          pstr(290);
          cprintf("\r\n");
          pstr(291);
          cprintf("\r\n");
          pstr(292);
          cprintf(" ");
//          cprintf("\r\nHas no maximum invalid login setting.");
//          cprintf("\r\nThis means if this account can be repeatedly attacked");
//          cprintf("\r\nwithout being locked out!");
//          cprintf("\r\n Do you wish to add a maximum invalid login setting? ");
          maxtry=blch();
          yeah(maxtry)
          {
            pstr(211);
//            cprintf("Yes");
            ntl=100;
            while ((ntl>99) || (ntl<0))
            {
              cprintf("\r\n\r\n");
              pstr(26);
              cprintf(" [%d].",ltl);
//              cprintf("\r\n\r\nEnter the number of sequential invalid logins before the");
//              cprintf("\r\nuser's account is automatically locked up, up to a maximum of 99.");
//              cprintf("\r\nEnter selects the default [%d].",ltl);
              cprintf("\r\n");
              strcpy(na,gin(">",1));
              ntl=atoi(na);
              if (!strlen(na))
                ntl=ltl;
            }
            x=1;
          }
          else
          {
            pstr(213);
//            cprintf("No");
          }
        }
      }
      if (biton(options,c+4))
      {
        if (ed==0)
        {  /* Account has no expiry date */
          y=1;
          cprintf("\r\n\r\n ");
          pstr(281);
          cprintf(" ");
//          cprintf("\r\n\r\n User: ");
          cprintf("%s",lo);
          cprintf("\r\n");
          pstr(295);
          cprintf("\r\n");
          pstr(296);
          cprintf(" ");
//          cprintf("\r\nHas no expiry date on their account.");
//          cprintf("\r\n Do you wish to add an expiry date? ");
          maxtry=blch();
          yeah(maxtry)
          {
            pstr(211);
//            cprintf("Yes");
            ed=gdate();
            x=1;
          }
          else
          {
            pstr(213);
//            cprintf("No");
          }
        }
      }
      if (biton(options,c+5))
      {
        if (pe==0)
        {  /* Password has no expiry date */
          y=1;
          cprintf("\r\n\r\n ");
          pstr(281);
          cprintf(" ");
//          cprintf("\r\n\r\n User: ");
          cprintf("%s",lo);
          cprintf("\r\n");
          pstr(297);
          cprintf("\r\n");
          pstr(296);
          cprintf(" ");
//          cprintf("\r\nHas no expiry date on their password.");
//          cprintf("\r\n Do you wish to add an expiry date? ");
          maxtry=blch();
          yeah(maxtry)
          {
            pstr(211);
//            cprintf("Yes");
            pe=gdate();
            x=1;
          }
          else
          {
            pstr(213);
//            cprintf("No");
          }
        }
      }
      fputs(lo,npas);
      fputs(ps,npas);
      pwr;
    }
  }
  c+=6;
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
  cprintf("\r\n\r\n ");
  pstr(298);
//  cprintf("\r\n\r\n Audit Complete. Press a key...");
  strcpy(tol,glstr(299));
//  strcpy(tol,"Security Audit Performed.");
  tolog(tol);
  su=sul=1;
  blch();
}

void mshell(void)
{
const int SRCHLEN=3;
const char SRCH[4]="DIR";
char dr[MAXDRIVE],di[MAXDIR],fi[MAXFILE],ex[MAXEXT];
char ff[DIVLEN+2],opt,sel=1;
short int x,y,spp=0;
int yz,zz,msmax;
long loc[MAXUSER],yzl,zzl;
  crwin(2,7,70,20,tf,tb,2,glstr(300));
//  crwin(2,7,70,20,tf,tb,2,"Modify Shell Commands");
  if (!wm)
    clrscr();
  x=1;
  bk=0;
  pstr(301);
//  cprintf("WARNING: This procedure can cause your system to crash under");
//  cprintf("\r\ncertain circumstances! It modifies your command interpreter,");
//  cprintf("\r\nwhich may cause problems with certain configurations.");
  cprintf("\r\n");
  pstr(302);
//  cprintf("\r\nMAKE A BOOTDISK BEFORE ATTEMPTING THIS PROCEDURE!");
  while (x && !bk)
  {
    _bk=1;
    strcpy(lo,"\r\n\r\n");
    strcat(lo,glstr(303));
    strcat(lo,"\r\n[");
//    strcpy(lo,"\r\n\r\nEnter the path to your COMMAND.COM\r\n[");
    strcpy(pa,strlwr(getenv("COMSPEC")));
    strcat(lo,pa);
    strcat(lo,"]:");
    strcpy(na,gin(lo,1));
    if (!strlen(na))
      strcpy(na,pa);
    y=fnsplit(na,dr,di,fi,ex); // Check to see it's really a .com file
    strupr(ex);
    if (!streq(ex,".COM"))
    {
      cprintf("\r\n");
      pstr(304);
      cprintf("\r\n\r\n");
//      cprintf("\r\nFile must have a .COM extension.\r\n\r\n");
      x=1;
    }
    else
    {
      x=!cpath(0,na);
      if ((pass=fopen(na,"rb"))==NULL)
      {
        cprintf("\r\n");
        pstr(305);
//        cprintf("\r\nFile not found.");
        x=1;
      }
      fclose(pass);
    }
  }
  if (!bk)
  {
    if ((pass=fopen(na,"rb"))==NULL)
      error(OPSYS);
    fnsplit(na,lo,pa,ps,cp);
    strcat(lo,pa);
    tmpnam(temp);
    temp[strlen(temp)-4]='.';
    temp[strlen(temp)-3]='c';
    temp[strlen(temp)-2]='o';
    temp[strlen(temp)-1]='m';
    strcat(lo,temp);
    strcpy(temp,lo);
    for(zz=0;zz<=SRCHLEN;zz++) // Clear searching buffer
      ff[zz]=0;
    x=1;
    while(x && !bk)   // Search for shell commands
    {
      yz=1;
      while(yz && !feof(pass))
      {
        msmax=ff[0];
        for(zz=0;zz<SRCHLEN-1;zz++)
          ff[zz]=ff[zz+1];
        ff[zz]=fgetc(pass);
        ff[zz+1]=0;
        yz=!streq(ff,SRCH);
      }
      if (yz)
      {
        cprintf("\r\n\r\n");
        pstr(306);
//        cprintf("\r\n\r\nNo information could be obtained.");
        cprintf("\r\n");
        pstr(307);
//        cprintf("\r\nIt is possible you are using a version of COMMAND.COM that");
        cprintf("\r\n%s ",SENTRY);
        pstr(308);
        cprintf("\r\n\r\n");
//        cprintf("\r\n%s does not recognize, or that it's not a\r\n");
//        cprintf("valid command interpreter.\r\n\r\n",SENTRY);
        pstr(48);
//        cprintf("Press any key to continue...");
        blch();
        x--;   // Abort out of loop
        break;
      }
      else
      {
        spp=fgetc(pass);
        if ((msmax<10) && (spp<10)) // This is it
        {
          fseek(pass,-4,SEEK_CUR); // Go back a bit
          yz=x=spp=1;
          txt[x][0]=0; // Set change flag to "no"
          loc[x]=ftell(pass);
 					while (yz)
          {
  					txt[x][spp]=fgetc(pass);
            if ((spp==1) && ((txt[x][spp]<65) || (txt[x][spp]>90)))
            {
              // Set yz=0 when the end of the shell commands is reached
              yz=0;
              x--; // Back up one line
              bk=1; // Breakout!
            }
            if ((txt[x][spp]<65) || (txt[x][spp]>90))
            {      // The end of this shell command
              txt[x][spp]=0;  // Close off current line
              x++;    // Next line
              if (spp==2) // One char, which is not a commnad
              {
                x-=2;
                yz=0;
                bk=1;
              }
              else
              {
                spp=zz=0;
                while (((spp<65) || (spp>90)) && (zz<10)) // Read until next command
                {
                  spp=fgetc(pass);
                  zz++;
                }
                ungetc(spp,pass);  // Backup one char
                spp=0;
                txt[x][spp]=0; // Set change flag to "no"
                loc[x]=ftell(pass);
							}
            }
						spp++; // Next character
          }
        }
      }
    }
    fclose(pass);
    if (!bk)
    {  // Now clean up temp file, and don't continue execution
      sunlink(temp);
    }
    else
    {
      msmax=x; // Set the maximum number of menu items
      crwin(2,2,50,24,tf,tb,2,glstr(300));
//      crwin(2,2,50,24,tf,tb,2,"Modify Shell Commands");
      if (!wm)
        clrscr();
      // Show menu of items
      y=opt=x=0;
      while (!y)
      {
        txb(tb);
        txc(tf);
        clrscr();
        cprintf("\r\n");
        if (!x)
          cprintf("\r\n");
        if (x>0)
        {
          gotoxy(14,2);
          pstr(157);
          cprintf(" ");
//          cprintf("MORE [Page Up ] ");
        }
        cprintf("\r\n");
        if (x)
          cprintf("\r\n");
        for(y=x;y<WIN2+x;y++)
        {
          if (y<=msmax)
          {
            txb(tb);
            txc(tf);
            if (y)
            {
              if (!txt[y][0])
                cprintf(" - ");
              else
                if (txt[y][0]==1)
                  cprintf(" * ");
                else
                  if (txt[y][0]==2)
                    cprintf(" X ");
            }
            if (sel==(y % WIN2))
            {
              txb(hb);
              txc(hf);
            }
            if (y)
            {
              zz=1;
              while(txt[y][zz]>10)
              {
                cprintf("%c",txt[y][zz]);
                zz++;
              }
              cprintf("\r\n");
            }
          }
        }
        txb(tb);
        txc(tf);
        y=0;
        if (x+WIN2<=msmax)
        {
          gotoxy(12,WIN2+5);
          pstr(158);
          cprintf(" ");
//          cprintf("MORE [Page Down ] ");
        }
        gotoxy(1,WIN2+7);
        // Allow user to [D]isable or [E]dit
        pstr(309);
//        cprintf("[E]dit, [D]isable or ESC to quit.");
        opt=blch();
        switch (opt)
        {
        case 'e':
				// Edit a shell command
          crwin(4,10,60,15,tf,tb,2,"");
          if (!wm)
            clrscr();
          cprintf("\r\n");
          pstr(310);
          cprintf(" ");
//          cprintf("\r\nEnter new value for ");
          zz=1;
          while(txt[sel+x][zz]>10)
          {
            cprintf("%c",txt[sel+x][zz]);
            zz++;
          }
          cprintf(":\r\n");
          strcpy(lo,gin("->",1));
          strupr(lo);
          yz=1;
          if ((strlen(lo)+1)!=zz)
					{
            clrscr();
            pstr(311);
            cprintf("\r\n");
            pstr(312);
            cprintf(" ");
//            cprintf("WARNING: Shell commands that are not the same length");
//            cprintf("\r\nas the original command may cause problems.\r\n");
//            cprintf("\r\nDo you wish to keep it anyway? ");
            yz=blch();
            yeah(yz)
				{
              pstr(211);
//              cprintf("Yes");
              yz=1;
            }
            else
            {
              yz=0;
              pstr(213);
//              cprintf("No");
            }
          }
          if (yz)
          {
  				  txt[sel+x][0]=1; // Command changed
            txt[sel+x][strlen(lo)+1]=1; // Delimiter
            for(yz=0;yz<strlen(lo)+1;yz++) // Copy command to end of string
              txt[sel+x][zz+yz+1]=lo[yz];
            txt[sel+x][zz+yz]=0;
          }
          crwin(2,2,50,24,tf,tb,2,glstr(300));
//          crwin(2,2,50,24,tf,tb,2,"Modify Shell Commands");
          if (!wm)
            clrscr();
          break;
				case 'd':
				// Disable a shell command
          crwin(4,10,25,14,tf,tb,2,"");
          if (!wm)
            clrscr();
          zz=1;
          cprintf("\r\n ");
          while(txt[sel+x][zz]>10)
          {
            cprintf("%c",txt[sel+x][zz]);
            zz++;
          }
          if (txt[sel+x][0]!=2)
          {
            cprintf(" ");
            pstr(313);
//            cprintf(" disabled.");
            txt[sel+x][0]=2;
          }
          else
          {
            cprintf(" ");
            pstr(293);
//            cprintf(" enabled.");
            txt[sel+x][0]=0;
          }
          blch();
          crwin(2,2,50,24,tf,tb,2,glstr(300));
//          crwin(2,2,50,24,tf,tb,2,"Modify Shell Commands");
          if (!wm)
            clrscr();
          break;
        case 13:
          y=1;
          break;
        case 0:
          switch(ext)
          {
          case 77:
          case 80:
            if ((sel<(WIN2-1)) && ((sel+x)<msmax))
              sel++;
              else
              if ((sel+x)<msmax)
              {
                x+=WIN2;
                sel=0;
              }
            break;
          case 72:
          case 75:
            if ((sel>1) || ((sel>0) && (x>0)))
              sel--;
            else
              if (x>0)
              {
                x-=WIN2;
                sel=WIN2-1;
              }
            break;
          case 73:
            if (x>0)
            {
              x-=WIN2;
              if (!sel)
                sel=1;
            }
            else
              sel=1;
            break;
          case 81:
            if ((x+WIN2)<=msmax)
              x+=WIN2;
              else
              sel=msmax-x;
            if (!((sel+x)<=msmax))
              sel=msmax-x;
            break;
          }
          break;
        case ESC:
          y=1;
          break;
        }
        opt=0;
      }
      // Confirm changes
			clrscr();
      cprintf("\r\n");
      pstr(314);
      cprintf("\r\n\r\n");
//      cprintf("\r\nYou have made the following changes:\r\n\r\n");
      yz=spp=0;
			for(x=1;x<=msmax;x++)
      {
        if (txt[x][0])
        {
        	yz++;
          spp++;
          if (yz>WIN2)
          {
            cprintf("\r\n");
            pstr(315);
//            cprintf("\r\nPress any key for more...");
            blch();
            clrscr();
            yz=0;
          }
          zz=1;
          while(txt[x][zz]>10)
          {
            cprintf("%c",txt[x][zz]);
            zz++;
          }
          if (txt[x][0]==1)
          {
            cprintf(" --> ");
            zz++;
            while(txt[x][zz]>10)
            {
              cprintf("%c",txt[x][zz]);
              zz++;
            }
          }
          if (txt[x][0]==2)
          {
            cprintf(" ");
            pstr(316);
//            cprintf(" is disabled.");
          }
          cprintf("\r\n");
        }
      }
      if (spp) // If there are no changes, skip this section
      {
        cprintf("\r\n");
        pstr(317);
        cprintf(" ");
//        cprintf("\r\nIs this correct? ");
        x=blch();
        yeah(x)
        {
//***** Log all transactions!
          pstr(211);
//          cprintf("Yes");
          if ((pass=fopen(na,"rb"))==NULL)
            error(OPSYS);
          // Create the temp file on the same drive as the command processor
          if ((npas=fopen(temp,"wb"))==NULL)
            error(CRTMP);
          zzl=0;
			  	for(x=1;x<=msmax;x++)
          {
            if (txt[x][0])
            {
              for(yzl=zzl;yzl<loc[x];yzl++)
                fputc(fgetc(pass),npas);
              zzl=yzl; // Set after replacement
			  			if (txt[x][0]==1) // Replace
              {
                yz=1;
                while(txt[x][yz]>10)
                {
                  yz++;
                  zzl++; // Stay Current
                  fgetc(pass);
                }
                yz++;
                while(txt[x][yz]>10)
                {
                  fputc(txt[x][yz],npas);
                  yz++;
                }
              }
              else // Disable
              {
                yz=1;
                while(txt[x][yz]>10)
                {
                  yz++;
                  zzl++; // Stay Current
                  fgetc(pass);
                  fputc('*',npas);
                }
              }
            }
          }
          fcd(pass,npas); // Dump the rest of the file
          x=1;
        }
        else
        {
          pstr(213);
//          cprintf("No");
          x=0;
        }
	  		if (x)
        {
          // Run the new shell as a test. If it fails, system will probably
          // lock up, else Replace shell command(s), swap files.
          clrscr();
			 cprintf("\r\n");
          pstr(318);
//			 cprintf("\r\nThe modified command shell will now execute.");
			 cprintf("\r\n");
          pstr(319);
//          cprintf("\r\nPlease test it thoroughly to ensure there are");
//          cprintf("\r\nno problems.");
			 cprintf("\r\n\r\n");
          pstr(320);
//          cprintf("\r\n\r\nPress any key to run the test shell...");
          blch();
          sprintf(tol,glstr(321));
//          sprintf(tol,"Running the test shell.",SENTRY);
          tolog(tol);
          fclose(logf);
          strcpy(tol,SENTRY);
          strcat(tol," ");
          strcat(tol,glstr(322));
//          sprintf(tol,"%s DOS Shell",SENTRY);
          crwin(4,6,50,10,tf,tb,2,tol);
          cprintf("\n\r  ");
          pstr(323);
          cprintf(" %s",SENTRY);
          pstr(294);
          cprintf(".\n\r");
//          cprintf("\n\r  Type \"EXIT\" to leave the %s DOS Shell.\n\r",SENTRY);
          crwin(1,1,79,24,tf,tb,0,"");
          gotoxy(1,24);
					system(temp);
          if ((logf=fopen(ilog,"a"))==NULL)
            error(CRLOG);
          sprintf(tol,glstr(324));
//          sprintf(tol,"Returned from test shell.",SENTRY);
          tolog(tol);
          crwin(2,2,50,24,tf,tb,2,glstr(300));
//          crwin(2,2,50,24,tf,tb,2,"Modify Shell Commands");
          if (!wm)
            clrscr();
          cprintf("\r\n\r\n");
          pstr(325);
          cprintf(" ");
//          cprintf("\r\n\r\nWere there any problems? ");
          x=blch();
          nope(x)
          {
            pstr(213);
//            cprintf("No");
          	strcpy(tol,na);
            tol[strlen(tol)-4]='.';
            tol[strlen(tol)-3]='s';
            tol[strlen(tol)-2]='e';
            tol[strlen(tol)-1]='n';
            sunlink(tol);
						rename(na,tol);
          	rename(temp,na);
            sunlink(temp);
          }
          else
          {
            pstr(211);
//            cprintf("Yes");
            sunlink(temp);
          }
        }
        else
					sunlink(temp); // Abort changes, delete temp file
			}
      else
      {
        cprintf("\r\n");
        pstr(326);
//        cprintf("\r\nNo Changes Made. Press any key.");
        blch();
      }
    }
  }
}

void secm(void)
/*
  secm() allows the user to select which items they want to perform an
  audit on.
*/
{
char hs[(78-52+1)*(23-17+1)*2];
short int x=0,y;
char opt,sel=1;
unsigned long sopt=0;   /**** Should load defaults */
  strcpy(txt[1],glstr(327));
  if (Win95())
    strcpy(txt[2],glstr(328));
  else
    strcpy(txt[2],glstr(329));
  strcpy(txt[3],glstr(330));
  strcpy(txt[4],glstr(331));
  strcpy(txt[5],glstr(332));
  strcpy(txt[6],glstr(333));
  strcpy(txt[7],glstr(334));
  strcpy(txt[8],glstr(335));
  strcpy(txt[9],glstr(336));
  strcpy(txt[10],glstr(337));
  strcpy(txt[11],glstr(338));
  strcpy(txt[12],glstr(339));
  strcpy(txt[13],glstr(340));
  strcpy(txt[14],glstr(341));
  strcpy(txt[15],glstr(342));
  strcpy(txt[16],glstr(343));
  strcpy(txt[17],glstr(344));
  strcpy(txt[18],glstr(345));
  strcpy(txt[SEOPT],glstr(346));
//  strcpy(txt[1],"[ ] A call to Sentry in AUTOEXEC.BAT");
//  if (Win95())
//    strcpy(txt[2],"[ ] A \"BootKeys\" line in MSDOS.SYS");
//  else
//    strcpy(txt[2],"[ ] A \"switches\" line in CONFIG.SYS");
//  strcpy(txt[3],"[ ] A \"break on\" command in CONFIG.SYS");
//  strcpy(txt[4],"[ ] A short max or short min password length");
//  strcpy(txt[5],"[ ] A high number for maximum login attempts");
//  strcpy(txt[6],"[ ] A low number for wait delay");
//  strcpy(txt[7],"[ ] Password echoing should be off or masked");
//  strcpy(txt[8],"[ ] A password expiry max of over 365 days");
//  strcpy(txt[9],"[ ] An unused account expiry max of over 365 days");
//  strcpy(txt[10],"[ ] A long wait for the screen saver (over 600)");
//  strcpy(txt[11],"[ ] Case sensitivity is off");
//  strcpy(txt[12],"[ ] Secure Deletion is off");
//  strcpy(txt[13],"[ ] CTRL-C is enabled");
//  strcpy(txt[14],"[ ] Accounts that have expired (should be deleted)");
//  strcpy(txt[15],"[ ] # of failed login attempts is exceeded");
//  strcpy(txt[16],"[ ] SuperUser accounts with a max inv log setting");
//  strcpy(txt[17],"[ ] Normal accounts with no max inv log setting");
//  strcpy(txt[18],"[ ] Accounts with no expiry date");
//  strcpy(txt[SEOPT],"[ ] Passwords with no expiry date");
  if (!puttext(1,1,80,25,msc))
    error(SCWR);
  crwin(52,17,78,23,tf,tb,2,glstr(347));
  cprintf("\r\n");
  pstr(348);
  cprintf("\r\n");
  pstr(349);
  cprintf("\r\n");
  pstr(350);
  cprintf("\r\n");
  pstr(351);
  cprintf("\r\n");
  pstr(352);
//  crwin(52,17,78,23,tf,tb,2,"Audit Help");
//  cprintf("\r\nSPACE to select an item");
//  cprintf("\r\n'A' to select all items");
//  cprintf("\r\n'T' to toggle all items");
//  cprintf("\r\nENTER to accept, or");
//  cprintf("\r\nESC to abort");
  if (!gettext(52,17,78,23,hs))
    error(SCRD);
  crwin(2,2,58,21,tf,tb,2,glstr(226));
//  crwin(2,2,58,21,tf,tb,2,"Security Audit");
  y=opt=0;
  while (!y)
  {
    hl=sel+40;
    txb(tb);
    txc(tf);
    clrscr();
    cprintf("\r\n");
    if (!x)
      cprintf("\r\n");
    if (x>0)
    {
      gotoxy(14,2);
      pstr(157);
      cprintf(" ");
//      cprintf("MORE [Page Up ] ");
    }
    cprintf("\r\n");
    if (x)
      cprintf("\r\n");
    for(y=x;y<WIN1+x;y++)
    {
      if (y<=SEOPT)
      {
        if (sel==(y % WIN1))
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
          cprintf(" %s\r\n",txt[y]);
      }
    }
    txb(tb);
    txc(tf);
    y=0;
    if (x+WIN1<=SEOPT)
    {
      gotoxy(12,WIN1+5);
      pstr(158);
      cprintf(" ");
//      cprintf("MORE [Page Down ] ");
    }
    gotoxy(1,WIN1+7);
    pstr(353);
    cprintf(" ");
//    cprintf("Select items to audit: ");
    if (!puttext(52,17,78,23,hs))
      error(SCWR);
    opt=blch();
    switch (opt)
    {
    case 'a': /* Select all */
    case 'A':
      sopt=0;
      for(y=0;y<=(SEOPT-1);y++)
      {
        sopt+=rai(y);
        txt[y+1][1]='X';
      }
      y=0;
      break;
    case 't': /* Toggle all */
    case 'T':
      for(y=0;y<=(SEOPT-1);y++)
      {
        sopt^=rai(y);
        if ((sopt|rai(y))==sopt)
          txt[y+1][1]='X';
        else
          txt[y+1][1]=' ';
      }
      y=0;
      break;
    case ' ': /* Space - select/deselect item */
      sopt^=rai(sel+x-1);
      if ((sopt|rai(sel+x-1))==sopt)
        txt[sel+x][1]='X';
      else
        txt[sel+x][1]=' ';
      break;
    case 13:
      secaud(sopt);
      y=1;
      break;
    case 0:
      switch(ext)
      {
      case 77:
      case 80:
        if ((sel<(WIN1-1)) && ((sel+x)<SEOPT))
          sel++;
          else
          if ((sel+x)<SEOPT)
          {
            x+=WIN1;
            sel=0;
          }
        break;
      case 72:
      case 75:
        if ((sel>1) || ((sel>0) && (x>0)))
          sel--;
        else
          if (x>0)
          {
            x-=WIN1;
            sel=WIN1-1;
          }
        break;
      case 73:
        if (x>0)
        {
          x-=WIN1;
          if (!sel)
            sel=1;
        }
        else
          sel=1;
        break;
      case 81:
        if ((x+WIN1)<=SEOPT)
          x+=WIN1;
          else
          sel=SEOPT-x;
        if (!((sel+x)<=SEOPT))
          sel=SEOPT-x;
        break;
      }
      break;
    case ESC:
      y=1;
      break;
    }
    opt=0;
  }
}

void sysinit(void)
/*
  sysinit() initializes the System menu options in the string txt[].
  This is done seperately from the sys() function so that it can be
  performed as required.
*/
{
short int fc;

  for(fc=0;fc<INI;fc++) // Load all initialization strings in
  {
    strcpy(is[fc],glstr(fc+96));
  }

  strcpy(txt[1],glstr(354));
  strcpy(txt[2],glstr(355));
  strcpy(txt[3],glstr(356));
  strcpy(txt[4],glstr(357));
  strcpy(txt[5],glstr(362));
  strcpy(txt[6],glstr(358));
  strcpy(txt[7],glstr(359));
  strcpy(txt[SYOPT],glstr(360));

//  strcpy(txt[1],"1. Edit Initialization Settings");
//  strcpy(txt[2],"2. Send a Message to a User");
//  strcpy(txt[3],"3. Protect a File");
//  strcpy(txt[4],"4. Export Initialization Settings");
//  strcpy(txt[5],"5. Security Audit");
//  strcpy(txt[6],"6. Modify Shell Commands");
//  strcpy(txt[SYOPT],"7. Return to SuperUser Menu");

  if (!puttext(1,1,80,25,msc))
    error(SCWR);
  crwin(10,5,52,17,tf,tb,2,glstr(361));
//  crwin(10,6,48,17,tf,tb,2,"System Maintenance Menu");
}

void sys(void)
/*
  sys() is the function called when a SuperUser logs in and wishes to
  invoke the SuperUser menu (CTRL-enter on login). super() allows the
  user to select an option in much the same way as view() except they can
  also select by option number. Control of the program is subsequently
  passed to the appropriate function.
*/
{
short int x,y;
char opt,sel=1;
  sysinit();
  y=opt=0;
  while (1) /* This is iffy (but it works) */
  {
    hl=sel+30;
    clrscr();
    txb(tb);
    txc(tf);
    cprintf("\r\n");
    for(x=1;x<=SYOPT;x++)
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
      if (((opt-'0')<=SYOPT) && ((opt-'0')!=0))
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
    case 'L': /* Quick jump to log file menu */
      logm();
      break;
    case 'i':
      sel=1;
      opt=13;
      break;
    case 'm':
      sel=2;
      opt=13;
      break;
    case 'p':
      sel=3;
      opt=13;
      break;
    case 'e':
      sel=4;
      opt=13;
      break;
    case 'a':
      sel=5;
      opt=13;
      break;
    case 'c':
      sel=6;
      opt=13;
      break;
    case ESC:  /* Escape */
    case 'x':
      sel=SYOPT;
      opt=13;
      break;
    case 0:
      switch(ext)
      {
      case 77:   /* Cursor Right/Down */
      case 80:
        if (sel<SYOPT)
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
        sel=SYOPT;
        break;
      }
      break;
    }
    if (opt==13)
    {
      switch (sel)
      {
      case 1:
        iset();
        y=1;
        break;
      case 2:
        un=0;
        smsg();
        y=1;
	      break;
      case 3:
        prf();
        y=1;
        break;
      case 4:
       	idmp();
        y=1;
        break;
      case 5:
       	iimp();
        y=1;
        break;
      case 6:
        secm();
        y=1;
        break;
      case 7:
      	mshell();
	      y=1;
 	      break;
      case SYOPT:
  	    su=sul=1;
	      super();
	      break;
      }
    }
    if (y)
      sysinit();
    y=opt=0;
  }
}
