#include <iostream>

using namespace std;

template <class T>
class node{
public:
    T item;
    node <T> *next, *prev;
    node();
    node(T);
};

template <class T>
class mylist{
public:
struct iterator{
    node<T>* pointer;
    iterator& operator++(int){pointer = pointer->next; return (*this);}
    T operator*(){return pointer->item;}
    bool operator!=(const iterator& it){return pointer!=it.pointer;}
};
private:
    int size;
    node <T> *head, *tail;
    iterator iter;
public:
    mylist();
    mylist(const mylist&);
    //mylist &operator = (const mylist&);
    T get(int);
    int getSize();
    bool insert(int, T);
    bool remove(int);
    bool set(T,int);
    //T &operator[](int);
    iterator begin(){iter.pointer = head; return iter;}
    iterator end(){iter.pointer = tail->next; return iter;}
};

void display(mylist<int> l){
   /* int ctr = 0;
    while(ctr < l.getSize()){
        cout<<l.get(ctr)<<" ";
        ctr++;
    }
    cout<<endl;
    */
    if(l.getSize() > 0)
        for(mylist<int>::iterator iter = l.begin(); iter!=l.end(); iter++){
            cout<<*iter<<" ";
        }
    cout<<endl;
}

template <class T>
node<T>::node(){
    next = NULL;
    prev = NULL;
}

template <class T>
node<T>::node(T x){
    item = x;
    next = NULL;
    prev = NULL;
}

template <class T>
mylist<T>::mylist(){
    size = 0;
    head = NULL;
    tail = NULL;
    //iter.pointer = head;
}

template <class T>
mylist<T>::mylist(const mylist<T>&l){
    size = 0;
    head = tail = NULL;
    node <T> *tmp = l.head;
    int ctr = 0;
    while (ctr != l.size){
        insert(ctr, tmp->item);
        tmp = tmp->next;
        ctr++;
    }
}

template <class T>
bool mylist<T>::set(T itm,int pos){
    if(pos < 0 || pos > size){
        return false;
    }
    else{
        node<T> *tmp = head;
        int p = 0;
        while(p < pos){
            tmp = tmp->next;
            p++;
        }
        tmp->item = itm;
    }
    return true;
}
   

template <class T>
bool mylist<T>::insert(int pos, T item){
    if (pos > size || pos < 0){
        return false;
    }
    node<T> *temp = new node<T>(item);
    if(size == 0){
        head = tail = temp;
    }
    else if (pos == 0) {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    else if(pos == size){
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    else{
        int ctr = 0;
        node<T> *tmp = head;
        while (ctr != pos - 1){
            tmp = tmp->next;
            ctr++;
        }
        temp->next = tmp->next;
        tmp->next->prev = temp;
        tmp->next = temp;
        temp->prev = tmp;
    }

    size++;
    return true;
}

template <class T>
bool mylist<T>::remove(int pos) {
    if (pos < 0 || pos >= size) {
        return false;
    }
    else {
        node<T> *tmp= head;
        if (pos == 0) {
            head = tmp->next;
            if(head != NULL){
                head->prev = NULL;
            }
        }

        else if (pos == size-1) {
            tmp = tail;
            tail = tmp->prev;
            tmp->prev = NULL;
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
            node<T> *tmp3 = tmp2->next;
            tmp3->prev = tmp;
            tmp = tmp2;
            tmp->prev = tmp->next = NULL;
        }
        size--;
        delete tmp;
   }
   return true;
}

template <class T>
T mylist<T>::get(int pos){
    if(pos < 0 || pos >= size)
        throw 404;
    else{
         if(pos == size-1){
            return tail->item;
        }
        node<T> *tmp = head;
        int p = 0;
        while(p < pos){
            tmp = tmp->next;
            p++;
        }
        return tmp->item;
    }
}

template <class T>
int mylist<T>::getSize(){
    return size;
}

int main(){
    int cases;
    cin>>cases;
    mylist<int> l;
    while(cases!= 0){
        int type;
        cin>>type;
        int pos, item;
        if(type == 1){
            cin>>pos;
            cin>>item;
            l.insert(pos,item);
            display(l);
        }
        else if(type == 2){
            cin>>pos;
            l.remove(pos);
            display(l);
        }
        else if(type == 3){
            cin>>pos;
            try{
              cout<<l.get(pos)<<endl;
            }
            catch (int err){
                if(err==404)
                    cout<<"POSITION OUT OF BOUNDS\n";
            }
        }else{
            cin>>pos;
            cin>>item;
            l.set(item,pos);
            display(l);
        }
        cases--;
    }
}
