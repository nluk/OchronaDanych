#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string_view>
#include <set>



std::map<int,unsigned long long> occurences;
int minLen;

void oof(const std::string FILECONTENT){

    

    for(int i = 0; i < FILECONTENT.size(); i++)
    {
        for(int j = i+minLen; j < FILECONTENT.size(); j++)
        {
            
            if(FILECONTENT[i]==FILECONTENT[j]){
                int k = 0;
                int len = 0;
                int howMuch = 0;
                
             while((j+k < FILECONTENT.size()) && (i+k<FILECONTENT.size()) ){
                if (FILECONTENT[i + k] == FILECONTENT[j + k]) {
                           
                            k++;
                            howMuch++;
                            len=j-i;
                        } else {
                            len=j-i;
                            break;
                        }
             }

             if(howMuch>=minLen){
                 for(int nwd=1;nwd<=len;nwd++){
 
                           if (len % nwd == 0) {
                               if (nwd <= 20) occurences[nwd]++;
                           }
                       }
             }
            
                

                
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




int main(int argc, char *argv[]){






    std::string FILECONTENT;
    FILECONTENT.reserve(100000);
   
    std::ios::sync_with_stdio(false);
    minLen = std::stoi(std::string(argv[2]));
    
   

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

    for(auto& [number,frequency] : occurences){
        std::cout<<number<<" : "<<frequency<<'\n';
    }



    return 0;
}