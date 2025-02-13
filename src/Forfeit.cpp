#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <list>

//#include "TokenType.hpp"
#include "Token.hpp"
#include "Scanner.hpp"
#include "Forfeit.hpp"


using namespace std;

bool hadError=false;


void runFile(string path, char** argv);
void runPrompt();
void run(string source);
void error(int line, string message);
void report (int line, string where, string message);

int main (int args, char** argv) {
    
    //std::cout <<args<<std::endl;
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

    ifstream input(argv[1]);
    stringstream buffer;
    buffer << input.rdbuf();
    string content=buffer.str();


    run(content);

};

void runPrompt() {
    string line;

    while (true) {
        cout << "> ";
        getline(cin, line);
        
        if (cin.eof()) {
            break;
        }
        run(line);
        if (hadError) {
            break;
        }
        hadError=false;
    }
}


void run(string source) {
    Scanner scanner(source);
    list<Token> tokens = scanner.scanTokens();

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

