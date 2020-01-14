//Assignment 1 - Sabeel Kazi - CS780

#include<iostream>
#include <cstdlib>
#include<cassert>
#include <algorithm>
#include "safeMatrix.cpp"
using namespace std;

typedef int T;              //****** We define the datatype we are using for T here!!!

template <class T>
class VNT{
    public:
    bool full = false;
    int m, n;
    outerSA<T>* s;

    public:
    //creating an empty VNT
    VNT(){
        m = 1;
        n = 1;

        s = new outerSA<T>(1);
        s[0][0] = INT_MAX;
    }

    //overload [] operator
    SA<T>& operator[](int i){
        if(i > m){
            cout<< "index "<<i<<" out of range"<<endl;
            exit(1);
        }
        return (*s)[i];
    }

    VNT(int r, int c){
        m = r;
        n = c;
        s = new outerSA<T>(0, r-1, 0, c-1);

        setMax();
    }

    //function to check if full, will run always after filling an entry in the matrix
    void isFull(){
        full = true;
        for(int i=0; i < m; i++){
            for(int j=0; j < n; j++){
                if(s[i][j] == INT_MAX){
                    full = false;
                    return;
                }
            }
        }
    }

    //used to set all elements to max upon intitializing the VNT Object, in constructor
    void setMax() 
    { 
        for(int i=0; i<m; i++){
            (*s)[i].setMax();
        }
    } 

    //function for sorting row wise and column wise, provided by geeksforgeeks.com
    // function to sort each row of the matrix 
    void sortByRow() 
    { 
        for(int i=0; i<m; i++){
            (*s)[i].sort();
        }
    }
    
    // function to find transpose of the matrix, provided by geeksforgeeks.com
    void transpose() 
    { 
        for (int i = 0; i < m; i++) 
            for (int j = i + 1; j < m; j++)  
    
                // swapping element at index (i, j)  
                // by element at index (j, i) 
                swap((*s)[i][j], (*s)[j][i]);
    } 
    
    // function to sort the matrix row-wise/column/wise, provided by geeksforgeeks.com
    // This is the sort function, it is called automatically in other functions
    void sort(){ 
        // sort rows of mat[][] 
        sortByRow(); 
        // get transpose of mat[][] 
        transpose(); 
        // again sort rows of mat[][] 
        sortByRow(); 
        // again get transpose of mat[][] 
        transpose(); 
    }

    void add(T x){
        //if not full, find first int max, make it x, then sort and return
        if(!full){
            for(int i=0; i<m; i++){
                for(int j=0; j<n; j++){
                    if( (*s)[i][j] == INT_MAX){ 
                        (*s)[i][j] = x;
                        cout << "Adding \t" << x << "\n";
                        sort();
                        return;
                    }
                }
            }
            cout << "VNT Object is full, cannot add element "<< x << "\n";
            full = true;
            return;
        }
        else{
            cout << "VNT Object is full, cannot add element "<< x << "\n";
        }
    }

    T getMin(){
        //if the VNT is full, calling get min
        if(full == true) full = false;
        
        //since the table is always sorted, the smallest element will always be at the start
        T ret = (*s)[0][0];
        (*s)[0][0] = INT_MAX;

        //VNT must be resorted
        sort();

        cout << "\nRemoving min:\t"<< ret << "\n";

        //return the smallest value
        return ret;
    }

    void print(){
        cout << "\nThe VNT is currently: \n";
        (*s).print();
    }
};

//The VNT class is tested here in MAIN
//works best with a square VNT object(dimensions n*n)
int main(){ 
    //instantiate the VNT object
    VNT<T> test(3, 3);

    cout << "The VNT with no elements (defaults to INT_MAX): \n";
    test.print();
    cout << "\n";

    //add elements to it
    test.add(4);
    test.add(6);
    test.add(145);
    test.add(8);
    test.add(718);
    test.add(3);
    test.add(22);
    test.add(65);
    test.add(1);
    //VNT should be full here, next few elements won't add
    test.add(5);
    test.add(23);

    test.print();

    //using getMin
    test.getMin();

    test.print();
}
