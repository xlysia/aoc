#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <vector>

using namespace std;

namespace aoc2018{
    namespace day8{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2018/day8/day8sample")=="138");
            std::cout << solvedayp1("./2018/day8/day8") << std::endl;

            std::cout << "Part 2" << std::endl;
            solvedayp2("./2018/day8/day8sample");
            assert (solvedayp2("./2018/day8/day8sample")=="66");
            std::cout << solvedayp2("./2018/day8/day8") << std::endl;
        }


        struct node{
            int nchildren;
            int nmeta;
            vector<node> children;
        };

        int dfs(istream& in, node* n){
            int ans = 0;
            in >> n->nchildren;
            in >> n->nmeta;
            for (int i=0;i<n->nchildren;i++){
                node* child = new node;
                ans += dfs(in,child);
                n->children.push_back(*child);
            }
            for (int i=0;i<n->nmeta;i++){
                int val;
                in >> val;
                ans += val;
            }
            return ans;
        }

        int dfs2(istream& in, node* n){
            int ans = 0;
            in >> n->nchildren;
            in >> n->nmeta;
            vector<int> childvals;
            for (int i=0;i<n->nchildren;i++){
                node* child = new node;
                childvals.push_back(dfs2(in,child));
                n->children.push_back(*child);
            }

            if(n->nchildren==0){
                for (int i=0;i<n->nmeta;i++){
                    int val;
                    in >> val;
                    ans += val;
                }
                return ans;
            }

            for (int i=0;i<n->nmeta;i++){
                int val;
                in >> val;
                if(val > n->nchildren)continue;
                ans += childvals[val-1];
            }
            return ans;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());

            node* root = new node;
            int ans = dfs(cin,root);
            return std::to_string(ans);
        }

        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());

            node* root = new node;
            int ans = dfs2(cin,root);
            return std::to_string(ans);
        }
    }
}

