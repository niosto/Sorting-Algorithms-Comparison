#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <ctime>

using namespace std;

// Función que implementa el algoritmo de Insertion Sort para ordenar un vector de cadenas
void insertionSort(vector<string>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        string key = arr[i];  // Almacenar el elemento actual
        int j = i - 1;

        // Desplazar los elementos mayores que 'key' hacia la derecha
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // Insertar 'key' en la posición correcta
        arr[j + 1] = key;
    }
}

// Función que implementa el algoritmo Bubble Sort optimizado para ordenar un vector de cadenas
void bubble(vector<string>& arr, int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
            // Si hubo un intercambio, retroceder para verificar los elementos anteriores
            if (i != 0 && arr[i - 1] > arr[i])
                i -= 2;  
        }
    }
}

// Función para obtener el índice del bucket basado en la primera letra del string
// Retorna un valor entre 0 y 25 dependiendo de la letra (de 'a' a 'z')
int getBucketIndex(string str) {
    if (str.empty()) return 0;  
    return tolower(str[0]) - 'a';  // Convertir la primera letra a minúscula y calcular el índice
}

// Función que implementa el algoritmo Bucket Sort para ordenar un vector de cadenas
void bucketSort(vector<string>& arr, int n) {
    const int numBuckets = 26;  // Número de buckets, uno para cada letra del alfabeto
    vector<vector<string>> buckets(numBuckets);  // Crear los buckets como vectores de vectores

    // Distribuir las cadenas en los buckets basados en la primera letra
    for (const string& str : arr) {
        int bucketIndex = getBucketIndex(str);  // Obtener el índice del bucket
        buckets[bucketIndex].push_back(str);  // Colocar la cadena en su bucket
    }

    // Limpiar el vector original para llenarlo con las cadenas ordenadas
    arr.clear();

    // Ordenar individualmente cada bucket y luego concatenarlos al vector original
    for (int i = 0; i < numBuckets; ++i) {
        insertionSort(buckets[i]);  // Ordenar cada bucket usando Insertion Sort
        for (const string& str : buckets[i]) {
            arr.push_back(str);  // Concatenar los resultados ordenados en el vector original
        }
    }
}

// Función que mide y muestra el tiempo de ejecución del algoritmo Bubble Sort
void medirTiempoBubbleSort(vector<string>& arr, int n) {
    clock_t start = clock();  
    bubble(arr, n);  
    clock_t end = clock();  
    double duracion = double(end - start) / CLOCKS_PER_SEC;  
    cout << "Tiempo: " << duracion << " s. Usando Bubble Sort con: " << n + 1 << " registros" << endl;
}

// Función que mide y muestra el tiempo de ejecución del algoritmo Bucket Sort
void medirTiempoBucketSort(vector<string>& arr, int n) {
    clock_t start = clock(); 
    bucketSort(arr, n);  
    clock_t end = clock(); 
    double duracion = double(end - start) / CLOCKS_PER_SEC;  
    cout << "Tiempo: " << duracion << " s. Usando Bucket Sort con: " << n + 1 << " registros" << endl;
}

int main() {
    ifstream file;
    file.open("palabras1.txt", ios::in); 

    // Verificar si el archivo se abrió correctamente
    if (file.fail()) { 
        cout << "Error" << endl;  
        return 0;  
    }

    // Variables para el control del tamaño de los datos
    int j = 0;  // Contador de palabras leídas
    int aumento = 10000;  // Intervalo para medir el tiempo de ejecución de los algoritmos
    int i = 250000;  // Límite de palabras a procesar (247.000 registros en archivo)
    vector<string> array;  // Vector para almacenar las palabras
    array.reserve(i);  // Reservar espacio en el vector para mejorar el rendimiento

    // Leer las palabras del archivo y almacenarlas en el vector
    while (!file.eof() && j <= i) {
        string str;
        getline(file, str);  // Leer una línea del archivo (una palabra)
        array.push_back(str);  // Añadir la palabra al vector

        // Cada vez que se alcanzan múltiplos de 'aumento' o se llega al final del archivo
        if ((j + 1) % aumento == 0 || file.eof()) {
            vector<string> desorden = array;  // Crear una copias del vector para los algoritmos
            vector<string> desorden2 = array;  

            medirTiempoBubbleSort(desorden, j);
            medirTiempoBucketSort(desorden2, j);
        }
        j++; 
    }

    // Cerrar el archivo
    file.close();
    return 0;
}
