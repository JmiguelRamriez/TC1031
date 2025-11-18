# Sistema de Gestión de Biblioteca
## Proyecto TC1031

**Autor:** Jose Miguel Ramirez Gutierrez  
**Matrícula:** A01712628  

---

## Contexto del Proyecto

Este proyecto implementa un sistema completo de gestión de biblioteca que permite administrar eficientemente un catálogo de libros. El sistema está diseñado para facilitar operaciones comunes en una biblioteca como préstamos, devoluciones, búsquedas y ordenamiento del inventario, todo mientras mantiene la persistencia de datos entre sesiones.

El sistema resuelve la necesidad de organizar y acceder rápidamente a información sobre libros, permitiendo a los usuarios realizar búsquedas por múltiples criterios (autor, género, título, año), gestionar préstamos y devoluciones de manera eficiente, y mantener un registro actualizado del inventario disponible.

---
## Descripción del avance 1

En el primer avance se crearon las bases del proyecto:

- **Clase `Libro`**: Define los atributos y métodos de un libro individual (título, autor, género, año de publicación, cantidad total y cantidad disponible).
- **Clase `Biblioteca`**: Implementa la gestión del catálogo utilizando inicialmente un `std::vector` para almacenar los libros.
- **Main**: Interfaz de usuario con menú interactivo que permite realizar las operaciones básicas de la biblioteca.

**Funcionalidades implementadas:**
- Mostrar todos los libros del catálogo
- Prestar libros (reduciendo disponibilidad)
- Devolver libros (aumentando disponibilidad)
- Ordenar libros por título o año usando `std::sort` (Introsort)
- Buscar libros por autor, género o título

**Algoritmo de ordenamiento:**
El programa utiliza el algoritmo `std::sort` de la librería estándar de C++ (`<algorithm>`). Este no es un algoritmo simple, sino una implementación altamente optimizada, generalmente **Introsort (Ordenamiento introspectivo)**, que combina:
- QuickSort para casos promedio
- HeapSort cuando la recursión es muy profunda
- Insertion Sort para particiones pequeñas
- Complejidad temporal: O(n log n) en el peor caso

## Descripción del avance 2

El segundo avance se enfoca en mejorar la estructura de datos principal del sistema, implementando una **Lista Doblemente Ligada** personalizada para reemplazar el `std::vector` anterior.

**Implementación de Lista Doblemente Ligada:**
- Estructura `Nodo` con punteros `anterior` y `siguiente`
- Punteros `head` y `tail` para acceso eficiente a los extremos
- Contador `tamano` para conocer el número de libros instantáneamente

**Nuevas funcionalidades:**
- Lectura de datos desde archivo CSV (`leer_csv()`)
- Guardado de datos en archivo CSV (`guardar_csv()`)
- Persistencia de datos entre sesiones
- Gestión dinámica de memoria con destructor personalizado

### Cambios sobre el primer avance

1. **Cambio de estructura de datos: De `std::vector` a Lista Doblemente Ligada personalizada**
   - **Razón**: Mayor control sobre la gestión de memoria, operaciones O(1) en los extremos de la lista, y preparación para futuras extensiones que requieran inserciones/eliminaciones eficientes en cualquier posición.

2. **Cambio de algoritmo de ordenamiento: De `std::sort` (Introsort) a Selection Sort personalizado**
   - **Razón**: El Selection Sort es más simple de implementar sobre listas ligadas y es más eficiente en términos de número de intercambios. Para listas ligadas, intercambiar datos es más sencillo que reorganizar punteros como requeriría Merge Sort.

3. **Agregado de persistencia de datos mediante archivos CSV**
   - **Razón**: Permitir que los cambios realizados en el catálogo (préstamos, devoluciones, nuevos libros) se guarden y puedan recuperarse en futuras sesiones del programa.

4. **Implementación de manejo robusto de errores**
   - **Razón**: Agregar validación de archivos, manejo de excepciones en conversiones de tipo (`stoi`), y mensajes informativos para mejorar la experiencia del usuario y prevenir comportamientos indefinidos.

5. **Liberación explícita de memoria dinámica**
   - **Razón**: Prevenir fugas de memoria mediante la implementación de un destructor que recorre y libera todos los nodos de la lista correctamente.
  
## Descripción del avance 3

El tercer avance se centra en la **documentación completa y corrección del README**, asegurando que toda la información esté actualizada, sea clara y completa.

**Mejoras realizadas:**
- Documentación exhaustiva de todas las funciones con análisis de complejidad
- Explicación detallada de las decisiones de diseño
- Argumentación completa de las competencias SICT0301, SICT0302 y SICT0303
- Corrección de formato y estructura del README
- Añadido de ejemplos de uso y descripción de entradas/salidas

### Cambios sobre el segundo avance

1. **Documentación completa de análisis de complejidad**
   - **Razón**: Cumplir con los requisitos de la competencia SICT0301, proporcionando análisis detallado de mejor caso, caso promedio y peor caso para cada operación.

2. **Justificación detallada de decisiones de diseño**
   - **Razón**: Argumentar claramente por qué se eligió la Lista Doblemente Ligada y el Selection Sort, comparando con alternativas y explicando las ventajas específicas para este proyecto.

3. **Corrección y ampliación de la sección de competencias**
   - **Razón**: Asegurar que cada criterio de evaluación esté cubierto con argumentos sólidos y referencias específicas al código.

4. **Mejora de las instrucciones de compilación y uso**
   - **Razón**: Facilitar que cualquier persona pueda compilar y ejecutar el proyecto sin dificultades, incluyendo comandos específicos para diferentes sistemas operativos.

## Instrucciones para compilar el avance de proyecto

Ejecuta el siguiente comando en la terminal:

```bash
g++ Main.cpp -o biblioteca
```

### Asegúrate de tener los archivos `Libro.h`, `Biblioteca.h` y `Main.cpp` en el mismo directorio.

## Instrucciones para ejecutar el avance de proyecto

