head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.22.09;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.11.58;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.43.02;	author MIKE;	state Exp;
branches;
next	3.3;

3.3
date	95.12.18.18.16.31;	author MIKE;	state Exp;
branches;
next	3.2;

3.2
date	95.12.08.16.31.29;	author MIKE;	state Exp;
branches;
next	3.1;

3.1
date	95.11.30.18.41.52;	author MIKE;	state Exp;
branches;
next	3.0;

3.0
date	95.11.09.15.58.59;	author MIKE;	state Exp;
branches;
next	2.7;

2.7
date	95.10.26.18.05.15;	author MIKE;	state Exp;
branches;
next	2.6;

2.6
date	95.10.25.12.10.14;	author MIKE;	state Exp;
branches;
next	;


desc
@Header file for Sentry.
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
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <dir.h>
#include <errno.h>
#include "common.h"
#ifdef __cplusplus
}
#endif

/*
  DEFINES
*/

#define AEST 34
#define DAY2SEC 86400L  /* Number of seconds in a day */
#define ILST 59
#define INI 42   /* Number of initialization settings */
#define LGOPT 4 /* Number of Log File Maintenance Menu Options */
#define LLST 13
#define NLST 64
#define PEST 46
#define PMAX 8  /* Max size of a password "chunk" */
#define SUOPT 5 /* Number of SuperUser menu options */
#define USOPT 9 /* Number of User Mantenance menu options */
#define SYOPT 7 /* Number of System Mantenance menu options */
#define SEOPT 18 /* Number of Security Audit options */
#define VLBOT 18 /* View log file window bottom */
#define VLCONST 4  /* View log file window adjustment */
#define VLFULL 20 /* Number of lines to display at a time when not windowed */
#define VLLEFT 1  /* View log file window left */
#define VLRIGHT 78  /* View log file window right */
#define VLTOP 4  /* View log file window top */
#define WIN0 15   /* # of lines in init setting window */
#define WIN1 11   /* # of lines in security audit window */
#define WIN2 11   /* # of lines in modify shell command window */
#define WIND 15   /* # of lines in user viewing window */
#define pwr fprintf(npas,"%lu %lu %lu %d %d %lu\r\n",ut,ed,pe,fla,ntl,ae)
#define zenc(x) (((x)+(ze)*zze) % 256)
#define biton(x,y) (((x)|rai((y)))==(x))

/*
  GLOBAL CONSTANTS
*/

/*
  The section below customizes various settings according to each
  individual user. (Defined by USER)
*/

#if !USER
#define SALT  "ZX"
#define regno 19960720L
#define regto "Shareware\0"
/*#define regto "Preview Edition: Mike Weixler\0"*/
#endif
#if (USER==1)
#define SALT  "MB"
#define regno 63239046L
#define regto "Michael A. Bobbitt\0"
#define regch ".gryKf30pR."
#endif
#if (USER==2)
#define SALT  "DJ"
#define regno 99408290L
#define regto "D.J. Houghton\0"
#define regch "NLs7j/3Rn0."
#endif
#if (USER==3)
#define SALT  "RC"
#define regno 99105327L
#define regto "Robert D. Coombs\0"
#define regch "UAPkkdmjUyE"
#endif
#if (USER==4)
#define SALT  "BJ"
#define regno 99102696L
#define regto "Bret Jacobsen\0"
#define regch "a.Yr8OmS5E2"
#endif
#if (USER==5)
#define SALT  "TH"
#define regno 99282463L
#define regto "Todd W. Harris\0"
#define regch "hQBoAAZTnH."
#endif
#if (USER==6)
#define SALT  "JH"
#define regno 99082382L
#define regto "Jack Hill\0"
#define regch "qkgS.iN7RdE"
#endif
#if (USER==7)
#define SALT  "TB"
#define regno 99196107L
#define regto "Trevor Burry\0"
#define regch "unOXJfBNtDE"
#endif
#if (USER==8)
#define SALT  "KS"
#define regno 99286109L
#define regto "Keith Small\0"
#define regch "DKTv9Jw88Lg"
#endif
#if (USER==9)
#define SALT  "FS"
#define regno 30953671L
#define regto "First Southern Baptist Church\0"
#define regch "MAtboxrE1yw"
#endif
#if (USER==10)
#define SALT  "LD"
#define regno 99738162L
#define regto "L.D. Best\0"
#define regch "AAt85vVG26g"
#endif
#if (USER==11)
#define SALT  "W1"
#define regno 80962561L
#define regto "WMAC Lab - 1A\0"
#define regch "POhXsbyAa7U"
#endif
#if (USER==12)
#define SALT  "W2"
#define regno 80962562L
#define regto "WMAC Lab - 1B\0"
#define regch "I4EKqflplNA"
#endif
#if (USER==13)
#define SALT  "W3"
#define regno 80962563L
#define regto "WMAC Lab - 1C\0"
#define regch "MelPfm.5QBQ"
#endif
#if (USER==14)
#define SALT  "W4"
#define regno 80962654L
#define regto "WMAC Lab - 2A\0"
#define regch "zFEUatNYlJY"
#endif
#if (USER==15)
#define SALT  "W5"
#define regno 80962655L
#define regto "WMAC Lab - 2B\0"
#define regch "I0gWXRialNA"
#endif
#if (USER==16)
#define SALT  "EK"
#define regno 30967923L
#define regto "Eric Keyes\0"
#define regch "JTEZuai5b6Y"
#endif
#if (USER==17)
#define SALT  "NA"
#define regno 80962566L
#define regto "Native Textiles\0"
#define regch "mXJjyjE8WhM"
#endif
#if (USER==18)
#define SALT  "EM"
#define regno 80962567L
#define regto "EMASS\0"
#define regch "DcXpDwWlfb6"
#endif
#if (USER==19)
#define SALT  "IO"
#define regno 80962568L
#define regto "Ian John Oldfield\0"
#define regch "hvaL/l6cZHA"
#endif
#if (USER==20)
#define SALT  "NY"
#define regno 80962569L
#define regto "NYU Dept. of Economics\0"
#define regch "38o1Z.eDRwg"
#endif
#if (USER==21)
#define SALT  "CT"
#define regno 80962570L
#define regto "City of Coppell Texas\0"
#define regch "Ymzdk4Ytaiw"
#endif

