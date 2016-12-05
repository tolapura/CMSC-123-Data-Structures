#include <iostream>
#define MAX 20

using namespace std;

class array{
    private:
	  int items[MAX];
	  int size;
    public:
    array();
    array(int);
    int getSize();
    int operator[](int);
    bool insert(int, int);
    bool remove(int);
};

    array::array(){
        size = 0;
    }

    array::array(int n){
        size = 0;
	   for(int i=0; i<size; i++)
		 items[i] = n;
    }

    int array::getSize(){
        return size;
    }
    
    int array::operator[](int index){
        return items[index];
    }
    
    bool array::insert(int num, int pos){
        if(pos < 0 || pos > size){
            return false;
        }
        items[pos] = num;
        size++;
        return true;
    }
    bool array::remove(int pos){
        if(pos < 0 || pos > size){
            return false;
        }
        for(int i = pos; i < MAX-1; i++){
            items[i] = items[i+1];
        }
        size--;
        return true;
    }
bool checkSort(array a){
    if(a.getSize() == 1){
        return false;
    }
    for(int i = 0; i < a.getSize()-1; i++){
        if(a[i+1] < a[i]){
            return false;
        }
    }
    return true;
}

array removeDuplicate(array a){
    for(int i = 0; i<a.getSize()-1; i++){
        for(int j = i+1; j<a.getSize(); j++){
            if(a[i] == a[j]){
                a.remove(j);
                j--;
            }
        }
    }
    return a;
}

void display(array a){
    for(int i=0; i<a.getSize(); i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
int main() {
    int cases;
    cin >> cases;
    while(cases > 0){
        array a;
        int ctr=0;
        while(ctr!=10){
            int num;
            cin>>num;
            a.insert(num,ctr);
            ctr++;
        }
        a = removeDuplicate(a);
        checkSort(a)? cout<<"YES": cout<< "NO";
        cout<<endl;
        display(a);
        cases--;
    }
    return 0;
}
