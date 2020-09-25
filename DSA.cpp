#include <iostream>
#include <fstream>
#include <string>
#include <cstring> //because dirent stores dir names in char arrays...i.e. c type strings
#include <dirent.h> //format of directory entries
#include <sstream> //string stream
#include <vector> //to store the list of all the file names

using namespace std;

//hash function
unsigned long hashstring(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


//directory structure
DIR *dpdf;
struct dirent *epdf;


main()
{
	cout<<"Enter the path of the directory in which you wish to search"<<endl;
	string dir_path;
	cin>>dir_path;
	cout<<"The target directory is...\n"<<dir_path.c_str()<<endl;
	
	
	//reading all the files in the directory
	cout<<"Getting all files in this directory.....\n";
	dpdf = opendir("./files/"); //opening the current directory
	
	vector<string> files;
	
	//printing the file names
	if (dpdf != NULL)
	{
	   while (epdf = readdir(dpdf)){
		 
	      files.push_back(epdf->d_name);
	   }
	}	
	
	//getting the number of files in the directory
	long int num_files;
	num_files=files.size();
	
	//cout<<"number of files is "<<num_files<<endl;
	
	/*int i;
	for(i=0;i<num_files;i++)
		cout<<files[i]<<endl;
	*/	
	
		
	//getting the words from these files
	char word[20];
	streampos position
	for(i=0; i<num_files; i++)
	{
		ifstream myfile ("files[i].txt");
		if(myfile.is_open())
		{
			begin = myfile.tellg();
			if()
			
		}
	}
	
}







