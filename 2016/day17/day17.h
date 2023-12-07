#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <utils/md5.h>

using state = tuple<string,int,int> ;

namespace aoc2016{
    namespace day17{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("ihgpwlah")=="DDRRRD");
            assert (solvedayp1("kglvqrro")=="DDUDRLRRUDRD");
            assert (solvedayp1("ulqzkmiv")=="DRURDRUDDLLDLUURRDULRLDUUDDDRR");
            std::ifstream in("./2016/day17/day17");
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(std::cin, line);
            std::cout << solvedayp1(line) << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("ihgpwlah")=="370");
            assert (solvedayp2("kglvqrro")=="492");
            assert (solvedayp2("ulqzkmiv")=="830");
            std::cout << solvedayp2(line) << std::endl;
        }

        const vector<pair<int,int>> adj = {{-1,0},{1,0},{0,-1},{0,1}};

        std::string solvedayp1(std::string key){

            string ans = "";

            queue<state> queue;
            queue.push({"",1,1});

            while(!queue.empty()){
                auto [path,i,j] = queue.front();
                queue.pop();

                string hash = md5(key+path);
                for(int k = 0; k < 4 ;k++){
                    if(hash[k]<'b')continue;
                    auto [x,y] = adj[k];
                    x+=i,y+=j;
                    if(x<1 || x>4 || y<1 || y>4)continue;
                    if(x==4 && y==4){
                        return path+"UDLR"[k];
                    }
                    queue.push({path+"UDLR"[k],x,y});
                
                }
            }

            return "not found";
        }

        std::string solvedayp2(std::string key){

            int ans = 0;

            queue<state> queue;
            queue.push({"",1,1});

            while(!queue.empty()){
                auto [path,i,j] = queue.front();
                queue.pop();

                string hash = md5(key+path);
                for(int k = 0; k < 4 ;k++){
                    if(hash[k]<'b')continue;
                    auto [x,y] = adj[k];
                    x+=i,y+=j;
                    if(x<1 || x>4 || y<1 || y>4)continue;
                    if(x==4 && y==4){
                        ans = max(ans, (int)path.size()+1);
                        continue;
                    }
                    queue.push({path+"UDLR"[k],x,y});
                
                }
            }

            return to_string(ans);
        }
    }
}

