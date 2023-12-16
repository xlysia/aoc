#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day16{

        std::string solvedayp1(std::string p, int w,int n);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day16/day16sample",5,1)=="baedc");
            std::cout << solvedayp1("./2017/day16/day16",16,1) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp1("./2017/day16/day16",16,1e9) << std::endl;
        }

        void swap(char& a, char& b){
            char tmp = a;
            a = b;
            b = tmp;
        }

        std::string solvedayp1(std::string p,int w,int n){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            string programs = "abcdefghijklmnop";
            
            programs = programs.substr(0,w);


            struct move{
                char type;
                int a;
                int b;
                char c1,c2;
            };

            std::vector<move> moves;

            while (std::getline(std::cin, line)){
                std::stringstream ss(line);
                std::string move;
                while (std::getline(ss, move, ',')){
                    if (move[0]=='s'){
                        int n = std::stoi(move.substr(1));
                        moves.push_back({move[0],n,0,' ',' '});
                    } else if (move[0]=='x'){
                        moves.push_back({move[0],std::stoi(move.substr(1,move.find('/')-1)),std::stoi(move.substr(move.find('/')+1)),' ',' '});
                    } else if (move[0]=='p'){
                        moves.push_back({move[0],0,0,move[1],move[3]});
                    }
                }
            }
            int cycle = -1;
            unordered_map<string,int> seen;
            seen[programs] = 0;
            int N = 0;
            while(N<n){
                for (auto m : moves){
                    if (m.type=='s'){
                        std::rotate(programs.begin(),programs.begin()+w-m.a,programs.end());
                    } else if (m.type=='x'){
                        swap(programs[m.a],programs[m.b]);
                    } else if (m.type=='p'){
                        int a = programs.find(m.c1);
                        int b = programs.find(m.c2);
                        swap(programs[a],programs[b]);
                    }
                }
                N++;
                if (cycle <0 && seen.find(programs)!=seen.end()){
                    cycle = N-seen[programs];
                    N += (n-N)/cycle*cycle;
                }
                seen[programs] = N;
            }


            return programs;
        }
    }
}

