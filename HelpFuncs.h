// HelpFuncs.h

#ifndef _HELP_FUNCTIONS_
#define _HELP_FUNCTIONS_

	// INCLUDE
#include <iostream>
#include <ctime>

	// DECLARATIONS
#define _ISOLATE (cout << endl << endl)
#define _NEW_LINE (cout << endl)
#define _SGL_SPACE (cout << " ")
#define _DBL_SPACE (cout << "  ")
#define FOREVER while (true)
#define DO do
#define CONTINUE_UPON_REQUEST while (cin.get() != '0')

using std::cout;
using std::endl;

namespace {
		// display
	template<class Info>
	inline void display(const Info info)
		{cout << info; }

		// max
	inline int max(int a, int b)
		{return (a > b ? a : b); }

		// border
	inline void border(const int& size)
		{
			for (int j = 0; j < size; ++j)
				display("-");
		}

		// difference
	inline int difference(clock_t t1, clock_t t2)
		{ return (int)(t2 - t1); }

		// show_duration
	inline void show_duration(clock_t t1, clock_t t2)
		{
			_ISOLATE;
				display("Execution time: ");
				display(difference(t1, t2));
			_ISOLATE;
		}
} // NAMESPACE
#endif /* _HELP_FUNCTIONS_ */