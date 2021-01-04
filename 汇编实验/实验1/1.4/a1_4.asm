.386
STACK SEGMENT USE16 STACK
      DB 200 DUP(0)
STACK ENDS

DATA SEGMENT USE16
BNAME DB 'MAOSHILON',0;老板姓名
BPASS DB 'ABCD',0;密码
AUTH DB 0;当前登录状态，0表示客户状态，1表示老板状态
GOOD DW 0;当前浏览商品地址
N EQU 30;商品种类
SNAME DB 'SHOP',0;店铺名称
GA1 DB 'PEN',7 DUP(0),10;商品名称及折扣
    DW 35,56,70,25,?;推荐度还未计算
GANUM EQU $-GA1
GA2 DB 'BOOK',6 DUP(0),9;商品名称及折扣
    DW 12,30,25,5,?;推荐度还未计算
GAN DB N-2 DUP('TempValue',0,8,15,0,20,0,30,0,2,0,?,?);除了2个已经具体定义了的商品信息以外，其他商品信息暂时假定为一样的。
IN_NAME DB 10
        DB ?
        DB 10 DUP(0);输入账户缓冲区
IN_PWD DB 7
       DB ?
       DB 7 DUP(0);输入密码缓冲区
IN_GOOD DB 10
        DB ?
        DB 10 DUP(0);输入商品名称缓冲区
        
POS  DW 0;存放功能四调用前地址

CSF  DB 4 DUP(0),'H',0AH,0DH,'$';存放代码段首址的十六进制表示
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

TABLE DW L1,L2,L3,L4,L5,L6,L7,L8,L9;各功能标号地址表
DATA ENDS

CODE SEGMENT USE16
     ASSUME CS:CODE,DS:DATA,SS:STACK
START: MOV AX,DATA
       MOV DS,AX
MAIN:  LEA DX,CRLF
       MOV AH,9
       INT 21H
       LEA DX,NOT9
       MOV AH,9
       INT 21H
       CMP AUTH,1
       JE  BO
       JMP CUS
BO:    MOV BYTE PTR BNAME+9,'$'
       LEA DX,BNAME
       MOV AH,9
       INT 21H
       LEA DX,CRLF
       MOV AH,9
       INT 21H
       MOV BYTE PTR BNAME+9,0
       JMP N1
CUS:   LEA DX,NOT11    
       MOV AH,9
       INT 21H 
N1:    LEA DX,NOT10
       MOV AH,9
       INT 21H
       
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
       
N3:    LEA DX,CRLF
       MOV AH,9
       INT 21H
                          
       LEA DX,NOT1
       MOV AH,9
       INT 21H;输出主界面
       MOV AH,1
       INT 21H
       SUB AL,30H
       MOVZX ESI,AL 
       SUB ESI,1
       CMP ESI,9
       JA  L0
       JMP WORD PTR TABLE[ESI*2]
       
L0:    LEA DX,NOT4
       MOV AH,9
       INT 21H
       JMP MAIN
          
L1:    LEA DX,NOT2
       MOV AH,9
       INT 21H
       LEA DX,IN_NAME
       MOV AH,10
       INT 21H
       CMP IN_NAME+1,0;只输入回车
       JE  SAU0
       LEA DX,NOT3
       MOV AH,9
       INT 21H
       LEA DX,IN_PWD
       MOV AH,10
       INT 21H
       ;比较姓名
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
       ;比较密码
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
       JMP MAIN
        
SAU1:  MOV AUTH,1
       JMP MAIN

L2:    MOV GOOD,0
       LEA DX,NOT6
       MOV AH,9
       INT 21H
       LEA DX,IN_GOOD
       MOV AH,10
       INT 21H
       ;查找商品
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
       JE  SPOS
       JMP LOOPF
       
NEXTA: INC CX
       ADD BX,GANUM
       CMP CX,N
       JB  LOOPC
       LEA DX,NOT7
       MOV AH,9
       INT 21H
       LEA DX,CRLF
       MOV AH,9
       INT 21H
       JMP MAIN
       
SPOS:  MOV GOOD,BX
       JMP MAIN
       
L3:    CMP GOOD,0
       JE  UNVA
       MOV BX,GOOD
       MOV AX,15[BX]
       MOV CX,17[BX]
       CMP AX,CX
       JBE UNVA
       ADD BYTE PTR 17[BX],1
       JMP L4
       MOV POS,SEL
SEL:   JMP MAIN   

UNVA:  LEA DX,NOT8
       MOV AH,9
       INT 21H
       LEA DX,CRLF
       MOV AH,9
       INT 21H
       JMP MAIN

L4:    MOV CX,0
       MOV BX,OFFSET GA1
       
LOOPG: MOVZX AX,BYTE PTR 10[BX]
       MUL WORD PTR 13[BX]
       MOV SI,AX
       MOV AX,1280
       MUL WORD PTR 11[BX]
       DIV SI
       MOV SI,AX
       MOV DI,DX
       
       MOV AX,64
       MUL WORD PTR 17[BX]
       DIV WORD PTR 15[BX]
       ADD AX,SI
       ADD DX,DI
       JNC NAD1
       INC AX
NAD1:  MOV 19[BX],AX
       
       INC CX
       ADD BX,GANUM
       CMP CX,N
       JB  LOOPG
       JMP POS 

L5:    JMP MAIN

L6:    JMP MAIN

L7:    JMP MAIN

L8:    MOV AX,CS
       MOV CX,0
       MOV BX,16
       MOV SI,OFFSET CSF
LOP1:  MOV DX,0
       DIV BX
       PUSH DX
       INC CX
       OR AX,AX
       JNZ LOP1
LOP2:  POP AX
       CMP AL,10
       JB  LB
       ADD AL,7
LB:    ADD AL,30H
       MOV [SI],AL        
       INC SI
       LOOP LOP2
       LEA DX,CRLF
       MOV AH,9
       INT 21H
       LEA DX,CSF
       MOV AH,9
       INT 21H
       JMP MAIN
       
L9:    LEA DX,NOT5
       MOV AH,9
       INT 21H
       MOV AH,4CH
       INT 21H
CODE   ENDS
       END START
