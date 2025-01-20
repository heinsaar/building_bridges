// Dtown_Interface.cpp

#include "Dtown.h"

// CONSTRUCTOR
Downtown::Downtown(HashDot buildings)
	: _Dtown(buildings.length() + 1,
			 buildings.height() + 1)
	{
		_Process_hash_dot(buildings);
		_Enumerate_buildings();

		_H_D = buildings;

		_Total_Bridges_Length = 0;
		_Disconnected_Groups = 0;
		_Bridges = 0;		
	}
void Downtown::BuildBridges()
	{
		display(" Building bridges...");
			_Build_bridges();			
	}

// INTERFACE
void Downtown::ModelView()
	{
		_ISOLATE;

		_Scanner __s;

		_NEW_LINE;
		for (size_t __y = 0; __y < _Dtown.max_y(); ++__y) {
			_Dtown.locate(__s, 0, __y); _SGL_SPACE;
			for (size_t __x = 0; __x < _Dtown.max_x(); ++__x) {
				if (_Is_free(*__s))
					display(" ");
				else if (_Is_on_building(__s))
					//	display((**__s)._B_Id);
						display("o");
					 else // is on a bridge
						display(".");
				__s.move_east();
			}
			_NEW_LINE;
		}
	}
void Downtown::ViewStatistics()
	{
		_ISOLATE;
		_SGL_SPACE; border(23);
		display("\n Number of bridges....");
			display(_Bridges);				
		display("\n Total length.........");
			display(_Total_Bridges_Length);				
		display("\n Disconnected groups..");
			display(_Disconnected_Groups);

		if (_Bridges == 0){
			_ISOLATE;
			if (_Disconnected_Groups > 1)
				display(" No bridges are possible.");
			else
				display(" No bridges are needed.");
		}
		_NEW_LINE;
		_SGL_SPACE; border(23);
		_NEW_LINE;
	}
void Downtown::HashDotView()
	{
		_ISOLATE;			
		for (size_t __n = 0; __n < _H_D.height(); ++__n) {
			_SGL_SPACE; display(_H_D.get_line(__n));
			_NEW_LINE;
		}
		_ISOLATE;
	}