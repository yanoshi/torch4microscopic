﻿========================================================================
    コンソール アプリケーション: torch4microscopic プロジェクトの概要
========================================================================

このファイルには、torch4microscopic アプリケーションを構成する各ファイルの内容の概要が含まれています。


torch4microscopic.vcxproj
    これは、アプリケーション ウィザードを使用して生成された VC++ プロジェクトのメイン プロジェクト ファイルです。ファイルを生成した Visual C++ のバージョンに関する情報と、アプリケーション ウィザードで選択されたプラットフォーム、構成、およびプロジェクト機能に関する情報が含まれています。

torch4microscopic.vcxproj.filters
    これは、アプリケーション ウィザードで生成された VC++ プロジェクトのフィルター ファイルです。このファイルには、プロジェクト内のファイルとフィルターとの間の関連付けに関する情報が含まれています。この関連付けは、特定のノードで同様の拡張子を持つファイルのグループ化を示すために IDE で使用されます (たとえば、".cpp" ファイルは "ソース ファイル" フィルターに関連付けられています)。

torch4microscopic.cpp
    これは、メインのアプリケーション ソース ファイルです。

image_io.cpp
	画像ファイルからcv::Matオブジェクトを作成するための静的メソッド群。

mat_converter.cpp
	減衰やノイズ等を除去する処理を行うクラスMatConverterが記述されている。

parameters.h
	パラメータ用の列挙型等が記述されている。
