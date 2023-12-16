#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day19{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day19/day19sample")=="ABCDEF - steps : 38");
            std::cout << solvedayp1("./2017/day19/day19") << std::endl;
        }


        string bfs(vector<string>& grid , int sx , int sy , int d){
            
            int m = grid.size();
            int n = grid[0].size();

            pair<int,int> dir[4] = {{1,0},{-1,0},{0,1},{0,-1}};

            string ans = "";

            int x = sx;
            int y = sy;
            int steps = 0;
            while(1){
                if(grid[x][y] == '+'){
                    for(int i = 0 ; i < 4 ; i++){
                        int nx = x + dir[i].first;
                        int ny = y + dir[i].second;
                        if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                        if(grid[nx][ny] == ' ' || (nx == sx && ny == sy))continue;
                        x = nx;
                        y = ny;
                        d = i;
                        steps++;
                        break;
                    }
                }
                else if(grid[x][y] == ' '){
                    break;
                }
                else if(grid[x][y] >= 'A' && grid[x][y] <= 'Z'){
                    ans += grid[x][y];
                    sx = x;
                    sy = y;
                    x += dir[d].first;
                    y += dir[d].second;
                    steps++;
                }
                else{
                    sx = x;
                    sy = y;
                    x += dir[d].first;
                    y += dir[d].second;
                    steps++;
                }
                if(x < 0 || x >= m || y < 0 || y >= n) break;
                
            }
            ans += " - steps : " + to_string(steps);
            return ans;

        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            getline(std::cin, line);
            int start = line.find('|');
            grid.push_back(line);
            while (std::getline(std::cin, line)){
                grid.push_back(line);
            }

            return bfs(grid, 0, start, 0);
        }

    }
}

