// Lattice.h

#ifndef _CARTESIAN_LATTICE_
#define _CARTESIAN_LATTICE_

#include <cmath> // fabs()
#include <vector>
#include <utility>

using std::pair;
using std::vector;

	// TEMPLATE CLASS Lattice
template<class _Ker>
	class Lattice {
protected:
	struct _Node;

	typedef vector<_Node> _Imp;
	typedef typename _Imp::iterator _Nodeptr;	
	typedef pair<int,int> _Location;

	// STRUCT _Node
	struct _Node {
		_Node(const _Ker& __k = _Ker())
			: _Kernel(__k)
			{_North = _East = _South = _West = 0; }
		_Nodeptr _North, _East, _South, _West;
		_Ker _Kernel;
	};

	struct _Acc;
	friend struct _Acc;

	// STRUCT _Acc
	struct _Acc {
		typedef _Nodeptr& _Nodepref;
		typedef	_Ker& _Kernelref;
		static _Nodepref _West(_Nodeptr __p)
			{return ((_Nodepref)(*__p)._West); }
		static _Nodepref _East(_Nodeptr __p)
			{return ((_Nodepref)(*__p)._East); }
		static _Nodepref _North(_Nodeptr __p)
			{return ((_Nodepref)(*__p)._North); }
		static _Nodepref _South(_Nodeptr __p)
			{return ((_Nodepref)(*__p)._South); }
		static _Kernelref _Kernel(_Nodeptr __p)
			{return ((_Kernelref)(*__p)._Kernel); }
	};
public:
	typedef _Ker* _Kptr;
	typedef const _Ker* _Ckptr;
	typedef _Ker& reference;
	typedef const _Ker& const_reference;
	typedef size_t _Coord;

	class wanderer;
	class const_wanderer;
	friend class const_wanderer;

		// CLASS const_wanderer
		class const_wanderer {
	public:
		const_wanderer()
			{}
		const_wanderer(_Nodeptr __p, _Coord __x, _Coord __y)
			{_Curr = __p; _X = __x; _Y = __y; }
		const_wanderer(const wanderer& __w)
			: _Curr(__w._Curr), _X(__w._X), _Y(__w._Y){}
		const_reference operator*() const
			{return (_Acc::_Kernel(_Curr)); }
		_Ckptr operator->() const
			{return (&**this); }

	// HORIZONTAL / VERTICAL MOVE
		const_wanderer& move_west(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_West(_Curr);
					--_X; }
			return (*this); }
		const_wanderer& move_east(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_East(_Curr);
					++_X; }
			return (*this); }
		const_wanderer& move_north(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_North(_Curr);
					--_Y; }
			return (*this); }
		const_wanderer& move_south(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_South(_Curr);
					++_Y; }
			return (*this); }

	// DIAGONAL MOVE
		const_wanderer& move_ne(size_t __n = 1)
			{return (*this).move_north(__n).move_east(__n); }
		const_wanderer& move_se(size_t __n = 1)
			{return (*this).move_south(__n).move_east(__n); }
		const_wanderer& move_sw(size_t __n = 1)
			{return (*this).move_south(__n).move_west(__n); }
		const_wanderer& move_nw(size_t __n = 1)
			{return (*this).move_north(__n).move_west(__n); }

	// LOCATION
		bool is_northmost() const
			{return _Y == 0; }
		bool is_eastmost() const
			{return _X == _Max_X; }
		bool is_southmost() const
			{return _Y == _Max_Y; }
		bool is_westmost() const
			{return _X == 0; }
		bool is_at_edge() const
			{return	(is_northmost() ||
			is_westmost() || is_eastmost() ||
					 is_southmost()); }
		_Location location() const
			{return _Location(_X,_Y); }
		_Coord x() const {return _X; }
		_Coord y() const {return _Y; }
		
	// OPERATORS
		bool operator==(const const_wanderer& __w) const
			{return (_Curr == __w._Curr); }
		bool operator!=(const const_wanderer& __w) const
			{return (!(*this == __w)); }
	protected:
		_Nodeptr _Curr;
		_Coord _X, _Y;
		};

		// CLASS wanderer
	friend class wanderer;
		class wanderer : public const_wanderer {
	public:
		wanderer()
			{}
		wanderer(_Nodeptr __p, _Coord __x, _Coord __y)
			{_Curr = __p; _X = __x; _Y = __y; }
		reference operator*() const
			{return (_Acc::_Kernel(_Curr)); }
		_Kptr operator->() const
			{return (&**this); }

	// HORIZONTAL / VERTICAL MOVE
		wanderer& move_west(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_West(_Curr);
					--_X; }				
			return (*this); }
		wanderer& move_east(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_East(_Curr);
					++_X; }
			return (*this); }
		wanderer& move_north(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_North(_Curr);
					--_Y; }
			return (*this); }
		wanderer& move_south(size_t __n = 1)
			{for (; 0 < __n; --__n)
				{_Curr = _Acc::_South(_Curr);
					++_Y; }
			return (*this); }

	// DIAGONAL MOVE
		wanderer& move_ne(size_t __n = 1)
			{return (*this).move_north(__n).move_east(__n); }
		wanderer& move_se(size_t __n = 1)
			{return (*this).move_south(__n).move_east(__n); }
		wanderer& move_sw(size_t __n = 1)
			{return (*this).move_south(__n).move_west(__n); }
		wanderer& move_nw(size_t __n = 1)
			{return (*this).move_north(__n).move_west(__n); }

	// OPERATORS
		bool operator==(const wanderer& __w) const
			{return (_Curr == __w._Curr); }
		bool operator!=(const wanderer& __w) const
			{return (!(*this == __w)); }
		};
	Lattice()
		: _Lattice() {}
	Lattice(size_t __x, size_t __y)
		: _Max_X(__x), _Max_Y(__y),
			_Lattice(__x * __y)
		{
			_Connect_horizontally();
			_Connect_vertically();		
		}

