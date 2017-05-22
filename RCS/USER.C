head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.25.24;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	;


desc
@Contains the User Menu and all related functions.
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
  FUNCTIONS
*/

void cpass(void)
/*
  cpass(void) is the function called when a user wishes to change his
  password. cpass(void) requires the user to enter their old password
  (as verification), and then calls setp(void) to set the new password.

  na must be set to the login of the user changing passwords.
*/
{
short int err=1,x=0;
  while (err)
  {
    err=0;
    _bk=0;
    strncpy(pa,gin("\r\nOld Password:",0),max);
    strcpy(temp,pa);
    if ((strlen(pa)>max) || (strlen(pa)<min)) /* check length */
      err=2;
    strcpy(pa,penc(pa));    /* encode */
    temp[strlen(temp)+1]=0;
    temp[strlen(temp)]=STAMP;  /* add SU stamp */
    strcpy(temp,penc(temp));  /* encode */
    pass=ffwd(2,NULL);     /* goto accounts */
    if (!err)
      err=4;
    while((fgets(lo,MAX,pass))!=NULL && (!streq(lo,DIV)))
    {
      x++;
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
          un=x;
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
  un*=-1; /* Enable breaking out of setp() */
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
short int x,y,z,sel=1,tp=0,exx[MAXUSER];
long tn;
char opt=0;
  pass=ffwd(2,NULL);
  x=0;
  getdate(&td);
  gettime(&nw);
  tn=dostounix(&td,&nw);
  crwin(1,1,79,24,tf,tb,1,"User List");
  while(((fgets(lo,MAX,pass))!=NULL) && (!streq(lo,DIV)))
  {
    x++;
    exx[x]=0;
    if (x<MAXUSER)
    {
      fgets(ps,MAX,pass);
      fgets(ti,MAX,pass);
      chop2(lo);
      chop2(ps);
      if (ps[strlen(ps)-1]==STAMP)
      {
        strcat(lo," *");
        exx[x]^=1;
      }
      prd();
      strcpy(txt[x],lo);
      for(y=strlen(lo);y<LLST;y++)
        strcat(txt[x]," ");
      unixtodos(ut,&td,&nw);
      if ((ut<=ael) && ael)
        exx[x]^=2;
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
        if (ed<tn)
          exx[x]^=4;
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
        if (pe<tn)
          exx[x]^=8;
      }
      else
        strcat(txt[x]," * NONE *");
      strcpy(lo,txt[x]);
      for(y=strlen(lo);y<ILST;y++)
        strcat(txt[x]," ");
      sprintf(lo,"%d",fla);
      strcat(txt[x],lo);
      strcpy(lo,txt[x]);
			if ((fla>=ntl) && (ntl))
        exx[x]^=16;
      for(y=strlen(lo);y<NLST;y++)
        strcat(txt[x]," ");
      if (ntl)
        sprintf(lo,"%d",ntl);
      else
        strcpy(lo,"X");
      strcat(txt[x],lo);
      if (!vwh)
        exx[x]=0;
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
          exx[0]=hf;
        }
        else
        {
          txb(tb);
          txc(tf);
          exx[0]=tf;
        }
        if (y)
        {
          if (!exx[y])
            cprintf("%s",txt[y]);
					else
          {
            txc(exx[0]);
            if (biton(exx[y],0)) // SuperUser
              txc(vwc);
            // Print User Name
            for(z=0;z<LLST;z++)
              cprintf("%c",txt[y][z]);
            txc(exx[0]);
            if (biton(exx[y],1)) // Account has not been used
              txc(vwc);
            // Print Last Login
            for(z=LLST;z<AEST;z++)
              cprintf("%c",txt[y][z]);
            txc(exx[0]);
            if (biton(exx[y],2)) // Account Expired
              txc(vwc);
            // Print Account Expiry
            for(z=AEST;z<PEST;z++)
              cprintf("%c",txt[y][z]);
            txc(exx[0]);
            if (biton(exx[y],3)) // Password Expired
              txc(vwc);
            // Print Password Expiry
            for(z=PEST;z<ILST;z++)
              cprintf("%c",txt[y][z]);
            txc(exx[0]);
            if (biton(exx[y],4)) // Max Inv Logins exceeded
              txc(vwc);
            // Print Invalid Logins
            for(z=ILST;z<NLST;z++)
              cprintf("%c",txt[y][z]);
            txc(exx[0]);
				  	// Print Max Invalid Logins
            for(z=NLST;z<strlen(txt[y]);z++)
              cprintf("%c",txt[y][z]);
          }
//cprintf(" [%d]",exx[y]);
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
    case ESC:
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
  crwin(2,5,65,22,tf,tb,2,"Create User(s)");
  if (!wm)
    clrscr();
  while (err>0)
  {
    err=0;
    cprintf("\r\n\r\nNOTE: Pressing CTRL-ENTER after entering the login creates");
    cprintf("\r\n      that user as a SuperUser.\r\n\r\n");
    _bk=1;
    strncpy(na,gin("Login:",1),max);
    strcpy(temp,na);
    if (bk)
      break;
    if ((strlen(temp)>max) || (strlen(temp)<min))
      err=1;
    npas=ffwd(2,NULL);
    while((fgets(lo,MAX,npas))!=NULL && (!streq(lo,DIV)))
    {
      fgets(ps,MAX,npas);
      fgets(ti,MAX,npas);
      chop2(lo);
      if ((csck(temp,lo)) && (!err))
        err=4;
    }
    tmpath(temp);
    fclose(npas);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(OPTMP);
    pass=ffwd(3,npas);
    ed=ftell(npas);
    ed-=DIVLEN;
    fseek(npas,ed,SEEK_SET);
    if (!err)
    {
      _bk=1;
      strncpy(pa,gin("Password:",0),max);
      if (bk)
      {
        sunlink(temp);
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
        strncpy(ps,gin("Verify Password:",0),max);
        if (bk)
        {
          sunlink(temp);
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
            cprintf("\r\nThis user has been created with SuperUser priviliges.\r\n");
          }
          cprintf("\r\nDo you want this account to have an expiry date? ");
          opt=blch();
          if ((opt=='y') || (opt=='Y'))
          {
            cprintf("Yes");
            ed=gdate();
          }
          else
          {
            cprintf("No");
            ed=0;
          }
          cprintf("\r\nDo you want the password to have an expiry date? ");
          opt=blch();
          if ((opt=='y') || (opt=='Y'))
          {
            cprintf("Yes");
            pe=gdate();
          }
          else
          {
            cprintf("No");
            pe=0;
          }
          cprintf("\r\nDo you want other than the default (%d) for the maximum\r\nnumber of invalid logins? ",ltl);
          opt=blch();
          if ((opt=='y') || (opt=='Y'))
          {
            cprintf("Yes");
            ntl=100;
            while ((ntl>99) || (ntl<0))
            {
              cprintf("\r\n\r\nEnter 'X' to assign unlimited invalid logins.");
              cprintf("\r\n\r\nEnter the number of sequential invalid logins before the");
              cprintf("\r\nuser's account is automatically locked up, up to a maximum");
              cprintf("\r\nof 99. Enter selects the default [%d].",ltl);
              cprintf("\r\n");
              strcpy(cp,gin(">",1));
              ntl=atoi(cp);
              if (!strlen(cp))
                ntl=ltl;
            }
          }
          else
          {
            cprintf("No");
            ntl=ltl;
          }
          cprintf("\r\n");
          ae=0;
          /**** This variable is not used for any specific purpose
                at this time! (it's a spare) */
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
      sunlink(inam);
      rename(temp,inam);
    }
    else
      sunlink(temp);
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
    crwin(2,7,60,17,tf,tb,2,"Delete User(s)");
    if (!wm)
      clrscr();
    opt=0;
    pass=ffwd(2,NULL);
    /* Count the # of SuperUsers */
    while((fgets(lo,MAX,pass))!=NULL && (!streq(lo,DIV)))
    {
      fgets(ps,MAX,pass);
      if (ps[strlen(ps)-3]==STAMP)
        opt++;
      fgets(ti,MAX,pass);
    }
    fclose(pass);
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(OPTMP);
    pass=ffwd(2,npas);
    /* Scan to find user */
    while((y<x) && ((fgets(lo,MAX,pass))!=NULL))
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
          if (opt)
            cprintf("No");
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          cprintf("Yes");
          strcpy(tol,"User ");
          strcat(tol,na);
          strcat(tol," Deleted.");
          tolog(tol);
        }
      }
    }
    fcd(pass,npas);
    sunlink(inam);
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
    /* Count the number of SuperUsers */
    while((fgets(lo,MAX,pass))!=NULL && (!streq(lo,DIV)))
    {
      fgets(ps,MAX,pass);
      if (ps[strlen(ps)-3]==STAMP)
        opt++;
      fgets(ti,MAX,pass);
    }
    fclose(pass);
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(OPTMP);
    pass=ffwd(2,npas);
    while((y<v) && (fgets(lo,MAX,pass))!=NULL)
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
          cprintf("Yes");
          _bk=0;
          strncpy(pa,gin("\r\n\r\nPassword:",0),max);
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
            strncpy(na,gin("Verify Password:",0),max);
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
        else
          cprintf("No");
        fputs(lo,npas);
        fputs(ps,npas);
        fputs(ti,npas);
      }
    }
    fcd(pass,npas);
    sunlink(inam);
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
  x=view("Change Account Expiry");
  if (x)
  {
    crwin(2,5,65,22,tf,tb,2,"Set Account Expiry");
    if (!wm)
      clrscr();
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(OPTMP);
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
      cprintf("Yes");
      fputs(lo,npas);
      fputs(ps,npas);
      fputs(ti,npas);
    }
    else
    {
      cprintf("No");
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
    sunlink(inam);
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
    crwin(2,5,65,22,tf,tb,2,"Set Password Expiry");
    if (!wm)
      clrscr();
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(OPTMP);
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
      cprintf("Yes");
      fputs(lo,npas);
      fputs(ps,npas);
      fputs(ti,npas);
    }
    else
    {
      cprintf("No");
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
    sunlink(inam);
    rename(temp,inam);
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
  char opt;
  x=view("Max Invalid Logins");
  if (x)
  {
    crwin(2,5,65,22,tf,tb,2,"Assign Max Number of Invalid Logins");
    if (!wm)
      clrscr();
    tmpath(temp);
    if ((npas=fopen(temp,"wb"))==NULL)
      error(CRTMP);
    pass=ffwd(2,npas);
    while((y<x) && (fgets(lo,MAX,pass))!=NULL)
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
          cprintf("Yes");
          fputs(lo,npas);
          fputs(ps,npas);
          fputs(ti,npas);
        }
        else
        {
          cprintf("No");
          ntl=100;
          while ((ntl>99) || (ntl<0))
          {
            cprintf("\r\n\r\nEnter 'X' to assign unlimited invalid logins.");
            cprintf("\r\n\r\nEnter the number of sequential invalid logins before the");
            cprintf("\r\nuser's account is automatically locked up, up to a maximum");
            cprintf("\r\nof 99. Enter selects the default [%d].",ltl);
            cprintf("\r\n");
            strcpy(na,gin(">",1));
            ntl=atoi(na);
            if (!strlen(na))
              ntl=ltl;
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
    sunlink(inam);
    rename(temp,inam);
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
    error(SCWR);
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
  while (1) /* This is iffy (but it works) */
  {
    hl=sel+10;
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
      if (((opt-'0')<=USOPT) && ((opt-'0')!=0))
      {
        sel=opt-'0';
        opt=13;
      }
    }
    switch (opt)
    {
    case 'S': /* Quick jump to system menu */
      sys();
      break;
    case 'L': /* Quick jump to log file menu */
      logm();
      break;
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
    case ESC:  /* Escape */
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
    hl=sel+10;
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
      case 7:
        un=view("Change Password")*-1;
        if (un)
        {
          crwin(2,5,65,22,tf,tb,2,"Change Password");
          if (!wm)
            clrscr();
          setp();
        }
        y=1;
        break;
      case 8:
        alock();
        y=1;
        break;
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
@


4.7
log
@*** empty log message ***
@
text
@d2 12
d22 2
d33 1
a33 1
    if ((strlen(pa)>max) || (strlen(pa)<min))
d35 1
a35 1
    strcpy(pa,penc(pa));
d37 3
a39 3
    temp[strlen(temp)]=STAMP;
    strcpy(temp,penc(temp));
    pass=ffwd(2,NULL);
d107 3
a109 2
  short int x,y,sel=1,tp=0;
  char opt=0;
d112 3
d119 1
d129 1
d136 2
d160 2
d178 2
d189 2
d195 1
a195 1
        else
d198 2
d281 1
d287 1
d291 40
a330 1
          cprintf("%s",txt[y]);
d391 1
a391 1
    case 27:
d484 2
d487 1
d489 2
d492 1
d496 2
d499 1
d501 2
d504 2
a505 1
          cprintf("\r\nDo you want to set the maximum number of invalid logins? ");
d508 16
a523 1
            ntl=atoi(gin("\r\n\r\nHow many consecutive invalid logins\r\nbefore the account expires?",1));
d525 2
d528 1
d651 2
d659 1
d750 1
d823 2
d848 1
a848 1
  x=view("Change Accont Expiry");
d885 1
d892 1
d972 1
d979 1
d1015 2
a1016 2
  char opt,ho[MAX];
  x=view("Max Inxalid Logins");
d1019 1
a1019 1
    crwin(2,5,65,22,tf,tb,2,"Set Account Lock Out");
d1052 1
d1059 3
a1061 2
          x=0;
          while (x==0)
d1063 1
a1063 2
            x=1;
            cprintf("\r\n\r\nEnter 'N' or '0' to assign unlimited invalid logins.");
d1065 7
a1071 6
            cprintf("\r\nuser's account is automatically expired");
            strcpy(ho,gin(": ",1));
            if ((streq(ho,"n")) || (streq(ho,"N")))
              ntl=0;
            else
              ntl=atoi(ho);
d1123 1
a1123 1
  while (1) /**** This is iffy (but it works) */
d1151 5
a1155 2
      sel=opt-'0';
      opt=13;
d1159 6
d1198 1
a1198 1
    case 27:  /* Escape */
@
