#include "wlang.hpp"
#include "regex_constant.hpp"

int main(int argc, char *argv[]){
    // check command line arguments
    if(argc!=2){
        cerr<< "Error: Too many or too few command line arguments."<< endl;
        return 1;
    }
    if(!checkExtension(argv[1])){
        cerr<< "Error: Incorrect file extension for input file."<< endl;
        return 1;
    }

    // try opening the file 
    sourceCode.open(argv[1]);
    if(sourceCode.fail()){
        cerr<< "Error: Cannot open input file."<< endl;
        return 1;
    }

    char sentence[BUFFER_SIZE]; // sentence buffer for further parsing, size macro defined

    while(1){
        sourceCode.getline(sentence, BUFFER_SIZE, '.');
        if(sourceCode.eof()){
            break;
        }

        interpret(sentence);
    }

    return 0;
}


/** check if filename ends with correct extension
 * extension is defined in the variable EXTENSION globally
 * @param filename the name of the file
 * @return true if the extension is correct, false otherwise
*/
bool checkExtension(char* filename){
    for(int i=0; filename[i]!='\0'; i++){
        if(filename[i]=='.'){
            int j;
            for(j=1; j<=EXTENSION.length(); j++){
                if(filename[i+j]!= EXTENSION[j-1]){
                    return false;
                }
            }
            if(filename[i+j]!='\0'){
                return false;
            }
            return true;
        }
    }
    return false;
}

int interpret(char* sentence){
    int action= getAction(sentence);

    switch(action){
        case 0: // print statement
            printAction(sentence);
            break;
        case 1: // declaration
            declareAction(sentence);
            break;
    }
    return 0;
}

int getAction(char* sentence){
    for(int i=0; i<2; i++){
        if(std::regex_match(sentence, regex(regexStrings[i]))){
            return i;
        }
    }
    return 0;
}

int printAction(string sentence){
    std::smatch m;
    regex_search(sentence, m, regex("\".*\""));
    if(!m.empty()){
        cout<< validateString(string(m[0]));
    }
    return 0;
}

string validateString(string statement){
    statement= std::regex_replace(statement, regex("\""), "");
    for(auto key: regexEscape){
        statement= std::regex_replace(statement, key.second, key.first);
    }
    return statement;
}

int declareAction(string sentence){
    std::smatch m;
    std::regex_match(sentence, m, regex("Let\\s\\$([\\w]+?)\\sbe\\san?([a-z]+?)"));
    if(m.size()==0){ return 1;}

    string varName= string(m[1]);
    if(typeMap.contains(varName)){ return 1;}

    if(string(m[2])=="integer"){
        typeMap[varName]= 0;
    }
    else if(string(m[2])=="decimal"){
        typeMap[varName]= 1;
    }
    else if(string(m[2])=="string"){
        typeMap[varName]= 3;
    }
    else{
        return 1;
    }
    return 0;
}

int assignAction(string sentence){
    std::smatch m;
    std::regex_search(sentence, m, regex("(?<=\\$)([\\w]+?)\\s"));
    string varName= m[0];
    if(!typeMap.contains(varName)){ return 1;}
    
    return 0;
}