/*
  GLOBAL VARIABLES
*/

extern FILE *pass,*logf,*ini,*npas,*msg;
extern char na[MAX],lo[MAX],pa[MAX],ps[MAX],ti[MAX];
    /* login (x2), password (x2), and time stamps */
extern char xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX],xplen[MAX],xllen[MAX],lxplen[MAX],lxllen[MAX];
     /* Various messages, and log file messages */
extern char cp[MAX]; /* Change Password Key */
extern char envar[MAX]; /* Environment Variable */
extern char usr[MAX]; /* User name */
extern char pwd[MAX]; /* User's encrypted password */
extern char win[25]; /* Command line argument */
extern char ilog[128]; /* Path to the log file */
extern char ilbk[128]; /* Path to the backup log file */
extern char imsg[128]; /* Path to the message file */
extern char ins[128]; /* Path to Sentry.ins */
extern char inam[MAX]; /* Path to Sentry.exe */
extern char temp[132]; /* Temporary storage */
extern char bd[MAX];   /* conversion code */
extern char txt[MAXUSER][MAX]; /* Array of pointer to strings for menu items */
extern char tol[MAX];  /* String for printing to the log file */
extern char lp[MAX]; /* Login prompt */
extern char pp[MAX]; /* Password prompt */
extern char ssm[MAX]; /* Screen Saver Message */
extern char msc[80*25*2]; /* Array to hold initial screen */
extern char pec;  /* Password echo character */
extern char zex[MAXEXT]; /* Extension of ZULU file */
extern char te[MAXDRIVE+MAXPATH]; /* Drive & path of temp files */
extern char ze; /* ZULU encryption */

extern short int zm; /* ZULU mode */
extern short int min; /* Min Password/Pogin Length */
extern short int max; /* Max Password/Pogin Length */
extern short int maxtry; /* Max # of invalid tries to lockout */
extern short int un;  /* User Number */
extern short int wait; /* Wait time on invalid login */
extern short int sul; /* sul=1 -> logging in as SuperUser */
extern short int su; /* su=1 -> user has SuperUser access */
extern short int _bk; /* _bk=1 -> gin() input routine is exitable (ESC) */
extern short int bk; /* set by gin(): bk=1 -> input aborted (ESC) */
extern short int col; /* Colour 0/1 */
extern short int df; /* Date format */
extern short int tf,tb,hf,hb; /* Text and Highlighted Text Colours */
extern short int fla; /* Failed login attempts */
extern short int ntl; /* Number of failed login attempts to lockout */
extern short int ltl; /* Logins until Lockout */
extern short int cs; /* cs=1 -> case Insensitive */
extern short int wm;  /* Window mode (0=none, 1=on, 2=exploding) */
extern short int scrb;  /* seconds of idle time until screen saver */
extern short int rclf,rctop,rcri,rcbot,rcfrg,rcbak; /* backup window stats */
extern short int zze; /* ZULU encryption on/off */
extern short int hl; /* Help location (# of textfile block) */
extern short int llp; /* Last login Pause */
extern short int sdel; /* Secure Deletion 0/1 */
extern short int vwh; // View Highlighting 0/1
extern short int vwc; // View Highligiting Colour

