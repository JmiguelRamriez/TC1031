# Sistema de Gestión de Biblioteca
## Proyecto TC1031

**Autor:** Jose Miguel Ramirez Gutierrez  
**Matrícula:** A01712628  

---

## Contexto del Proyecto

Este proyecto implementa un sistema completo de gestión de biblioteca que permite administrar eficientemente un catálogo de libros. El sistema está diseñado para facilitar operaciones comunes en una biblioteca como préstamos, devoluciones, búsquedas y ordenamiento del inventario, todo mientras mantiene la persistencia de datos entre sesiones.

El sistema resuelve la necesidad de organizar y acceder rápidamente a información sobre libros, permitiendo a los usuarios realizar búsquedas por múltiples criterios (autor, género, título, año), gestionar préstamos y devoluciones de manera eficiente, y mantener un registro actualizado del inventario disponible.

---

## Descripción General del Proyecto

### Funcionalidades Principales

El sistema de gestión de biblioteca ofrece las siguientes capacidades:

1. **Visualización del Catálogo Completo**: Muestra todos los libros registrados en la biblioteca con información detallada (título, autor, género, año de publicación, cantidad total y disponible).

2. **Gestión de Préstamos**: Permite prestar libros a usuarios, reduciendo automáticamente la cantidad disponible y validando que haya ejemplares disponibles antes de realizar el préstamo.

3. **Gestión de Devoluciones**: Procesa devoluciones de libros prestados, incrementando la cantidad disponible y validando que no se excedan los límites del inventario.

4. **Ordenamiento del Catálogo**: Organiza los libros según diferentes criterios:
   - Por título (orden alfabético)
   - Por año de publicación (orden cronológico)

5. **Búsqueda Avanzada**: Encuentra libros mediante múltiples criterios:
   - Por autor (exacto)
   - Por género (exacto)
   - Por título (búsqueda parcial)
   - Por año de publicación (exacto)

6. **Persistencia de Datos**: Carga automáticamente el catálogo desde un archivo CSV al iniciar y guarda todos los cambios al finalizar la sesión.

### Estructura de Datos: Lista Doblemente Ligada

El proyecto utiliza una **Lista Doblemente Ligada** como estructura principal para almacenar y gestionar el catálogo de libros. Esta decisión de diseño fue tomada cuidadosamente considerando las necesidades específicas del sistema.

**Ventajas de la Lista Doblemente Ligada:**

- **Inserción Eficiente**: Las inserciones al inicio o al final se realizan en tiempo constante O(1), permitiendo agregar nuevos libros rápidamente sin necesidad de reorganizar toda la estructura.

- **Eliminación Eficiente**: Similar a las inserciones, las eliminaciones en los extremos son O(1), facilitando la gestión dinámica del catálogo.

- **Navegación Bidireccional**: Los punteros a nodos anteriores y siguientes permiten recorrer la lista en ambas direcciones, habilitando futuras funcionalidades como navegación tipo "historial" o paginación.

- **Gestión Dinámica de Memoria**: A diferencia de los vectores, no requiere realocaciones de memoria completas cuando crece el catálogo, evitando copias costosas de datos.

- **Flexibilidad**: Permite inserciones y eliminaciones en cualquier posición sin desplazamiento de elementos como ocurriría con arreglos.

**Implementación en el Proyecto:**

La lista mantiene punteros `cabeza` (primer nodo) y `cola` (último nodo), optimizando las operaciones en los extremos y manteniendo un contador `tamano` para conocer instantáneamente el número de libros en el catálogo.

---

## Descripción del Avance

### Avance Actual: Lista Doblemente Ligada

En esta versión del proyecto, se ha migrado completamente la estructura de almacenamiento de `std::vector` a una **Lista Doblemente Ligada implementada desde cero**. Esta transición representa una mejora significativa en términos de:

- **Eficiencia de Memoria**: La lista crece dinámicamente según sea necesario, sin reservar memoria adicional innecesaria.

- **Operaciones en los Extremos**: Inserción y eliminación en O(1) para ambos extremos de la lista.

