;MAOSHILONG
;FUN1,FUN2,FUN3,FUN4,FUN5,FUN7,FUN8,FUN9,RADIX

EXTRN DISP:NEAR,FUN6:FAR
PUBLIC FUN4,RADIX,AUTH,GOOD,CRLF

.386
;�궨��
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

STACK SEGMENT USE16  PARA STACK 'STACK'
      DB 200 DUP(0)
STACK ENDS

STACKBAK SEGMENT USE16 STACK
      DB 400 DUP(0)
STACKBAK ENDS

DATA SEGMENT USE16 PARA PUBLIC 'DATA'
BNAME DB 'MAOSHILON',0;�ϰ�����
BPASS DB 'ABCD',0;����
AUTH DB 0;��ǰ��¼״̬��0��ʾ�ͻ�״̬��1��ʾ�ϰ�״̬
GOOD DW 0;��ǰ�����Ʒ��ַ
N EQU 30;��Ʒ����
SNAME DB 'SHOP',0;��������
GA1 DB 'PEN',7 DUP(0),10;��Ʒ���Ƽ��ۿ�
    DW 35,56,70,25,?;�Ƽ��Ȼ�δ����
GANUM EQU $-GA1
GA2 DB 'BOOK',6 DUP(0),9;��Ʒ���Ƽ��ۿ�
    DW 12,30,25,5,?;�Ƽ��Ȼ�δ����
GAN DB N-2 DUP('TempValue',0,8,15,0,20,0,30,0,2,0,?,?);����2���Ѿ����嶨���˵���Ʒ��Ϣ���⣬������Ʒ��Ϣ��ʱ�ٶ�Ϊһ���ġ�
IN_NAME DB 10
        DB ?
        DB 10 DUP(0);�����˻�������
IN_PWD DB 7
       DB ?
       DB 7 DUP(0);�������뻺����
IN_GOOD DB 10
        DB ?
        DB 10 DUP(0);������Ʒ���ƻ����� 

CSF  DB 4 DUP(0),'H',0AH,0DH,'$';��Ŵ������ַ��ʮ�����Ʊ�ʾ
NOT9 DB 'WELCOME!',0AH,0DH
     DB 'Current user name:','$'
NOT11 DB 'Customer',0AH,0DH,'$'
NOT10 DB 'Current browsing product name:','$'
NOT1 DB 'Please put in your command:',0AH,0DH
     DB '1.LOGIN                 2.SEARCH GOODS',0AH,0DH
     DB '3.ORDER GOODS           4.CALCULATE POP',0AH,0DH
     DB '5.RANK                  6.CHANGE INFORMATION',0AH,0DH
     DB '7.CHANGE ENVIRONMENT    8.PRINT CS',0AH,0DH
     DB '9.QUIT',0AH,0DH,'$'
NOT2 DB 'Please put in your name:',0AH,0DH,'$'
NOT3 DB 'Please put in your password:',0AH,0DH,'$'
NOT4 DB 'Please put in number form 1 to 9!',0AH,0DH,'$'
NOT5 DB 'Thanks for your use!',0AH,0DH,'$'
NOT6 DB 'Please put in the name of goods',0AH,0DH,'$'
NOT7 DB 'There is no result',0AH,0DH,'$'
NOT8 DB 'Sorry,you can not buy it ',0AH,0DH,'$'
CRLF DB 0AH,0DH,'$'

TABLE DW L1,L2,L3,L4,L5,L6,L7,L8,L9;�����ܱ�ŵ�ַ��

DATA ENDS

CODE SEGMENT USE16 PARA PUBLIC  'CODE'
     ASSUME CS:CODE,DS:DATA,SS:STACK

     COUNT DB 18;���δ𡯼���
     SEC   DB ?,?;��ASCII��
     OLD_INT DW 0,0;�洢��INT 08H�ж�ʸ��
     CHSE DW 3031H;����Ϊÿ���ӵĵ�һ��Ǩ��
     NOST DB 1;��¼��ǰ���ջλ�ã�1��ʾSTACK��0��ʾSTACKBAK

NEW08H PROC FAR
       PUSHF
       CALL DWORD PTR CS:OLD_INT
       DEC  CS:COUNT
       JZ   DIS
       IRET
