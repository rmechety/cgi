#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string createtmpfile(void){
	char *name2 = std::tmpnam(NULL);
	std::ofstream ftocreate(name2);
	ftocreate.close();
	return std::string(name2);
}

std::string get_file_content(std::string filename)
{
	std::ifstream ifs;
	ifs.open (filename.c_str(), std::ifstream::in);

	std::stringstream strStream;
    strStream << ifs.rdbuf();

	return strStream.str();
};

std::string joinstr(std::string *strs,int n){
	
	std::string str;
	for (size_t i = 0; i < n; i++)
	{
		str += strs[i];
	}
	return str;
}


int runbin(std::string bin, std::string arg, std::string filename)
{
	std::string payload[] = {bin, " ",arg, " > ", filename};
	int size = *(&payload + 1) - payload;

	std::string cmd = joinstr(payload,size);
	
	return system(cmd.c_str());
}


std::string cgi(std::string bin,std::string arg){
	
	std::string outfile = createtmpfile();
	
	runbin(bin,arg,outfile);

	std::string out = get_file_content(outfile);

	return out;
}

int main(int argc, char const *argv[])
{
	putenv("HOME=/ooga");

	std::cout << cgi(std::string(argv[1]),std::string(argv[2])) << std::endl;


	return 0;
}
