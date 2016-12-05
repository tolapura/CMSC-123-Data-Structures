#include <iostream>
#include <cmath>
#include <limits>
using namespace std;
class hashTable{
    public:
        int* array;
        int max;
        int size;
        hashTable();
        ~hashTable();
        int hashIndex(int);
        int insert(int);
        int search(int);
};
hashTable::~hashTable(){
    delete[] array;
}

hashTable::hashTable(){
    max = pow(2,9);
    size = 0;
    array = new int[max];
    int i;
    for(i=0; i < max ; i++){
        array[i] = numeric_limits<double>::infinity();
    }
}

int hashTable::hashIndex(int x){
   int w = 16;
   int d = 9;
   int z = 60147;
   int themod = pow(2,w);
   return ((z*x) % themod) >> (w-d);
}

int hashTable::insert(int n){
    int ctr = 0;
    int index = hashIndex(n);
    if(size != max){
        while(array[index] != (int)numeric_limits<double>::infinity()){
            index++;
            ctr++;
        }
        array[index] = n;
    }
    return ctr;
}

int hashTable::search(int n){
    int index = hashIndex(n);
    int ctr = 0;
    if(size != 0){
        if(array[index] == (int)numeric_limits<double>::infinity()){
            return ctr;
        }
        else{
            while(array[index] != n || array[index] != (int)numeric_limits<double>::infinity()){
                index++;
                ctr++;
            }
        }
    }
    return ctr;
}


int main(){
    int cases;
    cin >> cases;
    while(cases != 0){
        hashTable h;
        int n;
        int i;
        cin >> n;
        while(n != 0){
            cin >> i;
            cout << h.insert(i) << " ";
            n--;
        }
        cin >> i;
        cout << endl;
        cout << h.search(i)<<endl;
        cases--;
    }
}
