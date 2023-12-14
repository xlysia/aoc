#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace aoc2023{
    namespace day14{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day14/day14sample")=="136");
            std::cout << solvedayp1("./2023/day14/day14") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day14/day14sample")=="64");
            std::cout << solvedayp2("./2023/day14/day14") << std::endl;
        }

        int sumRange(int a , int b){
            return (b-a+1)*(a+b)/2;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            vector<string> grid;
            while(cin.good()){
                getline(cin,line);
                grid.push_back(line);
            }

            //tilt north

            int m = grid.size();
            int n = grid.size();
            int ans = 0;
            // 'O' rolls up 
            for(int j = 0; j < n; j++){
                // starts from bottom up there can be more than one 'O' in a column no collision they stop at the first '#'
                int nbO = 0;
                for(int i = m-1; i >= -1; i--){
                    if(i < 0 || grid[i][j] == '#'){
                        for(int k = i+nbO; k > i; k--){
                            grid[k][j] = 'O';         
                        }
                        if(nbO){
                            // compute score for each 'O' at row i it scores m-i
                            ans += sumRange(m-i-nbO,m-i-1);
                        } 
                        nbO = 0;
                    }else if(grid[i][j] == 'O'){
                        nbO++;
                        grid[i][j] = '.';
                    }
                }
            }

            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            
            vector<string> grid;
            while(cin.good()){
                getline(cin,line);
                grid.push_back(line);
            }
            
            unordered_map<string,int> seen;
            int N = 0;
            int ans = 0;
            int CYCLE_NB = 1e9;
            int period = 0;
            while(N++<CYCLE_NB){
                //tilt north

                int m = grid.size();
                int n = grid.size();
                ans = 0;
                // 'O' rolls up 
                for(int j = 0; j < n; j++){
                    // starts from bottom up there can be more than one 'O' in a column no collision they stop at the first '#'
                    int nbO = 0;
                    for(int i = m-1; i >= -1; i--){
                        if(i < 0 || grid[i][j] == '#'){
                            for(int k = i+nbO; k > i; k--){
                                grid[k][j] = 'O';         
                            }

                            nbO = 0;
                        }else if(grid[i][j] == 'O'){
                            nbO++;
                            grid[i][j] = '.';
                        }
                    }
                }

                // tilt west 'O' rolls left

                for(int i = 0; i < m; i++){
                    // starts from right to left there can be more than one 'O' in a row no collision they stop at the first '#'
                    int nbO = 0;
                    for(int j = n-1; j >= -1; j--){
                        if(j < 0  || grid[i][j] == '#'){
                            for(int k = j+nbO; k > j; k--){
                                grid[i][k] = 'O';         
                            }
                            nbO = 0;
                        }else if(grid[i][j] == 'O'){
                            nbO++;
                            grid[i][j] = '.';
                        }
                    }
                }

                // tilt south 'O' rolls down

                for(int j = 0; j < n; j++){
                    // starts from top to bottom there can be more than one 'O' in a column no collision they stop at the first '#'
                    int nbO = 0;
                    for(int i = 0; i <= m; i++){
                        if(i >= m || grid[i][j] == '#'){
                            for(int k = i-nbO; k < i; k++){
                                grid[k][j] = 'O';         
                            }
                            if(nbO){
                                // compute score for each 'O' at row i it scores m-i
                                ans += sumRange(m-i+1,m-i+nbO);
                            } 
                            nbO = 0;
                        }else if(grid[i][j] == 'O'){
                            nbO++;
                            grid[i][j] = '.';
                        }
                    }
                }
              //  cout << "north load " << ans << endl;

                string key = accumulate(grid.begin(),grid.end(),string(""));
                if(!period && seen.find(key) != seen.end()){
                    period = N - seen[key];
                    N += (CYCLE_NB-N)/period * period;
                }
                seen[key] = N;
                // tilt east 'O' rolls right

                for(int i = 0; i < m; i++){
                    // starts from left to right there can be more than one 'O' in a row no collision they stop at the first '#'
                    int nbO = 0;
                    for(int j = 0; j <= n; j++){
                        if(j >= n || grid[i][j] == '#'){
                            for(int k = j-nbO; k < j; k++){
                                grid[i][k] = 'O';         

                            }
                            nbO = 0;
                        }else if(grid[i][j] == 'O'){
                            nbO++;
                            grid[i][j] = '.';
                        }
                    }
                }
            }
            return to_string(ans);
        }
    }
}

