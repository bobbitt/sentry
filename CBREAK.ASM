	TITLE	CA_Del
	page	,132

_TEXT      SEGMENT  BYTE PUBLIC 'CODE'
	ASSUME  cs: _TEXT

	ORG	100H

	public	CA_Del, Vector, Catch, Install
	public	TempA, TempD

CA_Del	PROC	FAR
	jmp	Install

Catch:	mov	WORD PTR cs:[TempA], ax
	mov	ax, ds
	mov	WORD PTR cs:[TempD], ax

	sub	ax,ax			; Check out keyboard flags
	mov	ds,ax
	mov	al, BYTE PTR ds:[417h]

;	WARNING: trapdoor to unlink CADEL. Press and release (in this order):
;	Insert, Caps Lock, Num Lock, Scroll Lock
;	Press and hold:
;	Left Shift, Right Shift, CTRL, and ALT
;	(You can let go now)

	cmp	al, 0FFh		; All stati set?
	jnz	Check_CA

	mov	ax, WORD PTR cs:[Vector] ; Yes, deinstall our vector
	mov	WORD PTR ds:[9*4], ax
	mov	ax, WORD PTR cs:[Vector + 2]
	mov	WORD PTR ds:[9*4 + 2], ax
	sub	ax, ax

Check_CA:
	and	al, 0Ch
	cmp	al, 0Ch			; Control and alt?
	jz	CheckDel

	cmp	al, 04h			; Control only?
	jnz	GoVect			; If not, forget it

	in	al, 60h			; Look for control C
	and	al, 7Fh			; Up or down
	cmp	al, 2Eh
	jz	Eat_It			; If so, make it vanish

	cmp	al, 46h			; Look for control break
	jz	Eat_It

	jnz	GoVect			; Otherwise let it pass

CheckDel:
	in      al,60h			; read the key
	and	al,7Fh
	cmp	al,53h			; DEL?
	jnz	GoVect			; if not, forget it

Eat_It:	in	al,61H			; Get value of keyboard control lines
	mov	ah,al			; Save it
	or	al,80h			; Set the "enable kbd" bit
	out	61H,al			;  and write it out the control port
	xchg	ah,al			; Fetch original control port value
	out	61H,al			;  and write it back
	mov	al,20H			; Send End-Of-Interrupt signal
	out	20H,al			;  to the 8259 Interrupt Controller

	mov	ax, WORD PTR cs:[TempD]
	mov	ds,ax
	mov	ax, WORD PTR cs:[TempA]
	iret

GoVect:	mov	ax, WORD PTR cs:[Vector+2]
	push	ax
	mov	ax, WORD PTR cs:[Vector]
	push	ax
	mov	ax, WORD PTR cs:[TempD]
	mov	ds,ax
	mov	ax, WORD PTR cs:[TempA]
	ret				; (Far return to original vector)

TempA:	dw	0
TempD:	dw	0
Vector:	dd	0

Install:
	push	cs			; Establish segment registers
	pop	es
	sub	ax, ax
	mov	ds, ax
	mov	di, OFFSET Vector
	mov	si, 9*4
	movsw				; Copy the current vector
	movsw

	mov	ax,cs			; Install my cs
	mov	ds:[9*4+2],ax
	mov	ax, OFFSET Catch	;  and IP
	mov	ds:[9*4], ax

	push	cs
	pop	ds

	mov	ax, WORD PTR cs:[2Eh]	; Free up environment
	mov	es, ax
	mov	ax, 4900H
	int	21h

	mov	dx, OFFSET Install	; Calculate # of paragraphs
	add	dx, 15			; Minus PSP, round up
	rcr	dx, 1
	sar	dx, 1
	sar	dx, 1
	sar	dx, 1

	mov	ax,3100h
	int	21h			; Terminate and stay resident
	int	20h			; Just in case

My_DS:	dw	0

CA_Del	ENDP

_TEXT	ENDS
END	CA_Del
