#include "image_io.h"

#include <boost/filesystem.hpp>

using namespace std;
using namespace cv;
using namespace boost;

std::shared_ptr<vector<Mat>> ImageIO::get_mats(string filepath)
{
	int count_z = 0;

	std::shared_ptr<vector<Mat>> return_obj(new vector<Mat>());


	//フォルダ検索(相変わらずboost先生は長い)
	boost::filesystem::path path = complete(filesystem::path(filepath, filesystem::native));
	boost::filesystem::directory_iterator end;
	for (filesystem::directory_iterator filenames(path); filenames != end; filenames++){
		
		string name = filenames->path().string();


#ifdef _DEBUG
		cout << count_z << endl;
#endif

		return_obj->push_back(ImageIO::get_mat_from_file(name));

		count_z++;
	}


	return return_obj;
}


Mat ImageIO::get_mat_from_file(string filename)
{
	Mat img_real = imread(filename, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	//-1はおまじない。
	// http://stackoverflow.com/questions/10969585/opencv-reading-a-16-bit-grayscale-image コチラいわく


	/*
	//表示
	namedWindow("Display window", WINDOW_AUTOSIZE);		// Create a window for display.
	imshow("Display window", new_image);                // Show our image inside it.

	waitKey(0);
	//*/

	return img_real;
}