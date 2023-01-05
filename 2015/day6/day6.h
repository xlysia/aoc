#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include "./utils/cvutils.h"

namespace aoc2015{
    namespace day6{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2015/day6/day6sample")=="998996");
            std::cout << solvedayp1("./2015/day6/day6") << std::endl;

            std::cout << "Part 2" << std::endl;
         //   assert (solvedayp2("./2015/input/day4sample")=="-1");
            std::cout << solvedayp2("./2015/day6/day6") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            bool panel[1000][1000];
            for(int i = 0; i < 1000;i++){
                for(int j = 0; j < 1000;j++){
                    panel[i][j] = false;
                }              
            }
            newFrame(cv::Size(1000,1000),cv::Scalar(0,0,0));
            show("",1);
            while(std::getline(std::cin,line)){
                size_t pos = 0;
                bool istoggle = false;
                bool isOn = false;
                Point u(-1,-1);
                Point v(-1,-1);
                line.push_back(' ');
                while ((pos = line.find(' ')) != std::string::npos) {
                    std::string token = line.substr(0, pos).c_str();
                    line.erase(0, pos + 1);

                    if(token == "toggle"){
                        istoggle = true;
                    }else if(token == "on"){
                        isOn = true;
                    }else if(token == "off" || token == "turn" || token == "through"){

                    }else{
                        pos = token.find(',');
                        if(u.x <0){
                            u.x = std::atoi(token.substr(0,pos).c_str());
                            token.erase(0, pos + 1);
                            u.y = std::atoi(token.c_str());
                        }else{
                            v.x = std::atoi(token.substr(0,pos).c_str());
                            token.erase(0, pos + 1);
                            v.y = std::atoi(token.c_str());
                        }
                    }
                }            
                for(int i = u.x;i <= v.x ; i++){
                    for(int j = u.y;j <= v.y ; j++){
                        if(istoggle)panel[i][j] = !panel[i][j];
                        else panel[i][j] = isOn;  
                        setPixel(i,j,cv::Vec3b(panel[i][j]*255,panel[i][j]*255,panel[i][j]*255));
                    }       
                }
                show("",1);
            }
            for(int i = 0;i < 1000 ; i++){
                for(int j = 0;j < 1000 ; j++){
                    res += panel[i][j];  
                }       
            }
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            int panel[1000][1000];
            for(int i = 0; i < 1000;i++){
                for(int j = 0; j < 1000;j++){
                    panel[i][j] = 0;
                }              
            }
            newFrame(cv::Size(1000,1000),cv::Scalar(0,0,0));
            show("",1);
            while(std::getline(std::cin,line)){
                size_t pos = 0;
                bool istoggle = false;
                bool isOn = false;
                Point u(-1,-1);
                Point v(-1,-1);
                line.push_back(' ');
                while ((pos = line.find(' ')) != std::string::npos) {
                    std::string token = line.substr(0, pos).c_str();
                    line.erase(0, pos + 1);

                    if(token == "toggle"){
                        istoggle = true;
                    }else if(token == "on"){
                        isOn = true;
                    }else if(token == "off" || token == "turn" || token == "through"){

                    }else{
                        pos = token.find(',');
                        if(u.x <0){
                            u.x = std::atoi(token.substr(0,pos).c_str());
                            token.erase(0, pos + 1);
                            u.y = std::atoi(token.c_str());
                        }else{
                            v.x = std::atoi(token.substr(0,pos).c_str());
                            token.erase(0, pos + 1);
                            v.y = std::atoi(token.c_str());
                        }
                    }
                }            
                for(int i = u.x;i <= v.x ; i++){
                    for(int j = u.y;j <= v.y ; j++){
                        if(istoggle)panel[i][j] += 2;
                        else panel[i][j] += isOn?1:-1;  
                        panel[i][j] = std::max(0,panel[i][j]);
                        setPixel(i,j,cv::Vec3b(panel[i][j],panel[i][j],panel[i][j]));
                    }       
                }
                show("",1);
            }
            for(int i = 0;i < 1000 ; i++){
                for(int j = 0;j < 1000 ; j++){
                    res += panel[i][j];  
                }       
            }
            return std::to_string(res);
        }
    }
}
