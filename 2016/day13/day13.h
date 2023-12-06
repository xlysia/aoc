#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <queue>
#include "utils/cvutils.h"


using namespace std;

namespace aoc2016{
    namespace day13{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day13/day13sample")=="11");
            std::cout << solvedayp1("./2016/day13/day13") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2016/day13/day13") << std::endl;
        }

        bool isWall(int x, int y, int fav){
            int res = x*x + 3*x + 2*x*y + y + y*y + fav;
            int count = 0;
            while (res > 0){
                if (res % 2 == 1){
                    count++;
                }
                res = res >> 1;
            }
            return count % 2 == 1;
        }


        pair<int,int> adj[4]{{1,0},{-1,0},{0,1},{0,-1}};

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int fav = 0,dx,dy;
            std::cin >> fav >> dx >> dy;

            int grid[100][100];
            memset(grid,-1,sizeof(grid));
            int W = 100;
            newFrame(cv::Size(W,W),cv::Scalar(0,0,0));
            queue<pair<int,int>> queue;
            queue.push({1,1});
            grid[1][1] = 0;
            setPixel(1,1,cv::Vec3b(255,255,255));
            setPixel(dx,dy,cv::Vec3b(0,255,0));
            int ans = 0;
            while(!queue.empty())
            {
                int s = queue.size();
                while(s--){ 
                    auto [i,j] = queue.front();
                    queue.pop();

                    for(auto [x,y] : adj){
                        x+=i,y+=j;
                        if(x < 0 || y < 0 || x >= W || y >= W || grid[x][y] != -1){
                            continue;
                        }
                        if(isWall(x,y,fav)){
                            grid[x][y] = 1;
                            setPixel(x,y,cv::Vec3b(100,100,100));
                            continue;
                        }else{
                            grid[x][y] = 0;
                            setPixel(x,y,cv::Vec3b(255,255,255));
                            if(x == dx && y == dy){
                                return std::to_string(ans+1);
                            }
                            queue.push({x,y});
                        }

                        resize(10);
                        showResize("2016day13",10);
                    }
                }



                ans++;
            }


            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            int fav = 0,dx,dy;
            std::cin >> fav >> dx >> dy;

            int grid[100][100];
            memset(grid,-1,sizeof(grid));
            int W = 100;
            newFrame(cv::Size(W,W),cv::Scalar(0,0,0));
            queue<pair<int,int>> queue;
            queue.push({1,1});
            grid[1][1] = 0;
            setPixel(1,1,cv::Vec3b(255,255,255));
            setPixel(dx,dy,cv::Vec3b(0,255,0));
            int ans = 1;
            int depth = 0;
            while(!queue.empty())
            {
                int s = queue.size();
                while(s--){ 
                    auto [i,j] = queue.front();
                    queue.pop();

                    for(auto [x,y] : adj){
                        x+=i,y+=j;
                        if(x < 0 || y < 0 || x >= W || y >= W || grid[x][y] != -1){
                            continue;
                        }
                        if(isWall(x,y,fav)){
                            grid[x][y] = 1;
                            setPixel(x,y,cv::Vec3b(100,100,100));
                            continue;
                        }else{
                            grid[x][y] = 0;
                            setPixel(x,y,cv::Vec3b(255,255,255));
                            queue.push({x,y});
                            ans++;
                        }

                        resize(10);
                        showResize("2016day13",10);
                    }
                }



                if(++depth>=50)return std::to_string(ans);
            }
            return std::to_string(-1);
        }
    }
}

