#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using FileContent = std::vector<std::string>;
const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool isLetter(char c){
    return c>='A' && c<='Z';
}

bool isNumber(char c){
    return c>='0' && c<='9';
}

int main(int argc, char *argv[]){

    FileContent fileContent;
    
    std::ifstream inputFile(argv[1],std::ios::in);
    if(inputFile.good()){
        std::string line;
        while(!inputFile.eof()){
            std::getline(inputFile,line);
            for(auto& ch : line) ch = std::toupper(ch);
            fileContent.push_back(line);
        }
    }

    std::map<char,unsigned long long> charCount;
    for(auto ch : alphabet) charCount[ch]=0;
    unsigned long long totalCount = 0;

    for (auto &line : fileContent) {
        for (auto &ch : line) {
            if(isNumber(ch)||isLetter(ch)){
                totalCount++;
                charCount[ch]++;
            }

        }
    }

    bool orderByChar = true;
    if(argc==3){
        if (argv[2]=="--numorder") {
            orderByChar = false;
        }
        
    }

    double sum = 0.0;
    std::vector<std::pair<char,unsigned long long>> result;

    for (auto& [character,count] : charCount){
        double percentage = (static_cast<double>(count)/static_cast<double>(totalCount))*100.0;
        sum+=percentage;
       
       if(orderByChar) std::cout<<character<<" : "<<percentage<<'\n';
       else result.emplace_back(std::pair<char,unsigned long long>(character,count));
    }

  if(!orderByChar){ std::sort(result.begin(),result.end(),
   [](const std::pair<char,unsigned long long>& A,const std::pair<char,unsigned long long>& B)->bool{
       return A.second>B.second;
   });
   for(auto& [character,count] : result){
       double percentage = (static_cast<double>(count)/static_cast<double>(totalCount))*100.0;
         if(orderByChar) std::cout<<character<<" : "<<percentage<<'\n';
   }

  }





}