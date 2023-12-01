#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

namespace aoc2023{
    namespace day1{

        std::string solvedayp1(std::string p);
        std::string solvedayp2(std::string p);
        void run(){
            std::cout << "Part 1" << std::endl;
            assert (solvedayp1("./2023/day1/day1sample")=="142");
            std::cout << solvedayp1("./2023/day1/day1") << std::endl;

            std::cout << "Part 2" << std::endl;
            assert (solvedayp2("./2023/day1/day1sample2")=="281");
            std::cout << solvedayp2("./2023/day1/day1") << std::endl;
        }

        std::string solvedayp1(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;

            while(std::getline(std::cin, line)){
                int N = line.size();
                for(int i = 0; i < N ; i++){
                    if(isdigit(line[i])){
                        res += (line[i] - '0')*10;
                        break;
                    }
                }
                for(int i = N-1 ; i >= 0 ; i--){
                    if(isdigit(line[i])){
                        res += line[i] - '0';
                        break;
                    }
                }
            }
            return std::to_string(res);
        }

        //make a map of numbers in english
        class TrieNode{
            public:
                TrieNode* children[26];
                int val = 0;
                TrieNode(){
                }
        };

        class Trie{
            public:
                TrieNode* root;
                Trie(){
                    root = new TrieNode();
                }

                queue<TrieNode*> candidates;

                void insert(std::string s, int val){
                    TrieNode* curr = root;

                    for(int i = 0; i < (int)s.size(); i++){
                        int idx = s[i] - 'a';
                        if(curr->children[idx] == NULL){
                            curr->children[idx] = new TrieNode();
                        }
                        curr = curr->children[idx];
                    }
                    curr->val = val;
                }

                int search(char c){
                    candidates.push(root);
                    int s = candidates.size();
                    int ans = 0;
                    while(s--){
                        TrieNode* curr = candidates.front();
                        candidates.pop();
                        if(curr->children[c - 'a'] != NULL){
                            curr = curr->children[c - 'a'];
                            if(curr->val){
                                ans = curr->val;
                            }else candidates.push(curr);
                        }
                    }
                    return ans;
                }
                void clear(){
                    while(!candidates.empty()){
                        candidates.pop();
                    }
                }

        };


        std::string solvedayp2(std::string p){
            std::ifstream in(p);
            std::cin.rdbuf(in.rdbuf());
            std::string line;
            int res =  0;
            Trie trie = Trie();
            trie.insert("one",1);
            trie.insert("two",2);
            trie.insert("three",3);
            trie.insert("four",4);
            trie.insert("five",5);
            trie.insert("six",6);
            trie.insert("seven",7);
            trie.insert("eight",8);
            trie.insert("nine",9);


            while(std::getline(std::cin, line)){

                int first = 0;
                int last = 0;

                int N = line.size(); 
                for(int i = 0; i < N ; i++){
                    if(isdigit(line[i])&&line[i]!='0'){
                        if(!first){
                            first = (line[i]-'0')*10;
                            last = (line[i]-'0');
                        }
                        else last = line[i]-'0';
                    }else{
                        int tmp = trie.search(line[i]);
                        if(tmp){
                            if(!first){
                                first = tmp*10;
                                last = tmp;
                            }
                            else last = tmp;
                        }
                    }
                }
                trie.clear();
                res += first+last;
            }
            return std::to_string(res);
        }
    }
}

