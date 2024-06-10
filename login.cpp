/*
Alex Ivan Diaz Yanez
Version 1
Login en la app de AgendaUAM
15/05/2024
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Limpia la pantalla segun MAC o Windows, Tuve un problema con 'cls', en MAC es CLS. Esta es la solucion segun StackOverflow.
void limpiarPantalla() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
//Funcion para esperar para continuar. en Mac no puedo usar System("pause")
void esperarContinuar(){
    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia las entradas
    cin.get(); // Espera a que el usuario presione Enter
    return;
}

void limpiarBuffer() {
    cin.clear(); // Limpia los errores
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
}
int stringToInt(const string &str) {
    try {
        int num = stoi(str); // Convierte el string a int
        return num;
    } catch (const invalid_argument &e) {
        cerr << "Error: argumento no válido. La cadena no contiene un número válido." << endl;
    } catch (const out_of_range &e) {
        cerr << "Error: argumento fuera de rango. El número es demasiado grande." << endl;
    }
    return 0; // Retorna 0 en caso de error
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
            cout <<"----------------------------\n";
            cout << "Usuario registrado exitosamente." << endl;
            cout <<"----------------------------\n\n";
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

struct resultadoSesion{
    int estado; //1 para bien, 0 para mal
    string nombreUsuario;
};
resultadoSesion iniciarSesion() {
    string nombreUsuario, contrasena, contrasena_introducida, usuario, nombre_usuario;
    bool usuarioEncontrado = false;
    limpiarPantalla();
    cout << "Introduzca su nombre de usuario: ";
    cin >> nombreUsuario;
    cout << "Introduzca su contrasena: ";
    cin >> contrasena_introducida;

    ifstream archivo("usuarios.txt"); // Abrir el archivo en modo lectura
    if (archivo.is_open()) {
        
        while (getline(archivo, usuario)) {
            nombre_usuario = usuario.substr(0, usuario.find(","));
            contrasena = usuario.substr(usuario.find(",") + 1); // desde la coma hasta el final de la cadena para retornar la contrasena

            if (nombre_usuario == nombreUsuario) {
                usuarioEncontrado = true;
                if (contrasena == contrasena_introducida) {
                    limpiarPantalla();
                    cout <<"----------------------------\n";
                    cout << "Inicio de sesión exitoso\n";
                    cout <<"----------------------------\n\n";
                    esperarContinuar();
                    limpiarPantalla();
                    archivo.close();
                    return {1, nombreUsuario};
                } else {
                    cout << "Contraseña no válida\n";
                    esperarContinuar();
                    limpiarPantalla();
                    break;
                }
            }
        }
        if (!usuarioEncontrado) {
            cout << "Usuario no existe\n";
            esperarContinuar();
            limpiarPantalla();
        }
    } else {
        cout << "No se pudo abrir el archivo de usuarios\n";
    }
    archivo.close();
    return {0, ""};
}
//Menu principal del programa
int menuPrincipal(string nombreUsuario){
    int selector;

    cout << "Hola, " << nombreUsuario<< endl;
    cout << "-------------------------------"<< endl;
    cout << "Elija una de estas opciones:\n";
    cout << "1. Registrar una nueva actividad" << endl;
    cout << "2. Modificar una actividad" << endl;
    cout << "3. Eliminar una actividad" << endl;
    cout << "4. Revisar actividades"<< endl;
    cout << "0. Salir";

    cout << endl << endl;
    cout<<"Seleccion: ";
    cin >> selector;
    limpiarPantalla();

    return selector;
}
struct Fecha{
    int dia, annio, mes;
};
struct ActividadDatos{
    Fecha fecha_actividad;
    string nombre_actividad, descripcion_actividad, lugar_actividad, nombreUsuario;
    int hora_inicio, hora_final, numero_actividad;
};

int obtenerUltimoNumeroActividad(const string& nombreUsuario) {
    string nombreArchivo = "actividades" + nombreUsuario + ".txt";
    ifstream archivo(nombreArchivo);
    int ultimoNumero = 0;

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            // obtener la posicion de la , para sacar el string
            size_t pos = linea.find(",");
            if (pos != string::npos) {
                string numeroActividadStr = linea.substr(0, pos);
                try {
                    //convertir string a int
                    int numeroActividad = stoi(numeroActividadStr);
                    // actualizar numero de la actividad para que no sea 0
                    if (numeroActividad > ultimoNumero) {
                        ultimoNumero = numeroActividad;
                    }
                } catch (const invalid_argument& e) {
                    cout << "Error: Número de actividad no válido en el archivo.\n";
                } catch (const out_of_range& e) {
                    cout << "Error: Número de actividad fuera de rango en el archivo.\n";
                }
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de actividades.\n";
    }
    // devolver el numero de la actividad + 1
    return ultimoNumero + 1;
}

ActividadDatos ingresarDatos(string nombreUsuario){
    ActividadDatos registro_actividad;
    registro_actividad.nombreUsuario = nombreUsuario;
    registro_actividad.numero_actividad = obtenerUltimoNumeroActividad(nombreUsuario);
    limpiarPantalla();
    limpiarBuffer();
    cout << "Introduzca el nombre de la actividad: ";
    getline(cin, registro_actividad.nombre_actividad);

    cout << "Introduzca la descripcion de la actividad: ";
    getline(cin, registro_actividad.descripcion_actividad);

    cout << "Introduzca el lugar de la actividad: ";
    getline(cin, registro_actividad.lugar_actividad);
    cout << "Ingrese la fecha de la actividad(formato: Dia Mes Año): ";
    cin >> registro_actividad.fecha_actividad.dia >> registro_actividad.fecha_actividad.mes >> registro_actividad.fecha_actividad.annio;

    cout << "Ingrese la hora de inicio (formato militar 1921): ";
    cin >> registro_actividad.hora_inicio;

    cout << "Ingrese la hora de fin (formato militar 1951): ";
    cin >> registro_actividad.hora_final;

    return registro_actividad;

}
void guardarDatosActividad(ActividadDatos& actividad) {
    string nombre_archivo = "actividades" + actividad.nombreUsuario + ".txt";
    ofstream archivo(nombre_archivo, ios::app); //Abre el archivo en modo escribir al final, usando tambien el nombre de usuario para identificarlos. 
    if (archivo.is_open()) {
        archivo << actividad.numero_actividad << ","
                << actividad.nombre_actividad << ","
                << actividad.descripcion_actividad << ","
                << actividad.lugar_actividad << ","
                << actividad.fecha_actividad.dia << "/"
                << actividad.fecha_actividad.mes << "/"
                << actividad.fecha_actividad.annio << ","
                << actividad.hora_inicio << ","
                << actividad.hora_final << "\n";
        archivo.close();
        limpiarPantalla();
    } else {
        cout << "No se pudo abrir el archivo para guardar los datos.\n";
        limpiarPantalla();
    }
}
void mostrarActividades(const string nombreUsuario) {
    string nombreArchivo = "actividades" + nombreUsuario + ".txt";
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        printf("|------------|----------------------|--------------------------------|-----------------|------------|-------------|------------|\n");
        printf("| %-10s | %-20s | %-30s | %-15s | %-10s | %-10s | %-10s |\n", "ID", "Nombre de actividad", "Descripcion de actividad", "Lugar", "Fecha", "Hora Inicio", "Hora Final");
        printf("|------------|----------------------|--------------------------------|-----------------|------------|-------------|------------|\n");

        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string numero_actividad, nombre_actividad, descripcion_actividad, lugar_actividad, fecha_actividad, hora_inicio, hora_final;

            getline(ss, numero_actividad, ',');
            getline(ss, nombre_actividad, ',');
            getline(ss, descripcion_actividad, ',');
            getline(ss, lugar_actividad, ',');
            getline(ss, fecha_actividad, ',');
            getline(ss, hora_inicio, ',');
            getline(ss, hora_final, ',');

            printf("| %-10s | %-20s | %-30s | %-15s | %-10s | %-11s | %-10s |\n", numero_actividad.c_str(),nombre_actividad.c_str(), descripcion_actividad.c_str(), lugar_actividad.c_str(), fecha_actividad.c_str(), hora_inicio.c_str(), hora_final.c_str());
            printf("|------------|----------------------|--------------------------------|-----------------|------------|-------------|------------|\n");
        }
        esperarContinuar();
        limpiarPantalla();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}

void eliminarActividad(const string nombreUsuario){
    string nombreArchivo = "actividades" + nombreUsuario + ".txt";
    int numero;
    bool existeNumero=true;
    ActividadDatos registro_actividades;
    ifstream archivo(nombreArchivo);
    mostrarActividades(nombreUsuario);
    cout << "\n\n--------------------------------------------------------\nIntroduzca el numero de actividad que desea eliminar\n--------------------------------------------------------\nNumero: ";
    cin >> numero;
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string numero_actividad, nombre_actividad, descripcion_actividad, lugar_actividad, fecha_actividad, hora_inicio, hora_final;
            getline(ss, numero_actividad, ',');
            registro_actividades.numero_actividad = stringToInt(numero_actividad);
            if (registro_actividades.numero_actividad != numero){
            existeNumero = false;
            getline(ss, nombre_actividad, ',');
            getline(ss, descripcion_actividad, ',');
            getline(ss, lugar_actividad, ',');
            getline(ss, fecha_actividad, ',');
            getline(ss, hora_inicio, ',');
            getline(ss, hora_final, ',');

            size_t primer_slash = fecha_actividad.find('/');
            size_t segundo_slash = fecha_actividad.find('/', primer_slash + 1);

            registro_actividades.nombre_actividad = nombre_actividad;
            registro_actividades.descripcion_actividad = descripcion_actividad;
            registro_actividades.lugar_actividad = lugar_actividad;
            registro_actividades.fecha_actividad.dia = stringToInt(fecha_actividad.substr(0, primer_slash));
            registro_actividades.fecha_actividad.mes = stringToInt(fecha_actividad.substr(primer_slash + 1, segundo_slash-primer_slash-1));
            registro_actividades.fecha_actividad.annio = stringToInt(fecha_actividad.substr(segundo_slash+1));
            registro_actividades.hora_inicio = stringToInt(hora_inicio);
            registro_actividades.hora_final = stringToInt(hora_final);
            guardarDatosActividad(registro_actividades);
            limpiarPantalla();
            }
        }
        if (existeNumero){
                limpiarPantalla();
                cout<<"El numero de la actividad que proporcionaste no existe";
                esperarContinuar();
                limpiarPantalla();
        }
        cout << "--------------------\nActividad eliminada\n--------------------\n";
        limpiarBuffer();
        esperarContinuar();
        archivo.close();
        remove(nombreArchivo.c_str());
        rename("actividades.txt", nombreArchivo.c_str());

    }
}

//Funcion principal
int main() {
    limpiarPantalla();
    int selectorInicio, selectorPrincipal;
    string datosUsuario, nombreUsuario, contrasena;
    resultadoSesion resultado_sesion;

    do {
        selectorInicio = menuInicio();

        switch (selectorInicio) {
            case 1:
                registrarUsuario(); //Registrar un nuevo usuario
                break;
            case 2:
                resultado_sesion = iniciarSesion();
                if (resultado_sesion.estado == 1){
                    
                    do {
        selectorPrincipal = menuPrincipal(resultado_sesion.nombreUsuario);
        switch (selectorPrincipal) {
            case 1:
                {
                    ActividadDatos datos_actividad = ingresarDatos(resultado_sesion.nombreUsuario);
                    guardarDatosActividad(datos_actividad);
                }
                break;
            case 2:
                cout << "Funcion de modificar actividad";
                break;
            case 3:
                eliminarActividad(resultado_sesion.nombreUsuario);
                break;
            case 4:
                mostrarActividades(resultado_sesion.nombreUsuario);
                cout << "Funcion de ordenar actividades incluidas";
                break;
            case 0:
                break;
            default:
                cout << "\n---------------------------\nElija una opcion del 0 al 4\n----------------------------\n";
                break;
        }
    } while (selectorPrincipal != 0);

                }
            case 3:
                cout << "Cerrando programa..." << endl;
                break;
            default:
                cout << "Comando inválido. Por favor, seleccione una opción válida.\n\n-----------------------\n" << endl;
        }
    } while (selectorInicio != 3);

    return 0;
}
