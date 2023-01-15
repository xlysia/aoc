#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include "utils/cvutils.h"

namespace aoc2017{
    namespace day3{
        
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2017/day3/day3") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2017/day3/day3") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int target;
            std::cin >> target;
            int side = std::sqrt(target)+2;
            if(side%2==0)side--;
            int first_o = (side-2)*(side-2)+1;
            int chr = first_o + side - 2;
            if(target <= chr){
                int a = target - first_o;
                int x = side /2;
                int y = -(side/2)+1+a;
                return std::to_string(abs(x) + abs(y));
            }
            first_o = chr;
            chr += side - 1;
            if(target <= chr){
                int a = target - first_o;
                int x = side /2 - a;
                int y = (side/2);
                return std::to_string(abs(x) + abs(y));
            }
            first_o = chr;
            chr += side - 1;
            if(target <= chr){
                int a = target - first_o;
                int x = -side /2;
                int y = (side/2)-a;
                return std::to_string(abs(x) + abs(y));
            }
            
            int y = -(side/2);
            int x = -side/2 + target - chr;
            return std::to_string(abs(x)+abs(y));
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int target = 0;
            std::cin >> target;
            int table[50][50];
            for(int i = 0; i < 50;i++){
                for(int j = 0; j < 50;j++){
                    table[i][j] = 0;
                }
            }

            Point O[4] = {Point(1,0),Point(0,-1),Point(-1,0),Point(0,1)};
            int idx = 3;
            Point u(25,25);
            int res = 1;
            table[u.y][u.x] = 1;
            newFrame(cv::Size(50,50),cv::Scalar(0,0,0));
            setPixel(u.x,u.y,cv::Vec3b(255,255,255));
            while(1){
                if(table[O[(idx+1)%4].y+u.y][O[(idx+1)%4].x+u.x] < 1){
                    idx = (idx+1)%4;
                }
                u += O[idx];
                res = 0;
                for(int i = u.x-1;i< u.x+2;i++){
                    for(int j = u.y-1;j< u.y+2;j++){
                        res += table[j][i];
                    }
                }
                table[u.y][u.x] = res;
                setPixel(u.x,u.y,cv::Vec3b(255,255,255));
                resize(5);
                showResize("day 3",0);
                if(res>= target)return std::to_string(res);
            }
            
            return std::to_string(res);
        }
    }
}

