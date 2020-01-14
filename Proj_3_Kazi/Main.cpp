//Project 2 | Sabeel Kazi | CS-780
//no need to display non canonical form because maps cannot hold duplicate keys
//multiplication is off also because of non duplicate keys
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <iterator> 
#include <stdio.h>
#include <vector>
#include <map>
using namespace std;

//open output file stream globally so all functions can acess it
ofstream myfile;

//a vector of maps that each store the key value pairs
vector<map<int, int>> store;

//function to merge duplicate keys
void mapMerge(int found, int exp, map<int, int>& polys){
  if(polys.count(found )){
    polys.find(found)->second += exp; 
  }
  else {
    polys.insert({found, exp});
  }
}

//function to store ints in line into a linkedList
void extractIntegerWords(string str, map<int, int>& polys){ 
    int keyValueCount = 1;                              //store as key if odd, store as value if even
    map<int, int> pairs;
    stringstream ss;     
  
    /* Storing the whole string into string stream */
    ss << str;
  
    /* Running loop till the end of the stream */
    string temp;
    int exp;                                    //stores the second integer/ coefficient
    int found; 
    while (!ss.eof()) { 
        /* extracting word by word from stream */
        ss >> temp; 
  
        /* Checking the given word is integer or not */
        //store alternating integers into the map
        if (stringstream(temp) >> found){
          if(keyValueCount == 1) {
            exp = found;
            keyValueCount++; 
          }
          else {
            mapMerge(found, exp, polys);
            keyValueCount = 1;
          }
        }
        /* To save from space at the end of string */
        temp = "";
    } 
    //newline for next line of numbs
    myfile <<"\n" ;
}

//function for printing addition linked lists
void printAddPolynomials(map<int, int>& p){
  int i=1;                                        //count elements for printing properly
  for (map<int, int>::iterator v = --p.end(); i <= p.size(); --v){
    if(v->second == 0)
      myfile << "";
    else if(v->first == 0 && i == p.size())
      myfile <<v->second;
    else if(v->first == 0)
      myfile <<v->second << " + ";
    else if(v->first == 0)
      myfile << v->second << " + ";
    else if(i != p.size())
      myfile << v->second << "x^" << v->first << " + ";
    else
      myfile << v->second << "x^" << v->first;
    i++;
  }
}

void canonicalAddition(map<int, int> polys){
  map<int, int> temp;  

  /* Go through the copied polynomial linked list. Add the similar elements of the first in the list. Move the front element to the 
  the new temp linkedList which holds the answer, and delete the element from the poly list. Do this for every 
  new front element of the temporary polys LinkedList */
  while(!polys.empty()){
    map<int, int>::iterator answer= polys.begin();
    for(map<int, int>::iterator it= ++polys.begin(); it != polys.end(); ++it){
      if(it->first == answer->first){
        answer->second += it->second;
        polys.erase(it);
      }
    }
    temp.insert(*(polys.begin()));
    map<int, int>::iterator eraseFirst= polys.begin();
    polys.erase(eraseFirst);
  }

  printAddPolynomials(temp);
}

//this function merges two maps and adds their entries with duplicate keys
void canonicalMapMerge(map<int, int>& one, map<int, int>& two){
  for(map<int, int>::iterator it= two.begin(); it != two.end();it++){
    map<int, int>::iterator it2 = one.find(it->first);
    //if the key value is not found in map 1, inser it to map 2
    if(it2 == two.end()){
      one.insert(*it);
    }
    //else add the coefficients, because maps can't hold dupe keys
    else{
      it2->second += it->second;
    }
  }
  //clear the second map
  two.clear();
}

void lineAddition(vector<map<int, int>> v){
  //for each 2nd linked list, push it into the previous one and then do canonical addition
  for (int i=1; i <= v.size(); i+=2){
    canonicalMapMerge(v[i-1], v[i]);
    myfile << "Lines " << i << " and " << i+1 << " :\n";
    canonicalAddition(v[i-1]);
    myfile << "\n";
  }
  myfile << "\n";
}

void lineSubtraction(vector<map<int, int>> v){
  //change the coefficient of each 2nd line to negative for subtraction
  for (int i=1; i <= v.size(); i+=2){
    for(map<int, int>::iterator it= v[i].begin(); it != v[i].end(); ++it){
        it->second *= -1;
    }
  }
  //for each 2nd linked list, push it into the second, then sort, add and print
  for (int i=1; i <= v.size(); i+=2){
    map<int, int>::iterator it= v[i-1].end();
    canonicalMapMerge(v[i-1], v[i]);
    myfile << "Lines " << i << " and " << i+1 << " :\n";
    canonicalAddition(v[i-1]);
    myfile << "\n";
  }
  myfile << "\n";
}

void lineMultiplication(vector<map<int, int>> v){
  //make bew vector to store the new multiplcations of each lines
  vector<map<int, int>> answer;

  //iterate through each of the lists and multiply
  for (int i=1; i <= v.size(); i+=2){
    map<int, int> temp;
    for(map<int, int>::iterator it= v[i-1].begin(); it != v[i-1].end(); ++it){
      for(map<int, int>::iterator it2= v[i].begin(); it2 != v[i].end(); ++it2){
        pair<int, int> t(it->second * it2->second, it->first + it2->first);
        temp.insert(t);
      }
    }
    answer.push_back(temp);                 //store the list into the vector
  }

  //iterate through the new vector and process, print the pairs
  int i = 1;
  for (vector<map<int, int>>::iterator it = answer.begin(); it != answer.end(); ++it){
    myfile << "Lines " << i << " and " << i+1 << " :\n";
    canonicalAddition(*it);
    myfile << "\n";
    i+= 2;
  }
  myfile << "\n";
}

int main()
{
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
    
    //process each line from the input file
    string line;
    int lineCount=1;
    while (getline(inFile, line)) { 
      //Print the line count for each polyniomial
      myfile <<"\nLine " << lineCount << ": " ;
      lineCount++;

      map<int, int> polys;                          //Store pairs in a map

      //First remove the newline character for each line
      line.pop_back();
      line.pop_back();
      
      //Call function to store integers into the map
      extractIntegerWords(line, polys);

      //Add the Polynomial using the function
      //sort them here, call by reference sort
      myfile <<"Canonical: \t\t\t\t\t";
      canonicalAddition(polys);

      store.push_back(polys);             //store linked lists into the vector for processing later

      myfile <<"\n";
    }
    //print out addition of line in canonical form
    myfile <<"\nCanonical Addition of lines ------------------------------------------------------\n";
    lineAddition(store);

    //print out subtraction of line in canonical form
    myfile <<"Canonical Subtraction of lines -----------------------------------------------------\n";
    lineSubtraction(store);

    //print out multiplication of line in canonical form
    myfile <<"Canonical Multiplication of lines --------------------------------------------------\n";
    lineMultiplication(store);

    // close the file stream
    inFile.close();
    myfile.close();
}
