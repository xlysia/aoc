#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include "utils/cvutils.h"

namespace aoc2018{
    namespace day3{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            std::cout << solvedayp1("./2018/day3/day3") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("./2018/day3/day3") << std::endl;
        }

        int fabric[1000][1000];

        void init(){
            newFrame(cv::Size(1000,1000),cv::Scalar(0,0,0));
            for(int i = 0; i < 1000;i++){
                for(int j = 0; j < 1000;j++){
                    fabric[i][j] = 0;
                }        
            }
        }

        int sumup(){
            int res = 0;
            for(int i = 0; i < 1000;i++){
                for(int j = 0; j < 1000;j++){
                    res+=fabric[i][j]>1;
                }        
            }
            return res;
        }

        struct tissue{
            int id,x,y,w,h;
        };
        std::vector<tissue> tissues;
        void parse(){
            std::string line;
            int i = 1;
            while(std::getline(std::cin,line)){
                size_t pos =line.find('@'); 
                line.erase(0,pos+1);

                int x[4];
                std::stringstream ss(line);
                for(int j = 0;j < 4;j++){
                    char c;
                    ss >> x[j] >> c;
                }
                tissues.push_back({i++,x[0],x[1],x[2],x[3]});
            }
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());

            init();
            parse();

            for(tissue t : tissues){
                for(int i = t.x;i<t.x+t.w;i++){
                    for(int j = t.y;j<t.y+t.h;j++){
                        fabric[j][i]++;
                        bool b = fabric[j][i]>1;
                        setPixel(i,j,cv::Vec3b(50,0,255*b));
                    }
                }
                show("2018 day 3",1);
            }

            return std::to_string(sumup());
        }

        std::string solvedayp2(std::string p){
            for(tissue t : tissues){
                bool b = true;
                for(int i = t.x;i<t.x+t.w;i++){
                    for(int j = t.y;j<t.y+t.h;j++){
                        b&=fabric[j][i]<2;
                    }
                }
                if(b){
                    for(int i = t.x;i<t.x+t.w;i++){
                        for(int j = t.y;j<t.y+t.h;j++){
                            setPixel(i,j,cv::Vec3b(255,255,255));
                        }
                    }
                    show("2018 day 3",0);
                    return std::to_string(t.id);
                }
            }
            return std::to_string(0);
        }
    }
}

