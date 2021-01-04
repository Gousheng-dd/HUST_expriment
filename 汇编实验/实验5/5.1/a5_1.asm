.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
CALREC   proto
SORT     proto
NUMTOSTR proto
NAMLEN   proto 

include      menuID.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

good	     struct
	     goodname  db  10 dup(0)
	     discount  db  0
	     buyprice  dw  0
	     selprice  dw  0
	     purchnum  dw  0
	     salenum   dw  0
	     recdeg    dw  0
good      ends

.data
ClassName    db       'TryWinClass',0
AppName      db       'Our First Window',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'I am EE1801,Mao Shilong',0
hInstance    dd       0
CommandLine  dd       0
ga1	     good  <'PEN',10,35,56,70,25,?>
ga2	     good  <'BOOK',9,12,30,25,5,?>
ga3	     good  <'BAG',8,50,90,10,2,?>
ga4	     good  <'COLA',5,2,10,30,10,?>
ga5	     good  <'SODA',9,10,35,50,5,?>
ganum EQU $-ga5
gat          good  <>
N equ 5
temstr       db 10 DUP(0)
slen         db 0   

msg_name     db       'name',0
msg_discount db       'discount',0
msg_buypr    db       'buying price',0
msg_selpr    db       'selling price',0
msg_purchnum db       'quantity of purchase',0
msg_salenum  db       'quantity of sale',0
msg_recdeg   db       'recommendation degree',0


menuItem     db       0  ;当前菜单状态, 1=处于list, 0=Clear

.code
Start:	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage, addr msg, NULL, 0, 0
	cmp    EAX, 0
	je     ExitLoop
	INVOKE TranslateMessage, addr msg
	INVOKE DispatchMessage, addr msg
	jmp    MsgLoop
	ExitLoop : mov    eax, msg.wParam
	ret
	WinMain      endp

	WndProc      proc   hWnd : DWORD, uMsg : DWORD, wParam : DWORD, lParam : DWORD
	LOCAL  hdc : HDC
	LOCAL  ps : PAINTSTRUCT
	.IF     uMsg == WM_DESTROY
	invoke PostQuitMessage, NULL
	.ELSEIF uMsg == WM_KEYDOWN
	.IF     wParam == VK_F1
	;; your code
	.ENDIF
	.ELSEIF uMsg == WM_COMMAND
	.IF     wParam == IDM_FILE_EXIT
	invoke SendMessage, hWnd, WM_CLOSE, 0, 0
	.ELSEIF wParam == IDM_ACTION_REC
		    invoke CALREC
		    invoke InvalidateRect,hWnd,0,1  ;擦除整个客户区
		    invoke UpdateWindow, hWnd
	    .ELSEIF wParam == IDM_ACTION_LIST
		    mov menuItem, 1
		    invoke InvalidateRect,hWnd,0,1  ;擦除整个客户区
		    invoke UpdateWindow, hWnd
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSEIF uMsg == WM_PAINT
             invoke BeginPaint,hWnd, addr ps
             mov hdc,eax
	     .IF menuItem == 1
		 invoke Display,hdc
	     .ENDIF
	     invoke EndPaint,hWnd,addr ps
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display      proc   hdc:HDC
             XX     equ  10
             YY     equ  10
	     XX_GAP equ  150
	     YY_GAP equ  30
	     
	     invoke SORT
	     
             invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_name,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_discount,8
             invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_buypr,12
             invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_selpr,13
             invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_purchnum,20
             invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_salenum,16
             invoke TextOut,hdc,XX+6*XX_GAP,YY+0*YY_GAP,offset msg_recdeg,21
             ;;
             ;商品1 
             mov ebx,offset ga1
	     call NAMLEN
             invoke TextOut,hdc,XX+0*XX_GAP,YY+1*YY_GAP,offset temstr,slen
             mov al,ga1.discount
             movzx eax,al
             call NUMTOSTR
             invoke TextOut,hdc,XX+1*XX_GAP,YY+1*YY_GAP,offset temstr,slen
             mov eax,0
	     mov ax,ga1.buyprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+2*XX_GAP,YY+1*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga1.selprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+3*XX_GAP,YY+1*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga1.purchnum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+4*XX_GAP,YY+1*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga1.salenum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+5*XX_GAP,YY+1*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga1.recdeg
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+6*XX_GAP,YY+1*YY_GAP,offset temstr,slen
             ;商品2
             mov ebx,offset ga2
	     call NAMLEN
             invoke TextOut,hdc,XX+0*XX_GAP,YY+2*YY_GAP,offset temstr,slen
             mov al,ga2.discount
             movzx eax,al
             call NUMTOSTR
             invoke TextOut,hdc,XX+1*XX_GAP,YY+2*YY_GAP,offset temstr,slen
             mov eax,0
	     mov ax,ga2.buyprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+2*XX_GAP,YY+2*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga2.selprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+3*XX_GAP,YY+2*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga2.purchnum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+4*XX_GAP,YY+2*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga2.salenum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+5*XX_GAP,YY+2*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga2.recdeg
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+6*XX_GAP,YY+2*YY_GAP,offset temstr,slen
             ;商品3
             mov ebx,offset ga3
	     call NAMLEN
             invoke TextOut,hdc,XX+0*XX_GAP,YY+3*YY_GAP,offset temstr,slen
             mov al,ga3.discount
             movzx eax,al
             call NUMTOSTR
             invoke TextOut,hdc,XX+1*XX_GAP,YY+3*YY_GAP,offset temstr,slen
             mov eax,0
	     mov ax,ga3.buyprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+2*XX_GAP,YY+3*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga3.selprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+3*XX_GAP,YY+3*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga3.purchnum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+4*XX_GAP,YY+3*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga3.salenum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+5*XX_GAP,YY+3*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga3.recdeg
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+6*XX_GAP,YY+3*YY_GAP,offset temstr,slen
             ;商品4
             mov ebx,offset ga4
	     call NAMLEN
             invoke TextOut,hdc,XX+0*XX_GAP,YY+4*YY_GAP,offset temstr,slen
             mov al,ga4.discount
             movzx eax,al
             call NUMTOSTR
             invoke TextOut,hdc,XX+1*XX_GAP,YY+4*YY_GAP,offset temstr,slen
             mov eax,0
	     mov ax,ga4.buyprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+2*XX_GAP,YY+4*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga4.selprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+3*XX_GAP,YY+4*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga4.purchnum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+4*XX_GAP,YY+4*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga4.salenum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+5*XX_GAP,YY+4*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga4.recdeg
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+6*XX_GAP,YY+4*YY_GAP,offset temstr,slen
             ;商品5
             mov ebx,offset ga5
	     call NAMLEN
             invoke TextOut,hdc,XX+0*XX_GAP,YY+5*YY_GAP,offset temstr,slen
             mov al,ga5.discount
             movzx eax,al
             call NUMTOSTR
             invoke TextOut,hdc,XX+1*XX_GAP,YY+5*YY_GAP,offset temstr,slen
             mov eax,0
	     mov ax,ga5.buyprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+2*XX_GAP,YY+5*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga5.selprice
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+3*XX_GAP,YY+5*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga5.purchnum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+4*XX_GAP,YY+5*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga5.salenum
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+5*XX_GAP,YY+5*YY_GAP,offset temstr,slen
             mov eax,0
             mov ax,ga5.recdeg
             movzx eax,ax
             call NUMTOSTR
             invoke TextOut,hdc,XX+6*XX_GAP,YY+5*YY_GAP,offset temstr,slen
             
             ret
