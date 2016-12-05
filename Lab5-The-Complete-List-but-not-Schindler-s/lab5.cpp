#include <iostream>
using namespace std;
template <class T>
class node {
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
node<T>::node(T item){
    this->item = item;
    next = NULL;
}


template <class T>
class list{
private:
    int size;
    node<T> *head, *tail;
public:
    list();
    ~list();
    list(const list&);
    list& operator=(const list&);
    bool insert(T,int);
    T get(int);
    int getSize();
    bool set(T, int);
    bool remove(int);
    bool isEmpty();

};
template <class T>
list<T>::list(){
    size = 0;
    head = NULL;
    tail = NULL;
}
template <class T>
list<T>::~list() {
    while(!isEmpty()) {
        remove(0);
    }
}
template <class T>
bool list<T>::isEmpty() {
    return size == 0;
}

template <class T>
bool list<T>::remove(int pos) {
    if (pos < 0 || pos >= size) {
        return false;
    }
    node<T> *tmp = head;
        if (pos == 0) {
            head = tmp->next;
        }
        else if (pos == size-1) {
            int p = 0;
            while (p < pos-1) {
                tmp = tmp->next;
                p++;
            }
            tail = tmp;
            tmp = tmp->next;
            tail->next = NULL;
        }

        else {
            int p = 0;
            while (p < pos-1) {
                tmp = tmp->next;
                p++;
            }
            node<T> *tmp2 = tmp->next;
            tmp->next = tmp2->next;
            tmp = tmp2;
        }
        size--;
        delete tmp;
        return true;
}

template <class T>
bool list<T>:: set(T item, int pos){
    if (pos < 0 || pos > size) {
        return false;
    }
    else {
        node<T> *tmp = head;
        int p = 0;
        while (p < pos){
            tmp = tmp -> next;
            p++;
        }
        tmp->item = item;
    }
    return true;
}


template <class T>
list<T>::list(const list<T>& l){
    size = 0;
    head = tail = NULL;
    node <T> *tmp = l.head;
    int ctr = 0;
    while (ctr != l.size){
        insert(tmp->item, ctr);
        tmp = tmp->next;
        ctr++;
    }
}

template <class T>
list<T>& list<T>::operator=(const list<T>& l){
    node <T> *tmp = l.head;
    int ctr = 0;
    while (ctr != l.size){
        insert(tmp->item, ctr);
        tmp = tmp->next;
        ctr++;
    }
}

template <class T>
T list<T>::get(int pos){
    if (pos < 0 || pos > size-1) {
        throw -1;
    }

    int ctr = 0;
    node<T> *tmp = head;
    while(ctr!=pos){
        tmp = tmp->next;
        ctr++;
    }
    return tmp->item;
}

template <class T>
bool list<T>::insert(T item, int pos){
    node<T> *temp = new node<T>(item);
    if (pos > size || pos < 0){
        return false;
    }
    else if(size == 0){
        head = tail = temp;
    }

    else if (pos == 0) {
        temp->next = head;
        head = temp;
    }
    else if(pos == size){
        tail->next = temp;
        tail = temp;
    }
    else{
        int ctr = 0;
        node<T> *tmp = head;
        while (ctr != pos - 1 ){
            tmp = tmp->next;
            ctr++;
        }
        temp->next = tmp->next;
        tmp->next = temp;
    }
    size++;
    return true;
}


template <class T>
int list<T>::getSize(){
    return size;
}

void display(list<int> l){
    int ctr = 0;
    while(ctr < l.getSize()){
      cout<<l.get(ctr)<<" ";
      ctr++;
    }
    cout<<endl;
}

int main(){
    int cases;
    cin>>cases;
    list<int> l;
    int pos,item,type;
    while(cases!=0){
        cin>>type;
        if(type == 1){
            cin>>pos;
            cin>>item;
            l.insert(item,pos);
            display(l);
        }
        else if(type == 2){
            cin>>pos;
            l.remove(pos);
            display(l);
        }
        else {
            cin>>pos;
            try {
                cout<<l.get(pos)<<endl;
             }
            catch(int err) {
                cout<<"POSITION OUT OF BOUNDS\n";
            }
        }
        cases--;
    };

    return 0;
}