extern int mlog; /* Max log file size (kb) */

/* Time Stamps */
extern long ut; /* Last login date */
extern long ed; /* Account Expiry Date */
extern long pe; /* Password Expiry Date */
extern long pel; /* Number of days a new password is good for */
extern long ae; /* Spare */
extern long ael; /* Number of days an account is good for */

extern struct date td;   /* Date */
extern struct time nw;   /* Time */
extern struct text_info sta; /* Startup video attributes */

extern unsigned _psp;

/*
  PROTOTYPE DECLARATIONS
*/

#ifdef __cplusplus
extern "C"
{
#endif
char* UNIXcrypt(char *pw, char *salt);
void lockup(void);
void error(int s);
void warning(int s);
int tsk(void);
void ssav(void);
char blch(void);
void help(void);
void prd(void);
char* tmpath(char *t);
short int guser(short int u);
void tolog(char *s);
void dlog(void);
char* gin(char *s,short int ech);
void txb(short int tc);
char* penc(char *te);
long gdate(void);
void setp(void);
void cpass(void);
short int view(char *ac);
void cru(void);
void del(void);
void toggle(void);
void cex(void);
void pex(void);
void vlog(char *tlf);
void mvlog(void);
void alock(void);
void iset(void);
void iedit(int set);
void smsg(void);
int exffwd(int mk);
void prf(void);
void idmp(void);
void secaud(unsigned long options);
void mshell(void);
void secm(void);
int get_env_index(char *var, char **env_var);
int getenvseg(unsigned *envseg);
unsigned get_env_var(unsigned env_addr, char ***env_var, int *count);
void put_env_var(unsigned env_addr, unsigned seglen, char **env_var);
extern int getswitch(void);
extern int setswitch(char);
void suinit(void);
void super(void);
void usrinit(void);
void user(void);
void sysinit(void);
void sys(void);
void loginit(void);
void logm(void);
char* gstr(void);
void stamp(void);
void badl(void);
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor,char *ti);
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor,char *ti);
int cpath(int dir,char *path);
FILE* ffwd(int sp,FILE* dmp);
void fcd(FILE* fn,FILE* dmp);
#if !USER
void shar(int x);
#endif
void sunl(const char *sul);
int Win95(void);
void dshell(void);
unsigned long rai(int r);
void init(void);
void fin(short int ec);
void main(short int argc,char *argv[]);
int _rtl_chmod(const char *path,int func,int attrib);
#ifdef __cplusplus
}
#endif
@


4.7
log
@*** empty log message ***
@
text
@a11 1
#include <alloc.h>
d16 1
d29 1
a29 1
#define INI 38   /* Number of initialization settings */
d34 2
a35 2
#define PMAX 8
#define SUOPT 9 /* Number of SuperUser menu options */
d37 11
a47 7
#define VLBOT 18
#define VLCONST 4
#define VLFULL 20
#define VLLEFT 1
#define VLRIGHT 78
#define VLTOP 4
#define WIN0 14   /* # of lines in init setting window */
d51 1
a52 1

