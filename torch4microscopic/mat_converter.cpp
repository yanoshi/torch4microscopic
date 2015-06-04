#include "mat_converter.h"

using namespace cv;
using namespace std;

MatConverter::MatConverter(std::shared_ptr<std::vector<cv::Mat>> input, parameters::NormalizeMode normalize_mode, bool cutback)
{
	this->input_obj = input;
	this->is_cutback = cutback;
	this->normalize_mode = normalize_mode;
}

std::shared_ptr<std::vector<cv::Mat>> MatConverter::get_result()
{
	std::shared_ptr<vector<Mat>> return_obj(new vector<Mat>());

	double val_min_lowest = (double)(2 ^ 16);
	double val_min_highest = (double)(2 ^ 16);

	double val_max = 0;

	if (this->is_cutback)
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


	for (int i = 0; this->input_obj->size(); i++)
	{
		Mat mat_obj;

		int img_height = input_obj->at(i).size().height;
		int img_width = input_obj->at(i).size().width;


		//���؂菈��
		if (this->is_cutback)
		{
			mat_obj = this->input_obj->at(i) - val_min_highest;
		}




		//���ω�����
		switch (this->normalize_mode)
		{
		case parameters::NormalizeMode::None:
			//�������Ȃ����̏���
			break;
			
		case parameters::NormalizeMode::Simple:
			//�e�摜�̍ő�l�ƍŏ��l�ő��؂�
			mat_obj = this->input_obj->at(i) * (65536.0 / (val_max - val_min_highest));
			break;
			

		case parameters::NormalizeMode::ExpDamping:
			//�w���֐��I�Ɍ�������
			//���̂Ƃ���A200um��1/10�ƍl���Čv�Z
			double depth = i * parameters::Values::unitsize_depth;
			mat_obj = mat_obj * (1 / pow(10.0, depth / 200.0));

			break;
		}

		return_obj->push_back(mat_obj);
	}

	return return_obj;
}