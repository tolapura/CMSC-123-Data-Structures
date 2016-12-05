#include <iostream>
#define INCREASE 3
using namespace std;

template <class T>
    
class vector{
    private:
        int size,max;
        T *items;
        void gridExpand();
    public:
        vector();
        vector(const vector<T>&);
        ~vector();
        bool insert(T,int);
        bool remove(int);
        T& operator[](int);
        T at(int);
        int getSize();
};

template <class T>
vector<T>::vector(const vector<T>& v){
	size = v.size;
	max = v.max;
	items = new T[max];

	copy(v.items,v.items+size,items);
}
template <class T>
vector<T>::~vector(){
	delete[] items;
}


template <class T>
void vector<T>::gridExpand(){
    T* temp = new T[max];
    for(int i = 0; i < size; i++){
        temp[i] = items[i];
    }
    items = new T[max + INCREASE];
    for(int i = 0; i < size; i++){
        items[i] = temp[i];
    }
    max = max + INCREASE;
    delete[] temp;
}

template <class T>
vector<T>::vector(){
    size = 0;
    max = 3;
    items = new T[max];
}

template <class T>
bool vector<T>::insert(T num, int pos){
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

template <class T>
bool vector<T>::remove(int pos){
    if(pos < 0 || pos > size){
        return false;
    }
    for(int i = pos; i < size-1; i++){
        items[i] = items[i+1];
    }
    size--;
    return true;
}

template <class T>
T& vector<T>::operator[](int i){
    return items[i];
}

template <class T>
T vector<T>::at(int i){
    return items[i];
}

template <class T>
int vector<T>::getSize(){
    return size;
}
template <class T>
ostream& operator << (ostream& out,vector <T> a){
    for(int i = 0; i < a.getSize(); i++){
        out << a.at(i) << " ";
    }
    return out;
}

bool checkSort(vector<int> a){
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

bool checkSortString(vector<string> a) {
     for(int i = 0; i < a.getSize()-1; i++){
        if((a[i].compare(a[i+1])) > 0){
            return false;
        }
    }
    if(a[0].compare(a[a.getSize()-1]) == 0){
        return false;
    }
    return true;

}

void removeDuplicate(vector<int>& a){
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

void removeDuplicateString(vector<string>& a){
    for(int i = 0; i<a.getSize()-1; i++){
        for(int j = i+1; j<a.getSize();){
            if((a[i].compare(a[j]) == 0)){
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
        int type;
        cin>>type;
        if (type == 1){ 
            vector<int> a;
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
        } else {
            vector<string> a;
            int ctr=0;
            while(ctr!=10){
                string str;
                cin>>str;
                a.insert(str,a.getSize());
                ctr++;
            }
            checkSortString(a)? cout<<"YES": cout<< "NO";
            cout<<endl;
            removeDuplicateString(a);
            cout<<a<<endl;
        }

        cases--;
    }
    return 0;
}