d64 3
a66 2
const long int regno=19960210L;
const char regto[20]="Shareware\0";
d70 3
a72 3
const long int regno=63239046L;
const char regto[20]="Michael A. Bobbitt\0";
const char regch[12]=".gryKf30pR.";
d76 3
a78 3
const long int regno=99408290L;
const char regto[20]="D.J. Houghton\0";
const char regch[12]="NLs7j/3Rn0.";
d82 3
a84 3
const long int regno=99105327L;
const char regto[20]="Robert D. Coombs\0";
const char regch[12]="UAPkkdmjUyE";
d88 3
a90 3
const long int regno=99102696L;
const char regto[20]="Bret Jacobsen\0";
const char regch[12]="a.Yr8OmS5E2";
d94 3
a96 3
const long int regno=99282463L;
const char regto[20]="Todd W. Harris\0";
const char regch[12]="hQBoAAZTnH.";
d100 3
a102 3
const long int regno=99082382L;
const char regto[20]="Jack Hill\0";
const char regch[12]="qkgS.iN7RdE";
d106 3
a108 3
const long int regno=99196107L;
const char regto[20]="Trevor Burry\0";
const char regch[12]="unOXJfBNtDE";
d112 3
a114 3
const long int regno=99286109L;
const char regto[20]="Keith Small\0";
const char regch[12]="DKTv9Jw88Lg";
d118 3
a120 3
const long int regno=30953671L;
const char regto[30]="First Southern Baptist Church\0";
const char regch[12]="MAtboxrE1yw";
d124 3
a126 3
const long int regno=99738162L;
const char regto[20]="L.D. Best\0";
const char regch[12]="AAt85vVG26g";
d130 3
a132 3
const long int regno=80962561L;
const char regto[20]="WMAC Lab - 1A\0";
const char regch[12]="POhXsbyAa7U";
d136 3
a138 3
const long int regno=80962562L;
const char regto[20]="WMAC Lab - 1B\0";
const char regch[12]="I4EKqflplNA";
d142 3
a144 3
const long int regno=80962563L;
const char regto[20]="WMAC Lab - 1C\0";
const char regch[12]="MelPfm.5QBQ";
d148 3
a150 3
const long int regno=80962654L;
const char regto[20]="WMAC Lab - 2A\0";
const char regch[12]="zFEUatNYlJY";
d154 3
a156 3
const long int regno=80962655L;
const char regto[20]="WMAC Lab - 2B\0";
const char regch[12]="I0gWXRialNA";
d160 33
a192 3
const long int regno=30967923L;
const char regto[20]="Eric Keyes\0";
const char regch[12]="JTEZuai5b6Y";
a194 42
const char is[INI][35]=  /* Listing of all initialization settings */
{
      {"Location of the Log File"},
      {"Location of the Backup Log File"},
      {"Location of the Message File"},
      {"Minimum Password Length"},
      {"Maximum Password Length"},
      {"Maximum Invalid Tries"},
      {"Wait Time After an Invalid Login"},
      {"Max Log File Size"},
      {"Key to Change Password"},
      {"Password Echo Character"},
      {"Days Until Passwords Expire"},
      {"Days Until Accounts Expire"},
      {"Screen Saver Activation Time"},
      {"Screen Saver Message"},
      {"Login Prompt"},
      {"Password Prompt"},
      {"Wrong Password Message"},
      {"Wrong Login Message"},
      {"Bad Password Length Message"},
      {"Bad Login Length Message"},
      {"Wrong Password Log Message"},
      {"Wrong Login Log Message"},
      {"Bad Password Length Log Message"},
      {"Bad Login Length Log Message"},
      {"Environment Variable"},
      {"Enable Sentry with Windows"},
      {"Show Title"},
      {"Date Format"},
      {"Case Sensitivity"},
      {"Windowed Mode"},
      {"Enable Colour"},
      {"Text Colour"},
      {"Text Background"},
      {"Highlighted Text Colour"},
      {"Highlighted Text Background"},
      {"Maximum Invalid Logins"},
      {"Type Ahead"},
      {"Clear Screen"},
};

d199 2
a200 2
FILE *pass,*logf,*ini,*npas,*msg;
char na[MAX],lo[MAX],pa[MAX],ps[MAX],ti[MAX];
d202 1
a202 1
char xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX],xplen[MAX],xllen[MAX],lxplen[MAX],lxllen[MAX];
d204 49
a252 44
char cp[MAX]; /* Password Key */
char usr[MAX]; /* User name */
char pwd[MAX]; /* User's encrypted password */
char win[25]; /* Command line argument */
char ilog[128]; /* Path to the log file */
char ilbk[128]; /* Path to the backup log file */
char ins[128]; /* Path to Sentry.ins */
char inam[MAX]; /* Path to Sentry.exe */
char temp[192]; /* Temporary storage */
char bd[MAX];   /* conversion code */
char *txt[MAXUSER]; /* Array of strings for menu items */
char tol[MAX];  /* String for printing to the log file */
char lp[MAX]; /* Login prompt */
char pp[MAX]; /* Password prompt */
char ssm[MAX]; /* Screen Saver Message */
char msc[80*25*2]; /* Array to hold initial screen */
char pec;  /* Password echo character */
char imsg[128]; /* Path to the message file */
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
d254 1
a254 1
int mlog; /* Max log file size (kb) */
d257 10
a266 18
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
d281 1
d312 3
a314 1
void secaud(void);
d325 2
d334 1
d340 1
a340 1
void sunlink(const char *sul);
d343 1
d347 1
a347 1
short int _chmod(const char *filename,short int func,short int attrib);
@


3.8
log
@*** empty log message ***
@
text
@d29 2
a30 1
#define INI 36   /* Number of initialization settings */
d35 1
a35 1
#define SUOPT 7 /* Number of SuperUser menu options */
a36 1
#define LGOPT 4 /* Number of Log File Maintenance Menu Options */
d43 1
d45 1
a45 2
#define WIN0 14   /* # of lines in init setting window */
#define pwr fprintf(npas,"%lu %lu %lu %d %d %lu\n",ut,ed,pe,fla,ntl,ae)
d48 1
d60 1
a60 1
const long int regno=19960120L;
d137 1
a137 1
const long int regno=08962563L;
d153 6
d198 2
d208 1
d213 1
d220 1
a220 1
char bd[MAX];
d227 1
a227 2
char pec;
/*char drv[27]; String of active drives */
d249 1
a249 1
short int cs;
d251 2
a252 1
short int scrb,rclf,rctop,rcri,rcbot,rcfrg,rcbak;
d254 15
a268 4
int mlog; /* Max log file size */
long ut,ed,pe,ae,pel,ael;
struct date td;
struct time nw;
d290 1
a290 1
void error(char *s);
d294 1
d297 1
a297 1
void guser(int u);
d318 1
d321 1
d344 3
@


