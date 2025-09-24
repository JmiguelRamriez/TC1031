#include <iostream>
#include "Biblioteca.h"
#include "Libro.h"
using namespace std;

int main() {
    Biblioteca biblio;

    // Crear libros
    Libro l1("111", "El Principito", "Saint-Exupéry", "Ficcion", 1943, 5, 5);
    Libro l2("222", "Cien Anios de Soledad", "Gabriel Garcia Marquez", "Realismo magico", 1967, 3, 3);
    Libro l3("333", "1984", "George Orwell", "Distopia", 1949, 4, 4);

    // Agregar libros a la biblioteca
    biblio.agregar_libro(l1);
    biblio.agregar_libro(l2);
    biblio.agregar_libro(l3);

    // Mostrar todos los libros
    cout << "\n Lista de libros en la biblioteca:\n";
    biblio.mostrar_todos_libros();

    cout << "=======================================" << endl;
    // Buscar por ISBN
    cout << "\n Buscando ISBN '222'...\n";
    Libro* encontrado = biblio.buscar_isbn("222");
    if (encontrado != nullptr) {
        cout << "Encontrado: " << encontrado->get_titulo() << endl;
    } else {
        cout << "No se encontro libro con ese ISBN\n";
    }

    cout << "=======================================" << endl;

    // Buscar por autor
    cout << "\n Buscando por autor 'George Orwell'...\n";
    vector<Libro*> por_autor = biblio.buscar_autor("George Orwell");
    for (auto* l : por_autor) {
        cout << "Encontrado: " << l->get_titulo() << endl;
    }

    cout << "=======================================" << endl;

    // Buscar por genero
    cout << "\n Buscando por genero 'Ficcion'...\n";
    vector<Libro*> por_genero = biblio.buscar_genero("Ficcion");
    for (auto* l : por_genero) {
        cout << "Encontrado: " << l->get_titulo() << endl;
    }

    cout << "=======================================" << endl;

    // Buscar por anio
    cout << "\n Buscando libros del anio 1949...\n";
    vector<Libro*> por_anio = biblio.bucar_anio(1949);
    for (auto* l : por_anio) {
        cout << "Encontrado: " << l->get_titulo() << endl;
    }
    
    cout << "=======================================" << endl;

    cout << "Ordenar libros por titulo" << endl;
    biblio.ordenar_titulo();
    biblio.mostrar_disponibles();
    
    cout << "Ordenar libros por anio"<<endl;
    biblio.ordenar_anio();
    biblio.mostrar_disponibles();

    return 0;
}
