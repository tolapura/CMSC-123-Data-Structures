#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stack>
#include <string>

using namespace std;

template <class T>
class node {
public:
    T item;
    node* left;
    node* right;
    node();
    node(T);
};
template <class T>
node<T>::node() {
    left = right = NULL;
}

template <class T>
node<T>::node(T item) {
    left = right = NULL;
    this->item = item;
}

node<string>* disect(string, node<string>*);
void postorder(node<string>* n, stack<string>&);
void solve(stack<string>);
bool isOperand(string);
string toString(float);
string compute(string,string,string);

int main() {
    int cases;
    cin >> cases;
    string line;
    while (cases != 0) {
        cin >> line;
        node<string>* root = NULL;
        stack<string> s;
        root = disect(line, root);
        postorder(root,s);
        solve(s);
        }
    return 0;
}

void solve(stack<string> storage){
    stack<string> temp1;
    while(storage.size() != 0){
        temp1.push(storage.top());
        storage.pop();
    }

    stack<string> temp2;
    while(temp1.size() != 0){
        string s = temp1.top();
        temp1.pop();
        if(isOperand(s)){
            string child1 = temp2.top();
            temp2.pop();
            string child2 = temp2.top();
            temp2.pop();
            string ans = compute(child1,child2,s);
            node<string>* tmp = new node<string>(ans);
            temp2.push(tmp->item);
        }
        else{
            node<string>* tmp = new node<string>(s);
            temp2.push(tmp->item);
        }
    }
    cout<<temp2.top()<<endl;
}
string compute(string s1, string s2, string operation){
    float left = atof(s1.c_str());
    float right = atof(s2.c_str());
    string str = "";
    if(operation.compare("+") == 0){
        str = toString(right+left);
    } else if (operation.compare("-") == 0){
        str = toString(right-left);
    } else if (operation.compare("*") == 0){
        str = toString(right*left);
    } else if (operation.compare("/") == 0){
        str = toString(right/left);
    } else {
        str = toString(pow(left,right));
    }
    return str;
}

string toString(float a) {
    ostringstream strs;
    strs << a;
    string str = strs.str();
    return str;
}


bool isOperand(string s){
    string operators = "-+/*^";
    int pos = operators.find(s);
    return pos != string::npos ? true : false;
}
void postorder(node<string>* n, stack<string>& storage){
    if(n != NULL){
        postorder(n->left,storage);
        postorder(n->right,storage);
        storage.push(n->item);
    }
}

node<string>* disect(string line,node<string>* leaf){
    string operators = "-+/*^";
    int pos;
    int i;
    for(i = 0; i < operators.length(); i++){
        pos = line.find(operators[i]);
        if(pos != string::npos){
            break;
        }
    }
    if(i == operators.length()){
        leaf = new node<string>(line);
    }
    else{
        string operand = "";
        operand += line[pos];
        leaf = new node<string>(operand);
        leaf->left =  disect(line.substr(0,pos), leaf->left);
        leaf->right = disect(line.substr(pos+1), leaf->right);
    }
    return leaf;
}
