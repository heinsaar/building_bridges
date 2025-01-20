// Dtown_Model.cpp

#include "Dtown.h"

// CREATING THE DOWNTOWN MODEL
void Downtown::_Process_hash_dot(const HashDot& __buildings)
	{_Create_downtown_model(__buildings); }

bool Downtown::_Is_hash(const char& __symbol)
	{ return __symbol == '#'; }

void Downtown::_Set_building_id(_Block& __b, _ID __id)
	{ __b._B_Id = __id; }

void Downtown::_Put_a_block(_BlockSite& __s)
	{ __s = new _Block(); }

void Downtown::_Put_panel(_PanelSite& __s, _Panel& __pan)
	{ __s = &__pan; }

void Downtown::_Place_panel_at(_PanelSite& __s, _Panel& __pan)
	{
		if (_Is_free(__s))
			_Put_panel(__s, __pan);
	}
void Downtown::_Place_block_at(_BlockSite& __s)
	{
		if (_Is_free(__s))
			_Put_a_block(__s);
	}
void Downtown::_Place_blocks_clockwise(_BlockPlacer __b_p)
	{
		_Place_block_at(*__b_p);
			__b_p.move_east();
		_Place_block_at(*__b_p);
			__b_p.move_south();
		_Place_block_at(*__b_p);
			__b_p.move_west();
		_Place_block_at(*__b_p);
	}
void Downtown::_Place_panels_clockwise(_PanelPlacer __p_p)
	{
		_Panel __pan_1, __pan_2, __pan_3, __pan_4;

		_Place_panel_at((*__p_p)->_S, __pan_4);
		_Place_panel_at((*__p_p)->_E, __pan_1);

			__p_p.move_east();

		_Place_panel_at((*__p_p)->_W, __pan_1);
		_Place_panel_at((*__p_p)->_S, __pan_2);

			__p_p.move_south();

		_Place_panel_at((*__p_p)->_N, __pan_2);
		_Place_panel_at((*__p_p)->_W, __pan_3);

			__p_p.move_west();

		_Place_panel_at((*__p_p)->_E, __pan_3);
		_Place_panel_at((*__p_p)->_N, __pan_4);
	}
void Downtown::_Create_downtown_model(const HashDot& __buildings)
	{
		_BlockPlacer  __b_p;
		_PanelPlacer& __p_p = __b_p;

		for (size_t __h = 0; __h < __buildings.height(); ++__h) {
			_Dtown.locate(__b_p, 0, __h);
			string __hd_str = __buildings.get_line(__h);
			for (_Symbolptr __s_p = __hd_str.begin();
							__s_p < __hd_str.end();
						  ++__s_p , __b_p.move_east()) {
			    if (_Is_hash(*__s_p)) {
					_Place_blocks_clockwise(__b_p);
					_Place_panels_clockwise(__p_p);
				}
			}
		}
	}
