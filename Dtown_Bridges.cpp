// Dtown_Bridges.cpp

#include "Dtown.h"

#include <algorithm> // find()

// BUILDING BRIDGES
void Downtown::_Reset(size_t& __depth)
	{ __depth = 1; }

bool Downtown::_Is_among(const list<_ID>& __c, _ID __id)
	{ return (std::find(__c.begin(), __c.end(), __id) != __c.end()); }

bool Downtown::_Is_connected(_ID __id)
	{ return _Is_among(_Connected, __id); }

void Downtown::_Record_connection(const _ID& __b_id)
	{
		_Connected.push_back(__b_id);
		_Isolated.remove(__b_id);
	}
void Downtown::_Set_seek_directions(_Directions& __dirs, const _Block& __b)
	{
		if (_Is_free(__b._N))
			__dirs.push(NORTH);
		if (_Is_free(__b._E))
			__dirs.push(EAST);
		if (_Is_free(__b._S))
			__dirs.push(SOUTH);
		if (_Is_free(__b._W))
			__dirs.push(WEST);
	}
void Downtown::_Connect_buildings(_Buildingptr __a, _Buildingptr __b,
											   const _Direction& __ab)
	{
	/*	display("\n Connecting buildings... ");
		display((**__a)._B_Id);
		if ((**__a)._B_Id > 9) _SGL_SPACE
		else _DBL_SPACE
		display((**__b)._B_Id);				*/
		size_t __n = _Dtown.distance(__a, __b);
		vector<_Panel> __panels(__n);

		_Place_blocks_between(__a, __b, __ab);
		_Build_bridge(__a, __panels, __ab);

		_Total_Bridges_Length += __n; ++_Bridges;
	}
void Downtown::_Place_blocks_between(_Buildingptr __a, _Buildingptr __b,
												  const _Direction& __ab)
	{
		switch (__ab) {
			case NORTH: {
				__a.move_north();
				while (__a != __b) {
					if (_Is_free(*__a))
						_Put_a_block(*__a);
					__a.move_north();
				}
			} break;
			case EAST: {
				__a.move_east();
				while (__a != __b) {
					if (_Is_free(*__a))
						_Put_a_block(*__a);
					__a.move_east();
				}
			} break;
			case SOUTH: {
				__a.move_south();
				while (__a != __b) {
					if (_Is_free(*__a))
						_Put_a_block(*__a);
					__a.move_south();
				}
			} break;
			case WEST: {
				__a.move_west();
				while (__a != __b) {
					if (_Is_free(*__a))
						_Put_a_block(*__a);
					__a.move_west();
				}
			} break;
		}
	}
void Downtown::_Build_bridge(_PanelPlacer __a, vector<_Panel>& __pan,
											 const _Direction& __from_a)
	{
		_PanelPlacer __b = __a;

		switch(__from_a) {
		case NORTH: {
				__b.move_north();
				for (size_t __i = 0; __i < __pan.size(); ++__i) {
					_Put_panel((**__a)._N, __pan[__i]);
					_Put_panel((**__b)._S, __pan[__i]);
					__a.move_north(); __b.move_north();
				}
			} break;
			case EAST: {
				__b.move_east();
				for (size_t __i = 0; __i < __pan.size(); ++__i) {
					_Put_panel((**__a)._E, __pan[__i]);
					_Put_panel((**__b)._W, __pan[__i]);
					__a.move_east(); __b.move_east();
				}
			} break;
			case SOUTH: {
				__b.move_south();
				for (size_t __i = 0; __i < __pan.size(); ++__i) {
					_Put_panel((**__a)._S, __pan[__i]);
					_Put_panel((**__b)._N, __pan[__i]);
					__a.move_south(); __b.move_south();
				}
			} break;
			case WEST: {
				__b.move_west();
				for (size_t __i = 0; __i < __pan.size(); ++__i) {
					_Put_panel((**__a)._W, __pan[__i]);
					_Put_panel((**__b)._E, __pan[__i]);
					__a.move_west(); __b.move_west();
				}
			} break;
		}
	}
bool Downtown::_Connect_isolated(_Scanner __s, int __d)
	{
		int& __depth = __d; // seek depth
		_Directions __dirs;
		_Set_seek_directions(__dirs, **__s);

		bool __found = false;

		while (!__dirs.empty()) {

			_Buildingptr __c; // closest at __d distance

			switch (__dirs.front()) {
				case NORTH: {
					__c = _Seek_north(__s, __depth);
					if (__c != __s) // found?
						if (__found = !_Is_connected((**__c)._B_Id)) {
							_Connect_buildings(__s, __c, NORTH);
							_Record_connection((**__c)._B_Id);
						}						
				} break;
				case EAST: {
					__c = _Seek_east(__s, __depth);
					if (__c != __s) // found?
						if (__found = !_Is_connected((**__c)._B_Id)) {
							_Connect_buildings(__s, __c, EAST);
							_Record_connection((**__c)._B_Id);
						}
				} break;
				case SOUTH: {
					__c = _Seek_south(__s, __depth);
					if (__c != __s) // found?
						if (__found = !_Is_connected((**__c)._B_Id)) {
							_Connect_buildings(__s, __c, SOUTH);
							_Record_connection((**__c)._B_Id);
						}						
				} break;
				case WEST: {
					__c = _Seek_west(__s, __depth);
					if (__c != __s) // found?
						if (__found = !_Is_connected((**__c)._B_Id)) {
							_Connect_buildings(__s, __c, WEST);
							_Record_connection((**__c)._B_Id);
						}
				} break;
			}
			if (__found)
				return true; // found!
			__dirs.pop(); // seek next...
		}
		return false; // did not find
	}
