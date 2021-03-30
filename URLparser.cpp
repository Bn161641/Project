//This program will get an input of a URL and take the components apart and parse it
//Hello i love myself
#include<iostream>
#include<string>
#include<cstring>
#include "inc_a.h"
using namespace std;

//function prototype
void parseURL(string[], string[], string);
void validate(bool[], string[], string &, string &, int &);
double version = 1.2;

int main()
{
	//declaring variables
	string URL, URLcomponents[5];		//URLcomponents[0] = protocol, URLcomponents[1] = domain, URLcomponents[2] = port, 
						//URLcomponents[3] = filePath, URLcomponents[4] = parameters
	string domainName, filePathEnding;
	string lookFor[4] = { "://", ":", "/", "?" };
	bool valid[5] = { 1, 1, 1, 1, 1 }, displayInvalid = 0;	//this valid array corresponds with the URLcomponents array to check if each category is valid
	int numberOfDots = 0;
	
	
	displayVersion();

	//getting URL from user
	cout << "Enter URL\n";
	cin >> URL;
	
	//parse URL
	parseURL(URLcomponents, lookFor, URL);
	
	//validate components of URL
	validate(valid, URLcomponents, domainName, filePathEnding, numberOfDots);
	
	//check if all component is valid
	for(int i = 0; i < 5; i++)
	{
		//if a component shows up as invalid display the error
		if(!valid[i])
		{
			//dispay this one time
			if(!displayInvalid)
			{
				cout << "Invalid URL with following erroneous components:\n";
				displayInvalid = 1;
			}
			
			//switch statement for each error
			switch (i)
			{
			case 0:
				cout << "Protocol:    " << URLcomponents[i] << " is not a valid protocol.\n";
				break;
			case 1:
				//display if form is wrong
				if(numberOfDots != 2)
				{
					cout << "Domain:      " << "is not in form of <x>.<y>.<z>\n";
				}
				
				//display if domanName is wrong
				if(domainName != "com" && domainName != "net" && domainName != "edu" && domainName != "biz" && domainName != "gov")
				{
					cout << "Domain:      " << domainName << " is an invalid domain name.\n";
				}
				break;
			case 2:
				cout << "Port:        "  << "port number must be between 1 and 65535\n";
				break;
			case 3:
				cout << "File path:   " << filePathEnding << " is an invalid domain name.\n";
			case 4:
				if(URLcomponents[4] != "not found")
				{
					cout << "Parameters:  " << "parameters must start with ?\n";
				}
				break;
			default:
				cout << "system error\n";
			}
		}
	}
	
	//if no error was found, display content normally
	//removing "?" out of parameter for display
	if(URLcomponents[4].at(0) == '?')
	{
		URLcomponents[4] = URLcomponents[4].substr(1, URLcomponents[4].size());
	}
	
	if(!displayInvalid)
	{
		cout << "Protocol:    " << URLcomponents[0] << endl;
		cout << "Domain:      " << URLcomponents[1] << endl;
		
		//display port if there is a port
		if(URLcomponents[2] != "not found")
		{
			cout << "Port:        " << URLcomponents[2] << endl;
		}
		
		cout << "File path:   " << URLcomponents[3] << endl;
		
		//display parameters if there a parameter
		if(URLcomponents[4] != "not found")
		{
			cout << "Parameters:  " << URLcomponents[4] << endl;
		}
	}
	
	return 0;
}

//this function contains a loop that iterate through the URL to separate it into components
void parseURL(string URLcomponents[], string lookFor[], string URL)
{
	//for loop to parse the URL
	for(int i = 0; i < 5; i++)
	{
		//if statement to avoid error since lookFor size is 4
		if(i < 4)
		{
			//because parament is optional ? may not show up
			if(i == 3 && URL.find(lookFor[i]) == -1)
			{
				URLcomponents[i] = URL;
			}
			//making sure lookFor is in the string because port is optional
			else if(URL.find(lookFor[i]) != -1)
			{
				URLcomponents[i] = URL.substr(0, URL.find(lookFor[i]));
			
				if(lookFor[i] != "/" && lookFor[i] != "?")
				{
					URL = URL.substr(URL.find(lookFor[i]) + lookFor[i].size(), URL.size());
				}
				else
				{
					URL = URL.substr(URL.find(lookFor[i]), URL.size());
				}
			}
			else
			{
				URLcomponents[i] = "not found";
			}
		}
		else
		{
			if(URL.at(0) == '?')
			{
				URLcomponents[i] = URL.substr(0, URL.size());
			}
			else
			{
				URLcomponents[i] = "not found";
			}
		}
	}
	
	//if statement to move domain out of URLcomponents[2] and into URLcomponents[1], this is caused due to port being optional
	if(URLcomponents[1] == "not found")
	{
		URLcomponents[1] = URLcomponents[2];
		URLcomponents[2] = "not found";
	}
	
}

//this function validate each components of the URL
void validate(bool valid[], string URLcomponents[], string &domainName, string &filePathEnding, int &numberOfDots)
{
	//validate protocol
	if(URLcomponents[0] == "http" || URLcomponents[0] == "https" || URLcomponents[0] == "ftp" || URLcomponents[0] == "ftps")
	{
		valid[0] = 1;
	}
	else
	{
		valid[0] = 0;
	}
	
	//validate domain
	domainName = URLcomponents[1].substr(URLcomponents[1].rfind(".") + 1, URLcomponents[1].size());
	if(domainName == "com" || domainName == "net" || domainName == "edu" || domainName == "biz" || domainName == "gov")
	{
		//count the number of '.'
		for(int i = 0; i < domainName.size(); i++)
		{
			if(domainName.at(i) == '.')
			{
				numberOfDots++;
			}
		}
		
		if(numberOfDots == 2)
		{
			valid[1] = 1;
		}
		else
		{
			valid[0] = 1;
		}
	}
	else
	{
		valid[1] = 0;
	}
	
	//validate port
	if (URLcomponents[2] != "not found")
	{
		//convert string to int
		int portNumber = stoi(URLcomponents[2]);
		
		//check if portNumber is in the range of 1 to 65535
		if(portNumber >= 1 && portNumber <= 65535)
		{
			valid[2] = 1;
		}
		else
		{
			valid[2] = 0;
		}
		
	}
	
	//validate file path
	filePathEnding = URLcomponents[3].substr(URLcomponents[3].rfind("."), URLcomponents[3].size());
	if((URLcomponents[3].at(0) == '/') && (filePathEnding == ".html" || filePathEnding == ".htm"))
	{
		valid[3] = 1;
	}
	else
	{
		valid[3] = 0;
	}
	
	//validate parameters
	if(URLcomponents[4].at(0) == '?' || URLcomponents[4] == "not found")
	{
		valid[4] = 1;
	}
	else
	{
		valid[4] = 0;
	}
	
}
