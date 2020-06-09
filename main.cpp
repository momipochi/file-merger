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

int maxLength=0;
    if(fileA.is_open() || fileB.is_open()) {
        bool lock1 = true, lock2 = true;
        while (lock1 || lock2) {
            vector<string> tmpA;
            vector<string> tmpB;
            string lineA, lineB;

            if(getline(fileA,lineA)){

                stringstream a(lineA);
                string wordA;
                while(getline(a,wordA,',')){
                    tmpA.push_back(wordA);
                }
            }else{
                lock1 = false;
            }
            if(getline(fileB,lineB)){
                stringstream b(lineB);
                string wordB;
                while(getline(b,wordB,',')){
                    tmpB.push_back(wordB);
                }

            }else{
                lock2 = false;
            }
            if ((tmpA.size() + tmpB.size()) > maxLength) {
                maxLength = tmpA.size() + tmpB.size();
            }
            tmpA.clear();
            tmpB.clear();
        }
    }
    fileA.close();fileB.close();
    fileA.open("Book1.csv");
    fileB.open("Book2.csv");

    if(fileA.is_open() || fileB.is_open()){
        bool key1 = true, key2=true;
        while(key1 || key2){
            vector<string> tmpA;
            vector<string> tmpB;
            string lineBuild;
            string lineA,lineB;

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


            if((tmpA.size()+tmpB.size()) < maxLength){
                if((tmpA.size()+tmpB.size() == 0)){
                    break;
                }

                int length = maxLength-(tmpA.size()+tmpB.size());
                cout<<length<<endl;
                for(int i = 0;i<length; i++){
                    lineBuild += ",";
                }

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
