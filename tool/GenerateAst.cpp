#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <list>

using namespace std;
void defineAst (string outputDir, string baseName, list<string> types);
string trim (string& str);
void defineType(ofstream& writer, string baseName, string className, string fieldList);
vector<string> split(string&str, const string& del);
void defineVisitor(ofstream& writer, string baseName, list<string> types);

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
    writer << "using namespace std;"<<endl<<endl;

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

void defineType(ofstream& writer, string baseName, string className, string fieldList) {
    writer << "class " + className + " : public "+ baseName + "{"<<endl;
    writer << "public:"<<endl;

    vector<string> fields=split(fieldList, ", ");

    //fields
    for (string field : fields) {
        writer << "    "+field+"_;"<<endl;
    }

    //constructor

    writer << "    " + className+ "("+fieldList+") {"<<endl;

    //Store parameters in fields

    for (string field : fields) {
        string name = split(field, " ")[1];
        writer << "        this->"+name+"_ = "+name+";"<<endl;
    }
    writer<<"    }"<<endl;

    //visitor pattern
    writer << "    template <typename R>"<<endl;
    writer << "    R accept(Visitor<R> visitor){"<<endl;
    writer << "        return visitor.visit"+className+baseName+"(*this);"<<endl;
    writer << "    }"<<endl;

    writer<<"};"<<endl<<endl;
    
    

    
    
}

void defineVisitor(ofstream& writer, string baseName, list<string> types){
    writer << "    template <typename R>"<<endl;
    writer << "    class Visitor {"<<endl;
    for (string type : types) {
        string typeName=trim(split(type, ":")[0]);
        string temp=baseName;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //lowercase
        writer << "        virtual R visit"+typeName+baseName+"("+typeName+" "+ temp+") = 0;"<<endl;
    }
    writer << "        virtual R accept(Visitor<R> visitor);" <<endl;

    writer<< "    };"<<endl;
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