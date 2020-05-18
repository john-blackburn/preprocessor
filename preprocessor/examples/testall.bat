echo off
setlocal

set PREPROCESSOR=..\..\x64\Debug\preprocessor.exe
set NERRORS=0

%PREPROCESSOR% afterx.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% assert.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% array.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% concat.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% continuation.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% funclike.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% funclike_space.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% func_pointer.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% if.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% if_func_macro.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% infake.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% mi.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% min.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% misnest.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% multiline_func.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% nostringexp.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% pragma.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% prescan.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% stringize_result.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% tablesize.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% tablesize2.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% unbalanced.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% unshielded.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% fibonacci.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% selfref.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% stringize.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% in.cpp -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% deprecated.cpp -check

%PREPROCESSOR% fi\fi.c -FIpch\precompiled.hpp -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% multi_include/foo.c -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

%PREPROCESSOR% longford.rc -DRC_INVOKED -check
set /a NERRORS=%NERRORS%+%ERRORLEVEL%

echo NUMBER OF ERRORS=%NERRORS%

if "%NERRORS%"=="0" (
  echo PASS PASS PASS PASS PASS PASS PASS
) else (
  echo FAIL FAIL FAIL FAIL FAIL FAIL FAIL 
)

REM %PREPROCESSOR% vararg.c -check

endlocal
