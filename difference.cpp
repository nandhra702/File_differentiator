//firstly we need to open the files, read in the content, then print the string s containing the lines that are different

#include<fstream>
#include<iostream>
#include<vector>
#include<iomanip>
#include <boost/algorithm/string.hpp>
#include<queue>
using namespace std;
using namespace boost::algorithm;

string formatter(string s, int i, queue<int>* qptr, bool file_tag){

       
    //we take the string input, then we see if it fits the width of 60 characters.
    //if it doesnt, we either trim it down or add spaces to the end of it.
    
    int length = s.length();
    if(length>60){
        //we need to trim it down to 60 characters
        s = s.substr(0,60); //so extract substring of length 60 starting from index 0
    
    }

    else if(length<60){
        //we will need to add spaces to its end
        s+= string(60 - length, ' ');

    }
    
    //this function will format the string s to be of fixed width 60 and color it if different
    if(file_tag){
        //means we are formatting file2
        //firstly we check the top element of the queue
        if(!qptr->empty() && qptr->front() == i){
            //means this line is different, so we color it red
            s = "\e[31m" + s + "\e[0m"; //red color escape sequence
            qptr->pop(); //remove the top element from the queue
        }

    }
      
    return s; //we return the string if its already of length 60
}



int main(int argcount, char* argv[]){

     if(argcount != 3){
        cout << "Usage: differentiate <file1> <file2>\n";
        return 1;
    }


    string file1_address = argv[1];
    string file2_address = argv[2];

    
    //now while reading the files, we need to skip empty lines and lines that are comments and lines 
    //that are part of multiline comments.
    
    fstream infile1 (file1_address);
    bool file_tag1 = false; //this helps us to identify which file we are currently formatting
    //error handling bhi kr hi lo
    if(!infile1.is_open()){
        cout<<"The file file1.txt didnt open";
        return 1;
    }
    
    vector<string>f1data;
    string temp="";
    while(getline(infile1,temp)){
        
        trim(temp); //trim the string to remove leading and trailing spaces
        if(!(temp.empty() || temp[0] == '#' || (temp[0] == '/' && temp[1] == '/'))) {
            //skip empty lines and comment lines
            f1data.push_back(temp); 
            //we push back only if the line is not empty and not a comment
        }
        
    }

    
    //do same for the 2nd file and then close both the files
    fstream infile2 (file2_address);
    bool file_tag2 = true; //this helps us to identify which file we are currently formatting
    //error handling bhi kr hi lo
    if(!infile2.is_open()){
        cout<<"The file file2.txt didnt open";
        return 1;
    }
    
    vector<string>f2data;
    temp="";
    while(getline(infile2,temp)){
        trim(temp);
        if(!(temp.empty() || temp[0] == '#' || (temp[0] == '/' && temp[1] == '/'))) {
            //skip empty lines and comment lines
            f2data.push_back(temp);
        }
        
        
    }


    //now before comparing, we equate the number of elements in both vectors. IF either one is shorter, we add empty spaces to the bottom of the file as well as to the vector.
    if(f1data.size()>f2data.size()){
        //means file 2 is smaller
        //so we add new lines to the bottom of file 2 and to its vector
        int diff = f1data.size()-f2data.size();
        for(int i=0;i<diff;i++){
            f2data.push_back("");
           
        }
    }

    else{
        //means file1 is short in lenght
        int diff = f2data.size()-f1data.size();
        for(int i=0;i<diff;i++){
            f1data.push_back("");
        }

    }

    //close both the files
    infile1.close();
    infile2.close();

    //now I need to compare 2 files of same size
    queue<int> result;
    for(int i=0;i<f1data.size();i++){
        if(f1data[i]!=f2data[i]){
            result.push(i); //store the index of the line that is different
        }
    }
    //pointer to this queue that we will pass to the formatter function
    queue<int>* qptr = &result;    

    cout<<"\e[30;105m  DISPLAYING BOTH THE FILES : RED LINES INDICATE CHANGES IN 2nd FILE AGAINST 1st \e[0m"<<"\n\n";



    for(int i=0;i<f1data.size();i++){
        cout<<formatter(f1data[i],i,qptr,file_tag1)<<" || "<<formatter(f2data[i],i,qptr,file_tag2)<<"\n";
    }
    


}
