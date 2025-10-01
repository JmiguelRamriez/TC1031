# Proyecto TC1031
## Sistema de Gestión de Biblioteca

Este proyecto implementa un sistema básico de gestión para una biblioteca utilizando C++. El sistema está estructurado en tres componentes principales: la clase `Libro`, la clase `Biblioteca` y un archivo `Main.cpp` que actúa como demostración.

En su estado actual, el programa tiene las siguientes funcionalidades:
* **Gestión de Libros:** La clase `Libro` encapsula toda la información relevante de un libro, como ISBN, título, autor, año, género y la cantidad de ejemplares.
* **Catálogo Central:** La clase `Biblioteca` maneja un catálogo de libros almacenado en un `std::vector`, funcionando como el núcleo del sistema.
* **Operaciones del Catálogo:** Se pueden agregar nuevos libros al catálogo y mostrar la lista completa de libros o solo aquellos con ejemplares disponibles.
* **Búsqueda:** El sistema permite buscar libros por ISBN (devuelve un único resultado), autor, género o año de publicación (devuelven múltiples resultados).
* **Préstamos y Devoluciones:** Se ha implementado la lógica para prestar y devolver libros, actualizando la cantidad de ejemplares disponibles.
* **Ordenamiento:** El catálogo de la biblioteca puede ser ordenado por **título** (alfabéticamente) o por **año de publicación** (ascendente).

El archivo `Main.cpp` inicializa una biblioteca con 5 libros de ejemplo y ejecuta todas las funciones mencionadas para demostrar que el sistema es funcional.

---

## Cómo Usar el Programa

Para compilar y ejecutar el programa, necesitarás un compilador de C++ (como g++).

1.  **Compilación:**
    Asegúrate de tener los tres archivos (`Libro.h`, `Biblioteca.h`, `Main.cpp`) en el mismo directorio. Abre una terminal y ejecuta el siguiente comando. Se usa el estándar C++11 por las funciones lambda utilizadas en el ordenamiento.
    ```bash
    g++ Main.cpp
    ```

2.  **Ejecución:**
    Una vez compilado, ejecuta el programa con el siguiente comando:
    ```bash
    ./a.out   # Para sistemas tipo Linux/macOS
    a.exe     # Para sistemas Windows
    ```

3.  **Resultados Esperados:**
    El programa imprimirá en la consola una serie de acciones: la lista completa de libros, los resultados de las búsquedas por ISBN, autor, género y año, y finalmente, mostrará la lista de libros ordenada primero por título y luego por año.

---

## Cumplimiento de Sub-competencias

### SICT0301: Evalúa los componentes

**Análisis de complejidad de los algoritmos de ordenamiento usados en el programa.**

El programa utiliza el algoritmo `std::sort` de la librería estándar de C++ (`<algorithm>`) para ordenar el catálogo de libros. Este no es un algoritmo simple, sino una implementación altamente optimizada, generalmente **Introsort (Ordenamiento introspectivo)**.

`Introsort` es un algoritmo híbrido que combina las fortalezas de tres algoritmos de ordenamiento: Quicksort, Heapsort y Insertion Sort.
* Comienza con **Quicksort** por su excelente rendimiento en el caso promedio. Su complejidad es O(n log n) en tiempo y O(log n) en espacio para la pila de recursión.
* Si la recursión de Quicksort se profundiza demasiado (lo que podría llevar a un rendimiento de O(n²)), `Introsort` cambia a **Heapsort** para garantizar la complejidad de O(n log n) en el peor de los casos.
* Para subproblemas muy pequeños (por ejemplo, menos de 16 elementos), `Introsort` cambia a **Insertion Sort**, que es más eficiente para conjuntos de datos pequeños.

Gracias a esta combinación, la complejidad de `std::sort` es:

* **Complejidad Temporal (Tiempo):**
    * **Mejor de los casos:** O(n log n)
    * **Caso Promedio:** O(n log n)
    * **Peor de los casos:** O(n log n)
* **Complejidad Espacial (Memoria):** O(log n), debido al espacio requerido por la pila de recursión de Quicksort.

---

### SICT0302: Toma decisiones

**Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.**

La selección de `std::sort` es una decisión adecuada para este problema por las siguientes razones:

1.  **Eficiencia y Escalabilidad:** Con una complejidad garantizada de O(n log n), el algoritmo es lo suficientemente rápido para manejar catálogos de bibliotecas de cualquier tamaño, desde unos pocos libros hasta miles. A diferencia de algoritmos O(n²) como el ordenamiento de burbuja, `std::sort` no se degradará significativamente a medida que la cantidad de libros aumente.

2.  **Uso de la Biblioteca Estándar:** Utilizar un algoritmo de la biblioteca estándar es una decisión de ingeniería sólida. `std::sort` está probado, depurado y optimizado por los desarrolladores del compilador. Esto evita la necesidad de "reinventar la rueda" y reduce la probabilidad de introducir errores que podrían surgir al implementar un algoritmo de ordenamiento desde cero.

3.  **Flexibilidad:** El problema requiere ordenar por diferentes criterios (título y año). `std::sort` es ideal para esto, ya que permite pasar una **función de comparación personalizada**. Este enfoque demuestra el uso **correcto y avanzado** del algoritmo, ya que se adapta fácilmente a las necesidades específicas del problema sin requerir cambios estructurales. La selección y aplicación de `std::sort` son, por lo tanto, óptimas para los requisitos del proyecto.

---
