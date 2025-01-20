// Dtown_Main_Alg.cpp

#include "Dtown.h"

// THE CONNECTING ALGORITHM
void Downtown::_Connect_group(_Scanner __s)
	{
		_Record_connection((**__s)._B_Id);

		size_t __dist = 1; // seek depth
		size_t __max_depth = max(_Dtown.max_x(), _Dtown.max_y());

		_Direction __from = NONE;	  // first move always from
		_Move_clockwise(__s, __from); // an EXTERNAL_CORNER
		_Scanner __start = __s;		  // from WEST to EAST
 
		while (__dist != __max_depth) {				
			do {
				if (_Is_on_building(__s)) { // may be on a bridge!
					bool __found = _Connect_isolated(__s, __dist);
					if (_Isolated.empty())
						return;
					if (__found)
						_Reset(__dist); // reset seek depth
				}
				_Move_clockwise(__s, __from);
			} while (__s != __start);
			if (__from == WEST) // done full cycle
				++__dist;
		}
		_Connected.clear();
	}
// THE MAIN ALGORITHM
void Downtown::_Build_bridges()
	{
		_Buildingptr __b;
		while (!_Isolated.empty()) {
			__b = _Building_location(_Isolated.front());
			_Connect_group(__b);
			++_Disconnected_Groups;
		}
	}