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

class ImageIO
{
public:
	//�t�@�C�����J����Mat��Vector��Ԃ�
	static std::shared_ptr<std::vector<cv::Mat>> get_mats(std::string filename);

	//Mat���t�@�C���ɃZ�[�u
	static void save_mats(std::shared_ptr<std::vector<cv::Mat>> mats_obj, std::string filepath);

private:
	//�摜�t�@�C�����Mat���쐬
	static cv::Mat get_mat_from_file(std::string filename);

	//�摜�t�@�C���ɕۑ�
	static void save_mat(cv::Mat mat_obj, std::string filename);
};