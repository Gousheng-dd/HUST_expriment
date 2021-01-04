;MAOSHILONG
;DISP,FUN6,STTONUM

EXTRN FUN4:NEAR,RADIX:NEAR,AUTH:BYTE,GOOD:WORD,CRLF:BYTE,IN_PWD:BYTE
PUBLIC DISP,FUN6

.386
;宏定义
WRITE MACRO A
       LEA DX,A
       MOV AH,9
       INT 21H
ENDM

READ  MACRO A
       LEA DX,A
       MOV AH,10
       INT 21H
ENDM

STACK SEGMENT USE16 PARA STACK 'STACK'
      DB 200 DUP(0)
STACK ENDS

DATA	SEGMENT	USE16 PARA PUBLIC 'DATA'

GO1 DB 'Name:','$';存储待输出商品名称
GO2 DB 'Discount:',3 DUP(0),'$';存储待输出折扣
GO3 DB 'Buying price:',6 DUP(0),'$';存储待输出进货价
GO4 DB 'Selling price:',6 DUP(0),'$';存储待输出销售价
GO5 DB 'Quantity of purchase:',6 DUP(0),'$';存储待输出进货量
GO6 DB 'Quantity of sale:',6 DUP(0),'$';存储待输出销售量
GO7 DB 'Recommendation degree:',6 DUP(0),'$';存储待输出推荐度
NOT12 DB 'Sorry,you can not change it ',0ah,0dh,'$'

IN_DIS DB 3
       DB ?
       DB 3 DUP(0);输入折扣缓冲区
IN_BPR DB 6
       DB ?
       DB 6 DUP(0);输入进价缓冲区
IN_SPR DB 6
       DB ?
       DB 6 DUP(0);输入售价缓冲区
IN_QOP DB 6
       DB ?
       DB 6 DUP(0);输入进货量缓冲区

DATA	ENDS

CODE	SEGMENT	USE16 PARA PUBLIC  'CODE'
	ASSUME	DS:DATA, CS: CODE, SS: STACK
	MOV AX,DATA
	MOV DS,AX

DISP PROC
	
       PUSH EAX
       PUSH EBX
       PUSH CX
       PUSH EDX
       PUSH SI
       PUSH DI
       
       MOV GOOD,BX
       ;输出商品名称
       WRITE GO1
       MOV SI,0
LOOPI: CMP BYTE PTR [BX+SI],0
       JE  N4
       INC SI
       JMP LOOPI

N4:    MOV BYTE PTR [BX+SI],'$'
       MOV DX,BX
       MOV AH,9
       INT 21H
       MOV BYTE PTR [BX+SI],0
       WRITE CRLF
       ;输出折扣
       LEA BX,GO2+9
       MOV SI,0
LOOPO: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,3
       JB  LOOPO
       
       MOV BX,GOOD
       MOVZX EAX,BYTE PTR 10[BX]
       MOV EBX,10
       LEA SI,GO2+9
       CALL RADIX
       WRITE GO2
       WRITE CRLF
       ;输出销售价
       LEA BX,GO4+14
       MOV SI,0
LOOPP: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,6
       JB  LOOPP
       
       MOV BX,GOOD
       MOVZX EAX,WORD PTR 13[BX]
       MOV EBX,10
       LEA SI,GO4+14
       CALL RADIX
       WRITE GO4
       WRITE CRLF
       ;输出进货总量
       LEA BX,GO5+21
       MOV SI,0
LOOPQ: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,6
       JB  LOOPQ
       
       MOV BX,GOOD
       MOVZX EAX,WORD PTR 15[BX]
       MOV EBX,10
       LEA SI,GO5+21
       CALL RADIX
       WRITE GO5
       WRITE CRLF
       ;输出已售数量
       LEA BX,GO6+17
       MOV SI,0
LOOPR: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,6
       JB  LOOPR
       
       MOV BX,GOOD
       MOVZX EAX,WORD PTR 17[BX]
       MOV EBX,10
       LEA SI,GO6+17
       CALL RADIX
       WRITE GO6
       WRITE CRLF
       ;输出推荐度
       LEA BX,GO7+22
       MOV SI,0
LOOPS: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,6
       JB  LOOPS
       
       MOV BX,GOOD
       MOVZX EAX,WORD PTR 19[BX]
       MOV EBX,10
       LEA SI,GO7+22
       CALL RADIX
       WRITE GO7
       WRITE CRLF
       POP DI
       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET
       
DISP ENDP

FUN6 PROC
	
       PUSH EAX
       PUSH EBX
       PUSH CX
       PUSH EDX
       PUSH SI
       CMP AUTH,0
       JE  CANT
       CMP GOOD,0
       JE  CANT
       
DIS:   ;折扣
       LEA BX,GO2+9
       MOV SI,0
