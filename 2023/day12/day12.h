#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>

using namespace std;

namespace aoc2023{
    namespace day12{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day12/day12sample")=="21");
            std::cout << solvedayp1("./2023/day12/day12") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day12/day12sample")=="525152");
            std::cout << solvedayp2("./2023/day12/day12") << std::endl;
        }

        long long dfs(string board, vector<int> values, int ib, int iv,vector<vector<long long>>& memo){
            int n = board.size();
            int k = values.size();
            if(ib >= n){
                if(iv != k)return 0;
                return 1;
            }
            if(iv == k){
                for(int i = ib; i < n; i++){
                    if(board[i] == '#')return 0;
                }
                return 1;
            }

            if(memo[ib][iv] != -1)return memo[ib][iv];

            if(board[ib] == '#'){
                for(int i = ib; i < ib+values[iv]; i++){
                   if(i >= n || board[i] == '.')return memo[ib][iv] = 0;
                }
                if(ib+values[iv] > n || (ib+values[iv] < n  && board[ib+values[iv]] == '#'))return memo[ib][iv] = 0;
                memo[ib][iv] = dfs(board, values, ib+values[iv]+1, iv+1, memo);
            }else if(board[ib] == '.'){
                memo[ib][iv] = dfs(board, values, ib+1, iv, memo);
            }else if(board[ib]=='?'){
                bool b = true;
                for(int i = ib; i < ib+values[iv]; i++){
                   if(i >= n || board[i] == '.'){b = false;break;}
                }
                b &= (ib+values[iv] < n && board[ib+values[iv]] != '#') || ib+values[iv] == n;

                memo[ib][iv] = dfs(board, values, ib+1, iv, memo) + (b?dfs(board, values, ib+values[iv]+1, iv+1, memo):0);
            }

            return memo[ib][iv];
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            long long ans = 0;
            while(std::getline(std::cin, line)){
                std::istringstream iss(line);
                std::string board;
                iss >> board;
                vector<int> values;
                string val;
                while(getline(iss, val, ',')){
                    values.push_back(stoi(val));
                }
                int k = values.size();
                int n = board.size();
                vector<vector<long long>> memo = vector<vector<long long>>(n, vector<long long>(k, -1));

                ans += dfs(board, values, 0,0,memo);

            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;


            long long ans = 0;

            while(std::getline(std::cin, line)){
                std::istringstream iss(line);
                std::string board;
                iss >> line;

                for(int i = 0; i < 4; i ++){
                    board.append(line+"?");
                }
                board.append(line);

                vector<int> values;
                string val;
                while(getline(iss, val, ',')){
                    values.push_back(stoi(val));
                }
                int k = values.size();
                for(int i = 0; i < 4; i ++){
                    for(int j = 0; j < k; j++){
                        values.push_back(values[j]);
                    }
                }

                k = values.size();
                int n = board.size();
                vector<vector<long long>> memo = vector<vector<long long>>(n, vector<long long>(k, -1));

                ans += dfs(board, values, 0,0,memo);

            }

            return std::to_string(ans);
        }
    }
}

