#include <iostream>
#include <array>
#include "../include/api/api.h" 

#include "../include/mouse/mouse.h"


int main() {
	rwa2::Mouse mouse;
	
	mouse.display_walls();
	// for(int i=0;i<5;++i)
	// 	mouse.move_forward();
		// API::moveForward();
		// std::cerr<<"Turning right";
	// mouse.new_search(2,13);
	
	if(mouse.v_new_search(15,13)){
		// {mouse.color_path();
		
		mouse.trace_path();
		std::cerr<<"TRACED PATH";}

	else
		std::cerr<<"SEARCH FAILED";
	
	std::flush(std::cerr);
	
	}
		


