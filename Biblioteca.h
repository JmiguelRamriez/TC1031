/*
 * Biblioteca.h
 *
 * Created on: 02/10/2025
 * Author: Jose Miguel Ramirez Gutierrez A01712628
 */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept> 
#include "Libro.h"

using namespace std;

struct Nodo {
    Libro data;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const Libro& l) : data(l), siguiente(nullptr), anterior(nullptr) {}
};

class Biblioteca {
    private:
        // Punteros al inicio y fin de la Lista Doblemente Ligada.
        Nodo* cabeza;
        Nodo* cola;
        int tamano; // Para llevar la cuenta de libros fácilmente
        
    public:
        Biblioteca();
        ~Biblioteca(); // Destructor para liberar memoria

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
 * Complejidad temporal: O(1)
 */
Biblioteca::Biblioteca() : cabeza(nullptr), cola(nullptr), tamano(0) {}

/*
 * ~Biblioteca() - Destructor.
 * Complejidad temporal: O(n)
 * Descripcion: Libera la memoria de todos los nodos de la lista para evitar memory leaks.
 */
Biblioteca::~Biblioteca() {
    Nodo* actual = cabeza;
    Nodo* siguiente;
    while (actual != nullptr) {
        siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

/*
 * agregar_libro() - Agrega un libro al final de la lista.
 * Complejidad temporal: O(1)
 * Descripcion: Se aprovecha el puntero 'cola' para realizar una inserción
 * constante al final de la lista.
 */
void Biblioteca::agregar_libro(const Libro& libro) {
    Nodo* nuevo_nodo = new Nodo(libro);
    if (cabeza == nullptr) {
        cabeza = nuevo_nodo;
        cola = nuevo_nodo;
    } else {
        cola->siguiente = nuevo_nodo;
        nuevo_nodo->anterior = cola;
        cola = nuevo_nodo;
    }
    tamano++;
}

/*
 * mostrar_todos_libros() - Muestra todos los libros.
 * Complejidad temporal: O(n)
 */
void Biblioteca::mostrar_todos_libros() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->data.mostrar_info() << endl;
        actual = actual->siguiente;
    }
}

/*
 * mostrar_disponibles() - Muestra solo los libros con ejemplares disponibles.
 * Complejidad temporal: O(n)
 */
void Biblioteca::mostrar_disponibles() {
    bool hay_disponible = false;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_cantidad_disponible() > 0) {
            cout << actual->data.mostrar_info() << endl;
            hay_disponible = true;
        }
        actual = actual->siguiente;
    }
}