3.3
log
@Protected files, export settings.
@
text
@a1 36
$Header&

$Log: sentry.h $
Revision 3.2  1995/12/08 16:31:29  MIKE
Mini-mail system.

Revision 3.1  1995/11/30 18:41:52  MIKE
Password echo char & log DOS shell.

Revision 3.0  1995/11/09 15:58:59  MIKE
Sentry V3.0
Hardcoded ini and pwd files.
Exploding windows.
Other minor changes.

Revision 2.7  1995/10/26 18:05:15  MIKE
Screen blanking, minor bugs fixed.

Revision 2.6  1995/10/25 12:10:14  MIKE
Version 2.6
Login and Password prompts are customizable.
Initialization setting changes are logged.
DOS environment variable is set to user's login name.

Revision 1.1  1995/10/25 12:09:07  MIKE
Initial revision

Revision 2.3  1995/09/24 21:38:07  MIKE
Sentry V2.3 - Minor changes.

Revision 2.2  1995/09/08 13:15:13  MIKE
Windowed output, longer password encryption.

*/

/*
d4 4
a7 1

d17 4
a25 14
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
*/

a26 2
#define AUCOL YELLOW /* Text colour used for author info */
#define BUFSZ 8192  /* Size of disk buffer */
a27 3
#define DFC LIGHTGRAY /* Default text colour */
#define DIV "*NS*\r\n" /* Divider for data segments */
#define DIVLEN 6
d29 1
a29 1
#define INI 34   /* Number of initialization settings */
a30 3
#define MAX 80  /* Maximum length for most strings */
#define MAXUSER 100  /* Maximum number of users */
#define MEMCHECK(x)   if ((x) == NULL) error("Out of memory!")
d34 3
a36 7
#define PROD 1       /* PROD=0 for testing, PROD=1 for production */
#define RGCOL LIGHTRED /* Text colour used for registration info */
#define SCRWIDTH 78
#define SENTRY "Sentry"
#define STAMP '~'  /* SuperUser stamp */
#define SUOPT 14    /* Number of SuperUser menu options */
#define TICOL LIGHTGREEN  /* Text colour used for title */
a44 5
#define chop(x) (x)[strlen(x)-1]=0
#define chop2(x) (x)[strlen(x)-2]=0
#define csck(z1,z2) (cs?streq(strupr(z1),strupr(z2)):streq(z1,z2))
#define streq(s1,s2) (!strcmp(s1,s2))
#define txc(x) if (col) textcolor(x)
d46 1
a46 1
#define zenc(x)	(((x)+(ze)*zze) % 256)
d59 1
a59 1
const long int regno=19951105L;
d116 36
a152 1
const char ver[5]="3.3";  /* Current Version Number */
d156 1
d162 1
d197 1
a197 1
FILE *pass,*log,*ini,*npas,*msg;
d199 4
a202 1
char cp[MAX]; /* Password Key, changes to login name */
d205 2
a208 2
char xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX],xplen[MAX],xllen[MAX],lxplen[MAX],lxllen[MAX];
     /* Various messages, and log file messages */
d220 2
d239 3
a241 2
short int cs,wm,scrb,rclf,rctop,rcri,rcbot,rcfrg,rcbak;
short int ze; /* ZULU encryption */
d243 1
d262 4
d270 1
d273 1
d276 1
d283 1
a283 1
short int view(void);
d289 2
a290 1
void vlog(void);
d305 4
d317 1
a317 1
void shar(void);
d323 3
@


3.2
log
@Mini-mail system.
@
text
@d5 3
d49 1
a68 5
/* If it's not the shareware version, include the encoding routine */
#if USER
#include "crypt.c"
#endif

d90 1
a90 1
#define SUOPT 12    /* Number of SuperUser menu options */
d106 1
d156 1
a156 1
const char regch[12]="exqeIUsep5c";
d177 1
a177 1
const char ver[5]="3.2";  /* Current Version Number */
d180 2
a181 2
			{"Location of the Log File"},
			{"Location of the Message File"},
d186 4
a189 4
			{"Key to Change Password"},
			{"Password Echo Character"},
			{"Days Until Passwords Expire"},
			{"Days Until Accounts Expire"},
d228 1
a228 1
		 /* Various messages, and log file messages */
