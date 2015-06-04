rem 足切り、指数関数的な増幅モードで増幅を行います

pushd "%0\.."

torch4microscopic.exe -i "%1" -o "%1_normalized" --amp_mode exp --cutback --unitsize_depth 0.2988970588 --gaussian --window_size 5

exit