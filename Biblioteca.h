/*
 * Biblioteca.h
 *
 *  Created on: 02/10/2025
 *      Author: Jose Miguel Ramirez Gutierrez A01712628
 */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Libro.h"

using namespace std;

class Biblioteca {
    private:
        // Vector que contiene todos los libros de la biblioteca.
        vector<Libro> libros;
        
    public:
        Biblioteca();

        void agregar_libro(const Libro& libro);
        void mostrar_todos_libros();
        void mostrar_disponibles();
        void ordenar_anio();
        void ordenar_titulo();
        void guardar_csv(const string& filename);
        void leer_csv(const string& filename);

        bool prestar_libro(const string& titulo);
        bool devolver_libro(const string& titulo);

        vector<Libro*> buscar_autor(const string& autor);
        vector<Libro*> buscar_genero(const string& genero);
        vector<Libro*> buscar_titulo(const string& titulo);
        vector<Libro*> bucar_anio(const int anio);
};

/*
 * Biblioteca() - Constructor por defecto.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Inicializa una biblioteca vacia. El vector de libros se inicializa
 * automáticamente como vacío, por lo que la operación es de tiempo constante.
 */
Biblioteca::Biblioteca() {}

/*
 * agregar_libro() - Agrega un libro al vector de libros.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(n) (si el vector necesita redimensionarse)
 * Descripcion: Inserta un libro al final del vector. En el caso promedio es O(1),
 * pero si el vector necesita redimensionarse para acomodar más elementos,
 * puede ser O(n) debido a la reasignación de memoria y copia de elementos.
 */
void Biblioteca::agregar_libro(const Libro& libro) {
    libros.push_back(libro);
}

/*
 * mostrar_todos_libros() - Muestra todos los libros de la biblioteca.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Recorre el vector completo de libros e imprime la información de cada uno.
 * La complejidad es lineal respecto al número de libros en la biblioteca.
 */
void Biblioteca::mostrar_todos_libros() {
    for (int i = 0; i < libros.size(); i++) {
        cout << libros[i].mostrar_info() << endl;
    }
}

/*
 * mostrar_disponibles() - Muestra solo los libros con ejemplares disponibles.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Recorre todo el vector de libros y muestra solo aquellos que tienen
 * al menos un ejemplar disponible para préstamo. La complejidad es lineal.
 */
void Biblioteca::mostrar_disponibles() {
    bool hay_disponible = false;

    for (int i = 0; i < libros.size(); i++) {
        if (libros[i].get_cantidad_disponible() > 0) {
            cout << libros[i].mostrar_info() << endl;
            hay_disponible = true;
        }
    }
}

/*
 * ordenar_titulo() - Ordena los libros alfabéticamente por título.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripcion: Utiliza el algoritmo sort de la STL con una función lambda
 * para ordenar por título. La complejidad es O(n log n) tipica de los
 * algoritmos de ordenamiento eficientes.
 */
void Biblioteca::ordenar_titulo() {
    sort(libros.begin(), libros.end(), [](const Libro& a, const Libro& b) {
        return a.get_titulo() < b.get_titulo(); 
    });
}

/*
 * ordenar_anio() - Ordena los libros por año de publicación.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripcion: Utiliza el algoritmo sort de la STL con una función lambda
 * para ordenar por año. La complejidad es O(n log n).
 */
void Biblioteca::ordenar_anio() {
    sort(libros.begin(), libros.end(), [](const Libro& a, const Libro& b) {
        return a.get_anio_publicacion() < b.get_anio_publicacion();
    });
}

/*
 * leer_csv() - Carga libros desde un archivo CSV.
 * Complejidad temporal:
 * - Mejor caso: O(n * m)
 * - Caso promedio: O(n * m)
 * - Peor caso: O(n * m)
 * Descripcion: Lee un archivo CSV línea por línea, donde n es el número de líneas
 * y m es la longitud promedio de cada línea. Por cada línea, parsea los campos
 * separados por comas y crea un objeto Libro. La complejidad total es O(n * m).
 */
void Biblioteca::leer_csv(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "No se pudo abrir el archivo: " << filename << endl;
        cout << "Iniciando con biblioteca vacia." << endl;
        return;
    }

    string linea;
    while (getline(inFile, linea)) {
        stringstream ss(linea);
        string titulo, autor, genero, anio_str, cant_total_str, cant_disponible_str;

        // Leer cada campo separado por comas como string
        getline(ss, titulo, ',');
        getline(ss, autor, ',');
        getline(ss, genero, ',');
        getline(ss, anio_str, ',');
        getline(ss, cant_total_str, ',');
        getline(ss, cant_disponible_str, ',');

        // Convertir strings a enteros
        int anio = stoi(anio_str);
        int cant_total = stoi(cant_total_str);
        int cant_disponible = stoi(cant_disponible_str);

        // Crear el libro y agregarlo
        Libro libro(titulo, autor, genero, anio, cant_total, cant_disponible);
        libros.push_back(libro);
    }

    inFile.close();
    cout << "Se cargaron " << libros.size() << " libros desde " << filename << endl;
}

