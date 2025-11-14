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

#### Algoritmos de Ordenamiento

El sistema implementa ordenamiento mediante **Selection Sort adaptado para listas ligadas**. A continuación se presenta el análisis completo:

**Selection Sort para Lista Doblemente Ligada:**

```cpp
void Biblioteca::ordenar_titulo() {
    Nodo* i = cabeza;
    while (i != nullptr) {
        Nodo* j = i->siguiente;
        while (j != nullptr) {
            if (i->data.get_titulo() > j->data.get_titulo()) {
                swap_libro_data(i, j);
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }
}
```

**Análisis de Complejidad Temporal:**

**Mejor Caso: O(n²)**
- Ocurre cuando la lista ya está ordenada
- Aún así, el algoritmo debe comparar cada elemento con todos los demás
- Primera iteración: n-1 comparaciones
- Segunda iteración: n-2 comparaciones
- Total: (n-1) + (n-2) + ... + 1 = n(n-1)/2 ≈ O(n²)

**Caso Promedio: O(n²)**
- Para una distribución aleatoria de elementos
- Número de comparaciones permanece constante: n(n-1)/2
- Número promedio de intercambios: n²/4
- Complejidad total: O(n²)

**Peor Caso: O(n²)**
- Ocurre cuando la lista está ordenada en orden inverso
- Máximo número de intercambios: n(n-1)/2
- Complejidad dominante: O(n²)

**Análisis de Complejidad Espacial:**

**Espacio: O(1)**
- El ordenamiento se realiza in-place
- Solo se utilizan variables auxiliares constantes (i, j, temp)
- No requiere estructuras auxiliares proporcionales a n

**Justificación del Algoritmo:**

Selection Sort fue elegido para listas ligadas porque:

1. Es simple de implementar sobre estructuras enlazadas
2. Realiza el mínimo número de intercambios (O(n) en el mejor caso)
3. Para listas ligadas, el overhead de otros algoritmos más complejos (como Merge Sort) no justifica su uso en catálogos pequeños a medianos
4. El intercambio de datos entre nodos es más eficiente que reorganizar enlaces

#### Estructura de Datos: Lista Doblemente Ligada

**Análisis Completo de Operaciones:**

**1. Inserción al Final - `agregar_libro()`:**

```cpp
void Biblioteca::agregar_libro(const Libro& libro) {
    Nodo* nuevo_nodo = new Nodo(libro);
    if (cabeza == nullptr) {
        cabeza = nuevo_nodo;
        cola = nuevo_nodo;
    } else {
        cola->siguiente = nuevo_nodo;
        nuevo_nodo->anterior = cola;
        cola = nuevo_nodo;
    }
    tamano++;
}
```

**Complejidad: O(1)**
- Gracias al puntero `cola`, la inserción al final es instantánea
- No requiere recorrer la lista completa
- Solo realiza asignaciones de punteros constantes

**2. Recorrido Completo - `mostrar_todos_libros()`:**

```cpp
void Biblioteca::mostrar_todos_libros() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->data.mostrar_info() << endl;
        actual = actual->siguiente;
    }
}
```

**Complejidad: O(n)**
- Debe visitar cada nodo exactamente una vez
- n representa el número de libros en el catálogo

**3. Búsqueda por Atributo:**

```cpp
vector<Libro*> Biblioteca::buscar_autor(const string& autor) {
    vector<Libro*> encontrados;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_autor() == autor) {
            encontrados.push_back(&(actual->data));
        }
        actual = actual->siguiente;
    }
    return encontrados;
}
```

**Complejidad:**
- **O(n)** para búsquedas por autor, género y año
- **O(n × m)** para búsqueda por título
  - n: número de libros
  - m: longitud promedio de los títulos
  - La función `find()` para búsqueda de subcadenas tiene complejidad O(m)

**4. Préstamo y Devolución:**

**Complejidad:**
- **Mejor Caso: O(1)** - El libro está en la primera posición
- **Caso Promedio: O(n/2) ≈ O(n)** - El libro está en el medio
- **Peor Caso: O(n)** - El libro está al final o no existe

