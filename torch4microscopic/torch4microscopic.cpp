// torch4microscopic.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//


#include <iostream>
#include <vector>
#include <fstream>
#include <boost/program_options.hpp>

#include "parameters.h"
#include "image_io.h"

using namespace std;
using namespace cv;
using namespace boost::program_options;

int main(int argc, char* argv[])
{
	//オプション定義
	options_description inout_options("path setting");
	options_description calc_options("calculation option");

	inout_options.add_options()
		("input,i", value<string>(), "input path")
		("output,o", value<string>(), "output path");

	calc_options.add_options()
		("amp_exp", "enable amplifier (exponential growth method)")
		("cutback", "enable subtraction for cutback (average lowest pixel)");

	variables_map cmd_values;

	//各パラメータ情報を格納する変数
	parameters::NormalizeMode normalize_mode;
	bool is_cutback;
	string input_src, output_src;


	try 
	{
		options_description option_marged("");
		option_marged.add(inout_options).add(calc_options);


		store(parse_command_line(argc, argv, option_marged), cmd_values);
		notify(cmd_values);


		if (!(cmd_values.count("input") && cmd_values.count("output")))
		{
			cout << option_marged << endl;
			exit(0);
		}
		else
		{
			input_src = cmd_values["input"].as<string>();
			output_src = cmd_values["output"].as<string>();
		}

		if (cmd_values.count("amp_exp"))
			normalize_mode = parameters::NormalizeMode::ExpDamping;
		else
			normalize_mode = parameters::NormalizeMode::None;

		is_cutback = cmd_values.count("cutback");


		
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
		exit(0);
	}
	

	//ファイル読み込み
	std::shared_ptr<vector<Mat>> input_mats;
	
	try
	{
		input_mats = ImageIO::get_mats(input_src);
	}
	catch (exception &e)
	{
		cout << e.what() << endl;

		exit(0);
	}

	ImageIO::save_mats(input_mats, output_src);

	getchar();
	return 0;
}

