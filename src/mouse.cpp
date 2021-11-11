#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<time.h>
#include <unistd.h>

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
        }
    }
}

void rwa2::Mouse::turn_left(){
    m_direction=(m_direction+3)%4;
    std::cerr<<"Turning left";
    API::turnLeft();
}
void rwa2::Mouse::v_turn_left(){
    v_direction=(v_direction+3)%4;
    std::cerr<<"Turning left";
   
}

void rwa2::Mouse::turn_right(){
    m_direction=(m_direction+1)%4;
    std::cerr<<"Turning right";
    API::turnRight();
}
void rwa2::Mouse::v_turn_right(){
    v_direction=(v_direction+1)%4;
    std::cerr<<"Turning right";
    
}

void rwa2::Mouse::move_forward(){
    API::moveForward();
    std::cerr<<"Moving forward, m_direction is:"<<m_direction;
    if(m_direction==0)
        // m_y+=1;
        {
        m_y=m_y+1;
        std::cerr<<"Incremented m_y"<<m_y;}
    else if(m_direction==1)
        {m_x+=1;
        std::cerr<<"Incremented m_x"<<m_x;
        }
    else if(m_direction==2){
        m_y-=1;
        std::cerr<<"Decremented m_y"<<m_y;
    }
    else if(m_direction==3){
        m_x-=1;
        std::cerr<<"Decremented m_x"<<m_x;
    }
    else{std::cerr<<"m_x, m_y, not changed. ";}

}

void rwa2::Mouse::v_move_forward(){
    std::cerr<<"Incrementing something, m_direction is:"<<v_direction;
    if(v_direction==0)
        // m_y+=1;
        {
        v_y=v_y+1;
        std::cerr<<"Incremented m_y"<<v_y;}
    else if(v_direction==1)
        {v_x+=1;
        std::cerr<<"Incremented m_x"<<v_x;
        }
    else if(v_direction==2){
        v_y-=1;
        std::cerr<<"Decremented m_y"<<v_y;
    }
    else if(v_direction==3){
        v_x-=1;
        std::cerr<<"Decremented m_x"<<v_x;
    }
    else{std::cerr<<"m_x, m_y, not changed. ";}

}

bool rwa2::Mouse::is_valid( int direction){
    std::array<int,2> n {m_x,m_y};
    if(!(m_maze.at(m_x).at(m_y).is_wall(direction)))
        return true;
    else return false;
}

bool rwa2::Mouse::v_is_valid( int direction){
    std::array<int,2> n {v_x,v_y};
    if(!(m_maze.at(v_x).at(v_y).is_wall(direction)))
        return true;
    else return false;
}

bool rwa2::Mouse::is_visited(int x, int y){
    std::array<int,2> n {x,y};
    return (std::find(visited.begin(),visited.end(),n)!=visited.end());

}

bool rwa2::Mouse::v_is_visited(int x, int y){
    std::array<int,2> n {x,y};
    return (std::find(v_visited.begin(),v_visited.end(),n)!=v_visited.end());

}

void rwa2::Mouse::align_direction(int direction){
    std::cerr<<"Aligning direction to : "<<direction;
    int temp=(4+direction-m_direction)%4;
    if(temp==1)turn_right();
    if(temp==2){
        turn_right();turn_right();
    }
    if(temp==3)turn_left();
    
    m_direction=direction;

}

void rwa2::Mouse::v_align_direction(int direction){
    std::cerr<<"Aligning direction to : "<<direction;
    int temp=(4+direction-v_direction)%4;
    if(temp==1)v_turn_right();
    if(temp==2){
        v_turn_right();v_turn_right();
    }
    if(temp==3)v_turn_left();
    v_direction=direction;

}

void rwa2::Mouse::go_to_node(int x, int y){
    std::cerr<<"Backtrack step executed";
    std::cerr<<"m_direction here is: "<<m_direction;
    int rotation_direction {0};
    bool same_pos=true;
    if(y-m_y!=0){
        same_pos=false;
        if(y-m_y==-1)
            rotation_direction=2;
        else if(y-m_y==1)
            rotation_direction=0;
    }

    else if(x-m_x!=0){
        same_pos=true;
        if(x-m_x==-1)
            rotation_direction=3;
        else if(x-m_x==1)
            rotation_direction=1;

    }
    if(!same_pos)
        {align_direction(rotation_direction);
        move_forward();}
}


void rwa2::Mouse::v_go_to_node(int x, int y){
    std::cerr<<"Backtrack step executed";
    std::cerr<<"m_direction here is: "<<v_direction;
    int rotation_direction {0};
    bool same_pos=true;
    if(y-v_y!=0){
        same_pos=false;
        if(y-v_y==-1)
            rotation_direction=2;
        else if(y-v_y==1)
            rotation_direction=0;
    }

    else if(x-v_x!=0){
        same_pos=true;
        if(x-v_x==-1)
            rotation_direction=3;
        else if(x-v_x==1)
            rotation_direction=1;

    }
    if(!same_pos)
        {v_align_direction(rotation_direction);
        v_move_forward();}
}

