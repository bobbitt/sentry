/*
  INCLUDES
*/
#include "sentry.h"

/*
  FUNCTIONS
*/

void about(void)
{
  strcpy(tol,glstr(389));
  strcat(tol," ");
//  strcpy(tol,"About ");
  strcat(tol,SENTRY);
  crwin(3,4,68,16,tf,tb,2,tol);
  txc(TICOL);
  cprintf("%s",SENTRY);
  cprintf(" ");
  cprintf("%s",ver);
  txc(tf);
  cprintf("\r\n\r\n");
  cprintf("Copyright (C) 1995-1999 Cipher Logic Canada Inc.\r\n");
  pstr(391);
  cprintf("\r\n\r\n");
  pstr(392);
  cprintf("\r\n");
//  cprintf("All Rights Reserved.\r\n\r\n");
//  cprintf("For more info, please send e-mail to\r\n");
  txc(AUCOL);
  cprintf(EMAIL);
  txc(tf);
  cprintf(" ");
  pstr(393);
  cprintf("\r\n\r\n");
//  cprintf(" or visit:\r\n\r\n");
  txc(RGCOL);
  cprintf(WWW);
  cprintf("\r\n\r\n");
  txc(tf);
  pstr(48);
//  cprintf("Press any key to continue...");
  blch();

}

void suinit(void)
/*
  suinit() initializes the SuperUser menu options in the string txt[].
  This is done seperately from the super() function so that it can be
  performed as required. view() also uses the txt[] variable, so
  suinit() must be called after each call to view().
*/
{
  strcpy(txt[1],glstr(396));
  strcpy(txt[2],glstr(397));
  strcpy(txt[3],glstr(398));
  strcpy(txt[4],glstr(399));
  strcpy(txt[5],glstr(400));
  strcpy(txt[SUOPT],glstr(401));
//  strcpy(txt[1],"1. User Maintenance Menu");
//  strcpy(txt[2],"2. Log File Maintenance Menu");
//  strcpy(txt[3],"3. System Maintenance Menu");
//  strcpy(txt[4],"4. Sentry DOS Shell");
//  strcpy(txt[5],"5. About Sentry");
//  strcpy(txt[SUOPT],"6. Exit");
  if (!puttext(1,1,80,25,msc))
    error(SCWR);
  crwin(10,8,48,12+SUOPT,tf,tb,2,glstr(55));
//  crwin(10,8,48,12+SUOPT,tf,tb,2,"SuperUser Menu");
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
    cprintf("\r\n");
    pstr(92);
    cprintf(" ");
//    cprintf("\r\nOption: ");
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
    case 'D':
      sel=4;
      opt=13;
      break;
    case 'a':
    case 'A':
      sel=5;
      opt=13;
      break;
    case ESC:  /* Escape */
    case 'x':
      sel=SUOPT;
      opt=13;
      break;
    case 0:
      switch(ext)
      {
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
        sprintf(tol,"%s %s",SENTRY,glstr(322));
//        sprintf(tol,"%s DOS Shell",SENTRY);
        crwin(4,6,50,10,tf,tb,2,tol);
	      dshell();
	      y=1;
        break;
      case 5:
        about();
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
