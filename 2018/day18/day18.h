#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace aoc2018{
    namespace day18{

        std::string solveday(std::string p, long long N);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solveday("./2018/day18/day18sample",10)=="1147");
            std::cout << solveday("./2018/day18/day18",10) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solveday("./2018/day18/day18",1000000000) << std::endl;
        }

        std::string solveday(std::string p, long long N){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            vector<string> board;

            while(getline(cin,line)){
                board.push_back(line);
            }

            int m = board.size();
            int n = board[0].size();
            long long turn = 0;

            unordered_map<string,long long> memo;
            int cycle = 0;

            string key = "";
            for(int i = 0; i < m; i++){
                key.append(board[i]);
            }
            memo[key] = 0;

            while(turn++ < N){
                vector<string> newboard = board;
                for(int i = 0; i < m; i++){
                    for(int j = 0; j < n; j++){
                        int tree = 0;
                        int lumber = 0;
                        for(int di = -1; di <= 1; di++){
                            for(int dj = -1; dj <= 1; dj++){
                                if(di == 0 && dj == 0) continue;
                                if(i+di < 0 || i+di >= m || j+dj < 0 || j+dj >= n) continue;
                                if(board[i+di][j+dj] == '|') tree++;
                                if(board[i+di][j+dj] == '#') lumber++;
                            }
                        }
                        if(board[i][j] == '.'){
                            if(tree >= 3) newboard[i][j] = '|';
                        }
                        else if(board[i][j] == '|'){
                            if(lumber >= 3) newboard[i][j] = '#';
                        }
                        else if(board[i][j] == '#'){
                            if(lumber >= 1 && tree >= 1) newboard[i][j] = '#';
                            else newboard[i][j] = '.';
                        }
                    }
                }
                board = newboard;
                key = "";
                for(int i = 0; i < m; i++){
                    key.append(board[i]);
                }
                if(cycle==0 && memo.find(key) != memo.end()){
                    cycle = turn - memo[key];
                    turn += (N - turn) / cycle * cycle;             
                }else{
                    memo[key] = turn;
                }
            }

            int tree =  0;
            int lumber = 0;
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    if(board[i][j] == '|') tree++;
                    if(board[i][j] == '#') lumber++;
                }
            }
            return std::to_string(tree*lumber);
        }
    }
}

