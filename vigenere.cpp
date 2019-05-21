#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using FileContent = std::vector<std::string>;
const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::map<char,std::map<char,char>> matrix;


void initializeMatrix(){

    std::string alphabet_copy = alphabet;

    for(size_t i = 0; i < alphabet.length(); i++)
    {
        for(size_t j = 0; j < alphabet.length(); j++)
        {
            matrix[alphabet[i]][alphabet[j]]=alphabet_copy[j];
        }
        std::rotate(alphabet_copy.begin(),alphabet_copy.begin()+1,alphabet_copy.end());

    }


}



bool isLetter(char c){
    return c>='A' && c<='Z';
}

bool isNumber(char c){
    return c>='0' && c<='9';
}


void encode(const std::string& code,FileContent& fileContent){

    int code_pos = 0;

    for(auto& line : fileContent){
        for (int i = 0; i<line.length();i++) {
            char& ch = line[i];
            if (isLetter(ch) || isNumber(ch)) {

                ch = matrix[code[code_pos]][ch];
                code_pos++;
                code_pos%=code.size();

            }
        }
    }
}

void decode(const std::string& code, FileContent& fileContent) {
    int code_pos = 0;
    for (auto &line : fileContent) {
        for (int i = 0; i<line.length();i++) {
            char& ch = line[i];
            if (isLetter(ch) || isNumber(ch)) {

                auto row = matrix[code[code_pos]];
                for(auto& pair : row){
                    if(pair.second==ch){
                        ch=pair.first;
                        break;
                    }

                }
                code_pos++;
                code_pos%=code.size();

            }
        }
    }
}



int main(int argc, char *argv[]){



    initializeMatrix();


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

    std::string code(argv[3]);
     for(auto& ch : code) ch = std::toupper(ch);

    if(mode=="--encode") encode(code,fileContent);
    else if(mode=="--decode") decode(code,fileContent);


    for(auto& str : fileContent) std::cout<<str<<'\n';




    return 0;
}