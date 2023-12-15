#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day12{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day12/day12sample")=="6");
            std::cout << solvedayp1("./2017/day12/day12") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day12/day12sample")=="2");
            std::cout << solvedayp2("./2017/day12/day12") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<vector<int>> adj(2000);

            while (std::getline(std::cin, line)) {
                std::istringstream iss(line);
                int a;
                iss >> a;
                string token;
                iss >> token;
                while (iss >> token) {
                    if (token.back() == ',')token.pop_back();
                    adj[a].push_back(stoi(token));
                }
            }

            vector<bool> visited(2000, false);
            visited[0] = true;

            queue<int> q;
            q.push(0);
            int ans =  1;
            while(!q.empty()){
                int cur = q.front();
                q.pop();
                for (int i : adj[cur]) {
                    if (!visited[i]) {
                        visited[i] = true;
                        q.push(i);
                        ans++;
                    }
                }
            }

            
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<vector<int>> adj(2000);
            vector<bool> visited(2000, true);
            while (std::getline(std::cin, line)) {
                std::istringstream iss(line);
                int a;
                iss >> a;
                string token;
                iss >> token;
                while (iss >> token) {
                    if (token.back() == ',')token.pop_back();
                    adj[a].push_back(stoi(token));
                    
                }
                visited[a] = false;
            }

            
            int ans = 0;
            for(int k = 0; k < 2000;k++){
                if(visited[k])continue;

                visited[k] = true;
                ans++;
                queue<int> q;
                q.push(k);
                while(!q.empty()){
                    int cur = q.front();
                    q.pop();
                    for (int i : adj[cur]) {
                        if (!visited[i]) {
                            visited[i] = true;
                            q.push(i);
                        }
                    }
                }
            }
            return std::to_string(ans);
        }
    }
}

