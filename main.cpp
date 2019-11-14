#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <ctime>
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
public:
    Node<T>* x;
    Node<T>* y;
    int columns;
    int rows;
    Matrix() : columns(0), rows(0){
        x = new Node<T>(0,0);
        y = new Node<T>(0,0);
    }
    ~Matrix(){}
    void resize(int sizeX = 0,int sizeY = 0){
        Node<T>* temp_1 = x;
        Node<T>* temp_2 = y;
        //------------------------------------------------------------
        while (temp_1 != nullptr) {
            temp_2 = temp_1;
            while (temp_2 != nullptr && temp_2->down != nullptr) {
                temp_2 = temp_2->down;
                if(sizeX < temp_2->posX){sizeX = temp_2->posX;}
                if(sizeY < temp_2->posY){sizeY = temp_2->posY;}
            }
            temp_1 = temp_1->next;
        }
        //------------------------------------------------------------
        Node<T>* temp = x;
        //------------------------------------------------------------
        int i = 1;
        if(columns < sizeX+1){
            columns = sizeX+1;
            while (temp->next) {
                temp = temp->next;
                i++;
            }
            while (i < columns) {
                temp->next = new Node<T>(i, 0);
                temp = temp->next;
                i++;
            }
        } else if (columns > sizeX+1) {
            columns = sizeX+1;
            while (temp->next->posX < columns) {
                temp = temp->next;
            }
            Node<T>* temp_prev = temp;
            temp = temp->next;
            temp_prev->next = nullptr;
            while (temp->next) {
                temp_prev = temp;
                temp = temp->next;
                delete temp_prev;
            }
        }
        //------------------------------------------------------------
        i = 1;
        temp = y;
        if(rows < sizeY+1){
            rows = sizeY+1;
            while (temp->down) {
                temp = temp->down;
                i++;
            }
            while (i < rows) {
                temp->down = new Node<T>(0, i);
                temp = temp->down;
                i++;
            }
        } else if (rows > sizeY+1) {
            rows = sizeY+1;
            while (temp->down->posY < rows) {
                temp = temp->down;
            }
            Node<T>* temp_prev = temp;
            temp = temp->down;
            temp_prev->down = nullptr;
            while (temp->down) {
                temp_prev = temp;
                temp = temp->down;
                delete temp_prev;
            }
        }
    }
    void insert (int _posY, int _posX, T _data) {
        Node<T>* new_node = new Node<T>(_posX, _posY, _data);
        //------------------------------------------------------------
        resize(_posX,_posY);
        //------------------------------------------------------------
        Node<T>* temp_1 = x;
        Node<T>* temp_2 = y;
        //------------------------------------------------------------
        while (temp_1 != nullptr && temp_1->posX != new_node->posX) {
            temp_1 = temp_1->next;
        }
        while (temp_1->down != nullptr && temp_1->posY < new_node->posY ) {
            temp_1 = temp_1->down;
        }
        Node<T>* down_temp = temp_1->down;
        temp_1->down = new_node;
        new_node->down = down_temp;
        //------------------------------------------------------------
        while (temp_2 != nullptr && temp_2->posY != new_node->posY) {
            temp_2 = temp_2->down;
        }
        while (temp_2->next != nullptr && temp_2->posX < new_node->posX) {
            temp_2 = temp_2->next;
        }
        Node<T>* next_temp = temp_2->next;
        temp_2->next = new_node;
        new_node->next = next_temp;
    }
    void erase (int _posY, int _posX) {
        Node<T>* temp_1 = x;
        Node<T>* temp_2 = y;
        //------------------------------------------------------------
        while (temp_1 != nullptr && temp_1->next != nullptr && temp_1->posX != _posX) {
            temp_1 = temp_1->next;
        }
        while (temp_1 != nullptr && temp_1->down != nullptr && temp_1->down->posY < _posY ) {
            temp_1 = temp_1->down;
        }
        if(temp_1 != nullptr && temp_1->down != nullptr && temp_1->down->posY == _posY){
            Node<T>* down_temp = temp_1->down;
            temp_1->down = temp_1->down->down;
            delete down_temp;
        }
        //------------------------------------------------------------
        while (temp_2 != nullptr && temp_2->down != nullptr && temp_2->posY < _posY) {
            temp_2 = temp_2->down;
        }
        while (temp_2 != nullptr && temp_2->next != nullptr && temp_2->next->posX < _posX) {
            temp_2 = temp_2->next;
        }
        if(temp_2 != nullptr && temp_2->next != nullptr && temp_2->next->posX == _posX){
            Node<T>* next_temp = temp_2->next;
            temp_2->next = temp_2->next->next;
            delete next_temp;
        }
        //------------------------------------------------------------
        resize();
    }

    static Matrix<T> identity(int _posY, int _posX){
        Matrix<T> matrix;
        for(int i = 0; i < _posY && i < _posX; i++)
            matrix.insert(i,i,1);
        return matrix;
    }

    template <typename _T>
    inline friend ostream& operator << (ostream& os,  Matrix<_T> matrix){
        _T matrix_print[matrix.columns][matrix.rows];
        Node<_T>* temp_1 = matrix.x;
        Node<_T>* temp_2;
        //------------------------------------------------------------
        for(int i = 0; i < matrix.columns; i++){
            for(int j = 0; j < matrix.rows; j++){
                matrix_print[i][j] = NULL;
            }
        }
        //------------------------------------------------------------
        while (temp_1 != nullptr) {
            temp_2 = temp_1;
            while (temp_2->down != nullptr) {
                temp_2 = temp_2->down;
                matrix_print[temp_2->posX][temp_2->posY] = temp_2->data;
            }
            temp_1 = temp_1->next;
        }
        //------------------------------------------------------------
        for(int i = 0; i < matrix.rows; i++){
            for(int j = 0; j < matrix.columns; j++){
                os << matrix_print[j][i] << ' ';
            }
            os << endl;
        }
        //------------------------------------------------------------
        return os;
    }
};


