#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>

std::string create_tmpfile(void){
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


int run_bin(std::string bin,std::string infilename ,std::string outfilename)
{
	std::string payload[] = {"cat ", infilename, " | " ,bin, " > ", outfilename};
	int size = *(&payload + 1) - payload;

	std::string cmd = joinstr(payload,size);

	return system(cmd.c_str());
}

int write_infile(std::string infile, std::string body){
	return system(("echo " + body + " > " + infile ).c_str());	
}


std::string cgi(std::string bin,std::string body){
	
	std::string outfile = create_tmpfile();
	std::string infile = create_tmpfile();

	write_infile(infile,body);

	run_bin(bin, infile, outfile);

	std::string out = get_file_content(outfile);

	remove(infile.c_str());
	remove(outfile.c_str());

	return out;
}

int main(int argc, char const *argv[])
{
	char *env[] = {"CONTENT_LENGTH=15","CONTENT_TYPE=application/x-www-form-urlencoded","GATEWAY_INTERFACE=CGI/1.1","PATH_INFO=/post.php","PATH_TRANSLATED=/post.php","QUERY_STRING=","REDIRECT_STATUS=200","REMOTE_IDENT=","REMOTE_USER=","REMOTEaddr=0","REQUEST_METHOD=POST","REQUEST_URI=/post.php","SCRIPT_FILENAME=./post.php","SCRIPT_NAME=./post.php","SERVER_NAME=0","SERVER_PORT=8000","SERVER_PROTOCOL=HTTP/1.1","SERVER_SOFTWARE=Weebserv/1.0"};
	int size = *(&env + 1) - env;

	for (size_t i = 0; i < size; i++)
	{
		putenv(env[i]);
	}

	std::cout << cgi(std::string(argv[1]),std::string(argv[2])) << std::endl;


	return 0;
}
