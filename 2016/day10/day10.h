#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day10{
        
        struct bot{
            int id;
            int microships[2];
            int holds;

            int lowto;
            bool lowtoOutput;
            bool hightoOutput;            
            int highto;

            bool grab(int a){
                if(holds>1)return false;
                microships[holds] = a;
                holds++;
                return true;
            }
        };

        struct output{
            int microship;
        };

        struct Board{
            std::vector<output> outputs;
            std::vector<bot> bots;
        };  

        Board board;

        std::string solveday(std::string p,int a,int b);

        void run(){
            assert (solveday("./2016/day10/day10sample",2,5)=="30");
            std::cout << solveday("./2016/day10/day10",61,17) << std::endl;
        }

        void parse(){
            std::string line;
            board.bots.clear();
            board.outputs.clear();

            while(std::getline(std::cin,line)){
                size_t pos;
                std::vector<std::string> x = {};
                while((pos=line.find(' ')) != std::string::npos){
                    std::string token = line.substr(0,pos);
                    x.push_back(token);
                    line.erase(0,pos+1);
                }
                x.push_back(line);

                if(x[0] == "value"){
                    int a = std::atoi(x[1].c_str());
                    int b = std::atoi(x[5].c_str());
                    while((int)board.bots.size()<=b){
                        board.bots.push_back(bot());
                    }
                    board.bots[b].grab(a);
                }else{
                    int a = std::atoi(x[1].c_str());
                    int b = std::atoi(x[6].c_str());
                    int c = std::atoi(x[11].c_str());
                    while((int)board.bots.size()<=a){
                        board.bots.push_back(bot());
                    }
                    board.bots[a].lowto = b;
                    board.bots[a].highto = c;
                    board.bots[a].lowtoOutput = x[5]!="bot";
                    board.bots[a].hightoOutput = x[10]!="bot";
                    if(board.bots[a].lowtoOutput){
                        while((int)board.outputs.size()<=b){
                            board.outputs.push_back(output());
                        }                       
                    }else{
                        while((int)board.bots.size()<=b){
                            board.bots.push_back(bot());
                        }                         
                    }
                    if(board.bots[a].hightoOutput){
                        while((int)board.outputs.size()<=c){
                            board.outputs.push_back(output());
                        }                       
                    }else{
                        while((int)board.bots.size()<=c){
                            board.bots.push_back(bot());
                        }                         
                    }
                }
            }
            for(int i = 0 ; i <(int) board.bots.size();i++){
                board.bots[i].id = i;
            }
        }

        int explore(int a,int b){
            while(1){
                bool found = false;
                for(auto& bot : board.bots){
                    if(bot.holds>1){
                        if(a == bot.microships[0] && b == bot.microships[1])std::cout << "P1: "<< bot.id << std::endl;
                        else if(b == bot.microships[0] && a == bot.microships[1])std::cout << "P1: "<< bot.id << std::endl;
                        if((bot.lowtoOutput || (board.bots[bot.lowto].holds<2))
                            &&
                           (bot.hightoOutput || (board.bots[bot.highto].holds<2))){
                            found = true;
                            int low = bot.microships[0]> bot.microships[1] ? bot.microships[1]:bot.microships[0];
                            int high = bot.microships[0]> bot.microships[1] ? bot.microships[0]:bot.microships[1];
                            bot.microships[0] = -1;
                            bot.microships[1] = -1;
                            bot.holds = 0;
                            if(bot.hightoOutput)board.outputs[bot.highto].microship = high;
                            else board.bots[bot.highto].grab(high);
                            if(bot.lowtoOutput)board.outputs[bot.lowto].microship = low;
                            else board.bots[bot.lowto].grab(low);
                        }
                    }
                }
                if(!found)break;
            }
            return board.outputs[0].microship*board.outputs[1].microship*board.outputs[2].microship;
        }

        std::string solveday(std::string p,int a, int b){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse();
            int res = explore(a,b);
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
 	    std::string line;
            int res = 0;
            return std::to_string(res);
        }
    }
}

