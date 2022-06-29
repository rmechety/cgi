#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string createtmpfile(void){
	char *tmpfname = std::tmpnam(NULL);
	std::ofstream ftocreate(tmpfname);
	ftocreate.close();
	return std::string(tmpfname);
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
	std::string payload[] = {"exec cgi ", bin, " ",arg, " > ", filename};
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
	putenv("REDIRECT_STATUS=200"); //Security needed to execute php-cgi
	putenv("GATEWAY_INTERFACE=CGI/1.1");
	putenv("SCRIPT_NAME=hello");
	putenv("SCRIPT_FILENAME=hello.php");
	putenv("REQUEST_METHOD=GET");
	putenv("CONTENT_LENGTH=10000");
	putenv("CONTENT_TYPE=text/html");
	putenv("PATH_INFO=PATHINFO"); //might need some change, using config path/contentLocation
	// this->_env["PATH_TRANSLATED"]=request.getPath()); //might need some change, using config path/contentLocation
	// this->_env["QUERY_STRING"]=request.getQuery());
	// this->_env["REMOTEaddr"]=to_string(config.getHostPort().host));
	// this->_env["REMOTE_IDENT"]=headers["Authorization"]);
	// this->_env["REMOTE_USER"]=headers["Authorization"]);
	putenv("REQUEST_URI=/hello.php");
	std::cout << cgi(std::string(argv[1]),std::string(argv[2])) << std::endl;


	return 0;
}
