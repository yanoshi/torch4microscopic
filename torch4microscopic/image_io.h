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

class ImageIO
{
public:
	//ファイルを開いてMatなVectorを返す
	static std::shared_ptr<std::vector<cv::Mat>> get_mats(std::string filename);

	//Matをファイルにセーブ
	static void save_mats(std::shared_ptr<std::vector<cv::Mat>> mats_obj, std::string filepath);

private:
	//画像ファイルよりMatを作成
	static cv::Mat get_mat_from_file(std::string filename);

	//画像ファイルに保存
	static void save_mat(cv::Mat mat_obj, std::string filename);
};