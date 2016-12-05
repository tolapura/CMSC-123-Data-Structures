#include <iostream>

using namespace std;

template <class T>
class Heap {
private:
    int size;
    int max;
    T *array;
public:
    ~Heap();
    Heap(int);
    void insert(T);
    void fix();
    void print();
};
template <class T>
Heap<T>::~Heap(){
    delete[] array;
}
template <class T>
Heap<T>::Heap(int max) {
    array = new int[max+1];
    this->max = max;
    size = 0;
}
template <class T>
void Heap<T>::print() {
    int index = 1;
    while(index <= size){
        cout << array[index] << " ";
        index++;
    }
    cout << endl;
}
template <class T>
void Heap<T>::insert(T item){
    array[++size] = item;
    fix();
}
template <class T>
void Heap<T>::fix(){
    int index = size;  
    if(index != 1){
        while(array[index/2] > array[index]){
            int temp = array[index];
            array[index] = array[index/2];
            array[index/2] = temp;
            index = index/2;
        }
    }
}
int main() {
    int cases;
    cin >> cases;
    while (cases != 0) {
        int num;
        cin >> num;
        Heap<int> heap(num);
        while (num != 0) {
            int item;
            cin >> item;
            heap.insert(item);
            heap.print();
            num--;
        }
        cases--;
    }
}
