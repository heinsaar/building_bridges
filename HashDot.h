// HashDot.h

#ifndef _HASH_DOT_
#define _HASH_DOT_

#pragma warning (disable : 4786)

#include "HelpFuncs.h"

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

	// CLASS HashDot
	class HashDot {
public:
	string get_line(size_t __n) const;
	size_t height() const;
	size_t length() const;
	  void input_downtown_area();
	  void input_hash_dot();
	  void random(size_t __n, size_t __m, int __d);		

	HashDot& operator=(const HashDot& __hd);
private:
	char _random_hash_dot(int __d);

// IMPLEMENTATION
	vector<string> _H_D_Store;
	size_t _Height;
	size_t _Length;
	};


#endif /* _HASH_DOT_ */