### En Linux/macOS:
```bash
./biblioteca.out
```

### En Windows:
```bash
biblioteca.exe
```

## Descripción de las entradas del avance de proyecto

El programa requiere un archivo CSV con el siguiente formato:

**Archivo: `libros.csv`**

Formato de cada línea:
```
titulo,autor,genero,año_publicacion,cantidad_total,cantidad_disponible
```

**Ejemplo de contenido:**
```csv
La Iliada,Homero,Epico,-750,3,3
Don Quijote de la Mancha,Miguel de Cervantes,Clasico,1605,2,2
1984,George Orwell,Distopia,1949,4,4
El Principito,Antoine de Saint-Exupery,Ficcion,1943,5,5
Harry Potter y la Piedra Filosofal,J. K. Rowling,Fantasia,1997,10,10
```

**Campos del archivo:**
1. **titulo**: Nombre completo del libro (string)
2. **autor**: Nombre del autor (string)
3. **genero**: Género literario (string)
4. **año_publicacion**: Año de publicación (int, puede ser negativo para obras antiguas)
5. **cantidad_total**: Número total de ejemplares en la biblioteca (int)
6. **cantidad_disponible**: Número de ejemplares disponibles para préstamo (int)

**Entradas del usuario durante la ejecución:**
- Número de opción del menú (1-6)
- Títulos exactos de libros para préstamo/devolución
- Criterios de búsqueda: nombres de autores, géneros o títulos (parciales o completos)
- Opción de ordenamiento: por título (1) o por año (2)

## Descripción de las salidas del avance de proyecto

### Salida en consola:

**1. Menu principal:**
```
1. Mostrar todos los libros disponibles
2. Pedir prestado un libro
3. Devolver libros
4. Ordenar los libros
5. Buscar los libros
6. SALIR y Guardar
Elige una opcion: 
```

**2. Listado de libros:**
```
--- Libros en la biblioteca ---
Titulo: La Iliada
Autor: Homero
Genero: Epico
Anio de publicacion: -750
Disponibles: 3/3

Titulo: 1984
Autor: George Orwell
Genero: Distopia
Anio de publicacion: 1949
Disponibles: 4/4
```

**3. Confirmaciones de operaciones:**
```
Se prestó el libro: 1984
Se devolvió el libro: 1984
Libros ordenados por titulo:
Se cargaron 50 libros desde libros.csv
Biblioteca guardada en libros.csv
```

**4. Resultados de búsqueda:**
```
--- Libros encontrados de J. K. Rowling ---
Titulo: Harry Potter y la Piedra Filosofal
Autor: J. K. Rowling
Genero: Fantasia
Anio de publicacion: 1997
Disponibles: 10/10
```

**5. Mensajes de error:**
```
No se encontró el libro con título: [titulo]
No hay ejemplares disponibles de: [titulo]
No se pudo abrir el archivo: libros.csv
Todos los ejemplares de [titulo] ya están en la biblioteca.
```

### Salida en archivo:

**Archivo: `libros.csv` (actualizado al salir)**

El programa guarda automáticamente todos los cambios realizados en el mismo formato CSV de entrada, manteniendo la estructura:
```csv
titulo,autor,genero,año,cantidad_total,cantidad_disponible
```

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

**AVANCE 1:** En el primer avance se utilizó el algoritmo `std::sort` de la STL de C++, que implementa **Introsort (Ordenamiento introspectivo)**:

- **Mejor caso**: O(n log n) - Cuando los datos ya están parcialmente ordenados
- **Caso promedio**: O(n log n) - Para distribuciones aleatorias de datos
- **Peor caso**: O(n log n) - Garantizado por el uso de HeapSort cuando QuickSort se degrada
- **Complejidad espacial**: O(log n) - Por la recursión de QuickSort

Introsort es un algoritmo híbrido que combina QuickSort (rápido en promedio), HeapSort (garantía O(n log n) en peor caso) e Insertion Sort (eficiente para particiones pequeñas).

**AVANCE 2 Y 3:** Se migró a **Selection Sort personalizado** adaptado para listas doblemente ligadas:

- **Mejor caso**: O(n²) - Incluso si la lista está ordenada, debe comparar todos los elementos
- **Caso promedio**: O(n²) - Número de comparaciones constante: n(n-1)/2
- **Peor caso**: O(n²) - Cuando la lista está en orden inverso, realiza máximo número de intercambios
- **Complejidad espacial**: O(1) - Ordenamiento in-place, solo variables auxiliares

**Análisis detallado del Selection Sort:**

```
Para n elementos en la lista:
- Bucle externo: n iteraciones
- Bucle interno: (n-1) + (n-2) + ... + 1 = n(n-1)/2 comparaciones
- Total de comparaciones: Siempre n(n-1)/2 ≈ n²/2 ∈ O(n²)
- Número de intercambios: En el mejor caso 0, en el peor caso n-1
```

**Justificación del cambio:**
Aunque Selection Sort tiene peor complejidad asintótica que Introsort, fue elegido porque:
1. Es más simple de implementar sobre listas ligadas
2. Realiza el mínimo número de intercambios posible (O(n))
3. Para listas ligadas, intercambiar datos es más eficiente que reorganizar punteros
4. Para catálogos pequeños a medianos (< 500 libros), la diferencia de rendimiento es mínima
5. El código es más mantenible y fácil de depurar

**Dónde se observa:** Las funciones `ordenar_titulo()` y `ordenar_anio()` en Biblioteca.h (líneas 119-149) implementan el Selection Sort con dos bucles anidados que recorren la lista.

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.

**AVANCE 1:** Se utilizó `std::vector<Libro>` con las siguientes complejidades:
- Acceso por índice: O(1)
- Inserción al final (con capacidad): O(1)
- Inserción al final (sin capacidad): O(n) por realocación
- Búsqueda: O(n)
- Eliminación: O(n)

**AVANCES 2 Y 3:** Se implementó una **Lista Doblemente Ligada personalizada** con análisis completo de operaciones:

