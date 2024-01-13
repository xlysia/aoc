#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

namespace aoc2018{
    namespace day25{
        
        struct unionfind{
            int parent;
            int rank;
        };

        int find(int i,vector<unionfind>& u){
            if(u[i].parent!=i){
                u[i].parent = find(u[i].parent,u);
            }
            return u[i].parent;
        }

        void union_(int x, int y,vector<unionfind>&u){
            int xroot = find(x,u);
            int yroot = find(y,u);
            if(u[xroot].rank < u[yroot].rank){
                u[xroot].parent = yroot;
            }else if(u[xroot].rank > u[yroot].rank){
                u[yroot].parent = xroot;
            }else{
                u[yroot].parent = xroot;
                u[xroot].rank++;
            }
        }

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day25/day25sample")=="8");
            std::cout << solvedayp1("./2018/day25/day25") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2018/day25/day25sample")=="NOTDEF");
            std::cout << solvedayp2("./2018/day25/day25") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            vector<unionfind> groups;
            vector<vector<int>> points;

            while(getline(cin, line)){
                int x,y,z,w;
                sscanf(line.c_str(),"%d,%d,%d,%d",&x,&y,&z,&w);
                vector<int> point = {x,y,z,w};
                points.push_back(point);
                unionfind u;
                u.parent = groups.size();
                u.rank = 0;
                groups.push_back(u);
            }

            for(size_t i=0;i<points.size();i++){
                for(size_t j=i+1;j<points.size();j++){
                    int dist = 0;
                    for(int k=0;k<4;k++){
                        dist += abs(points[i][k]-points[j][k]);
                    }
                    if(dist<=3){
                        union_(i,j,groups);
                    }
                }
            }

            int ans =  0;
            for(size_t i=0;i<groups.size();i++){
                if(groups[i].parent==(int)i){
                    ans++;
                }
            }
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	        std::string line;
            int ans = 0;
            return std::to_string(ans);
        }
    }
}

