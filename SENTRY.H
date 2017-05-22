
//  INCLUDES

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


//  DEFINES

#define AEST 34
#define DAY2SEC 86400L  // Number of seconds in a day
#define ILST 59
#define INI 44   // Number of initialization settings
#define LGOPT 4  // Number of Log File Maintenance Menu Options
#define LLST 13
#define NLST 64
#define PEST 46
#define PMAX 8  // Max size of a password "chunk"
#define SUOPT 6 // Number of SuperUser menu options
#define USOPT 9 // Number of User Mantenance menu options
#define SYOPT 8 // Number of System Mantenance menu options
#define SEOPT 19 // Number of Security Audit options
#define VLBOT 18 // View log file window bottom
#define VLCONST 4  // View log file window adjustment
#define VLFULL 20 // Number of lines to display at a time when not windowed
#define VLLEFT 1  // View log file window left
#define VLRIGHT 78  // View log file window right
#define VLTOP 4  // View log file window top
#define WIN0 15   // # of lines in init setting window
#define WIN1 11   // # of lines in security audit window
#define WIN2 11   // # of lines in modify shell command window
#define WIN3 11   // # of lines in Protect File command window
#define WIND 15   // # of lines in user viewing window
#define pwr fprintf(npas,"%lu %lu %lu %d %d %lu\r\n",ut,ed,pe,fla,ntl,ae)
#define zenc(x) (((x)+(ze)*zze) % 256) // Simple encryption
#define biton(x,y) (((x)|rai((y)))==(x)) // Determines if bit y of x is on


//  GLOBAL VARIABLES

extern FILE *pass,*logf,*ini,*npas,*msg,*LANG;
extern char na[MAX],lo[MAX],pa[MAX],ps[MAX],ti[MAX];
    // login (x2), password (x2), and time stamps
extern char xpwd[MAX],xlog[MAX],lxpwd[MAX],lxlog[MAX],xplen[MAX],xllen[MAX],lxplen[MAX],lxllen[MAX];
     // Various messages, and log file messages
extern char cp[MAX]; // Change Password Key
extern char envar[MAX]; // Environment Variable
extern char usr[MAX]; // User name
extern char pwd[MAX]; // User's encrypted password
extern char win[MAX]; // Command line argument
extern char ilog[MAXDRIVE+MAXPATH]; // Path to the log file
extern char ilbk[MAXDRIVE+MAXPATH]; // Path to the backup log file
extern char imsg[MAXDRIVE+MAXPATH]; // Path to the message file
extern char ins[MAXDRIVE+MAXPATH]; // Path to Sentry.ins
extern char inam[MAX]; // Path to Sentry.exe
extern char temp[MAX2]; // Temporary storage
extern char bd[MAX];   // conversion code
extern char txt[MAXUSER][MAX]; // Array of pointer to strings for menu items
extern char tol[MAX];  // String for printing to the log file
extern char lp[MAX]; // Login prompt
extern char pp[MAX]; // Password prompt
extern char ssm[MAX]; // Screen Saver Message
extern char msc[80*25*2]; // Array to hold initial screen
extern char pec;  // Password echo character
extern char zex[MAXEXT]; // Extension of ZULU file
extern char te[MAXDRIVE+MAXPATH]; // Drive & path of temp files
extern char ze; // ZULU encryption

extern short int zm; // ZULU mode
extern short int min; // Min Password/Pogin Length
extern short int max; // Max Password/Pogin Length
extern short int maxtry; // Max # of invalid tries to lockout
extern short int un;  // User Number
extern short int wait; // Wait time on invalid login
extern short int sul; // sul=1 -> logging in as SuperUser
extern short int su; // su=1 -> user has SuperUser access
extern short int _bk; // _bk=1 -> gin() input routine is exitable (ESC)
extern short int bk; // set by gin(): bk=1 -> input aborted (ESC)
extern short int col; // Colour 0/1
extern short int df; // Date format
extern short int tf,tb,hf,hb; // Text and Highlighted Text Colours
extern short int fla; // Failed login attempts
extern short int ntl; // Number of failed login attempts to lockout
extern short int ltl; // Logins until Lockout
extern short int cs; // cs=1 -> case Insensitive
extern short int wm;  // Window mode (0=none, 1=on, 2=exploding)
extern short int scrb;  // seconds of idle time until screen saver
extern short int rclf,rctop,rcri,rcbot,rcfrg,rcbak; // backup window stats
extern short int zze; // ZULU encryption on/off
extern short int hl; // Help location (# of textfile block)
extern short int sl; // set_lang non-recursive flag
extern short int llp; // Last login Pause
extern short int sdel; // Secure Deletion 0/1
extern short int vwh; // View Highlighting 0/1
extern short int vwc; // View Highligiting Colour
extern short int ctrl; // Disable CTRL-C
extern short int pecc; // Password echo character count

extern int mlog; // Max log file size (kb)

// Time Stamps
extern long ut; // Last login date
extern long ed; // Account Expiry Date
extern long pe; // Password Expiry Date
extern long pel; // Number of days a new password is good for
extern long ae; // Spare
extern long ael; // Number of days an account is good for
extern long regno; // Registration Number

extern struct date td;   // Date
extern struct time nw;   // Time
extern struct text_info sta; // Startup video attributes

extern unsigned _psp;


//  PROTOTYPE DECLARATIONS

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
void set_lang(short int ask);
char blch(void);
void help(void);
void prd(void);
char* tmpath(char *t);
char* browse(short int ftype,int msg);
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
void del(int us);
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
void iimp(void);
void secaud(unsigned long options);
void mshell(void);
void secm(void);
int get_env_index(char *var, char **env_var);
int getenvseg(unsigned *envseg);
unsigned get_env_var(unsigned env_addr, char ***env_var, int *count);
void put_env_var(unsigned env_addr, unsigned seglen, char **env_var);
extern int getswitch(void);
extern int setswitch(char);
void about(void);
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
void pstr(int line);
char* glstr(int line);
void init(void);
void fin(short int ec);
void main(short int argc,char *argv[]);
int _rtl_chmod(const char *path,int func,int attrib);
#ifdef __cplusplus
}
#endif
