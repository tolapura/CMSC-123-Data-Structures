#include <iostream>

using namespace std;

template <class T>
class node {
public:
    T item;
    node* left;
    node* right;
    node* parent;
    int balance;
    int height;
    node();
    node(T);
};
template <class T>
node<T>::node() {
    left = right = parent = NULL;
    balance = height = 0;
}

template <class T>
node<T>::node(T item) {
    left = right = parent = NULL;
    balance = height = 0;
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
    void updateHeight(node<int>*);
    void leftRotate(node<int>*);
    void rightRotate(node<int>*);
    void leftRightRotate(node<int>*);
    void rightLeftRotate(node<int>*);
};

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
    updateHeight(n->parent);
    fixBalance(n);
}

template <class T>
void bst<T>::updateHeight(node<int> *n) {
    int heightLeft = -1;
    int heightRight = -1;
    while (n != NULL) {
        if (n->left != NULL) {
            heightLeft = n->left->height;
        }
        if (n->right != NULL) {
            heightRight = n->right->height;
        }
        n->height = heightLeft < heightRight ? heightRight+1 : heightLeft+1;
        if(abs(heightLeft - heightRight) <= 1){
            n->balance = 0;
        } else {
            n->balance = heightLeft > heightRight ? -1 : 1 ;
        }
        n = n->parent;
    }
}

template <class T>
void bst<T>::fixBalance(node<int>* n) {
    while(n->parent != NULL){




    }

    if(abs(heightLeft - heightRight) <= 1){
            balance = 0;
        } else {
            balance = heightLeft > heightRight ? -1 : 1 ;
            if(balance == -1){
                rightRotate(n);
            }
            else{
                leftRotate(n);
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
        int res = bst.search(nums);
        (res < 0) ? cout<< res*-1 << " !FOUND"<<endl :cout<< res << " FOUND" << endl;
        cases--;
    }
    return 0;
}