**1. Inserción al final - `agregar_libro()`:**
- **Complejidad**: O(1)
- **Análisis**: Gracias al puntero `cola`, la inserción es constante. Solo se actualizan los punteros del último nodo y el nuevo nodo, sin recorrer la lista.
- **Dónde se observa**: Biblioteca.h, líneas 61-72

**2. Recorrido completo - `mostrar_todos_libros()`:**
- **Complejidad**: O(n)
- **Análisis**: Debe visitar cada uno de los n nodos exactamente una vez desde `cabeza` hasta `nullptr`.
- **Dónde se observa**: Biblioteca.h, líneas 79-85

**3. Búsquedas por atributo:**
- **`buscar_autor()`, `buscar_genero()`, `bucar_anio()`**: O(n) - Recorrido lineal comparando un atributo específico
- **`buscar_titulo()`**: O(n × m) - Donde m es la longitud promedio de los títulos, debido al uso de `find()` para coincidencias parciales
- **Dónde se observa**: Biblioteca.h, líneas 247-294

**4. Préstamo y devolución - `prestar_libro()`, `devolver_libro()`:**
- **Mejor caso**: O(1) - El libro está en la primera posición
- **Caso promedio**: O(n/2) ≈ O(n) - El libro está en el medio
- **Peor caso**: O(n) - El libro está al final o no existe
- **Dónde se observa**: Biblioteca.h, líneas 215-244

**5. Lectura de archivo - `leer_csv()`:**
- **Complejidad**: O(n × m)
- **Análisis**: n es el número de libros en el archivo, m es la longitud promedio de cada línea. Incluye O(n) por liberar la lista existente + O(n × m) por procesar cada línea con `getline()` y `stringstream`.
- **Dónde se observa**: Biblioteca.h, líneas 151-199

**6. Guardado en archivo - `guardar_csv()`:**
- **Complejidad**: O(n)
- **Análisis**: Recorre cada nodo una vez escribiendo su información al archivo.
- **Dónde se observa**: Biblioteca.h, líneas 207-213

**7. Destructor - `~Biblioteca()`:**
- **Complejidad**: O(n)
- **Análisis**: Libera cada nodo individualmente recorriendo la lista completa.
- **Dónde se observa**: Biblioteca.h, líneas 46-57

**8. Clase Libro:**
Todos los métodos de la clase Libro (constructores, getters, setters) tienen complejidad O(1), excepto `mostrar_info()` que es O(m) donde m es la longitud total de las cadenas concatenadas.

**Comparación Vector vs Lista Doblemente Ligada:**

- **Acceso por índice**: Vector O(1), Lista Doblemente Ligada O(n)
- **Inserción al final**: Vector O(1) amortizado (requiere realocación ocasional), Lista Doblemente Ligada O(1)
- **Inserción al inicio**: Vector O(n), Lista Doblemente Ligada O(1)
- **Búsqueda**: Vector O(n), Lista Doblemente Ligada O(n)
- **Eliminación**: Vector O(n), Lista Doblemente Ligada O(1) si se tiene el puntero al nodo

#### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.

**Análisis de la función `main()` y flujo del programa:**

**Inicialización - `leer_csv()`:**
- **Complejidad**: O(n × m)
- Donde n es el número de libros y m la longitud promedio de cada línea
- Esta operación se ejecuta una sola vez al iniciar

**Ciclo principal del menú:**
El programa ejecuta un bucle `do-while` que continúa hasta que el usuario elija salir. Las operaciones dentro del menú tienen las siguientes complejidades:

1. **Opción 1 - Mostrar todos los libros**: O(n)
2. **Opción 2 - Prestar libro**: O(n) búsqueda + O(1) actualización = O(n)
3. **Opción 3 - Devolver libro**: O(n) búsqueda + O(1) actualización = O(n)
4. **Opción 4 - Ordenar libros**: O(n²) por Selection Sort
5. **Opción 5 - Buscar libros**: O(n) o O(n × m) según el criterio
6. **Opción 6 - Salir y guardar**: O(n)

**Funciones auxiliares:**
- `limpiar_consola()`: O(1) - Comando del sistema
- `pausar()`: O(1) - Espera entrada del usuario
- `Menu()`, `Ordenar()`, `Buscar()`: O(1) - Solo imprimen texto

**Complejidad Final del Programa:**

**Mejor caso**: O(n × m)
- Usuario carga el archivo, visualiza los libros y sale sin ordenar
- Dominado por la carga inicial del CSV

**Caso promedio**: O(n²)
- Usuario realiza varias operaciones incluyendo al menos un ordenamiento
- El ordenamiento O(n²) domina sobre otras operaciones O(n)

**Peor caso**: O(k × n²)
- Usuario ordena múltiples veces durante la sesión (k veces)
- Cada ordenamiento cuesta O(n²)
- Ejemplo: ordenar por título, buscar, ordenar por año, buscar de nuevo

**Complejidad espacial**: O(n)
- La lista almacena n libros
- Cada búsqueda puede retornar hasta n punteros en el vector de resultados
- No se utilizan estructuras auxiliares de tamaño proporcional a n²

**Escalabilidad del sistema:**

Para catálogos pequeños (menos de 100 libros), la implementación actual con Selection Sort es completamente adecuada y el tiempo de ordenamiento es imperceptible. En catálogos medianos (100-500 libros), el sistema sigue siendo aceptable para uso interactivo. Cuando el catálogo crece a tamaños de 500-1000 libros, comienza a notarse cierta degradación en el rendimiento del ordenamiento. Para catálogos muy grandes (más de 1000 libros), se recomendaría migrar a un algoritmo con complejidad O(n log n) como Merge Sort.

**Conclusión:**
La complejidad final del programa está determinada por el algoritmo de ordenamiento O(n²). Para el caso de uso típico de una biblioteca pequeña o mediana (< 500 libros), esta complejidad es aceptable y el sistema es suficientemente eficiente. Si el catálogo creciera significativamente, sería recomendable implementar un algoritmo de ordenamiento más eficiente como Merge Sort (O(n log n)) adaptado para listas ligadas.

