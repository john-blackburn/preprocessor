#pragma once
#include <string>
#include <list>
#include <map>

namespace preprocessor
{
    std::string preprocess(std::string mode, std::string infile, std::string outfile, std::list<std::string> defines, std::list<std::string> includePaths,
        std::list<std::string> forceIncludes, std::list<std::string>& included, std::map<std::string, std::string> attributeMap, bool hasIncludeSupported);

    bool checkAgainstMSVC(char* ppcode, char* icode, std::string outfile, std::string ifile);
}
