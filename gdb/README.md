GDB
====
GDBを通したデバッギングについてまとめていきます

# 概要・設定
- [InlineFunction](InlineFunction)
  - inline関数に対してブレークポイントを貼りたい場合の方法について
- [ChangeMyFunctionReturnValue](ChangeMyFunctionReturnValue)
  - 自作関数の戻り値を変更したい場合の方法
- [ChangeLibraryFunctionReturnValue](ChangeLibraryFunctionReturnValue)
  - 標準ライブラリなどの戻り値を変更したい場合の方法
- [FunctionPointerCallbackCheck](FunctionPointerCallbackCheck)
  - 関数ポインタのコールバックがセットされるのを検知する方法について
- [FunctionOverload](FunctionOverload)
  - 関数のオーバーロード時に特定のブレークポイントを指定する方法について
- [MacroDebug](MacroDebug)
  - マクロ情報もgdbで表示したい場合のデバッグ方法について
- [ProgrammaticallyBreakpoint](ProgrammaticallyBreakpoint)
  - gdbのbではなく、プログラム的にその行に到達したらブレークポイントとして処理したい場合の方法について
- [TemplateBreakpoint](TemplateBreakpoint)
  - テンプレートを使った場合にブレークポイントを指定する方法について
- [TraceForkChildParent](TraceForkChildParent)
  - fork()をした後にchildを追跡したり、parentを追跡する方法について
- [CatchException](CatchException)
  - C++で例外を補足する方法について
- [StopAllThreadsExceptCurrentThread](StopAllThreadsExceptCurrentThread)
  - マルチスレッドプログラムにおいて、nextやcontinue時に勝手にスレッド間の稼働状態を変更しないようにする方法について(つまり、gdbデバッグ時は他のスレッドは完全に停止することになる)
- [IgnoreSigPipe](IgnoreSigPipe)
  - SIGPIPEをgdbが受け取ってもハングしないようにする方法について
- [JumpProgram](JumpProgram)
  - 特定の分岐をJMPする方法について
- [BatchMacro](BatchMacro)
  - gdbにバッチファイルを指定する方法について

