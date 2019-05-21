#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string_view>
#include <set>

//using FileContent = std::vector<std::string>;
using LineViews = std::vector<std::string_view>;


int countSubstring(const std::string& FILECONTENT, const std::string_view& substring){
   int occurrences = 0;
   std::string::size_type pos = 0;
   int distance;
   bool foundFirst = false;

   int lastPos = 0;

   while ((pos = FILECONTENT.find(substring, pos )) != std::string::npos) {
            
          ++ occurrences;
          if(occurrences==2 && !foundFirst) {
              distance = (pos-lastPos);
              foundFirst=true;
          }
          
          pos += substring.length();
          lastPos = pos;
          
   }
   if(occurrences>1){
       std::cout <<substring<<" : " <<occurrences << std::endl;
        std::cout<<"Distance : "<<distance<<'\n';
   }

   return occurrences;
}

void oof(const std::string FILECONTENT){
    
    std::map<std::string,unsigned long long> occurences;
    std::set<std::string_view> uniqueSubstrings;

    for(int substringLength = 20; substringLength>=2; --substringLength){
        int startPos = 0;
        int endPos = startPos + substringLength;
        while(endPos<FILECONTENT.length()){
            int count = 1;
            std::string_view substring {FILECONTENT.c_str()+startPos,substringLength};//FILECONTENT.substr(startPos,endPos);
            if(uniqueSubstrings.find(substring)==uniqueSubstrings.end()){
                uniqueSubstrings.emplace(substring);
                 count = countSubstring(FILECONTENT,substring);
            }
           if(count>1){
                startPos+=substringLength;
                endPos+=substringLength;
            }
            else{
             startPos++;
             endPos++;
            }

        }
        
    }

   
    
}


bool isLetter(char c){
    return c>='A' && c<='Z';
}

bool isNumber(char c){
    return c>='0' && c<='9';
}

void select_alphabet_only(const std::string& line, std::string& FILECONTENT){
    for(const auto& character : line){
        if(isLetter(character)||isNumber(character)){
            FILECONTENT.push_back(character);
        }
    }
}

void sanitize_lines(const std::string& line,LineViews& lineViews){
    int substringBeginning = 0;
    for(int currentPos =0; currentPos<line.length();currentPos++){
        if(!isLetter(line[currentPos]) && !isNumber(line[currentPos])){
            std::string_view substring(line);
            substring.remove_prefix(substringBeginning);
            substring.remove_suffix(line.length()-currentPos);
            if(substring.length()>1) lineViews.push_back(std::move(substring));
            substringBeginning=currentPos+1;
        }
    }
}


int main(int argc, char *argv[]){






    std::string FILECONTENT;
    FILECONTENT.reserve(100000);
   
    std::ios::sync_with_stdio(false);
    
   

    std::ifstream inputFile(argv[1],std::ios::in);
    if(inputFile.good()){
        std::string line;
        while(!inputFile.eof()){
            std::getline(inputFile,line);
            for(auto& ch : line) ch = std::toupper(ch);
            select_alphabet_only(line,FILECONTENT);
        }
    }

    for(auto character : FILECONTENT)std::cout<<character;

   std::cout<<"\n********************************\n";


    
    oof(FILECONTENT);




    return 0;
}