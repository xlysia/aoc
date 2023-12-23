#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <unordered_map>
#include <utils/cvutils.h>

using namespace std;

#define DEBUG 0

namespace aoc2023{
    namespace day23{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day23/day23sample")=="94");
            std::cout << solvedayp1("./2023/day23/day23") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day23/day23sample")=="154");
            std::cout << solvedayp2("./2023/day23/day23") << std::endl;
        }
        using point = pair<int,int>;
        // override == operator for point
        bool operator==(const point& lhs, const point& rhs){
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
        point operator+(const point& lhs, const point& rhs){
            return {lhs.first+rhs.first, lhs.second+rhs.second};
        }
        point operator-(const point& lhs, const point& rhs){
            return {lhs.first-rhs.first, lhs.second-rhs.second};
        }
        point operator+=(const point& lhs, const point& rhs){
            return {lhs.first+rhs.first, lhs.second+rhs.second};
        }

        point dir[4] = {{0,1},{1,0},{0,-1},{-1,0}};

        int dfs(point curr, int depth , vector<string>& grid){
            int m = grid.size();
            int n = grid[0].size();
            point end = {m-1,n-2};
            if(curr == end)return depth;

            int ans = 0;
            for(auto d: dir){
                point next = curr + d;
                if(next.first < 0 || next.first >= m || next.second < 0 || next.second >= n || grid[next.first][next.second]=='#')continue;
                if( dir[0]==d && grid[next.first][next.second] != '.' &&grid[next.first][next.second] != '>' )continue;
                else if( dir[1]==d && grid[next.first][next.second] != '.' &&grid[next.first][next.second] != 'v' )continue;
                else if( dir[2]==d && grid[next.first][next.second] != '.' &&grid[next.first][next.second] != '<' )continue;
                else if( dir[3]==d && grid[next.first][next.second] != '.' &&grid[next.first][next.second] != '^' )continue;
                
                char c = grid[next.first][next.second];
                
                grid[next.first][next.second] = '#';

                #if DEBUG
                setPixel(next.second,next.first, cv::Vec3b(0,150,depth*2));
                resize(5);
                showResize("maze",1);
                #endif
                ans = max(ans ,dfs(next, depth+1, grid));
                grid[next.first][next.second] = c;
                #if DEBUG
                if(c == '.')setPixel(next.second,next.first, cv::Vec3b(255,255,255));
                else if(c == '>')setPixel(next.second,next.first, cv::Vec3b(0,0,255));
                else if(c == 'v')setPixel(next.second,next.first, cv::Vec3b(0,255,0));
                else if(c == '<')setPixel(next.second,next.first, cv::Vec3b(255,0,0));
                else if(c == '^')setPixel(next.second,next.first, cv::Vec3b(255,255,0));

                resize(5);
                showResize("maze",1);
                #endif
            }
            return ans;
        }

        int dfs2(int curr,int depth, vector<vector<point>>& adj, vector<bool>& visited){
            
            if(curr == 1)return depth;
            
            int ans = 0;
            for(auto n : adj[curr]){
                if(visited[n.first])continue;
                visited[n.first] = true;
                ans = max(ans, dfs2(n.first, depth+n.second, adj, visited));
                visited[n.first] = false;
            }
            return ans;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            while (getline(cin, line)){
                grid.push_back(line);
            }


            #if DEBUG

            int m = grid.size();
            int n = grid[0].size();
            newFrame(cv::Size(n,m), cv::Scalar(0,0,0));

            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    if(grid[i][j] == '#')continue;

                    if(grid[i][j] == '.')setPixel(j,i, cv::Vec3b(255,255,255));
                    else if(grid[i][j] == '>')setPixel(j,i, cv::Vec3b(0,0,255));
                    else if(grid[i][j] == 'v')setPixel(j,i, cv::Vec3b(0,255,0));
                    else if(grid[i][j] == '<')setPixel(j,i, cv::Vec3b(255,0,0));
                    else if(grid[i][j] == '^')setPixel(j,i, cv::Vec3b(255,255,0));
                }
            }
           #endif 

            point start = {0,1};
            
            int ans =  dfs(start, 0, grid);

            return std::to_string(ans);
        }

        void bfs(pair<point, int> node, vector<string>& grid, vector<vector<point>>& adj, map<point, int>& nodes){
            int m = grid.size();
            int n = grid[0].size();
            point curr = node.first;
            queue<point> q;
            q.push(curr);
            vector<bool> visited(nodes.size(), false);
            visited[node.second] = true;
            int depth = 0;
            while(!q.empty()){
                int s = q.size();
                depth++;
                while(s--){
                    curr = q.front();
                    q.pop();
                    for(auto d : dir){
                        point next = curr + d;
                        if(next.first < 0 || next.first >= m || next.second < 0 || next.second >= n || grid[next.first][next.second]=='#')continue;
                        if(grid[next.first][next.second] == 'A'){
                            if(visited[nodes[next]])continue;
                            visited[nodes[next]] = true;
                            adj[node.second].push_back({nodes[next], depth});
                            adj[nodes[next]].push_back({node.second, depth});
                            continue;
                        }
                        grid[next.first][next.second] = '#';
                        q.push(next);
                    }
                }
            }
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> grid;
            while (getline(cin, line)){
                grid.push_back(line);
            }
            point start = {0,1};
            
            // do a BFS to find all connected components
            vector<vector<point>> adj;

            map<point, int> nodes;

            int m = grid.size();
            int n = grid[0].size();

            nodes[start] = 0;
            nodes[{m-1,n-2}] = 1;
            grid[start.first][start.second] = 'A';
            grid[m-1][n-2] = 'A';

            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    if(grid[i][j] == '#')continue;
                    if(grid[i][j] == 'A')continue;

                    point curr = {i,j};

                    vector<point> adj;
                    int count = 0;
                    for(auto d : dir){
                        point next = curr + d;
                        if(next.first < 0 || next.first >= m || next.second < 0 || next.second >= n || grid[next.first][next.second]=='#')continue;
                        count++;
                    }
                    if(count < 3)continue;
                    nodes[curr] = nodes.size();
                    grid[curr.first][curr.second] = 'A';
                }
            }

            adj.resize(nodes.size());

            for(auto n : nodes){
                // bfs to find all connected components and distance
                bfs(n, grid, adj, nodes);
            }

            // find the longest path
            vector<bool> visited(nodes.size(), false);
            visited[0] = true;
            int ans = dfs2(0,0,adj,visited);

            return std::to_string(ans);
        }
    }
}

