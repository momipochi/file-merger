#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ofstream out;
    ifstream fileA,fileB;
    vector<string> v;
    fileA.open("Book1.csv");
    fileB.open("Book2.csv");


    if(fileA.is_open() || fileB.is_open()){
        string lineA,lineB;
        bool key1 = true, key2=true;
        while(key1 || key2){
            string row ="";
            if(getline(fileA,lineA,'\n')){
                row += lineA+",";
            }else{
                key1=false;
            }
            if(getline(fileB,lineB,'\n')){
                row += lineB;
            }else{
                key2=false;
            }
            v.push_back(row);
        };
    }


    out.open("merge.csv");
    if(out.is_open()){
        for(string str:v){
            out<<str<<"\n";
        }
    }
    out.close();

    for(string str:v){
        cout<<str<<endl;
    }

    return 0;
}
