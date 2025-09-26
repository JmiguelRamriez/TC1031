//Nombre: José Miguel Ramírez
//Matricula: A01712628

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "Libro.h"

using namespace std;

class Biblioteca {
    private:
        vector<Libro> libros;
        
    public:
        Biblioteca();

        void agregar_libro(const Libro& libro);
        void mostrar_todos_libros();
        void mostrar_disponibles();
        void ordenar_anio();
        void ordenar_titulo();

        bool prestar_libro(const string& titulo);
        bool devolver_libro(const string& titulo);

        Libro* buscar_isbn(const string& isbn);
        vector <Libro*> buscar_autor(const string& autor);
        vector <Libro*> buscar_genero(const string& genero);
        vector <Libro*> bucar_anio(const int anio);


};

Biblioteca::Biblioteca() {}

void Biblioteca::agregar_libro(const Libro& libro) {
    libros.push_back(libro);
}

void Biblioteca::mostrar_todos_libros() {
    for (int i = 0; i < libros.size(); i++) {
        cout << libros[i].mostrar_info() << endl;
    }
}

void Biblioteca::mostrar_disponibles(){
    bool hay_disponible = false;

    for (int i = 0; i < libros.size(); i++){
        if (libros[i].get_cantidad_disponible() > 0){
            cout << libros[i].mostrar_info() << endl;
            hay_disponible = true;
        }
    }
}

void Biblioteca::ordenar_titulo() {
    sort(libros.begin(), libros.end(), [](const Libro& a, const Libro& b) {
        return a.get_titulo() < b.get_titulo(); 
    });
}

void Biblioteca::ordenar_anio() {
    sort(libros.begin(), libros.end(), [](const Libro& a, const Libro& b) {
        return a.get_anio_publicacion() < b.get_anio_publicacion();
    });
}


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

Libro* Biblioteca::buscar_isbn(const string& isbn) {
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_isbn() == isbn) {
            return &libros[i]; 
        }
    }
    return nullptr; 
}

vector<Libro*> Biblioteca::buscar_autor(const string& autor) {
    vector<Libro*> encontrados;
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_autor() == autor) {
            encontrados.push_back(&libros[i]);
        }
    }
    return encontrados;
}

vector<Libro*> Biblioteca::buscar_genero(const string& genero) {
    vector<Libro*> encontrados;
    for (size_t i = 0; i < libros.size(); i++) {
        if (libros[i].get_genero() == genero) {
            encontrados.push_back(&libros[i]);
        }
    }
    return encontrados;
}

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