**5. Carga desde Archivo - `leer_csv()`:**

```cpp
void Biblioteca::leer_csv(const string& filename) {
    // ... código de limpieza O(n) ...
    while (getline(inFile, linea)) {
        // ... procesamiento de línea O(m) ...
        agregar_libro(libro); // O(1)
    }
}
```

**Complejidad: O(n × m)**
- n: número de libros en el archivo
- m: longitud promedio de cada línea
- Incluye O(n) por limpiar lista existente
- Incluye O(n × m) por procesar cada línea

**6. Guardado a Archivo - `guardar_csv()`:**

**Complejidad: O(n)**
- Recorre cada nodo una vez
- Escribe información al archivo en tiempo constante por nodo

**7. Destructor - `~Biblioteca()`:**

```cpp
Biblioteca::~Biblioteca() {
    Nodo* actual = cabeza;
    Nodo* siguiente;
    while (actual != nullptr) {
        siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}
```

**Complejidad: O(n)**
- Debe liberar cada nodo individualmente
- Previene fugas de memoria

#### Complejidad Final del Programa

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

#### Selección del Algoritmo de Ordenamiento

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

El algoritmo se implementa correctamente en dos funciones:

```cpp
// Ordenamiento por título (orden alfabético)
void Biblioteca::ordenar_titulo() {
    Nodo* i = cabeza;
    while (i != nullptr) {
        Nodo* j = i->siguiente;
        while (j != nullptr) {
            if (i->data.get_titulo() > j->data.get_titulo()) {
                swap_libro_data(i, j);
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }
}
```

**Elementos Clave de la Implementación:**

1. **Recorrido Doble**: Dos punteros (i, j) recorren la lista comparando elementos
2. **Comparación Adecuada**: Usa operador `>` para determinar orden alfabético
3. **Intercambio Eficiente**: Función `swap_libro_data()` intercambia solo los datos, no los nodos
4. **Preservación de Enlaces**: Mantiene intacta la estructura de la lista

**Adaptabilidad:**

La misma implementación sirve para ordenar por diferentes criterios:
- Por título: `i->data.get_titulo() > j->data.get_titulo()`
- Por año: `i->data.get_anio_publicacion() > j->data.get_anio_publicacion()`

Esto demuestra la **flexibilidad** del diseño, permitiendo extensiones futuras con mínimos cambios.

#### Selección de la Estructura de Datos

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
- Facilita futuras implementaciones:
  - Paginación del catálogo
  - Navegación tipo "anterior/siguiente"
  - Funciones de deshacer/rehacer

**4. Flexibilidad para Inserciones/Eliminaciones:**
- Permite insertar/eliminar en cualquier posición
- No requiere desplazar elementos como en arreglos
- Útil para futuras funcionalidades (ej. ordenamiento por inserción)

**Comparación con Alternativas:**

**Lista Doblemente Ligada (ELEGIDA):**
- Acceso: O(n)
- Inserción Final: O(1)
- Búsqueda: O(n)
- Memoria: n × (dato + 2 punteros)
- Balance óptimo para el proyecto

**Vector (std::vector) (NO ELEGIDO):**
- Acceso: O(1)
- Inserción Final: O(1) amortizado
- Búsqueda: O(n)
- Desventaja: Realocaciones costosas, no permite navegación bidireccional

**Lista Simple Ligada (NO ELEGIDA):**
- Acceso: O(n)
- Inserción Final: O(n) sin puntero cola
- Búsqueda: O(n)
- Desventaja: No permite navegación hacia atrás

**Array Estático (NO ELEGIDO):**
- Acceso: O(1)
- Inserción Final: O(1)
- Desventaja: Tamaño fijo, desperdicio de memoria

**Árbol AVL (NO ELEGIDO):**
- Acceso: O(log n)
- Inserción: O(log n)
- Desventaja: Overhead innecesario, complica ordenamiento personalizado

**Implementación en el Proyecto:**

