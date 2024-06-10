#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <cstdio>

using namespace std;

struct Fecha{
    int dia, annio, mes;
};
struct ActividadDatos{
    Fecha fecha_actividad;
    string nombre_actividad, descripcion_actividad, lugar_actividad, nombreUsuario;
    int hora_inicio, hora_final, numero_actividad;
};
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
        cout << "Datos guardados exitosamente.\n";
        cout << "---------------------------------\n";
    } else {
        cout << "No se pudo abrir el archivo para guardar los datos.\n";
    }
}

void eliminarActividad(const string nombreUsuario){
    string nombreArchivo = "actividades" + nombreUsuario + ".txt";
    int numero;
    bool existeNumero;
    ActividadDatos registro_actividades;
    ifstream archivo(nombreArchivo);
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
            //limpiar pantalla
            }
            if (existeNumero)
            {
                // limpiar pantalla
                cout<<"El numero de la actividad que proporcionaste no existe";
                // esperar
            }
        }
        cout << "Tarea eliminada";
            // esperar
        archivo.close();
        remove(nombreArchivo.c_str());
        rename("actividades.txt", nombreArchivo.c_str());

    }
}
int main (){    
    eliminarActividad("Alex");
    return 0; 
}