d237 1
a237 1
/* char drv[27]; String of active drives */
d239 21
a259 2
short int min,max,maxtry,un=0,wait,sul,_bk,bk,col,df,tf,tb,hf,hb,fla,ntl;
short int ltl,cs,su,wm,scrb,rclf,rctop,rcri,rcbot,rcfrg,rcbak;
d284 1
d303 2
d316 2
a317 4
void crwin(short int lf,short int top,short int ri,short int bot,short int
frg,short int bak,short int bor);
void wdr(short int lf,short int top,short int ri,short int bot,short int
bak,short int bor);
d319 1
a319 1
void fcd(FILE* str,FILE* dmp);
@


3.1
log
@Password echo char & log DOS shell.
@
text
@d5 3
d73 1
d77 2
a78 2
#define ILST 60
#define INI 32   /* Number of initialization settings */
d83 2
a84 2
#define NLST 68
#define PEST 47
d89 1
d91 1
a91 1
#define SUOPT 11    /* Number of SuperUser menu options */
d106 1
d177 1
a177 1
const char ver[5]="3.1";  /* Current Version Number */
d180 2
a181 1
      {"Location of the Log File"},
d188 2
a189 1
      {"Days Until Passwords Expire"},
d220 19
a238 5
FILE *pass,*log,*ini,*npas;
char na[MAX],pa[MAX],lo[MAX],ps[MAX],ti[MAX],cp[MAX],win[25];
char ilog[128],temp[192],xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX];
char bd[MAX],*txt[MAXUSER],tol[MAX],xplen[MAX],xllen[MAX],lxplen[MAX];
char lxllen[MAX],inam[MAX],lp[MAX],pp[MAX],ssm[MAX],msc[80*25*2],pec;
d241 1
a241 1
long pel;
d264 1
d282 1
@


3.0
log
@Sentry V3.0
Hardcoded ini and pwd files.
Exploding windows.
Other minor changes.
@
text
@d5 6
d59 1
d62 1
d64 1
a64 1
  #include "crypt.c"
d74 1
a74 1
#define INI 31   /* Number of initialization settings */
d76 2
a77 2
#define MAX 80
#define MAXUSER 100
d100 1
d106 5
d112 3
a114 3
  #define SALT  "ZX"
  const long int regno=19951105L;
  const char regto[20]="Shareware\0";
d117 4
a120 4
  #define SALT  "MB"
  const long int regno=63239046L;
  const char regto[20]="Michael A. Bobbitt\0";
  const char regch[12]=".gryKf30pR.";
d123 4
a126 4
  #define SALT  "DJ"
  const long int regno=99408290L;
  const char regto[20]="D.J. Houghton\0";
  const char regch[12]="NLs7j/3Rn0.";
d129 4
a132 4
  #define SALT  "RC"
  const long int regno=99105327L;
  const char regto[20]="Robert D. Coombs\0";
  const char regch[12]="UAPkkdmjUyE";
d135 4
a138 4
  #define SALT  "BJ"
  const long int regno=99102696L;
  const char regto[20]="Bret Jacobsen\0";
  const char regch[12]="a.Yr8OmS5E2";
d141 4
a144 4
  #define SALT  "TH"
  const long int regno=99282463L;
  const char regto[20]="Todd W. Harris\0";
  const char regch[12]="hQBoAAZTnH.";
d147 4
a150 4
  #define SALT  "JH"
  const long int regno=99082382L;
  const char regto[20]="Jack Hill\0";
  const char regch[12]="exqeIUsep5c";
d153 4
a156 4
  #define SALT  "TB"
  const long int regno=99196107L;
  const char regto[20]="Trevor Burry\0";
  const char regch[12]="unOXJfBNtDE";
d159 10
a168 4
  #define SALT  "KS"
  const long int regno=99286109L;
  const char regto[20]="Keith Small\0";
  const char regch[12]="DKTv9Jw88Lg";
d171 2
a172 2
const char ver[5]="3.0";
const char is[INI][35]=
d174 32
a205 31
    {"Location of the Log File"},
    {"Minimum Password Length"},
    {"Maximum Password Length"},
    {"Maximum Invalid Tries"},
    {"Wait Time After an Invalid Login"},
    {"Key to Change Password"},
    {"Days Until Passwords Expire"},
    {"Screen Saver Activation Time"},
    {"Screen Saver Message"},
    {"Login Prompt"},
    {"Password Prompt"},
    {"Wrong Password Message"},
    {"Wrong Login Message"},
    {"Bad Password Length Message"},
    {"Bad Login Length Message"},
    {"Wrong Password Log Message"},
    {"Wrong Login Log Message"},
    {"Bad Password Length Log Message"},
    {"Bad Login Length Log Message"},
    {"Environment Variable"},
    {"Enable Sentry with Windows"},
    {"Show Title"},
    {"Date Format"},
    {"Case Sensitivity"},
    {"Windowed Mode"},
    {"Enable Colour"},
    {"Text Colour"},
    {"Text Background"},
    {"Highlighted Text Colour"},
    {"Highlighted Text Background"},
    {"Maximum Invalid Logins"},
