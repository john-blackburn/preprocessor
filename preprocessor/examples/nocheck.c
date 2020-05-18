#if defined(_IS_ASSIGNABLE_NOCHECK_SUPPORTED) && !defined(__CUDACC__)
IS_ASSIGNABLE_NOCHECK_SUPPORTED = _IS_ASSIGNABLE_NOCHECK_SUPPORTED
#endif
#ifdef _STL_COMPILER_PREPROCESSOR
_STL_COMPILER_PREPROCESSOR
#else
false
#endif

#ifdef __STDC__   // only if /Za
I am standard C __STDC__
#endif

#ifdef __STDC_HOSTED__
I am hosted implementation C __STDC_HOSTED__
#endif

// This is a .c file so normally not defined. However we can force C++ compilation using /TP
#ifdef __cplusplus
I am C++
#endif

// This is a .c file so normally not defined. However we can force C++ compilation using /TP
#ifdef __STDCPP_THREADS__
STDCPP_THREADS__ = __STDCPP_THREADS__
#endif
