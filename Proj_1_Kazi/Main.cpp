//Assignemnt 1 - Sabeel Kazi - CS780
#include<iostream>
#include <cstdlib>
#include<cassert>
#include <algorithm>
using namespace std;

//we define typedef, so we can use it for the overriding the ostream operator
typedef int T;              //****** We define the datatype we are using for T here!!!

template <class T>
class SA{
    private:
        int low, high;
        T* p;

    public:
    // default constructor
    // allows for writing things like SA a;

    SA(){
        low=0; 
        high=-1;
        p=NULL;
    }

    // 2 parameter constructor lets us write
    // SA x(10,20);
    SA(int l, int h){
        if((h-l+1)<=0){
            cout<< "constructor error in bounds definition"<<endl;
            exit(1);
        }
        low = l;
        high = h;
        p = new T[h-l+1];
    }

    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9
    SA(int i){
        low=0; high=i-1;
        p=new T[i];
    }
    // copy constructor for pass by value and
    // initialization

    SA(const SA & s){
        int size=s.high-s.low+1;
        p=new T[size];
        for(int i=0; i<size; i++)
        p[i]=s.p[i];
        low=s.low;
        high=s.high;
    }
    // destructor

    ~SA(){
        delete [] p;
    }
    //overloaded [] lets us write
    //SA x(10,20); x[15]= 100;

    int& operator[](int i){
        if(i<low || i>high){
            cout<< "index "<<i<<" out of range"<<endl;
            exit(1);
        }
        return p[i-low];
    }


    // overloaded assignment lets us assign
    // one SA to another

    SA & operator=(const SA & s){
        if(this==&s) return *this;

        delete [] p;
        int size=s.high-s.low+1;
        p=new T[size];

        for(int i=0; i<size; i++) p[i]=s.p[i];

        low=s.low;
        high=s.high;
        return *this;
    }

    void selectionSort(int a[], int n) {
        int i, j, min, temp;
        for (i = 0; i < n - 1; i++) {
            min = i;
            for (j = i + 1; j < n; j++)
                if (a[j] < a[min])
                    min = j;
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }

    void sort(){
        selectionSort(p, high-low+1);
    }

    // overloads << so we can directly print SAs
    friend ostream& operator<<(ostream& os, SA<T> s);
};
ostream& operator<<(ostream& os, SA<T> s){
    int size=s.high-s.low+1;
    for(int i=0; i<size; i++) cout<<s.p[i]<< " ";
    cout << endl;
    return os;
};

//My Code begins here
//*******************************************************************************
template <class T>
class outerSA{
    private:
        int left, right, top, bottom;
        int heightSize;
        int rowSize;
        SA<T>* p;
    
    public: 
    outerSA(){
        bottom = 0;
        top = -1;
        left = 0;
        right = -1;
        p = NULL;
    }

    outerSA(int b, int t, int l, int r){
        //if out of bounds, spit error and exit
        if((r-l+1) <= 0 || (t-b+1) <= 0){
            cout<< "constructor error in bounds definition"<<endl;
            exit(1);
        }
        //or create an array of safe arrays
        bottom = b;
        top = t;
        left = l;
        right = r;

        heightSize = top - bottom + 1;
        rowSize = right - left + 1;

        p = new SA<T>[heightSize];
        for(int i=0; i < heightSize; i++){
            SA<T> n(l, r);
            p[i] = n;
        }
    }

    outerSA(int i){
        bottom = 0; 
        top = i-1;
        left = 0;
        right = i-1;

        heightSize = i;
        rowSize = i;

        p = new SA<T>[heightSize];
        for(int i=0; i < heightSize; i++){
            SA<T> n(rowSize);
            p[i] = n;
        }
    }

    // copy constructor for pass by value and initialization
    outerSA(const outerSA& s){
        //get sizes of the passed object to be copied
        rowSize = s.rowSize;
        heightSize = s.heightSize;

        //create the new 2d array object it will point to
        p = new SA<T>[heightSize];

        for(int i=0; i < heightSize; i++){
            SA<T> n(rowSize);
            p[i] = n;
        }

        //set sizes of this safeArray object
        left = s.left;
        right = s.right;
        top = s.top;
        bottom = s.bottom;
    }

    ~outerSA(){
        delete [] p;
    } 

    // overloaded assignment lets us assign
    // one SA to another 
    SA<T>& operator[](int i){
        if(i<bottom || i>top){
            cout<< "index "<<i<<" out of range"<<endl;
            exit(1);
        }
        return p[i-bottom];
    }

    outerSA<T>& operator=(const outerSA<T> & s){
        //if its equals itself, return itself
        if(this==&s)return *this;

        rowSize = s.rowSize;
        heightSize = s.heightSize;

        delete[] p;

        //create the new 2d array object it will point to
        p = new SA<T>[heightSize];

        for(int i=0; i < heightSize; i++){
            SA<T> n = s.p[i];
            p[i] = n;
        }

        //set sizes of this safeArray object
        left = s.left;
        right = s.right;
        top = s.top;
        bottom = s.bottom;
    
        return *this;
    }

    void sort(){
        for(int i=0; i < heightSize; i++){
            p[i].sort();
        }
    }

    // overloads << so we can directly print SAs
    friend ostream& operator<<(ostream& os, outerSA<T> s); 
};

ostream& operator<<(ostream& os, outerSA<T> s){
    for(int i=0; i < s.heightSize; i++){
       cout << s.p[i];
    }
    return os; 
}

int main(){ 

    //make a 2D-array of 1, 2 and assogn values      
    cout << "Testing assignment and printing of individual elements: \n";        
    outerSA<T> test(1, 2, 1, 3);
    test[1][1] = 62;
    test[1][2] = 23;
    test[1][3] = 9872;
    test[2][1] = 45;
    test[2][2] = 65;
    test[2][3] = 3879;
    cout << test[1][1] << endl;

    cout << "Sort the elements of the array then print: \n";
    test.sort();
    cout << test[1];
    cout << test[2];

    //test the assignment operator, and make a copy of test in test2
    cout << "Creating new 2D array and assigning it the previous one: \n";       
    outerSA<T> test2(4);
    test2 = test;
    cout << test2[2][3] << endl;

    cout << "Printing individual lines of copied array: \n";
    //check that printing works of the copied 2d array
    //ostream operator works for single arrays
    cout << test2[1];
    cout << test2[2];

    //having trouble getting the ostream operator to work for 2D array
    cout << "Printing the whole Array (**ostream not printing whole 2D array properly): \n";
    cout << test;

    //could not find proper matrix multiplication class for further testing
    return 0;
} 