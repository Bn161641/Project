#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include "inc_a.h"
using namespace std;

double version = 1.2;

//this program 	receives text from standard input, accepts one of three options: -d, -f and -b
//, and display one line from the input accoring to the given option
//-d = directories
//-f = files
//-b = bytes
int main(int argc, char* argv[])
{
	displayVersion();
	//declaring variables
	string input = argv[1];		//convert argv into a string for comparison
	string line[3];

	for(int i = 0; i < 3; i++)
	{
		getline(cin, line[i]);
	}

	//if input is == -d display the first line with directories
	if(input == "-d")
	{
		for(int i = 0; i < 3; i++)
		{
			if(line[i].find("directories") != string::npos)
			{
				cout << line[i] << endl;
				break;
			}
		}
	}

	//if input is == -f display the first line with files
	else if(input == "-f")
	{
		for(int i = 0; i < 3; i++)
		{
			if(line[i].find("files") != string::npos)
			{
				cout << line[i] << endl;
				break;
			}
		}
	}

	//if input is == -b display the first line with bytes
	else if(input == "-b")
	{
		for(int i = 0; i < 3; i++)
		{
			if(line[i].find("bytes") != string::npos)
			{
				cout << line[i] << endl;
				break;
			}
		}
	}

	//if none of the 3 options matches input, display error
	else
	{
		cout << "Error invalid option" << endl;
	}

	return 0;
}
