#include <iostream>
#include <array>
#include "../include/api/api.h" 

#include "../include/mouse/mouse.h"


/*
Set a goal to either of the possible goals.
Search path from origin to goal. 
*/
int main(){

	rwa2::Mouse mouse;
	std::array<int,2> G1={7,7};
	std::array<int,2> G2={7,8};
	std::array<int,2> G3={8,7};
	std::array<int,2> G4={8,8};

	mouse.set_goal(G1[0],G1[1]);

	bool found=false;
	while(mouse.search_maze(mouse.get_position()[0],mouse.get_position()[1])){ //search the path from current mouse posn. to goal
	//move along the stack generated from search_maze, trace_path traverses and returns 
	//  true if there are no obstacles and entire path is traversed, else false.
		if(mouse.trace_path())
			{found=true;
			break;}		
	}
	if(!found)
		std::cerr<<"Solution not found!";
	

	
}