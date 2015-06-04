#include "mat_converter.h"

using namespace cv;
using namespace std;

MatConverter::MatConverter(std::shared_ptr<std::vector<cv::Mat>> input, parameters::Values values)
{
	this->input_obj = input;
	this->param_values = values;
}

std::shared_ptr<std::vector<cv::Mat>> MatConverter::get_result()
{
	std::shared_ptr<vector<Mat>> return_obj(new vector<Mat>());

	double val_min_lowest = (double)(2 ^ 16);
	double val_min_highest = (double)(2 ^ 16);

	double val_max = 0;

	if (this->param_values.enable_cutback)
	{
		for (int i = 0; i < this->input_obj->size(); i++)
		{
			double temp_min, temp_max;
			Point point_min, point_max;
			cv::minMaxLoc(this->input_obj->at(i), &temp_min, &temp_max, &point_min, &point_max);

			if (val_min_lowest > temp_min)
				val_min_lowest = temp_min;

			if (val_min_highest == (double)(2 ^ 16))
				val_min_highest = temp_min;
			else if (val_min_highest < temp_min)
				val_min_highest = temp_min;

			if (val_max < temp_max)
				val_max = temp_max;
		}
	}


	for (int i = 0; i < this->input_obj->size(); i++)
	{
		Mat mat_obj;

		int img_height = input_obj->at(i).size().height;
		int img_width = input_obj->at(i).size().width;


		//足切り処理
		if (this->param_values.enable_cutback)
		{
			mat_obj = this->input_obj->at(i) - val_min_highest;
		}
		else{
			mat_obj = Mat(this->input_obj->at(i));
		}




		//平均化処理
		switch (this->param_values.normalize_mode)
		{
		case parameters::NormalizeMode::None:
			//何もしない時の処理
			break;
			
		case parameters::NormalizeMode::Simple:
			//各画像の最大値と最小値で足切り
			mat_obj = mat_obj * (65536.0 / (val_max - val_min_highest));
			break;
			

		case parameters::NormalizeMode::ExpDamping:
			//指数関数的に減衰する
			//今のところ、200umで1/10と考えて計算
			double depth = i * param_values.unitsize_depth;
			mat_obj = mat_obj * (1 / pow(10.0, depth / 200.0));

			break;
		}


		//ガウシアンフィルタ
		if (this->param_values.enable_gblur)
		{
			GaussianBlur(mat_obj, mat_obj, this->param_values.window_size, 0);
		}

		return_obj->push_back(mat_obj);
	}

	return return_obj;
}