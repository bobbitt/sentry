/*
  INCLUDES
*/

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <errno.h>
#include "common.h"
#ifdef __cplusplus
}
#endif

/*
  DEFINES
*/

#define tolog(x)
#define INSTALL

/*
  GLOBAL VARIABLES
*/

extern FILE *fn,*ini,*npas;
extern char lo[MAX],temp[MAX2],ssm[MAX],inam[MAX],t2[MAX2],t3[MAX2];
extern char sd[MAXDRIVE]; /* Start Drive */
extern char sp[MAXPATH];  /* Start Path */
extern char id[MAXDRIVE]; /* Install Drive */
extern char ip[MAXPATH];  /* Install Path */
extern char msc[80*25*2]; /* Array to hold initial screen */
extern char regno[9];

extern short int df,bk,_bk;
extern short int sul,max,col,hb,rclf,rctop,rcri,rcbot,rcfrg,rcbak;
extern short int scrb; /* Screen Saver time */
extern short int wm;  /* Windowed Mode on (exploding) */
extern short int col; /* Colour on */
extern short int tf; /* Text Colour */
extern short int tb;  /* Text Background */
extern short int hf;  /* Highlighted Colour */
extern short int hb; /* Highlighted Background */
extern short int sdel; /* Secure Deletion on */
extern short int un;    /* Install/Uninstall */

extern struct date td;
extern struct time nw;
extern struct text_info sta; /* Startup video attributes */

/*
  PROTOTYPE DECLARATIONS
*/

#ifdef __cplusplus
extern "C"
{
#endif
char* UNIXcrypt(char *pw, char *salt);
int tsk(void);
void set_lang(short int ask);
void error(int s);
char* gin(char *s,short int ech);
int Win95(void);
char blch(void);
void txb(short int tc);
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor,char *tt);
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor,char *tt);
int cpath (int dir,char *path);
void pstr(int line);
char* glstr(int line);
#if !USER
void shar(int x);
#endif
void sunl(const char *sul);
char* penc(char *te);
void fin(short int ec);
void sfile(void);
void secres(void);
int regset(int st);
void main();
int _rtl_chmod(const char *path,int func,int attrib);
#ifdef __cplusplus
}
#endif
