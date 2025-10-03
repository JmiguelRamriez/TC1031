# Sistema de Gestión de Biblioteca
## Proyecto TC1031

**Autor:** Jose Miguel Ramirez Gutierrez  
**Matrícula:** A01712628  
**Fecha:** Octubre 2025

---

## Descripción del Avance

Este proyecto implementa un sistema de gestión para una biblioteca utilizando C++. El sistema permite administrar un catálogo de libros mediante estructuras de datos eficientes y algoritmos de ordenamiento optimizados.

### Estado Actual del Proyecto

El sistema cuenta con las siguientes funcionalidades completamente implementadas:

**Gestión de Catálogo:**
- Agregar libros al sistema
- Visualizar todos los libros o solo los disponibles
- Persistencia de datos mediante archivos CSV (carga y guardado automático)

**Sistema de Búsqueda:**
- Búsqueda por autor: encuentra todos los libros de un autor específico
- Búsqueda por género: lista libros de un género determinado
- Búsqueda por título: búsqueda flexible que encuentra coincidencias parciales

**Ordenamiento del Catálogo:**
- Ordenamiento alfabético por título
- Ordenamiento cronológico por año de publicación
- Implementación mediante `std::sort` con funciones lambda personalizadas

**Préstamos y Devoluciones:**
- Sistema de préstamo que reduce la cantidad disponible
- Sistema de devolución que incrementa la cantidad disponible
- Validaciones de disponibilidad y límites

### Componentes del Sistema

**1. Clase `Libro` (Libro.h)**
- Encapsula la información de cada libro: título, autor, género, año de publicación, cantidad total y cantidad disponible
- Proporciona métodos getter/setter y funciones de visualización

**2. Clase `Biblioteca` (Biblioteca.h)**
- Almacena el catálogo de libros en un `std::vector<Libro>`
- Implementa todas las operaciones de búsqueda, ordenamiento y gestión
- Maneja la persistencia mediante archivos CSV

**3. Programa Principal (Main.cpp)**
- Interfaz interactiva de usuario mediante menú en consola
- Gestiona el flujo del programa y la interacción con el usuario
- Coordina todas las operaciones del sistema

---

## Instrucciones de Uso

### Compilación del Programa

Asegúrate de tener los tres archivos (`Libro.h`, `Biblioteca.h`, `Main.cpp`) en el mismo directorio.

```bash
g++ .\Main.cpp -o biblioteca
```


### Ejecución

```bash
# En Linux/macOS
./biblioteca

# En Windows
biblioteca.exe
```

### Uso del Sistema

Al ejecutar el programa, aparecerá un menú con 6 opciones:

```
1. Mostrar todos los libros disponibles
2. Pedir prestado un libro
3. Devolver libros
4. Ordenar los libros
5. Buscar los libros
6. SALIR y Guardar
```

**Flujo de uso:**
1. El programa carga automáticamente los libros desde `libros.csv` (si existe)
2. Selecciona una opción ingresando el número correspondiente
3. Sigue las instrucciones en pantalla para cada operación
4. Al seleccionar la opción 6, el programa guarda automáticamente todos los cambios

### Formato del Archivo CSV

El archivo `libros.csv` utiliza el siguiente formato:
```
titulo,autor,genero,año,cantidad_total,cantidad_disponible
```

Ejemplo:
```
Cien Años de Soledad,Gabriel Garcia Marquez,Realismo Magico,1967,5,3
1984,George Orwell,Distopia,1949,4,4
El Principito,Antoine de Saint-Exupery,Fabula,1943,3,2
```

---

## Cumplimiento de Sub-competencias

### SICT0301: Evalúa los componentes

**Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.**

El programa utiliza `std::sort` de la biblioteca estándar de C++, que implementa el algoritmo **Introsort** (Ordenamiento Introspectivo). A continuación se presenta el análisis completo de complejidad:

#### Descripción del Algoritmo: Introsort

Introsort es un algoritmo híbrido que combina tres algoritmos de ordenamiento para garantizar eficiencia en todos los escenarios:

1. **Quicksort** - Utilizado como algoritmo principal por su excelente rendimiento promedio
   - Divide el arreglo en particiones usando un pivote
   - Complejidad promedio: O(n log n)
   
2. **Heapsort** - Activado como respaldo cuando la recursión se profundiza demasiado
   - Evita la degradación a O(n²) que puede ocurrir con Quicksort
   - Garantiza el peor caso de O(n log n)
   
3. **Insertion Sort** - Aplicado para subproblemas pequeños (típicamente < 16 elementos)
   - Más eficiente que Quicksort para conjuntos de datos pequeños
   - Reduce el overhead de la recursión

#### Análisis de Complejidad Temporal

**Mejor Caso: O(n log n)**
- Ocurre cuando los pivotes de Quicksort dividen el arreglo de manera balanceada
- El arreglo se divide en log n niveles
- En cada nivel se realizan n comparaciones
- Total: n × log n comparaciones

