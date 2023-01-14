#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day8{
        int H = 6;
        int W = 50;
        bool screen[6][50];

        void init(){
            for(int i=0; i < H;i++){
                for(int j=0; j < W;j++){
                    screen[i][j] = false;
                }            
            }
        }

        int sum(){
            int res =0;
            for(int i=0; i < H;i++){
                for(int j=0; j < W;j++){
                    res+=screen[i][j];
                }            
            }
            return res;
        }

        void rotateRow(int r, int o){
            int row[W];
            for(int i = 0; i < W;i++){
                row[i] = screen[r][i];
            }
            for(int i = 0; i < W;i++){
                screen[r][i] = row[(i-o+10*W)%W];
            }
        }
        void rotateColumn(int c, int o){
            int column[H];
            for(int i = 0; i < H;i++){
                column[i] = screen[i][c];
            }
            for(int i = 0; i < H;i++){
                screen[i][c] = column[(i-o+10*H)%H];
            }  
        }
        void turnOn(int a, int b){
            for(int i=0; i < b;i++){
                for(int j=0; j < a;j++){
                    screen[i][j] = true;
                }            
            }
        }

        void refresh(){
            for(int i=0; i < H;i++){
                for(int j=0; j < W;j++){
                    setPixel(j,i,cv::Vec3b(screen[i][j]*255,screen[i][j]*255,screen[i][j]*255));
                }            
            }
        }

        std::string solvedayp1(std::string p);

        void run(){
            std::cout << "Part 1" << std::endl;
            H = 3;
            W = 7;
            assert (solvedayp1("./2016/day8/day8sample")=="6");
            H = 6;
            W = 50;
            std::cout << solvedayp1("./2016/day8/day8") << std::endl;

            std::cout << "Part 2" << std::endl;
            resize(10);
            showResize("2016 - day 8",0);
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            init();
            std::string line;
            newFrame(cv::Size(W,H),cv::Scalar(0,0,0));
            while(std::getline(std::cin,line)){
                size_t pos = line.find(' ');
                bool brot = line.substr(0,pos) == "rotate";
                line.erase(0,pos+1);

                if(brot){
                    pos = line.find('=');
                    bool brow = (int)pos == 5;
                    line.erase(0,pos+1);
                    pos = line.find( " by ");
                    int a = std::atoi(line.substr(0,pos).c_str());
                    line.erase(0,pos+4);
                    int b = std::atoi(line.c_str());

                    if(brow)rotateRow(a,b);
                    else rotateColumn(a,b);
                }else{
                    pos = line.find( "x");
                    int a = std::atoi(line.substr(0,pos).c_str());
                    line.erase(0,pos+1);
                    int b = std::atoi(line.c_str());
                    turnOn(a,b);
                }
                refresh();
                resize(10);
                showResize("2016 - day 8",1);
            }


            return std::to_string(sum());
        }
    }
}

