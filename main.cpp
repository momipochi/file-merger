#include <iostream>
#include <string>

#include "File_merger.h"

using namespace std;

int main() {

    string tmpA,tmpB,saveDir;
    int num;
    cout<<"choose first file: ";
    cin>>tmpA;
    cout<<"\n"<<"choose second file: ";
    cin>>tmpB;
    cout<<"\n"<<"specify save location and filename: ";
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
