/*
 * Main.cpp
 *
 *  Created on: 03/10/2025
 *      Author: Jose Miguel Ramirez Gutierrez A01712628
 */

#include <iostream>
#include <string>
#include "Biblioteca.h"
#include "Libro.h"

using namespace std;

// Funcion que limpia la consola según el sistema operativo
/*
 * limpiar_consola() - Limpia la pantalla de la consola.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Descripcion caso: O(1)
 * Descripción: Ejecuta el comando apropiado del sistema para limpiar la consola.
 * En Windows utiliza "cls" y en sistemas Unix/Linux utiliza "clear".
 * La operación es de tiempo constante ya que solo invoca un comando del sistema operativo.
 */
void limpiar_consola(){
    #ifdef _WIN32
        system("cls"); // Comando para limpiar la consola en Windows
    #else
        system("clear"); // Comando para limpiar la consola en Unix/Linux
    #endif
}

// Funcion que pausa la ejecución hasta que el usuario presione Enter
/*
 * pausar() - Pausa la ejecución esperando entrada del usuario.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Limpia el buffer de entrada con cin.ignore() y luego espera
 * a que el usuario presione Enter mediante cin.get(). Útil para pausar el
 * programa y permitir al usuario leer información antes de continuar.
 * La operación es de tiempo constante.
 */
void pausar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(); // Limpia el buffer
    cin.get();    // Espera la tecla Enter
}

// Menu principal
/*
 * Menu() - Muestra el menú principal de opciones al usuario.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Imprime en consola las 6 opciones disponibles del sistema
 * de gestión de biblioteca. La operación es de tiempo constante ya que
 * solo imprime texto fijo predefinido.
 */
void Menu(){
    cout << "1. Mostrar todos los libros disponibles" << endl;
    cout << "2. Pedir prestado un libro" << endl;
    cout << "3. Devolver libros" << endl;
    cout << "4. Ordenar los libros" << endl;
    cout << "5. Buscar los libros" << endl;
    cout << "6. SALIR y Guardar" << endl;
    cout << "Elige una opcion: ";
}

// Submenu para ordenar libros
/*
 * Ordenar() - Muestra el submenú de opciones de ordenamiento.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Imprime las opciones disponibles para ordenar los libros:
 * por título o por año de publicación. Operación de tiempo constante.
 */
void Ordenar(){
    cout << "1. Ordenar por titulo" << endl;
    cout << "2. Ordenar por anio" << endl;
    cout << "Elige una opcion: ";
}

// Submenu para buscar libros
/*
 * Buscar() - Muestra el submenú de opciones de búsqueda.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Imprime las opciones disponibles para buscar libros:
 * por autor, género o título. Operación de tiempo constante.
 */
void Buscar(){
    cout << "1. Buscar por autor" << endl;
    cout << "2. Buscar por genero" << endl;
    cout << "3. Buscar por titulo" << endl;
    cout << "Elige una opcion: ";
}

// Opción 1: Mostrar todos los libros cargados en la biblioteca
/*
 * opcionMostrarLibros() - Muestra todos los libros de la biblioteca.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcio: Invoca el método mostrar_todos_libros() de la biblioteca
 * que recorre y muestra la información de cada libro en el inventario.
 * La complejidad es lineal respecto al número de libros (n) en la biblioteca,
 * ya que debe mostrar cada uno de ellos.
 */
void opcionMostrarLibros(Biblioteca &biblio) {
    cout << "\n--- Libros en la biblioteca ---" << endl;
    biblio.mostrar_todos_libros();
    pausar();
}

// Opción 2: Pedir prestado un libro (reduce cantidad disponible en 1)
/*
 * opcionPrestarLibro() - Gestiona el préstamo de un libro al usuario.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el libro buscado está en la primera posición)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Solicita al usuario el título del libro a prestar mediante
 * getline() y luego invoca prestar_libro() que realiza una búsqueda lineal
 * en el vector de libros. La complejidad promedio es O(n) donde n es el
 * número de libros en la biblioteca.
 */
void opcionPrestarLibro(Biblioteca &biblio) {
    cout << "Escribe el titulo del libro que quieres prestar: ";
    string titulo_prestar;
    getline(cin, titulo_prestar); 
    biblio.prestar_libro(titulo_prestar);
    pausar();
}

// Opción 3: Devolver un libro (aumenta cantidad disponible en 1)
/*
 * opcionDevolverLibro() - Gestiona la devolución de un libro prestado.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el libro está en la primera posición)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Solicita al usuario el título del libro a devolver y luego
 * invoca devolver_libro() que busca el libro en el vector. Si lo encuentra
 * y la cantidad disponible es menor al total, incrementa la disponibilidad.
 * La búsqueda lineal resulta en complejidad O(n) promedio.
 */
void opcionDevolverLibro(Biblioteca &biblio) {
    cout << "Escribe el titulo del libro que quieres devolver: ";
    string titulo_devolver;
    getline(cin, titulo_devolver);
    biblio.devolver_libro(titulo_devolver);
    pausar();
}

// Opción 4: Ordenar libros (por título o año)
/*
 * opcionOrdenarLibros() - Ordena la colección según el criterio elegido.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripcion: Presenta un submenu para elegir el criterio de ordenamiento
 * (título o año). Utiliza el algoritmo sort de la STL que tiene complejidad
 * O(n log n). Después de ordenar, muestra todos los libros con complejidad
 * adicional O(n), resultando en O(n log n) + O(n) = O(n log n) total.
 */
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


// Opción 5: Buscar libros por autor, género o título
/*
 * opcionBuscarLibros() - Busca libros según diferentes criterios de búsqueda.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n * m) (para búsqueda por título)
 * Descripcion: Presenta un submenú con tres opciones de búsqueda:
 * 1) Por autor: Busca todos los libros de un autor especifico - O(n)
 * 2) Por género: Busca todos los libros de un género especifico - O(n)
 * 3) Por título: Busca libros cuyo título contenga una subcadena - O(n * m)
 *    donde m es la longitud promedio de los títulos debido al uso de find().
 * En todos los casos, muestra los resultados encontrados al usuario.
 */
void opcionBuscarLibros(Biblioteca &biblio) {
    int opcion_buscar;
    Buscar();
    cin >> opcion_buscar;
    cin.ignore();

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
/*
 * main() - Función principal del programa de gestión de biblioteca.
 * Complejidad temporal:
 * - Mejor caso: O(n) (carga del archivo CSV y salida inmediata)
 * - Caso promedio: Variable según operaciones ejecutadas
 * - Peor caso: Variable según operaciones ejecutadas
 * Descripcion: Inicializa el sistema de biblioteca cargando los datos desde
 * un archivo CSV con complejidad O(n * m). Presenta un menú interactivo en
 * un ciclo do-while que permite al usuario realizar diferentes operaciones
 * hasta que elija salir (opción 6). Al salir, guarda los cambios en el
 * archivo CSV con complejidad O(n). El cin.ignore() después de leer la opción
 * es crucial para limpiar el buffer y evitar problemas con getline() en las
 * funciones subsecuentes. La complejidad total depende de las operaciones
 * que el usuario ejecute durante la sesión.
 */
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