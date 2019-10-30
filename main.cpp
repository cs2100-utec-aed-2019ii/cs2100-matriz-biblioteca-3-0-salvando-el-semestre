#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Node {
public:
    T data;
    int posX;
    int posY;
    Node<T>* next = nullptr;
    Node<T>* down = nullptr;

    Node(){}
    Node(int _posX, int _posY) : posX(_posX), posY(_posY){}
    Node(int _posX, int _posY, T _data) : posX(_posX), posY(_posY), data(_data){}
    ~Node(){}
};

template <class T>
class Matrix {
private:
    Node<T>* x;
    Node<T>* y;
    int columns;
    int rows;
public:
    Matrix() : columns(0), rows(0){
        x = new Node<T>(0,0);
        y = new Node<T>(0,0);
    }
//    Matrix(int n, int m) : columns(n), rows(m){}
    void insert (int _posX, int _posY, T _data) {
        Node<T>* new_node = new Node<T>(_posX, _posY, _data);
        Node<T>* temp = x;
        int i = 1;
        if(columns <= _posX){
            columns = _posX+1;
            while (temp->next) {
                temp = temp->next;
                i++;
            }
            while (i < columns) {
                temp->next = new Node<T>(i, 0);
                temp = temp->next;
                i++;
            }
        }
        i = 1;
        temp = y;
        if(rows <= _posY){
            rows = _posY+1;
            while (temp->down) {
                temp = temp->down;
                i++;
            }
            while (i < rows) {
                temp->down = new Node<T>(0, i);
                temp = temp->down;
                i++;
            }
        }
        Node<T>* temp_1 = x;
        Node<T>* temp_2 = y;
        while (temp_1 != nullptr && temp_1->posX != new_node->posX) {
            temp_1 = temp_1->next;
        }
        while (temp_1->down != nullptr && temp_1->posY < new_node->posY ) {
            temp_1 = temp_1->down;
        }
        Node<T>* down_temp = temp_1->down;
        temp_1->down = new_node;
        new_node->down = down_temp;
        while (temp_2 != nullptr && temp_2->posY < new_node->posY) {
            temp_2 = temp_2->down;
        }
        while (temp_2->next != nullptr && temp_2->posX < new_node->posX) {
            temp_2 = temp_2->next;
        }
        Node<T>* next_temp = temp_2->next;
        temp_2->next = new_node;
        new_node->next = next_temp;
    }
    ~Matrix(){}
/*
    Matrix& operator << (const T& _value){
        this->insert(_value[0]);
        return *this;
    }*/

    template <typename _T>
    inline friend ostream& operator << (ostream& os,  Matrix<_T>& matrix){
        _T matrix_print[matrix.columns][matrix.rows];
        Node<T>* temp_1 = matrix.x;
        Node<T>* temp_2;
        for(int i = 0; i < matrix.columns; i++){
            for(int j = 0; j < matrix.rows; j++){
                matrix_print[i][j] = NULL;
            }
        }
        while (temp_1 != nullptr) {
            temp_2 = temp_1;
            while (temp_2->down != nullptr) {
                temp_2 = temp_2->down;
                matrix_print[temp_2->posX][temp_2->posY] = temp_2->data;
            }
            temp_1 = temp_1->next;
        }
        for(int i = 0; i < matrix.columns; i++){
            for(int j = 0; j < matrix.rows; j++){
                os << matrix_print[i][j] << ' ';
            }
            os << endl << endl;
        }
        return os;
    }
};

int main( int, char * [])
{
    Matrix<double> m1;
    m1.insert(2,0,0);
    m1.insert(8,0,1);
    m1.insert(6,1,0);
    m1.insert(100,2,20);
    //m1 << (2,0,0) << (8,0,1) << (6,1,0) << (100,2,20);  // Insert
    cout << m1 << endl; // print in console
    //m1 >> (100,2,20); // delete

    //Matrix<double> m2 = Matrix<double>::identity(100,100);
    //ofstream _out("res.txt");
    //_out << m2 << endl; // print in file
    //_out.close();

    //cout << mult(m1 * m2) << endl; //  mutiplication
    //cout << add(m1 + m2) << endl; // addition
    //cout << transpose(m1) << endl; // transpose

    //cout << inv(m1 * m2) << endl; // Inversa - Extra!

/*	  // Cargar desde imagen -  Extra (Usar CImg.h)
    Matrix<double> m_image = load_from_image("myimage.jpg");
    m_image = transpose(m_image;
    ofstream _out_i("res.txt");
    _out_i << m_image;
    _out_i.close()
*/
    return 1;
}