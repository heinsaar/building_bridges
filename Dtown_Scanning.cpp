// Dtown_Scanning.cpp

#include "Dtown.h"

// SCANNING THE DOWNTOWN
bool Downtown::_Is_free(const _BlockSite& __b_s)
	{ return __b_s == 0; }

bool Downtown::_Is_free(const _PanelSite& __p_s)
	{ return __p_s == 0; }

bool Downtown::_Is_cross_point(const _Block& __b)
	{ return __b._B_Id == 0; }

bool Downtown::_Is_on_building(const _Scanner& __s)
	{ return (**__s)._B_Id != 0; }

bool Downtown::_On_different_buildings(const _Scanner& __a,
									   const _Scanner& __b)
	{ return (**__a)._B_Id != (**__b)._B_Id; }

bool Downtown::_Is_line_segment(const _Block& __b)
	{
		return (_Is_free(__b._N) && _Is_free(__b._S))
			|| (_Is_free(__b._W) && _Is_free(__b._E));
	}
bool Downtown::_Found_building(const _Scanner& __sk,
							   const _Scanner& __s)
	{
		return _Is_on_building(__sk) &&
		_On_different_buildings(__sk, __s);
	}
bool Downtown::_Is_on_contour(const _Scanner& __s)
	{
		if (!_Is_free(*__s) && (**__s)._B_Id == 0 &&
			_Count_free_directions(**__s) > 0)
			return true;
		return false;
	}
void Downtown::_Set_contour_id(const _Scanner& __s,
							   const _ID& __id)
	{
		_Scanner __e = __s;
		_Direction __from = NONE;
		do {
			_Set_building_id(**__e, __id);
			_Move_clockwise(__e, __from);
		} while (__e != __s);
	}
void Downtown::_Enumerate_buildings()
	{
		_Scanner __s;
		_ID __id = 1;
		for (size_t __y = 0; __y < _Dtown.max_y(); ++__y) {
			_Dtown.locate(__s, 0, __y);
			while (!__s.is_eastmost()) {
				if (_Is_on_contour(__s)) {						
					_Set_contour_id(__s, __id);
					_Isolated.push_back(__id);
					++__id;
				}
				__s.move_east();
			}
		}
	}
Downtown::_Buildingptr Downtown::_Building_location(const _ID& __n)
	{
		_Scanner __s;
			
		for (size_t __y = 0; __y < _Dtown.max_y(); ++__y) {
			_Dtown.locate(__s, 0, __y);
			while (!__s.is_eastmost()) {
				if (!_Is_free(*__s))
					if ((**__s)._B_Id == __n)
						return __s; // upper leftmost corner
				__s.move_east();
			}
		}
	}
Downtown::_Buildingptr Downtown::_Seek_north(const _Scanner& __s, size_t __n)
	{
		_Scanner __sk = __s;

		while (!__sk.is_northmost() && __n > 0) {
			__sk.move_north(); --__n;
			if (!_Is_free(*__sk))
				if (_Found_building(__sk, __s))
					return __sk;
		}
		return __s;	// did not find
	}
Downtown::_Buildingptr Downtown::_Seek_east(const _Scanner& __s, size_t __n)
	{
		_Scanner __sk = __s;

		while (!__sk.is_eastmost() && __n > 0) {
			__sk.move_east(); --__n;
			if (!_Is_free(*__sk))
				if (_Found_building(__sk, __s))
					return __sk;
		}
		return __s;	// did not find
	}
Downtown::_Buildingptr Downtown::_Seek_south(const _Scanner& __s, size_t __n)
	{
		_Scanner __sk = __s;

		while (!__sk.is_southmost() && __n > 0) {
			__sk.move_south(); --__n;
			if (!_Is_free(*__sk))
				if (_Found_building(__sk, __s))
					return __sk;
		}
		return __s;	// did not find
	}
Downtown::_Buildingptr Downtown::_Seek_west(const _Scanner& __s, size_t __n)
	{
		_Scanner __sk = __s;

		while (!__sk.is_westmost() && __n > 0) {
			__sk.move_west(); --__n;
			if (!_Is_free(*__sk))
				if (_Found_building(__sk, __s))
					return __sk;
		}
		return __s;	// did not find
	}
int Downtown::_Count_free_directions(const _Block& __b)
	{
		short __n = 0;

			if (_Is_free(__b._N)) ++__n;
			if (_Is_free(__b._E)) ++__n;
			if (_Is_free(__b._S)) ++__n;
			if (_Is_free(__b._W)) ++__n;

		return __n;
	}
bool Downtown::_Is_bridge_start(const _Block& __b, _Direction __from)
	{
	// Is one of the panels actually a start of a bridge?
		switch (__from) {
			case NORTH:
				return !_Is_free(__b._E); // bridge on east?
			case EAST:
				return !_Is_free(__b._S); // bridge on south?
			case SOUTH:
				return !_Is_free(__b._W); // bridge on west?
			case WEST:
				return !_Is_free(__b._N); // bridge on north?
		}
	}
Downtown::_BlockShape Downtown::_Block_shape(const _Block& __b)
	{
		switch(_Count_free_directions(__b)) {
			case 2:
				if (_Is_line_segment(__b))
					return LINE_SEGMENT;
				return CORNER;
			case 1:
				return T_SHAPE;
			case 0:
				return CROSS;				
		}
	}
Downtown::_WallShape Downtown::_Scanner_view(const _Block& __b,
											 _Direction __from)
	{
	// What is the block for a builder moving clockwise?
		_WallShape __at;
			
		switch(_Block_shape(__b)) {

			case LINE_SEGMENT: case T_SHAPE: {
				__at = FLAT_WALL;
				if (_Is_bridge_start(__b, __from))
					__at = INTERNAL_CORNER;					
				} break;
			case CROSS: {
				__at = INTERNAL_CORNER;
				if (_Is_cross_point(__b))
					__at = FLAT_WALL;					
				} break;
			case CORNER: {
				__at = EXTERNAL_CORNER;
				} break;
		}
		return __at;
	}
