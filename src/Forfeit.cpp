#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <list>

#include "TokenType.hpp"
#include "Token.hpp"

using namespace std;

bool hadError=false;

template <typename T>
int main (int args, char** argv) {
    //std::cout << "start" << std::endl;
    if (args >2) {
        std::cout << "Usage: Forfeit [script]" << std::endl;
        return 1;
    }
    else if (args==2) {
        runFile(argv[1], argv);
        if (hadError) return 1;
    }
    else {
        runPrompt();
        if (hadError) return 1;
    }
    return 0;

    
}

void runFile(string path, char** argv) {

    /*ifstream ifs(path, ios::binary|ios::ate);
    ifstream::pos_type pos=ifs.tellg();
    std::vector<char> result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);*/

    ifstream input(argv[1]);
    stringstream buffer;
    buffer << input.rdbuf();
    string content=buffer.str();


    auto run(content);

    

};

void runPrompt() {
    string line;

    while (true) {
        cout << "> ";
        getline(cin, line);
        
        if (cin.eof()) {
            break;
        }
        auto run(line);
        if (hadError) {
            break;
        }
        hadError=false;
    }
}

template <typename T>
void run(string source) {
    Scanner scanner = new Scanner(source);
    list<Token<T>> tokens = scanner.scanTokens();

    //Temp
    for (Token token : tokens) {
        cout << token << endl;
    }
}

void error(int line, string message) {
    report(line, "", message);
}

void report (int line, string where, string message){
    cout << "[line "<<line<<"] Error"<<where<<": "<<message<<endl;
    hadError=true;
}

