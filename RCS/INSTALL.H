head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.26.40;	author MIKE;	state Exp;
branches;
next	;


desc
@Install Header File
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
#include <conio.h>
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
  GLOBAL CONSTANTS
*/

#if !USER
#define SALT  "ZX"
#define SPAS  "Sentry~"
#define regno 19960720L
#define regto "Shareware\0"
#endif
#if (USER==1)
#define SALT  "MB"
#define SPAS  "MBp74HGQk7hWE"
#define regno 63239046L
#define regto "Michael A. Bobbitt\0"
#endif
#if (USER==2)
#define SALT  "DJ"
#define SPAS  "DJ2BUpmVM4/xU"
#define regno 99408290L
#define regto "D.J. Houghton\0"
#endif
#if (USER==3)
#define SALT  "RC"
#define SPAS  "RCN.qL3UlDmIE"
#define regno 99105327L
#define regto "Robert D. Coombs\0"
#endif
#if (USER==4)
#define SALT  "BJ"
#define SPAS  "BJG7i6maoJRE6"
#define regno 99102696L
#define regto "Bret Jacobsen\0"
#endif
#if (USER==5)
#define SALT  "TH"
#define SPAS  "THUMM5Fi38.b."
#define regno 99282463L
#define regto "Todd W. Harris\0"
#endif
#if (USER==6)
#define SALT  "JH"
#define SPAS  "JHeq9EbrDnJZc"
#define regno 99082382L
#define regto "Jack Hill\0"
#endif
#if (USER==7)
#define SALT  "TB"
#define SPAS  "TBt5GcmDBdTIM"
#define regno 99196107L
#define regto "Trevor Burry\0"
#endif
#if (USER==8)
#define SALT  "KS"
#define SPAS  "KSzw5mvqg3tZ2"
#define regno 99286109L
#define regto "Keith Small\0"
#endif
#if (USER==9)
#define SALT  "FS"
#define SPAS  "FSq34W5yzSC0g"
#define regno 30953671L
#define regto "First Southern Baptist Church\0"
#endif
#if (USER==10)
#define SALT  "LD"
#define SPAS  "LDFgRR47DRLiU"
#define regno 99738162L
#define regto "L.D. Best\0"
#endif
#if (USER==11)
#define SALT  "W1"
#define SPAS  "W1bt9Cp6ks86g"
#define regno 80962561L
#define regto "WMAC Lab - 1A\0"
#endif
#if (USER==12)
#define SALT  "W2"
#define SPAS  "W22zJjx1w8WP6"
#define regno 80962562L
#define regto "WMAC Lab - 1B\0"
#endif
#if (USER==13)
#define SALT  "W3"
#define SPAS  "W3eLlfs4Umpyw"
#define regno 80962563L
#define regto "WMAC Lab - 1C\0"
#endif
#if (USER==14)
#define SALT  "W4"
#define SPAS  "W4hZDKD7yDhfM"
#define regno 80962654L
#define regto "WMAC Lab - 2A\0"
#endif
#if (USER==15)
#define SALT  "W5"
#define SPAS  "W5NaiytFlccf6"
#define regno 80962655L
#define regto "WMAC Lab - 2B\0"
#endif
#if (USER==16)
#define SALT  "EK"
#define SPAS  "EKT090TtfEJU2"
#define regno 30967923L
#define regto "Eric Keyes\0"
#endif
#if (USER==17)
#define SALT  "NA"
#define SPAS  "NAnM7N/iKuKUg"
#define regno 80962566L
#define regto "Native Textiles\0"
#endif
#if (USER==18)
#define SALT  "EM"
#define SPAS  "EMucquDgJQovw"
#define regno 80962567L
#define regto "EMASS\0"
#endif
#if (USER==19)
#define SALT  "IO"
#define SPAS  "IOeFA1hn7a6rM"
#define regno 80962568L
#define regto "Ian John Oldfield\0"
#endif
#if (USER==20)
#define SALT  "NY"
#define SPAS  "NYE2eFz3w4/xc"
#define regno 80962569L
#define regto "NYU Dept. of Economics\0"
#endif
#if (USER==21)
#define SALT  "CT"
#define SPAS  "CTI9iMPDTCi4M"
#define regno 80962570L
#define regto "City of Coppell Texas\0"
#endif

/*
  GLOBAL VARIABLES
*/

extern FILE *fn,*ini,*npas;
extern char lo[MAX],temp[192],ssm[MAX],inam[MAX],t2[192],t3[192];
extern char sd[MAXDRIVE]; /* Start Drive */
extern char sp[MAXPATH];  /* Start Path */
extern char id[MAXDRIVE]; /* Install Drive */
extern char ip[MAXPATH];  /* Install Path */
extern char msc[80*25*2]; /* Array to hold initial screen */

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
int tsk(void);
void error(int s);
char* gin(char *s,short int ech);
int Win95(void);
char blch(void);
void txb(short int tc);
void crwin(short int lf,short int top,short int ri,short int bot,short int frg,short int bak,short int bor,char *tt);
void wdr(short int lf,short int top,short int ri,short int bot,short int bak,short int bor,char *tt);
int cpath (int dir,char *path);
#if !USER
void shar(int x);
#endif
void sunl(const char *sul);
void fin(short int ec);
void sfile(void);
void secres(void);
void main();
int _rtl_chmod(const char *path,int func,int attrib);
#ifdef __cplusplus
}
#endif
@
