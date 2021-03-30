//this program takes in a path to a directory and counts the amount of directories, files, and
//hello my name is bryan
//number of bytes of file in that single directory
//this program also goes into the sub directory as well and counts any addtional direcories or
//files found
#include<iostream>
#include<dirent.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string>
#include<string.h>
#include "inc_a.h"
using namespace std;

double version = 1.2;

//this class holds the counters for directory files, plain files, and the number of bytes
//occupied by the plain files
class DirectoriesFilesBytesCounter
{
	public:
		int dCounter;
		int fCounter;
		int bCounter;
};

//function protype
DirectoriesFilesBytesCounter filecnt(char*);

int main(int argc, char* argv[])
{
	displayVersion();
	//declare variable
	DirectoriesFilesBytesCounter counter;

	//calling function
	counter = filecnt(argv[1]);

	//outputing information
	cout << "The total number of directories in directory " << argv[1] << " is " << counter.dCounter << ". \n";
	cout << "The total number of files in directory " << argv[1] << " is " << counter.fCounter << ". \n";
	cout << "The total number of bytes occupied by all files in directory " << argv[1] << " is " << counter.bCounter << ". \n";
	
	
	return 0;
}


//this function goes through the path of a directory and counts the number of directories,
//files, and the amount of bytes that file takes up.
DirectoriesFilesBytesCounter filecnt(char *path)
{
	//declaring variables
	DirectoriesFilesBytesCounter counter1;
	char newPath[1000];
	static int fileCount = 0, directoryCount = 0, byteCount = 0;

	DIR *dir;		//pointer to an open directory
	struct dirent *dirent;	
	dir = opendir(path);	//open directory

	//display error if can't open
	if(dir == NULL)
	{
		cout << "Error in opening directory " << path << endl;
		exit(-1);
	}
	
	//go through the path and count files and directories
	while((dirent = readdir(dir)))
	{
		//check that it is not current directory
		if(dirent->d_name[0] != '.')
		{
			//go inside subdirectories, recursive calls
			if((*dirent).d_type==DT_DIR)
			{
				directoryCount++;
				strcpy(newPath, path);
				strcat(newPath, "/");
				strcat(newPath, (*dirent).d_name);
				filecnt(newPath);
			}

			if((*dirent).d_type==DT_REG)
			{
				fileCount++;
				byteCount = byteCount + (*dirent).d_reclen;
			}
		}
	}

	closedir(dir);
	counter1.dCounter = directoryCount;
	counter1.fCounter = fileCount;
	counter1.bCounter = byteCount;

	return counter1;
}


