#include <cstdio>
#include <cstdlib>
#include <string>
#include <limits>
#include <unistd.h>
#include <iostream>
#include <sstream>

std::string tostr(int k) {
 std::stringstream ss;
  ss<<k;
  std::string s;
  ss>>s;

  return s;
  }

int main(int argc, char const *argv[]) {

	// FILE * tmp = tmpnam();
	char B[500] = {0};
	char *Bf = std::tmpnam(B);
	std::string cmd = argv[1];
	cmd+=" ";
	cmd+=argv[2];

	// char filePath[1024] = {0};

	// std::string pathfd = "/proc/self/fd/" ;
	// pathfd +=tostr(tmp->_fileno);

	// std::cout <<"PATHFD >" <<pathfd <<"<"<< std::endl;
	// std::cout <<"fno >" <<tmp->_fileno <<"<"<< std::endl;

	// readlink( pathfd.c_str() ,filePath,1024);

	cmd+=" > ";
	cmd += Bf ;
	// cmd+="res";
	// std::cout <<"PATH >" <<filePath <<"<"<< std::endl;
	// // system(cmd.c_str());
	// char buf[]="zobi";
	// fwrite(buf , sizeof(char),4, tmp);

	char	buffer[20] = {0};


	std::cerr<<"rtr"<<std::endl;
	FILE * f = fopen(Bf,"r");
	std::cerr<<"fdasf"<<std::endl;

	std::cerr<<"ptr : " << f <<std::endl;
	std::cerr <<"sldjgf"<< fread (buffer,1,2,f) << std::endl;

	std::cout << "buf : >"<< buffer[0] << "<"<<std::endl;
	return 0;
}
// #include <filesystem>
// int main(){

//     std::FILE* tmpf = std::tmpfile();
//     std::fputs("Hello, world", tmpf);
//     std::rewind(tmpf);
//     char buf[6];
//     std::fgets(buf, sizeof buf, tmpf);
//     std::cout << buf << '\n';

//     // Linux-specific method to display the tmpfile name
//     std::cout << std::filesystem::read_symlink(
//                      std::filesystem::path("/proc/self/fd") / std::to_string(fileno(tmpf))
//                  ) << '\n';

// }