void rwa2::Mouse::give_info(int dir,int x,int y){
    // std::cerr<<"X here is:"<<x<<" and Y is: "<<y;
    // m_maze.at(x).at(y).set_wall(dir,API::wallFront());
    std::cerr<<'\n'<<"INFO: is_valid:"<<is_valid(dir)<< " is_visited: "<<is_visited(x,y)<<" wallFront():"<<API::wallFront()<<"m_direction:"<<m_direction<<'\n';

}
// Solve maze func
bool rwa2::Mouse::new_search(int goal_x,int goal_y){
    std::cerr<<"Current position: "<<m_x<<", "<<m_y;
    std::cerr<<"Current m_direction: "<<m_direction;
    std::cerr<<"Current stack length is:"<<s.size()<<'\n';
    
    std::array<int,2> n {m_x,m_y};
    if(m_x==goal_x && m_y==goal_y){
        std::cerr<<"Reached GOAL!";
        // print_stack();
        // for(int i=0;i<12;++i)
        //     move_forward();
        return true;}
    else if(s.empty())
        s.push({m_x,m_y});

    
    if(!is_visited(m_x,m_y)){
        visited.push_back(n);
    }


    //Check all directions one by one. variable found_dir stores whether next movable direction is found or not.
    bool found_dir=false;
    m_maze.at(m_x).at(m_y).set_wall(m_direction,API::wallFront());
    m_maze.at(m_x).at(m_y).set_wall((m_direction+3)%4,API::wallLeft());
    m_maze.at(m_x).at(m_y).set_wall((m_direction+1)%4,API::wallRight());
    display_walls();
    //Check North
    if(!found_dir){
        align_direction(0); //Rotate north
        give_info(0,m_x,m_y+1);
        if(is_valid(0) && !is_visited(m_x,m_y+1) && !API::wallFront()) //is_valid() gives 'wall_present according to m_maze?'
        {move_forward();
        s.push({m_x,m_y});
        found_dir=true;
        std::cerr<<"Going North."<<'\n';
        }}

    //Check East
    if(!found_dir){
        align_direction(1); //Rotate east
        give_info(1,m_x+1,m_y);
        // sleep(1);
        if(is_valid(1) && !is_visited(m_x+1,m_y) && !API::wallFront()) //is_valid() gives 'wall_present?'
        {move_forward();
        s.push({m_x,m_y});
        found_dir=true;
        std::cerr<<"Going East."<<'\n';}}

    //Check South
   if(!found_dir){
        align_direction(2); //Rotate south
        give_info(2,m_x,m_y-1);
        if(is_valid(2) && !is_visited(m_x,m_y-1) && !API::wallFront()) //is_valid() gives 'wall_present?'
        {move_forward();
        s.push({m_x,m_y});
        found_dir=true;
        std::cerr<<"Going South."<<'\n';}}

    //Check West
    if(!found_dir){
        align_direction(3); //Rotate west
        give_info(3,m_x-1,m_y);
        if(is_valid(3) && !is_visited(m_x-1,m_y) && !API::wallFront()) //is_valid() gives 'wall_present?'
        {move_forward();
        s.push({m_x,m_y});
        found_dir=true;
        std::cerr<<"Going West."<<'\n';}}
    // If no direction found still, pop the current position. if stack is empty,  return false
    // // -----Working part start ------
    // if(!found_dir) {
    //     if(!s.empty()){
    //         s.pop();
    //         go_to_node(s.top()[0],s.top()[1]);
    //         new_search(goal_x,goal_y);
    //         }
    //     else {
    //         std::cerr<<"Returning final false coz of empty stack";
    //         for(int i=0;i<10;++i)
    //             move_forward();
    //         return false;}
    // }
    // std::cerr<<"Current stack top is: "<<s.top()[0]<<", "<<s.top()[1]<<'\n';
    // new_search(goal_x,goal_y);s
    // -----Working part end------------

    // -----Trial part starts works now!--------------
    if(!found_dir){
        if(!s.empty())
            s.pop();
        else 
            return false;
        }
    if(!s.empty()){
        std::cerr<<"RECURSIVE CALL";
        go_to_node(s.top()[0],s.top()[1]);
        new_search(goal_x,goal_y);}
    else return false;
    // ------Trial part ends ------------


}

void rwa2::Mouse::print_stack(){
    int len=s.size();
    for(int i=0;i<len;++i){
        std::cerr<<s.top()[0]<<", "<<s.top()[1]<<'\n';
        s.pop();}
}

