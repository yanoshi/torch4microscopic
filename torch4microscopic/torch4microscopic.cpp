// torch4microscopic.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <boost/program_options.hpp>


using namespace std;
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

	try 
	{
		options_description option_marged("");
		option_marged.add(inout_options).add(calc_options);

		if (!cmd_values.count("input") || cmd_values.count("output"))
		{
			cout << option_marged << endl;
		}

		store(parse_command_line(argc, argv, option_marged), cmd_values);
		notify(cmd_values);

		
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}

	
	return 0;
}

