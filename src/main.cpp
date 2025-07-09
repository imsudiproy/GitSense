#include<iostream>
#include<filesystem>
#include"CLI/CLI11.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv){
	CLI::App app{"git-summary-cli: A CLI tool"};

	std::string path = ".";
	bool verbose = false;
	int count = 0;

	app.add_option("--path", path, "Path to a directory")->check(CLI::ExistingDirectory);
	app.add_flag("--verbose", verbose, "Enable Verbose output");
	app.add_option("--count", count, "Number of items to process");

	CLI11_PARSE(app, argc, argv);

	std::cout<< "Options parsed:\n";
	std::cout<< "	PathL "<< path << "\n";
	std::cout << "	Verbose: " << (verbose ? "true" : "false") << "\n";
	std::cout << "	Count: " << count << "\n";
	return 0;
}
