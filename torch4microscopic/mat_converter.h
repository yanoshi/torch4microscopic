//OpenCV用インクルード文
//インクルードファイル指定
#include <opencv2/opencv.hpp>
//静的リンクライブラリの指定
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
	parameters::NormalizeMode normalize_mode;
	bool is_cutback;


public:
	MatConverter(std::shared_ptr<std::vector<cv::Mat>> input, parameters::NormalizeMode normalize_mode, bool cutback);

	std::shared_ptr<std::vector<cv::Mat>> get_result();
};
