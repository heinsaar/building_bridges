// Main.cpp

	// INCLUDE
#include "Dtown.h"

	// MAIN
int main()
{
	srand(time(0));

/*	HashDot buildings;
	buildings.input_downtown_area();
	buildings.input_hash_dot();
*/
//	FOREVER
	DO
	{		
		HashDot buildings;

//		buildings.random(120,45, 10);	// full screen beauty
//		buildings.random(70,35, 5);		// middle size view
		buildings.random(30,15, 4);		// small view

		Downtown Altonville(buildings);
		Altonville.HashDotView();
		Altonville.BuildBridges();
		Altonville.ModelView();
		Altonville.ViewStatistics();
		display("\n Next downtown...");
	}
	CONTINUE_UPON_REQUEST;

	return 0;
}

