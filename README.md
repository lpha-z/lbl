lbl - header only C++17 fixed width integer library
===================================================

## What is this / これはなに

This library provides `N` bits unsigned integer types (std::uint *N* \_t compatible) and `N` bits signed integer types (values are represented using 2's complement, std::int *N* \_t compatible).

このライブラリは、`N`ビットの符号なし整数型（std::uint *N* \_tと互換性があります）と`N`ビットの符号あり整数型（値は二の補数で表現されます。std::int *N* \_tと互換性があります）を提供します。

## Usage / 使い方

```c++
#include "lbl/xintN_t.hpp"
int main() {
    using namespace lbl;
    uintN_t<36> x { 1ull << 35 };
    intN_t<31>  y { 32 - 999 * 999 * 999 };
    uintN_t<13> a = 0;
    intN_t<42>  b = ~0ull >> 40
    if( b ) {
        uint64_t c = a;
        int64_t  d = b;
    }
    return 0;
}
```

## Specification

### Undefined behavior

#### Bit shift operators

* The behavior is undefined if the right operand is greater than or equal to the bit width of the left operand.
* The behavior is undefined if the right operand is negative.

#### Divide and Reminder operators

* The behavior is undefined if the right operand is zero (divide by zero).

#### The other operations

* The behavior is **NOT** undefined even if overflow occur (unlike std::int *N* \_t). For example, `intN_t<3>(3) + intN_t<3>(3) == intN_t<3>(-2)` and `intN_t<3>(-4) / intN_t<3>(-1) == intN_t<3>(-4)`.

### Implementation-defined behavior

* Right shift of `intN_t<N>` is arithmetic right shift.

## 仕様

### 未定義動作

#### ビットシフト演算子

* 右オペランドの値が左オペランドのビット幅以上の時、動作は未定義です。
* 右オペランドの値が負の時、動作は未定義です。

#### 除算演算子と剰余演算子

* 右オペランドの値が0の時、つまり零除算を行った時、動作は未定義です。

#### その他の演算

* 値がその型で表せないとき、つまりオーバーフローした時でも、動作は未定義と**なりません**（std::int *N* \_tと異なります）。例えば、`intN_t<3>(3) + intN_t<3>(3) == intN_t<3>(-2)`や`intN_t<3>(-4) / intN_t<3>(-1) == intN_t<3>(-4)`などです。

### 処理系定義動作

* `intN_t<N>`の右シフトは、算術右シフトとなります。
