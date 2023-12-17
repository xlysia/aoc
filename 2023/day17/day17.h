#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <limits.h>
#include <queue>

using namespace std;

namespace aoc2023{
    namespace day17{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day17/day17sample")=="102");
            std::cout << solvedayp1("./2023/day17/day17") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day17/day17sample")=="94");
            assert (solvedayp2("./2023/day17/day17sample2")=="71");
            std::cout << solvedayp2("./2023/day17/day17") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;

            while(getline(cin , line)){
                grid.push_back(line);
            }

            int m = grid.size();
            int n = grid[0].size();
            using state = tuple<int,int,int,int,int>;
            
            priority_queue<state, vector<state>, greater<state>> minheap;
            minheap.push({0,0,0,0,0});
            minheap.push({0,0,0,0,2});
            
            vector<vector<vector<vector<bool>>>> visited(m, vector<vector<vector<bool>>>(n, vector<vector<bool>>(4, vector<bool>(4, false))));

            pair<int,int> dirs[4] = {{0,1},{0,-1},{1,0},{-1,0}};
            int oppdir[4] = {1,0,3,2};
            while(!minheap.empty()){
                auto [v , x, y, z , d] = minheap.top();
                minheap.pop();

                if(x == m-1 && y == n-1){
                    return std::to_string(v);
                }

                for(int i = 0; i < 4; i++){
                    if(z == 3 && i == d) continue;
                    if(i == oppdir[d]) continue;
                    int nx = x + dirs[i].first;
                    int ny = y + dirs[i].second;
                    if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                    int nz = i == d? z+1:1;
                    if(visited[nx][ny][i][nz]) continue;
                    int nv = v + grid[nx][ny] - '0';
                    minheap.push({nv, nx, ny, nz, i});

                    visited[nx][ny][i][nz] = true;
                }
            }

            return "FAILED";
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;

            while(getline(cin , line)){
                grid.push_back(line);
            }

            int m = grid.size();
            int n = grid[0].size();
            using state = tuple<int,int,int,int,int>;
            
            priority_queue<state, vector<state>, greater<state>> minheap;
            minheap.push({0,0,0,0,0});
            minheap.push({0,0,0,0,2});
            
            vector<vector<vector<vector<bool>>>> visited(m, vector<vector<vector<bool>>>(n, vector<vector<bool>>(4, vector<bool>(10, false))));

            pair<int,int> dirs[4] = {{0,1},{0,-1},{1,0},{-1,0}};
            int oppdir[4] = {1,0,3,2};
            while(!minheap.empty()){
                auto [v , x, y, z , d] = minheap.top();
                minheap.pop();

                if(x == m-1 && y == n-1){
                    if(z < 4)continue;
                    return std::to_string(v);
                }

                if(z < 4){
                    int nx = x + dirs[d].first;
                    int ny = y + dirs[d].second;
                    if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                    int nz = z+1;
                    if(visited[nx][ny][d][nz]) continue;
                    int nv = v + grid[nx][ny] - '0';
                    minheap.push({nv, nx, ny, nz, d});
                }else{
                    for(int i = 0; i < 4; i++){
                        if(z == 10 && i == d) continue;
                        if(i == oppdir[d]) continue;
                        int nx = x + dirs[i].first;
                        int ny = y + dirs[i].second;
                        if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                        int nz = i == d? z+1:1;
                        if(visited[nx][ny][i][nz]) continue;
                        int nv = v + grid[nx][ny] - '0';
                        minheap.push({nv, nx, ny, nz, i});

                        visited[nx][ny][i][nz] = true;
                    }
                }


            }

            return "FAILED";
        }
    }
}

