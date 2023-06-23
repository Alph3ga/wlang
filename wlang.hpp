#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <regex>

#define BUFFER_SIZE 8192  // 8kb buffer size, each sentence can be maximum of this size

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::regex;

const string EXTENSION= "wlang";  // the valid extension of a sourcecode file

std::ifstream sourceCode;  // input file stream for source code file
// all the mappings for variable name ( to type, and to value )
std::unordered_map<string, int> typeMap;
std::unordered_map<string, long long int> numberMap;
std::unordered_map<string, long double> decimalMap;
std::unordered_map<string, string> stringMap;

bool checkExtension(char* filename);
int interpret(char* sentence);

int printAction(string sentence);
int declareAction(string sentence);
int assignAction(string sentence);
int getAction(char* sentence);

string validateString(string statement);