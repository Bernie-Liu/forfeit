#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <list>

using namespace std;

vector<string> split(string&str, const string& del);
string trim (string& str);


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

void defineAst (string outputDir, string baseName, list<string> types) {
    string path = outputDir + "/" + baseName +".cpp";

    ofstream writer(path);
    writer << "#include <any>"<<endl;
    writer << "#include \"Token.hpp\""<<endl;
    //writer << "using namespace std;"<<endl<<endl;

    for (string type : types) {
        string className=trim(split(type, ":")[0]);
        writer << "class "+className+";"<<endl;
    }

    writer<<endl;

    writer << "class "+ baseName +"{"<<endl;
    writer << "public:"<<endl;
    defineVisitor(writer, baseName, types);


    writer << "};"<<endl<<endl;
    
    //AST classes
    for (string type : types) {
        vector<string> vec=split(type, ":");

        string className=trim(vec[0]);
        string fields=trim(vec[1]);
        defineType(writer, baseName, className, fields);
    }

    //base accept()
    writer <<endl;
    


    writer.close();
    
}

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