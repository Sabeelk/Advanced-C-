//Project 2 | Sabeel Kazi | CS-780
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <iterator> 
#include <stdio.h>
#include <vector>
using namespace std;

//open output file stream globally so all functions can acess it
ofstream myfile;

vector<list<pair<int, int>>> store;

//function to store ints in line into a linkedList
void extractIntegerWords(string str, list<pair<int, int>>& polys){ 
    int keyValueCount = 1;                              //store as key if odd, store as value if even
    pair<int, int> pairs;
    stringstream ss;     
  
    /* Storing the whole string into string stream */
    ss << str; 
  
    /* Running loop till the end of the stream */
    string temp; 
    int found; 
    while (!ss.eof()) { 
        /* extracting word by word from stream */
        ss >> temp; 
  
        /* Checking the given word is integer or not */
        //store alternating integers into linked list as pairs
        if (stringstream(temp) >> found){
          if(keyValueCount == 1) {
            pairs.first = found;
            keyValueCount++; 
          }
          else {
            pairs.second = found;
            pair<int, int> input(pairs);
            polys.push_back(input);
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
void printAddPolynomials(list<pair<int, int>>& p){
  int i=1;                                        //count elements for printing properly
  for (auto v : p){
    if(v.first == 0)
      myfile << "";
    else if(v.second == 0 && i == p.size())
      myfile <<v.first;
    else if(v.second == 0)
      myfile <<v.first << " + ";
    else if(v.second == 0)
      myfile << v.first << " + ";
    else if(i != p.size())
      myfile << v.first << "x^" << v.second << " + ";
    else
      myfile << v.first << "x^" << v.second;
    i++;
  }
}

void sortPolynomials(list<pair<int, int>>& p){
  for(list<pair<int, int> >::iterator it= p.begin(); it != p.end(); ++it){
    int temp = it->first;
    it->first = it->second;
    it->second = temp;
  }
  p.sort();
  p.reverse();
  for(list<pair<int, int> >::iterator it= p.begin(); it != p.end(); ++it){
    int temp = it->first;
    it->first = it->second;
    it->second = temp;
  }
}

void nonCanonical(list<pair<int, int>>& polys){
  printAddPolynomials(polys);
}

void canonicalAddition(list<pair<int, int>> polys){
  list<pair<int, int> > temp;  

  /* Go through the copied polynomial linked list. Add the similar elements. Move the front element to the 
  the new temp linkedList which holds the answer, and delete the element from the poly list. Do this for every 
  new front element of the temporary polys LinkedList */
  while(!polys.empty()){
    pair<int, int>& answer= polys.front();
    for(list<pair<int, int> >::iterator it= ++polys.begin(); it != polys.end(); ++it){
      if(it->second == answer.second){
        answer.first += it->first;
        polys.erase(it);
      }
    }
    temp.push_back(polys.front());
    polys.pop_front();
  }

  printAddPolynomials(temp);
}

void lineAddition(vector<list<pair<int, int>>> v){
  //for each 2nd linked list, push it into the first
  for (int i=1; i <= v.size(); i+=2){
    list<pair<int, int> >::iterator it= v[i-1].end();
    v[i-1].merge(v[i]);
    sortPolynomials(v[i-1]);
    myfile << "Lines " << i << " and " << i+1 << " :\n";
    canonicalAddition(v[i-1]);
    myfile << "\n";
  }
  myfile << "\n";
}

void lineSubtraction(vector<list<pair<int, int>>> v){
  //change the coefficient of each 2nd line to negative for subtraction
  for (int i=1; i <= v.size(); i+=2){
    for(list<pair<int, int> >::iterator it= v[i].begin(); it != v[i].end(); ++it){
        it->first *= -1;
    }
  }
  //for each 2nd linked list, push it into the first, then sort, add and print
  for (int i=1; i <= v.size(); i+=2){
    list<pair<int, int> >::iterator it= v[i-1].end();
    v[i-1].merge(v[i]);
    sortPolynomials(v[i-1]);
    myfile << "Lines " << i << " and " << i+1 << " :\n";
    canonicalAddition(v[i-1]);
    myfile << "\n";
  }
  myfile << "\n";
}

void lineMultiplication(vector<list<pair<int, int>>> v){
  //make bew vector to store the new multiplcations of each lines
  vector<list<pair<int, int>>> answer;

  //iterate through each of the lists and multiply
  for (int i=1; i <= v.size(); i+=2){
    list<pair<int, int>> temp;
    for(list<pair<int, int> >::iterator it= v[i-1].begin(); it != v[i-1].end(); ++it){
      for(list<pair<int, int> >::iterator it2= v[i].begin(); it2 != v[i].end(); ++it2){
        pair<int, int> t(it->first * it2->first, it->second + it2->second);
        temp.push_back(t);
      }
    }
    answer.push_back(temp);                 //store the list into the vector
  }

  //iterate through the new vector and process, print the pairs
  int i = 1;
  for (vector<list<pair<int, int>>>::iterator it = answer.begin(); it != answer.end(); ++it){
    sortPolynomials(*it);
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

      list<pair<int, int> > polys;                          //Store pairs in a LinkedList

      //First remove the newline character for each line
      line.pop_back();
      line.pop_back();
      
      //Call function to store integers into the linkedList
      extractIntegerWords(line, polys);

      //print out pairs in non-canonical form
      myfile <<"Non-Canonical: \t\t\t\t";
      nonCanonical(polys);

      //Add the Polynomial using the function
      //sort them here, call by reference sort
      myfile <<"\nCanonical: \t\t\t\t\t";
      sortPolynomials(polys);
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
