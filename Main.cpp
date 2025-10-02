//Nombre: José Miguel Ramírez
//Matricula: A01712628

#include <iostream>
#include "Biblioteca.h"
#include "Libro.h"

using namespace std;

int main() {
    Biblioteca biblio;

    biblio.leer_csv("libros.csv"); // Carga los libros al iniciar el programa

    int opcion;
    bool continuar = true;

    while (continuar) {
        cout << "\nMenu de la Biblioteca:" << endl;
        cout << "1. Mostrar todos los libros" << endl;
        cout << "2. Prestar un libro" << endl;
        cout << "3. Devolver un libro" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (opcion) {
            case 1: {
                cout << "\n--- Libros en la biblioteca ---" << endl;
                biblio.mostrar_todos_libros();
                break;
            }
            case 2: {
                string titulo;
                cout << "Ingrese el titulo del libro a prestar: ";
                cin.ignore(); // Limpiar el buffer del teclado
                getline(cin, titulo);
                biblio.prestar_libro(titulo);
                break;
            }
            case 3: {
                string titulo;
                cout << "Ingrese el titulo del libro a devolver: ";
                cin.ignore();
                getline(cin, titulo);
                biblio.devolver_libro(titulo);
                break;
            }
            case 4: {
                biblio.guardar_csv("libros.csv");
                cout << "Guardando cambios y saliendo..." << endl;
                continuar = false;
                break;
            }
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    }

    return 0;
}
