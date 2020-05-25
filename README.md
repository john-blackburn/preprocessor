# preprocessor

A C/C++ preprocessor library written in C++. Only the C++ standard library is used so the code should be easy to incorporate into other programs.

# Features

* Full standards compliant C/C++ preprocessor
* The only predefined macros and include paths are ones you specify, so the preprocessor can imitate the behaviour of any commercial one (MSVC, gcc etc)
* `__has_cpp_attribute` supported (user must specify what attributes are supported)
* `__has_include supported`
* Additional "flatten" mode supported: This processeses `#include` and `#if` but does not expand macros
* Additional "dependencies" mode supported: simply discovers what files would be included (directly and indirectly). Does not output processed code.
* When processing resource files (RC), assets such as Bitmap, Icons are additionally shown as dependencies along with include files.

Some extensions are supported (needed to deal with `windows.h` etc)
* `defined(x)` permitted within a macro definition
* $ allowed in identifier names
* Non-standard symbols permitted such as @ (these are used in `windows.h` and its descendants, for some reason...)
* `#pragma once` supported. Also MSVC's `#pragma push_macro` and `pop_macro` are supported. Other pragmas as simply output for the compiler to deal with.

# Using the library

There is only one public function you need to call (located in the "preprocessor" namespace):

```
string preprocess(string mode, string infile, string outfile, list<string> defines, list<string> includePaths, list<string> forceIncludes, 
    list<string> &included, map<string, string> attributeMap, bool hasIncludeSupported);
```

This preprocesses a file "infile" (`.c`, `.cpp`, `.rc` etc) and writes the result to a single file "outfile", processing all `#include, #if` etc. If infile is an empty string, nothing is written to disk and the output is instead returned as a string. The function also sets "included": a list of all files which were directly and indirectly included during the preprocess step. (if preprocessing a resource file, `.rc`, included assets such as bitmaps files are also shown in this list)

If the preprocess fails, a string exception is thrown.

The remaining arguments are as follows:

* "defines" specifies predefined macros. It is a list of strings each of which is a regular `#define` statement

* "includePaths" specifies include paths to search. It is a list of include paths (strings) either absolute path or relative to the present working directory

* "forceIncludes" specifies force includes. It is a list of strings each of which is a regular `#include` statement. The file is processed as if these include statements appeared at the beginning.

* "attributeMap" specifies the behaviour of the `__has_cpp_attributes` function. It is a string-string map, eg `attributeMap["nodiscard"] = "201907L"` might be set. To turn off this feature, pass in an empty map. In that case `__has_cpp_attribute` will be undefined and the function can't be used

* "hasIncludeSupported": set to true if `__has_include` should be supported. If false, `__has_include` is not defined and function can't be used. If it is true then preprocessor code such as `__has_include(<stdio.h>)` will return true if this library is present

There are several modes of operation:

* mode="full": full, normal preprocess. All macros are expanded.

* mode="flatten": preprocess includes and ifs but don't expand macros. The resulting single file can be "compiled" (ie preprocessed then compiled) by any standard compiler.

* mode="dependencies": discover which files are included but don't write postprocessed output to file (or return as a string)

It's important to realise that the preprocessor does not predefine any include paths or defines (except `__LINE__`, `__FILE__`, `__DATE__`, `__TIME__` which are always available). You must specify these via "defines" and "includePaths". The preprocessor can then be made to imitate the behaviour of any other preprocessor (MSVC, gcc etc). The example driver program supplied (`main.cpp`) imitates the MSVC preprocessor by setting macros such as `_MSC_FULL_VER` etc.

For example, to achieve the same result as with this MSVC command:

```
cl /E foo.c -DFoo=2 -DBAR -DFUNC(X,Y)=X+Y -Ipath/to/headers -FIbar.h
```

you would call preprocess with the following specifications:

```
defines[0,1,...,n] = << MSVC specific defines >>
defines[n+1]="#define Foo 2"
defines[n+1]="#define BAR 1" (in -D, value defaults to "1" but we must specify this)
defines[n+2]="#define FUNC(X,Y) X+Y"

includePaths[0,1,..,m]= << MSVC specific includes >> 
includePaths[m+1]="path/to/headers" (forward or backslashes allowed)

forceIncludes[0]="#include \"bar.h\""

attributeMap["nodiscard"] = "201907L"  // etc

preprocess("full", "foo.c", "foo.i", defines, includePaths, forceIncludes, included, attributeMap, true);
```

(see `main.cpp` for a full set of MSVC-specific defines and includes)

# Example main program

A main program (`main.cpp`) has been supplied which shows how to use the library to create a simple command line preprocessor. Note how "preprocess" is called. This program is presented for illustration and testing only. If incorporating this repo into your own programs, you should call "preprocess" directly. The program has been set up to imitate the behaviour of the MSVC preprocessor by setting defines and includes equivalently.

The resulting preprocessor executable can be called as follows:

```
preprocessor.exe infile.c [-Ddefine[=val]] [-Ipath] [-FIheader.h] [-check] [-flatten] [-dependencies]
```

If `-check` is specified then, after preprocessing the file, the MSVC preprocessor is called on the same file and the two postprocessed files are compared (ignoring white space differences). A success or fail message is output. If using -check you must run the above command in the "x64 native tools command prompt for VS2019" so that the program can run `cl.exe`.

`-flatten` and `-dependencies` specify using the corresponding mode as described above. If neither is specified the "full" mode is used (`-check` only makes sense for the "full" mode)

# Building the code

As described the example main program attempts to imitate the behaviour of the MSVC preprocessor. As such you need to tell it where you have installed the MSVC compiler and Windows Kits. To do this set the following variables, at the beginning of `main.cpp`, (default values shown)

```
    const string VSPath = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Tools/MSVC/14.25.28610";
    const string windowsKits = "C:/Program Files (x86)/Windows Kits/10/include/10.0.18362.0";
```

Then, build the code in Visual Studio (Build > Build Solution) in both Debug and Release modes. Please build the x64 version as the test scripts will use that executable.

# Testing the code

Open "x64 native tools command prompt for VS2019", cd to `preprocessor/examples` and run

```
testall.bat
```

This will run `preprocessor.exe` on several examples (C, C++ and resource files) and check the result against MSVC output. If any tests fail, the batch file will tell you. The output from this preprocessor is written in `.pp` files and that from MSVC is written in `.i` files so you can examine these directly.

Next, cd to `preprocessor` and run

```
test_roundtrip.bat
```

This causes the preprocessor to preproccess itself (i.e. it preprocesses `main.cpp`, `expression.cpp`, `preprocessor.cpp`). These are all checked against MSVC output. Then, the preprocessed code is compiled into another executable, `preprocessor2.exe`, which is again invoked to preprocess the preprocessor code. This is again checked against MSVC. All the output is placed in a new subdirectory "postprocessed"

Now run

```
test_roundtrip_flatten.bat
```

This is the same as `test_roundtrip.bat` except that the preprocessed code is flattened, then compiled into `preprocessor2.exe` which is invoked to preprocess the preprocessor code and the result checked against MSVC. The output files are placed in a new subdirectory "flattened"
