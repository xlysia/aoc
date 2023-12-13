#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2023{
    namespace day13{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day13/day13sample")=="405");
            std::cout << solvedayp1("./2023/day13/day13") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day13/day13sample")=="400");
            std::cout << solvedayp2("./2023/day13/day13") << std::endl;
        }
        
        vector<vector<bool>> transpose(std::vector<std::vector<bool>>& v){
            int m = v.size();
            int n = v[0].size();
            std::vector<std::vector<bool>> v2(n,std::vector<bool>(m,0));
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    v2[j][i] = v[i][j];
                }
            }
            return v2;
        }

        int process(vector<vector<bool>>& grid){
            // look for mirror

            int m = grid.size();

            for(int i = 1; i < m; i++){
                if(grid[i] == grid[i-1]){
                    int l = i-1;
                    int r = i;
                    while(l>=0 && r < m){
                        if(grid[l] == grid[r]){
                            l--,r++;
                        }
                        else break;
                    }
                    if(l==-1 || r==m){
                        return i;
                    }
                }
            }

            return 0;
        }

        int nbdiff(vector<bool>& row1, vector<bool>& row2){
            int n = row1.size();
            int ans = 0;
            for(int i = 0; i < n; i++){
                if(row1[i]!=row2[i]) ans++;
            }
            return ans;
        }
        int process2(vector<vector<bool>>& grid){
            // look for mirror

            int m = grid.size();
            
            for(int i = 1; i < m; i++){
                if(nbdiff(grid[i],grid[i-1])<2){
                    int d = 0;
                    int l = i-1;
                    int r = i;
                    while(l>=0 && r < m){
                        d += nbdiff(grid[l],grid[r]);
                        if(d < 2){
                            l--,r++;
                        }
                        else break;
                    }
                    if((l==-1 || r==m) && d == 1){
                        return i;
                    }
                }
            }

            return 0;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<std::vector<bool>> grid;

            int ans = 0;
            while(cin.good()){
                getline(cin,line);
                if(line.size()==0){
                    ans += 100*process(grid);
                    grid = transpose(grid);
                    ans += process(grid);
                    grid.clear();
                }
                else{
                    std::vector<bool> row;
                    for(int i = 0; i < (int)line.size(); i++){
                        if(line[i]=='#') row.push_back(1);
                        else row.push_back(0);
                    }
                    grid.push_back(row);
                }
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            std::vector<std::vector<bool>> grid;

            int ans = 0;
            while(cin.good()){
                getline(cin,line);
                if(line.size()==0){
                    ans += 100*process2(grid);
                    grid = transpose(grid);
                    ans += process2(grid);
                    grid.clear();
                }
                else{
                    std::vector<bool> row;
                    for(int i = 0; i < (int)line.size(); i++){
                        if(line[i]=='#') row.push_back(1);
                        else row.push_back(0);
                    }
                    grid.push_back(row);
                }
            }
            return std::to_string(ans);
        }
    }
}