void rwa2::Mouse::v_print_stack(){
    int len=v_s.size();
    for(int i=0;i<len;++i){
        std::cerr<<v_s.top()[0]<<", "<<v_s.top()[1]<<'\n';
        v_s.pop();}
}

void rwa2::Mouse::color_path(){
    std::cerr<<"INSIDE COLORING PATH!";
    int len=v_s.size();
    for(int i=0;i<len;++i){
        API::setColor(v_s.top()[0],v_s.top()[1],'b');
        v_s.pop();
    }

}




// Search maze -virtual planning
bool rwa2::Mouse::v_new_search(int goal_x,int goal_y){
    
    std::cerr<<"Current position: "<<v_x<<", "<<v_y;
    std::cerr<<"Current m_direction: "<<v_direction;
    std::cerr<<"Current stack length is:"<<s.size()<<'\n';
    API::setColor(v_x,v_y,'r');
    std::array<int,2> n {v_x,v_y};
    if(v_x==goal_x && v_y==goal_y){
        std::cerr<<"REACHED GOAL!";
        print_stack();
        // for(int i=0;i<12;++i)
        //     move_forward();
        return true;}
    else if(v_s.empty())
        v_s.push({v_x,v_y});

    
    if(!v_is_visited(v_x,v_y)){
        v_visited.push_back(n);
    }


    //Check all directions one by one. variable found_dir stores whether next movable direction is found or not.
    bool found_dir=false;

    //Check North
    if(!found_dir){
        v_align_direction(0); //Rotate north
        give_info(0,v_x,v_y+1);
        if(v_is_valid(0) && !v_is_visited(v_x,v_y+1)) //is_valid() gives 'wall_present according to m_maze?'
        {v_move_forward();
        v_s.push({v_x,v_y});
        found_dir=true;
        std::cerr<<"Going North."<<'\n';
        }}

    //Check East
    if(!found_dir){
        v_align_direction(1); //Rotate east
        give_info(1,v_x+1,v_y);
        // sleep(1);
        if(v_is_valid(1) && !v_is_visited(v_x+1,v_y)) //is_valid() gives 'wall_present?'
        {v_move_forward();
        v_s.push({v_x,v_y});
        found_dir=true;
        std::cerr<<"Going East."<<'\n';}}

    //Check South
   if(!found_dir){
        v_align_direction(2); //Rotate south
        give_info(2,v_x,v_y-1);
        if(v_is_valid(2) && !v_is_visited(v_x,v_y-1)) //is_valid() gives 'wall_present?'
        {v_move_forward();
        v_s.push({v_x,v_y});
        found_dir=true;
        std::cerr<<"Going South."<<'\n';}}

    //Check West
    if(!found_dir){
        v_align_direction(3); //Rotate west
        give_info(3,v_x-1,v_y);
        if(v_is_valid(3) && !v_is_visited(v_x-1,v_y)) //is_valid() gives 'wall_present?'
        {v_move_forward();
        v_s.push({v_x,v_y});
        found_dir=true;
        std::cerr<<"Going West."<<'\n';}}
    // If no direction found still, pop the current position. if stack is empty, we're done, return false
    // -----Trial part starts works now!--------------
    if(!found_dir){
        if(!v_s.empty())
            v_s.pop();
        else 
            return false;
        }
    if(!v_s.empty()){
        std::cerr<<"RECURSIVE CALL";
        v_go_to_node(v_s.top()[0],v_s.top()[1]);
        v_new_search(goal_x,goal_y);}
    else return false;
    // ------Trial part ends ------------
 
}
bool rwa2::Mouse::move_path_step(int x, int y){
    std::cerr<<"MOVE_PATH_STEP";
    std::cerr<<"m_direction here is: "<<m_direction;
    int rotation_direction {0};
    bool same_pos=true;
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
    std::cerr<<"Rotation direction is:"<<rotation_direction;
    
    if(!same_pos)
        {align_direction(rotation_direction);
        if(API::wallFront()){
            std::cerr<<"Wall is in front";
            return false;}
        std::cerr<<"Robot moving forward now";
        move_forward();
        return true;

        } 
}
void rwa2::Mouse::trace_path(){
    std::cerr<<"NOW INSIDE TRACE PATH";
    std::cerr<<"Stack length is:"<<v_s.size();
    std::stack<std::array<int,2>> temp;
    int len=v_s.size();
    for(int i=0;i<len;++i){
        temp.push(v_s.top());
        v_s.pop();
    }
    std::cerr<<"TEMP length is:"<<temp.size();

    for(int i=0;i<len;++i){
        move_path_step(temp.top()[0],temp.top()[1]);
    }
}
