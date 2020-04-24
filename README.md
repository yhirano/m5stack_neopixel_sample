M5StackにNeoPixelをつなぐサンプル
==

M5StackにNeoPixelをつなぐサンプルです。

開発環境
--

* PlatformIO
* NeoPixelを制御するライブラリとして[FastLED](https://github.com/FastLED/FastLED)

使い方
--

1. ポートAに[NeoPixel](https://www.switch-science.com/catalog/5209/)をつなぐ
1. ポートBに[Angle Unit](https://m5stack.com/products/angle-unit)をつなぐ
1. 本リポジトリのプログラムを書き込む
1. ボタンA, B, Cのどれかを押しながらAngle Unitをまわす。RGBの値が指定できる。
1. 指定されたRGBの値にNeoPixelが光る
