#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day2{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);

        void initpanels();

        void run(){
            initpanels();
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day2/day2sample")=="1985");
            std::cout << solvedayp1("./2016/day2/day2") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2016/day2/day2sample")=="5DB3");
            std::cout << solvedayp2("./2016/day2/day2") << std::endl;
        }
        int** panel;
        int** panel2;
        
        void initpanels(){
            int p[5][5] = {{false,false,false,false,false},
                {false,'1','2','3',false},{false,'4','5','6',false},{false,'7','8','9',false},
                {false,false,false,false,false}};
            panel = new int *[5];
            for(int i = 0;i<5;i++){
                panel[i] = new int[5];
                for(int j = 0;j<5;j++){
                    panel[i][j] = p[i][j];
                }
            } 

            int p2[7][7] = {{false,false,false,false,false,false,false},
                {false,false,false,'1',false,false,false},
                {false,false,'2','3','4',false,false},
                {false,'5','6','7','8','9',false},
                {false,false,'A','B','C',false,false},
                {false,false,false,'D',false,false,false},
                {false,false,false,false,false,false,false}};
            panel2 = new int *[7];
            for(int i = 0;i<7;i++){
                panel2[i] = new int[7];
                for(int j = 0;j<7;j++){
                    panel2[i][j] = p2[i][j];
                }
            } 
        }
        


        std::string explore(int** board,Point p){
            std::string res = "";
            std::string line;

            while(std::getline(std::cin,line)){
                for(char c : line){
                    switch(c){
                        case 'U':
                            if(board[p.y-1][p.x]>0)p.y--;
                            break;
                        case 'D':
                            if(board[p.y+1][p.x]>0)p.y++;
                            break;
                        case 'L':
                            if(board[p.y][p.x-1]>0)p.x--;
                            break;
                        case 'R':
                            if(board[p.y][p.x+1]>0)p.x++;
                            break;
                        default:
                            break;
                    }
                }
                res.push_back(char(board[p.y][p.x]));
            }
            return res;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            return explore(panel,Point(2,2));
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            return explore(panel2,Point(1,3));
        }
    }
}