d216 1
a216 1
char lxllen[MAX],inam[MAX],lp[MAX],pp[MAX],ssm[MAX],msc[80*25*2];
a243 1
void txc(short int tc);
d250 1
a250 1
void creat(void);
d270 4
a273 2
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor);
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor);
@


2.7
log
@Screen blanking, minor bugs fixed.
@
text
@d5 3
d36 1
d60 5
a64 2
#define AUCOL YELLOW
#define DFC LIGHTGRAY
d66 1
a66 1
#define INI 31   /* Number of attributes in the .ini file */
d75 1
a75 1
#define RGCOL LIGHTRED
d77 3
a79 3
#define STAMP '~'
#define SUOPT 11
#define TICOL LIGHTGREEN
d86 4
a89 2
#define WIND 15
#define WIN0 14
d99 1
a99 1
  const long int regno=19951001L;
d151 2
a152 2
const char ver[5]="2.7";
const char is[INI][2][35]=
a153 5
  {
    {"Location of the Password File"},
    {"PassFile"}
  },
  {
a154 3
    {"LogFile"}
  },
  {
a155 3
    {"MinPasswordLen"}
  },
  {
a156 3
    {"MaxPasswordLen"}
  },
  {
a157 3
    {"MaxTries"}
  },
  {
a158 3
    {"WaitTime"}
  },
  {
a159 3
    {"SetPassKey"}
  },
  {
a160 3
    {"PasswordExpiresIn"}
  },
  {
d162 1
a162 3
    {"ScreenBlank"}
  },
  {
a163 3
    {"LoginPrompt"}
  },
  {
a164 3
    {"PasswordPrompt"}
  },
  {
a165 3
    {"WrongPassword"}
  },
  {
a166 3
    {"WrongLogin"}
  },
  {
a167 3
    {"PasswordLength"}
  },
  {
a168 3
    {"LoginLength"}
  },
  {
a169 3
    {"LogWrongPassword"}
  },
  {
a170 3
    {"LogWrongLogin"}
  },
  {
a171 3
    {"LogPasswordLength"}
  },
  {
a172 3
    {"LogLoginLength"}
  },
  {
a173 3
    {"EnvToSet"}
  },
  {
a174 3
    {"Windows"}
  },
  {
a175 3
    {"ShowTitle"}
  },
  {
a176 3
    {"DateFormat"}
  },
  {
a177 3
    {"CaseSensitive"}
  },
  {
a178 3
    {"WindowMode"}
  },
  {
a179 3
    {"Colour"}
  },
  {
a180 3
    {"TextColour"}
  },
  {
a181 3
    {"TextBackground"}
  },
  {
a182 3
    {"HighColour"}
  },
  {
a183 3
    {"HighBackground"}
  },
  {
a184 2
    {"InvalidLogins"}
  }
d192 1
a192 1
char na[MAX],pa[MAX],lo[MAX],ps[MAX],ti[MAX],cp[MAX],ipas[128],win[25];
d195 1
a195 1
char lxllen[MAX],inam[MAX],lp[MAX],pp[MAX];
d247 1
a247 1
void getini(void);
a248 1
char* gstr(void);
d251 3
@


2.6
log
@Version 2.6
Login and Password prompts are customizable.
Initialization setting changes are logged.
DOS environment variable is set to user's login name.
@
text
@d1 342
a342 333
/*
$Header&

$Log: sentry.h $
Revision 1.1  1995/10/25 12:09:07  MIKE
Initial revision

Revision 2.3  1995/09/24 21:38:07  MIKE
Sentry V2.3 - Minor changes.

Revision 2.2  1995/09/08 13:15:13  MIKE
Windowed output, longer password encryption.

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
#include <ctype.h>

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

#if USER
  #include "crypt.c"
#endif

#define AEST 34
#define AUCOL YELLOW
#define DFC LIGHTGRAY
#define ILST 60
#define INI 31   /* Number of attributes in the .ini file */
#define LLST 13
#define MAX 80
#define MAXUSER 100
#define MEMCHECK(x)   if ((x) == NULL) error("Out of memory!")
#define NLST 68
#define PEST 47
#define PMAX 8
#define PROD 1       /* PROD=0 for testing, PROD=1 for production */
#define RGCOL LIGHTRED
#define SCRWIDTH 78
#define STAMP '~'
#define SUOPT 11
#define TICOL LIGHTGREEN
#define VLBOT 18
#define VLCONST 4
#define VLFULL 20
#define VLLEFT 1
#define VLRIGHT 78
#define VLTOP 4
#define WIND 15
#define WIN0 14
#define csck(z1,z2) (cs?streq(strupr(z1),strupr(z2)):streq(z1,z2))
#define streq(s1,s2) (!strcmp(s1,s2))

