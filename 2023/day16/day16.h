#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <utils/cvutils.h>


using namespace std;

namespace aoc2023{
    namespace day16{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day16/day16sample")=="46");
            std::cout << solvedayp1("./2023/day16/day16") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day16/day16sample")=="51");
            std::cout << solvedayp2("./2023/day16/day16") << std::endl;
        }

        int bfs(vector<string>& grid , int x, int y , int d ,bool draw = false){
            int m = grid.size();
            int n = grid[0].size();

            if(draw)newFrame(cv::Size(n, m), cv::Scalar(0,0,0));

            // bfs
                                    // R      L       D      U
            pair<int, int> dir[4] = {{0,1}, {0,-1}, {1,0}, {-1,0}}; 

            queue<tuple<int, int,int>> q;

            switch (grid[x][y])
            {
            
            case '/':
                if(d == 0){
                    d = 3;
                }else if(d == 1){
                    d = 2;
                }else if(d == 2){
                    d = 1;
                }else if(d == 3){
                    d = 0;
                }
                q.push({x, y, d});
                break;
            case '\\':
                if(d == 0){
                    d = 2;
                }else if(d == 1){
                    d = 3;
                }else if(d == 2){
                    d = 0;
                }else if(d == 3){
                    d = 1;
                }
                q.push({x, y, d});
                break;
            case '|':
                if(d >= 2)q.push({x, y, d});
                else{
                    q.push({x, y, 2});
                    q.push({x, y, 3});
                }
                break;
            case '-':
                if(d < 2)q.push({x, y, d});
                else{
                    q.push({x, y, 0});
                    q.push({x, y, 1});
                }
                break;
            default:q.push({x, y, d});break;
            }

            bool visited[m][n];
            memset(visited, false, sizeof(visited));
            bool memo[m][n][4];
            memset(memo, false, sizeof(memo));
            
            memo[x][y][d] = true;
            visited[x][y] = true;
            int ans = 1;

            while(!q.empty()){
                auto [x, y, d] = q.front();
                if(draw){
                    setPixel(y,x, cv::Vec3b(255,255,255));
                    resize(10);
                    showResize("Day 16", 1);
                }              
                q.pop();

                x += dir[d].first;
                y += dir[d].second;
                if(x < 0 || x >= m || y < 0 || y >= n){
                    continue;
                }
                if(memo[x][y][d])continue;
                if(!visited[x][y]){
                    visited[x][y] = true;
                    ans++;
                }
                memo[x][y][d] = true;
                switch (grid[x][y])
                {
                
                case '/':
                    if(d == 0){
                        d = 3;
                    }else if(d == 1){
                        d = 2;
                    }else if(d == 2){
                        d = 1;
                    }else if(d == 3){
                        d = 0;
                    }
                    q.push({x, y, d});
                    break;
                case '\\':
                    if(d == 0){
                        d = 2;
                    }else if(d == 1){
                        d = 3;
                    }else if(d == 2){
                        d = 0;
                    }else if(d == 3){
                        d = 1;
                    }
                    q.push({x, y, d});
                    break;
                case '|':
                    if(d >= 2)q.push({x, y, d});
                    else{
                        q.push({x, y, 2});
                        q.push({x, y, 3});
                    }
                    break;
                case '-':
                    if(d < 2)q.push({x, y, d});
                    else{
                        q.push({x, y, 0});
                        q.push({x, y, 1});
                    }
                    break;
                default:q.push({x, y, d});break;
                }
            }

            if(draw){
                resize(10);
                showResize("Day 16", 0);
            }

            return ans;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;

            while (getline(cin, line))
            {
                grid.push_back(line);
            }
            
            return std::to_string(bfs(grid, 0, 0, 0, true));
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;

            while (getline(cin, line))
            {
                grid.push_back(line);
            }
            
            int m = grid.size();
            int n = grid[0].size();

            int ans = 0;

            for(int i = 0; i < m; i++){
                ans = max(ans, bfs(grid, i, 0, 0));
                ans = max(ans, bfs(grid, i, n-1, 1));
            }
            for(int j = 0; j < n; j++){
                ans = max(ans, bfs(grid, 0, j, 2));
                ans = max(ans, bfs(grid, m-1, j, 3));
            }

            return std::to_string(ans);
        }
    }
}

