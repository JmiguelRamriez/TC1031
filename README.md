# Proyecto TC1031
Proyecto de Biblioteca 

Este proyecto implementa un sistema básico de gestión para una biblioteca utilizando C++. El sistema está estructurado en tres componentes principales: la clase Libro, la clase Biblioteca y un archivo Main.cpp que actúa como demostración.

En su estado actual, el programa tiene las siguientes funcionalidades:

Gestión de Libros: La clase Libro encapsula toda la información relevante de un libro, como ISBN, título, autor, año, género y la cantidad de ejemplares.

Catálogo Central: La clase Biblioteca maneja un catálogo de libros almacenado en un std::vector, funcionando como el núcleo del sistema.

Operaciones del Catálogo: Se pueden agregar nuevos libros al catálogo y mostrar la lista completa de libros o solo aquellos con ejemplares disponibles.

Búsqueda: El sistema permite buscar libros por ISBN (devuelve un único resultado), autor, género o año de publicación (devuelven múltiples resultados).

Préstamos y Devoluciones: Se ha implementado la lógica para prestar y devolver libros, actualizando la cantidad de ejemplares disponibles.

Ordenamiento: El catálogo de la biblioteca puede ser ordenado por título (alfabéticamente) o por año de publicación (ascendente).

El archivo Main.cpp inicializa una biblioteca con 5 libros de ejemplo y ejecuta todas las funciones mencionadas para demostrar que el sistema es funcional.

