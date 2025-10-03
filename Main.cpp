#include <iostream>
#include <string>
#include "Biblioteca.h"
#include "Libro.h"

using namespace std;

// -------------------------------------------------------------------
// Función que limpia la consola según el sistema operativo
// -------------------------------------------------------------------
void limpiar_consola(){
    #ifdef _WIN32
        system("cls"); // Comando para limpiar la consola en Windows
    #else
        system("clear"); // Comando para limpiar la consola en Unix/Linux
    #endif
}

// -------------------------------------------------------------------
// Función que pausa la ejecución hasta que el usuario presione Enter
// -------------------------------------------------------------------
void pausar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(); // Limpia el buffer
    cin.get();    // Espera la tecla Enter
}

// -------------------------------------------------------------------
// Menú principal
// -------------------------------------------------------------------
void Menu(){
    cout << "1. Mostrar todos los libros disponibles" << endl;
    cout << "2. Pedir prestado un libro" << endl;
    cout << "3. Devolver libros" << endl;
    cout << "4. Ordenar los libros" << endl;
    cout << "5. Buscar los libros" << endl;
    cout << "6. SALIR y Guardar" << endl;
    cout << "Elige una opcion: ";
}

// -------------------------------------------------------------------
// Submenú para ordenar libros
// -------------------------------------------------------------------
void Ordenar(){
    cout << "1. Ordenar por titulo" << endl;
    cout << "2. Ordenar por anio" << endl;
    cout << "Elige una opcion: ";
}

// -------------------------------------------------------------------
// Submenú para buscar libros
// -------------------------------------------------------------------
void Buscar(){
    cout << "1. Buscar por autor" << endl;
    cout << "2. Buscar por genero" << endl;
    cout << "3. Buscar por titulo" << endl;
    cout << "Elige una opcion: ";
}

// ===================== FUNCIONES DEL SWITCH ========================

// -------------------------------------------------------------------
// Opción 1: Mostrar todos los libros cargados en la biblioteca
// -------------------------------------------------------------------
void opcionMostrarLibros(Biblioteca &biblio) {
    cout << "\n--- Libros en la biblioteca ---" << endl;
    biblio.mostrar_todos_libros();
    pausar();
}

// -------------------------------------------------------------------
// Opción 2: Pedir prestado un libro (reduce cantidad disponible en 1)
// -------------------------------------------------------------------
void opcionPrestarLibro(Biblioteca &biblio) {
    cout << "Escribe el titulo del libro que quieres prestar: ";
    string titulo_prestar;
    getline(cin, titulo_prestar); 
    biblio.prestar_libro(titulo_prestar);
    pausar();
}

// -------------------------------------------------------------------
// Opción 3: Devolver un libro (aumenta cantidad disponible en 1)
// -------------------------------------------------------------------
void opcionDevolverLibro(Biblioteca &biblio) {
    cout << "Escribe el titulo del libro que quieres devolver: ";
    string titulo_devolver;
    getline(cin, titulo_devolver);
    biblio.devolver_libro(titulo_devolver);
    pausar();
}

// -------------------------------------------------------------------
// Opción 4: Ordenar libros (por título o año)
// -------------------------------------------------------------------
void opcionOrdenarLibros(Biblioteca &biblio) {
    int opcion_orden;
    Ordenar();
    cin >> opcion_orden;
    cin.ignore();

    if (opcion_orden == 1) {
        biblio.ordenar_titulo();
        cout << "\nLibros ordenados por titulo:\n";
    } else if (opcion_orden == 2) {
        biblio.ordenar_anio();
        cout << "\nLibros ordenados por anio:\n";
    } else {
        cout << "Opcion no valida.\n";
    }

    // Muestra lista después de ordenar
    biblio.mostrar_todos_libros();
    pausar();
}

// -------------------------------------------------------------------
// Opción 5: Buscar libros por autor, género o título
// -------------------------------------------------------------------
void opcionBuscarLibros(Biblioteca &biblio) {
    int opcion_buscar;
    Buscar();
    cin >> opcion_buscar;
    cin.ignore(); // Evitar problemas con getline

    if (opcion_buscar == 1) {
        // Buscar por autor
        cout << "Escribe el autor que quieres buscar: ";
        string autor_buscar;
        getline(cin, autor_buscar);
        vector<Libro*> encontrados = biblio.buscar_autor(autor_buscar);
        
        if (encontrados.empty()){
            cout << "No se encontraron libros de ese autor.\n";
        } else {
            cout << "\n--- Libros encontrados de " << autor_buscar << " ---\n";
            for(Libro* libro : encontrados){
                cout << libro->mostrar_info() << endl;
            }
        }

    } else if (opcion_buscar == 2) {
        // Buscar por género
        cout << "Escribe el genero que quieres buscar: ";
        string genero_buscar;
        getline(cin, genero_buscar);
        vector<Libro*> encontrados = biblio.buscar_genero(genero_buscar);

        if (encontrados.empty()){
            cout << "No se encontraron libros de ese genero.\n";
        } else {
            cout << "\n--- Libros encontrados del genero " << genero_buscar << " ---\n";
            for(Libro* libro : encontrados){
                cout << libro->mostrar_info() << endl;
            }
        }

    } else if (opcion_buscar == 3) {
        // Buscar por título
        cout << "Escribe el titulo que quieres buscar: ";
        string titulo_buscar;
        getline(cin, titulo_buscar);
        vector<Libro*> encontrados = biblio.buscar_titulo(titulo_buscar);

        if (encontrados.empty()){
            cout << "No se encontraron libros con ese titulo.\n";
        } else {
            cout << "\n--- Libros encontrados con el titulo \"" << titulo_buscar << "\" ---\n";
            for(Libro* libro : encontrados){
                cout << libro->mostrar_info() << endl;
            }
        }

    } else {
        cout << "Opcion no valida.\n";
    }
    pausar();
}


// ============================ MAIN ================================
int main() {
    Biblioteca biblio;

    // Al iniciar el programa, se cargan los libros desde un archivo CSV
    biblio.leer_csv("libros.csv");

    int opcion;
    do {
        Menu();             // Mostrar menú
        cin >> opcion;      // Leer opción
        cin.ignore();       // *** IMPORTANTE: Limpiar el buffer AQUÍ ***
        limpiar_consola();  // Limpiar pantalla

        // Selección según la opción
        switch (opcion){
            case 1: 
                opcionMostrarLibros(biblio); 
                break;
            case 2:
                opcionPrestarLibro(biblio); 
                break;
            case 3: 
                opcionDevolverLibro(biblio);
                break;
            case 4: 
                opcionOrdenarLibros(biblio);
                break;
            case 5: 
                opcionBuscarLibros(biblio);
                break;
            case 6: 
                cout << "Guardando biblioteca en libros.csv...\n";
                biblio.guardar_csv("libros.csv");
                cout << "Hasta luego!!!!\n";
                break;
            default:
                cout << "Opcion no valida. Por favor, intenta de nuevo.\n";
                pausar();
                break;
        }
    } while (opcion != 6);

    return 0;
}