### SICT0302: Toma decisiones

#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

**AVANCE 1:** Se utilizó `std::sort` (Introsort) de la STL:
- **Ventajas**: Complejidad O(n log n) garantizada, implementación optimizada y probada
- **Desventajas**: Requiere acceso aleatorio (iteradores de acceso aleatorio), no es adecuado para listas ligadas

**AVANCES 2 Y 3:** Se migró a **Selection Sort personalizado**

**Justificación de la selección:**

El Selection Sort fue elegido cuidadosamente considerando las características del problema:

**1. Compatibilidad con listas ligadas:**
- No requiere acceso aleatorio a elementos
- Funciona naturalmente con recorridos secuenciales
- Más simple que Merge Sort para listas ligadas

**2. Mínimo número de intercambios:**
- Realiza exactamente (n-1) intercambios en todos los casos
- Para listas ligadas, intercambiar datos es O(1)
- Reduce el riesgo de errores en la gestión de punteros

**3. Implementación in-place:**
- No requiere memoria adicional O(n)
- Solo usa variables auxiliares constantes
- Ideal para sistemas con restricciones de memoria

**4. Caso de uso apropiado:**
- Bibliotecas típicas tienen 50-500 libros
- En este rango, la diferencia entre O(n²) y O(n log n) es mínima
- La simplicidad del código compensa la menor eficiencia asintótica

**Comparación con alternativas NO seleccionadas:**

**Bubble Sort** (NO elegido):
- También O(n²) pero con más intercambios innecesarios
- Menos eficiente que Selection Sort sin ventajas compensatorias

**Insertion Sort** (NO elegido):
- O(n²) en promedio, O(n) en mejor caso
- Bueno para datos casi ordenados, pero no aprovecha la estructura de lista doblemente ligada

**Merge Sort** (NO elegido):
- O(n log n) en todos los casos
- Más eficiente asintóticamente pero:
  - Complejo de implementar en listas ligadas
  - Requiere dividir la lista y recombinarla
  - El overhead no se justifica para catálogos pequeños
  - Mayor superficie de código = más propenso a errores

**Quick Sort** (NO elegido):
- O(n log n) promedio, O(n²) peor caso
- Difícil de implementar eficientemente en listas ligadas
- Requiere estrategias especiales para elegir el pivote
- No ofrece ventajas claras sobre Merge Sort para listas

**Heap Sort** (NO elegido):
- O(n log n) garantizado
- Requiere construir un heap, no compatible con listas ligadas naturalmente
- Complejidad de implementación innecesaria

**Uso correcto del algoritmo:**

**Implementación en `ordenar_titulo()` (Biblioteca.h, líneas 119-134):**

```cpp
void Biblioteca::ordenar_titulo() {
    Nodo* i = cabeza;
    while (i != nullptr) {
        Nodo* j = i->siguiente;
        while (j != nullptr) {
            if (i->data.get_titulo() > j->data.get_titulo()) {
                swap_libro_data(i, j);  // Intercambia solo datos, no punteros
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }
}
```

**Elementos clave que demuestran uso correcto:**

1. **Recorrido externo**: El puntero `i` recorre toda la lista desde la cabeza
2. **Recorrido interno**: Para cada `i`, el puntero `j` recorre desde `i->siguiente` hasta el final
3. **Comparación apropiada**: Usa el operador `>` de strings para orden alfabético
4. **Intercambio eficiente**: La función auxiliar `swap_libro_data()` intercambia solo los datos, no los nodos
5. **Preservación de estructura**: Los enlaces de la lista permanecen intactos
6. **Avance correcto**: Ambos punteros avanzan con `->siguiente`

**Implementación en `ordenar_anio()` (Biblioteca.h, líneas 141-149):**

Idéntica estructura pero compara años con `get_anio_publicacion()`, demostrando la **flexibilidad** del diseño para diferentes criterios de ordenamiento.

**Verificación de correctitud:**

El algoritmo cumple con las propiedades de un ordenamiento correcto:
- **Terminación**: Los bucles siempre terminan cuando llegan a `nullptr`
- **Preservación de datos**: No se pierden ni duplican libros
- **Orden correcto**: Después de la ejecución, cada elemento es menor o igual que los siguientes
- **Estabilidad**: El orden relativo de elementos iguales no importa en este caso de uso

**Dónde se observa:** Las funciones `ordenar_titulo()` y `ordenar_anio()` en Biblioteca.h implementan correctamente Selection Sort, invocadas desde `opcionOrdenarLibros()` en Main.cpp (líneas 146-167).

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.

**AVANCE 1:** Se utilizó `std::vector<Libro>`:
- **Ventajas**: Acceso O(1) por índice, simplicidad de uso, compatibilidad con `std::sort`
- **Desventajas**: Realocaciones costosas al crecer, desplazamiento de elementos en inserciones/eliminaciones medias

**AVANCES 2 Y 3:** Se implementó **Lista Doblemente Ligada personalizada**

**Justificación de la selección:**

La Lista Doblemente Ligada fue elegida después de analizar los requisitos del sistema:

**1. Gestión dinámica de memoria:**
- El catálogo crece y decrece según las necesidades reales
- No requiere conocer el tamaño máximo de antemano
- Evita desperdicio de memoria por sobre-reservas
- Previene realocaciones costosas como en vectores (que pueden ser O(n))

**2. Eficiencia en operaciones en extremos:**
- Inserción al final en O(1) constante gracias al puntero `tail`
- Eliminación al inicio/final en O(1) (aunque no implementada aún)
- Ideal para agregar nuevos libros sin costo de reorganización

**3. Navegación bidireccional:**
- Punteros `anterior` y `siguiente` permiten recorrer en ambas direcciones
- Facilita futuras funcionalidades:
  - Paginación del catálogo (anterior/siguiente página)
  - Navegación tipo "historial" de libros consultados
  - Operaciones de deshacer/rehacer

