#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day24{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day24/day24sample")=="31");
            std::cout << solvedayp1("./2017/day24/day24") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day24/day24sample")=="19");
            std::cout << solvedayp2("./2017/day24/day24") << std::endl;
        }


        int dfs(int i, std::vector<std::pair<int,int>> &tiles, vector<bool> &used){
            int ans = 0;
            int n = tiles.size();
            for(int j = 0; j < n; j++){
                if(used[j])continue;
                if(tiles[j].first == i){
                    used[j] = true;
                    ans = std::max(ans,tiles[j].first + tiles[j].second + dfs(tiles[j].second,tiles,used));
                    used[j] = false;
                }
                if(tiles[j].second == i){
                    used[j] = true;
                    ans = std::max(ans,tiles[j].first + tiles[j].second + dfs(tiles[j].first,tiles,used));
                    used[j] = false;
                }
            }
            return ans;
        }


        pair<int,int> dfs2(int i,int depth,std::vector<std::pair<int,int>> &tiles, vector<bool> &used){
            int ans = 0;
            int dans = depth;
            int n = tiles.size();
            for(int j = 0; j < n; j++){
                if(used[j])continue;
                if(tiles[j].first == i){
                    used[j] = true;
                    auto [val,d] = dfs2(tiles[j].second,depth+1,tiles,used);
                    if(d > dans){
                        dans = d;
                        ans = tiles[j].first + tiles[j].second + val;
                    }else if(d == dans){
                        ans = std::max(ans,tiles[j].first + tiles[j].second + val);
                    }
                    used[j] = false;
                }
                if(tiles[j].second == i){
                    used[j] = true;
                    auto [val,d] = dfs2(tiles[j].first,depth+1,tiles,used);
                    if(d > dans){
                        dans = d;
                        ans = tiles[j].first + tiles[j].second + val;
                    }else if(d == dans){
                        ans = std::max(ans,tiles[j].first + tiles[j].second + val);
                    }
                    used[j] = false;
                }
            }
            return {ans,dans};
        }
    
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());

            using tile = std::pair<int,int>;
            std::vector<tile> tiles;
            vector<bool> used;

            std::string line;
            while(std::getline(std::cin,line)){
                std::stringstream ss(line);
                getline(ss,line,'/');
                int a = std::stoi(line);
                int b;
                ss >> b;
                tiles.push_back({a,b});
                used.push_back(false);
            }



            int ans =  dfs(0,tiles,used);
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
           std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());

            using tile = std::pair<int,int>;
            std::vector<tile> tiles;
            vector<bool> used;

            std::string line;
            while(std::getline(std::cin,line)){
                std::stringstream ss(line);
                getline(ss,line,'/');
                int a = std::stoi(line);
                int b;
                ss >> b;
                tiles.push_back({a,b});
                used.push_back(false);
            }



            auto ans = dfs2(0,0,tiles,used);
            return std::to_string(ans.first);
        }
    }
}

