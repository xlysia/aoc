#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

using namespace std;

namespace aoc2016{
    namespace day21{

        std::string solvedayp1(string word, std::string p);
        std::string solvedayp2(string word, std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("abcde","./2016/day21/day21sample")=="decab");
            std::cout << solvedayp1("abcdefgh","./2016/day21/day21") << std::endl;

            std::cout << "Part 2" << std::endl;
            std::cout << solvedayp2("fbgdceah","./2016/day21/day21") << std::endl;
        }


        void swap(std::string& s, int x, int y){
            char tmp = s[x];
            s[x] = s[y];
            s[y] = tmp;
        }

        void rotate(std::string& s, int x){
            // use tmp string
            std::string tmp = s;
            int n = s.size();
            for (int i = 0; i < n; i++){
                s[(i+x)%n] = tmp[i];
            }
        }

        void move(std::string& s, int x, int y){
            char tmp = s[x];
            s.erase(x,1);
            s.insert(y,1,tmp);
        }

        void reverse(std::string& s, int x, int y){
            std::string tmp = s.substr(x,y-x+1);
            std::reverse(tmp.begin(),tmp.end());
            s.replace(x,y-x+1,tmp);
        }

        std::string solvedayp1(string word, std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            while(cin.good()){
                getline(cin,line);
                std::istringstream iss(line);

                /*
                swap position 4 with position 0
                reverse positions 0 through 4
                rotate left 1 step
                move position 1 to position 4
                rotate based on position of letter b
                */

                iss >> line;
                if(line == "swap"){
                    iss >> line;
                    if(line == "position"){
                        int x, y;
                        iss >> x >> line >> line >> y;
                        swap(word,x,y);
                    }else{
                        char x, y;
                        iss >> x >> line >> line >> y;
                        swap(word,word.find(x),word.find(y));
                    }

                }else if(line == "rotate"){
                    iss >> line;
                    if(line == "left"){
                        int x;
                        iss >> x;
                        x%=word.size();
                        rotate(word,word.size()-x);
                    }else if(line == "right"){
                        int x;
                        iss >> x;
                        x%=word.size();
                        rotate(word,x);
                    }else if(line == "based"){
                        iss >> line >> line >> line >> line >> line;
                        int pos = word.find(line);
                        rotate(word,(1+pos+(pos>3)));
                    }
                }else if(line == "move"){
                    int from, to;
                    iss >> line >> from >> line >> line >> to;
                    move(word,from,to);
                }else if(line == "reverse"){
                    int from, to;
                    iss >> line >> from >> line >> to;
                    reverse(word,from,to);
                }
            }

            return word;
        }

        std::string solvedayp2(string word,std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            std::vector<std::string> lines;
            while(cin.good()){
                getline(cin,line);
                lines.push_back(line);
            }

            for(int i = lines.size()-1; i >= 0; i--){
                line = lines[i];
                std::istringstream iss(line);

                iss >> line;
                if(line == "swap"){
                    iss >> line;
                    if(line == "position"){
                        int x, y;
                        iss >> x >> line >> line >> y;
                        swap(word,x,y);
                    }else{
                        char x, y;
                        iss >> x >> line >> line >> y;
                        swap(word,word.find(x),word.find(y));
                    }

                }else if(line == "rotate"){
                    iss >> line;
                    if(line == "left"){
                        int x;
                        iss >> x;
                        x%=word.size();
                        rotate(word,x);
                    }else if(line == "right"){
                        int x;
                        iss >> x;
                        x%=word.size();
                        rotate(word,word.size()-x);
                    }else if(line == "based"){
                        iss >> line >> line >> line >> line >> line;
                        int pos = word.find(line);
                        // 0 1 2 3 4 5 6 7
                        // 1 3 5 7 2 4 6 0
                        int shift[8] = {7,7,2,6,1,5,0,4};
                        rotate(word,shift[pos]);
                    }
                }else if(line == "move"){
                    int from, to;
                    iss >> line >> from >> line >> line >> to;
                    move(word,to,from);
                }else if(line == "reverse"){
                    int from, to;
                    iss >> line >> from >> line >> to;
                    reverse(word,from,to);
                }
            }

            return word;
        }
    }
}

