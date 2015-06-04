# これは何？

二光子顕微鏡から積層画像群(16bit Gray Scale TTF Files)を見やすい形に変換するやつです。

# コマンドラインオプション

## -i [directory path], --input [directory path]
入力画像群が格納されているディレクトリを指定する

## -o [directory path], --output [directory path]
出力先のディレクトリを指定する

## --amp_mode [mode name]
増幅モードを指定する

### mode names
- simple
 - 最大画素値が16bit整数型の最大値になるように増幅する
- exp
 - 観測点の深さに応じて指数関数的に減衰していると仮定し行う(200umで1/10になると仮定している)
 
## --cutback
最小画素値が0になるように各画素から減算を行う

## --unitsize_depth [double],-d [double]
画像1枚ごとに観測点が何um変化するかを指定する。
--amp_modeがexpの際に必須。

# その他
`convert_using_expmode.bat` か `convert_using_simplemode.bat` にフォルダを投げ込めば楽できます。

# License
MIT