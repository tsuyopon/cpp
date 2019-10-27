# 概要
C++11からはtemplateで可変長引数を使える様になりました。

可変長引数を受けとるテンプレートは次の様に"..."を使うことで定義できます。
```
// 可変長引数の書式
template <typename... Arguments>
int fname(Arguments... args);
```

# 参考資料
- https://docs.microsoft.com/en-us/cpp/cpp/ellipses-and-variadic-templates?redirectedfrom=MSDN&view=vs-2019
