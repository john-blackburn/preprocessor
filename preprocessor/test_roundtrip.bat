echo off
setlocal

..\x64\Release\preprocessor.exe preprocessor.cpp -check
if %errorlevel% neq 0 exit /b %errorlevel%

..\x64\Release\preprocessor.exe expression.cpp -check
if %errorlevel% neq 0 exit /b %errorlevel%

..\x64\Release\preprocessor.exe main.cpp -check
if %errorlevel% neq 0 exit /b %errorlevel%

if not exist postprocessed mkdir postprocessed

copy preprocessor.cpp.pp postprocessed\preprocessor.cpp
copy expression.cpp.pp postprocessed\expression.cpp
copy main.cpp.pp postprocessed\main.cpp

cd postprocessed
cl /EHsc /c /O2 preprocessor.cpp
cl /EHsc /c /O2 expression.cpp
cl /EHsc /c /O2 main.cpp
link /OUT:preprocessor2.exe /SUBSYSTEM:CONSOLE preprocessor.obj expression.obj main.obj

if %errorlevel% neq 0 exit /b %errorlevel%

preprocessor2.exe ..\preprocessor.cpp -check
if %errorlevel% neq 0 exit /b %errorlevel%

preprocessor2.exe ..\expression.cpp -check
if %errorlevel% neq 0 exit /b %errorlevel%

preprocessor2.exe ..\main.cpp -check
if %errorlevel% neq 0 exit /b %errorlevel%

echo PASS PASS PASS PASS PASS PASS PASS PASS PASS

endlocal
echo on
