*/ Proyecto-C-
Proyecto final de C++

Autor: Jorge Jesús Santos García 

Informe: Automatización del Sistema de Préstamos de una Biblioteca

Descripción del Problema:
Se necesita automatizar el sistema de préstamos de una biblioteca que contiene libros con información como título, autor(es) y materia . Los libros pueden ser consultados en las salas o solicitados en préstamo fuera de la biblioteca. Para solicitar un préstamo, se requiere presentar una identificación con número de identidad, nombre y apellidos. Los libros pueden ser buscados por materias, autor o título. El préstamo es por una semana y se permite tener hasta tres ejemplares prestados. Si un usuario no devuelve un libro a tiempo, no podrá solicitar nuevos préstamos hasta que devuelva todos los ejemplares.

Solución Propuesta:
Se implementará un programa en C++ que cumpla con los requisitos mencionados. Se utilizarán conceptos de Programación Orientada a Objetos (POO) para modelar las entidades involucradas en el sistema, como Libro, Usuario y Préstamo. Se aplicará la sobrecarga de operadores para facilitar operaciones entre objetos. Se emplearán estructuras de datos de la STL para almacenar y gestionar la información de los libros, usuarios y préstamos. Además, se utilizará programación funcional para realizar operaciones sobre colecciones de datos de manera eficiente.

-----------------------------------------
|              Biblioteca               |
-----------------------------------------
 - librosDisponibles: vector<Libro>   
 - librosPrestados: map<Libro, Usuario>
-----------------------------------------
 + agregarLibro(libro: Libro)         
 + prestarLibro(libro: Libro, usuario: Usuario) 
 + devolverLibro(libro: Libro)        
 + mostrarLibrosDisponibles()         
 + guardarDatos(archivo: string)      
-----------------------------------------

-----------------------------------------
|                Libro                 |
-----------------------------------------
- titulo: string                     
- autor: string                      
- materia: string                    
-----------------------------------------
 + Libro(t: string, a: string, m: string)
-----------------------------------------

-----------------------------------------
|               Usuario                |
-----------------------------------------
 - nombre: string                      - identidad: string                  |
---------------------------------------+ Usuario(n: string, id: string)   
-----------------------------------------

Libro "1" -- "1..*" Biblioteca

Usuario "1" -- "1..*" Biblioteca


Con esta solución, se podrá gestionar de forma eficiente el sistema de préstamos de la biblioteca, permitiendo a los usuarios consultar y solicitar libros de manera automatizada.*/