```cpp
struct Nodo {
    Libro data;
    Nodo* siguiente;
    Nodo* anterior;
    
    Nodo(const Libro& l) : data(l), siguiente(nullptr), anterior(nullptr) {}
};

class Biblioteca {
private:
    Nodo* cabeza;    // Puntero al primer nodo
    Nodo* cola;      // Puntero al último nodo
    int tamano;      // Contador de libros
    
public:
    // ... métodos ...
};
```

**Características Clave:**
- **Doble Enlace**: Cada nodo apunta al anterior y al siguiente
- **Sentinelas**: `cabeza` y `cola` optimizan operaciones en extremos
- **Contador**: `tamano` permite conocer el tamaño en O(1)

**Uso Correcto de la Estructura:**

**1. Inserción Eficiente:**

```cpp
void Biblioteca::agregar_libro(const Libro& libro) {
    Nodo* nuevo_nodo = new Nodo(libro);
    if (cabeza == nullptr) {
        // Lista vacía: nuevo nodo es cabeza y cola
        cabeza = nuevo_nodo;
        cola = nuevo_nodo;
    } else {
        // Insertar al final usando puntero cola
        cola->siguiente = nuevo_nodo;
        nuevo_nodo->anterior = cola;
        cola = nuevo_nodo;
    }
    tamano++;
}
```

**2. Gestión de Memoria:**

```cpp
Biblioteca::~Biblioteca() {
    Nodo* actual = cabeza;
    Nodo* siguiente;
    while (actual != nullptr) {
        siguiente = actual->siguiente;
        delete actual;  // Libera cada nodo
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}
```

**Demostración de Competencia:**
- Implementación completa desde cero (no usa estructuras de STL)
- Manejo correcto de memoria dinámica (new/delete)
- Prevención de fugas de memoria mediante destructor
- Actualización correcta de punteros en todas las operaciones
- Manejo de casos especiales (lista vacía, un elemento, etc.)

---

## Implementación de Acciones Científicas

### SICT0303: Implementa acciones científicas

#### Mecanismos de Consulta de Información

El sistema implementa múltiples mecanismos científicamente correctos para consultar información de la lista doblemente ligada:

**1. Consulta Completa del Catálogo:**

```cpp
void Biblioteca::mostrar_todos_libros() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->data.mostrar_info() << endl;
        actual = actual->siguiente;
    }
}
```

**Características:**
- Recorre la lista desde `cabeza` hasta el final (nullptr)
- Accede al dato de cada nodo mediante `actual->data`
- Complejidad O(n) - visita cada nodo exactamente una vez
- Manejo correcto de lista vacía (if cabeza == nullptr)

**2. Consulta Filtrada por Disponibilidad:**

```cpp
void Biblioteca::mostrar_disponibles() {
    bool hay_disponible = false;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_cantidad_disponible() > 0) {
            cout << actual->data.mostrar_info() << endl;
            hay_disponible = true;
        }
        actual = actual->siguiente;
    }
}
```

**Características:**
- Filtra elementos según criterio de disponibilidad
- Mantiene bandera para detectar casos sin resultados
- Acceso eficiente mediante métodos getter

**3. Búsqueda por Múltiples Criterios:**

```cpp
vector<Libro*> Biblioteca::buscar_autor(const string& autor) {
    vector<Libro*> encontrados;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_autor() == autor) {
            encontrados.push_back(&(actual->data));
        }
        actual = actual->siguiente;
    }
    return encontrados;
}
```

**Características:**
- Retorna punteros a los datos encontrados (no copias)
- Permite múltiples resultados mediante vector
- Manejo seguro: retorna vector vacío si no hay coincidencias
- Validación mediante comparación directa de strings

**4. Búsqueda con Subcadenas (Título):**

```cpp
vector<Libro*> Biblioteca::buscar_titulo(const string& titulo) {
    vector<Libro*> encontrados;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.get_titulo().find(titulo) != string::npos) {
            encontrados.push_back(&(actual->data));
        }
        actual = actual->siguiente;
    }
    return encontrados;
}
```

**Características:**
- Búsqueda flexible mediante `find()`
- Encuentra coincidencias parciales
- Útil cuando el usuario no recuerda el título completo

