rem 足切り、通常モードで増幅を行います

pushd %0\..

torch4microscopic.exe -i "%1" -o "%1_normalized" --amp_mode simple --cutback --gaussian --window_size 5

pause