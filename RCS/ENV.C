head	5.0;
access;
symbols;
locks
	MIKE:5.0; strict;
comment	@ * @;


5.0
date	96.08.14.09.24.22;	author MIKE;	state Exp;
branches;
next	4.7;

4.7
date	96.04.19.21.09.29;	author MIKE;	state Exp;
branches;
next	3.8;

3.8
date	96.01.23.14.45.57;	author MIKE;	state Exp;
branches;
next	3.3;

3.3
date	95.12.18.18.17.52;	author MIKE;	state Exp;
branches;
next	;


desc
@Handles DOS environment variables.
@


5.0
log
@Version 5.0
@
text
@/*
  INCLUDES
*/
#include "sentry.h"

/*
  FUNCTIONS
*/

char *endptr(p)
char *p;
{
  while (*p) p++;
  return p;
}

int get_env_index(char *var, char **env_var)
{
  /*
   * Find the index into the env_var array of the variable <var>.
      If not
   * found, returns the index of the terminating null entry
   */
  register int i;
  char *temp;
  MEMCHECK(temp = (char *)malloc(strlen(var)+2)) ;
  strcpy( temp, var);
  strupr(strcat(temp,"="));
  for( i = 0; env_var[i]; i++ ) {
    if(strstr(env_var[i], temp) == env_var[i]) break;
  }
  free(temp);
  return(i);
}


int getenvseg(unsigned *envseg )
{
  /*
   * Try to locate the parent environment and fill in the segment a
      ddress
   * This routine has some OS version dependencies
   * Returns  1  if environment found
   *      0  if environment not found
   */
  unsigned  ppsp;
  union REGS  regs;
  int status ;

  regs.x.ax = 0xD44D;           /* 4dos signature value */
  regs.x.bx = 0;
  int86(0x2F, &regs, &regs);        /* TSR multiplex interrput */
  ppsp   = regs.x.cx;           /* psp of immediate parent shell */

  if( regs.x.ax == 0x44dd && ppsp == *(unsigned far *)MK_FP(_psp,0x16) ) {
    /*
         * good, we are running 4dos - AND it is our parent
         * in this case we don't care about dos version
         */
    *envseg =  *(unsigned far *)MK_FP(ppsp,0x2C);
  } else {
    /*
         * Follow the pointers back to our parent psp and fro
        m there get the
         * parent environment segment address
         * With early command.com (pre 3.3) the lowest level
        shell did not fill
         * in the environment segment (it is 0) but we can st
        ill find the
         * environment since it always follows the lowest lev
        el shell directly
         */
    ppsp = *(unsigned far *)MK_FP(_psp,0x16);
    *envseg =  *(unsigned far *)MK_FP(ppsp,0x2C);
    if ((*envseg == 0) &&
        (_osmajor <= 2 || (_osmajor == 3 && _osminor <= 20))) {
      /*
             * we have the pre 3.3 master command.com -
           have to assume that the
             * environment segment directly follows the
           program segment
             * so get the length from the MCB and add i
          t to ppsp
             */
      *envseg = ppsp + *(unsigned far *)MK_FP(ppsp - 1,
          3) + 1;
    }
  }
  /*
     * Verify that the owner of the envseg matches the ppsp we got
      above
     * - just to be a little paranoid
     */
  if ( *(unsigned far *)MK_FP((*envseg)-1, 1) != ppsp) {
    *envseg = 0 ;   /* something wrong :-( */
    status  = 0;
  } else {
    status  = 1 ;
  }
  return(status);
}


unsigned get_env_var(unsigned env_addr, char ***env_var, int *count)
{
  /*
   * Copy the parent environment from the segment address given in
      env_addr, into
   * the memory block pointed to by env_blk.
   * Extract pointers to the start of each variable and build array
       env_var.
   * Return the length of the environment block, (bytes, always a m
      ultiple of 16)
   */
  static char *env_blk;
  unsigned i, len, offset;
  unsigned seglen;

  seglen = *(unsigned far *)MK_FP(env_addr - 1, 3) * 16;
  if ((env_blk = (char *)malloc(seglen)) == (char *)NULL)
    error(NOENV);

  movedata(env_addr, 0, _DS, (unsigned)&env_blk[0], seglen);
  /*
     * make one pass through, counting variables, and allocate spac
      e for the
     * env_var array.  Allow for two extra entries - one to add a n
      ew variable
     * and a terminating null.
     */
  i = 0;
  offset = 0;
  do
  {
    offset += strlen(env_blk+offset) + 1;
    i++;
  } while(*(env_blk+offset));
  MEMCHECK(*env_var = (char **)malloc((i+2)*sizeof(char **))) ;
  *count = i;

  /* load pointers to each of the strings in the array env_var[] */
        i = 0;
  offset = 0;
  do
  {
    len = strlen(env_blk+offset);
    (*env_var)[i] = env_blk+offset;
    offset += len+1;
    i++;
  } while(*(env_blk+offset));
  (*env_var)[i] = NULL;       /* terminate with an extra null */
  return (seglen);
}


void put_env_var(unsigned env_addr, unsigned seglen, char **env_var)
{
  /*
   * Copy the modified environment from the allocated data area, us
      ing the
   * env_var array of pointers, into the memory block pointed to by
       env_addr.
   */
  char  *var_addr;
  unsigned offset, len, i;
  unsigned zero = 0;
  /*
     * Cycle through once to test for environment overflow.  If ove
      rflow,
     * nothing is copied to the old environment block
     */
  for( i=0, offset=0, len=0; env_var[i]; offset+=len, i++)  {
    len = strlen(env_var[i]) + 1;
    if (offset+len >= seglen-2)   /* overflow */
      error(ENVOV);
  }
  /*
     * Now actually copy the strings
     */
  for( i=0, offset=0, len=0; env_var[i]; offset+=len, i++)  {
    len = strlen(env_var[i]) + 1;
    if (len == 1) {
      /* this entry was null - skip it */
      len = 0;
      continue;
    }
    var_addr = env_var[i];
    movedata(_DS, (unsigned)var_addr, env_addr, offset, len);
  }
  /* stuff a zero word at the end of the environment block */
  movedata(_DS, (unsigned)&zero, env_addr, offset, sizeof(unsigned));
}
@


4.7
log
@*** empty log message ***
@
text
@d2 5
@


3.8
log
@*** empty log message ***
@
text
@d116 1
a116 1
    error ("Cannot allocate memory for environment block");
d170 1
a170 1
      error("Environment overflow - not modified.");
@


3.3
log
@Protected files, export settings.
@
text
@d2 1
a2 1
	FUNCTIONS
@
