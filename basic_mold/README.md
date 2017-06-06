# 概要
型について
キャスト変換については../c++cast/を参考のこと(こちらにも型変換周りのプログラムがある)

# 詳細
https://ja.wikipedia.org/wiki/%E6%95%B4%E6%95%B0%E5%9E%8B

```
ssize_t	%zd
size_t	%zu
int_max_t	%jd
intmax_t	%ju
signed char	%hhd
unsigned char	%hhu
short int	%%hd
unsigned short int	%hu
int	%d
unsigned int	%u
long int	%ld
unsigned long int	%lu
long long int	%lld
unsigned long long int	%llu
```


linuxでは以下のinttype.hをincludeでして__STDC_FORMAT_MACROSを定義しておけば
さらに以下の書式がつかえるようになる。マクロのため実際は上記と同等なものが定義されている
```
int32_t	%PRId32
uint32_t	%PRIu32
int64_t	%PRId64
uint64_t	%PRIu64
```


さらに以下の書式がつかえるようになる。

```
#include
#define __STDC_FORMAT_MACROS

int32_t %PRId32
uint32_t %PRIu32
int64_t %PRId64
uint64_t %PRIu64
```