**Correctitud de los Mecanismos:**
- Recorrido completo sin omitir nodos
- Condición de terminación correcta (actual != nullptr)
- Avance adecuado (actual = actual->siguiente)
- Acceso seguro a datos mediante punteros válidos
- Manejo de casos especiales (lista vacía, sin resultados)

#### Mecanismos de Lectura de Archivos

El sistema implementa un mecanismo robusto y científicamente correcto para cargar datos desde archivos CSV:

```cpp
void Biblioteca::leer_csv(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "No se pudo abrir el archivo: " << filename << endl;
        cout << "Iniciando con biblioteca vacia." << endl;
        return;
    }

    // Limpiar la lista existente y liberar memoria
    Nodo* actual_del = cabeza;
    Nodo* siguiente_del;
    while (actual_del != nullptr) {
        siguiente_del = actual_del->siguiente;
        delete actual_del;
        actual_del = siguiente_del;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;

    string linea;
    int libros_cargados = 0;
    while (getline(inFile, linea)) {
        stringstream ss(linea);
        string titulo, autor, genero, anio_str, cant_total_str, cant_disponible_str;

        if (getline(ss, titulo, ',') &&
            getline(ss, autor, ',') &&
            getline(ss, genero, ',') &&
            getline(ss, anio_str, ',') &&
            getline(ss, cant_total_str, ',') &&
            getline(ss, cant_disponible_str, ',')) {

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
        }
    }

    inFile.close();
    cout << "Se cargaron " << libros_cargados << " libros desde " << filename << endl;
}
```

**Aspectos Científicamente Correctos:**

**1. Validación de Archivo:**

```cpp
if (!inFile.is_open()) {
    cout << "No se pudo abrir el archivo..." << endl;
    return;
}
```

- Verifica que el archivo exista y sea accesible
- Manejo gracioso de errores: inicia con biblioteca vacía
- Previene comportamientos indefinidos

**2. Limpieza de Memoria Antes de Cargar:**

```cpp
Nodo* actual_del = cabeza;
Nodo* siguiente_del;
while (actual_del != nullptr) {
    siguiente_del = actual_del->siguiente;
    delete actual_del;
    actual_del = siguiente_del;
}
```

- Libera memoria existente antes de cargar nuevos datos
- Previene fugas de memoria
- Garantiza estado limpio de la estructura

**3. Procesamiento Línea por Línea:**

```cpp
while (getline(inFile, linea)) {
    stringstream ss(linea);
    // ... procesamiento ...
}
```

- Lectura eficiente mediante getline
- Uso de stringstream para parsear campos CSV
- Manejo correcto de delimitadores (comas)

**4. Conversión de Tipos con Validación:**

```cpp
try {
    int anio = stoi(anio_str);
    int cant_total = stoi(cant_total_str);
    int cant_disponible = stoi(cant_disponible_str);
} catch (const invalid_argument& e) {
    cerr << "Error de formato..." << endl;
} catch (const out_of_range& e) {
    cerr << "Error de rango..." << endl;
}
```

- Conversión segura de strings a enteros
- Manejo de excepciones para datos inválidos
- Sistema robusto que continúa funcionando ante errores

**5. Carga Progresiva:**

```cpp
agregar_libro(libro); 
libros_cargados++;
```

- Inserta cada libro válido en la estructura
- Aprovecha la operación O(1) de agregar al final
- Contador de libros cargados para retroalimentación

**6. Cierre Correcto de Recursos:**

```cpp
inFile.close();
cout << "Se cargaron " << libros_cargados << " libros..." << endl;
```

- Libera recursos del sistema operativo
- Proporciona retroalimentación al usuario

**Formato del Archivo CSV:**

```
La Iliada,Homero,Epico,-750,3,3
La Odisea,Homero,Epico,-700,3,3
Don Quijote de la Mancha,Miguel de Cervantes,Clasico,1605,2,2
```

Cada línea contiene:
- Título del libro
- Autor
- Género
- Año de publicación
- Cantidad total de ejemplares
- Cantidad disponible

#### Mecanismos de Escritura de Archivos

El sistema implementa un mecanismo correcto para persistir los datos del catálogo:

```cpp
void Biblioteca::guardar_csv(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "No se