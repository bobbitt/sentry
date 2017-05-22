head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.21.34;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.11.58;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.43.39;	author MIKE;	state Exp;
branches;
next	;


desc
@Functions common to Sentry.exe and Install.exe
@


5.0
log
@Version 5.0
@
text
@/*
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
  9 = First Southern Baptist Church
 10 = L.D. Best
 11 = WMAC Lab - 1A
 12 = WMAC Lab - 1B
 13 = WMAC Lab - 1C
 14 = WMAC Lab - 2A
 15 = WMAC Lab - 2B
 16 = Eric Keyes
 17 = Native Textiles
 18 = EMASS
 19 = Ian John Oldfield
 20 = NYU Dept. of Economics
 21 = City of Coppell Texas
*/

#define PROD 1
          /* PROD=0 for testing, PROD=1 for production */
#define ver "5.0"
#define AUBK  "c:\\autoexec.sen"
#define AUCOL YELLOW /* Text colour used for author info */
#define AUTO  "c:\\autoexec.bat"
#define BUFSZ 8192  /* Size of disk buffer */
#define COBK  "c:\\config.sen"
#define CONF  "c:\\config.sys"
#define DEL 8
#define ESC 27
#define DFC LIGHTGRAY /* Default text colour */
#define DIV "*NS*\r\n" /* Divider for data segments */
#define DIVLEN 6
#define ERR 22         /* Number of error messages */
#define MAX 90  /* Maximum length for most strings */
#define MAXUSER 100  /* Maximum number of users */
#define MEMCHECK(x)   if ((x) == NULL) warning(NOMEM) /* Display warning and keep going */
#define MSBK  "c:\\msdos.sen"
#define MSDO  "c:\\msdos.sys"
#define PRBK  "progman.sen"
#define PROG  "progman.ini"
#define RGCOL LIGHTRED /* Text colour used for registration info */
#define SCRWIDTH 78
#define SENTRY "Sentry"
#define SPIN "|/-\\"
#define STAMP '~'  /* SuperUser stamp */
#define TICOL LIGHTGREEN  /* Text colour used for title */
#define WIN_DELAY 30 /* Delay for exploding windows */
#define BUSY " Please Wait...."
#define chop(x) (x)[strlen(x)-1]=0
#define chop2(x) (x)[strlen(x)-2]=0
#define csck(z1,z2) (cs?streq(strupr(z1),strupr(z2)):streq(z1,z2))
#define streq(s1,s2) (!strcmp(s1,s2))
#define txc(x) if (col) textcolor(x)
#define sunlink(x) if (sdel) sunl(x); else unlink(x)

/* Initialization Setting Defines */

#define LLOG 0  /* Location of the Log File */
#define LBKL 1  /* Location of the Backup Log File */
#define LMSG 2  /* Location of the Message File */
#define MINP 3  /* Minimum Password Length */
#define MAXP 4  /* Maximum Password Length */
#define MAXI 5  /* Maximum Invalid Tries */
#define WAIT 6  /* Wait Time After an Invalid Login */
#define MAXL 7  /* Max Log File Size */
#define PKEY 8  /* Key to Change Password */
#define PECH 9  /* Password Echo Character */
#define PEXP 10 /* Days Until Passwords Expire */
#define AEXP 11 /* Days Until Accounts Expire */
#define SSAT 12 /* Screen Saver Activation Time */
#define SMSG 13 /* Screen Saver Message */
#define LOGP 14 /* Login Prompt */
#define PASP 15 /* Password Prompt */
#define WPMS 16 /* Wrong Password Message */
#define WLMS 17 /* Wrong Login Message */
#define BPLM 18 /* Bad Password Length Message */
#define BLLM 19 /* Bad Login Length Message */
#define WPLM 20 /* Wrong Password Log Message */
#define WLLM 21 /* Wrong Login Log Message */
#define BPLL 22 /* Bad Password Length Log Message */
#define BLLL 23 /* Bad Login Length Log Message */
#define ENVV 24 /* Environment Variable */
#define SWIN 25 /* Enable Sentry with Windows */
#define TITL 26 /* Show Title */
#define DATE 27 /* Date Format */
#define CASE 28 /* Case Sensitivity */
#define WINM 29 /* Windowed Mode */
#define COLR 30 /* Enable Colour */
#define TEXC 31 /* Text Colour */
#define TEXB 32 /* Text Background */
#define HTXC 33 /* Highlighted Text Colour */
#define HTXB 34 /* Highlighted Text Background */
#define MXIL 35 /* Maximum Invalid Logins */
#define TYPE 36 /* Type Ahead */
#define CLRS 37 /* Clear Screen */
#define LLPA 38 /* Last Login Pause */
#define SDEL 39 /* Secure Delete */
#define VHGH 40 // View Highlighting
#define VHGC 41 // View Highlighting Colour

