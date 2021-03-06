#pragma once

//OpenCV用インクルード文
//インクルードファイル指定
#include <opencv2/opencv.hpp>
//静的リンクライブラリの指定
#include <opencv2/opencv_lib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace parameters
{


	//各画像の明るさを平滑化する際のモード
	enum class NormalizeMode
	{
		//何もしません
		None,
		//最もシンプルな方法を利用。各画像毎に最大輝度点を最大値に、最低輝度点を最小値に持っていく。
		Simple,
		//線形的に明るさは減衰するはずなので、それを利用して平滑化
		ExpDamping
	};

	/*
	//足切の方法
	enum class CutbackMode
	{
		//パーセンテージで足切
		Relative,
		//絶対値で足切
		Absolute,
		//最低値を切る
		CutLowest,
		//最低値から何割かを切る
		CutLowerByPersent
	};
	*/


	class Values
	{
	public:
		double unitsize_depth;
		bool enable_cutback;
		cv::Size window_size;
		bool enable_gblur;
		NormalizeMode normalize_mode;

		Values()
		{
			unitsize_depth = 0.0;
			enable_cutback = false;
			enable_gblur = false;
			window_size = cv::Size(5, 5);
			normalize_mode = NormalizeMode::None;
		}
	};

	
}