// Función auxiliar para intercambiar la data de dos nodos (usada para ordenar)
void swap_libro_data(Nodo* a, Nodo* b) {
    Libro temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/*
 * ordenar_titulo() - Ordena los libros alfabéticamente por título.
 * Complejidad temporal: O(n^2)
 * Descripcion: Se utiliza una variante de Selection Sort que intercambia los
 * datos de los nodos. Para una lista ligada, este algoritmo es más simple de
 * implementar que Merge Sort y tiene una complejidad cuadrática.
 */
void Biblioteca::ordenar_titulo() {
    Nodo* i = cabeza;
    while (i != nullptr) {
        Nodo* j = i->siguiente;
        while (j != nullptr) {
            if (i->data.get_titulo() > j->data.get_titulo()) {
                swap_libro_data(i, j);
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }
}

/*
 * ordenar_anio() - Ordena los libros por año de publicación.
 * Complejidad temporal: O(n^2)
 * Descripcion: Selection Sort con criterio de año, resultando en complejidad cuadrática.
 */
void Biblioteca::ordenar_anio() {
    Nodo* i = cabeza;
    while (i != nullptr) {
        Nodo* j = i->siguiente;
        while (j != nullptr) {
            if (i->data.get_anio_publicacion() > j->data.get_anio_publicacion()) {
                swap_libro_data(i, j);
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }
}

/*
 * leer_csv() - Carga libros desde un archivo CSV.
 * Complejidad temporal: O(n * m)
 * Descripcion: Incluye la lógica de liberación de memoria antes de cargar
 * y utiliza la operación O(1) de agregar al final de la lista.
 */
void Biblioteca::leer_csv(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "No se pudo abrir el archivo: " << filename << endl;
        cout << "Iniciando con biblioteca vacia." << endl;
        return;
    }

    // Limpiar la lista existente y liberar memoria
    Nodo* actual_del = cabeza;
    Nodo* siguiente_del;
    while (actual_del != nullptr) {
        siguiente_del = actual_del->siguiente;
        delete actual_del;
        actual_del = siguiente_del;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;

    string linea;
    int libros_cargados = 0;
    while (getline(inFile, linea)) {
        stringstream ss(linea);
        string titulo, autor, genero, anio_str, cant_total_str, cant_disponible_str;

        if (getline(ss, titulo, ',') &&
            getline(ss, autor, ',') &&
            getline(ss, genero, ',') &&
            getline(ss, anio_str, ',') &&
            getline(ss, cant_total_str, ',') &&
            getline(ss, cant_disponible_str, ',')) {

            try {
                int anio = stoi(anio_str);
                int cant_total = stoi(cant_total_str);
                int cant_disponible = stoi(cant_disponible_str);

                Libro libro(titulo, autor, genero, anio, cant_total, cant_disponible);
                agregar_libro(libro); 
                libros_cargados++;

            } catch (const invalid_argument& e) {
                cerr << "Error de formato en la línea: " << linea << ". Ignorando libro." << endl;
            } catch (const out_of_range& e) {
                cerr << "Error de rango en la línea: " << linea << ". Ignorando libro." << endl;
            }
        }
    }

    inFile.close();
    cout << "Se cargaron " << libros_cargados << " libros desde " << filename << endl;
}

/*
 * guardar_csv() - Guarda los libros en un archivo CSV.
 * Complejidad temporal: O(n)
 */
void Biblioteca::guardar_csv(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir: " << filename << endl;
        return;
    }

    Nodo* actual = cabeza;
    while (actual != nullptr) {
        outFile << actual->data.get_titulo() << "," 
                << actual->data.get_autor() << "," 
                << actual->data.get_genero() << "," 
                << actual->data.get_anio_publicacion() << "," 
                << actual->data.get_cantidad_total() << "," 
                << actual->data.get_cantidad_disponible() << endl;
        actual = actual->siguiente;
    }

    outFile.close();
    cout << "Biblioteca guardada en " << filename << endl;
}

/*
 * prestar_libro() - Presta un libro.
 * Complejidad temporal: O(n)
 */
bool Biblioteca::prestar_libro(const string& titulo) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_titulo() == titulo) {
            if (actual->data.get_cantidad_disponible() > 0) {
                actual->data.set_cantidad_disponible(actual->data.get_cantidad_disponible() - 1);
                cout << "Se prestó el libro: " << titulo << endl;
                return true; 
            } else {
                cout << "No hay ejemplares disponibles de: " << titulo << endl;
                return false; 
            }
        }
        actual = actual->siguiente;
    }
    cout << "No se encontró el libro con título: " << titulo << endl;
    return false; 
}

/*
 * devolver_libro() - Devuelve un libro.
 * Complejidad temporal: O(n)
 */
bool Biblioteca::devolver_libro(const string& titulo) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_titulo() == titulo) {
            if (actual->data.get_cantidad_disponible() < actual->data.get_cantidad_total()) {
                actual->data.set_cantidad_disponible(actual->data.get_cantidad_disponible() + 1);
                cout << "Se devolvió el libro: " << titulo << endl;
                return true; 
            } else {
                cout << "Todos los ejemplares de " << titulo << " ya están en la biblioteca." << endl;
                return false; 
            }
        }
        actual = actual->siguiente;
    }
    cout << "No se encontró el libro con título: " << titulo << endl;
    return false;
}

/*
 * buscar_autor() - Busca todos los libros de un autor.
 * Complejidad temporal: O(n)
 */
vector<Libro*> Biblioteca::buscar_autor(const string& autor) {
    vector<Libro*> encontrados;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_autor() == autor) {
            encontrados.push_back(&(actual->data));
        }
        actual = actual->siguiente;
    }
    return encontrados;
}

/*
 * buscar_genero() - Busca todos los libros de un género.
 * Complejidad temporal: O(n)
 */
vector<Libro*> Biblioteca::buscar_genero(const string& genero) {
    vector<Libro*> encontrados;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_genero() == genero) {
            encontrados.push_back(&(actual->data));
        }
        actual = actual->siguiente;
    }
    return encontrados;
}

/*
 * buscar_titulo() - Busca libros cuyo titulo contenga una cadena específica.
 * Complejidad temporal: O(n * m)
 */
vector<Libro*> Biblioteca::buscar_titulo(const string& titulo) {
    vector<Libro*> encontrados;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_titulo().find(titulo) != string::npos) {
            encontrados.push_back(&(actual->data));
        }
        actual = actual->siguiente;
    }
    return encontrados;
}

/*
 * bucar_anio() - Busca todos los libros publicados en un año especifico.
 * Complejidad temporal: O(n)
 */
vector<Libro*> Biblioteca::bucar_anio(const int anio) {
    vector<Libro*> encontrados;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_anio_publicacion() == anio) {
            encontrados.push_back(&(actual->data));
        }
        actual = actual->siguiente;
    }
    return encontrados;
}

#endif