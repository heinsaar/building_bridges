// HashDot.cpp

#include "HashDot.h"

void HashDot::input_downtown_area()
	{
		size_t __m;

		display("\nDowntown area: ");
		cin >> __m;

		_Height = __m;
		_H_D_Store.resize(__m);
	}
void HashDot::input_hash_dot()
	{			
		display("Hash dot layout:\n\n");			
		for (int __y = 0; __y < _Height; ++__y)
			cin >> _H_D_Store[__y];

		_Length = get_line(0).size();
	}
void HashDot::random(size_t __n, size_t __m, int __d)
	{
		_H_D_Store.resize(__m);

		for (int __y = 0; __y < __m; ++__y)
			for (int __x = 0; __x < __n; ++__x)
				_H_D_Store[__y] += _random_hash_dot(__d);

		_Length = __n;
		_Height = __m;
	}
HashDot& HashDot::operator=(const HashDot& __hd)
	{
		if (this == &__hd)
			;
		else {
			_H_D_Store = __hd._H_D_Store;
			_Height = __hd._Height;
			_Length = __hd._Length;
		}
		return (*this);
	}	
string HashDot::get_line(size_t __n) const
	{return _H_D_Store[__n]; }

size_t HashDot::height() const
	{return _Height; }

size_t HashDot::length() const
	{return _Length; }

char HashDot::_random_hash_dot(int __d)
	{ return (rand() % 200 < __d) ? '#' : '.'; }
