/*
 * Libro.h
 *
 *  Created on: 02/10/2025
 *      Author: Jose Miguel Ramirez Gutierrez A01712628
 */

#ifndef LIBRO_H
#define LIBRO_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Libro {
    private:
        string titulo;
        string autor;
        string genero;
        int anio_publicacion;
        int cantidad_total;
        int cantidad_disponible;

    public:
        Libro();
        Libro(string t, string a, string g, int anio, int cant_t, int cant_d);

        string get_titulo() const;
        string get_genero() const;
        string get_autor() const;
        int get_anio_publicacion() const;
        int get_cantidad_disponible() const;
        int get_cantidad_total() const;
        
        void set_cantidad_disponible(int cant_d);
        string mostrar_info();
};

/*
 * Libro() - Constructor por defecto.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Inicializa todos los atributos del libro con valores por defecto.
 * La operación es de tiempo constante ya que solo asigna valores a las variables miembro.
 */
Libro::Libro() {
    titulo = "";
    autor = "";
    genero = "";
    anio_publicacion = 0;
    cantidad_total = 0;
    cantidad_disponible = 0;
}

/*
 * Libro() - Constructor parametrizado.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Inicializa un objeto Libro con los valores proporcionados.
 * Utiliza lista de inicialización, lo que hace la operación de tiempo constante.
 */
Libro::Libro(string t, string a, string g, int anio, int cant_t, int cant_d) :
    titulo(t), autor(a), genero(g), anio_publicacion(anio), 
    cantidad_total(cant_t), cantidad_disponible(cant_d) {}

/*
 * get_titulo() - Retorna el título del libro.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Devuelve el ttulo del libro. Es una operación de tiempo constante
 * ya que solo retorna el valor de una variable miembro.
 */
string Libro::get_titulo() const {
    return titulo;
}

/*
 * get_autor() - Retorna el autor del libro.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Devuelve el autor del libro. Operacion de tiempo constante.
 */
string Libro::get_autor() const {
    return autor;
}

/*
 * get_genero() - Retorna el género del libro.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Devuelve el género del libro. Operacion de tiempo constante.
 */
string Libro::get_genero() const {
    return genero;
}

/*
 * get_anio_publicacion() - Retorna el año de publicación del libro.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Devuelve el año de publicacion. Operación de tiempo constante.
 */
int Libro::get_anio_publicacion() const {
    return anio_publicacion;
}

/*
 * get_cantidad_disponible() - Retorna la cantidad de ejemplares disponibles.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Devuelve la cantidad de ejemplares disponibles para préstamo.
 * Operación de tiempo constante.
 */
int Libro::get_cantidad_disponible() const {
    return cantidad_disponible;
}

/*
 * get_cantidad_total() - Retorna la cantidad total de ejemplares.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Devuelve el numero total de ejemplares del libro en la biblioteca.
 * Operación de tiempo constante.
 */
int Libro::get_cantidad_total() const {
    return cantidad_total;
}

/*
 * set_cantidad_disponible() - Establece la cantidad de ejemplares disponibles.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripcion: Modifica la cantidad de ejemplares disponibles del libro.
 * Operación de tiempo constante.
 */
void Libro::set_cantidad_disponible(int cant_d) {
    cantidad_disponible = cant_d;
}

/*
 * mostrar_info() - Genera una cadena con la informacion del libro.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripcion: Construye y retorna un string con toda la informacion del libro.
 * La complejidad es lineal respecto a la longitud total de los strings concatenados,
 * debido a las múltiples operaciones de concatenación de cadenas.
 */
string Libro::mostrar_info() {
    string info = "Titulo: " + titulo + "\n";
    info += "Autor: " + autor + "\n";
    info += "Genero: " + genero + "\n";
    info += "Anio de publicacion: " + to_string(anio_publicacion) + "\n";
    info += "Disponibles: " + to_string(cantidad_disponible) + "/" + 
            to_string(cantidad_total) + "\n";
    return info;
}

#endif