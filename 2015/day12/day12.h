#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <regex>

namespace aoc2015{
    namespace day12{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);

        void run(){
            std::cout << "Part 1:" << std::endl;
            assert (solvedayp1("./2015/day12/day12sample")=="15");
            std::cout << solvedayp1("./2015/day12/day12") << std::endl;

            std::cout << "Part 2:" << std::endl;

            std::cout << solvedayp2("./2015/day12/day12") << std::endl;
        }

        class Group{
            public:
            bool barray = false;
            bool bred = false;
            std::vector<int> values = {};
            std::vector<Group*> children = {};
            Group* parent = nullptr;
            Group(){}
            int getval(){
                int res = 0;
                for(int i : values)res+=i;
                for(Group* g : children){
                    res += g->getval();
                }
                return res;
            }
            int getval2(){
                if(bred && !barray)return 0;
                int res = 0;
                for(int i : values)res+=i;
                for(Group* g : children){
                    res += g->getval2();
                }
                return res;
            }
        };

        std::vector<Group*> list;
        Group* root;

        void parse(std::vector<Group*>& list);
        int getval(std::vector<Group*>& list);
        int getval2(std::vector<Group*>& list);
        
        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse(list);
            int res = getval(list);
            return std::to_string(res);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            parse(list);
            int res = getval2(list);
            return std::to_string(res);
        }

        void parse(std::vector<Group*>& list){
            char c;
            list.clear();
            root = new Group;
            Group* group = root;
            list.push_back(root);
            std::string str = "";
            std::string val = "";
            bool bname = false;
            while(std::cin >> c){
                if(c == '{' || c=='['){
                    list.push_back(new Group());
                    group->children.push_back(list.back());
                    list.back()->parent = group;
                    group = list.back();
                    group->barray = c == '[';
                }else if(c=='}' || c== ']'){
                    if(val.size()>0)group->values.push_back(std::atoi(val.c_str()));
                    val = "";
                    group = group->parent;
                }
                else if(c=='"'){
                    bname = !bname;
                    if(bname)str="";
                    else {
                        group->bred |= str == "red";
                    }
                }else if(bname){
                    str.push_back(c);
                }else if(c == ':'||c==','){
                    if(val.size()>0)group->values.push_back(std::atoi(val.c_str()));
                    str = "";
                    val = "";
                }
                else{
                    val.push_back(c);
                }
            }
        }

        int getval(std::vector<Group*>& list){
            return root->getval();
        }
        int getval2(std::vector<Group*>& list){
            return root->getval2();
        }
    }
}

