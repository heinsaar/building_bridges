// Dtown.h

#ifndef _DOWNTOWN_MODEL_
#define _DOWNTOWN_MODEL_

#pragma warning (disable : 4786) // Characters truncated
#pragma warning (disable : 4715) // Not all control paths return a value

#include "Lattice.h"
#include "HashDot.h"

#include <algorithm>
#include <list>
#include <queue>

using std::list;
using std::find;
using std::queue;

	// CLASS Downtown
	class Downtown {
public:
	Downtown(HashDot);

// INTERFACE
	void BuildBridges();
	void ModelView();
	void ViewStatistics();
	void HashDotView();

private:
	struct _Panel;
	struct _Block;

	enum _Direction { NONE, NORTH, EAST, SOUTH, WEST };
	enum _BlockShape { LINE_SEGMENT, CORNER, T_SHAPE, CROSS };
	enum _WallShape { FLAT_WALL, EXTERNAL_CORNER, INTERNAL_CORNER };

	typedef Lattice<_Block*>::wanderer	_BlockPlacer;
	typedef Lattice<_Block*>::wanderer	_PanelPlacer;
	typedef Lattice<_Block*>::wanderer	_Buildingptr;
	typedef Lattice<_Block*>::wanderer	_Scanner;	
	typedef queue<_Direction>		_Directions;
	typedef string::iterator		_Symbolptr;	
	typedef _Block*				_BlockSite;
	typedef _Panel*				_PanelSite;
	typedef size_t				_ID;

	// STRUCT _Block
	struct _Block {
		_Block(_ID __bld_id = 0)
			{_N = _E = _S = _W = 0;
			_B_Id = __bld_id; }

		_ID _B_Id;
		_PanelSite _N, _E, _S, _W;
	};

	// STRUCT _Panel
	struct _Panel {};

// BUILDING BRIDGES
			void _Reset(size_t&);
	 inline bool _Is_among(const list<_ID>&, _ID);
	 inline	bool _Is_connected(_ID);
	 inline	void _Record_connection(const _ID&);
			void _Set_seek_directions(_Directions&, const _Block&);
			void _Connect_buildings(_Buildingptr, _Buildingptr, const _Direction&);
			void _Place_blocks_between(_Buildingptr, _Buildingptr, const _Direction&);
			void _Build_bridge(_PanelPlacer, vector<_Panel>&, const _Direction&);
			bool _Connect_isolated(_Scanner, int);	
			void _Connect_group(_Scanner); // the connecting algorithm
			void _Build_bridges(); // the main algorithm

// MOVING CLOCKWISE
	  _Direction _First_move_direction(const _Block&);
	  _Direction _First_from_external_corner(const _Block&);
	  _Direction _External_corner_direction(const _Direction&);
	  _Direction _Internal_corner_direction(const _Direction&);
	  _Direction _Flat_wall_direction(const _Direction&);
	  _Direction _Orient(const _Block&, _Direction&);
			void _Move(_Scanner&, _Direction&);
			void _Move_clockwise(_Scanner&, _Direction&);

// SCANNING THE DOWNTOWN
	 inline  int _Count_free_directions(const _Block&);
	 inline	bool _Is_free(const _BlockSite&);
	 inline	bool _Is_free(const _PanelSite&);
	 inline	bool _Is_cross_point(const _Block&);
	 inline	bool _Is_on_building(const _Scanner&);
	 inline	bool _Is_line_segment(const _Block&);
	 inline	bool _Is_on_contour(const _Scanner&);
	 inline	bool _Found_building(const _Scanner&,	const _Scanner&);
	 inline	bool _On_different_buildings(const _Scanner&, const _Scanner&);
			bool _Is_bridge_start(const _Block&, _Direction);
			void _Set_contour_id(const _Scanner&, const _ID&);
			void _Enumerate_buildings();
	_Buildingptr _Building_location(const _ID&);
	_Buildingptr _Seek_north(const _Scanner&, size_t);
	_Buildingptr _Seek_east(const _Scanner&, size_t);
	_Buildingptr _Seek_south(const _Scanner&, size_t);
	_Buildingptr _Seek_west(const _Scanner&, size_t);
	 _BlockShape _Block_shape(const _Block&);
	  _WallShape _Scanner_view(const _Block&, _Direction);	

// CREATING THE DOWNTOWN MODEL
	 inline	bool _Is_hash(const char&);
	 inline	void _Put_a_block(_BlockSite&);
	 inline	void _Put_panel(_PanelSite&, _Panel&);
	 inline	void _Place_panel_at(_PanelSite&, _Panel&);
	 inline	void _Place_block_at(_BlockSite&);
			void _Process_hash_dot(const HashDot&);	
			void _Set_building_id(_Block&, _ID);	
			void _Place_blocks_clockwise(_BlockPlacer);
			void _Place_panels_clockwise(_PanelPlacer);
			void _Create_downtown_model(const HashDot&);	

// OUTPUT INFO
	size_t _Bridges;
	size_t _Total_Bridges_Length;
	size_t _Disconnected_Groups;
	HashDot _H_D;

// DYNAMIC STATISTICS FOR THE MAIN ALGORITHM
	list<_ID> _Connected;
	list<_ID> _Isolated;

// IMPLEMENTATION
	Lattice<_Block*> _Dtown;
	};

#endif /* _DOWNTOWN_MODEL_ */
