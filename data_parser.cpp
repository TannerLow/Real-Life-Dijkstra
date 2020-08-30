#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv){
	//Handle cmd line arguments
	if(argc < 2){
		printf("Usage: <file location>");
		return 0;
	}
	
	//Load file
	//ifstream fileHandle(argv[1]);
	string line;
	getline(cin, line);

	int found = line.find("lat");
	printf("%d\n", found);
	line.replace(0,found + 5, "");
	printf("%s\n", line.c_str());

	int end = line.find('\"');
	found = line.find("lon", end);
	printf("%d\n", end);
	printf("%d\n", found);
	line.replace(end, found+5 - end, " ");

	end = line.find('\"');
	line.replace(end, line.size() - end, "");
	printf("%s\n", line.c_str());
	return 0;
}