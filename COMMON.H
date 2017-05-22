/*
  DEFINES
*/

#define USER 1
/*
  0 = ShareWare
  1 = Registered
*/

#define DEBUG 0
          /* DEBUG=1 for testing, DEBUG=0 for production */

#define ver "6.5"
#define AUBK  "c:\\autoexec.sen"
#define AUCOL YELLOW /* Text colour used for author info */
#define AUTO  "c:\\autoexec.bat"
#define BREAK "cbreak.sys"
#define BRNEW "cbreak.com"
#define BUFSZ 8192  /* Size of disk buffer */
#define COBK  "c:\\config.sen"
#define CONF  "c:\\config.sys"
#define DEL 8  // ASCII code for del char
#define EMAIL "info@cipherlogic.on.ca"
#define WWW "http:/\/www.cipherlogic.on.ca"
#define DFC LIGHTGRAY /* Default text colour */
#define DIV "*NS*\r\n" /* Divider for data segments */
#define DIVLEN 6  // Length of divider
#define ESC 27   // ASCII code for escape char
#define ERR 26         /* Number of error messages */
#define MAX 90    /* Maximum length for most strings */
#define MAX2 192  /* Maximum length for longer strings */
#define MAXUSER 100  /* Maximum number of users */
#define MEMCHECK(x)   if ((x) == NULL) warning(NOMEM) /* Display warning and keep going */
#define MSBK  "c:\\msdos.sen"
#define MSDO  "c:\\msdos.sys"
#define PRBK  "progman.sen"
#define PROG  "progman.ini"
#define RGCOL LIGHTRED /* Text colour used for registration info */
#define SCRWIDTH 78
#define SENTRY "Sentry"  // Program name
#define SPIN "|/-\\" // Characters used for spinner
#define STAMP '~'  /* SuperUser stamp */
#define TICOL LIGHTGREEN  /* Text colour used for title */
#define WIN_DELAY 40 /* Delay for exploding windows */
// #define BUSY " Please Wait...."  // Please wait string
#define chop(x) if (strlen(x)) {(x)[strlen(x)-1]=0;}
#define chop2(x) if (strlen(x)>1) {(x)[strlen(x)-2]=0;}
#define csck(z1,z2) (cs?streq(strupr(z1),strupr(z2)):streq(z1,z2))
#define streq(s1,s2) (!strcmp(s1,s2))
#define txc(x) if (col) textcolor(x)
#define sunlink(x) if (sdel) sunl(x); else unlink(x)
#define yeah(x) if (((x)==yes) || ((x)==(yes+32)))
#define nope(x) if (((x)==no) || ((x)==(no+32)))
#define DEFTXTCOL WHITE // Text colour used for most items
#define DEFBAKCOL BLUE // Background colour used for most items
#define WINTXTCOL WHITE // Text colour used for window borders
#define WINBAKCOL BLUE // Background colour used for window borders


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
#define CTRL 42 // Disable CRTL-C
#define PECC 43 // Password Echo Character Count

/* Error Message Defines */

#define NOENV 0  // Cannot Locate Environment.
#define ENVOV 1  // Environment Overflow - Not Modified.
#define CRBKL 2  // Error Creating Backup Log File!
#define CRLOG 3  // Error Creating Log File!
#define CRTMP 4  // Error Creating Temp File!
#define OPLOG 5  // Error Opening Log File!
#define OPMSG 6  // Error Opening Message File!
#define OPPRF 7  // Error Opening Protected File!
#define OPINS 8  // Error Opening Sentry.ins!
#define OPSYS 9  // Error Opening System Files!
#define OPTMP 10 // Error Opening Temp File!
#define RDOP  11 // Error Reading Data Segment [Open]
#define RDSC  12 // Please run the INSTALL.EXE program!
#define SCTMP 13 // Error Scanning Temp File!
#define ACINF 14 // Error in Account Information!
#define INSET 15 // Error in Initialization Settings!
#define SCRD  16 // Internal Screen Error [Reading]
#define SCWR  17 // Internal Screen Error [Writing]
#define NOMEM 18 // Out of memory!
#define REGER 19 // Registration Error - Program Aborted!
#define EXPIR 20 // This account has expired.
#define LICEN 21 // Cannot Find LICENSE.TXT!
#define OLDI  22 // The Initialization Settings Are Old!
#define NEWI  23 // The Initialization Settings Are New!
#define CHKS  24 // Executable Intrgrity Error!
#define OPSTR 25 // Error Opening String File!

/*
  Common Variables
*/

extern FILE *LANG;

extern char SALT[4]; // crypt() Salt
extern char regto[30]; // Registered User
extern char regch[16]; // Checksum
extern char BUSY[22]; // "Please Wait...." banner
extern char yes;  // Character used to respond to "yes" prompts
extern char no;  // Character used to respond to "no" prompts
extern char lang_name[10]; // Contains the name of the language file

extern short int sum;   /* SuperUser Menu? Nope, not yet. */
extern short int ext; // Extended character on input
extern short int lang; // Language 0=English, 1=Spanish
extern short int sl; // set_lang non-recursive flag

extern unsigned long CHECK; // Checksum Value
