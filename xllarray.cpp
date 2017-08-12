// xllarray.cpp
#include "xllarray.h"
#include "fmsarray.h"

using namespace xll;

#ifdef _DEBUG
#include <vector>

Auto<Open> xao([] {
	try {
		std::vector<int> v{1,2,3};
		{
			auto i = fms::sequence::make_iterator(v.begin(), v.end());
			auto i2(i);
			i = i2;
			ensure (i == i2);
			ensure (*i == 1);
			ensure (*++i == 2);
			ensure (*i++ == 2);
			ensure (*i == 3);
			ensure (i);
			++i;
			ensure (!i);
			std::advance(i, -1);
			ensure (i);
			ensure (*i == 3);
		}
		{
			auto i = fms::sequence::make_iterator(v);
			auto i2(i);
			i = i2;
			ensure (i == i2);
			ensure (*i == 1);
			ensure (*++i == 2);
			ensure (*i++ == 2);
			ensure (*i == 3);
			ensure (i);
			++i;
			ensure (!i);
			std::advance(i, -1);
			ensure (i);
			ensure (*i == 3);
		}
	}
	catch (const std::exception& ex) {
		MessageBoxA(0, ex.what(), "error", MB_OK);

		return FALSE;
	}

	return TRUE;
});
#endif // _DEBUG

