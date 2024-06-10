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

int main (){    
    return 0; 
}