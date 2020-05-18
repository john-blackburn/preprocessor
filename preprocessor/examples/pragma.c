#pragma once

#if 0
#error "disaster"
#endif

#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(pop)

#define _tempnam 3

#pragma push_macro("_tempnam")
#undef _tempnam
_tempnam
#pragma pop_macro("_tempnam")

_tempnam
