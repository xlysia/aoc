#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

using namespace std;

namespace aoc2016{
    namespace day24{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day24/day24sample")=="14");
            std::cout << solvedayp1("./2016/day24/day24") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2016/day24/day24") << std::endl;
        }

        void bfs(pair<int,int> start,vector<string> &board,vector<vector<int>> &adj){
            int m = board.size();
            int n = board[0].size();
            int k = board[start.first][start.second] - '0';
            vector<vector<bool>> visited(m,vector<bool>(n,0));
            queue<pair<int,int>> q;
            q.push(start);
            pair<int,int> dir[4]{{0,1},{0,-1},{1,0},{-1,0}};
            visited[start.first][start.second] = 1;
            int depth = 0;
            while(!q.empty()){
                int s = q.size();
                while(s--){
                    auto [i,j] = q.front();
                    q.pop();
                    for(auto [x,y]:dir){
                        x+=i,y+=j;
                        if(x < 0 || x >= m || y < 0 || y >= n || visited[x][y] || board[x][y] == '#')continue;
                        visited[x][y] = 1;
                        q.push({x,y});
                        if(board[x][y] != '.'){
                            int l = board[x][y] - '0';
                            adj[k][l] = adj[l][k] = depth+1;
                        }
                    }
                }
                depth++;
            }
        }

        int dfs(vector<vector<int>> &adj,bool seen[],int u,int d,int k){
            if(d == k-1)return 0;
            seen[u] = 1;
            int ans = INT_MAX;
            for(int i = 0; i < k; i++){
                if(seen[i] || !adj[u][i])continue;
                ans = min(ans,adj[u][i] + dfs(adj,seen,i,d+1,k));
            }
            seen[u] = 0;
            return ans;
        }

        int dfs2(vector<vector<int>> &adj,bool seen[],int u,int d,int k){
            if(d == k-1){
                return adj[u][0];
            }
            seen[u] = 1;
            int ans = INT_MAX;
            for(int i = 0; i < k; i++){
                if(seen[i] || !adj[u][i])continue;
                ans = min(ans,adj[u][i] + dfs2(adj,seen,i,d+1,k));
            }
            seen[u] = 0;
            return ans;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> board;
            vector<vector<int>> adj;
            vector<pair<int,int>> targets(10,{0,0});
            
            int k = 0,n; 

            while(std::getline(std::cin, line)){
            //    std::cout << line << std::endl;
                board.push_back(line);
                n = line.size();

                for(int j = 0; j < n; j++){
                    if(line[j] == '#' || line[j] == '.')continue;
                    targets[line[j]-'0'] = {board.size()-1,j};
                    
                    k++;
                }

            }
            
            adj.resize(k,vector<int>(k,0));
            targets.resize(k);
            for(int i = 0;i < k ; i++){
                bfs(targets[i],board,adj);
            }

            bool seen[k];
            memset(seen,0,sizeof(seen));

            int ans = dfs(adj,seen,0,0,k);

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<string> board;
            vector<vector<int>> adj;
            vector<pair<int,int>> targets(10,{0,0});
            
            int k = 0,n; 

            while(std::getline(std::cin, line)){
         //       std::cout << line << std::endl;
                board.push_back(line);
                n = line.size();

                for(int j = 0; j < n; j++){
                    if(line[j] == '#' || line[j] == '.')continue;
                    targets[line[j]-'0'] = {board.size()-1,j};
                    
                    k++;
                }

            }
            
            adj.resize(k,vector<int>(k,0));
            targets.resize(k);
            for(int i = 0;i < k ; i++){
                bfs(targets[i],board,adj);
            }

            bool seen[k];
            memset(seen,0,sizeof(seen));

            int ans = dfs2(adj,seen,0,0,k);

            return std::to_string(ans);
        }
    }
}

