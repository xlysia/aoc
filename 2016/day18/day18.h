#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2016{
    namespace day18{

        std::string solvedayp1(std::string p,int rows);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day18/day18sample",10)=="38");
            std::cout << solvedayp1("./2016/day18/day18",40) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp1("./2016/day18/day18",400000) << std::endl;
        }

        std::string solvedayp1(std::string p,int rows){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(std::cin,line);
            int ans =  0;

            for(char c : line){
                if(c == '.') ans++;
            }
            int width = line.size();
            for(int i = 1; i < rows; i++){
                std::string newline = "";
                for(int j = 0; j < width; j++){

                    char left = j == 0 ? '.' : line[j-1];
                    char right = j == width-1 ? '.' : line[j+1];

                    if(left == '^' && line[j] == '^' && right == '.'){
                        newline.push_back('^');
                    }else if(left == '.' && line[j] == '^' && right == '^'){
                        newline.push_back('^');
                    }else if(left == '^' && line[j] == '.' && right == '.'){
                        newline.push_back('^');
                    }else if(left == '.' && line[j] == '.' && right == '^'){
                        newline.push_back('^');
                    }else{
                        newline.push_back('.');
                        ans++;
                    }
                }
                line = newline;
            }

            return std::to_string(ans);
        }
    }
}

