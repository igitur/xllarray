	// xllarray.cpp
#include "xllarray.h"
#include "fmsarray.h"

using namespace xll;

#ifdef _DEBUG
#include <vector>

Auto<Open> xao([] {
	try {
		fms::sequence::iterator_test();
	}
	catch (const std::exception& ex) {
		MessageBoxA(0, ex.what(), "error", MB_OK);

		return FALSE;
	}

	return TRUE;
});
#endif // _DEBUG