**Caso Promedio: O(n log n)**
- Quicksort maneja la mayoría de los casos con particiones razonablemente balanceadas
- El comportamiento promedio se mantiene en O(n log n)
- La probabilidad de degradación es extremadamente baja

**Peor Caso: O(n log n)**
- Si Quicksort comienza a degradarse (recursión profunda), Introsort cambia a Heapsort
- Heapsort garantiza O(n log n) en el peor caso
- Esta es la ventaja principal sobre Quicksort puro, que tiene peor caso O(n²)

#### Análisis de Complejidad Espacial

**Espacio: O(log n)**
- Corresponde al espacio utilizado por la pila de recursión
- En el peor caso, la profundidad de recursión es log n
- El algoritmo realiza ordenamiento in-place, no requiere arreglos auxiliares grandes

#### Implementación en el Proyecto

El programa utiliza `std::sort` en dos funciones:

```cpp
// Ordenamiento por título (alfabético)
void Biblioteca::ordenar_titulo() {
    sort(libros.begin(), libros.end(), [](const Libro& a, const Libro& b) {
        return a.get_titulo() < b.get_titulo(); 
    });
}
```
Complejidad: O(n log n) donde n es el número de libros

```cpp
// Ordenamiento por año de publicación (cronológico)
void Biblioteca::ordenar_anio() {
    sort(libros.begin(), libros.end(), [](const Libro& a, const Libro& b) {
        return a.get_anio_publicacion() < b.get_anio_publicacion();
    });
}
```
Complejidad: O(n log n) donde n es el número de libros

Ambas funciones tienen el mismo análisis de complejidad porque utilizan el mismo algoritmo base (`std::sort`), solo cambia el criterio de comparación mediante las funciones lambda.

---

### SICT0302: Toma decisiones

**Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.**

#### Justificación de la Selección

La elección de `std::sort` (Introsort) es la más adecuada para este problema por las siguientes razones:

**1. Eficiencia Garantizada**
- Complejidad O(n log n) garantizada en todos los casos (mejor, promedio y peor)
- Escalable para bibliotecas de cualquier tamaño, desde decenas hasta miles de libros
- Muy superior a algoritmos O(n²) como Bubble Sort o Selection Sort, que se degradarían rápidamente con catálogos grandes

Comparación de rendimiento para n = 1000 libros:
- Bubble Sort: ~1,000,000 operaciones (O(n²))
- Introsort: ~10,000 operaciones (O(n log n))
- Diferencia: 100 veces más rápido

**2. Uso de Biblioteca Estándar**
- `std::sort` es una implementación probada y optimizada por los desarrolladores del compilador
- Evita errores comunes al implementar algoritmos desde cero
- Código más mantenible y fácil de entender para otros programadores
- Reduce significativamente el tiempo de desarrollo

**3. Flexibilidad mediante Funciones Lambda**
- Permite ordenar por múltiples criterios sin duplicar código
- Las funciones lambda hacen el código expresivo y legible
- Fácil de extender para nuevos criterios de ordenamiento

**4. Adaptabilidad al Problema**
- El sistema requiere ordenar por diferentes atributos (título y año)
- `std::sort` se adapta perfectamente mediante comparadores personalizados
- No requiere cambios estructurales para agregar nuevos criterios

#### Uso Correcto del Algoritmo

El programa demuestra el uso correcto de `std::sort` mediante:

**Sintaxis Apropiada:**
```cpp
sort(libros.begin(), libros.end(), comparador)
```
- `libros.begin()`: iterador al inicio del vector
- `libros.end()`: iterador al final del vector
- `comparador`: función lambda que define el criterio de ordenamiento

**Comparadores Correctos:**
- Retornan `true` si el primer elemento debe ir antes que el segundo
- Implementan relaciones de orden estricto (a < b)
- Garantizan ordenamiento estable y correcto

**Orden Ascendente:**
Ambos ordenamientos están implementados en orden ascendente:
- Títulos: orden alfabético A-Z
- Años: orden cronológico (más antiguos primero)

Este es el comportamiento esperado para un sistema de biblioteca, facilitando la búsqueda y navegación del catálogo.

#### Alternativas Consideradas y Descartadas

**Bubble Sort / Selection Sort:**
- Complejidad O(n²) inaceptable para catálogos grandes
- Ineficientes incluso para catálogos medianos

**Merge Sort:**
- Complejidad O(n log n) pero requiere O(n) espacio adicional
- Menos eficiente en la práctica que Introsort
- `std::sort` es superior en todos los aspectos

**Quick Sort puro:**
- Peor caso O(n²) podría causar problemas
- Introsort (usado por `std::sort`) resuelve esta limitación

La selección de `std::sort` es, por lo tanto, **la decisión óptima** para este proyecto, cumpliendo con eficiencia, corrección y mejores prácticas de programación.

---