Matrix<double> mult (Matrix<double> m1,Matrix<double> m2){
    Matrix<double> resultado;
    double matrix_mult[m2.columns][m1.rows];
    double matrix_m1[m1.columns][m1.rows];
    double matrix_m2[m2.columns][m2.rows];
    Node<double>* temp_1 = m1.x;
    Node<double>* temp_2;
    if(m1.columns == m2.rows) {
        //------------------------------------------------------------
        for (int i = 0; i < m1.columns; i++) {
            for (int j = 0; j < m1.rows; j++) {
                matrix_m1[i][j] = 0;
            }
        }
        //------------------------------------------------------------
        while (temp_1 != nullptr) {
            temp_2 = temp_1;
            while (temp_2->down != nullptr) {
                temp_2 = temp_2->down;
                matrix_m1[temp_2->posX][temp_2->posY] = temp_2->data;
            }
            temp_1 = temp_1->next;
        }
        //------------------------------------------------------------
        temp_1 = m2.x;
        temp_2;
        //------------------------------------------------------------
        for (int i = 0; i < m2.columns; i++) {
            for (int j = 0; j < m2.rows; j++) {
                matrix_m2[i][j] = 0;
            }
        }
        //------------------------------------------------------------
        while (temp_1 != nullptr) {
            temp_2 = temp_1;
            while (temp_2->down != nullptr) {
                temp_2 = temp_2->down;
                matrix_m2[temp_2->posX][temp_2->posY] = temp_2->data;
            }
            temp_1 = temp_1->next;

        }
        //------------------------------------------------------------
        double cont;
        //------------------------------------------------------------
        for (int i = 0; i < m2.columns; i++) {
            for (int j = 0; j < m1.rows; j++) {
                matrix_mult[i][j] = 0;
            }
        }
        //------------------------------------------------------------
        for (int i = 0; i < m1.rows; i++) {
            for (int j = 0; j < m2.columns; j++) {
                cont = 0;
                for (int k = 0; k < m1.columns; k++) {
                    cont += (matrix_m1[k][i] * matrix_m2[j][k]);
                }
                matrix_mult[j][i] = cont;
            }
        }
        //------------------------------------------------------------
        for (int i = 0; i < m1.rows; i++) {
            for (int j = 0; j < m2.columns; j++) {
                if (matrix_mult[j][i] != 0) {
                    resultado.insert(i, j, matrix_mult[j][i]);
                }
            }
        }
        //------------------------------------------------------------
    }
    return resultado;
}

