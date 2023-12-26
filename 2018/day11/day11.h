#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <tuple>

using namespace std;

namespace aoc2018{
    namespace day11{

        tuple<int,int,int> solvedayp1(vector<vector<int>>& grid,int K);
        tuple<int,int,int,int> solvedayp2(vector<vector<int>>& grid);
        void parse(std::string p, int& serial){
            std::ifstream infile(p);
            infile >> serial;
            infile.close();
        }
        void run(){
            int serial;
            parse("./2018/day11/day11",serial);
            
            vector<vector<int>> grid(300,vector<int>(300,0));
            for(int i = 0; i < 300; i++){
                for(int j = 0; j < 300; j++){
                    int rackid = i+10;
                    int power = rackid*j;
                    power += serial;
                    power *= rackid;
                    power = (power/100)%10;
                    power -= 5;
                    grid[i][j] = power;
                }
            }

            // vector<int> sumRow(300,0), sumCol(300,0);
            for(int i = 1; i < 300; i++){
                grid[i][0] += grid[i-1][0];
                grid[0][i] += grid[0][i-1];
            }
            for(int i = 1; i < 300; i++){
                for(int j = 1; j < 300; j++){
                    grid[i][j] += grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1];
                }
            }

            std::cout << "Part 1" << std::endl;
            auto p1 = solvedayp1(grid,3);
            std::cout << get<1>(p1) << "," << get<2>(p1) << std::endl;

            std::cout << "Part 2" << std::endl;
            auto p2 = solvedayp2(grid);
            std::cout << get<1>(p2) << "," << get<2>(p2) << "," << get<3>(p2) << std::endl;
        }

        tuple<int,int,int> solvedayp1(vector<vector<int>>& grid,int K){
            int max = 0;
            int x = 0;
            int y = 0;
            int m = grid.size();

            for(int i = 0; i < m-K; i++){
                for(int j = 0; j < m-K; j++){
                    int sum = grid[i+K][j+K] - grid[i][j+K] - grid[i+K][j] + grid[i][j];
                    if(sum > max){
                        max = sum;
                        x = i+1;
                        y = j+1;
                    }
                }
            }

            return {max,x,y};
        }

        tuple<int,int,int,int> solvedayp2(vector<vector<int>>& grid){

            int max = 0;
            int X,Y,K;
            for(int i = 1; i <= 300;i++){
                auto [m,x,y] = solvedayp1(grid,i);
                if(m > max){
                    max = m;
                    K = i;
                    X = x;
                    Y = y;
                }
            }

            return {max,X,Y,K};
        }
    }
}

