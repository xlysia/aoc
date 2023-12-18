#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>    

using namespace std;

namespace aoc2017{
    namespace day21{

        std::string solvedayp1(std::string p, int N);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day21/day21sample",2)=="12");
            std::cout << solvedayp1("./2017/day21/day21",5) << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp1("./2017/day21/day21",18) << std::endl;
        }


        void draw(string pattern){
            return;
            int W = sqrt(pattern.size());
            for(int i = 0; i < W; i++){
                for(int j = 0; j < W; j++){
                    cout << pattern[i*W + j];
                }
                cout << endl;
            }
        }

        void rotate90(string& pattern){
            // pattern is either 2x2 or 3x3
            int W = sqrt(pattern.size());
            string tmp = pattern;
            // rotate pattern is a n*n grid on an array
            
            // rotate 90° clockwise
            for(int i = 0; i < W; i++){
                for(int j = 0; j < W; j++){
                    tmp[i*W + j] = pattern[(W - j - 1)*W + i];
                }
            }
            pattern = tmp;
        }

        void expand(string& pattern, map<string,string>& rules ){
            
            // pattern is either 2x2 or 3x3
            int W = sqrt(pattern.size());
         //   draw(pattern);
            // chek if pattrn in rules
            if (rules.find(pattern) != rules.end()){
                pattern = rules[pattern];
                return;
            }
            // flip pattern
            string pattern2 = pattern;
            for(int i = 0; i < W; i++){
                for(int j = 0; j < W; j++){
                    pattern2[i*W + j] = pattern[i*W + W - j - 1];
                }
            }
            //cout << "flipped" << endl;
           // draw(pattern2);
            if (rules.find(pattern2) != rules.end()){
                pattern = rules[pattern2];
                return;
            }
        
            // rotate pattern 90 degrees clockwise
            for(int k = 0; k < 3;k++){

                rotate90(pattern);
                rotate90(pattern2);

                if (rules.find(pattern) != rules.end()){
                    pattern = rules[pattern];
                    return;
                }
                if (rules.find(pattern2) != rules.end()){
                    pattern = rules[pattern2];
                    return;
                }

            }

            cout << "ERROR: pattern not found" << endl;

        }

        std::string solvedayp1(std::string p,int N){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            // read input to get enhancement rules
            std::map<std::string, std::string> rules;
            while (std::getline(std::cin, line)){
                std::istringstream iss(line);
                std::string from, to;
                iss >> from >> to >> to;
                // rmv slashes
                from.erase(std::remove(from.begin(), from.end(), '/'), from.end());
                to.erase(std::remove(to.begin(), to.end(), '/'), to.end());

                rules[from] = to;
            }

            // initial pattern
            std::string pattern = ".#...####";
            //string test = ".#..";
            draw(pattern);
            while(N--){
                
                // split pattern into 2x2 or 3x3 squares
                std::vector<std::string> squares;
                int W = sqrt(pattern.size());
                if (W % 2 == 0){
                    // split into 2x2 squares
                    int n = W/2;
                    for (int i = 0; i < n; i++){
                        for (int j = 0; j < n; j++){
                            std::string square = string(4,'.');
                            for(int k = 0; k < 2; k++){
                            // each line of the square
                                for(int l = 0; l < 2; l++){
                                    square[k*2 + l] = pattern[W*(2*i+k) + j*2 + l];
                                }
                            }
                            squares.push_back(square);
                        }
                    }
                } else {
                    // split into 3x3 squares
                    int n = W/3 ;
                    for (int i = 0; i < n; i++){
                        for (int j = 0; j < n; j++){
                            std::string square = string(9,'.');
                            for(int k = 0; k < 3; k++){
                            // each line of the square
                                for(int l = 0; l < 3; l++){
                                    square[k*3 + l] = pattern[W*(3*i+k) + j*3 + l];
                                }
                            }
                            squares.push_back(square);
                        }
                    }
                }
                // apply enhancement rules
                // some squates needs to be rotated &| flipped firt to match the rules
                int n = squares.size();
                for (int i = 0; i < n; i++){

                    expand(squares[i],rules);

                }
                // join squares back together
                int s = sqrt(squares.size());
                int w = sqrt(squares[0].size()); 
                std::string newpattern = string(n*w*w,'.');

                for(int i = 0; i < s;i++){
                    for(int j = 0; j < s; j++){
                        std::string square = squares[i*s + j];
                        for(int k = 0; k < w; k++){
                            // each line of the square
                            for(int l = 0; l < w; l++){
                                newpattern[s*w*(w*i+k) + j*w + l ] = square[k*w + l];
                            }
                        }
                    }   
                }


                pattern = newpattern;
                draw(pattern);
            }

            // count number of on pixels
            int ans =  0;

            for(int i = 0; i < (int)pattern.size(); i++){
                if (pattern[i] == '#'){
                    ans++;
                }
            }


            return std::to_string(ans);
        }
    }
}