Matrix<double> add (Matrix<double> m1,Matrix<double> m2){
    Matrix<double> resultado;
    double matrix_mult[m2.columns][m1.rows];
    double matrix_m1[m1.columns][m1.rows];
    double matrix_m2[m2.columns][m2.rows];
    Node<double>* temp_1 = m1.x;
    Node<double>* temp_2;
    if(m1.columns == m2.columns && m1.rows == m2.rows) {
        //------------------------------------------------------------
        for (int i = 0; i < m1.columns; i++) {
            for (int j = 0; j < m1.rows; j++) {
                matrix_m1[i][j] = 0;
            }
        }
        //------------------------------------------------------------
        while (temp_1 != nullptr) {
            temp_2 = temp_1;
            while (temp_2->down != nullptr) {
                temp_2 = temp_2->down;
                matrix_m1[temp_2->posX][temp_2->posY] = temp_2->data;
            }
            temp_1 = temp_1->next;
        }
        //------------------------------------------------------------
        temp_1 = m2.x;
        temp_2;
        //------------------------------------------------------------
        for (int i = 0; i < m2.columns; i++) {
            for (int j = 0; j < m2.rows; j++) {
                matrix_m2[i][j] = 0;
                matrix_mult[i][j]=0;
            }
        }
        //------------------------------------------------------------
        while (temp_1 != nullptr) {
            temp_2 = temp_1;
            while (temp_2->down != nullptr) {
                temp_2 = temp_2->down;
                matrix_m2[temp_2->posX][temp_2->posY] = temp_2->data;
            }
            temp_1 = temp_1->next;
        }
        //------------------------------------------------------------
        double cont;

        //------------------------------------------------------------
        for (int i = 0; i < m1.rows; i++) {
            for (int j = 0; j < m1.columns; j++) {
                matrix_mult[j][i] = matrix_m1[j][i] + matrix_m2[j][i];
            }
        }
        //------------------------------------------------------------
        for (int i = 0; i < m1.rows; i++) {
            for (int j = 0; j < m2.columns; j++) {
                if (matrix_mult[j][i] != 0) {
                    resultado.insert(i, j, matrix_mult[j][i]);
                }
            }
        }
        //------------------------------------------------------------
    }
    return resultado;
}

Matrix<double> transpose(Matrix<double> m1){
    Matrix<double> resultado;
    Node<double>* temp_1 = m1.x;
    Node<double>* temp_2;
    //------------------------------------------------------------
    while (temp_1 != nullptr) {
        temp_2 = temp_1;
        while (temp_2->down != nullptr) {
            temp_2 = temp_2->down;
            resultado.insert(temp_2->posX,temp_2->posY,temp_2->data);
        }
        temp_1 = temp_1->next;
    }
    //------------------------------------------------------------
    return resultado;
}

int main( int, char * [])
{
    srand(time(NULL));
    Matrix<double> m1;
    for(int i= 0; i < 10; i++) //es de 100
        m1.insert(rand()%10,rand()%10,rand()%25);//(f,c,val)
    cout << m1 << endl; // print in console
    m1.erase(100,2); // delete(f,c)
    Matrix<double> m2 = Matrix<double>::identity(m1.rows,m1.rows); //f,c
    ofstream _out("res.txt");
    _out << m2 << endl; // print in file
    _out.close();
    cout << mult(m1,m2) << endl; //  mutiplication
    cout << add(m1,m1) << endl; // addition
    cout << transpose(m1) << endl; // transpose
    //cout << inv(m1) << endl; // Inversa - Extra!
    // Cargar desde imagen -  Extra (Usar CImg.h)
    //Matrix<double> m_image = load_from_image("lenna.jpg");//512x512
    //ofstream _out_i("res.txt");
    //_out_i << m_image;
    //_out_i.close()
    return 1;
}