#include <iostream>
#define INCREASE 3
using namespace std;

class vector{
    private:
        int size,max;
        int *items;
        void gridExpand();
    public:
        vector();
        bool insert(int,int);
        bool remove(int);
        int& operator[](int);
        int at(int);
        int getSize();
        friend ostream& operator << (ostream&,vector);
};

void vector::gridExpand(){
    int* temp = new int[max];
    for(int i = 0; i < size; i++){
        temp[i] = items[i];
    }
    items = new int[max + INCREASE];
    for(int i = 0; i < size; i++){
        items[i] = temp[i];
    }
    max = max + INCREASE;
    delete[] temp;
}

vector::vector(){
    size = 0;
    max = 3;
    items = new int[max];
}

bool vector::insert(int num, int pos){
    if(pos < 0 || pos > size){
        return false;
    }
    if(size == max){
        gridExpand();
    }
    items[pos] = num;
    size++;
    return true;
}

bool vector::remove(int pos){
    if(pos < 0 || pos > size){
        return false;
    }
    for(int i = pos; i < size-1; i++){
        items[i] = items[i+1];
    }
    size--;
    return true;
}

int& vector::operator[](int i){
    return items[i];
}

int vector::at(int i){
    return items[i];
}

int vector::getSize(){
    return size;
}

ostream& operator << (ostream& out,vector a){
    for(int i = 0; i < a.size; i++){
        out << a.items[i] << " ";
    }
    return out;
}


bool checkSort(vector a){
    for(int i = 0; i < a.getSize()-1; i++){
        if(a[i] > a[i+1]){
            return false;
        }
    }
    if(a[0] == a[a.getSize()-1]){
        return false;
    }
    return true;
}

void removeDuplicate(vector& a){
    for(int i = 0; i<a.getSize()-1; i++){
        for(int j = i+1; j<a.getSize();){
            if(a[i] == a[j]){
                a.remove(j);
            }
            else{
                j++;
            }
        }
    }
}

int main() {
    int cases;
    cin >> cases;
    while(cases > 0){
        vector a;
        int ctr=0;
        while(ctr!=10){
            int num;
            cin>>num;
            a.insert(num,a.getSize());
            ctr++;
        }
        checkSort(a)? cout<<"YES": cout<< "NO";
        cout<<endl;
        removeDuplicate(a);
        cout<<a<<endl;
        cases--;
    }
    return 0;
}
