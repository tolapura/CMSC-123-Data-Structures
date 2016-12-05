#include <iostream>

using namespace std;

template <class T>
class node {
public:
    T item;
    node* left;
    node* right;
    node* parent;
    node();
    node(T);
};
template <class T>
node<T>::node() {
    left = right = parent = NULL;
}

template <class T>
node<T>::node(T item) {
    left = right = parent = NULL;
    this->item = item;
}

template <class T>
class bst {
private:
    node<T>* bstnode;
public:
    bst();
    ~bst();
    void insert(int);
    int search(int);
    node<int>* get(int);
    int remove(int);
    int min(node<int>*);
    void print(node<int>*);
    void print();
};

template <class T>
void bst<T>::print(node<int>* root){
    if(root != NULL){
        print(root->left);
        cout<<root->item<<" ";
        print(root->right);
        
    }
}
template <class T>
void bst<T>::print(){
    print(bstnode);
}

template <class T>
bst<T>::bst() {
    bstnode = NULL;
}

template <class T>
bst<T>::~bst() {
    while(bstnode != NULL){
        remove(bstnode->item);
    }
}

template <class T>
int bst<T>::remove(int item) {
    node<int>* temp = get(item);
    int countSearch = search(item);
    if(temp != NULL){
        if (temp->left == NULL && temp->right == NULL) {
            if (temp->parent != NULL) {
                node<int>* parent = temp->parent;
                if(parent->left == temp) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
                temp->parent = NULL;
                delete temp;
            } else {
                delete temp;
                bstnode = NULL;
            }
        }
        else if (temp->left == NULL) {
            if(temp->parent != NULL){
                node<int>* parent = temp->parent;
                node<int>* rightChild = temp->right;
                if (parent->right == temp) {
                    parent->right = rightChild;
                } else {
                    parent->left = rightChild;
                }
                rightChild->parent = parent;
                temp->parent = temp->right = NULL;
                delete temp;
            } else{
                bstnode = temp->right;
                bstnode->parent = NULL;
                temp->right = NULL;
                delete temp;
            }
        }
        else if (temp->right == NULL) {
             if(temp->parent != NULL){
                node<int>* parent = temp->parent;
                node<int>* leftChild = temp->left;
                if (parent->right == temp) {
                    parent->right = leftChild;
                } else {
                    parent->left = leftChild;
                }
                leftChild->parent = parent;
                temp->parent = temp->left = NULL;
                delete temp;
            }else{ 
                bstnode = temp->left;
                bstnode->parent = NULL;
                temp->left = NULL;
                delete temp;
             }
        } else{
     
                int minimum = min(temp->right);
                remove(minimum);
                temp->item = minimum;
        }
    }
    return countSearch;
}

template <class T>
node<int>* bst<T>::get(int item) {
    node<int>* temp = bstnode;
        while(temp != NULL){
            if(temp->item == item){
                return temp;
            }
            if(item < temp->item){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
     return NULL;
}

template <class T>
int bst<T>::min(node<int>* n){
    while(n->left != NULL) {
        n = n->left;    
    }
    return n->item;
}

template <class T>
void bst<T>::insert(int item){
    node<int>* before = NULL;
    node<int>* n = new node<int>(item);
    if(bstnode == NULL) {
        bstnode = n;
    } else{
        node<int>* temp = bstnode;
        while(temp != NULL){
            if(item < temp->item){
                before = temp;
                temp = temp->left;
            }
            else{
                before = temp;
                temp = temp->right;
            }
        }
        if(before->item > item){
            before->left = n;
            n->parent = before;
        }
        else{
            before->right = n;
            n->parent = before;
        }
    }
}

template <class T>
int bst<T>::search(int item){
    int count = 0;
    node<int>* temp = bstnode;
        while(temp != NULL){
            if(temp->item == item){
                return count+1;
            }
            if(item < temp->item){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
            count++;
        }
    return (count)* -1;
}


int main() {
    int cases;
    cin >> cases;
    int num;
    int toSearch;
    while (cases != 0){
        bst<int> bst;
        cin >> num;
        int nums;
        while (num != 0){
            cin >> nums;
            bst.insert(nums);
            num--;
        }
        cin >> nums;
        int res = bst.remove(nums);
        (res < 0) ? cout<< res*-1 << " !FOUND"<<endl :cout<< res << " DELETED" << endl;
        cases--;
    }
    return 0;
}

