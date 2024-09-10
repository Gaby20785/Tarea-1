#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


/* mult_opti:
    Parámetros:
        vector<vector<int>> &A: referencia a una matriz de int que representa la primera matriz a multiplicar.
        vector<vector<int>> &B: referencia a una matriz de int que representa la segunda matriz a multiplicar.
        vector<vector<int>> &B_T: referencia a una matriz de int donde se almacenará la transpuesta de la matriz B.
        vector<vector<int>> &C: referencia a una matriz de int donde se almacenará el resultado de la multiplicación.
        int d: dimensión de las matrices cuadradas (A, B, B_T y C).
    Descripción:
        Esta función realiza la multiplicación de dos matrices cuadradas A y B, optimizando la localidad de los datos mediante la transposición de la matriz B.
        Primero, se calcula la transpuesta de la matriz B y se almacena en la matriz B_T, lo que se realiza con dos bucles anidados.
        Luego, se realiza la multiplicación de las matrices utilizando A y B_T, almacenando el resultado en la matriz C:
        El resultado de la multiplicación se acumula en el elemento correspondiente de la matriz C (C[i][j]).
*/
void mult_opti(vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &B_T, vector< vector<int> > &C, int d) {
    
    for(int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            B_T[j][i] = B[i][j]; 
        }
    }
    
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            for (int k = 0; k < d; k++){
                C[i][j] += A[i][k]*B_T[j][k];
            }
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
void print_m (vector< vector<int> > m, int d)
{
	for (int i = 0; i < d; i++) 
	{
        for (int j = 0; j < d; j++) 
        {
            cout << "\t" << m[i][j];
        }
        cout << endl;
    }
}

/*Se multiplican son matrices cuadradas A y B, se pide la dimension de las matrices
y se muestra por pantalla las matrices a multiplicar, luego la matriz resultante y el
tiempo que tardó el algortimo.
*/
int main (int argc, char* argv[])
{
    int dim;
    cout << "Ingrese el tamaño de la matriz: " << endl;
    cin >> dim;

	vector<int> inside (dim);

	// Inicialización de matrices
	vector< vector<int> > A (dim, inside);
	vector< vector<int> > B (dim, inside);
    vector< vector<int> > B_T (dim, inside);
	vector< vector<int> > C (dim, inside);


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

    mult_opti(A, B, B_T, C, dim);

    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double,std::milli> duration = fin - inicio;

    cout << "\nMatriz C: " << endl;
    print_m (C, dim);
    cout << "Tiempo de ejecución: "<< duration.count() << "milisegundos"<< endl;
   	return 0;
}