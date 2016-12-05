#include <iostream>
#include <cmath>
#include <limits>
#include <list>
using namespace std;
class hashTable{
    public:
        list<string> table[1 << 10];
        int max;
        int type;
        hashTable(int);
        ~hashTable();
        int hashIndex(string);
        int hashCode1(string);
        int hashCode2(string);
        int insert(string);
        int search(string);
};
hashTable::~hashTable(){
}

hashTable::hashTable(int type){
    this->type = type;
    max = 1 << 10;
}

int hashTable::hashIndex(string s){
    unsigned int x;
    if(type == 1){
        x = hashCode1(s);
    }
    else{
        x = hashCode2(s);
    }
   int w = 31;
   int d = 10;
   int z = 60147;
   int themod = 1 << w;
   return ((z*x) % themod) >> (w-d);
}

int hashTable::insert(string s){
    int index = hashIndex(s);
    table[index].push_back(s);
    return table[index].size();
}

int hashTable::hashCode1(string s) {
    int h = 0, i = 0;
    for(;i < s.size(); i++) {
        h = 31 * h + s[i];
    }
    return h;
}

int hashTable::hashCode2(string s) {
    unsigned int h = 0, high, i = 0;
    while (s[i] != '\0') {
        h = (h << 4) + s[i++];
        if (high = h & 0xF0000000) {
            h ^= high >> 24;
        }
        h&= ~high;
    }
    return h;
}

int hashTable::search(string s){
    int index = hashIndex(s);
    int ctr = 1;
    list<string>::iterator it;
    for(it = table[index].begin(); it != table[index].end(); ++it){
        if((*it).compare(s) == 0){
            break;
        }
        ctr++;
    }
    return ctr;
}


int main(){
    int cases;
    cin >> cases;
    while(cases != 0){
        hashTable h1(1);
        hashTable h2(2);
        int n;
        string s;
        cin >> n;
        while(n != 0){
            cin >> s;
            cout << h1.insert(s)<< " ";
            h2.insert(s);
            n--;
        }
        cin >> s;
        cout << h1.search(s)<<" ";
        cout << h2.search(s)<<" "<<endl;
        cases--;
    }
}

