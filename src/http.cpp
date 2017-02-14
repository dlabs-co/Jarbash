#include "http.h"

#include <string.h>
#include <sstream>
#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

std::string test(void)
{
	curlpp::Cleanup myCleanup;
	std::ostringstream os;
	os << curlpp::options::Url(std::string("http://example.com"));
	return os.str();
}
