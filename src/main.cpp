#include <iostream>
#include <array>
#include "../include/api/api.h" 

#include "../include/mouse/mouse.h"


// int main() {
// 	rwa2::Mouse mouse;
	
// 	mouse.display_walls();
// 	// for(int i=0;i<5;++i)
// 	// 	mouse.move_forward();
// 		// API::moveForward();
// 		// std::cerr<<"Turning right";
// 	// mouse.new_search(2,13);
// 	if(mouse.v_new_search(1,13)){
// 		// {mouse.color_path();
// 		std::cerr<<"TRACED PATH";	
// 		mouse.trace_path();
// 		// for(int i=0;i<14;++i)
//         //     mouse.move_forward();
// 		}

// 	else
// 		std::cerr<<"SEARCH FAILED";
	
// 	// std::flush(std::cerr);
	
// 	}
		

/*
Structure of calling functions:
while(true){
	if(search_maze(m_x,m_y))  ---> search the path from current mouse posn. to goal
		{if(mouse.trace_path())    ---> move along the stack generated from search_maze, trace_path traverses and returns 
										true if there are no obstacles and entire path is traversed, else false.
			break;
		
		}
}
*/
int main(){

	rwa2::Mouse mouse;
	mouse.set_goal(15,3);
	// if(mouse.search_maze(0,0))
	// 	mouse.print_stack();
	bool found=false;
	while(mouse.search_maze(mouse.get_position()[0],mouse.get_position()[1])){
	// while(mouse.search_maze(11,15)){
		if(mouse.trace_path())
			{found=true;
			// for(int i=0;i<16;++i)API::moveForward();
			break;}
		else{
			std::cerr<<"Recalculating maze";
			std::cerr<<"Mouse is at:"<<mouse.get_position()[0]<<", "<<mouse.get_position()[1];
			mouse.print_stack();
			// for(int i=0;i<16;++i)API::moveForward();
			}
			
			
	}
	// if(!found){
		// API::moveForward();
	// 	std::cout<<"Goal not found";
	// 	std::cerr<<"Goal not found";
	// }

	
}