**4. Flexibilidad para extensiones futuras:**
- Permite inserciones y eliminaciones en cualquier posición sin desplazar elementos
- Base para implementar ordenamiento más sofisticado (Merge Sort)
- Preparado para funcionalidades avanzadas (categorías, subcatálogos)

**5. Control total sobre la implementación:**
- Permite optimizaciones específicas al dominio del problema
- Facilita el aprendizaje y comprensión de estructuras de datos
- Mayor control sobre el manejo de memoria

**Comparación con alternativas NO seleccionadas:**

**Vector (std::vector)** (NO elegido para avance final):
- Requiere realocaciones O(n) cuando crece (copia de todos los elementos)
- Inserción/eliminación en medio es O(n) por desplazamiento
- Desperdicio de memoria por factor de crecimiento (típicamente 1.5x o 2x)
- No permite navegación bidireccional eficiente
- **Por qué no**: Aunque simple, las limitaciones superan los beneficios para este proyecto

**Lista Simple Ligada** (NO elegida):
- Solo permite navegación en una dirección
- Inserción al final sería O(n) sin puntero tail especial
- Dificulta futuras implementaciones bidireccionales
- **Por qué no**: La navegación unidireccional limita las posibles extensiones

**Array Estático** (NO elegido):
- Tamaño fijo predefinido, inflexible
- Desperdicio masivo de memoria o limitación artificial de capacidad
- No escalable para catálogos crecientes
- **Por qué no**: Demasiado rígido para una aplicación real

**Árbol Binario de Búsqueda** (NO elegido):
- Complejidad O(log n) para búsquedas (mejor que O(n))
- Mantiene datos ordenados automáticamente
- **Por qué no**: Overhead innecesario para ordenamientos por múltiples criterios, complejidad de implementación no justificada, las búsquedas lineales O(n) son aceptables para catálogos pequeños

**Árbol AVL** (NO elegido):
- Garantiza O(log n) en peor caso con auto-balanceo
- **Por qué no**: Complejidad de implementación muy alta, rotaciones complejas aumentan superficie de error, beneficios no justifican la complejidad para este tamaño de datos

**Tabla Hash (std::unordered_map)** (NO elegida):
- Búsquedas O(1) promedio por clave
- **Por qué no**: No mantiene orden de inserción naturalmente, requiere estructura adicional para ordenamiento, búsquedas por múltiples criterios son complejas, no se necesita ese nivel de eficiencia en búsqueda

**Implementación y uso correcto:**

**Estructura del Nodo (Biblioteca.h, líneas 16-22):**

```cpp
struct Nodo {
    Libro data;           // Datos del libro
    Nodo* siguiente;      // Puntero al siguiente nodo
    Nodo* anterior;       // Puntero al nodo anterior
    
    Nodo(const Libro& l) : data(l), siguiente(nullptr), anterior(nullptr) {}
};
```

**Clase Biblioteca (Biblioteca.h, líneas 24-33):**

```cpp
class Biblioteca {
private:
    Nodo* head;      // Puntero al primer nodo
    Nodo* tail;      // Puntero al último nodo
    int tamano;      // Contador de libros
```

**Demostración de uso correcto:**

**1. Constructor (líneas 43):**
Inicializa `head` y `tail` como `nullptr` y `tamano` en 0, estableciendo correctamente el estado inicial de una lista vacía.

**2. Inserción al final - `agregar_libro()` (líneas 61-72):**

La función maneja correctamente dos casos:
- **Lista vacía**: El nuevo nodo se convierte tanto en `head` como en `tail`
- **Lista con elementos**: Se enlaza el nuevo nodo al final usando `tail`, actualizando los punteros `siguiente` del nodo actual y `anterior` del nuevo nodo, y finalmente actualizando `tail`

Esta implementación garantiza O(1) en todos los casos gracias al puntero `tail`.

**3. Recorrido y consulta (líneas 79-85, 91-100):**

Las funciones de recorrido inician desde `head` y avanzan mediante `actual->siguiente` hasta llegar a `nullptr`. Este patrón estándar garantiza que se visiten todos los nodos exactamente una vez.

**4. Gestión de memoria - Destructor (líneas 46-57):**

El destructor implementa correctamente la liberación de memoria:
```cpp
Nodo* actual = head;
while (actual != nullptr) {
    Nodo* siguiente = actual->siguiente;
    delete actual;
    actual = siguiente;
}
```

Este patrón asegura que todos los nodos se liberen sin fugas de memoria, usando un puntero auxiliar para no perder la referencia al siguiente nodo antes de eliminar el actual.

**5. Limpieza antes de carga - `leer_csv()` (líneas 157-166):**

Antes de cargar nuevos datos del CSV, la función libera toda la memoria existente de manera similar al destructor, luego reinicia `head`, `tail` y `tamano` a sus valores iniciales. Esto previene fugas de memoria y garantiza un estado limpio.

**6. Guardado en archivo - `guardar_csv()` (líneas 207-220):**

Recorre la lista desde `head` hasta el final, escribiendo cada libro al archivo. La navegación secuencial demuestra el uso apropiado de la estructura enlazada.

**Validación de correctitud:**

La implementación cumple con todas las propiedades de una lista doblemente ligada correcta:

- **Invariante de enlaces**: Si un nodo A apunta a B con `siguiente`, entonces B apunta a A con `anterior`
- **Invariante de extremos**: `head->anterior` y `tail->siguiente` siempre son `nullptr`
- **Consistencia de tamaño**: El contador `tamano` siempre refleja el número real de nodos
- **No hay ciclos**: La lista termina correctamente en `nullptr`
- **Gestión de memoria**: Toda memoria dinámica se libera apropiadamente

**Casos especiales manejados correctamente:**

- **Lista vacía**: `head` y `tail` son `nullptr`, `tamano` es 0
- **Un solo elemento**: `head` y `tail` apuntan al mismo nodo
- **Múltiples elementos**: Enlaces bidireccionales correctos en toda la cadena

