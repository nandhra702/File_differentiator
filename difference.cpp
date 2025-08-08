//firstly we need to open the files, read in the content, then print the string s containing the lines that are different

#include<fstream>
#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

string formatter(string s){

    //this function will format the string s to be of fixed width 60
    //we take the string input, then we see if it fits the width of 60 characters.
    //if it doesnt, we either trim it down or add spaces to the end of it.

    int length = s.length();
    if(length>60){
        //we need to trim it down to 60 characters
        s = s.substr(0,60); //so extract substring of length 60 starting from index 0
        return s;
    }

    else if(length<60){
        //we will need to add spaces to its end
        s+= string(60 - length, ' ');
        return s;
    }
    return s; //we return the string if its already of length 60
}



int main(){
    
    fstream infile1 ("file1.txt");
    //error handling bhi kr hi lo
    if(!infile1.is_open()){
        cout<<"The file file1.txt didnt open";
        return 1;
    }
    
    vector<string>f1data;
    string temp="";
    while(!infile1.eof()){
        getline(infile1,temp);
        f1data.push_back(temp);
    }

    
    //do same for the 2nd file and then close both the files
    fstream infile2 ("file2.txt");
    //error handling bhi kr hi lo
    if(!infile2.is_open()){
        cout<<"The file file2.txt didnt open";
        return 1;
    }
    
    vector<string>f2data;
    temp="";
    while(!infile2.eof()){
        getline(infile2,temp);
        f2data.push_back(temp);
    }

    //now before comparing, we equate the number of elements in both vectors. IF either one is shorter, we add empty spaces to the bottom of the file as well as to the vector.
    if(f1data.size()>f2data.size()){
        //means file 2 is smaller
        //so we add new lines to the bottom of file 2 and to its vector
        int diff = f1data.size()-f2data.size();
        for(int i=0;i<diff;i++){
            f2data.push_back("");
            //now we also add newlines to bottom of file2.
            infile2<<"\n";
        }
    }

    else{
        //means file1 is short in lenght
        int diff = f2data.size()-f1data.size();
        for(int i=0;i<diff;i++){
            f1data.push_back("");
            //now we also add newlines to bottom of file1.
            infile1<<"\n";
        }

    }

    //close both the files
    infile1.close();
    infile2.close();

    //now I need to compare 2 files of same size
    string result="";
    for(int i=0;i<f2data.size();i++){
        if(f1data[i]!=f2data[i]){
            result+= "_" + to_string(i+1);
        }
    }
    cout<<result<<"\n";

    cout<<"DISPLAYING BOTH THE FILES TOGETHER\n\n";
    for(int i=0;i<f1data.size();i++){
        cout<<formatter(f1data[i])<<" || "<<formatter(f2data[i])<<"\n";
    }
    


}
