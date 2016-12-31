# 概要
enumについて

# 詳細
- defMumeiVar.c
 - 無名型enum {E1,E2}の変数としてEを定義している(無名型変数となる)
```
enum{E1,E2} E;
```
- defOnlyEnum.c
 - 無名型enum {E1,E2}を定義している。変数は定義していない。
```
enum {E1,E2};
```
- defTypeAndDefVar.c
 - 型Eとしてenum {E1,E2}を定義している。型Eとして変数a1を定義している。
```
enum E {E1,E2} a1;
```
- defType.c
 - 型Eとしてenum {E1,E2}を定義している。変数は定義していない。
```
enum E {E1,E2};
```
- typedefEnumMumeiVar.c
 - enum{E1,E2}のエイリアスとしてEを定義している。型Eではないので注意。
```
typedef enum{E1,E2} E;
```
- typedefEnumAndDefTypeAndDefVar.c
 - enum{E1,E2}の型としてEtypeを定義している。
 - enum{E1,E2}のエイリアスとしてEを定義している。
```
typedef enum Etype{E1,E2} E;
```