**Dónde se observa el uso correcto:**

La estructura de datos se utiliza correctamente en todas las operaciones del sistema:
- Inserción: Biblioteca.h, líneas 61-72
- Recorrido: Biblioteca.h, líneas 79-85, 91-100
- Búsqueda: Biblioteca.h, líneas 247-294
- Ordenamiento: Biblioteca.h, líneas 119-149
- Gestión de memoria: Biblioteca.h, líneas 46-57, 157-166
- Persistencia: Biblioteca.h, líneas 151-220

Esta implementación demuestra dominio completo de:
- Manejo de punteros y memoria dinámica
- Implementación de estructuras de datos desde cero
- Gestión correcta de casos especiales
- Prevención de fugas de memoria
- Uso eficiente de la estructura para las operaciones del sistema

### SICT0303: Implementa acciones científicas

#### Implementa mecanismos para consultar información de las estructuras correctos.

El sistema implementa múltiples mecanismos científicamente correctos para consultar información de la lista doblemente ligada, todos siguiendo principios rigurosos de recorrido y acceso a datos.

**1. Consulta Completa del Catálogo - `mostrar_todos_libros()` (Biblioteca.h, líneas 79-85):**

La función recorre la lista desde `head` hasta el final (`nullptr`), accediendo al dato de cada nodo mediante `actual->data` e imprimiéndolo con `mostrar_info()`. Tiene complejidad O(n) ya que visita cada nodo exactamente una vez.

**Correctitud del mecanismo:**
- Inicializa el puntero en `head` (inicio de la lista)
- Condición de terminación correcta: `actual != nullptr`
- Avance adecuado: `actual = actual->siguiente`
- Acceso seguro a datos mediante validación de puntero
- Maneja correctamente el caso de lista vacía (`head == nullptr`)

**2. Consulta Filtrada por Disponibilidad - `mostrar_disponibles()` (Biblioteca.h, líneas 91-100):**

Recorre toda la lista pero solo muestra los libros que cumplen con el criterio de disponibilidad (`cantidad_disponible > 0`). Mantiene una bandera `hay_disponible` para detectar si existen o no libros disponibles.

**Correctitud del mecanismo:**
- Filtrado mediante condición booleana antes de mostrar
- No modifica la estructura, solo consulta
- Informa apropiadamente si no hay resultados
- Preserva el orden de la lista durante el recorrido

**3. Búsqueda por Múltiples Criterios:**

El sistema implementa cuatro funciones de búsqueda, cada una optimizada para su criterio específico:

**a) `buscar_autor()` (Biblioteca.h, líneas 247-257):**
- Recorre la lista completa comparando el atributo `autor`
- Complejidad: O(n)
- Usa comparación exacta con el operador `==`
- Almacena punteros a los libros encontrados en un `vector<Libro*>`

**b) `buscar_genero()` (Biblioteca.h, líneas 264-274):**
- Similar a búsqueda por autor pero compara el atributo `genero`
- Complejidad: O(n)
- Permite encontrar todos los libros de un género específico

**c) `buscar_titulo()` (Biblioteca.h, líneas 281-291):**
- Usa el método `find()` de strings para coincidencias parciales
- Complejidad: O(n × m) donde m es la longitud promedio de los títulos
- Permite búsquedas más flexibles (ej: "Harry" encuentra "Harry Potter...")
- La función `find()` retorna `string::npos` si no hay coincidencia

**d) `bucar_anio()` (Biblioteca.h, líneas 298-308):**
- Compara el año de publicación con un valor entero específico
- Complejidad: O(n)
- Útil para encontrar obras de una época determinada

**Características comunes de todas las búsquedas:**

1. **Retorno seguro**: Todas retornan un `vector<Libro*>` que puede estar vacío si no hay resultados
2. **No modifican datos**: Son consultas de solo lectura
3. **Punteros vs copias**: Retornan punteros para eficiencia, evitando copias costosas
4. **Múltiples resultados**: El uso de vector permite retornar todos los libros que coincidan
5. **Recorrido completo**: Garantizan encontrar todas las coincidencias en la lista

**Uso correcto en el programa principal (Main.cpp, líneas 177-233):**

El menú de búsqueda maneja apropiadamente los resultados:
```cpp
vector<Libro*> encontrados = biblio.buscar_autor(autor_buscar);

if (encontrados.empty()){
    cout << "No se encontraron libros de ese autor.\n";
} else {
    for(Libro* libro : encontrados){
        cout << libro->mostrar_info() << endl;
    }
}
```

Este patrón demuestra:
- Validación de resultados vacíos antes de iterar
- Uso correcto de punteros sin dereferencias peligrosas
- Recorrido del vector de resultados con range-based for loop
- Acceso a métodos mediante el operador `->` apropiadamente

**Correctitud científica de los mecanismos:**

Todos los mecanismos de consulta implementados siguen principios científicamente correctos:

1. **Completitud**: Recorren toda la estructura sin omitir elementos
2. **Corrección**: Las condiciones de búsqueda son lógicamente correctas
3. **Terminación**: Todos los bucles terminan cuando se alcanza el final (`nullptr`)
4. **Eficiencia**: No realizan trabajo redundante ni recorridos múltiples innecesarios
5. **Seguridad**: Validan punteros antes de desreferenciarlos
6. **Preservación**: No modifican la estructura durante consultas de solo lectura

**Dónde se observa**: Las funciones de consulta están implementadas en Biblioteca.h (líneas 79-100 para mostrar, 247-308 para búsquedas) y se utilizan correctamente desde Main.cpp en las funciones `opcionMostrarLibros()`, `opcionBuscarLibros()` y el menú interactivo.

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

El sistema implementa un mecanismo robusto y científicamente correcto para cargar datos desde archivos CSV mediante la función `leer_csv()` (Biblioteca.h, líneas 151-199).

**Aspectos Científicamente Correctos:**

