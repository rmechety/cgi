#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <unistd.h>

/**
 * It creates a temporary file, writes nothing to it, and returns the name of the file
 *
 * @return A string containing the name of a temporary file.
 */
std::string create_tmpfile(void)
{
	char *tmpfname = std::tmpnam(NULL);
	std::ofstream ftocreate(tmpfname);
	ftocreate.close();
	return std::string(tmpfname);
}

/**
 * It reads the contents of a file into a string
 *
 * @param filename The name of the file to read.
 *
 * @return A string containing the contents of the file.
 */
std::string get_file_content(std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename.c_str(), std::ifstream::in);

	std::stringstream strStream;
	strStream << ifs.rdbuf();

	return strStream.str();
};

/**
 * It takes an array of strings and the number of strings in the array, and returns a single string
 * that is the concatenation of all the strings in the array
 *
 * @param strs an array of strings
 * @param n the number of strings to join
 *
 * @return A string
 */
std::string joinstr(std::string *strs, int n)
{

	std::string str;
	for (size_t i = 0; i < n; i++)
	{
		str += strs[i];
	}
	return str;
}

/**
 * It takes a binary, an input file, and an output file, and runs the binary on the input file,
 * writing the output to the output file
 *
 * @param bin the binary to run
 * @param infilename The input file to be used by the binary
 * @param outfilename The name of the file that will be created.
 *
 * @return The return value of the system call.
 */
int run_bin(std::string bin, std::string infilename, std::string outfilename)
{
	std::string payload[] = {"cat ", infilename, " | ", bin, " > ", outfilename};
	int size = *(&payload + 1) - payload;

	std::string cmd = joinstr(payload, size);

	return system(cmd.c_str());
}

/**
 * It writes a string to a file
 *
 * @param infile The file to write to.
 * @param body The body of the file to be written.
 *
 * @return The return value of the system call.
 */
int write_infile(std::string infile, std::string body)
{
	return system(("echo " + body + " > " + infile).c_str());
}

/**
 * It takes a binary and a string, writes the string to a temporary file, runs the binary with the
 * temporary file as input, and returns the output of the binary as a string
 *
 * @param bin the path to the binary to run
 * @param body The body of the request.
 *
 * @return The output of the cgi script.
 */

std::string cgi(std::string bin, std::string body)
{

	std::string outfile = create_tmpfile();
	std::string infile = create_tmpfile();

	write_infile(infile, body);

	run_bin(bin, infile, outfile);

	std::string out = get_file_content(outfile);

	remove(infile.c_str());
	remove(outfile.c_str());

	return out;
}

int main(int argc, char const *argv[])
{
	char *env[] = {"CONTENT_LENGTH=15",
				   "CONTENT_TYPE=application/x-www-form-urlencoded",
				   "GATEWAY_INTERFACE=CGI/1.1",
				   "PATH_INFO=/post.php",
				   "PATH_TRANSLATED=/post.php",
				   "QUERY_STRING=",
				   "REDIRECT_STATUS=200",
				   "REMOTE_IDENT=",
				   "REMOTE_USER=",
				   "REMOTEaddr=0",
				   "REQUEST_METHOD=POST",
				   "REQUEST_URI=/post.php",
				   "SCRIPT_FILENAME=./post.php",
				   "SCRIPT_NAME=./post.php",
				   "SERVER_NAME=0",
				   "SERVER_PORT=8000",
				   "SERVER_PROTOCOL=HTTP/1.1",
				   "SERVER_SOFTWARE=Weebserv/1.0"};
	int size = *(&env + 1) - env;

	for (size_t i = 0; i < size; i++)
	{
		putenv(env[i]);
	}

	std::cout << cgi(std::string(argv[1]), std::string(argv[2])) << std::endl;

	return 0;
}