DIS:   MOV CS:COUNT,18
       STI
       PUSHA
       MOV AL,0
       OUT 70H,AL
       JMP $+2
       IN  AL,71H
       MOV AH,AL
       AND AL,0FH
       SHR AH,4
       ADD AX,3030H
       XCHG AH,AL
       MOV  WORD PTR CS:SEC,AX
       CMP AX,CS:CHSE
       JNZ QT
       
       CLI
       CMP CS:NOST,1
       JE  ITOB
       MOV AX,STACK
       MOV ES,AX
       MOV EAX,0
LOOPQ: MOV BL,SS:[EAX]
       MOV ES:[EAX],BL
       INC EAX
       CMP EAX,400
       JNZ LOOPQ
       
       MOV AX,STACK
       MOV SS,AX
       MOV CS:NOST,1
       JMP QT
       
ITOB:  MOV AX,STACKBAK
       MOV ES,AX
       MOV EAX,0
LOOPP: MOV BL,SS:[EAX]
       MOV ES:[EAX],BL
       INC EAX
       CMP EAX,400
       JNZ LOOPP
       
       MOV AX,STACKBAK
       MOV SS,AX
       MOV CS:NOST,0
       
QT:    STI 
                    
       POPA
       IRET
NEW08H ENDP

FUN1 PROC

       PUSH SI
       PUSH DI
       PUSH AX
       PUSH DX
       WRITE NOT2
       READ IN_NAME
       CMP IN_NAME+1,0;ֻ����س�
       JE  SAU0
       WRITE NOT3
       READ IN_PWD
       ;�Ƚ�����
       MOVZX SI,IN_NAME+1
       MOV DI,SI
       ADD DI,2
       CMP BYTE PTR BNAME[SI],0
       JNE SAU0
       
LOOPA: MOV AL,IN_NAME-1[DI]
       CMP AL,BNAME-1[SI]
       JNE SAU0
       DEC DI
       DEC SI
       JNE LOOPA
       ;�Ƚ�����
       MOVZX SI,IN_PWD+1
       MOV DI,SI
       ADD DI,2
       CMP BYTE PTR BPASS[SI],0
       JNE SAU0
       
LOOPB: MOV AL,IN_PWD-1[DI]
       CMP AL,BPASS-1[SI]
       JNE SAU0
       DEC DI
       DEC SI
       JE  SAU1
       JMP LOOPB
       
SAU0:  MOV AUTH,0
       POP DX
       POP AX
       POP DI
       POP SI
       RET
       
SAU1:  MOV AUTH,1
       POP DX
       POP AX
       POP DI
       POP SI
       RET

FUN1 ENDP

FUN2 PROC
	
       PUSH EAX
       PUSH EBX
       PUSH CX
       PUSH EDX
       PUSH SI
       PUSH DI
       MOV GOOD,0
       WRITE NOT6
       READ IN_GOOD
       ;������Ʒ
       MOV CX,0
       MOV BX,OFFSET GA1
LOOPC: MOVZX SI,IN_GOOD+1
       MOV DI,SI
       ADD DI,2
       CMP BYTE PTR [BX+SI],0
       JNE NEXTA
LOOPF: MOV AL,IN_GOOD-1[DI]
       CMP AL,[BX+SI-1]
       JNE NEXTA
       DEC DI
       DEC SI
       JNE LOOPF
       CALL DISP
       POP DI
       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET
       
NEXTA: INC CX
       ADD BX,GANUM
       CMP CX,N
       JB  LOOPC
       WRITE NOT7
       WRITE CRLF
       POP DI
       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET
       
FUN2 ENDP

FUN3 PROC
	
       PUSH AX
       PUSH BX
       PUSH DX
       CMP GOOD,0
       JE  UNVA
       MOV BX,GOOD
       MOV AX,15[BX]
       CMP AX,17[BX]
       JBE UNVA
       ADD BYTE PTR 17[BX],1
       CALL FUN4
       POP DX
       POP BX
       POP AX
       RET

UNVA:  WRITE NOT8
       WRITE CRLF
       POP DX
       POP BX
       POP AX
       RET
       
FUN3 ENDP

FUN4 PROC
	
       PUSH AX
       PUSH BX
       PUSH CX
       PUSH DX
       PUSH SI
       PUSH DI
       MOV CX,0
       MOV BX,OFFSET GA1
       
