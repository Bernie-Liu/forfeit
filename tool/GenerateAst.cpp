#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;
void defineAst (string outputDir, string baseName, list<string> types);

int main(int args, char** argv) {
    if (args !=2) {
        cout << "Usage: generate_ast <output directory>" << endl;
        return 1;
    }
    string outputDir=argv[1];
   
    defineAst(outputDir, "Expr", list<string> {"Binary   : Expr left, Token operator, Expr right",
      "Grouping : Expr expression",
      "Literal  : Object value",
      "Unary    : Token operator, Expr right"});
}

void defineAst (string outputDir, string baseName, list<string> types) {
    string path = outputDir + "/" + baseName +".hpp";

    ofstream writer(path);
    
    writer << "class "+ baseName +"{"<<endl;
    writer <<endl;
    writer << "};"<<endl;
    writer.close();
}