- **Recorridos Bidireccionales**: Capacidad de navegar la lista en ambas direcciones mediante los punteros `anterior` y `siguiente`.

- **Gestión de Recursos**: Implementación de destructor que libera correctamente toda la memoria dinámica, previniendo fugas de memoria.

### Cambios Respecto a Versiones Anteriores

**Primera Versión**: Utilizaba `std::vector` para almacenar los libros, lo cual era simple pero limitado en términos de flexibilidad y eficiencia para operaciones de inserción/eliminación.

**Versión Actual**: Implementa una lista doblemente ligada personalizada que ofrece:
- Mayor control sobre la gestión de memoria
- Operaciones más eficientes en los extremos
- Mejor preparación para futuras extensiones del sistema
- Navegación bidireccional del catálogo

---

## Análisis de Complejidad

### SICT0301: Evalúa los componentes

#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa

El sistema implementa ordenamiento mediante **Selection Sort adaptado para listas ligadas**. 

**Análisis de Complejidad Temporal:**

**Mejor Caso: O(n²)**
- Ocurre cuando la lista ya está ordenada
- El algoritmo debe comparar cada elemento con todos los demás
- Total de comparaciones: (n-1) + (n-2) + ... + 1 = n(n-1)/2 ≈ O(n²)

**Caso Promedio: O(n²)**
- Para una distribución aleatoria de elementos
- Número de comparaciones permanece constante: n(n-1)/2
- Número promedio de intercambios: n²/4
- Complejidad total: O(n²)

**Peor Caso: O(n²)**
- Ocurre cuando la lista está ordenada en orden inverso
- Máximo número de intercambios: n(n-1)/2
- Complejidad dominante: O(n²)

**Análisis de Complejidad Espacial: O(1)**
- El ordenamiento se realiza in-place
- Solo se utilizan variables auxiliares constantes
- No requiere estructuras auxiliares proporcionales a n

**Justificación del Algoritmo:**

Selection Sort fue elegido para listas ligadas porque:

1. Es simple de implementar sobre estructuras enlazadas
2. Realiza el mínimo número de intercambios (O(n) en el mejor caso)
3. Para listas ligadas, el overhead de otros algoritmos más complejos como Merge Sort no justifica su uso en catálogos pequeños a medianos
4. El intercambio de datos entre nodos es más eficiente que reorganizar enlaces

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa

**Lista Doblemente Ligada - Análisis Completo de Operaciones:**

**1. Inserción al Final - `agregar_libro()`:**
- **Complejidad: O(1)**
- Gracias al puntero `cola`, la inserción al final es instantánea
- No requiere recorrer la lista completa
- Solo realiza asignaciones de punteros constantes

**2. Recorrido Completo - `mostrar_todos_libros()`:**
- **Complejidad: O(n)**
- Debe visitar cada nodo exactamente una vez
- n representa el número de libros en el catálogo

**3. Búsqueda por Atributo:**
- **O(n)** para búsquedas por autor, género y año
- **O(n × m)** para búsqueda por título (donde m es la longitud promedio de los títulos, debido al uso de la función `find()` para búsqueda de subcadenas)

**4. Préstamo y Devolución - `prestar_libro()`, `devolver_libro()`:**
- **Mejor Caso: O(1)** - El libro está en la primera posición
- **Caso Promedio: O(n/2) ≈ O(n)** - El libro está en el medio
- **Peor Caso: O(n)** - El libro está al final o no existe

**5. Carga desde Archivo - `leer_csv()`:**
- **Complejidad: O(n × m)**
- n: número de libros en el archivo
- m: longitud promedio de cada línea
- Incluye O(n) por limpiar lista existente
- Incluye O(n × m) por procesar cada línea

**6. Guardado a Archivo - `guardar_csv()`:**
- **Complejidad: O(n)**
- Recorre cada nodo una vez
- Escribe información al archivo en tiempo constante por nodo

**7. Destructor - `~Biblioteca()`:**
- **Complejidad: O(n)**
- Debe liberar cada nodo individualmente
- Previene fugas de memoria

#### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa

**Análisis Global del Sistema:**

El programa presenta diferentes complejidades según la operación ejecutada:

**Operaciones Principales:**
1. **Mostrar Catálogo**: O(n) - Recorrido lineal
2. **Préstamo/Devolución**: O(n) - Búsqueda lineal + actualización O(1)
3. **Ordenamiento**: O(n²) - Selection Sort sobre lista ligada
4. **Búsqueda Simple**: O(n) - Búsqueda lineal
5. **Búsqueda por Título**: O(n × m) - Búsqueda con subcadenas
6. **Carga Inicial**: O(n × m) - Procesamiento de archivo
7. **Guardado Final**: O(n) - Recorrido y escritura

**Complejidad Dominante del Sistema: O(n²)**

La operación más costosa del sistema es el **ordenamiento**, que utiliza Selection Sort con complejidad O(n²). Esta operación domina la complejidad total cuando se ejecuta.

**Análisis por Escenarios:**

**Mejor Caso (Sin Ordenamiento): O(n × m)**
- Usuario solo visualiza, busca o presta/devuelve libros
- Complejidad dominada por la carga inicial del archivo

**Caso Promedio: O(n²)**
- Usuario realiza ordenamiento al menos una vez durante la sesión
- El ordenamiento domina sobre otras operaciones

**Peor Caso: O(n²)**
- Usuario ordena múltiples veces con catálogo en orden inverso
- Cada ordenamiento requiere máximo número de comparaciones e intercambios

**Escalabilidad:**
- Para catálogos pequeños (< 100 libros): O(n²) es aceptable
- Para catálogos medianos (100-1000 libros): Comienza a notarse la degradación
- Para catálogos grandes (> 1000 libros): Se recomienda migrar a algoritmos O(n log n)

---

## Toma de Decisiones

### SICT0302: Toma decisiones

#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente

**Algoritmo Elegido: Selection Sort adaptado para Lista Doblemente Ligada**

**Justificación de la Decisión:**

**1. Simplicidad de Implementación en Listas Ligadas:**
- Selection Sort se adapta naturalmente a estructuras enlazadas
- No requiere acceso aleatorio a elementos como otros algoritmos (ej. Quick Sort)
- Implementación clara y fácil de mantener

**2. Mínimo Número de Intercambios:**
- Realiza exactamente n-1 intercambios en todos los casos
- Para listas ligadas, intercambiar datos es más eficiente que reorganizar punteros
- Reduce el riesgo de errores en la gestión de enlaces

**3. Uso Eficiente para Catálogos Pequeños a Medianos:**
- Para bibliotecas típicas (50-500 libros), la diferencia de rendimiento con algoritmos más complejos es mínima
- El overhead de algoritmos más sofisticados no se justifica en estos tamaños

**4. Estabilidad y Predictibilidad:**
- Comportamiento consistente y predecible
- Facilita el debugging y testing
- No requiere memoria adicional (ordenamiento in-place)

**Comparación con Alternativas:**

**Selection Sort (ELEGIDO):**
- Complejidad: O(n²)
- Ventajas: Simple, pocos intercambios, in-place
- Razón de selección: Balance óptimo entre simplicidad y eficiencia para el proyecto

**Bubble Sort (NO ELEGIDO):**
- Complejidad: O(n²)
- Desventaja: Demasiados intercambios innecesarios
- Por qué no: Ineficiente comparado con Selection Sort

**Insertion Sort (NO ELEGIDO):**
- Complejidad: O(n²)
- Desventaja: Lento para datos aleatorios
- Por qué no: No aprovecha la estructura de lista ligada

**Merge Sort (NO ELEGIDO):**
- Complejidad: O(n log n)
- Desventaja: Requiere O(n) espacio adicional, complejo para listas
- Por qué no: Overhead innecesario para catálogos pequeños

**Quick Sort (NO ELEGIDO):**
- Complejidad: O(n log n) promedio, O(n²) peor caso
- Desventaja: Requiere acceso aleatorio, difícil en listas
- Por qué no: Complejo de implementar en listas ligadas

