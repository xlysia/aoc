#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 

namespace aoc2017{
    namespace day7{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2017/day7/day7sample")=="tknk");
            std::cout << solvedayp1("./2017/day7/day7") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2017/day7/day7sample")=="60");
            std::cout << solvedayp2("./2017/day7/day7") << std::endl;
        }

        struct disk{
            std::string name;
            int weight;
            std::vector<string> children;
            string parent = "";
        };

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            unordered_map<string,int> nametoID;
            vector<disk*> disks;
            int ID = 0;

            while(std::getline(std::cin,line)){
                std::istringstream iss(line);
                std::string token;

                iss >> token;
                if(nametoID.find(token)==nametoID.end()){
                    nametoID[token] = ID++;
                    disks.push_back(new disk());
                }
                disk* d = disks[nametoID[token]];
                d->name = token;
                iss >> token;
                d->weight = std::stoi(token.substr(1,token.size()-2));
                if(iss.good())iss >> token;
                while(iss.good()){
                    iss >> token;
                    if(iss.good()){
                        token.pop_back();
                    }
                    d->children.push_back(token);

                    if(nametoID.find(token)==nametoID.end()){
                        nametoID[token] = ID++;
                        disks.push_back(new disk());
                    }
                    disks[nametoID[token]]->parent = d->name;
                }

            }

            for(int i = 0; i < (int) disks.size(); i++){
                if(disks[i]->parent==""){
                    return disks[i]->name;
                }
            }   

            return "NOTDEF";
        }

        int dfs(vector<disk*> &disks, unordered_map<string,int> &nametoID, string name,int& ans){

            if(disks[nametoID[name]]->children.empty())return disks[nametoID[name]]->weight;

            int K = disks[nametoID[name]]->children.size();

            int b = -1;
        
            int a = dfs(disks,nametoID,disks[nametoID[name]]->children[0],ans);
        
            int corrected = -1;

            for(int i = 1; i < K; i++){
                
                int tmp = dfs(disks,nametoID,disks[nametoID[name]]->children[i],ans);
                
                if(b > -1){
                    if(tmp == b){
                        corrected = b;
                        ans = disks[nametoID[disks[nametoID[name]]->children[i-2]]]->weight - (a-b);
                    }
                    else{
                        corrected = a;
                        ans = disks[nametoID[disks[nametoID[name]]->children[i-1]]]->weight - (b - a);
                    } 
                    break;
                }
                if(tmp == a){
                    corrected = a;
                }
                else{
                    // found anomaly
                    b = tmp;
                    if(corrected>-1){
                        ans = disks[nametoID[disks[nametoID[name]]->children[i]]]->weight - (tmp - corrected);
                        break;
                    }

                }
                
            }
            return corrected*K + disks[nametoID[name]]->weight;
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;

            unordered_map<string,int> nametoID;
            vector<disk*> disks;
            int ID = 0;

            while(std::getline(std::cin,line)){
                std::istringstream iss(line);
                std::string token;

                iss >> token;
                if(nametoID.find(token)==nametoID.end()){
                    nametoID[token] = ID++;
                    disks.push_back(new disk());
                }
                disk* d = disks[nametoID[token]];
                d->name = token;
                iss >> token;
                d->weight = std::stoi(token.substr(1,token.size()-2));
                if(iss.good())iss >> token;
                while(iss.good()){
                    iss >> token;
                    if(iss.good()){
                        token.pop_back();
                    }
                    d->children.push_back(token);

                    if(nametoID.find(token)==nametoID.end()){
                        nametoID[token] = ID++;
                        disks.push_back(new disk());
                    }
                    disks[nametoID[token]]->parent = d->name;
                }

            }
            
            string base = "";

            for(int i = 0; i < (int) disks.size(); i++){
                if(disks[i]->parent==""){
                    base = disks[i]->name;
                    break;
                }
            }   

            int ans = -1;
            // we assumed that the anomaly is on odd nb of children in fact otherwise we have 2 possibilities and wed need to check both trees
            dfs(disks,nametoID,base,ans);

            return to_string(ans);
        }
    }
}

