bits 64
section .text
global addfunc

addfunc:
		; スタックフレームの設定を行う
		push rbp              ; ベースポインタをスタックに積む
		mov  rbp,rsp          ; 現時点でのスタックポインタの位置をベースポインタに変更する

		; 関数の戻り値はraxレジスタに設定する必要がある
		mov  rax,0            ; raxを0で初期化する
		add  rax,rdi          ; 第１引数
		add  rax,rsi          ; 第２引数
		add  rax,rdx          ; 第３引数
		add  rax,rcx          ; 第４引数
		add  rax,r8           ; 第５引数
		add  rax,r9           ; 第６引数

		; 第7引数以降はスタックから取得する
		add  rax,[rbp+16]     ; 第７引数
		add  rax,[rbp+24]     ; 第８引数
		add  rax,[rbp+32]     ; 第９引数

		; 戻り前のお決まり
		leave                 ; mov rsp,bsp  / pop ebpの２命令と同様
		ret