LOOPG: MOVZX AX,BYTE PTR 10[BX]
       MUL WORD PTR 13[BX]
       MOV SI,AX
       MOV AX,1280
       MUL WORD PTR 11[BX]
       DIV SI
       MOV 19[BX],AX
       MOV DI,DX
       
       MOV AX,64
       MUL WORD PTR 17[BX]
       DIV WORD PTR 15[BX]
       ADD DX,DI
       JNC NAD1
       INC AX
NAD1:  ADD 19[BX],AX
       
       INC CX
       ADD BX,GANUM
       CMP CX,N
       JB  LOOPG
       POP DI
       POP SI
       POP DX
       POP CX
       POP BX
       POP AX
       RET

FUN4 ENDP

FUN5 PROC
	
	JMP MAIN
	RET

FUN5 ENDP

FUN7 PROC
	
	PUSH EAX
	PUSH DS
	PUSH BX
	PUSH DX
	PUSH ES
	
	PUSH CS
	POP DS 
	MOV EAX,DWORD PTR OLD_INT
	CMP EAX,0
	JNE  RT
	MOV AX,3508H
	INT 21H
	MOV OLD_INT,BX
	MOV OLD_INT+2,ES
	MOV DX,OFFSET NEW08H
	MOV AX,2508H
	INT 21H
	
RT:     POP ES
        POP DX
        POP BX
        POP DS
        POP EAX
	JMP MAIN
	RET

FUN7 ENDP

FUN8 PROC
	
       PUSH EAX
       PUSH EBX
       PUSH CX
       PUSH EDX
       PUSH SI
       MOV AX,SS
       MOVZX EAX,AX
       MOV EBX,16
       LEA SI,CSF
       CALL RADIX
       WRITE CRLF
       WRITE CSF
       POP SI
       POP EDX
       POP CX
       POP EBX
       POP EAX
       RET

FUN8 ENDP

FUN9 PROC
	
       PUSH EAX
       PUSH DX
       
       MOV EAX,DWORD PTR CS:OLD_INT
       CMP EAX,0
       JZ  QUIT
       LDS DX,DWORD PTR CS:OLD_INT
       MOV AX,2508H
       INT 21H
       MOV AX,DATA
       MOV DS,AX
       
QUIT:  WRITE NOT5
       MOV AH,4CH
       INT 21H
       PUSH DX
       PUSH EAX
       RET
       
FUN9 ENDP

RADIX PROC
	
       PUSH CX
       PUSH EDX
       XOR CX,CX
LOP1:  XOR DX,DX
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
       MOV [SI],AL        
       INC SI
       LOOP LOP2
       POP EDX
       POP CX
       RET

RADIX ENDP

START: MOV AX,DATA
       MOV DS,AX
MAIN:  WRITE CRLF
       WRITE NOT9
       CMP AUTH,1
       JE  BO
       JMP CUS
BO:    MOV BYTE PTR BNAME+9,'$'
       WRITE BNAME
       WRITE CRLF
       MOV BYTE PTR BNAME+9,0
       JMP N1
CUS:   WRITE NOT11    
N1:    WRITE NOT10
       
       CMP GOOD,0
       JE  N3
       MOV BX,GOOD
       MOV SI,0
LOOPH: CMP BYTE PTR [BX+SI],0
       JE  N2
       INC SI
       JMP LOOPH

N2:    MOV BYTE PTR [BX+SI],'$'
       MOV DX,BX
       MOV AH,9
       INT 21H
       MOV BYTE PTR [BX+SI],0
       
N3:    WRITE CRLF                  
       WRITE NOT1;���������
       MOV AH,1
       INT 21H
       SUB AL,30H
       MOVZX ESI,AL 
       SUB ESI,1
       CMP ESI,9
       JA  L0
       JMP WORD PTR TABLE[ESI*2]
       
L0:    WRITE NOT4
       JMP MAIN

L1:    CALL FUN1
       JMP MAIN         

L2:    CALL FUN2
       JMP MAIN
       
L3:    CALL FUN3
       JMP MAIN
       
L4:    CALL FUN4
       JMP MAIN

L5:    CALL FUN5
       JMP  MAIN

L6:    CALL FUN6
       JMP  MAIN

L7:    CALL FUN7
       JMP  MAIN

L8:    CALL FUN8
       JMP MAIN
       
L9:    CALL FUN9
       JMP  MAIN
CODE   ENDS
       END START
       
