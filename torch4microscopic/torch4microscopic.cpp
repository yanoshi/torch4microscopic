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

double parameters::Values::unitsize_depth = 0.0;

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
		("amp_exp_power", value<double>(), "amp power")
		("cutback", "enable subtraction for cutback (average lowest pixel)")
		("unitsize_depth,d", value<double>() ,"depth of z order");

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


		if (cmd_values.count("amp_mode"))
		{
			if (cmd_values["amp_mode"].as<string>() == "exp")
			{
				normalize_mode = parameters::NormalizeMode::ExpDamping;

				if (cmd_values.count("unitsize_depth"))
				{
					parameters::Values::unitsize_depth = cmd_values["unitsize_depth"].as<double>();
				}
				else
				{
					cout << calc_options << endl;
					exit(0);
				}
			}
			else if (cmd_values["amp_mode"].as<string>() == "simple")
			{
				normalize_mode = parameters::NormalizeMode::Simple;
			}
			else
				normalize_mode = parameters::NormalizeMode::None;

		}
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

	
	//変換処理
	std::shared_ptr<vector<Mat>> output_mats;
	MatConverter converter(input_mats, normalize_mode, is_cutback);

	output_mats = converter.get_result();


	ImageIO::save_mats(output_mats, output_src);
#ifdef _DEBUG
	cout << "Please press enter key..." << endl;
	getchar();
#endif
	return 0;
}

