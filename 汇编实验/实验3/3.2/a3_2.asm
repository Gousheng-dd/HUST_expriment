.386
.model flat,c

PUBLIC AUTH,BNAME,GOOD,GOODNAME
PUBLIC FUN1,FUN2,FUN3,FUN4,FUN5,FUN6,FUN7,FUN8

printf  PROTO :PTR SBYTE, :VARARG
scanf   PROTO :PTR SBYTE, :VARARG
gets    PROTO :VARARG
includelib  libcmt.lib
includelib  legacy_stdio_definitions.lib

.STACK 200


.DATA
BNAME DB 'MAOSHILON',0;老板姓名
BPASS DB 'ABCD',0;密码
AUTH DB 0;当前登录状态，0表示客户状态，1表示老板状态
GOOD DD 0;当前浏览商品地址
GOODNAME DB 10 DUP(0)
N EQU 30;商品种类
SNAME DB 'SHOP',0;店铺名称
GA1 DB 'PEN',7 DUP(0),10;商品名称及折扣
    DW 35,56,70,25,?;推荐度还未计算
GANUM EQU $-GA1
GA2 DB 'BOOK',6 DUP(0),9;商品名称及折扣
    DW 12,30,25,5,?;推荐度还未计算
GAN DB N-2 DUP('TempValue',0,8,15,0,20,0,30,0,2,0,?,?);除了2个已经具体定义了的商品信息以外，其他商品信息暂时假定为一样的。

IN_GOOD     DB 10 DUP(0);输入商品名称缓冲区 
IN_GOODLEN  DB ?

CSF  DB '0X',8 DUP(0),0;存放代码段首址的十六进制表示
NOT6 DB 'Please put in the name of goods',0
NOT7 DB 'There is no result',0
NOT8 DB 'Sorry,you can not buy it ',0
CRLF DB 0AH,0DH,0

GO1 DB 'Name:',0;存储待输出商品名称
GO2 DB 'Discount:',3 DUP(0),0;存储待输出折扣
GO3 DB 'Buying price:',6 DUP(0),0;存储待输出进货价
GO4 DB 'Selling price:',6 DUP(0),0;存储待输出销售价
GO5 DB 'Quantity of purchase:',6 DUP(0),0;存储待输出进货量
GO6 DB 'Quantity of sale:',6 DUP(0),0;存储待输出销售量
GO7 DB 'Recommendation degree:',6 DUP(0),0;存储待输出推荐度
NOT12 DB 'Sorry,you can not change it ',0

IN_DIS     DB 3 DUP(0);输入折扣缓冲区
IN_DISLEN  DB ?

IN_BPR     DB 6 DUP(0);输入进价缓冲区
IN_BPRLEN  DB ?

IN_SPR     DB 6 DUP(0);输入售价缓冲区
IN_SPRLEN  DB ?

IN_QOP     DB 6 DUP(0);输入进货量缓冲区
IN_QOPLEN  DB ?

lpFmt	DB	"%s",0ah, 0dh, 0
buf     DB      "%s", 0

.CODE


FUN1 PROC IN_NAME:DWORD,IN_NAMELEN:DWORD,IN_PWD:DWORD,IN_PWDLEN:DWORD

       PUSH ESI
       PUSH EDI
       PUSH AX
       PUSH EBX
       PUSH ECX
       PUSH EDX
       
       CMP IN_NAMELEN,0;只输入回车
       JE  SAU0
       MOV EBX,IN_NAME     
       ;比较姓名
       MOV ESI,IN_NAMELEN
       MOV EDI,ESI
       CMP BYTE PTR BNAME[ESI],0
       JNE SAU0
       
LOOPA: MOV AL,[EBX+EDI-1]
       CMP AL,BNAME[ESI-1]
       JNE SAU0
       DEC EDI
       DEC ESI
       JNE LOOPA
       ;比较密码
       MOV EBX,IN_PWD
       MOV ESI,IN_PWDLEN
       MOV EDI,ESI
       CMP BYTE PTR BPASS[ESI],0
       JNE SAU0
       
LOOPB: MOV AL,[EBX+EDI-1]
       CMP AL,BPASS[ESI-1]
       JNE SAU0
       DEC EDI
       DEC ESI
       JE  SAU1
       JMP LOOPB
       
SAU0:  MOV AUTH,0
       POP EDX
       POP ECX
       POP EBX
       POP AX
       POP EDI
       POP ESI
       RET
       
SAU1:  MOV AUTH,1
       POP EDX
       POP ECX
       POP EBX
       POP AX
       POP EDI
       POP ESI
       RET

FUN1 ENDP

FUN2 PROC
	
       PUSH EAX
       PUSH EBX
       PUSH CX
       PUSH EDX
       PUSH ESI
       PUSH EDI
       MOV GOOD,0
       MOV EBX,OFFSET GOODNAME
       MOV ESI,0
