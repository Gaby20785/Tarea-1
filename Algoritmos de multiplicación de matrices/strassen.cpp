#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/* split:
    Parámetros:
        vector<vector<int>> &A: referencia a la matriz original que se va a dividir.
        vector<vector<int>> &B: referencia a la submatriz resultante.
        int row: índice de la fila de inicio en la matriz A.
        int col: índice de la columna de inicio en la matriz A.
        int d: dimensión de la submatriz B.
    Descripción:
        Esta función divide la matriz A en una submatriz B a partir de la posición especificada por row y col.
        Recorre los elementos de la submatriz B y los copia desde la matriz A, empezando en (row, col).
*/
void split (vector< vector<int> > &A, vector< vector<int> > &B, int row, int col, int d) {
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++) {
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++) {
            B[i1][j1] = A[i2][j2];
        }
    }
}

/* join:
    Parámetros:
        vector<vector<int>> &A: referencia a la submatriz que se va a unir en la matriz B.
        vector<vector<int>> &B: referencia a la matriz resultante.
        int row: índice de la fila de inicio en la matriz B.
        int col: índice de la columna de inicio en la matriz B.
        int d: dimensión de la submatriz A.
    Descripción:
        Esta función une la submatriz A en la matriz B a partir de la posición especificada por row y col.
        Recorre los elementos de la submatriz A y los copia en la matriz B, empezando en (row, col).
*/
void join (	vector< vector<int> > &A, vector< vector<int> > &B, int row, int col, int d) {
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++){
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++){
        	B[i2][j2] = A[i1][j1];
        }
    }
}

/* add:
    Parámetros:
        vector<vector<int>> &A: referencia a la primera matriz a sumar.
        vector<vector<int>> &B: referencia a la segunda matriz a sumar.
        vector<vector<int>> &C: referencia a la matriz resultante de la suma.
        int d: dimensión de las matrices.
    Descripción:
        Esta función suma dos matrices A y B de dimensión d y almacena el resultado en la matriz C.
        Recorre todos los elementos de las matrices y realiza la suma elemento a elemento.
*/
void add (	vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d) {
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

/* subtract:
    Parámetros:
        vector<vector<int>> &A: referencia a la primera matriz a restar.
        vector<vector<int>> &B: referencia a la segunda matriz a restar.
        vector<vector<int>> &C: referencia a la matriz resultante de la resta.
        int d: dimensión de las matrices.
    Descripción:
        Esta función resta dos matrices A y B de dimensión d y almacena el resultado en la matriz C.
        Recorre todos los elementos de las matrices y realiza la resta elemento a elemento.
*/
void subtract (	vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d) {
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

/* print_m:
    Parámetros:
        vector<vector<int>> m: matriz de int que se desea imprimir.
        int d: dimensión de la matriz cuadrada.
    Descripción:
        Esta función imprime una matriz cuadrada m en formato de tabla. 
        Se utiliza un bucle anidado para recorrer todas las filas y columnas de la matriz.
*/
void print_m (vector< vector<int> > m, int d){
	for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            cout << "\t" << m[i][j];
        }
        cout << endl;
    }
}

