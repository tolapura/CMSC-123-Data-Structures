#include <iostream>

using namespace std;

template <class T>
class node{
public:
    T item;
    node<T> *next;
    node();
    node(T);
};
template <class T>
node<T>::node(){
    next = NULL;
}
template <class T>
node<T>::node(T i){
    item = i;
    next = NULL;
}
template <class T>
class queueList {
private:
    node<T>* _front;
    node<T>* _rear;
    int size;
public:
    queueList();
    void display();
    void enqueue(T);
    bool dequeue();
    T getFront();
    T getLast();
};
template <class T>
queueList<T>::queueList() {
     _front = NULL;
     _rear = NULL;
     size = 0;
 }
template <class T>
void queueList<T>::enqueue(T item){
    node<T>* temp = new node<T>(item);
    if (size == 0) {
        _front = _rear = temp;
    }
    else {
        _rear->next = temp;
        _rear = temp;
    }
    size++;
}
 template <class T>
bool queueList<T>::dequeue(){
    if (size != 0) {
        node<T>* del = new node<T>();
        del = _front;
        _front = del->next;
        del->next = NULL;
        delete del;
        size--;
        return true;
    }
    return false;
}
template <class T>
void queueList<T>::display(){
    node<T>* temp = _front;
    while (temp!= NULL) {
        cout << temp->item << " ";
        temp = temp-> next;
    }
    cout<< endl;
}
template <class T>
T queueList<T>::getFront(){
    if (size == 0) {
        throw 404;
    }
    return _front->item;
}
template <class T>
T queueList<T>::getLast(){
    if (size == 0) {
        throw 404;
    }
    return _rear->item;
}

int main() {
    int cases;
    cin >> cases;
    queueList<int> l;
    while (cases != 0) {
        int type;
        cin >> type;
        if (type == 1) {
            int item;
            cin >> item;
            l.enqueue(item);
            l.display();
        }
        else if (type == 2) {
            l.dequeue();
            l.display();
        }
       
        else if (type == 3) {
            try {
                cout<<l.getFront()<<endl;
            } catch (int err) {
                if (err == 404) {
                    cout << "queue is empty."<<endl;
                }
            }
        }
        else if (type == 4) {
            try {
                cout<<l.getLast()<<endl;
            } catch (int err) {
                if (err == 404) {
                    cout << "queue is empty."<<endl;
                }
            }
        }
        else{
            l.display();
        }
       
        cases--;
    }
}
