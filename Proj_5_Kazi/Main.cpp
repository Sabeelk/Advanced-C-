//Project 2 | Sabeel Kazi | CS-780
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator> 
#include <stdio.h>
#include <map>

using namespace std;

ofstream myfile;
map<string, map<int, int> > map1;                 //map stores the word and 

int main(){
    //open output file stream globally so all functions can acess it
    myfile.open("output.txt");

    ifstream inFile;
    // open the file stream
    inFile.open("input.txt");
    // check if opening a file failed
    if (inFile.fail()) {
        cerr << "Error opening the file" << endl;
        inFile.close();
        exit(1);
    }

    //read each line and process each word
    string line, word;
    int lineCount = 1;
    while (getline(inFile, line)) {
        // skip empty lines:
        if(line.empty()) continue;

        istringstream lineStream(line);
        for (int wordPos = 0; lineStream >> word; wordPos += word.size()+1) {
            //If it's not in the map, insert it
            //if it is add to value map
            map1[word][lineCount] =  wordPos;
        }
        lineCount++;
    }

    //print each part of the map
    for(auto i: map1){
        myfile << i.first << " " << i.second.size() << " [ ";
        for(auto j: i.second){
            myfile << "(" << j.first << "," << j.second << ") ";
        }
        myfile << "]" << endl;
    }

    // close the file stream
    inFile.close();
    myfile.close();
}