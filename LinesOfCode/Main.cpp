#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <experimental/filesystem>
#include "Windows.h"

namespace fs = std::experimental::filesystem;
static unsigned int total = 0;

/*
*	Retrieves the file name.
*	
*/
std::string splitFilename(const std::string &str) {
	std::size_t found = str.find_last_of("/\\");
	std::string file = str.substr(found + 1);
	return file;
}

/*
*	Counts the lines of code of the specified file.
*	
*/
int countLines(std::string path) {
	unsigned int lines = 0;
	// Open file
	std::ifstream File(path);
	if (!File.is_open()) {
		return -1;
	}

	std::string t;

	while (getline(File, t)) {
		++lines;
	}

	std::cout << std::setw(36) << std::left << std::setfill('-') << splitFilename(path) << "Lines of code:	" << lines << std::endl;

	// Close file
	File.close();

	total += lines;
	return lines;
}

/*
*	Main entry point.
*	
*/
int main() {
	std::cout << "Welcome to LinesOfCode, a little tool that allows you, to count all lines of code of your C++ project!" << std::endl;
	std::cout << "Please enter the directory path of your project:	";
	std::string path;
	std::cin >> path;

	std::cout << "Please enter the number of different file extensions you want to add:	";
	int NUM_EXTENSIONS;
	std::cin >> NUM_EXTENSIONS;
	std::string *extensions = new std::string[NUM_EXTENSIONS];
	std::cout << "Please enter the file extensions you want to scan your project folder for:	" << std::endl;
	for (int i = 0; i < NUM_EXTENSIONS; i++) {
		std::cout << "Please enter file extension number " << i + 1 << ":" << std::endl;
		std::string ext;
		std::cin >> ext;
		extensions[i] = ext;
	}
	
	for (auto &p : fs::recursive_directory_iterator(path)) {
		for (int i = 0; i < NUM_EXTENSIONS; i++) {
			if (p.path().extension() != "" &&
				(p.path().extension() == extensions[i])) {
				countLines(p.path().generic_string());
			}
		}
	}
	std::cout << "\n\nTotal lines of code:		" << total << "\n\n" << std::endl;
	delete[] extensions;

	system("pause");

	return 0;
}