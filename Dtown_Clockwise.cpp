// Dtown_Clockwise.cpp

#include "Dtown.h"

// MOVING CLOCKWISE
Downtown::_Direction Downtown::_First_move_direction(const _Block& __b)
	{ return _First_from_external_corner(__b); }

Downtown::_Direction Downtown::_First_from_external_corner(const _Block& __b)
	{
		// always one type of EXTERNAL_CORNER
		// (for the main algorithm using the
		// current _Building_location method)

			if (_Is_free(__b._W) &&
				_Is_free(__b._N) &&
				!_Is_free(__b._E))
				return EAST;

		// other types of EXTERNAL_CORNER
		// (present here for extensibility)
	/*		if (_Is_free(__b._N) &&
				_Is_free(__b._E) &&
				!_Is_free(__b._S))
				return SOUTH;
			if (_Is_free(__b._E) &&
				_Is_free(__b._S) &&
				!_Is_free(__b._W))
				return WEST;
			if (_Is_free(__b._S) &&
				_Is_free(__b._W) &&
				!_Is_free(__b._N))
				return NORTH;			*/
	}		
Downtown::_Direction Downtown::_External_corner_direction(const _Direction& __from)
	{
		switch (__from) {				
			case NORTH:
				return WEST;
			case EAST:
				return NORTH;
			case SOUTH:
				return EAST;
			case WEST:
				return SOUTH;
		}
	}
Downtown::_Direction Downtown::_Internal_corner_direction(const _Direction& __from)
	{
		switch (__from) {				
			case NORTH:
				return EAST;
			case EAST:
				return SOUTH;
			case SOUTH:
				return WEST;
			case WEST:
				return NORTH;
		}
	}
Downtown::_Direction Downtown::_Flat_wall_direction(const _Direction& __from)
	{
		switch (__from) {
			case NORTH:
				return SOUTH;
			case EAST:					
				return WEST;
			case SOUTH:
				return NORTH;
			case WEST:
				return EAST;
		}
	}
Downtown::_Direction Downtown::_Orient(const _Block& __b, _Direction& __from)
	{
		if (__from == NONE)
			return _First_move_direction(__b);

		switch (_Scanner_view(__b, __from)) {
			case EXTERNAL_CORNER:
				return _External_corner_direction(__from);
			case INTERNAL_CORNER:
				return _Internal_corner_direction(__from);
			case FLAT_WALL:
				return _Flat_wall_direction(__from);
		}
	}
void Downtown::_Move(_Scanner& __s, _Direction& __to)
	{
		_Direction& __from = __to;
			switch (__to) {
				case NORTH: {
					__s.move_north();
					__from = SOUTH;
					} break;
				case EAST: {
					__s.move_east();
					__from = WEST;
					} break;
				case SOUTH: {
					__s.move_south();
					__from = NORTH;
					} break;
				case WEST: {
					__s.move_west();
					__from = EAST;
					} break;
			}
	}
void Downtown::_Move_clockwise(_Scanner& __s, _Direction& __from)
	{
		_Direction& __to = __from;
					__to = _Orient(**__s, __from);
		 _Move(__s, __to);
	}