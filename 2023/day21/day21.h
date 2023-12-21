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
            std::cout << solvedayp1("./2023/day21/day21",64) << std::endl;

            std::cout << "Part 2" << std::endl;
    //        assert (solvedayp2("./2023/day21/day21sample",5000)=="16733044");
            std::cout << solvedayp2("./2023/day21/day21",26501365) << std::endl;
        }

        std::string solvedayp1(std::string p,int steps){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int ans =  0;

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

            int m = grid.size(), n = grid[0].size();

            queue<point> q;
            q.push(start);

            point adj[4] = {{0,1},{0,-1},{1,0},{-1,0}};
            int N = 0;
            while(N++ < steps && !q.empty()){
                ans = q.size();
                while(ans--){
                    auto [i,j] = q.front();
                    q.pop();
                    for(auto [x,y] : adj){
                        x+=i,y+=j;
                        if(x<0||y<0||x>=m||y>=n || grid[x][y] == '#'||visited[x][y] >= N)continue;
                        q.push({x,y});
                        visited[x][y] = N;
                    }
                }
            }
            ans = q.size();
            return std::to_string(ans);
        }

        pair<int,int> adj[4] = {{0,1},{0,-1},{1,0},{-1,0}};

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

            int m = grid.size();

            set<tuple<int,int,int>> visited;
            int maxdepth = (steps%m) + 2*m;
            vector<int> frontiers(maxdepth);
            dfs(get<0>(start),get<1>(start),0,maxdepth,grid,visited,frontiers);

            // extrapolate
/*
b0 + (b1 * x) + (x*(x-1)/2)*(b2-b1)

*/
            int r = steps%m;
            vector<long long> ys = {frontiers[r-1],frontiers[m+r-1],frontiers[2*m+r-1]};
            long long a = ys[0];
            long long b = ys[1] - ys[0];
            long long c = ys[2] - ys[1];
            long long target = steps/m;
            ans =  a + (b * target) + (target*(target-1)/2)*(c-b);
            return std::to_string(ans);
        }
    }
}

