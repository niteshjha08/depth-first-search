#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

// void rwa2::Mouse::display_walls() {
//     for (int x = 0; x < m_maze_width; x += 1) {
//         for (int y = 0; y < m_maze_height; y += 1) {
//             if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
//                 //display this wall in the simulator
//                 API::setWall(x, y, 'n');
//             }
                
//             if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
//                 //display this wall in the simulator
//                 API::setWall(x, y, 'e');
//             }
                
//             if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
//                 //display this wall in the simulator
//                 API::setWall(x, y, 's');
//             }
                
//             if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
//                 //display this wall in the simulator
//                 API::setWall(x, y, 'w');
//             }
//             //display the number of walls surrounding the current node
//             API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
//         }
//     }
// }

// void rwa2::Mouse::turn_left(){
//     m_direction=(m_direction+3)%4;
//     std::cout<<"Turning left";
//     // API::turnLeft();
// }

// void rwa2::Mouse::turn_right(){
//     m_direction=(m_direction+1)%4;
//     std::cout<<"Turning right";
//     // API::turnRight();
// }

// void rwa2::Mouse::move_forward(){
//     // API::moveForward();
//     if(m_direction==direction::NORTH)
//         m_y+=1;
//     else if(m_direction==direction::EAST)
//         m_x+=1;
//     else if(m_direction==direction::SOUTH)
//         m_y-=1;
//     else if(m_direction==direction::WEST)
//         m_x-=1;

// }

// bool rwa2::Mouse::is_valid(int x,int y, int direction){
//     std::array<int,2> n {x,y};
//     if(!(m_maze.at(x).at(y).is_wall(direction)) && (std::find(visited.begin(),visited.end(),n)!=visited.end()))
//         return true;
//     else return false;
// }

// bool rwa2::Mouse::search_maze(int goal_x,int goal_y){

//     if(m_x==goal_x && m_y==goal_y)
//         return true;
//     else if(s.empty())
//         s.push({m_x,m_y});
    

//     std::array<int,2> n {m_x,m_y};
//     if (!(std::find(visited.begin(),visited.end(),n)!=visited.end())){
//         visited.push_back(n);
//     }

//     // Check for first direction in which wall is not present - N,E,S,W

//     // Check for North:
//     if(is_valid(m_x,m_y,0)){
//         s.push({m_x,m_y});
//         int temp=m_direction-0;
//         for(int i=0;i<temp;++i)
//             turn_right();
//         move_forward();
//         }
//     // Check for East
//     else if(is_valid(m_x,m_y,1)){
//         s.push({m_x,m_y});
//         int temp=(1-m_direction)%4;
//         for(int i=0;i<temp;++i)
//             turn_right();
//         move_forward();}
//     // Check for South
//     else if(is_valid(m_x,m_y,2)){
//         s.push({m_x,m_y});
//         int temp=(2-m_direction)%4;
//         for(int i=0;i<temp;++i)
//             turn_right();
//         move_forward();}
//     // Check for West
//     else if(is_valid(m_x,m_y,3)){
//         s.push({m_x,m_y});
//         int temp=(3-m_direction)%4;
//         for(int i=0;i<temp;++i)
//             turn_right();
//         move_forward();}

//     // No where to go, all sides are either walls or visited nodes.
//     // Pop topmost, and repeat for last visited node.
//     else {
//         if(!(s.empty()))
//             s.pop();
//         else return false;
//     }
//     // After popping, if the stack is not empty, repeat the search maze with position of last visited node.
//     if(!s.empty()){
//         m_x,m_y=s.top()[0],s.top()[1];
//         search_maze(goal_x,goal_y);

//     }
//     // If empty, too bad bro not found :/
//     else return false;
// }

int main(){
    std::stack<std::array<int,2>> a;
    a.push({2,1});
    a.push({5,6});
    for(int i=0;i<2;++i){
        std::cout<<a.top()[0]<<a.top()[1];
        a.pop();
    }
}