LOPA:  MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,10
       JB LOPA       
       
       INVOKE printf,OFFSET lpFmt,ADDR NOT6
       
       INVOKE scanf,OFFSET buf,ADDR IN_GOOD
       MOV EDX, OFFSET IN_GOOD
       MOV ECX,0
LOPD:  INC ECX
       CMP BYTE PTR [EDX+ECX-1],0
       JNE LOPD
       DEC ECX
       MOV IN_GOODLEN,CL
       ;查找商品
       MOV CX,0
       MOV EBX,OFFSET GA1
LOOPC: MOV AL,IN_GOODLEN
       MOVZX ESI,AL
       MOV EDI,ESI
       CMP BYTE PTR [EBX+ESI],0
       JNE NEXTA
LOOPF: MOV AL,IN_GOOD[EDI-1]
       CMP AL,[EBX+ESI-1]
       JNE NEXTA
       DEC EDI
       DEC ESI
       JNE LOOPF
       
       PUSH EBX
       MOV EBX,OFFSET GOODNAME
       MOV AL,IN_GOODLEN
       MOVZX ESI,AL
       MOV EDI,ESI
LOOPU: MOV AL,IN_GOOD[EDI-1]
       MOV [EBX+ESI-1],AL
       DEC EDI
       DEC ESI
       CMP ESI,0
       JNE LOOPU
       POP EBX
       CALL DISP
       
       POP EDI
       POP ESI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET
       
NEXTA: INC CX
       ADD EBX,GANUM
       CMP CX,N
       JB  LOOPC

       INVOKE printf,OFFSET lpFmt,NOT7
       POP EDI
       POP ESI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET
       
FUN2 ENDP

DISP PROC
	
       PUSH EAX
       PUSH EBX
       PUSH CX
       PUSH EDX
       PUSH ESI
       PUSH EDI
       
       MOV GOOD,EBX
       ;输出商品名称

       INVOKE printf,OFFSET lpFmt,ADDR GO1
       
       INVOKE printf,OFFSET lpFmt,ADDR GOODNAME

       ;输出折扣
       LEA EBX,GO2+9
       MOV ESI,0
LOOPO: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,3
       JB  LOOPO
       
       MOV EBX,GOOD
       MOVZX EAX,BYTE PTR 10[EBX]
       MOV EBX,10
       MOV ESI,OFFSET GO2
       ADD ESI,9
       CALL RADIX

       INVOKE printf,OFFSET lpFmt,ADDR GO2
       
       ;输出销售价
       MOV EBX,OFFSET GO4
       ADD EBX,14
       MOV ESI,0
LOOPP: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,6
       JB  LOOPP
       
       MOV EBX,GOOD
       MOVZX EAX,WORD PTR 13[EBX]
       MOV EBX,10
       LEA ESI,GO4+14
       CALL RADIX
       
       INVOKE printf,OFFSET lpFmt,ADDR GO4
       
       ;输出进货总量
       LEA EBX,GO5+21
       MOV ESI,0
LOOPQ: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,6
       JB  LOOPQ
       
       MOV EBX,GOOD
       MOVZX EAX,WORD PTR 15[EBX]
       MOV EBX,10
       LEA ESI,GO5+21
       CALL RADIX

       INVOKE printf,OFFSET lpFmt,ADDR GO5
       
       ;输出已售数量
       LEA EBX,GO6+17
       MOV ESI,0
LOOPR: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,6
       JB  LOOPR
       
       MOV EBX,GOOD
       MOVZX EAX,WORD PTR 17[EBX]
       MOV EBX,10
       LEA ESI,GO6+17
       CALL RADIX

       INVOKE printf,OFFSET lpFmt,ADDR GO6
       
       ;输出推荐度
       LEA EBX,GO7+22
       MOV ESI,0
LOOPS: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,6
       JB  LOOPS
       
       MOV EBX,GOOD
       MOVZX EAX,WORD PTR 19[EBX]
       MOV EBX,10
       LEA ESI,GO7+22
       CALL RADIX

       INVOKE printf,OFFSET lpFmt,ADDR GO7
       
       POP EDI
       POP ESI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET
       
DISP ENDP

FUN3 PROC
	
       PUSH AX
       PUSH BX
       PUSH DX
       CMP GOOD,0
       JE  UNVA
       MOV EBX,GOOD
       MOV AX,15[EBX]
       CMP AX,17[EBX]
       JBE UNVA
       ADD BYTE PTR 17[EBX],1
       CALL FUN4
       POP DX
       POP BX
       POP AX
       RET

UNVA:  
       INVOKE printf,OFFSET lpFmt,NOT8

       POP DX
       POP BX
       POP AX
       RET
       
FUN3 ENDP

