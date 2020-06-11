#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

namespace vecBuild{
    vector<string> v;
}
enum Order{A_to_B=1,B_to_A=2};
class File_merger{
public:
    ofstream out;
    ifstream fileA,fileB;
    string dirA,dirB,merge_dir;
    int maxLength = 0;
    File_merger(string dirA, string dirB,string save,int num){
        if(num == Order::A_to_B){
            this->dirA = dirA;
            this->dirB = dirB;
        }
        if(num == Order::B_to_A){
            this->dirA = dirB;
            this->dirB = dirA;
        }
        this->merge_dir = save;
    }

    void checkLength(){
        fileA.open(dirA);
        fileB.open(dirB);
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
                if (tmpA.size() > maxLength) {
                    maxLength = tmpA.size();
                }else if(tmpB.size() > maxLength){
                    maxLength = tmpB.size();
                }
                tmpA.clear();
                tmpB.clear();
            }
        }
        fileA.close();
        fileB.close();
    }

    void build_line(string& str, vector<string>& tmp){
        for(string s:tmp){
            str += s+",";
        }
    }
    void build_line_2(string& str, vector<string>& longer, vector<string>& shorter){
        for (int i = 0; i < shorter.size(); i++) {
            str += longer[i] + " " + shorter[i] + ",";
            if ((shorter.size() - i) == 1) {
                for (int k = i + 1; k < longer.size(); k++) {
                    str += longer[k] + ",";
                }
            }
        }
    }

    void cellBuild() {
        fileA.open(dirA);
        fileB.open(dirB);

        if (fileA.is_open() || fileB.is_open()) {
            bool key1 = true, key2 = true;
            while (key1 || key2) {
                vector<string> tmpA;
                vector<string> tmpB;
                string lineBuild;
                string lineA, lineB;

                //splitting whole line into words
                if (getline(fileA, lineA)) {
                    stringstream a(lineA);
                    string wordA;
                    while (getline(a, wordA, ',')) {
                        tmpA.push_back(wordA);
                    }
                } else {
                    key1 = false;
                }
                if (getline(fileB, lineB)) {
                    stringstream b(lineB);
                    string wordB;
                    while (getline(b, wordB, ',')) {
                        tmpB.push_back(wordB);
                    }

                } else {
                    key2 = false;
                }

                //putting all into one string
                if (tmpA.size() == 0) {
                    build_line(lineBuild, tmpB);
                } else if (tmpB.size() == 0) {
                    build_line(lineBuild, tmpA);
                } else if (tmpA.size() >= tmpB.size()) {
                    build_line_2(lineBuild,tmpA,tmpB);
                } else if (tmpA.size() <= tmpB.size()) {
                    build_line_2(lineBuild,tmpB,tmpA);
                }

                //adding missing commas
                if(tmpA.size() == 0 && tmpB.size() == 0){
                    break;
                }else if(tmpA.size() == tmpB.size()){
                    for(int i = 0;i<maxLength-tmpB.size();i++){
                        lineBuild += ",";
                    }
                }else if(tmpA.size() > tmpB.size()){
                    for(int i =0 ;i<maxLength-tmpA.size();i++){
                        lineBuild += ",";
                    }
                }else if(tmpB.size() > tmpA.size()){
                    for(int i = 0;i<maxLength-tmpB.size();i++){
                        lineBuild += ",";
                    }
                }
                vecBuild::v.push_back(lineBuild);
            }
        }
        fileA.close();
        fileB.close();
    }

    void write(){
        merge_dir+="/merge.csv";
        out.open(merge_dir);
        if(out.is_open()){
            for(string str:vecBuild::v){
                out<<str<<"\n";
            }
        }
        out.close();
    }

    void show(){
        for(string str:vecBuild::v){
            cout<<str<<endl;
        }
        cout<<"file saved in: "<<merge_dir<<endl;
    }

};
//D:/pjatk/SecondSemester/ppc/C++/Project/Book1.csv
int main() {

    string tmpA,tmpB,saveDir;
    int num;
    cout<<"choose first file: ";
    cin>>tmpA;
    cout<<"\n"<<"choose second file: ";
    cin>>tmpB;
    cout<<"\n"<<"where would you like it to be saved: ";
    cin>>saveDir;
    cout<<"would you like to save from first file to the second file or from second file to first file?\n";
    cout<<"enter 1 for the first option, enter 2 for the second option\n";
    cin>>num;

    while(num > 3 && num < 0){
        cout<<"please enter 1 or 2\n";
        cin>>num;
    }

    File_merger fm(tmpA,tmpB,saveDir,num);
    fm.checkLength();
    fm.cellBuild();
    fm.write();
    fm.show();
    return 0;
}