**Uso Correcto del Algoritmo:**

El algoritmo se implementa mediante dos bucles anidados que recorren la lista. El bucle externo selecciona cada elemento como referencia, mientras el bucle interno encuentra el elemento mínimo en el resto de la lista. Si se encuentra un elemento menor, se intercambian los datos (no los nodos).

**Elementos Clave de la Implementación:**
1. **Recorrido Doble**: Dos punteros recorren la lista comparando elementos
2. **Comparación Adecuada**: Usa operadores de comparación para determinar el orden
3. **Intercambio Eficiente**: Función auxiliar intercambia solo los datos, no los nodos
4. **Preservación de Enlaces**: Mantiene intacta la estructura de la lista

**Adaptabilidad:**

La misma implementación sirve para ordenar por diferentes criterios:
- Por título: Comparación alfabética de strings
- Por año: Comparación numérica de enteros

Esto demuestra la **flexibilidad** del diseño, permitiendo extensiones futuras con mínimos cambios.

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente

**Estructura Elegida: Lista Doblemente Ligada**

**Justificación de la Decisión:**

**1. Gestión Dinámica de Memoria:**
- El catálogo crece y decrece según necesidad
- No requiere conocer el tamaño máximo de antemano
- Evita desperdicio de memoria por reservas excesivas
- Previene realocaciones costosas como en vectores

**2. Eficiencia en Operaciones en Extremos:**
- Inserción al final en O(1) gracias al puntero `cola`
- Eliminación al inicio/final en O(1)
- Ideal para operaciones de agregar nuevos libros

**3. Navegación Bidireccional:**
- Permite recorrer hacia adelante y hacia atrás
- Facilita futuras implementaciones como paginación del catálogo, navegación tipo "anterior/siguiente" y funciones de deshacer/rehacer

**4. Flexibilidad para Inserciones/Eliminaciones:**
- Permite insertar/eliminar en cualquier posición
- No requiere desplazar elementos como en arreglos
- Útil para futuras funcionalidades

**Comparación con Alternativas:**

**Lista Doblemente Ligada (ELEGIDA):**
- Balance óptimo para el proyecto
- Operaciones eficientes en extremos O(1)
- Navegación bidireccional

**Vector (std::vector) (NO ELEGIDO):**
- Realocaciones costosas cuando crece
- No permite navegación bidireccional eficiente
- Desplazamiento de elementos en inserciones/eliminaciones medias

**Lista Simple Ligada (NO ELEGIDA):**
- No permite navegación hacia atrás
- Inserción final O(n) sin puntero cola
- Menos flexible para futuras extensiones

**Array Estático (NO ELEGIDO):**
- Tamaño fijo predefinido
- Desperdicio de memoria o limitación de capacidad
- No escalable

**Árbol AVL (NO ELEGIDO):**
- Overhead innecesario para este problema
- Complica el ordenamiento personalizado
- Mayor complejidad de implementación sin beneficios significativos

**Implementación en el Proyecto:**

La estructura utiliza una estructura `Nodo` con datos del libro y dos punteros (anterior y siguiente). La clase `Biblioteca` mantiene punteros a `cabeza` y `cola` para optimizar operaciones en extremos, además de un contador `tamano`.

**Uso Correcto de la Estructura:**

**1. Inserción Eficiente:**
La función de agregar libro verifica si la lista está vacía. Si lo está, el nuevo nodo se convierte en cabeza y cola. Si no, se enlaza al final usando el puntero cola, actualizando los enlaces bidireccionales correctamente.

**2. Gestión de Memoria:**
El destructor recorre la lista liberando cada nodo individualmente para prevenir fugas de memoria, utilizando un puntero auxiliar para no perder la referencia al siguiente nodo.

**Demostración de Competencia:**
- Implementación completa desde cero (no usa estructuras de STL como std::list)
- Manejo correcto de memoria dinámica (new/delete)
- Prevención de fugas de memoria mediante destructor
- Actualización correcta de punteros en todas las operaciones
- Manejo de casos especiales (lista vacía, un elemento, etc.)

