#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Coords{
private:
    int x{};
    int y{};

public:
    Coords()= default;
    Coords(int x, int y) : x(x), y(y) {}

    friend ostream &operator<<(ostream &os, const Coords &coords) ;

    friend istream &operator>>(istream &is, Coords &coords);

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);
};

ostream &operator<<(ostream &os, const Coords &coords) {
    os << "x: " << coords.x <<"\n"<< " y: " << coords.y;
    return os;
}

istream &operator>>(istream &is, Coords &coords) {
//    cout<<"x: ";
    is>>coords.x;
//    cin.get();
//    cout<<"y: ";
    is>>coords.y;
//    cin.get();
}

int Coords::getX() const {
    return x;
}

int Coords::getY() const {
    return y;
}

void Coords::setX(int x) {
    Coords::x = x;
}

void Coords::setY(int y) {
    Coords::y = y;
}


class Queue{
private:
    int queue_len;
    vector<Coords> coordonate;

public:
    Queue() = default;

    Queue(int queueLen, const vector<Coords> &coordonate);

    friend ostream &operator<<(ostream &os, const Queue &queue);
    friend istream &operator>>(istream &is, Queue &queue);

    int getQueueLen() const;

    const vector<Coords> &getCoordonate() const;

    void clear();

    bool isEmpty() const;

    friend Queue operator+=(Queue &queue, const Coords &newCoordonate);
    friend Queue operator--(Queue &queue);

    Coords operator[](int i){
        if(i<this->coordonate.size()) {
            return this->coordonate[i];
        }else{
            return {-1,1};
        }
    }

};

Queue operator+=(Queue &queue, const Coords &newCoordonate){
    queue.coordonate.push_back(newCoordonate);
    queue.queue_len++;

    return queue;
}

Queue operator--(Queue &queue){
    if(queue.isEmpty()){
        return queue;
    }else{
        vector<Coords> v;
        for (int i = 1; i < queue.coordonate.size(); ++i) {
            v.push_back(queue.coordonate[i]);
        }
        queue.coordonate = v;
//        queue.coordonate.erase(queue.coordonate.begin());
        queue.queue_len--;
        return queue;
    }

}

void Queue:: clear(){
    queue_len=0;
    coordonate.clear();

}

bool Queue:: isEmpty() const{
    if(queue_len==0){
        return true;
    }else{
        return false;
    }
}

ostream &operator<<(ostream &os, const Queue &queue) {
    for(auto i : queue.coordonate){
        os<<i<<"\n";
    }
}

istream &operator>>(istream &is, Queue &queue){
    Coords point;
    is>>queue.queue_len;
    for(int i=0;i<queue.queue_len;i++){
        is>>point;
        queue.coordonate.push_back(point);
    }
}

const vector<Coords> &Queue::getCoordonate() const {
    return coordonate;
}

Queue::Queue(int queueLen, const vector<Coords> &coordonate) : queue_len(queueLen), coordonate(coordonate) {}

int Queue::getQueueLen() const {
    return queue_len;
}

class Maze{
private:
    int n{};
    vector<vector<int>> matrix;
    Coords start;
    Coords end;
    Queue queue;

public:
    Maze() = default;

    Maze(int n, const vector<vector<int>> &matrix, const Coords &start, const Coords &anEnd, const Queue &queue);

    friend ostream &operator<<(ostream &os, const Maze &maze);

    friend istream &operator>>(istream &is, Maze &maze);

    int getN() const;

    const vector<vector<int>> &getMatrix() const;

    const Coords &getStart() const;

    const Coords &getAnEnd() const;

    const Queue &getQueue() const;

    void fill();

};


istream &operator>>(istream &is, Maze &maze){
    is>>maze.n;
    is>>maze.start;
    is>>maze.end;
    is>>maze.queue;
    vector<Coords> tempCoords=maze.queue.getCoordonate();
    maze.matrix.resize(maze.n);
    for(int i=0;i<maze.n;i++)
        maze.matrix[i].resize(maze.n);

    for(int i=0;i<maze.n;i++){
        for(int j=0;j<maze.n;j++){
            maze.matrix[i][j]=1;
        }
    }
    for(int i=0;i<maze.queue.getQueueLen();i++){
        maze.matrix[tempCoords[i].getY()][tempCoords[i].getX()]=0;
    }



}

ostream &operator<<(ostream &os, const Maze &maze){
    for(int i=0;i<maze.n;i++){
        for(int j=0;j<maze.n;j++){
            os<<maze.matrix[i][j]<<"\t";
        }
        os<<"\n";
    }
    return os;
}

Maze::Maze(int n, const vector<vector<int>> &matrix, const Coords &start, const Coords &anEnd, const Queue &queue) : n(
        n), matrix(matrix), start(start), end(anEnd), queue(queue) {}

int Maze::getN() const {
    return n;
}

const vector<vector<int>> &Maze::getMatrix() const {
    return matrix;
}

const Coords &Maze::getStart() const {
    return start;
}

const Coords &Maze::getAnEnd() const {
    return end;
}

const Queue &Maze::getQueue() const {
    return queue;
}

bool verif(Coords c, int n){
    return 0<=c.getX() and c.getX()<n and 0<=c.getY() and c.getY()<n;
}

void Maze::fill(){
    vector <vector <int> > viz, ways;
    ways.resize(n);
    viz.resize(n);
    for(int i=0;i<n;i++){
        viz[i].resize(n);
        ways[i].resize(n);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ways[i][j]=0;
            viz[i][j]=0;
        }
    }

    int col[3]={0,0,1};
    int row[3]={1,-1,0};

    viz[start.getY()][start.getX()]=1;
    Queue coada;
    Coords c1, c2;
    matrix[start.getY()][start.getX()]=1;
    ways[start.getY()][start.getX()]=1;

    coada+=start;

    while(!coada.isEmpty()){
        c1.setX(coada[0].getX());
        c1.setY(coada[0].getY());
        --coada;

        for(int i=0;i<3;i++){
            c2.setX(c1.getX()+col[i]);
            c2.setY(c1.getY()+row[i]);

            if(verif(c2, n)){
                ways[c2.getY()][c2.getX()]+=ways[c1.getY()][c1.getX()];
            }

            if(verif(c2,n) and matrix[c2.getY()][c2.getX()]==1 and viz[c2.getY()][c2.getX()]!=1){
                viz[c2.getY()][c2.getX()]=1;
                matrix[c2.getY()][c2.getX()]+= matrix[c1.getY()][c1.getX()];
                coada+=c2;

            }
        }
    }

    cout<<"Distanta minima este: "<<matrix[end.getY()][end.getX()]<<" iar numarul de drumuri este "<<ways[end.getY()][end.getX()];


}

int main(){
    Maze maze;
    cin>>maze;
    maze.fill();

}