Display      endp

CALREC          proc
	push ax
	push ebx
	push cx
	push dx
	push si
	push di
	mov cx,0
    mov ebx,0
	mov ebx,offset ga1
	
LOOPI:	movzx ax,(good ptr [ebx]).discount
	mul word ptr (good ptr [ebx]).selprice
	mov si,ax
	mov ax,1280
	mul (good ptr [ebx]).buyprice
	div si
	mov (good ptr [ebx]).recdeg,ax
	mov di,dx
	
	mov ax,64
	mul (good ptr [ebx]).salenum
	div (good ptr [ebx]).purchnum
	add dx,di
	jnc NAD1
	inc ax
NAD1:	add (good ptr [ebx]).recdeg,ax
	
	inc cx
	add ebx,ganum
	cmp cx,N
	jb LOOPI
	pop di
	pop si
	pop dx
	pop cx
	pop ebx
	pop ax
	ret

CALREC endp

NAMLEN          proc
	push ax
        push cx
	push ebx
	push edi
        push esi

	push ebx
	lea ebx, temstr
	mov esi, 0
LOOPJ:  mov byte ptr[ebx + esi], 0
	inc esi
	cmp esi, 10
	jb LOOPJ
	pop ebx

	mov cx,0
	lea edi,temstr
LOOPF:	cmp byte ptr [ebx],0
	je EXIT
	mov al,[ebx]
	mov [edi],al
	inc cx
	inc edi
	inc ebx
	jmp LOOPF
	
EXIT:	mov slen,cl
	pop esi
	pop edi
	pop ebx
	pop cx
        pop ax
	ret

NAMLEN endp

NUMTOSTR        proc
	push eax
	push ebx
	push ecx
	push dx
	push esi
	
	lea ebx,temstr
	mov esi,0
LOOPG:  mov byte ptr [ebx+esi],0
        inc esi
        cmp esi,10
        jb  LOOPG	
	
	mov ebx,10
	lea esi,temstr
	xor ecx,ecx
LOP1:   xor dx,dx
        div ebx
        push dx
        inc cx
        or eax,eax
        jnz LOP1
        mov slen,cl
        
LOP2:   pop ax
	add al,30h
	mov [esi],al
	inc esi
	loop LOP2
	
	pop esi
	pop dx
	pop ecx
	pop ebx
	pop eax 
	ret

NUMTOSTR endp

SORT         proc
	push ax
	push ebx
	push cx
	push dx
	push esi
	push edi
	
	mov ax,0
LOOPA:	mov cx,ax
        inc cx
LOOPC:  mov ebx,0
        mov esi,0
	mov ebx,offset ga1
        mov si,ganum
        imul si,ax
        movzx esi,si
	add esi,ebx
	mov dx,(good ptr [esi]).recdeg
	
	mov di,ganum
	imul di,cx
	movzx edi,di
	add edi,ebx
	cmp dx,(good ptr [edi]).recdeg
	ja  GRE
	mov dx,0
LOOPB:	push ax
	mov al,[esi]
	mov ah,[edi]
	mov [edi],al
	mov [esi],ah
	pop ax
	inc esi
	inc edi
	inc dx
	cmp dx,ganum
	jb  LOOPB
	
GRE:  	inc cx
        cmp cx,N
        jb  LOOPC
        
        inc ax
        cmp ax,N-1
        jb  LOOPA
        
	pop edi
	pop esi
	pop dx
	pop cx
	pop ebx
	pop ax 
	ret

SORT endp        
             end  Start
             