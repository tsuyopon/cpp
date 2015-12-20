# -----------------------------------------------------------------------------
# A 64-bit program that displays its commandline arguments, one per line.
#
# On entry, %rdi will contain argc and %rsi will contain argv.
# -----------------------------------------------------------------------------

        .global main

        .text
main:
        # puts関数を利用する際に必要となるrdi, rsiレジスタの値をスタックに保存しておく
		# mainは最初にrdiがargcを含み、rsiがargvを含んでいます。
		# 呼び出し元や呼び出し側で何を保存しなければならないのかは呼出規約に準ずる。(x86 Linuxでは第１引数=rdi、第２引数=rsiなど)
        push    %rdi                    # save registers that puts uses
        push    %rsi

		# スタックポインタから(低位に)8byte(64bit)分はripを格納する。
        sub     $8, %rsp                # must align stack before call

		# rsiの値をrdiレジスタに保存する。 第１引数はrdiに入れなければならない規約に準ずる
		# 間接参照する場合、GASだと中括弧()で囲み、NASMだと[]で囲みます。
        mov     (%rsi), %rdi            # the argument string to display

		# puts関数を呼び出します(参考: https://linuxjm.osdn.jp/html/LDP_man-pages/man3/putc.3.html)
        call    puts                    # print it

		# 先ほどsubをした分をもどします
        add     $8, %rsp                # restore %rsp to pre-aligned value

		# スタックはLIFOなので、pushで最後に入れたものから順番にレジスタにもどします
        pop     %rsi                    # restore registers puts used
        pop     %rdi

		# argvを含むrsiを8byte(64bit)移動して次の引数への値を指し示すようにする
        add     $8, %rsi                # point to next argument

		# argcを減算する
        dec     %rdi                    # count down

		# ZFフラグがセットされていない(ZF=0)場合に指定されたmainにジャンプします
		# decでrdiをカウントダウンした際にrdiが0になればZF=1となる。
        jnz     main                    # if not done counting keep going

        ret