/* Error Message Defines */

#define NOENV 0  /* Cannot Locate Environment. */
#define ENVOV 1  /* Environment Overflow - Not Modified. */
#define CRBKL 2  /* Error Creating Backup Log File! */
#define CRLOG 3  /* Error Creating Log File! */
#define CRTMP 4  /* Error Creating Temp File! */
#define OPLOG 5  /* Error Opening Log File! */
#define OPMSG 6  /* Error Opening Message File! */
#define OPPRF 7  /* Error Opening Protected File! */
#define OPINS 8  /* Error Opening Sentry.ins! */
#define OPSYS 9  /* Error Opening System Files! */
#define OPTMP 10 /* Error Opening Temp File! */
#define RDOP  11 /* Error Reading Data Segment [Open] */
#define RDSC  12 /* Please run the INSTALL.EXE program! */
#define SCTMP 13 /* Error Scanning Temp File! */
#define ACINF 14 /* Error in Account Information! */
#define INSET 15 /* Error in Initialization Settings! */
#define SCRD  16 /* Internal Screen Error [Reading] */
#define SCWR  17 /* Internal Screen Error [Writing] */
#define NOMEM 18 /* Out of memory! */
#define REGER 19 /* Registration Error - Program Aborted! */
#define EXPIR 20 /* This account has expired. */
#define LICEN 21 /* Cannot Find LICENSE.TXT! */

/*
  Variables
*/

extern short int sum;   /* SuperUser Menu? Nope, not yet. */
@


4.7
log
@*** empty log message ***
@
text
@d24 5
d31 3
d41 1
d48 1
a48 1
#define MEMCHECK(x)   if ((x) == NULL) error(NOMEM)
a51 2
#define PROD 1
          /* PROD=0 for testing, PROD=1 for production */
d60 1
d66 1
d108 4
a111 1

d127 1
a127 1
#define RDSC  12 /* Error Reading Data Segment [Scan] */
d138 3
a140 25
const char errmsg[ERR][38]=  /* Listing of all error messages */
{
      {"Cannot Locate Environment."},
      {"Environment Overflow - Not Modified."},
      {"Error Creating Backup Log File!"},
      {"Error Creating Log File!"},
      {"Error Creating Temp File!"},
      {"Error Opening Log File!"},
      {"Error Opening Message File!"},
      {"Error Opening Protected File!"},
      {"Error Opening Sentry.ins!"},
      {"Error Opening System Files!"},
      {"Error Opening Temp File!"},
      {"Error Reading Data Segment [Open]"},
      {"Please Run the INSTALL.EXE program."},
      {"Error Scanning Temp File!"},
      {"Error in Account Information!"},
      {"Error in Initialization Settings!"},
      {"Internal Screen Error [Reading]"},
      {"Internal Screen Error [Writing]"},
      {"Out of memory!"},
      {"Registration Error - Program Aborted!"},
      {"This account has expired."},
      {"Cannot Find LICENSE.TXT!"},
};
d142 1
a142 2
short int sum=0;   /* SuperUser Menu? */
const char ver[5]="5.0";  /* Current Version Number */
@


3.8
log
@*** empty log message ***
@
text
@d23 1
d26 1
d28 1
d30 3
d36 1
d39 4
a42 1
#define MEMCHECK(x)   if ((x) == NULL) error("Out of memory!")
d44 2
a45 1
       /* PROD=0 for testing, PROD=1 for production */
d49 1
d59 95
a153 1
const char ver[5]="3.8";  /* Current Version Number */
@