/*
 * guardar_csv() - Guarda los libros de la biblioteca en un archivo CSV.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Recorre el vector de libros y escribe la informacion de cada uno
 * en formato CSV. La complejidad es lineal respecto al número de libros.
 */
void Biblioteca::guardar_csv(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir: " << filename << endl;
        return;
    }

    for (const Libro& l: libros) {
        outFile << l.get_titulo() << "," 
                << l.get_autor() << "," 
                << l.get_genero() << "," 
                << l.get_anio_publicacion() << "," 
                << l.get_cantidad_total() << "," 
                << l.get_cantidad_disponible() << endl;
    }

    outFile.close();
    cout << "Biblioteca guardada en " << filename << endl;
}

/*
 * prestar_libro() - Presta un libro reduciendo su cantidad disponible en 1.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el libro está en la primera posición)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Busca un libro por título en el vector. Si lo encuentra y hay
 * ejemplares disponibles, reduce la cantidad disponible en 1. La búsqueda
 * lineal hace que la complejidad sea O(n) en el caso promedio.
 */
bool Biblioteca::prestar_libro(const string& titulo) {
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_titulo() == titulo) {
            if (libros[i].get_cantidad_disponible() > 0) {
                libros[i].set_cantidad_disponible(libros[i].get_cantidad_disponible() - 1);
                cout << "Se presto el libro: " << titulo << endl;
                return true; 
            } else {
                cout << "No hay ejemplares disponibles de: " << titulo << endl;
                return false; 
            }
        }
    }
    cout << "No se encontro el libro con titulo: " << titulo << endl;
    return false; 
}

/*
 * devolver_libro() - Devuelve un libro aumentando su cantidad disponible en 1.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el libro está en la primera posición)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Busca un libro por título. Si lo encuentra y la cantidad disponible
 * es menor que el total, incrementa la cantidad disponible en 1. La búsqueda
 * lineal resulta en complejidad O(n) en el caso promedio.
 */
bool Biblioteca::devolver_libro(const string& titulo) {
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_titulo() == titulo) {
            if (libros[i].get_cantidad_disponible() < libros[i].get_cantidad_total()) {
                libros[i].set_cantidad_disponible(libros[i].get_cantidad_disponible() + 1);
                cout << "Se devolvio el libro: " << titulo << endl;
                return true; 
            } else {
                cout << "Todos los ejemplares de " << titulo << " ya estan en la biblioteca." << endl;
                return false; 
            }
        }
    }
    cout << "No se encontro el libro con titulo: " << titulo << endl;
    return false;
}

/*
 * buscar_autor() - Busca todos los libros de un autor especifico.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Recorre todo el vector de libros y retorna un vector de punteros
 * a aquellos libros cuyo autor coincida con el buscado. La complejidad es lineal
 * ya que debe verificar todos los libros.
 */
vector<Libro*> Biblioteca::buscar_autor(const string& autor) {
    vector<Libro*> encontrados;
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_autor() == autor) {
            encontrados.push_back(&libros[i]);
        }
    }
    return encontrados;
}

/*
 * buscar_genero() - Busca todos los libros de un género especifico.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Recorre todo el vector de libros y retorna un vector de punteros
 * a aquellos libros cuyo género coincida con el buscado. La complejidad es lineal.
 */
vector<Libro*> Biblioteca::buscar_genero(const string& genero) {
    vector<Libro*> encontrados;
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_genero() == genero) {
            encontrados.push_back(&libros[i]);
        }
    }
    return encontrados;
}

/*
 * buscar_titulo() - Busca libros cuyo titulo contenga una cadena específica.
 * Complejidad temporal:
 * - Mejor caso: O(n * m)
 * - Caso promedio: O(n * m)
 * - Peor caso: O(n * m)
 * Descripcion: Recorre todos los libros (n) y para cada uno ejecuta la función
 * find() que tiene complejidad O(m) donde m es la longitud del título.
 * Retorna un vector de punteros a los libros que contienen la cadena buscada.
 */
vector<Libro*> Biblioteca::buscar_titulo(const string& titulo) {
    vector<Libro*> encontrados;
    for (size_t i = 0; i < libros.size(); i++) {
        // Búsqueda que incluye titulos que contengan la cadena buscada
        if (libros[i].get_titulo().find(titulo) != string::npos) {
            encontrados.push_back(&libros[i]);
        }
    }
    return encontrados;
}

/*
 * bucar_anio() - Busca todos los libros publicados en un año especifico.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Recorre todo el vector de libros y retorna un vector de punteros
 * a aquellos libros cuyo año de publicación coincida con el buscado.
 * La complejidad es lineal.
 */
vector<Libro*> Biblioteca::bucar_anio(const int anio) {
    vector<Libro*> encontrados;
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_anio_publicacion() == anio) {
            encontrados.push_back(&libros[i]);
        }
    }
    return encontrados;
}

#endif