LOOPK: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,3
       JB  LOOPK
       
       MOV BX,GOOD
       MOVZX EAX,BYTE PTR 10[BX]
       MOV EBX,10
       LEA SI,GO2+9
       CALL RADIX
       MOV GO2+11,'>'
       WRITE GO2
       WRITE CRLF
       MOV GO2+11,0
       READ IN_DIS
       CMP IN_DIS+1,0;只输入回车
       JE  BPR
       CMP IN_DIS+1,2
       JA  DIS
       CMP IN_DIS+1,1
       JNE IF10
       CMP IN_DIS+2,31H
       JB  DIS
       CMP IN_DIS+2,39H
       JA  DIS
       MOV AL,IN_DIS+2
       SUB AL,30H
       MOV BX,GOOD
       MOV 10[BX],AL
       JMP BPR
       
IF10:  CMP WORD PTR IN_DIS+2,'01'
       JNE DIS
       MOV BX,GOOD
       MOV BYTE PTR 10[BX],10
       
       ;进货价
BPR:   LEA BX,GO3+13
       MOV SI,0
LOOPL: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,6
       JB  LOOPL
       
       MOV BX,GOOD
       PUSH BX
       LEA BX,IN_PWD
       MOV AX,WORD PTR 2[BX]
       POP BX
       XOR AX,WORD PTR 11[BX]
       MOVZX EAX,AX
       MOV EBX,10
       LEA SI,GO3+13
       CALL RADIX
       MOV GO3+18,'>'
       WRITE GO3
       WRITE CRLF
       MOV GO3+18,0
       READ IN_BPR
       CMP IN_BPR+1,0;只输入回车
       JE  SPR
       MOV BX,GOOD
       ADD BX,11
       PUSH BX
       LEA BX,IN_BPR+2
       PUSH BX
       MOVZX AX,IN_BPR+1
       PUSH AX
       CALL STTONUM
       CMP DX,0
       JE  BPR
       
       LEA BX,IN_PWD
       MOV AX,WORD PTR 2[BX]
       MOV BX,GOOD
       XOR 11[BX],AX
       
SPR:   ;销售价
       LEA BX,GO4+14
       MOV SI,0
LOOPM: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,6
       JB  LOOPM
       
       MOV BX,GOOD
       MOVZX EAX,WORD PTR 13[BX]
       MOV EBX,10
       LEA SI,GO4+14
       CALL RADIX
       MOV GO4+19,'>'
       WRITE GO4
       WRITE CRLF
       MOV GO4+19,0
       READ IN_SPR
       CMP IN_SPR+1,0;只输入回车
       JE  QOP
       MOV BX,GOOD
       ADD BX,13
       PUSH BX
       LEA BX,IN_SPR+2
       PUSH BX
       MOVZX AX,IN_SPR+1
       PUSH AX
       CALL STTONUM
       CMP DX,0
       JE  SPR
       
QOP:   ;进货总量
       LEA BX,GO5+21
       MOV SI,0
LOOPN: MOV BYTE PTR [BX+SI],0
       INC SI
       CMP SI,6
       JB  LOOPN
       
       MOV BX,GOOD
       MOV BX,GOOD
       MOVZX EAX,WORD PTR 15[BX]
       MOV EBX,10
       LEA SI,GO5+21
       CALL RADIX
       MOV GO5+26,'>'
       WRITE GO5
       WRITE CRLF
       MOV GO5+26,0
       READ IN_QOP
       CMP IN_QOP+1,0;只输入回车
       JE  EXT
       MOV BX,GOOD
       ADD BX,15
       PUSH BX
       LEA BX,IN_QOP+2
       PUSH BX
       MOVZX AX,IN_QOP+1
       PUSH AX
       CALL STTONUM
       CMP DX,0
       JE  QOP
       
EXT:   CALL FUN4
       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET
	
CANT:  WRITE NOT12
       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET

FUN6 ENDP

STTONUM PROC
	
	PUSH BP
	MOV BP,SP
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH SI
	PUSH DI
	
	MOV DI,8[BP]
	PUSH WORD PTR [DI]
	MOV WORD PTR [DI],0
	MOV CX,1
	MOV SI,4[BP]
	DEC SI
	MOV BX,6[BP]
LOOPJ:  CMP BYTE PTR [BX+SI],30H
	JB  ILL
	CMP BYTE PTR [BX+SI],39H
	JA  ILL
	MOVZX AX,BYTE PTR [BX+SI]
	SUB AX,30H
	MUL CX
	ADD [DI],AX
	CMP SI,0
	JE  DEA
	DEC SI
	IMUL CX,10
	JMP LOOPJ
	
DEA:    MOV DX,1
        POP DI
        POP DI
        POP SI
        POP CX
        POP BX
        POP AX
        POP BP
	RET 6
		
ILL:	MOV DX,0
        POP WORD PTR [DI]
        POP DI
        POP SI
        POP CX
        POP BX
        POP AX
        POP BP
	RET 6

STTONUM ENDP


CODE ENDS
     END