/*
  GLOBAL CONSTANTS
*/

#if !USER
  #define SALT  "ZX"
  const long int regno=19951001L;
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
#if (USER==8)
  #define SALT  "KS"
  const long int regno=99286109L;
  const char regto[20]="Keith Small\0";
  const char regch[12]="DKTv9Jw88Lg";
#endif

const char ver[5]="2.6";
const char is[INI][2][35]=
{
  {
    {"Location of the Password File"},
    {"PassFile"}
  },
  {
    {"Location of the Log File"},
    {"LogFile"}
  },
  {
    {"Minimum Password Length"},
    {"MinPasswordLen"}
  },
  {
    {"Maximum Password Length"},
    {"MaxPasswordLen"}
  },
  {
    {"Maximum Invalid Tries"},
    {"MaxTries"}
  },
  {
    {"Wait Time After an Invalid Login"},
    {"WaitTime"}
  },
  {
    {"Key to Change Password"},
    {"SetPassKey"}
  },
  {
    {"Days Until Passwords Expire"},
    {"PasswordExpiresIn"}
  },
  {
    {"Screen Saver Activation Time"},
    {"ScreenBlank"}
  },
  {
    {"Login Prompt"},
    {"LoginPrompt"}
  },
  {
    {"Password Prompt"},
    {"PasswordPrompt"}
  },
  {
    {"Wrong Password Message"},
    {"WrongPassword"}
  },
  {
    {"Wrong Login Message"},
    {"WrongLogin"}
  },
  {
    {"Bad Password Length Message"},
    {"PasswordLength"}
  },
  {
    {"Bad Login Length Message"},
    {"LoginLength"}
  },
  {
    {"Wrong Password Log Message"},
    {"LogWrongPassword"}
  },
  {
    {"Wrong Login Log Message"},
    {"LogWrongLogin"}
  },
  {
    {"Bad Password Length Log Message"},
    {"LogPasswordLength"}
  },
  {
    {"Bad Login Length Log Message"},
    {"LogLoginLength"}
  },
  {
    {"Environment Variable"},
    {"EnvToSet"}
  },
  {
    {"Enable Sentry with Windows"},
    {"Windows"}
  },
  {
    {"Show Title"},
    {"ShowTitle"}
  },
  {
    {"Date Format"},
    {"DateFormat"}
  },
  {
    {"Case Sensitivity"},
    {"CaseSensitive"}
  },
  {
    {"Windowed Mode"},
    {"WindowMode"}
  },
  {
    {"Enable Colour"},
    {"Colour"}
  },
  {
    {"Text Colour"},
    {"TextColour"}
  },
  {
    {"Text Background"},
    {"TextBackground"}
  },
  {
    {"Highlighted Text Colour"},
    {"HighColour"}
  },
  {
    {"Highlighted Text Background"},
    {"HighBackground"}
  },
  {
    {"Maximum Invalid Logins"},
    {"InvalidLogins"}
  }
};

/*
  GLOBAL VARIABLES
*/

FILE *pass,*log,*ini,*npas;
char na[MAX],pa[MAX],lo[MAX],ps[MAX],ti[MAX],cp[MAX],ipas[128],win[25];
char ilog[128],temp[192],xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX];
char bd[MAX],*txt[MAXUSER],tol[MAX],xplen[MAX],xllen[MAX],lxplen[MAX];
char lxllen[MAX],inam[MAX],lp[MAX],pp[MAX];
short int min,max,maxtry,un=0,wait,sul,_bk,bk,col,df,tf,tb,hf,hb,fla,ntl;
short int ltl,cs,su,wm,scrb;
long pel;
struct date td;
struct time nw;

typedef struct
{        /* structure to use for growing string types */
  char *b;          /* base of string */
  char *p;          /* current "head" of string */
  int  len;         /* length allocated */
  int  inc;         /* how much to grow by each time we fill up */
} estring;

extern unsigned _psp;

/*
  PROTOTYPE DECLARATIONS
*/

char* UNIXcrypt(char *pw, char *salt);
void lockup(void);
void error(char *s);
int tsk(void);
char blch(void);
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
void iset(void);
void iedit(int set);
int get_env_index(char *var, char **env_var);
int getenvseg(unsigned *envseg);
unsigned get_env_var(unsigned env_addr, char ***env_var, int *count);
void put_env_var(unsigned env_addr, unsigned seglen, char **env_var);
extern int getswitch(void);
extern int setswitch(char);
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
@