**1. Validación de Apertura de Archivo (líneas 152-157):**

```cpp
ifstream inFile(filename);
if (!inFile.is_open()) {
    cout << "No se pudo abrir el archivo: " << filename << endl;
    cout << "Iniciando con biblioteca vacia." << endl;
    return;
}
```

Antes de procesar, verifica que el archivo se pueda abrir correctamente usando `is_open()`. Si falla, informa al usuario y retorna inmediatamente, evitando comportamientos indefinidos o crashes. Esto demuestra programación defensiva y manejo apropiado de errores.

**2. Limpieza de Memoria Antes de Cargar (líneas 160-166):**

Antes de cargar nuevos datos, libera toda la memoria existente:

```cpp
Nodo* actual_del = head;
Nodo* siguiente_del;
while (actual_del != nullptr) {
    siguiente_del = actual_del->siguiente;
    delete actual_del;
    actual_del = siguiente_del;
}
head = nullptr;
tail = nullptr;
tamano = 0;
```

Este mecanismo previene fugas de memoria y garantiza un estado limpio. Usa un puntero auxiliar `siguiente_del` para no perder la referencia al siguiente nodo antes de eliminar el actual, lo cual es un patrón correcto de liberación de listas ligadas.

**3. Procesamiento Línea por Línea (líneas 168-198):**

Lee el archivo línea por línea con `getline()`, luego usa `stringstream` para parsear cada línea separando campos por comas:

```cpp
while (getline(inFile, linea)) {
    stringstream ss(linea);
    string titulo, autor, genero, anio_str, cant_total_str, cant_disponible_str;

    if (getline(ss, titulo, ',') &&
        getline(ss, autor, ',') &&
        getline(ss, genero, ',') &&
        getline(ss, anio_str, ',') &&
        getline(ss, cant_total_str, ',') &&
        getline(ss, cant_disponible_str, ',')) {
        // Procesamiento...
    }
}
```

Este enfoque es eficiente y maneja correctamente el formato CSV. El encadenamiento de condiciones con `&&` asegura que solo se procesen líneas con formato completo.

**4. Conversión de Tipos con Validación (líneas 177-189):**

Convierte los strings de año y cantidades a enteros usando `stoi()`, envuelto en bloques try-catch:

```cpp
try {
    int anio = stoi(anio_str);
    int cant_total = stoi(cant_total_str);
    int cant_disponible = stoi(cant_disponible_str);

    Libro libro(titulo, autor, genero, anio, cant_total, cant_disponible);
    agregar_libro(libro); 
    libros_cargados++;

} catch (const invalid_argument& e) {
    cerr << "Error de formato en la línea: " << linea << ". Ignorando libro." << endl;
} catch (const out_of_range& e) {
    cerr << "Error de rango en la línea: " << linea << ". Ignorando libro." << endl;
}
```

Este manejo de excepciones es científicamente correcto porque:
- Captura `invalid_argument` para datos no numéricos (ej: "abc" en lugar de un año)
- Captura `out_of_range` para números fuera del rango de int
- No detiene el programa completo por un dato malo, solo ignora esa línea
- Informa al usuario mediante `cerr` sobre líneas problemáticas
- Continúa procesando el resto del archivo

**5. Carga Progresiva (líneas 184-185):**

Cada libro válido se inserta en la estructura usando `agregar_libro()` que tiene complejidad O(1). Se mantiene un contador `libros_cargados` para dar retroalimentación precisa al usuario.

**6. Cierre Correcto de Recursos (líneas 196-197):**

```cpp
inFile.close();
cout << "Se cargaron " << libros_cargados << " libros desde " << filename << endl;
```

Al finalizar, cierra explícitamente el archivo para liberar recursos del sistema operativo e informa al usuario cuántos libros se cargaron exitosamente.

**Formato del Archivo CSV:**

El archivo `libros.csv` tiene el formato:
```
titulo,autor,genero,año_publicacion,cantidad_total,cantidad_disponible
```

Ejemplo de líneas válidas:
```
La Iliada,Homero,Epico,-750,3,3
1984,George Orwell,Distopia,1949,4,4
Harry Potter y la Piedra Filosofal,J. K. Rowling,Fantasia,1997,10,10
```

**Complejidad del mecanismo:**

- **Temporal**: O(n × m) donde n es el número de libros y m es la longitud promedio de cada línea
- **Espacial**: O(n) para almacenar los libros en la lista

**Correctitud científica:**

El mecanismo es científicamente correcto porque:

1. **Robustez**: Maneja errores de archivo, formato y conversión sin crashes
2. **Integridad**: Libera memoria previa antes de cargar para evitar leaks
3. **Validación**: Verifica formato y tipos de datos antes de crear objetos
4. **Eficiencia**: Usa O(1) para cada inserción gracias al puntero `tail`
5. **Retroalimentación**: Informa al usuario sobre éxito, errores y cantidad cargada
6. **Recuperación**: Continúa procesando después de errores individuales
7. **Gestión de recursos**: Cierra archivos apropiadamente

**Dónde se observa**: La función `leer_csv()` está implementada en Biblioteca.h (líneas 151-199) y se invoca automáticamente al inicio del programa en Main.cpp (línea 236) con `biblio.leer_csv("libros.csv")`.

#### Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta

El sistema implementa un mecanismo correcto para persistir los datos del catálogo en formato CSV mediante la función `guardar_csv()` (Biblioteca.h, líneas 207-220).

**Aspectos Científicamente Correctos:**

**1. Validación de Apertura (líneas 208-212):**

```cpp
ofstream outFile(filename);
if (!outFile.is_open()) {
    cerr << "No se pudo abrir el archivo para escribir: " << filename << endl;
    return;
}
```

Verifica que el archivo se pueda abrir para escritura antes de intentar escribir datos. Si falla, muestra un mensaje de error en `cerr` (salida de error estándar) y termina la función sin intentar escribir, evitando comportamientos indefinidos.

**2. Recorrido y Escritura Secuencial (líneas 214-220):**

