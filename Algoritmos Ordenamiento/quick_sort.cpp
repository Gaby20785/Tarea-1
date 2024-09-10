#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

/*partition:
    Parámetros: 
        int arr[]: arreglo a que contiene subarreglo que se desea particionar.
        int low: índice del primer elemento del subarreglo.
        int high: índice del último elemento del subarreglo.
    Descripción:
        Selecciona como pivote al último elemento del subarreglo,
        luego se comparan los elementos del subarreglo con el pivote,
        dejando los elementos menor al pivote a su izquierda, y los 
        elementos mayores a la derecha. Finalmente retorna la posición
        del pivote.

*/
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

/*quickSort:
    Parámetros: 
        int arr[]: arreglo a ordenar.
        int low: índice del primer elemento del arreglo.
        int high: índice del último elemento del arreglo.
    Descripción:
       Si hay al menos dos elementos, se particiona el arreglo y luego se 
       divide el arreglo en dos, usando el pivote como punto de división, 
       luego se ordenan los arreglos de forma recursiva con QuickSort.
*/
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

/*Se ordena un arreglo con Quick Sort, se pide tamaño del arreglo
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

    quickSort(arr, 0, size - 1);

    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double,std::milli> duration = fin - inicio;

    cout << "Lista ordenada: ";
    printArray(arr, size);
    cout << "Tiempo de ejecución: "<< duration.count() << "milisegundos"<< endl;

    return 0;
}