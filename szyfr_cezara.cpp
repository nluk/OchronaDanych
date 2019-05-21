#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using FileContent = std::vector<std::string>;
const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";



bool isLetter(char c){
    return c>='A' && c<='Z';
}

bool isNumber(char c){
    return c>='0' && c<='9';
}


void encode(int n,FileContent& fileContent){

    
    for(auto& line : fileContent){
        for(auto& ch : line){
            if(isLetter(ch)||isNumber(ch)){
                int pos = alphabet.find(ch);
                pos = (pos+n)%alphabet.size();
                ch = alphabet[pos];
            }
        }
    }
}

void decode(int n, FileContent &fileContent) {
    for (auto &line : fileContent) {
        for (auto &ch : line) {
            if (isLetter(ch) || isNumber(ch)) {

                int pos = alphabet.find(ch);
                n %= alphabet.size();

                if (n <= pos) {
                    pos-=n;
                    ch = alphabet[pos];
                } else {
                    int newPos = alphabet.size() - n + pos;
                    ch = alphabet[newPos];
                }
            }
        }
    }
}



int main(int argc, char *argv[]){

    

    FileContent fileContent;
    const std::string mode(argv[1]);



    std::ifstream inputFile(argv[2],std::ios::in);
    if(inputFile.good()){
        std::string line;
        while(!inputFile.eof()){
            std::getline(inputFile,line);
            for(auto& ch : line) ch = std::toupper(ch);
            fileContent.push_back(line);
        }
    }

    int n = std::stoi(argv[3]);

    if(mode=="--encode") encode(n,fileContent);
    else if(mode=="--decode") decode(n,fileContent);


    for(auto& str : fileContent) std::cout<<str<<'\n';
    



    return 0;
}