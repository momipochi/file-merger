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
    fileA.open("D:\\pjatk\\SecondSemester\\ppc\\C++\\Project\\Book1.csv");
    fileB.open("D:\\pjatk\\SecondSemester\\ppc\\C++\\Project\\Book2.csv");


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
                for(string str:tmpB){
                    lineBuild += str+",";
                }
            }else if(tmpB.size() == 0){
                for(string str:tmpA){
                    lineBuild += str+",";
                }
            }else if(tmpA.size()>=tmpB.size()){
                for(int i = 0;i<tmpB.size();i++){
                    lineBuild += tmpA[i]+" "+tmpB[i]+",";
                    if((tmpB.size()-i) == 1){
                        for(int k = i+1;k<tmpA.size();k++){
                            lineBuild+=tmpA[k]+",";
                        }
                    }
                }
            }else if(tmpA.size()<=tmpB.size()){
                for(int i = 0;i<tmpA.size();i++){
                    lineBuild += tmpA[i]+" "+tmpB[i]+",";
                    if((tmpA.size()-i) == 1){
                        for(int k = i+1; k<tmpB.size();k++){
                            lineBuild+=tmpB[k]+",";
                        }
                    }
                }
            }

            v.push_back(lineBuild);
        }
    }


    out.open("D:\\pjatk\\SecondSemester\\ppc\\C++\\Project\\merge.csv");
    if(out.is_open()){
        for(string str:v){
            out<<str<<"\n";
        }
    }
    out.close();

    for(string str:v){
        cout<<str<<endl;
    }
    string b = "fuck you";

    cout<<b[1]<<endl;
    return 0;
}
