#ifndef LIBRO_H
#define LIBRO_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Libro {
    private:
        string isbn;
        string titulo;
        string autor;
        string genero;
	int anio_publicacion;
        int cantidad_total;
        int cantidad_disponible;

    public:
        Libro();
        Libro(string i, string t, string a, string g, int anio, int cant_t, int cant_d );

        string get_isbn();
        string get_titulo() const;
        string get_genero();
        string get_autor();
        int get_anio_publicacion()const;
        int get_cantidad_disponible();
        int get_cantidad_total();
        
        void set_cantidad_disponible(int cant_d);
        string mostrar_info();
};

Libro::Libro(){
    isbn = "";
    titulo = "";
    autor = "";
    genero = "";
    anio_publicacion = 0;
    cantidad_total = 0;
    cantidad_disponible = 0;
}

Libro::Libro(string i, string t, string a, string g, int anio, int cant_t, int cant_d ):
isbn(i), titulo(t), autor(a), genero(g), anio_publicacion(anio), cantidad_total(cant_t), cantidad_disponible(cant_d){};

string Libro::get_isbn(){
    return isbn;
}

string Libro::get_titulo() const {
        return titulo;
}

string Libro::get_autor(){
    return autor;
}

string Libro::get_genero(){
    return genero;
}

int Libro::get_anio_publicacion() const{
    return anio_publicacion;
}

int Libro::get_cantidad_disponible(){
    return cantidad_disponible;
}

int Libro::get_cantidad_total(){
        return cantidad_total;
}

void Libro::set_cantidad_disponible(int cant_d){
       cantidad_disponible = cant_d;
}
string Libro::mostrar_info() {
    string info = "ISBN: " + isbn + "\n";
    info += "Titulo: " + titulo + "\n";
    info += "Autor: " + autor + "\n";
    info += "Genero: " + genero + "\n";
    info += "Anio de publicacion: " + to_string(anio_publicacion) + "\n";
    info += "Disponibles: " + to_string(cantidad_disponible) + "/" + to_string(cantidad_total) + "\n";
        return info;
}


#endif
