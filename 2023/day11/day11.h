#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2023{
    namespace day11{

        std::string solvedayp1(std::string p,int factor);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day11/day11sample",2)=="374");
            std::cout << solvedayp1("./2023/day11/day11",2) << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp1("./2023/day11/day11sample",10)=="1030");
            assert (solvedayp1("./2023/day11/day11sample",100)=="8410");
            std::cout << solvedayp1("./2023/day11/day11",1000000) << std::endl;
        }

        std::string solvedayp1(std::string p,int factor){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            typedef long long ll;
            vector<ll> rows(1000,0);
            vector<ll> cols(1000,0);

            vector<pair<int,int>> galaxies;
            int m = 0;
            int n = 0;
            while(cin.good()){
                std::getline(std::cin,line);
                n = line.size();
                for(int i = 0; i < n; i++){
                    if(line[i] == '#'){
                        rows[m]++;
                        cols[i]++;
                        galaxies.push_back(make_pair(m,i));
                    }
                }
                m++;
            }

            rows.resize(m);
            cols.resize(n);

            vector<ll> distrows(m,0);
            vector<ll> distcols(n,0);

            for(int i = 1; i < m;i++){
                distrows[i] = distrows[i-1] + (rows[i-1]>0?1:factor);
            }

            for(int i = 1; i < n;i++){
                distcols[i] = distcols[i-1] + (cols[i-1]>0?1:factor);
            }

            ll ans =  0;

            int K = galaxies.size();
            for(int i = 0; i <K; i++){
                int x1 = galaxies[i].first;
                int y1 = galaxies[i].second;

                for(int j = i+1; j < K; j++){
                    int x2 = galaxies[j].first;
                    int y2 = galaxies[j].second;

                    ans += abs(distrows[x1]-distrows[x2]) + abs(distcols[y1]-distcols[y2]);
                }
            }

            return std::to_string(ans);
        }
    }
}

