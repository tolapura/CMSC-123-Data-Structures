#include <iostream>
#include <fstream>
#include <typeinfo>
#include <stack>
#include <queue>
#include <string>

#define in "maze.in"
#define out "maze.out"

using namespace std;

class squares {
public:
	char type;
    int row;
    int col;
    bool vis;
    squares();
    squares(int row, int col, char type);
};

squares::squares(int row, int col, char type){
	this->row = row;
	this->col = col;
	this->type = type;
	vis = false;
}

squares::squares() {
    vis = false;
}


template <class T>
class agenda{
private:
    T *adt;
    int type;
public:
    agenda();
    inline ~agenda(){delete adt;}
    inline bool isEmpty(){return adt->empty();};
    inline int getSize(){return adt->size();};
    void add(squares);
    bool remove();
    squares peek();
};

template <class T>
agenda<T>::agenda(){
    adt = new T();
    string t1 = typeid(*adt).name();
    string t2 = typeid(stack<squares> ).name();
    string t3 = typeid(queue<squares> ).name();
    if(t1.compare(t2)==0){
        type = 1;
    } else if(t1.compare(t3)==0){
        type = 2;
    }
}

template <class T>
void agenda<T>::add(squares s) {
    adt->push(s);
}

template <class T>
bool agenda<T>::remove() {
    bool flag = false;
    if (!isEmpty()) {
            adt->pop();
        flag = true;
    }
    return flag;
}

template <class T>
squares agenda<T>::peek() {
    return (type == 1) ? ((stack<squares>*)adt)->top() : ((queue<squares>*)adt)->front();
}

class maze {
public:
    squares** sa;
    int r;
    int c;
    squares getOrigin();
    string toString();
    maze(int, int);
    maze(const maze&);
    maze(maze*);
    ~maze();
};

maze::maze(maze* m) {
    r = m->r;
    c = m->c;
    sa = new squares*[r];
    for(int i = 0; i < r; i++){
        sa[i] = new squares[c];
    }
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            this->sa[i][j] = m->sa[i][j];
        }
    }
}

maze::maze(const maze& m) {
    r = m.r;
    c = m.c;
    for(int i = 0; i < m.r; i++){
        for(int j = 0; j < m.c; j++){
            this->sa[i][j] = m.sa[i][j];
        }
    }
}

maze::maze(int row, int col) {
    sa = new squares*[row];
    for(int i = 0; i < row; i++)
        sa[i] = new squares[col];
    r = row;
    c = col;
}

string maze::toString() {
	string result = "";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result += sa[i][j].type;
        }
        result += "\n";
    }
    return result;
}

squares maze::getOrigin() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (sa[i][j].type == 'o') {
                return sa[i][j];
            }
        }
    }
}

maze::~maze() {
    for(int i = 0; i < r; i++) {
        delete[] sa[i];
    }
    delete[] sa;
}

template <class T>
class mazesolver {
private:
    agenda<T> *a;
    maze *m;
    agenda<stack<squares> > *route;
public:
    mazesolver();
    mazesolver(maze*);
    ~mazesolver();
    void solve();
    void writeSolution();
    inline bool left(maze* m, int x, int y){return (m->sa[x][y-1].type!='#')&&(y>0)&&(m->sa[x][y-1].vis==0);};
    inline bool up(maze* m, int x, int y){return (m->sa[x-1][y].type!='#')&&(x>0)&&(m->sa[x-1][y].vis==0);};
    inline bool right(maze* m, int x, int y){return (m->sa[x][y+1].type!='#')&&(y<m->c-1)&&(m->sa[x][y+1].vis==0);};
    inline bool down(maze* m, int x, int y){return (m->sa[x+1][y].type !='#')&&(x<m->r-1)&&(m->sa[x+1][y].vis==0);};
};

template <class T>
mazesolver<T>::mazesolver(maze *m) {
    a = new agenda<T>();
    this->m = m;
}

template <class T>
mazesolver<T>::mazesolver() {
}

template <class T>
mazesolver<T>::~mazesolver() {
    delete a;
    delete route;
}

template <class T>
void mazesolver<T>::solve() {
    maze* temp = new maze(m);
    bool routeExist = false;
    int x = temp->getOrigin().row;
    int y = temp->getOrigin().col;
    this->route = new agenda<stack<squares> >();
    route->add(temp->sa[x][y]);

	while(!route->isEmpty()){
        squares top = route->peek();
        int x = top.row;
        int y = top.col;
        char check = top.type;
        if(check == '*'){
        	routeExist = true;
            break;
        } else {
            temp->sa[x][y].vis = true;
            if(this->left(temp, x, y)) {
                a->add(temp->sa[x][y-1]);
            }
            if(this->up(temp, x, y)) {
                a->add(temp->sa[x-1][y]);
            }
            if(this->right(temp, x, y)) {
                a->add(temp->sa[x][y+1]);
            }
            if(this->down(temp, x, y)) {
                a->add(temp->sa[x+1][y]);
            }

            if(a->isEmpty()) {
                route->remove();
            } else {
                route->add(a->peek());
                while(!a->isEmpty()){
                    a->remove();
                }
            }
        }
    }
}
template <class T>
void mazesolver<T>::writeSolution(){
    ofstream outputFile(out,ios_base::app);
    maze* temp = new maze(m);
    string output;
	if(!route->isEmpty()) {
		route->remove();
    	while(!route->isEmpty()){
	        if(route->getSize() == 1){
	            break;
	        }
	        squares draw = route->peek();
	        draw.type = 'x';
	        temp->sa[draw.row][draw.col] = draw;
	        route->remove();
    	}
	}
	output = temp->toString();
    outputFile << output;
    outputFile << "\n";
}


int main(){
    ifstream file(in);
    int cases;
    int r;
    int c;
    char type;
    string output = "";
	if(file.is_open()){
		int cases;
		file >> cases;
		for (int i = 0; i < cases; i++) {
            file>>r;
            file>>c;
            maze *m = new maze(r, c);
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    file >> type;
                    squares temp(i, j, type);
                    m->sa[i][j] = temp;
                }
            }
            mazesolver<queue<squares> > ms(m);
            ms.solve();
            ms.writeSolution();
            mazesolver<stack<squares> > ss(m);
            ss.solve();
            ss.writeSolution();
		}
		file.close();
	}
	return 0;
}