FUN4 PROC
	
       PUSH AX
       PUSH EBX
       PUSH CX
       PUSH DX
       PUSH SI
       PUSH DI
       MOV CX,0
       MOV EBX,OFFSET GA1
       
LOOPG: MOVZX AX,BYTE PTR 10[EBX]
       MUL WORD PTR 13[EBX]
       MOV SI,AX
       MOV AX,1280
       MUL WORD PTR 11[EBX]
       DIV SI
       MOV 19[EBX],AX
       MOV DI,DX
       
       MOV AX,64
       MUL WORD PTR 17[EBX]
       DIV WORD PTR 15[EBX]
       ADD DX,DI
       JNC NAD1
       INC AX
NAD1:  ADD 19[EBX],AX
       
       INC CX
       ADD EBX,GANUM
       CMP CX,N
       JB  LOOPG
       POP DI
       POP SI
       POP DX
       POP CX
       POP EBX
       POP AX
       RET

FUN4 ENDP

FUN5 PROC
	
	PUSH AX
	PUSH EBX
	PUSH CX
	PUSH DX
	PUSH ESI
	PUSH EDI
	
	MOV AX,0
LOOPV:	MOV CX,AX
        INC CX
LOOPX:  MOV EBX,0
        MOV ESI,0
	MOV EBX,OFFSET GA1
        MOV SI,GANUM
        IMUL SI,AX
        MOVZX ESI,SI
	ADD ESI,EBX
	MOV DX,19[ESI]
	
	MOV DI,GANUM
	IMUL DI,CX
	MOVZX EDI,DI
	ADD EDI,EBX
	CMP DX,19[EDI]
	JA  GRE
	MOV DX,0
LOOPY:	PUSH AX
	MOV AL,[ESI]
	MOV AH,[EDI]
	MOV [EDI],AL
	MOV [ESI],AH
	POP AX
	INC ESI
	INC EDI
	INC DX
	CMP DX,GANUM
	JB  LOOPY
	
GRE:  	INC CX
        CMP CX,N
        JB  LOOPX
        
        INC AX
        CMP AX,N-1
        JB  LOOPV
        
        MOV GOOD,0
        MOV EBX,OFFSET GOODNAME
        MOV ESI,0
LOPI:   MOV BYTE PTR [EBX+ESI],0
        INC ESI
        CMP ESI,10
        JB LOPI
        
	POP EDI
	POP ESI
	POP DX
	POP CX
	POP EBX
	POP AX
	RET

FUN5 ENDP

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
       LEA EBX,GO2+9
       MOV ESI,0
LOOPK: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,3
       JB  LOOPK
       
       MOV EBX,GOOD
       MOVZX EAX,BYTE PTR 10[EBX]
       MOV EBX,10
       LEA ESI,GO2+9
       CALL RADIX
       MOV GO2+11,'>'

       INVOKE printf,OFFSET lpFmt,ADDR GO2
       
       MOV GO2+11,0

       INVOKE gets,ADDR IN_DIS
       MOV ECX,0
       MOV EDX,OFFSET IN_DIS
LOPE:  INC ECX
       CMP BYTE PTR [EDX+ECX-1],0
       JNE LOPE
       DEC ECX
       MOV IN_DISLEN,CL
       
       CMP IN_DISLEN,0;只输入回车
       JE  BPR
       CMP IN_DISLEN,2
       JA  DIS
       CMP IN_DISLEN,1
       JNE IF10
       CMP IN_DIS,31H
       JB  DIS
       CMP IN_DIS,39H
       JA  DIS
       MOV AL,IN_DIS
       SUB AL,30H
       MOV EBX,GOOD
       MOV 10[EBX],AL
       JMP BPR
       
IF10:  CMP WORD PTR IN_DIS,'01'
       JNE DIS
       MOV EBX,GOOD
       MOV BYTE PTR 10[EBX],10
       
       ;进货价
BPR:   LEA EBX,GO3+13
       MOV ESI,0
LOOPL: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,6
       JB  LOOPL
       
       MOV EBX,GOOD
       MOVZX EAX,WORD PTR 11[EBX]
       MOV EBX,10
       LEA ESI,GO3+13
       CALL RADIX
       MOV GO3+18,'>'

       INVOKE printf,OFFSET lpFmt,ADDR GO3
       
       MOV GO3+18,0

       INVOKE gets,ADDR IN_BPR
       MOV ECX,0
       MOV EDX, OFFSET IN_BPR
LOPF:  INC ECX
       CMP BYTE PTR [EDX+ECX-1],0
       JNE LOPF
       DEC ECX
       MOV IN_BPRLEN,CL
       
       CMP IN_BPRLEN,0;只输入回车
       JE  SPR
       MOV EBX,GOOD
       ADD EBX,11
       PUSH EBX
       LEA EBX,IN_BPR
       PUSH EBX
       MOVZX EAX,IN_BPRLEN
       PUSH EAX
       CALL STTONUM
       CMP DX,0
       JE  BPR
       
