#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
	std::string payload[] = {"bin", " ","arg", " > ", "filename"};

	// std::cout << sizeof(payload)/sizeof(char);
	std::cout << *(&payload + 1) - payload;


	return 0;
}
