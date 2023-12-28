#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

namespace aoc2018{
    namespace day14{

        std::string solvedayp1(int N);
        int solvedayp2(int val);
        void run(){
            int val;
            ifstream in("./2018/day14/day14");
            in >> val;
            in.close();

            std::cout << "Part 1" << std::endl;
            assert (solvedayp1(2018)=="5941429882");
            std::cout << solvedayp1(val) << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2(51589)==9);
            assert (solvedayp2(92510)==18);
            assert (solvedayp2(59414)==2018);
            std::cout << solvedayp2(val) << std::endl;
        }

        std::string solvedayp1(int N){
            vector<int> recipes ={3,7};

            int elf1 = 0;
            int elf2 = 1;

            while((int)recipes.size() < N+10){
                int sum = recipes[elf1] + recipes[elf2];
                if(sum >= 10){
                    recipes.push_back(sum/10);
                }
                recipes.push_back(sum%10);
                elf1 = (elf1 + recipes[elf1] + 1) % (int)recipes.size();
                elf2 = (elf2 + recipes[elf2] + 1) % (int)recipes.size();
            }
            string ans = "";
            for(int i = N; i < N+10; i++){
                ans.push_back(recipes[i]+'0');
            }
            return ans;
        }

        int solvedayp2(int val){
            // get first time that val appear
            vector<int> recipes ={3,7};

            int elf1 = 0;
            int elf2 = 1;

            string valstr = to_string(val);
            while(true){
                int sum = recipes[elf1] + recipes[elf2];
                if(sum >= 10){
                    recipes.push_back(sum/10);
                    if(recipes.size() >= valstr.size()){
                        bool found = true;
                        for(int i = 0; i < (int)valstr.size(); i++){
                            if(recipes[recipes.size()-1-i] != valstr[valstr.size()-1-i]-'0'){
                                found = false;
                                break;
                            }
                        }
                        if(found){
                            return recipes.size()-valstr.size();
                        }
                    }
                }
                recipes.push_back(sum%10);
                if(recipes.size() >= valstr.size()){
                    bool found = true;
                    for(int i = 0; i < (int)valstr.size(); i++){
                        if(recipes[recipes.size()-1-i] != valstr[valstr.size()-1-i]-'0'){
                            found = false;
                            break;
                        }
                    }
                    if(found){
                        return recipes.size()-valstr.size();
                    }
                }
                elf1 = (elf1 + recipes[elf1] + 1) % (int)recipes.size();
                elf2 = (elf2 + recipes[elf2] + 1) % (int)recipes.size();

            }

            return 0;
        }
    }
}