---

## Implementación de Acciones Científicas

### SICT0303: Implementa acciones científicas

#### Implementa mecanismos para consultar información de las estructuras correctos

El sistema implementa múltiples mecanismos científicamente correctos para consultar información de la lista doblemente ligada:

**1. Consulta Completa del Catálogo:**

La función recorre la lista desde la cabeza hasta el final (nullptr), accediendo al dato de cada nodo e imprimiéndolo. Tiene complejidad O(n) ya que visita cada nodo exactamente una vez, con manejo correcto de lista vacía.

**2. Consulta Filtrada por Disponibilidad:**

Recorre toda la lista pero solo muestra los libros que tienen ejemplares disponibles (cantidad_disponible > 0). Mantiene una bandera para detectar si hay o no libros disponibles.

**3. Búsqueda por Múltiples Criterios:**

El sistema implementa búsquedas por autor, género, título y año. Cada función recorre la lista completa, compara el atributo correspondiente y almacena punteros a los libros que coinciden en un vector. Retorna el vector de resultados, que puede estar vacío si no hay coincidencias.

**Características de las búsquedas:**
- Retorna punteros a los datos encontrados (no copias)
- Permite múltiples resultados mediante vector
- Manejo seguro: retorna vector vacío si no hay coincidencias
- La búsqueda por título usa `find()` para coincidencias parciales

**Correctitud de los Mecanismos:**
- Recorrido completo sin omitir nodos
- Condición de terminación correcta (actual != nullptr)
- Avance adecuado (actual = actual->siguiente)
- Acceso seguro a datos mediante punteros válidos
- Manejo de casos especiales (lista vacía, sin resultados)

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta

El sistema implementa un mecanismo robusto y científicamente correcto para cargar datos desde archivos CSV.

**Aspectos Científicamente Correctos:**

**1. Validación de Archivo:**
Antes de procesar, verifica que el archivo se pueda abrir correctamente usando `is_open()`. Si falla, informa al usuario y continúa con biblioteca vacía, evitando comportamientos indefinidos.

**2. Limpieza de Memoria Antes de Cargar:**
Antes de cargar nuevos datos, libera toda la memoria existente recorriendo la lista y eliminando cada nodo. Esto previene fugas de memoria y garantiza un estado limpio.

**3. Procesamiento Línea por Línea:**
Lee el archivo línea por línea con `getline()`, luego usa `stringstream` para parsear cada línea separando campos por comas. Este enfoque es eficiente y maneja correctamente el formato CSV.

**4. Conversión de Tipos con Validación:**
Convierte los strings de año y cantidades a enteros usando `stoi()`, envuelto en bloques try-catch para manejar excepciones de formato inválido (`invalid_argument`) o valores fuera de rango (`out_of_range`). Si ocurre un error, se ignora esa línea y continúa procesando.

**5. Carga Progresiva:**
Cada libro válido se inserta en la estructura usando la función `agregar_libro()` que tiene complejidad O(1). Se mantiene un contador de libros cargados para dar retroalimentación.

**6. Cierre Correcto de Recursos:**
Al finalizar, cierra el archivo para liberar recursos del sistema operativo e informa al usuario cuántos libros se cargaron exitosamente.

**Formato del Archivo CSV:**

```
La Iliada,Homero,Epico,-750,3,3
La Odisea,Homero,Epico,-700,3,3
```

Cada línea contiene: título, autor, género, año de publicación, cantidad total y cantidad disponible, separados por comas.

#### Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta

El sistema implementa un mecanismo correcto para persistir los datos del catálogo en formato CSV.

**Aspectos Científicamente Correctos:**

**1. Validación de Apertura:**
Verifica que el archivo se pueda abrir para escritura. Si falla, muestra mensaje de error y termina la función sin intentar escribir.

**2. Recorrido y Escritura:**
Recorre la lista desde la cabeza hasta el final, escribiendo la información de cada libro en formato CSV (campos separados por comas) usando el operador `<<` del ofstream.

