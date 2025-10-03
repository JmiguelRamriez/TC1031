/*
 * Main.cpp
 *
 *  Created on: 02/10/2025
 *      Author: Jose Miguel Ramirez Gutierrez A01712628
 */

#include <iostream>
#include <string>
#include "Biblioteca.h"
#include "Libro.h"

using namespace std;

// Función que limpia la consola según el sistema operativo
/*
 * limpiar_consola() - Limpia la pantalla de la consola.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Ejecuta el comando apropiado para limpiar la consola según
 * el sistema operativo. En Windows usa "cls" y en Unix/Linux usa "clear".
 * La complejidad es constante ya que solo ejecuta un comando del sistema.
 */
void limpiar_consola() {
    #ifdef _WIN32
        system("cls"); // Comando para limpiar la consola en Windows
    #else
        system("clear"); // Comando para limpiar la consola en Unix/Linux
    #endif
}

// Función que pausa la ejecución hasta que el usuario presione Enter
/*
 * pausar() - Pausa la ejecución hasta que el usuario presione Enter.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Limpia el buffer de entrada y espera a que el usuario presione
 * Enter antes de continuar. La operación es de tiempo constante.
 */
void pausar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(); // Limpia el buffer
    cin.get();    // Espera la tecla Enter
}

// Menú principal
/*
 * Menu() - Muestra el menú principal de opciones.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Imprime el menú de opciones disponibles en la consola.
 * La operación es de tiempo constante ya que solo imprime texto fijo.
 */
void Menu() {
    cout << "1. Mostrar todos los libros disponibles" << endl;
    cout << "2. Pedir prestado un libro" << endl;
    cout << "3. Devolver libros" << endl;
    cout << "4. Ordenar los libros" << endl;
    cout << "5. Buscar los libros" << endl;
    cout << "6. SALIR y Guardar" << endl;
    cout << "Elige una opcion: ";
}

// Submenú para ordenar libros
/*
 * Ordenar() - Muestra las opciones de ordenamiento.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Imprime el submenú con las opciones para ordenar libros.
 * Operación de tiempo constante.
 */
void Ordenar() {
    cout << "1. Ordenar por titulo" << endl;
    cout << "2. Ordenar por anio" << endl;
    cout << "Elige una opcion: ";
}

// Submenú para buscar libros
/*
 * Buscar() - Muestra las opciones de búsqueda.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Imprime el submenú con las opciones para buscar libros.
 * Operación de tiempo constante.
 */
void Buscar() {
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
 * Descripción: Llama a la función mostrar_todos_libros() de la biblioteca,
 * que recorre y muestra todos los libros. La complejidad es lineal respecto
 * al número de libros en la biblioteca.
 */
void opcionMostrarLibros(Biblioteca &biblio) {
    cout << "\n--- Libros en la biblioteca ---" << endl;
    biblio.mostrar_todos_libros();
    pausar();
}

// Opción 2: Pedir prestado un libro (reduce cantidad disponible en 1)
/*
 * opcionPrestarLibro() - Gestiona el préstamo de un libro.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el libro está al inicio)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Solicita el título del libro al usuario y llama a prestar_libro().
 * La complejidad depende de la búsqueda lineal del libro en el vector.
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
 * opcionDevolverLibro() - Gestiona la devolución de un libro.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el libro está al inicio)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Solicita el título del libro al usuario y llama a devolver_libro().
 * La complejidad depende de la búsqueda lineal del libro en el vector.
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
 * opcionOrdenarLibros() - Ordena los libros según el criterio elegido.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripción: Permite al usuario elegir ordenar por título o año, luego
 * ejecuta el método de ordenamiento correspondiente y muestra los resultados.
 * La complejidad es O(n log n) debido al algoritmo de ordenamiento más
 * O(n) para mostrar los libros, resultando en O(n log n) total.
 */