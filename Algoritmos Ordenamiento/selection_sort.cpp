#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

//https://www.swhosting.com/es/comunidad/manual/algoritmos-de-ordenacion-con-ejemplos-en-c


/*SelectionSort:
    Parámetros: 
        int arr[]: arreglo de int que se desea ordenar.
        int size[]: tamaño del arreglo a ordenar.
    Descripción:
        Se recorre todo el arreglo. Para cada posición i se vuelve a recorrer el arreglo desde la posición
        i + j en busca del elemento más pequeño, este elemento será intercambiado por el de la posición i.
        De forma más general, el algoritmo busca repetidamente el elemento más pequeño de la parte desordenada
        colocandolo en la posición correspondiente.
*/

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) { 
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) { //Se busca el elemento más pequeño en la sección desordenada.
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

/*printArray:
    Parámetros: 
        int arr[]: arreglo de int que se desea mostrar por pantalla.
        int size[]: tamaño del arreglo.
    Descripción:
        Se recorre todo el arreglo, imprimiento cada elemento.
*/

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/*Se ordena un arreglo con Selection Sort, se pide tamaño del arreglo
y que tipo de dataset se quiere usar: ordenados, orden inverso, desordenado.
Se muestra por pantalla el arreglo a ordenar, luego el arreglo ordenado y el
tiempo que tardó el algortimo.
*/
int main() {

    int n;
    cout << "Ingrese tamano: "<< endl;
    cin >> n;
    int arr[n];
    int size = n;

    int numero;

    cout << "Seleccione el tipo de array: " << endl;
    cout << "1. Ordenado 2. Orden inverso 3. Desordenado" << endl;

    int opcion;
    string texto;
    

    cin >> opcion;

    if (opcion == 1){
        texto = "array_ordenado.txt";
    }
    else if (opcion == 2){
        texto = "array_reves.txt";
    }
    else {
        texto = "array_desordenado.txt";
    }

    ifstream File(texto);

    for (int i = 0; i < n; i++){
        File >> numero;
        arr[i] = numero;
    }

    File.close();

    cout << "Lista original: ";
    printArray(arr, size);

    auto inicio = chrono::high_resolution_clock::now();

    selectionSort(arr, size);

    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double,std::milli> duration = fin - inicio;

    cout << "Lista ordenada: ";
    printArray(arr, size);
    cout << "Tiempo de ejecución: "<< duration.count() << "milisegundos"<< endl;

    return 0;
}