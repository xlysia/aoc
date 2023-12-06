#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <utils/md5.h>

namespace aoc2016{
    namespace day14{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2016/day14/day14sample")=="22728");
            std::cout << solvedayp1("./2016/day14/day14") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2016/day14/day14sample")=="22551");
            std::cout << solvedayp2("./2016/day14/day14") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(cin, line);
            map<char,queue<int>> candidates;
            int ans = 0;
            int i = -1;
            string token;
            int stop = 1000;
            vector<int> keys;
            while(1){
                i++;
                if(ans >= 64 && --stop)break;
                token = md5(line+to_string(i));
                token.push_back('_');
                char c = '_';
                bool iscand = false;
                int count = 0;
                for(int j = 0; j < (int)token.size(); j++){
                    if(c == token[j])count++;
                    else{
                        if(count >=5){
                            while(!candidates[c].empty()){
                                int k = candidates[c].front();
                                candidates[c].pop();
                                if(i-k <= 1000){
                                    ans++;
                                    keys.push_back(k);
                                }
                            }
                        }
                        if(count >= 3){
                            if(!iscand ){
                                candidates[c].push(i);
                                iscand = true;
                            }
                            
                        }
                        c = token[j];
                        
                        count = 1;
                    }
                }
            }
            sort(keys.begin(), keys.end());
            return std::to_string(keys[63]);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            getline(cin, line);
            map<char,queue<int>> candidates;
            int ans = 0;
            int i = -1;
            string token;
            int stop = 1000;
            vector<int> keys;
            while(1){
                i++;
                if(ans >= 64 && --stop)break;
                token = md5(line+to_string(i));
                for(int j = 0; j < 2016; j++)token = md5(token);
                token.push_back('_');
                char c = '_';
                bool iscand = false;
                int count = 0;
                for(int j = 0; j < (int)token.size(); j++){
                    if(c == token[j])count++;
                    else{
                        if(count >=5){
                            while(!candidates[c].empty()){
                                int k = candidates[c].front();
                                candidates[c].pop();
                                if(i-k <= 1000){
                                    ans++;
                                    cout << ans << " "<< k << endl;
                                    keys.push_back(k);
                                }
                            }
                        }
                        if(count >= 3){
                            if(!iscand ){
                                candidates[c].push(i);
                                iscand = true;
                            }
                            
                        }
                        c = token[j];
                        
                        count = 1;
                    }
                }
            }
            sort(keys.begin(), keys.end());
            return std::to_string(keys[63]);
        }
    }
}