**3. Formato Consistente:**
Cada libro se guarda en una línea con el formato: `titulo,autor,genero,año,cantidad_total,cantidad_disponible`. Este formato es consistente con el usado en la lectura, garantizando compatibilidad.

**4. Cierre de Recursos:**
Cierra el archivo explícitamente al finalizar para asegurar que todos los datos se escriban correctamente y se liberen los recursos del sistema.

**5. Retroalimentación al Usuario:**
Informa al usuario que la biblioteca se guardó exitosamente, proporcionando confianza de que los cambios se persistieron.

**Complejidad: O(n)** donde n es el número de libros, ya que debe recorrer toda la lista una vez.

Este mecanismo garantiza que todos los cambios realizados durante la sesión (préstamos, devoluciones, libros agregados) se guarden correctamente para futuras sesiones.

---

## Instrucciones de Compilación y Ejecución

### Requisitos
- Compilador C++ con soporte para C++11 o superior
- Sistema operativo: Windows, Linux o macOS
- Archivo `libros.csv` en el mismo directorio (se crea automáticamente si no existe)

### Compilación

Asegúrate de tener los tres archivos (`Libro.h`, `Biblioteca.h`, `Main.cpp`) en el mismo directorio.

```bash
g++ main.cpp -o biblioteca
```

### Ejecución

**En Linux/macOS:**
```bash
./biblioteca
```

**En Windows:**
```bash
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
4. Al seleccionar la opción 6, el programa guarda automáticamente todos los cambios en `libros.csv`

---

## Entradas y Salidas del Programa

### Entrada: Archivo CSV

El programa lee un archivo `libros.csv` con el siguiente formato:

```
titulo,autor,genero,año,cantidad_total,cantidad_disponible
```

Ejemplo:
```
La Iliada,Homero,Epico,-750,3,3
Don Quijote de la Mancha,Miguel de Cervantes,Clasico,1605,2,2
1984,George Orwell,Distopia,1949,4,4
```

### Entradas del Usuario

Durante la ejecución, el usuario puede ingresar:
- Número de opción del menú (1-6)
- Títulos de libros para préstamo/devolución
- Criterios de búsqueda (autor, género, título, año)
- Criterios de ordenamiento (título o año)

### Salidas del Programa

**1. Listado de Libros:**
Muestra la información completa de cada libro:
- Título
- Autor
- Género
- Año de publicación
- Disponibilidad (ejemplares disponibles / total)

**2. Resultados de Búsqueda:**
Muestra todos los libros que coinciden con el criterio especificado, o informa si no se encontraron resultados.

**3. Confirmaciones:**
Mensajes de confirmación para operaciones exitosas:
- "Se prestó el libro: [título]"
- "Se devolvió el libro: [título]"
- "Se cargaron X libros desde libros.csv"
- "Biblioteca guardada en libros.csv"

**4. Mensajes de Error:**
- "No se encontró el libro con título: [título]"
- "No hay ejemplares disponibles de: [título]"
- "No se pudo abrir el archivo: libros.csv"
- Errores de formato en líneas del CSV

---

## Conclusión

Este proyecto demuestra la implementación exitosa de un sistema de gestión de biblioteca usando una Lista Doblemente Ligada como estructura de datos principal. El sistema cumple con todos los requisitos de las competencias:

- **SICT0301**: Análisis completo de complejidad de algoritmos (Selection Sort O(n²)) y estructuras de datos (Lista Doblemente Ligada), determinando la complejidad final del programa como O(n²).

- **SICT0302**: Selección justificada de Selection Sort como algoritmo de ordenamiento y Lista Doblemente Ligada como estructura de datos, ambos adecuados al problema y usados correctamente.

- **SICT0303**: Implementación correcta de mecanismos de consulta, lectura y escritura de archivos con validación de errores y manejo robusto de datos.

El sistema es funcional, eficiente para catálogos de tamaño pequeño a mediano, y está preparado para futuras extensiones gracias a su diseño modular y estructura flexible.
