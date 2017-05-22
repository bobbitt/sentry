; protect.asm -- resident write protect for hard disk
; from pc magazine 13 jan 1987 page 320
; additional ROM BIOS codes taken from BYTE 1987 IBM issue, p.176
;
cseg        segment
            assume cs:cseg
            org    100h
;
start:      jmp    initialize
;
oldint13    dd     ?            ; original interrupt 13 vector
switch      db     0fh          ; on/off switch for protection
;
; new interrupt 13 (bios disk i/o)
; --------------------------------
newint13    proc   far
            cmp    ah,03h       ; see if doing disk write
            jz     checkstat    ; if writing then check drive number
;
            cmp    ah,05h       ; see if doing disk format
            jz     checkstat    ; if formatting then check drive number
;
            cmp    ah,06h       ; XT: format track & set bad sector flags
            jz     checkstat
;
            cmp    ah,07h       ; XT: format DRIVE starting at desired track
            jz     checkstat
;
            cmp    ah,0Bh       ; write long
            jz     checkstat
;
            cmp    ah,0Fh       ; write sector buffer
            jz     checkstat
;
            cmp    ah,13h       ; XT: drive diagnostic
            jz     checkstat
;
            cmp    ah,19h       ; PS/2: park heads
            jz     checkstat
;
            cmp    ah,1ah       ; PS/2: ESDI disk, format unit
            jz     checkstat
;
continue:   jmp    cs:[oldint13]; allow operation to proceed
;
checkstat:  cmp    switch,00h   ; is protect switch on?
            jnz    continue     ; if not then proceed
            cmp    dl,00h       ; was drive a selected?
            jz     continue     ; if yes, then proceed
            cmp    dl,01h       ; was drive b selected?
            jz     continue     ; if yes, then proceed
; ******************************************************************
; * Check here for filename. If it's in the exclusion list, abort. *
; ******************************************************************

;
; abort if drive was c or higher
;
abort:      mov    ah,03h       ; set write protect error code
            stc                 ; set failure status
            ret    2            ; return with existing flags
;
newint13    endp
;
; program installation
; begin by searching for an existing copy of code
; -----------------------------------------------
;
initialize: mov    dx,offset newint13    ; offset to begin code search
            mov    ax,cs        ; ds:si points to destination
            mov    es,ax        ; es:di points to source
;
nextseg:    dec    ax           ; search previous segment
            mov    ds,ax        ; load new segment to search
            mov    si,dx        ; point to beginning of string
            mov    di,dx        ; point to beginning of string
; 4 words must match to confirm a copy of program exists
            mov    cx,0004h     ; four words must match
            cld                 ; clear df for autoincrement
            repe   cmpsw
            jnz    notfound     ; if no match then keep trying
;
; a local copy of the program may exist in an input buffer
; any local copies may be identified by switch set to 0fh
            cmp    ds:switch,0fh; is this an installed copy?
            jnz    togglesw     ; if real copy then toggle switch
notfound:   cmp    ax,0001h     ; stop searching at low memory
            jnz    nextseg      ; search next segment
;
; if code not found then it must be installed as follows
;
            mov    switch,00h   ; set switch to on
            mov    ax,3513h     ; setup to get old vector
            int    21h
;
; put old vector in memory
;
            mov    word ptr cs:[oldint13],bx
            mov    word ptr cs:[oldint13+2],es
;
            push   cs
            pop    ds           ; set ds to cs
;
; send message, exit and remain resident
            mov    dx, offset protect_on
            mov    ah,09h       ; print string function call
            int    21h
;
; make interrupt 13 point to this program
            mov    dx,offset newint13
            mov    ax,2513h     ; set new interrupt 13
            int    21h
;
            mov    dx, offset initialize    ; number of bytes to stay
            int    27h          ; terminate and stay resident
;
; if program already exists in memory then only toggle switch
togglesw:   not    ds:switch    ; ds has been set by switch
            cmp    ds:switch,00h; is switch on?
            jz     on
            mov    dx, offset protect_off
            jmp    exit
on:         mov    dx, offset protect_on
exit:       mov    ah,09h       ; print string function call
            push   cs
            pop    ds           ; restore ds
            int    21h
            int    20h          ; exit to dos
;
protect_on  db     "Sentry Hard Disk Protection Enabled$"
protect_off db     "Sentry Hard Disk Protection Disabled$"
cseg        ends
;
            end    start
