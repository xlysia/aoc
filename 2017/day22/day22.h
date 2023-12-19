#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include "utils/cvutils.h"

using namespace std;

namespace aoc2017{
    namespace day22{

        std::string solvedayp1(std::string p,int bursts);
        std::string solvedayp2(std::string p,int bursts,bool bdraw = false);
        void run(){
            std::cout << "Part 1" << std::endl;
          /*  assert (solvedayp1("./2017/day22/day22sample",7)=="5");
            assert (solvedayp1("./2017/day22/day22sample",70)=="41");
            assert (solvedayp1("./2017/day22/day22sample",10000)=="5587");
            std::cout << solvedayp1("./2017/day22/day22",10000) << std::endl;
*/
            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day22/day22sample",100)=="26");
            assert (solvedayp2("./2017/day22/day22sample",10000000)=="2511944");
            std::cout << solvedayp2("./2017/day22/day22",10000000,1) << std::endl;
        }

        std::string solvedayp1(std::string p , int bursts){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());

            
            string line;

            getline(cin, line);
            int n = line.size();
            int m = 0;
            vector<string> grid(400,string(400 + n,'.'));

            grid[200+m++] = string(200,'.') + line + string(200,'.');
            while(getline(cin, line)){
                // copy the line in the grid
                grid[200+m++] = string(200,'.') + line + string(200,'.');
            }

            int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};

            int d = 0;

            int x = 200 + m/2;
            int y = 200 + n/2;
            int ans = 0;

            newFrame({400+n,400},cv::Scalar(0,0,0));
            for(int i = 0; i < 400; i++){
                for(int j = 0; j < 400; j++){
                    if(grid[i][j] == '#'){
                        setPixel(j,i,cv::Vec3b(255,255,255));
                    }
                }
            }

            if(grid[x][y] == '.')setPixel(y,x,cv::Vec3b(0,0,100)); 
            else setPixel(y,x,cv::Vec3b(255,255,100));

            resize(3);
            showResize("Day 22",0);


            while(bursts--){
                if(grid[x][y] == '#'){
                    d = (d+3)%4;
                    grid[x][y] = '.';
                    setPixel(y,x,cv::Vec3b(0,0,0));
                }else{
                    d = (d+1)%4;
                    grid[x][y] = '#';
                    ans++;
                    setPixel(y,x,cv::Vec3b(255,255,255));
                }
                x += dir[d][0];
                y += dir[d][1];

                if(grid[x][y] == '.')setPixel(y,x,cv::Vec3b(0,0,100)); 
                else setPixel(y,x,cv::Vec3b(255,255,100));
                resize(3);
                showResize("Day 22",1);
            }

            resize(3);
            showResize("Day 22",0);
            saveFrame("Day 22");

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p , int bursts,bool bdraw){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());

            
            string line;

            getline(cin, line);
            int n = line.size();
            int m = 0;
            vector<string> grid(1000,string(1000 + n,'.'));

            grid[500+m++] = string(500,'.') + line + string(500,'.');
            while(getline(cin, line)){
                // copy the line in the grid
                grid[500+m++] = string(500,'.') + line + string(500,'.');
            }

            int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};

            int d = 0;

            int x = 500 + m/2;
            int y = 500 + n/2;
            int ans = 0;

            if(bdraw){
                newFrame({1000+n,1000},cv::Scalar(0,0,0));
                for(int i = 0; i < 1000; i++){
                    for(int j = 0; j < 1000+n; j++){
                        if(grid[i][j] == '#'){
                            setPixel(j,i,cv::Vec3b(255,255,255));
                        }
                    }
                }
                if(grid[x][y] == '.')setPixel(y,x,cv::Vec3b(0,0,100)); 
                else setPixel(y,x,cv::Vec3b(255,255,100));
            }




            while(bursts--){
                if(grid[x][y] == '#'){
                    d = (d+3)%4;
                    grid[x][y] = 'F';
                    if(bdraw)setPixel(y,x,cv::Vec3b(200,200,200));
                }else if(grid[x][y] == '.'){
                    d = (d+1)%4;
                    grid[x][y] = 'W';
                    if(bdraw)setPixel(y,x,cv::Vec3b(125,125,125));
                }else if(grid[x][y] == 'W'){
                    grid[x][y] = '#';
                    ans++;
                    if(bdraw)setPixel(y,x,cv::Vec3b(255,255,255));
                }else if(grid[x][y] == 'F'){
                    d = (d+2)%4;
                    grid[x][y] = '.';
                    if(bdraw)setPixel(y,x,cv::Vec3b(0,0,0));
                }

                x += dir[d][0];
                y += dir[d][1];



                if(bdraw){
                    if(grid[x][y] == '.')setPixel(y,x,cv::Vec3b(0,0,100)); 
                    else setPixel(y,x,cv::Vec3b(255,255,100));
                    show("Day 22 p2",1);
                }

            }
            
            if(bdraw){
                show("Day 22 p2",0);
                saveFrame("Day 22 p2");
            }
            return std::to_string(ans);
        }
    }
}

