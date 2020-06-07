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
            string lineBuild ="";
            vector<string> tmpA;
            vector<string> tmpB;
            if(getline(fileA,lineA)){

                stringstream a(lineA);
                string wordA;
                while(getline(a,wordA,',')){
                    tmpA.push_back(wordA);
                }
            }else{
                key1 = false;
            }
            if(getline(fileB,lineB)){
                stringstream b(lineB);
                string wordB;
                while(getline(b,wordB,',')){
                    tmpB.push_back(wordB);
                }

            }else{
                key2 = false;
            }

            if(tmpA.size() == 0){
                for(int i =0;i<tmpB.size();i++){
                    lineBuild+=",";
                }
                for(string str:tmpB){
                    lineBuild += str+",";
                }
            }else if(tmpB.size() == 0){
                for(int i =0;i<tmpA.size();i++){
                    lineBuild+=",";
                }
                for(string str:tmpA){
                    lineBuild += str+",";
                }
            }else {
                for(string str:tmpA){
                    lineBuild += str+",";
                }
                for(int i =0;i<tmpB.size()-1;i++){
                    lineBuild += tmpB[i]+",";
                }
                lineBuild += tmpB[tmpB.size()-1];
            }

            v.push_back(lineBuild);
        }
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
