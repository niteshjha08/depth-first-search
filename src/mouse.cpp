/**
 * @file mouse.cpp
 * @author Nitesh Jha (niteshj@umd.edu), Anish Mitra (amitra12@umd.edu), Naveen Mangla (nmangla@umd.edu)
 * @brief 
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include <unistd.h>

void rwa2::Mouse::set_goal(int x,int y){
    goal_x=x;
    goal_y=y;
}

std::array<int,2> rwa2::Mouse::get_position(){
    return std::array<int,2>{m_x,m_y} ;
}

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
            //reset goal text as G and also set color of goal cell
            API::setText(goal_x,goal_y,"G");
            API::setColor(goal_x,goal_y,'w');
        }
    }
}

void rwa2::Mouse::turn_left(){
    m_direction=(m_direction+3)%4;  //calculate direction after turning left
    API::turnLeft();
}

void rwa2::Mouse::turn_right(){
    m_direction=(m_direction+1)%4; //calculate direction after turning right
    API::turnRight();
}

void rwa2::Mouse::move_forward(){
    API::moveForward();
    //update mouse x,y coordinates upon moving forward according to current mouse direction
    if(m_direction==0)
        m_y+=1;
    else if(m_direction==1)
        m_x+=1;
    else if(m_direction==2)
        m_y-=1;
    else if(m_direction==3)
        m_x-=1;

}
// return bool indicating if there is a wall in the (x,y,direction) using m_maze
bool rwa2::Mouse::is_valid( int x, int y, int direction){
    std::array<int,2> n {x,y};
    if(!(m_maze.at(x).at(y).is_wall(direction)))
        return true;
    else return false;
}

// return bool if the (x,y) is visited in searching path
bool rwa2::Mouse::is_visited(int x, int y){
    std::array<int,2> n {x,y};
    return (std::find(visited.begin(),visited.end(),n)!=visited.end());

}
// aligns mouse direction m_direction to the passed 'direction'
void rwa2::Mouse::align_direction(int direction){
    int temp=(4+direction-m_direction)%4; //find difference for turning in API
    //Rotate according to difference
    if(temp==1)
        turn_right();
    if(temp==2){
        turn_right();
        turn_right();
    }
    if(temp==3)
        turn_left();
    // assign value to m_direction
    m_direction=direction;

}

// Search_maze to generate path for the mouse to follow
bool rwa2::Mouse::search_maze(int x, int y){
    
    // check if this is the goal
    if(x==goal_x && y==goal_y){
        std::cerr<<"REACHED GOAL!";
        return true;
        }
    // push (x,y) to stack if it is empty, initial condition
    else if(s.empty())
        s.push({x,y});
    // push (x,y) to vector if it is not visited earlier
    if(!is_visited(x,y))
        visited.push_back(std::array<int,2> {x, y});
    
    //Check all directions one by one. variable found_dir stores whether next movable direction is found or not.
    bool found_dir=false;

    //Only if a direction has not been found(always the case as it is checked first), north direction is checked
    if(!found_dir){
        // set next step as north only if :
        //(is there wall in north direction in current node) and (is the node to the north unvisited) is true
        if(is_valid(x,y,0) && !is_visited(x,y+1))
            {
                y+=1;
                s.push({x,y});
                found_dir=true;
                API::setColor(x,y,'g');

            }
        }

    //Check East
    if(!found_dir){
        // set next step as east only if :
        //(is there wall in east direction in current node) and (is the node to the east unvisited) is true
        if(is_valid(x,y,1) && !is_visited(x+1,y))
        {
            x+=1;
            s.push({x,y});
            found_dir=true;
            API::setColor(x,y,'g');

        }
    }

    //Check South
   if(!found_dir){
        // set next step as south only if :
        //(is there wall in south direction in current node) and (is the node to the south unvisited) is true
        if(is_valid(x,y,2) && !is_visited(x,y-1)) 
        {
            y-=1;
            s.push({x,y});
            found_dir=true;
            API::setColor(x,y,'g');

        }
    }

    //Check West
    if(!found_dir){
        // set next step as west only if :
        //(is there wall in west direction in current node) and (is the node to the west unvisited) is true
        if(is_valid(x,y,3) && !is_visited(x-1,y)) 
        {
            x-=1;
            s.push({x,y});
            found_dir=true;
            API::setColor(x,y,'g');
        }
    }
    // If no direction found still, pop the current position. if stack is empty, return false
    if(!found_dir){
        if(!s.empty()){
            API::clearColor(s.top()[0],s.top()[1]);
            s.pop();
        }
        else 
            return false;
        }
    
    if(!s.empty()){
        x=s.top()[0];
        y=s.top()[1];
        search_maze(x,y);
    }
    else return false;
}


bool rwa2::Mouse::move_path_step(int x, int y){
    // optimizing as walls are being found at every step while moving
    m_maze.at(m_x).at(m_y).set_wall(m_direction,API::wallFront());
    m_maze.at(m_x).at(m_y).set_wall((m_direction+3)%4,API::wallLeft());
    m_maze.at(m_x).at(m_y).set_wall((m_direction+1)%4,API::wallRight());
    display_walls(); //update display of walls
    int rotation_direction {0};
    // stores if current position is same as (x,y)
    bool same_pos=true;
    // Determine direction to move between (x,y) and mouse position (m_x,m_y)
    if(y-m_y!=0){
        same_pos=false;
        if(y-m_y==-1)
            rotation_direction=2;
        else if(y-m_y==1)
            rotation_direction=0;
    }

    else if(x-m_x!=0){
        same_pos=false;
        if(x-m_x==-1)
            rotation_direction=3;
        else if(x-m_x==1)
            rotation_direction=1;

    }
    
    // execute motion only if wall is not in front and (x,y) is not same as current mouse position
    if(!same_pos)
        {
        align_direction(rotation_direction);
        if(API::wallFront()){
            return false;}
        move_forward();
        return true;

        } 
        return true;
}

// Trace the stack generated by search_maze()
bool rwa2::Mouse::trace_path(){

    std::stack<std::array<int,2>> temp;
    std::stack<std::array<int,2>> s_temp=s;

    //Reversing stack to traverse node by node.
    int len=s.size();
    for(int i=0;i<len;++i){
        temp.push({s_temp.top()[0],s_temp.top()[1]});
        s_temp.pop();
    }

    // Move step by step
    for(int i=0;i<len;++i){
        if(!move_path_step(temp.top()[0],temp.top()[1])) //if cannot move-wall found, pop, and go to top node.
            {
            modify_maze(m_x,m_y,m_direction);
            std::stack<std::array<int,2>> empty_stack{};
            API::clearAllColor();
            s=empty_stack; // empty stack for new search with newly found walls
            std::vector<std::array<int,2>> empty_vector {};
            visited=empty_vector; //empty vector visited for new search with newly found walls
            return false;
            }
        temp.pop();
        
    }
    return true;

}

//Modify in case there was wall found while executing stack generated by search_maze()
void rwa2::Mouse::modify_maze(int x,int y, int direction){
    m_maze.at(x).at(y).set_wall(direction,true);
    display_walls();
}
