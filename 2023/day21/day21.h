#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <utils/cvutils.h>


using namespace std;


namespace aoc2023{
    namespace day21{

        std::string solvedayp1(std::string p,int steps);
        std::string solvedayp2(std::string p, int steps);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day21/day21sample",6)=="16");
            std::cout << solvedayp1("./2023/day21/day21",64) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2023/day21/day21",26501365) << std::endl;
        }
        pair<int,int> adj[4] = {{0,1},{0,-1},{1,0},{-1,0}};

        int bfs(pair<int,int> start, int steps, vector<string>& grid){
            int ans = 0;
            int m = grid.size(), n = grid[0].size();
            vector<vector<bool>> seen (m,vector<bool>(n,false));
            vector<vector<bool>> frontier(m,vector<bool>(n,false));

            queue<tuple<int,int,int>> q;
            q.push({start.first,start.second,steps});

            while(!q.empty()){
                auto [i,j,d] = q.front();
                q.pop();
                if(d%2==0 && !frontier[i][j]){ans++;frontier[i][j]=true;}
                if(d==0)continue;
                for(auto [x,y] : adj){
                    x+=i,y+=j;
                    if(x<0||y<0||x>=m||y>=n || grid[x][y] == '#'||seen[x][y])continue;
                    q.push({x,y,d-1});
                    seen[x][y] = true;
                }
            }

            return ans;
        }

        std::string solvedayp1(std::string p,int steps){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            vector<vector<int>> visited;
            using point = pair<int,int>;

            point start;

            while(getline(cin,line)){
                if(line.find("S")!=string::npos){
                    start = {grid.size(),line.find("S")};
                }
                visited.push_back({});
                for(char c: line)visited.back().push_back(c=='#'?INT_MAX:0);
                grid.push_back(line);
            }
            int m = grid.size();
            vector<string> biggrid(5*m,string(5*m,'.'));
            // copy grid inside each of biggrid tiles
            for(int a = 0; a < 5; a++){
                for(int b = 0; b < 5; b++){
                    for(int i = 0; i < m; i++){
                        for(int j = 0; j < m; j++){
                            biggrid[a*m+i][b*m+j] = grid[i][j];
                        }
                    }
                }
            }
            // we start at the center of the biggrid
            int sx = 2*m + m/2, sy = 2*m + m/2;
            int ans = bfs({sx,sy},steps,biggrid);
            return std::to_string(ans);
        }


        void dfs(int i,int j, int d, int max_depth , vector<string>& grid, set<tuple<int,int,int>>& visited,vector<int>& frontiers){
            if(d == max_depth)return;
            int n = grid.size();

            for(auto [x,y] : adj){
                x+=i,y+=j;
                if(grid[((x%n)+n)%n][((y%n)+n)%n] == '#')continue;
                if(visited.count({x,y,d}))continue;
                visited.insert({x,y,d});
                frontiers[d]++;
                dfs(x,y,d+1,max_depth,grid,visited,frontiers);
            }
            
        }



        std::string solvedayp2(std::string p,int steps){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            long long ans =  0;

            vector<string> grid;
            
            using point = tuple<int,int,int,int>; // x,y i,j (index of tile)

            point start;

            while(getline(cin,line)){
                if(line.find("S")!=string::npos){
                    start = {grid.size(),line.find("S"),0,0};
                }
                grid.push_back(line);
            }

            // extrapolate  

            /*     X 
                 X X X
               X X X X X
                 X X X 
                   X
                each X is a tile that is the current input grid create the big one            
            */
            int m = grid.size();
            vector<string> biggrid(5*m,string(5*m,'.'));
            // copy grid inside each of biggrid tiles
            for(int a = 0; a < 5; a++){
                for(int b = 0; b < 5; b++){
                    for(int i = 0; i < m; i++){
                        for(int j = 0; j < m; j++){
                            biggrid[a*m+i][b*m+j] = grid[i][j];
                        }
                    }
                }
            }
            // we start at the center of the biggrid
            int sx = 2*m + m/2, sy = 2*m + m/2;

            int r = steps%m;

            vector<long long> ys = {bfs({sx,sy},r,biggrid),bfs({sx,sy},r+m,biggrid),bfs({sx,sy},r+2*m,biggrid)};

            // get ys with dfs


/*
b0 + (b1 * x) + (x*(x-1)/2)*(b2-b1)
*/

            long long a = ys[0];
            long long b = ys[1] - ys[0];
            long long c = ys[2] - ys[1];

            long long target = steps/m;
            ans =  a + (b * target) + (target*(target-1)/2)*(c-b);
            return std::to_string(ans);
        }
    }
}

