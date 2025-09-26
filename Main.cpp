//Nombre: José Miguel Ramírez
//Matricula: A01712628


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
    Libro l4("444", "Don Quijote de la Mancha", "Miguel de Cervantes", "Clasico", 1605, 2, 2);
    Libro l5("555", "Orgullo y Prejuicio", "Jane Austen", "Romance", 1813, 6, 6);

    // Agregar libros a la biblioteca
    biblio.agregar_libro(l1);
    biblio.agregar_libro(l2);
    biblio.agregar_libro(l3);
    biblio.agregar_libro(l4);
    biblio.agregar_libro(l5);


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
    for (int i = 0; i < por_autor.size(); i++) {
        cout << "Encontrado: " << por_autor[i]->get_titulo() << endl;
    }

    cout << "=======================================" << endl;

    // Buscar por genero
    cout << "\n Buscando por genero 'Ficcion'...\n";
    vector<Libro*> por_genero = biblio.buscar_genero("Ficcion");
    for (int i = 0; i < por_genero.size(); i++) {
        cout << "Encontrado: " << por_genero[i]->get_titulo() << endl;
    }

    cout << "=======================================" << endl;

    // Buscar por anio
    cout << "\n Buscando libros del anio 1949...\n";
    vector<Libro*> por_anio = biblio.bucar_anio(1949);
    for (int i = 0; i < por_anio.size(); i++) {
        cout << "Encontrado: " << por_anio[i]->get_titulo() << endl;
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

