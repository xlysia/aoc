#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include "utils/cvutils.h"

namespace aoc2015{
    namespace day18{
        int grid_size = 10;
        int step = 4;
        bool bStayOn = false;
        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            grid_size = 6;
            step = 4;
            assert (solvedayp1("./2015/day18/day18sample")=="4");
            grid_size = 100;
            step = 100;
            std::cout << solvedayp1("./2015/day18/day18") << std::endl;

            std::cout << "Part 2" << std::endl;
            grid_size = 6;
            step = 5;
            assert (solvedayp2("./2015/day18/day18sample")=="17");
            grid_size = 100;
            step = 100;
            std::cout << solvedayp2("./2015/day18/day18") << std::endl;
        }

        void parse(bool** grid){
            std::string line;
            int l = 0;
            int W = grid_size + 2;
            newFrame(cv::Size(W,W),cv::Scalar(0,0,0));
            while(std::getline(std::cin,line)){
                l++;
                for(int i = 0;i<(int)line.size();i++){
                    if(line[i] == '#'){
                        grid[l][i+1] = true;
                        setPixel(i+1,l,cv::Vec3b(255,255,255));
                    } 
                }
            }
            if(bStayOn){
                grid[1][1] = true;
                setPixel(1,1,cv::Vec3b(255,255,255));
                grid[1][W-2] = true;
                setPixel(1,W-2,cv::Vec3b(255,255,255));
                grid[W-2][1] = true;
                setPixel(W-2,1,cv::Vec3b(255,255,255));
                grid[W-2][W-2] = true;
                setPixel(W-2,W-2,cv::Vec3b(255,255,255));
            }
            resize(10);
            showResize("day18",1);
        }

        void init(bool** grid){
            int W = grid_size + 2;
            for(int i = 0; i <W; i++){
                grid[i] = new bool[W];
            } 

            for(int i = 0; i < W;i++){
                for(int j = 0; j < W;j++){
                    grid[i][j] = false;
                }
            }
            if(bStayOn){
                grid[1][1] = true;
                grid[1][W-2] = true;
                grid[W-2][1] = true;
                grid[W-2][W-2] = true;
            }
        }

        int eval(bool** grid){
            int res = 0;
            int W = grid_size + 2;
            for(int i = 1;i < W-1;i++){
                for(int j = 1;j < W-1;j++){
                    res+=grid[i][j];
                }
            }
            return res;
        }

        bool toggle(bool **grid,int k , int l){
            int res = -grid[k][l];
            for(int i = k-1;i < k+2;i++){
                for(int j = l-1;j < l+2;j++){
                    res += grid[i][j];
                }
                
            }

            return (res == 3)||(grid[k][l]&&res==2);
        }

        int explore(bool **grid,int step){
            int W = grid_size + 2;
            bool ** grids;
            grids = new bool *[W];
            init(grids);
            int n = 0;
            newFrame(cv::Size(W,W),cv::Scalar(0,0,0));

            while(n++ < step){
                for(int i = 1;i < W-1;i++){
                    for(int j = 1;j < W-1;j++){
                        if(n%2){
                            bool b = toggle(grid,i,j);
                            grids[i][j] = b;
                            setPixel(j,i,cv::Vec3b(b*255,b*255,b*255));
                        }
                        else{
                            bool b = toggle(grids,i,j);
                            grid[i][j] = b;
                            setPixel(j,i,cv::Vec3b(b*255,b*255,b*255));
                        }
                    }
                }
                if(bStayOn){
                    grid[1][1] = true;
                    setPixel(1,1,cv::Vec3b(255,255,255));
                    grid[1][W-2] = true;
                    setPixel(1,W-2,cv::Vec3b(255,255,255));
                    grid[W-2][1] = true;
                    setPixel(W-2,1,cv::Vec3b(255,255,255));
                    grid[W-2][W-2] = true;
                    setPixel(W-2,W-2,cv::Vec3b(255,255,255));
                    grids[1][1] = true;
                    grids[1][W-2] = true;
                    grids[W-2][1] = true;
                    grids[W-2][W-2] = true;
                }
                resize(10);
                showResize("day18",1);
            }
            if(step%2)return eval(grids);
            else return eval(grid);
        }

        std::string solvedayp1(std::string p){
            bStayOn = false;
            bool** grid;
            grid = new bool *[grid_size+2];
            init(grid);

            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse(grid);

            int res =  explore(grid,step);
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            bStayOn = true;
            bool** grid;
            grid = new bool *[grid_size+2];
            init(grid);

            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse(grid);

            int res =  explore(grid,step);
            return std::to_string(res);
        }
    }
}

