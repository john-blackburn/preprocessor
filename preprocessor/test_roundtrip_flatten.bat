echo off
setlocal

..\x64\Release\preprocessor.exe preprocessor.cpp -flatten
if %errorlevel% neq 0 exit /b %errorlevel%

..\x64\Release\preprocessor.exe expression.cpp -flatten
if %errorlevel% neq 0 exit /b %errorlevel%

..\x64\Release\preprocessor.exe main.cpp -flatten
if %errorlevel% neq 0 exit /b %errorlevel%

if not exist flattened mkdir flattened

copy preprocessor.cpp.pp flattened\preprocessor.cpp
copy expression.cpp.pp flattened\expression.cpp
copy main.cpp.pp flattened\main.cpp

cd flattened
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
