#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
int main() {
    string line;
    ifstream fin("Periodic.svg");
    ofstream fout("new_Periodic.svg");
    while(!fin.eof()){
        getline(fin,line);
        if(fin.fail())
            break;
        string target1="<tspan(?:.*)?\\/>";
        regex r1(target1);
        line=regex_replace(line,r1,"");
        string target2="(\\d+\\.\\d{1})\\d*";
        regex r2(target2);
        line=regex_replace(line,r2,"$1");
        fout<<line;
    }
    fin.close();
    fout.close();
//    string line="<text id=\"text26\" xml:space=\"preserve\" y=\"130.46858\" x=\"205.44441\" style=\"font-size:1.32000005px;line-height:125%;fill:#000000;stroke-width:0.16500001\" font-size=\"8px\"><tspan id=\"tspan24\" y=\"130.46858\" x=\"205.44441\" style=\"stroke-width:0.16500001\"/></text>";
//    string target1="<tspan(?:.*)?\\/>";
//    regex r1(target1);
//    smatch m;
//    while(regex_search(line,m,r)){
//        for(auto x:m){
//            cout<<x<<' ';
//        }
//        cout<<endl;
//        line=m.suffix();
//    }
//    line=regex_replace(line,r1,"");
//    string target2="(\\d+\\.\\d{1})\\d*";
//    regex r2(target2);
//    line=regex_replace(line,r2,"$1");
//    cout<<line<<endl;
    return 0;
}