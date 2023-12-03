#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

using namespace std;

namespace aoc2023{
    namespace day3{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day3/day3sample")=="4361");
            std::cout << solvedayp1("./2023/day3/day3") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day3/day3sample")=="467835");
            std::cout << solvedayp2("./2023/day3/day3") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line1,line2,line3;
            int ans = 0;
            getline(std::cin,line2);
            getline(std::cin,line3);
            while(int n = line2.size()){
                int curr = 0;
                int L = -1,R=-1;
                line2.push_back('.');
                for(int i = 0; i <= n; i++){
                    if(isdigit(line2[i])){
                        if(curr<1)L = i;
                        curr = 10*curr+ (line2[i]-'0');
                    }
                    else{
                        R=i;
                        if(curr>0){
                            bool found = false;
                            for(int j = std::max(0,L-1); j <= std::min(n-1,R); j++){
                                if(line1.size()>0 && !isdigit(line1[j]) && line1[j] != '.'){
                                    found = true;
                                    break;
                                }else if(line3.size()>0 && !isdigit(line3[j]) && line3[j] != '.'){
                                    found = true;
                                    break;
                                }else if(!isdigit(line2[j]) && line2[j] != '.' ){
                                    found = true;
                                    break;
                                }
                            }
                            if(found){
                                ans += curr;
                            }
                        }
                        curr = 0;
                    }
                }

                
                // end
                line1 = line2;
                line2 = line3;
                line3 = "";
                getline(std::cin,line3);         
            }

            return std::to_string(ans);
        }

        int check(std::string &line, int k, int &tmp){
            if(line.empty())return 0;
            int ans = 0;

            int curr = 0;
            int L = -1;
            for(int i = max(0,k-10); i <= min((int)line.size()-1,k+10); i++){
                if(!isdigit(line[i])){
                    if(curr>0){
                        if(k>=L-1 && k <= i)
                        {
                            ans ++;
                            tmp*=curr;
                        }
                    }
                    curr = 0;
                }
                else{
                    if(curr<1)L = i;
                    curr = 10*curr+ (line[i]-'0');
                }
            }
            
            return ans;
        }
        
        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line1,line2,line3;
            int ans = 0;
            getline(std::cin,line2);
            getline(std::cin,line3);
            line2.push_back('.');
            line3.push_back('.');
            while(int n = line2.size()){
                
                for(int i = 0; i <= n; i++){
                    
                    if(line2[i] == '*'){
                        //gear?
                        int count = 0;
                        int tmp = 1;
                        count += check(line1,i,tmp);
                        count += check(line2,i,tmp);
                        count += check(line3,i,tmp);
                        if(count == 2)ans+=tmp;
                    }
                }

                
                // end
                line1 = line2;
                line2 = line3;
                line3 = "";
                if(getline(std::cin,line3))line3.push_back('.');
                     
            }

            return std::to_string(ans);
        }
    }
}

