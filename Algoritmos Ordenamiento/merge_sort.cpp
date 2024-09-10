#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

/*merge:
    Parámetros: 
        int arr[]: arreglo de int que contiene los subarreglos que se desean ordenar.
        int left: índice del primer elemento del primer subarreglo.
        int mid: índice del último elemento del primer subarreglo.
        int right: índice del último elemento del segundo subarreglo.
    Descripción:
       Se hace uso de arreglos auxiliares temporales para almacenar los subarreglos (L[n1] y R[n2]),
       luego se van comparando los elementos de ambos subarreglos en orden haciendo uso de dos indices,
       y se coloca el menor elemento resultante de la comparación en el arreglo principal (arr[]). Luego
       de recorrerse por completo uno de los subarreglos, los elementos restantes del otro subarreglo son
       colocados en el arreglo principal.
*/
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

/*mergeSort:
    Parámetros: 
        int arr[]: arreglo de int que se desea ordenar.
        int left: índice dell primer elemento del array.
        int right: índice del último elemento del array.
    Descripción:
       Si el array tiene más de un elemento se divide el arreglo en dos, luego se
       llama de forma recursiva a mergeSort para ordenar ambas mitades del arreglo que
       fue dividido, por último se combinan ambas mitades ordenadas haciendo uso de merge. 
*/

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/*printList:
    Parámetros: 
        int arr[]: arreglo de int que se desea mostrar por pantalla.
        int size[]: tamaño del arreglo.
    Descripción:
        Se recorre todo el arreglo, imprimiento cada elemento.
*/
void printList(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/*Se ordena un arreglo con Merge Sort, se pide tamaño del arreglo
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
    printList(arr, size);

    auto inicio = chrono::high_resolution_clock::now();

    mergeSort(arr, 0, size - 1);

    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = fin - inicio;

    cout << "Lista ordenada: ";
    printList(arr, size);
    cout << "Tiempo de ejecución: "<< duration.count() << "milisegundos"<< endl;

    return 0;
}