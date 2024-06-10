#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

void mostrarActividades(const string nombreUsuario) {
    string nombreArchivo = "actividades" + nombreUsuario + ".txt";
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
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

            printf("| %-10s | %-20s | %-30s | %-15s | %-10s | %-11s | %-10s |\n", numero_actividad.c_str(), nombre_actividad.c_str(), descripcion_actividad.c_str(), lugar_actividad.c_str(), fecha_actividad.c_str(), hora_inicio.c_str(), hora_final.c_str());
        }
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

int main (){
    mostrarActividades("Alex");
    return 0; 
}