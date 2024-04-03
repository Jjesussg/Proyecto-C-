#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

class Libro {
public:
    std::string titulo;
    std::string autor;
    std::string materia;

    Libro(std::string t, std::string a, std::string m) : titulo(t), autor(a), materia(m) {}

    bool operator==(const Libro& other) const {
        return titulo == other.titulo && autor == other.autor && materia == other.materia;
    }
    bool operator<(const Libro& other) const {
        return titulo < other.titulo && autor < other.autor && materia < other.materia;
    }
};

class Usuario {
public:
    std::string nombre;
    std::string identidad;
    Usuario() : nombre(""),identidad(""){}
    Usuario(std::string n, std::string id) : nombre(n), identidad(id) {}
};

class Biblioteca {
public:
    std::vector<Libro> librosDisponibles;
    std::map<Libro, Usuario> librosPrestados;

public:
    void agregarLibro(Libro libro) {
        librosDisponibles.push_back(libro);
    }

    void prestarLibro(Libro libro, Usuario usuario) {
        librosPrestados[libro] = usuario;

        // Eliminar el libro prestado de la lista de disponibles
        librosDisponibles.erase(std::remove(librosDisponibles.begin(), librosDisponibles.end(), libro), librosDisponibles.end());

        std::cout << "El libro '" << libro.titulo << "' ha sido prestado a " << usuario.nombre << std::endl;
    }

    void devolverLibro(Libro libro) {
        librosDisponibles.push_back(libro);
        librosPrestados.erase(libro);

        std::cout << "El libro '" << libro.titulo << "' ha sido devuelto" << std::endl;
    }

    bool mostrarLibrosDisponibles() {
        for (const Libro& libro : librosDisponibles) {
            std::cout << "Titulo: " << libro.titulo << ", Autor: " << libro.autor << ", Materia: " << libro.materia << std::endl;
        }
    }

    void guardarDatos(std::string archivo) {
        std::ofstream file(archivo);

        if (file.is_open()) {
            for (const Libro& libro : librosDisponibles) {
                file << "Libro: " << libro.titulo << ", Autor: " << libro.autor << ", Materia: " << libro.materia << "\n";
            }

            for (const auto& prestamo : librosPrestados) {
                file << "Libro prestado: " << prestamo.first.titulo << " a " << prestamo.second.nombre << "\n";
            }

            file.close();
            std::cout << "Datos guardados exitosamente en el archivo '" << archivo << "'" << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo para guardar los datos" << std::endl;
        }
    }
};

int main() {
    Biblioteca biblioteca;

    // Cargar datos de la biblioteca desde un archivo (si existe)
    std::ifstream file("datos_biblioteca.txt");
    if (file.is_open()) {
        std::string linea;
        while (getline(file, linea)) {
            if (linea.find("Libro: ") != std::string::npos) {
                std::string titulo, autor, materia;
                size_t pos = linea.find("Autor: ");
                titulo = linea.substr(7, pos - 8);
                pos = linea.find("Materia: ");
                autor = linea.substr(linea.find("Autor: ") + 7, pos - linea.find("Autor: ") - 8);
                materia = linea.substr(linea.find("Materia: ") + 9);

                Libro libro(titulo, autor, materia);
                biblioteca.agregarLibro(libro);
            } else if (linea.find("Libro prestado: ") != std::string::npos) {
                std::string titulo, nombreUsuario;
                size_t pos = linea.find(" a ");
                titulo = linea.substr(16, pos - 16);
                nombreUsuario = linea.substr(pos + 3);

                Libro libroPrestado(titulo, "", "");
                Usuario usuario(nombreUsuario, "");
                biblioteca.prestarLibro(libroPrestado, usuario);
            }
        }
        file.close();
        std::cout << "Datos cargados exitosamente desde el archivo 'datos_biblioteca.txt'" << std::endl;
    } else {
        std::cout << "No se encontro un archivo con datos de la biblioteca. Se creara uno nuevo al guardar los datos." << std::endl;
    }

    while (true) {
        int opcion;
        std::cout << " 1.Agregar libro \n 2.Prestar libro \n 3.Devolver libro \n 4.Mostrar libros disponibles \n 5.Guardar datos \n 6.Salir \n";
        std::cout << "Ingrese el numero de la opcion que desea realizar: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string titulo, autor, materia;
            std::cout << "Ingrese el titulo del libro: ";
            std::cin.ignore();
            getline(std::cin, titulo);
            std::cout << "Ingrese el autor del libro: ";
            getline(std::cin, autor);
            std::cout << "Ingrese la materia del libro: ";
            getline(std::cin, materia);

            Libro nuevoLibro(titulo, autor, materia);
            biblioteca.agregarLibro(nuevoLibro);
        } else if (opcion == 2) {
                biblioteca.mostrarLibrosDisponibles();
                int indiceLibro;
                std::cout << "Ingrese el numero del libro que desea prestar: ";
                std::cin >> indiceLibro;
                    indiceLibro-=1;
                if (indiceLibro >= 0 && indiceLibro < biblioteca.librosDisponibles.size()) {
                    Libro libroAPrestar = biblioteca.librosDisponibles[indiceLibro];

                    std::string nombreUsuario, identidadUsuario;
                    std::cout << "Ingrese su nombre: ";
                    std::cin.ignore();
                    getline(std::cin, nombreUsuario);
                    std::cout << "Ingrese su numero de identidad: ";
                    getline(std::cin, identidadUsuario);
                    Usuario nuevoUsuario(nombreUsuario, identidadUsuario);
                    biblioteca.prestarLibro(libroAPrestar, nuevoUsuario);
                } else {
                    std::cout << "Numero de libro invalido. Intentelo de nuevo." << std::endl;
                }

        } else if (opcion == 3) {
            if (!biblioteca.librosPrestados.empty()) {
                int i = 1;
                for (const auto& prestamo : biblioteca.librosPrestados) {
                    std::cout << i++ << ". Libro: " << prestamo.first.titulo << ", Prestado a: " << prestamo.second.nombre << "\n";
                }

                int indiceDevolver;
                std::cout << "Ingrese el numero del libro que desea devolver: ";
                std::cin >> indiceDevolver;
                indiceDevolver-=1;
                if (indiceDevolver >= 0 && indiceDevolver < biblioteca.librosPrestados.size()) {
                    auto it = biblioteca.librosPrestados.begin();
                    std::advance(it, indiceDevolver);
                    Libro libroADevolver = it->first;

                    biblioteca.devolverLibro(libroADevolver);
                } else {
                    std::cout << "Numero de libro invalido. Intentelo de nuevo." << std::endl;
                }
            } else {
                std::cout << "No hay libros prestados para devolver." << std::endl;
            }
        } else if (opcion == 4) {
            biblioteca.mostrarLibrosDisponibles();
        } else if (opcion == 5) {
            biblioteca.guardarDatos("datos_biblioteca.txt");
        } else if (opcion == 6) {
            break;
        } else {
            std::cout << "Opcion invalida. Por favor ingrese un numero valido." << std::endl;
        }
    }

    return 0;
}
