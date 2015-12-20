bits 64
section .text
global func

; 参考資料: http://d.hatena.ne.jp/eagletmt/20080712/1215841076
func:
		; スタックフレームの設定を行う
		push rbp              ; ベースポインタをスタックに積む
		mov  rbp,rsp          ; 現時点でのスタックポインタの位置をベースポインタに変更する

		; 関数の戻り値はraxレジスタに設定する必要がある
		mov  rbx,rdi      ; first parameter to function
        mov  rax,rbx          ; rbxをraxに格納する
		add  rax,1            ; raxを1インクリメントする

		; 戻り前のお決まり
		leave                 ; mov rsp,bsp  / pop ebpの２命令と同様
		ret

