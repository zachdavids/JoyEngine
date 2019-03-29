#include "Tools.h"

#include <fstream>
#include <sstream>

void Engine::Tools::ReadFile(std::string* output, std::string const& path)
{
	std::ifstream stream;
	std::stringstream sstr;

	stream.open(path);
	sstr << stream.rdbuf();
	stream.close();
	*output = sstr.str();
	sstr.str("");
	sstr.clear();
}