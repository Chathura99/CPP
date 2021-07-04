#include <iostream>
#include <fstream>
using namespace std;
# define NO_OF_CHARS 256
void preProcess( string str, int size,int badchar[NO_OF_CHARS]){
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = size;
 
    for (i = 0; i <size-1; i++)
        badchar[(int) str[i]] = size-i-1;
   
}
void search( string txt, string pat,string t){
    int m = pat.size();
    int n = txt.size();
    int count=0;
    int badchar[NO_OF_CHARS];
    ofstream f2("output/patternmatch"+t+"output");
    preProcess(pat, m, badchar);
    int wildcartplace[m];
    
    for (int i = m-1; i >=0; i--){
        if(pat[i]=='_')
            wildcartplace[i] = 1;
        else
            wildcartplace[i] = 0;
    }
    int s = 0; 
    while(s <= (n - m)){
        int j = m - 1;
        while(j >= 0 && pat[j] == txt[s + j] || wildcartplace[j]==1)
            j--;
        if (j < 0){
            if(badchar[txt[s + m-1]]==m && pat[m-1]==txt[s + m-1]){
                //cout << "pattern occurs = " <<  s <<" th index"<< endl;
                f2<<"pattern occurs = " <<  s <<" th index"<< endl;
                s++;
                count++;
            }else{
                //cout << "pattern occurs = " <<  s <<" th index"<< endl;
                f2<<"pattern occurs = " <<  s <<" th index"<< endl;
                s +=  badchar[txt[s + m-1]];
                count++;
            }
        }else{
            if(badchar[txt[s + m-1]]==m){
                s++;
            }else{
                s +=  badchar[txt[s + m-1]];
            }
        }
        //cout<<"\nshift by"<<s;
    }
    //cout<<"\n\""<<pat<<"\" pattern occures at "<<count<<" times in \""<<txt<<"\"\n\n";
    f2<<"\n"<<"pattern : "<<pat<<"\ntext : "<<txt<<"\noccures : "<<count<<" times"; 
}
int main(){
    char run='y';
    string txt,pat;
    string pat3;
    string test;
    while(run=='Y' || run=='y'){
        cout<<"\nEnter test case no (enter only no like 1, 2, 3, 4... ):";
        cin>>test;
        ifstream f1("input/text/text"+test+".txt");
        ifstream f2("input/pattern/pattern"+test+".txt");
        getline (f1, txt);
        getline (f2, pat);
	        if(pat.size()>0 && txt.size()>0 && f1.is_open() && f2.is_open()){
	            search(txt,pat,test);
	            cout<<"Search result saved in output folder successfully!\n";
	        }    
	        else
	            cout<<"Your test case not valid!\n";
        cout<<"\nDo you want to run another test case ('y'/'Y'/'n'/'N')?\n";
        f1.close();
        f2.close();
        cin>>run;
    }
    return 0;
}
