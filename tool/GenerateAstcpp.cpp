#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <list>

using namespace std;


int main(int args, char** argv) {
    if (args !=2) {
        cout << "Usage: generate_ast <output directory>" << endl;
        return 1;
    }
    string outputDir=argv[1];
    
    
    //op=operator
    defineAst(outputDir, "Expr", list<string> {"Binary   : Expr left, Token op, Expr right",
      "Grouping : Expr expression",
      "Literal  : any value",
      "Unary    : Token op, Expr right"});
}

vector<string> split(string&str, const string& del);
string trim (string& str);

string trim(string& str) {
    //leading and trailing whitespace
    regex pattern("^\\s+|\\s+$");
    return regex_replace(str, pattern, "");
}

vector<string> split(string&str, const string& del) {
    regex pattern(del);
    sregex_token_iterator it(str.begin(), str.end(), pattern, -1);
    sregex_token_iterator end;
    vector<std::string> result(it, end);

    return result;
}