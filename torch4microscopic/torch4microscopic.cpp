// torch4microscopic.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//


#include <iostream>
#include <vector>
#include <fstream>
#include <boost/program_options.hpp>

#include "parameters.h"
#include "image_io.h"
#include "mat_converter.h"

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
		("amp_mode", value<string>(), "enable amplifier (exponential growth mode[exp] OR adjust highest pixel mode[simple])")
		("cutback", "enable subtraction for cutback (average lowest pixel)")
		("unitsize_depth,d", value<double>() ,"depth of z order")
		("gaussian,g","enable gaussian blur")
		("window_size,w",value<int>(),"filter's window size");

	variables_map cmd_values;

	//各パラメータ情報を格納する変数
	string input_src, output_src;
	parameters::Values param;


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


		if (cmd_values.count("amp_mode"))
		{
			if (cmd_values["amp_mode"].as<string>() == "exp")
			{
				param.normalize_mode = parameters::NormalizeMode::ExpDamping;

				if (cmd_values.count("unitsize_depth"))
				{
					param.unitsize_depth = cmd_values["unitsize_depth"].as<double>();
				}
				else
				{
					cout << calc_options << endl;
					exit(0);
				}
			}
			else if (cmd_values["amp_mode"].as<string>() == "simple")
			{
				param.normalize_mode = parameters::NormalizeMode::Simple;
			}
			else
				param.normalize_mode = parameters::NormalizeMode::None;

		}
		else
			param.normalize_mode = parameters::NormalizeMode::None;

		param.enable_cutback = cmd_values.count("cutback");

		if (cmd_values.count("gaussian"))
		{
			param.enable_gblur = true;
			if (cmd_values.count("window_size"))
				param.window_size = Size(cmd_values["window_size"].as<int>(), cmd_values["window_size"].as<int>());
		}
		
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

	
	//変換処理
	std::shared_ptr<vector<Mat>> output_mats;
	MatConverter converter(input_mats, param);

	output_mats = converter.get_result();


	ImageIO::save_mats(output_mats, output_src);
#ifdef _DEBUG
	cout << "Please press enter key..." << endl;
	getchar();
#endif
	return 0;
}