// ACCESSORS
	size_t max_x() const
		{return _Max_X; }
	size_t max_y() const
		{return _Max_Y; }

// LOCATION RELATED
	const_wanderer zero() const
		{return const_wanderer(_Lattice.begin(), 0, 0); }
	wanderer zero()
		{return wanderer(_Lattice.begin(), 0, 0); }

	int distance(const_wanderer& __a, const_wanderer& __b)
		{int __dx = __a.x() - __b.x() ;
		int __dy = __a.y() - __b.y() ;
		return (__dx != 0) ? fabs(__dx) : fabs(__dy); }

	int distance(wanderer& __a, wanderer& __b)
		{float __dx = __a.x() - __b.x() ;
		float __dy = __a.y() - __b.y() ;
		return (__dx != 0) ? fabs(__dx) : fabs(__dy); }

	const_wanderer locate(const_wanderer& __w,
			_Coord __x, _Coord __y)
		{__w = zero();
		__w.move_east(__x).move_south(__y);
				return __w;	}

	wanderer locate(wanderer& __w,
			_Coord __x, _Coord __y)
		{__w = zero();
		__w.move_east(__x).move_south(__y);
				return __w;	}
protected:

// CONNECTING THE NODES
	void _Connect_east(_Nodeptr __curr)
		{
			_Nodeptr __east = __curr + 1;
			(*__curr)._East = __east;
			(*__east)._West = __curr;
		}
	void _Connect_south(_Nodeptr __curr)
		{
			_Nodeptr __south = __curr + _Max_X;
			(*__curr)._South = __south;
			(*__south)._North = __curr;
		}
	void _Connect_horizontally()
		{
			for (_Nodeptr __y = _Lattice.begin();
						  __y < _Lattice.end(); 
						  __y += _Max_X)
				for (_Nodeptr __x = __y;
							  __x < __y + _Max_X - 1;
							++__x)
					 _Connect_east(__x);
		}
	void _Connect_vertically()
		{
			for (_Nodeptr __y = _Lattice.begin();
						  __y < _Lattice.end() - _Max_X;
						  __y += _Max_X)
				for (_Nodeptr __x = __y;
							  __x < __y + _Max_X;
							++__x)
					 _Connect_south(__x);
		}
private:
	size_t _Max_X;
	size_t _Max_Y;

// IMPLEMENTATION
	_Imp _Lattice;
	};

#endif /* _CARTESIAN_LATTICE_ */