#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day14{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day14/day14sample")=="8108");
            std::cout << solvedayp1("./2017/day14/day14") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day14/day14sample")=="1242");
            std::cout << solvedayp2("./2017/day14/day14") << std::endl;
        }

        void knot(vector<int>& values, int K, int idx){
            int N = values.size();
            int end = idx+K;
            if (end > N){
                vector<int> tmp = vector<int>(values.begin()+idx,values.end());
                tmp.insert(tmp.end(),values.begin(),values.begin()+end-N);
                std::reverse(tmp.begin(),tmp.end());
                for (int i=0;i<K;i++){
                    values[(idx+i)%N] = tmp[i];
                }
            } else {
                std::reverse(values.begin()+idx,values.begin()+end);
            }
        }

        string getHash(string word){
         // range from 1 to w
            vector<int> values = vector<int>(256);
            std::iota(values.begin(), values.end(), 0);
            int idx = 0;
            int skip = 0;
    
            vector<int> lengths;

            for(char c : word){
                lengths.push_back(c);
            }
            vector<int> vector2 = {17, 31, 73, 47, 23};
            lengths.insert( lengths.end(), vector2.begin(), vector2.end() );
            for(int i = 0; i < 64; ++i){
                for(int K : lengths){
                    knot(values,K,idx);
                    idx = (idx+K+skip++)%256;
                }
            }


            string ans = "";
            for(int i = 0; i < 16; ++i){
                int x = 0;
                for(int j = 0; j < 16; ++j){
                    x ^= values[i*16+j];
                }
                if(x < 16) ans += "0";
                stringstream ss;
                ss << std::hex << x;
                ans += ss.str();
            }
            return ans;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            string line;
            getline(cin,line);
            int ans = 0;

            for(int i = 0; i < 128; ++i){
                string word = line + "-" + std::to_string(i);
                string hash = getHash(word);
                for(char c : hash){
                    // count bits in hex char
                    int x = 0;
                    if(c >= '0' && c <= '9'){
                        x = c - '0';
                    } else {
                        x = c - 'a' + 10;
                    }
                    for(int j = 0; j < 4; ++j){
                        if(x & (1 << j)) ans++;
                    }
                }
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            string line;
            getline(cin,line);
            int ans = 0;

            vector<vector<bool>> grid(128,vector<bool>(128,false));

            for(int i = 0; i < 128; ++i){
                string word = line + "-" + std::to_string(i);
                string hash = getHash(word);
                int k = 0;
                for(char c : hash){
                    // count bits in hex char
                    int x = 0;
                    if(c >= '0' && c <= '9'){
                        x = c - '0';
                    } else {
                        x = c - 'a' + 10;
                    }
                    for(int j = 0; j < 4; ++j){
                        if(x & (1 << j)) grid[i][k*4+3-j] = true;
                    }
                    k++;
                }
            }

            vector<vector<int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};

            for(int i = 0; i < 128; ++i){
                for(int j = 0; j < 128; ++j){
                    if(!grid[i][j])continue;
                    ans++;

                    queue<pair<int,int>> q;
                    q.push({i,j});
                    grid[i][j] = false;
                    while(!q.empty()){
                        auto p = q.front();
                        q.pop();
                        for(auto d : dirs){
                            int x = p.first + d[0];
                            int y = p.second + d[1];
                            if(x < 0 || x >= 128 || y < 0 || y >= 128) continue;
                            if(!grid[x][y]) continue;
                            grid[x][y] = false;
                            q.push({x,y});
                        }
                    }
                }
            }

            return to_string(ans);
        }
    }
}

