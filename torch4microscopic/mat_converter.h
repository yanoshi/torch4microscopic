//OpenCV�p�C���N���[�h��
//�C���N���[�h�t�@�C���w��
#include <opencv2/opencv.hpp>
//�ÓI�����N���C�u�����̎w��
#include <opencv2/opencv_lib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <vector>
#include <memory>
#include <string>

#include "parameters.h"

class MatConverter
{
private:
	std::shared_ptr<std::vector<cv::Mat>> input_obj;
	parameters::Values param_values;


public:
	MatConverter(std::shared_ptr<std::vector<cv::Mat>> input, parameters::Values values);

	std::shared_ptr<std::vector<cv::Mat>> get_result();
};