/********************************************************************
*********************** Strassen Algorithm **************************
********************************************************************/
/* strassen:
    Parámetros:
        vector<vector<int>> &A: referencia a la primera matriz a multiplicar.
        vector<vector<int>> &B: referencia a la segunda matriz a multiplicar.
        vector<vector<int>> &C: referencia a la matriz resultante de la multiplicación.
        int d: dimensión de las matrices.
    Descripción:
        Esta función implementa el algoritmo de Strassen para la multiplicación de matrices cuadradas de dimensión d.
        Si la dimensión de la matriz es 1, realiza una multiplicación directa.
        Si la dimensión no es divisible por dos, agrega padding a las matrices.
        Divide las matrices A y B en submatrices de tamaño d/2.
        Calcula las matrices M1 a M7 utilizando las submatrices.
        Calcula las submatrices C11, C12, C21 y C22 utilizando las matrices M1 a M7.
        Une las submatrices resultantes en la matriz C.
*/
void strassen (vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d) {

    //Caso base
    if (d == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

	//Si la dimensión no es divisible por dos, agrega padding a las matrices.
	if (d % 2 != 0) {
		d++;
		A.resize (d);
		B.resize (d);
		C.resize (d);
		
		for (int i = 0; i < d; i++) {
			A[i].resize (d);
			B[i].resize (d);
			C[i].resize (d);
		}
	}

	int new_d = d/2;
        
    vector<int> inside (new_d);

    // inicialización de submatrices	
	vector< vector<int> > A11 (new_d, inside);
	vector< vector<int> > A12 (new_d, inside);
	vector< vector<int> > A21 (new_d, inside);
	vector< vector<int> > A22 (new_d, inside);
	vector< vector<int> > B11 (new_d, inside);
	vector< vector<int> > B12 (new_d, inside);
	vector< vector<int> > B21 (new_d, inside);
	vector< vector<int> > B22 (new_d, inside);
	vector< vector<int> > C11 (new_d, inside);
	vector< vector<int> > C12 (new_d, inside);
	vector< vector<int> > C21 (new_d, inside);
	vector< vector<int> > C22 (new_d, inside);

	// se dividen las matrices A y B en 4 submatrices
	split(A, A11, 0 , 0, new_d);
    split(A, A12, 0 , new_d, new_d);
    split(A, A21, new_d, 0, new_d);
    split(A, A22, new_d, new_d, new_d);
    split(B, B11, 0 , 0, new_d);
    split(B, B12, 0 , new_d, new_d);
    split(B, B21, new_d, 0, new_d);
    split(B, B22, new_d, new_d, new_d);

    // matrices auxiliares
	vector< vector<int> > result1 (new_d, inside);
	vector< vector<int> > result2 (new_d, inside);

    /************************************************
    *** 	M1 = (A11 + A22)(B11 + B22)
    *** 	M2 = (A21 + A22) B11
    *** 	M3 = A11 (B12 - B22)
    *** 	M4 = A22 (B21 - B11)
    *** 	M5 = (A11 + A12) B22
    *** 	M6 = (A21 - A11) (B11 + B12)
    *** 	M7 = (A12 - A22) (B21 + B22)
    ************************************************/

	// calcula M1
	add(A11, A22, result1, new_d);
	add(B11, B22, result2, new_d);
	vector< vector<int> > M1 (new_d, inside);
	strassen(result1, result2, M1, new_d);

	// calcula M2
	add(A21, A22, result1, new_d);
	vector< vector<int> > M2 (new_d, inside);
	strassen(result1, B11, M2, new_d);

	// calcula M3
	subtract(B12, B22, result2, new_d);
	vector< vector<int> > M3 (new_d, inside);
	strassen(A11, result2, M3, new_d);

	// calcula M4
	subtract(B21, B11, result2, new_d);
	vector< vector<int> > M4 (new_d, inside);
	strassen(A22, result2, M4, new_d);

	// calcula M5
	add(A11, A12, result1, new_d);
	vector< vector<int> > M5 (new_d, inside);
	strassen(result1, B22, M5, new_d);

	// calcula M6
	subtract(A21, A11, result1, new_d);
	add(B11, B12, result2, new_d);
	vector< vector<int> > M6 (new_d, inside);
	strassen(result1, result2, M6, new_d);

	// calcula M7
	subtract(A12, A22, result1, new_d);
	add(B21, B22, result2, new_d);
	vector< vector<int> > M7 (new_d, inside);
	strassen(result1, result2, M7, new_d);

	/**********************************************
    ***      C11 = M1 + M4 - M5 + M7
    ***      C12 = M3 + M5
    ***      C21 = M2 + M4
    ***      C22 = M1 - M2 + M3 + M6
    **********************************************/

	// calcula C11
    add(M1, M4, result1, new_d);
    add(result1, M7, result2, new_d);
    subtract(result2, M5, C11, new_d);

    // calcula C12
    add(M3, M5, C12, new_d);

    // calcula C21
    add(M2, M4, C21, new_d);

    // calcula C22
    subtract(M1, M2, result1, new_d);
    add(M3, M6, result2, new_d);
    add(result1, result2, C22, new_d);

    // se unen las matrices en una
    join(C11, C, 0 , 0, new_d);
    join(C12, C, 0 , new_d, new_d);
    join(C21, C, new_d, 0, new_d);
    join(C22, C, new_d, new_d, new_d);
}


/*Se multiplican son matrices cuadradas A y B, se pide la dimension de las matrices
y se muestra por pantalla las matrices a multiplicar, luego la matriz resultante y el
tiempo que tardó el algortimo.
*/
int main (int argc, char* argv[]) {

    int dim;
    cout << "Ingrese el tamaño de la matriz: " << endl;
    cin >> dim;

	// vector for the inside of the matrices
	vector<int> inside (dim);

	// initialize matrices to be multiplied
	vector< vector<int> > A (dim, inside);
	vector< vector<int> > B (dim, inside);
	vector< vector<int> > C (dim, inside);

	// intialize how many lines we will be scanning

    int numero;

    ifstream File("A.txt");

    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            File >> numero;
            A[i][j] = numero;
        }
    }

    File.close();

    ifstream File2("B.txt");

    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            File2 >> numero;
            B[i][j] = numero;
        }
    }

    File2.close();

    cout << "Matriz A: " << endl;
    print_m (A, dim);
    cout << "\nMatriz B: " << endl;
    print_m (B, dim);

    auto inicio = chrono::high_resolution_clock::now();

    strassen(A, B, C, dim);

    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = fin - inicio;

    cout << "\nMatriz C: " << endl;
    print_m (C, dim);
    cout << "Tiempo de ejecución: "<< duration.count() << "milisegundos"<< endl;
   	return 0;

}