SPR:   ;销售价
       LEA EBX,GO4+14
       MOV ESI,0
LOOPM: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,6
       JB  LOOPM
       
       MOV EBX,GOOD
       MOVZX EAX,WORD PTR 13[EBX]
       MOV EBX,10
       LEA ESI,GO4+14
       CALL RADIX
       MOV GO4+19,'>'
       
       INVOKE printf,OFFSET lpFmt,ADDR GO4
       
       MOV GO4+19,0

       INVOKE gets,ADDR IN_SPR
       MOV ECX,0
       MOV EDX, OFFSET IN_SPR
LOPG:  INC ECX
       CMP BYTE PTR [EDX+ECX-1],0
       JNE LOPG
       DEC ECX
       MOV IN_SPRLEN,CL
       
       CMP IN_SPRLEN,0;只输入回车
       JE  QOP
       MOV EBX,GOOD
       ADD EBX,13
       PUSH EBX
       LEA EBX,IN_SPR
       PUSH EBX
       MOVZX EAX,IN_SPRLEN
       PUSH EAX
       CALL STTONUM
       CMP DX,0
       JE  SPR
       
QOP:   ;进货总量
       LEA EBX,GO5+21
       MOV ESI,0
LOOPN: MOV BYTE PTR [EBX+ESI],0
       INC ESI
       CMP ESI,6
       JB  LOOPN
       
       MOV EBX,GOOD

       MOVZX EAX,WORD PTR 15[EBX]
       MOV EBX,10
       LEA ESI,GO5+21
       CALL RADIX
       MOV GO5+26,'>'

       INVOKE printf,OFFSET lpFmt,ADDR GO5
       
       MOV GO5+26,0

       INVOKE gets,ADDR IN_QOP
       MOV ECX,0
       MOV EDX, OFFSET IN_QOP
LOPH:  INC ECX
       CMP BYTE PTR [EDX+ECX-1],0
       JNE LOPH
       DEC ECX
       MOV IN_QOPLEN,CL
       
       CMP IN_QOPLEN,0;只输入回车
       JE  EXT
       MOV EBX,GOOD
       ADD EBX,15
       PUSH EBX
       LEA EBX,IN_QOP
       PUSH EBX
       MOVZX EAX,IN_QOPLEN
       PUSH EAX
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
	
CANT:  
       INVOKE printf,OFFSET lpFmt,ADDR NOT12

       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET

FUN6 ENDP

STTONUM PROC
	
	PUSH EBP
	MOV EBP,ESP
	PUSH AX
	PUSH EBX
	PUSH ECX
	PUSH ESI
	PUSH EDI

	MOV ECX,0
	MOV EDI,16[EBP]
	PUSH WORD PTR [EDI]
	MOV WORD PTR [EDI],0
	MOV CX,1
	MOV ESI,8[EBP]
	DEC ESI
	MOV EBX,12[EBP]
LOOPJ:  CMP BYTE PTR [EBX+ESI],30H
	JB  ILL
	CMP BYTE PTR [EBX+ESI],39H
	JA  ILL
	MOVZX AX,BYTE PTR [EBX+ESI]
	SUB AX,30H
	MUL CX
	ADD [EDI],AX
	CMP ESI,0
	JE  DEA
	DEC ESI
	IMUL CX,10
	JMP LOOPJ
	
DEA:    MOV DX,1
        POP DI
        POP EDI
        POP ESI
        POP ECX
        POP EBX
        POP AX
        POP EBP
	RET 12
		
ILL:	MOV DX,0
        POP WORD PTR [EDI]
        POP EDI
        POP ESI
        POP CX
        POP EBX
        POP AX
        POP EBP
	RET 12

STTONUM ENDP

FUN7 PROC
	
	RET

FUN7 ENDP

FUN8 PROC
	
       PUSH EAX
       PUSH EBX
       PUSH CX
       PUSH EDX
       PUSH SI
	   MOV EAX,0
       MOV EAX,CS
       MOV EBX,16
       LEA SI,CSF+2
       CALL RADIX

       INVOKE printf,OFFSET lpFmt,ADDR CSF
       
       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET

FUN8 ENDP

RADIX PROC
	
       PUSH ECX
       PUSH EDX
       XOR ECX,ECX
LOP1:  XOR EDX,EDX
       DIV EBX
       PUSH DX
       INC CX
       OR EAX,EAX
       JNZ LOP1
LOP2:  POP AX
       CMP AL,10
       JB  LB
       ADD AL,7
LB:    ADD AL,30H
       MOV [ESI],AL        
       INC ESI
       LOOP LOP2
       POP EDX
       POP ECX
       RET

RADIX ENDP

END
