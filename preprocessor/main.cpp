#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <map>

#include "preprocessor.h"

using namespace std;

// ----------------------------------------------------------------------
// Read in post-processed file into char array and return it
// ----------------------------------------------------------------------

char* readall(string fname)
{
    FILE* fp = fopen(fname.c_str(), "rb");
    if (!fp)
    {
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    rewind(fp);

    char* code = (char*)malloc(sz + 1);
    fread(code, 1, sz, fp);

    fclose(fp);

    code[sz] = '\0';

    return code;
}

// ######################################################################

int main(int argc, char** argv)
{

    // ----------------------------------------------------------------------
    // Fill in this for your MSVC location (used to set predefined macros and include paths for the preprocessor)
    // ----------------------------------------------------------------------

    const string VSPath = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Tools/MSVC/14.25.28610";
    const string windowsKits = "C:/Program Files (x86)/Windows Kits/10/include/10.0.18362.0";

    // ----------------------------------------------------------------------
    // Setup defines and includes to mimic MSVC
    // see https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=vs-2019
    // ----------------------------------------------------------------------

    list<string> defines, includePaths, included, forceIncludes;

    // Standard predefined macros
    defines.push_back("#define __STDC_HOSTED__ 1");

    // Set MSVC predefined macros to imitate MSVC
    defines.push_back("#define _WIN32 1");
    defines.push_back("#define _WIN64 1");
    defines.push_back("#define _M_AMD64 100");
    defines.push_back("#define _M_X64 100");
    defines.push_back("#define _MSVC_LANG " + to_string(_MSVC_LANG) + "L");
    defines.push_back("#define _MSC_VER " + to_string(_MSC_VER));
    defines.push_back("#define _MSC_FULL_VER " + to_string(_MSC_FULL_VER));
    defines.push_back("#define _MSVC_STL_VERSION " + to_string(_MSVC_STL_VERSION));
    defines.push_back("#define _MT 1");
    defines.push_back("#define _MSC_EXTENSIONS 1");
    defines.push_back("#define _MSC_BUILD 0");
    defines.push_back("#define _IS_ASSIGNABLE_NOCHECK_SUPPORTED 1");  // undocumented!

    // Set MSVC predefined includes
    includePaths.push_back(VSPath + "/ATLMFC/include");
    includePaths.push_back(VSPath + "/include");
    includePaths.push_back(windowsKits + "/ucrt");
    includePaths.push_back(windowsKits + "/shared");
    includePaths.push_back(windowsKits + "/um");
    includePaths.push_back(windowsKits + "/winrt");
    includePaths.push_back(windowsKits + "/cppwinrt");

    // ----------------------------------------------------------------------
    // Read cmd line arguments, get infile, outfile and -check
    // Format:
    //    preprocessor infile.c [-Ddefine=val] [-Ipath] [-FIheader.h] [-check]
    // eg preprocessor infile.c -DFoo=2 -DBAR -DFUNC(X,Y)=X+Y -Ipath/to/headers -FIbar.h -check
    // writes infile.c.pp in pwd [and foo.i if -check specified]
    // ----------------------------------------------------------------------

    const char* usage =
        "Usage:\n"
        "   preprocessor infile.c [-Ddefine[=val]] [-Ipath] [-FIheader.h] [-check] [-flatten] [-dependencies]\n"
        "eg preprocessor infile.c -DFoo=2 -DBAR -DFUNC(X,Y)=X+Y -Ipath/to/headers -FIbar.h -check\n"
        "You can have multiple -I, -D, -FI. The value must follow the flag immediately (-DFoo, not -D Foo)\n";

    bool check = false;
    string mode = "full";
    string infile = "";
    string extraArgs = "";

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];

        if (arg == "-check")
        {
            check = true;
        }
        else if (arg == "-flatten")
        {
            mode = "flatten";
        }
        else if (arg == "-dependencies")
        {
            mode = "dependencies";
        }
        else if (arg.substr(0, 2) == "-D")
        {
            extraArgs += (arg + " ");

            size_t ieq = arg.find('=');
            if (ieq == string::npos)
            {
                defines.push_back("#define " + arg.substr(2) + " 1");
            }
            else
            {
                arg[ieq] = ' ';
                defines.push_back("#define " + arg.substr(2));
            }
        }
        else if (arg.substr(0, 2) == "-I")
        {
            extraArgs += (arg + " ");
            includePaths.push_back(arg.substr(2));
        }
        else if (arg.substr(0, 3) == "-FI")
        {
            extraArgs += (arg + " ");
            forceIncludes.push_back("#include \"" + arg.substr(3) + "\"");
        }
        else if (arg.substr(0, 2) == "-h" || arg.substr(0, 2) == "-?" || arg.substr(0, 6) == "--help")
        {
            printf("%s\n", usage);
            exit(0);
        }
        else if (arg[0] == '-')
        {
            printf("Unknown argument: %s\n", argv[i]);
            printf("%s\n", usage);
            exit(1);
        }
        else
        {
            if (infile != "")
            {
                printf("Error, only 1 file can be specified\n");
                printf("%s\n", usage);
                exit(1);
            }
            infile = argv[i];
        }
    }

    if (infile == "")
    {
        printf("Input file must be specified\n");
        printf("%s\n", usage);
        exit(1);
    }

    if (infile.rfind('.') == string::npos)
    {
        printf("Source file has no extension, expecting foo.c or foo.cpp");
        exit(1);
    }

    // ----------------------------------------------------------------------
    // additional macros specific to C or C++
    // Setup attribute map for __has_cpp_attribute(x) (C++ only, leave map empty to turn off this feature)
    // __has_include(x) is simply turned on/off with a boolean (C++ only)
    // see https://en.cppreference.com/w/cpp/feature_test
    // see https://en.cppreference.com/w/cpp/preprocessor/include
    // ----------------------------------------------------------------------

    map<string, string> hasCppAttributeMap;
    bool hasIncludeSupported;

    if (infile.rfind(".cpp") == infile.size() - 4)   // ends in .cpp
    {
        defines.push_back("#define __cplusplus " + to_string(__cplusplus) + "L");
        defines.push_back("#define __STDCPP_THREADS__ 1");
        defines.push_back("#define _WCHAR_T_DEFINED 1");
        defines.push_back("#define _NATIVE_WCHAR_T_DEFINED 1");
        defines.push_back("#define _CPPRTTI 1");
        defines.push_back("#define __STDCPP_DEFAULT_NEW_ALIGNMENT__ 16ull");
        defines.push_back("#define __cpp_constexpr " + to_string(__cpp_constexpr) + "L");
        defines.push_back("#define __cpp_binary_literals " + to_string(__cpp_binary_literals) + "L");

        hasIncludeSupported = true;                    // true if supported
        hasCppAttributeMap["nodiscard"] = "201907L";   // use empty map if not supported
        hasCppAttributeMap["deprecated"] = "201309L";
    }
    else
    {
        const bool Za = false;  // should set this based on compiler option /Za
        if (Za)
            defines.push_back("#define __STDC__ 1");
        hasIncludeSupported = false;   // not supported in C. hasCppAttributeMap is empty so not supported either
    }

    // ----------------------------------------------------------------------
    // Find raw file name of input file (not full path) and output file name
    // ----------------------------------------------------------------------

    string infileName, outfile;

    bool found = false;
    for (int i = size(infile) - 1; i >= 0; i--)
    {
        char c = infile[i];
        if (c == '/' || c == '\\')
        {
            infileName = infile.substr(i + 1);
            found = true;
            break;
        }
    }

    if (!found)
        infileName = infile;

    outfile = infileName + ".pp";

    // ----------------------------------------------------------------------
    // Call preprocess and print a list of included files (directly or indirectly)
    // Post processed file written to outfile
    // ----------------------------------------------------------------------

    printf("Preprocessing file: %s -> %s\n", infile.c_str(), outfile.c_str());

    try
    {
        preprocessor::preprocess(mode, infile, outfile, defines, includePaths, forceIncludes, included, hasCppAttributeMap, hasIncludeSupported);
    }
    catch (string msg)
    {
        printf("Error: %s\n", msg.c_str());
        exit(1);
    }

    if (included.empty())
    {
        printf("No files included by the preprocessor\n");
    }
    else
    {
        printf("The following files were included by the preprocessor:\n");
        for (string incl : included)
        {
            printf("%s\n", incl.c_str());
        }
        printf("\n");
    }

    // ---------------------------------------------------------------------
    // If -check specified, postprocess using MSVC compiler and compare to our output, written above
    // ---------------------------------------------------------------------

    bool passed = true;

    if (check)
    {
        size_t ind = infileName.rfind('.');
        string ifile = infileName.substr(0, ind) + ".i";

//        string cmd = "\"" + cl + "\" /nologo /P " + infile + " " + extraArgs;
        string cmd = "cl /nologo /P " + infile + " " + extraArgs;
        printf("Running CL with command:\n%s\nOutput in: %s\n", cmd.c_str(), ifile.c_str());

        printf("CL says:\n");
        system(cmd.c_str());
        printf("End CL output\n");

        char* ppcode = readall(outfile);
        char* icode = readall(ifile);

        if (ppcode == NULL || icode == NULL)
        {
            printf("ERROR: postprocessed file not found\n");
            exit(1);
        }

        passed = preprocessor::checkAgainstMSVC(ppcode, icode, outfile, ifile);

        free(ppcode);
        free(icode);
    }

    if (passed)
        return 0;
    else
        return 1;
}
