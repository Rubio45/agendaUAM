/*
Alex Ivan Diaz Yanez
Version 1
Login en la app de AgendaUAM
15/05/2024

Investigar conio.h
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Limpia la pantalla segun MAC o WIN, Tuve un problema con 'cls', en MAC es CLS. Esta es la solucion segun StackOverflow.
void limpiarPantalla() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
//Funcion para esperar para continuar. en Mac no puedo usar System("pause").
void esperarContinuar(){
    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia las entradas
    cin.get(); // Espera a que el usuario presione Enter
    return;
}

//Menu de inicio de la aplicacion
int menuInicio(){
    int selector;

    cout << "Bienvenido a la Agenda UAM\n";
    cout << "Elija una de estas opciones:\n";
    cout << "1. Crear un nuevo perfil de usuario" << endl;
    cout << "2. Acceder a su perfil de usuario" << endl;
    cout << "3. Salir del programa" << endl;

    cout << endl << endl;
    cout<<"Seleccion: ";
    cin >> selector;
    limpiarPantalla();

    return selector;
}

// Función para verificar si un usuario ya existe en el archivo
bool usuarioExiste(string nombreUsuario) {
    ifstream archivo("usuarios.txt"); // Abrir el archivo en modo lectura
    if (archivo.is_open()) {
        string usuario;
        while (getline(archivo, usuario)) {
            if (usuario.substr(0, usuario.find(",")) == nombreUsuario) {
                archivo.close();
                return true; // El usuario ya existe
            }
        }
        archivo.close(); // Cerrar el archivo
    }
    return false; // El usuario no existe
}

// Función para registrar un nuevo usuario
void registrarUsuario() {
    string nombreUsuario, contrasena, contrasena_verificacion;
    limpiarPantalla();

    // Obtener el usuario
    cout << "Registro de nuevo usuario\n-----------------------" << endl;
    cout << "Nombre de usuario sin espacios: ";
    cin>> nombreUsuario;

    if (usuarioExiste(nombreUsuario)) {
        cout << "El nombre de usuario ya está en uso. Por favor, elija otro nombre de usuario." << endl;
        esperarContinuar();
        limpiarPantalla();
        return;
    }
    // Obtener la contrasena
    cout << "Contrasena: ";
    cin >> contrasena;
    cout << "Repita la contrasena: ";
    cin >> contrasena_verificacion;

    // Verificar contrasena
    if (contrasena == contrasena_verificacion) {
        // Guardar los datos del usuario en un archivo txt
        ofstream archivo("usuarios.txt", ios::app); // Abrir el archivo en modo de anadir al final
        if (archivo.is_open()) {
            archivo << nombreUsuario << "," << contrasena << endl; // Guardar los datos en el archivo
            archivo.close(); // Cerrar el archivo
            cout << "Usuario registrado exitosamente." << endl;
            esperarContinuar();
            limpiarPantalla();
            return;
        } else {
            cout << "Error: No se pudo abrir el archivo para guardar los datos del usuario." << endl;
            esperarContinuar();
            return;
        }
    } else {
        cout << "Las contraseñas no coinciden. Inténtelo de nuevo." << endl;
        cout << "Registro de nuevo usuario\n\n-----------------------\n" << endl;
        esperarContinuar(); //Darle tiempo a leer el mensaje
        registrarUsuario(); // Vuelve a llamar a la función para que el usuario pueda intentarlo nuevamente
    }
}

//Funcion principal
int main() {
    limpiarPantalla();
    int selector;
    string datosUsuario, nombreUsuario, contrasena;

    do {
        selector = menuInicio();

        switch (selector) {
            case 1:
                registrarUsuario(); // Registrar un nuevo usuario
                break;
            case 2:
                // Implementar acceso al perfil de usuario
                break;
            case 3:
                cout << "Cerrando programa..." << endl;
                break;
            default:
                cout << "Comando inválido. Por favor, seleccione una opción válida.\n\n-----------------------\n" << endl;
        }
    } while (selector != 3);

    return 0;
}