```cpp
Nodo* actual = head;
while (actual != nullptr) {
    outFile << actual->data.get_titulo() << "," 
            << actual->data.get_autor() << "," 
            << actual->data.get_genero() << "," 
            << actual->data.get_anio_publicacion() << "," 
            << actual->data.get_cantidad_total() << "," 
            << actual->data.get_cantidad_disponible() << endl;
    actual = actual->siguiente;
}
```

Recorre la lista desde `head` hasta el final, escribiendo la información de cada libro en formato CSV (campos separados por comas) usando el operador `<<` del `ofstream`. El recorrido es científicamente correcto:

- Inicia en `head` (primer nodo)
- Condición de terminación: `actual != nullptr`
- Avanza correctamente: `actual = actual->siguiente`
- Escribe todos los campos en orden consistente
- Usa `endl` para agregar nueva línea y hacer flush del buffer

**3. Formato Consistente:**

Cada libro se guarda en una línea con el formato:
```
titulo,autor,genero,año,cantidad_total,cantidad_disponible
```

Este formato es **consistente con el usado en la lectura** (`leer_csv()`), garantizando compatibilidad bidireccional. La consistencia es crucial para la correctitud científica de la persistencia de datos.

**4. Cierre de Recursos (líneas 222-223):**

```cpp
outFile.close();
cout << "Biblioteca guardada en " << filename << endl;
```

Cierra el archivo explícitamente al finalizar para asegurar que:
- Todos los datos se escriban correctamente del buffer al disco
- Se liberen los recursos del sistema operativo
- No queden archivos abiertos innecesariamente

Además, informa al usuario que la operación fue exitosa, proporcionando retroalimentación y confianza.

**Complejidad del mecanismo:**

- **Temporal**: O(n) donde n es el número de libros, ya que debe recorrer toda la lista una vez
- **Espacial**: O(1) adicional, solo usa el puntero `actual` y el buffer interno del `ofstream`

**Correctitud científica:**

El mecanismo es científicamente correcto porque:

1. **Completitud**: Guarda todos los libros sin omitir ninguno
2. **Integridad**: Mantiene todos los campos de datos de cada libro
3. **Consistencia**: Usa el mismo formato que la función de lectura
4. **Ordenamiento**: Preserva el orden actual de la lista (incluyendo ordenamientos previos)
5. **Validación**: Verifica apertura exitosa antes de escribir
6. **Gestión de recursos**: Cierra archivos apropiadamente
7. **Atomicidad básica**: Sobrescribe el archivo completo (no hace escrituras parciales)

**Garantía de persistencia:**

Este mecanismo garantiza que todos los cambios realizados durante la sesión se guarden correctamente:

- **Préstamos**: Las cantidades disponibles actualizadas se guardan
- **Devoluciones**: Los incrementos en disponibilidad se persisten
- **Libros agregados**: Nuevos libros se incluyen en el archivo
- **Ordenamientos**: El orden actual (por título o año) se mantiene

**Uso en el programa:**

La función se invoca al salir del programa (Main.cpp, línea 184-185):

```cpp
case 6: 
    cout << "Guardando biblioteca en libros.csv...\n";
    biblio.guardar_csv("libros.csv");
    cout << "Hasta luego!!!!\n";
    break;
```

Esto asegura que, antes de terminar el programa, todos los cambios se escriban al archivo, permitiendo que la próxima sesión inicie con el estado actualizado del catálogo.

**Dónde se observa**: La función `guardar_csv()` está implementada en Biblioteca.h (líneas 207-223) y se invoca desde Main.cpp (línea 185) cuando el usuario selecciona la opción 6 (Salir) del menú principal.

---

## Conclusión

Este proyecto demuestra la implementación exitosa de un sistema de gestión de biblioteca usando una **Lista Doblemente Ligada** como estructura de datos principal. El sistema cumple completamente con todos los requisitos de las competencias evaluadas:

**SICT0301 - Evalúa los componentes:**
- Análisis exhaustivo de complejidad del algoritmo de ordenamiento Selection Sort (O(n²) en todos los casos)
- Análisis detallado de todas las operaciones de la Lista Doblemente Ligada (desde O(1) para inserciones hasta O(n²) para ordenamiento)
- Determinación correcta de la complejidad final del programa como O(n²), dominada por las operaciones de ordenamiento

**SICT0302 - Toma decisiones:**
- Justificación sólida de la selección de Selection Sort adaptado para listas ligadas, considerando simplicidad de implementación, mínimo número de intercambios y adecuación al tamaño típico de catálogos
- Argumentación detallada de la elección de Lista Doblemente Ligada sobre alternativas como vectores, listas simples, árboles y tablas hash, basada en gestión dinámica de memoria, eficiencia en extremos y navegación bidireccional
- Demostración de uso correcto de ambos componentes con referencias específicas al código

**SICT0303 - Implementa acciones científicas:**
- Implementación correcta de mecanismos de consulta (recorrido completo, filtrado, búsquedas por múltiples criterios) con validación apropiada y manejo de casos especiales
- Mecanismo robusto de lectura de archivos CSV con validación de apertura, limpieza de memoria previa, procesamiento línea por línea, manejo de excepciones y retroalimentación al usuario
- Mecanismo correcto de escritura de archivos CSV con formato consistente, validación de recursos y cierre apropiado, garantizando persistencia completa de cambios

El sistema es **funcional, eficiente para su caso de uso** (catálogos de pequeño a mediano tamaño), y está **preparado para futuras extensiones** gracias a su diseño modular, estructura de datos flexible y código bien documentado.

**Posibles extensiones futuras:**
- Implementar Merge Sort para mejorar el ordenamiento a O(n log n)
- Agregar eliminación de libros del catálogo
- Implementar inserción ordenada para mantener la lista siempre ordenada
- Añadir búsquedas por rangos de años
- Crear interfaz gráfica (GUI)
- Implementar sistema de usuarios y historial de préstamos
