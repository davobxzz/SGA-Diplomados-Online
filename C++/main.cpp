#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// ESTRUCTURA PARA GUARDAR OPERACIONES DE NOTAS
struct OperacionNota {
    string cedula;
    int posicionNota;
    string notaAnterior;
    string notaNueva;
};

// Pila para almacenar las operaciones
stack<OperacionNota> pilaNotas;

// REGISTRAR ALUMNO
void registrarAlumno() {

    string cedula, nombre, correo, programa;
    string linea, cedulaGuardada;

    cout << "\n===== REGISTRO DE ALUMNO =====" << endl;

    cout << "Ingrese la cedula: ";
    getline(cin, cedula);

    cout << "Ingrese el nombre: ";
    getline(cin, nombre);

    cout << "Ingrese el correo: ";
    getline(cin, correo);

    cout << "Tipo de programa (Curso, Diplomado o Bootcamp): ";
    getline(cin, programa);

    if (cedula.empty() || nombre.empty() ||
        correo.empty() || programa.empty() ||
        cedula.find(',') != string::npos ||
        nombre.find(',') != string::npos ||
        correo.find(',') != string::npos ||
        programa.find(',') != string::npos) {

        cout << "Error: datos vacios o con comas no permitidas." << endl;
        return;
    }

    ifstream archivoLectura("alumnos.txt");

    while (getline(archivoLectura, linea)) {

        size_t posicion = linea.find(',');

        if (posicion != string::npos) {
            cedulaGuardada = linea.substr(0, posicion);

            if (cedulaGuardada == cedula) {
                cout << "Error: ya existe un alumno con esa cedula." << endl;
                return;
            }
        }
    }

    archivoLectura.close();

    ofstream archivo("alumnos.txt", ios::app);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de alumnos." << endl;
        return;
    }

    archivo << cedula << "," << nombre << ","
            << correo << "," << programa << ",0,0,0\n";

    archivo.close();

    cout << "Alumno registrado correctamente." << endl;
}

// REGISTRAR PROFESOR
void registrarProfesor() {

    string cedula, nombre, correo;
    string especialidad, materia;
    string linea, cedulaGuardada;

    cout << "\n===== REGISTRO DE PROFESOR =====" << endl;

    cout << "Ingrese la cedula: ";
    getline(cin, cedula);

    cout << "Ingrese el nombre: ";
    getline(cin, nombre);

    cout << "Ingrese el correo: ";
    getline(cin, correo);

    cout << "Ingrese la especialidad: ";
    getline(cin, especialidad);

    cout << "Ingrese la materia: ";
    getline(cin, materia);

    if (cedula.empty() || nombre.empty() ||
        correo.empty() || especialidad.empty() ||
        materia.empty() || cedula.find(',') != string::npos ||
        nombre.find(',') != string::npos ||
        correo.find(',') != string::npos ||
        especialidad.find(',') != string::npos ||
        materia.find(',') != string::npos) {

        cout << "Error: datos vacios o con comas no permitidas." << endl;
        return;
    }

    ifstream archivoLectura("profesores.txt");

    while (getline(archivoLectura, linea)) {

        size_t posicion = linea.find(',');

        if (posicion != string::npos) {
            cedulaGuardada = linea.substr(0, posicion);

            if (cedulaGuardada == cedula) {
                cout << "Error: ya existe un profesor con esa cedula." << endl;
                return;
            }
        }
    }

    archivoLectura.close();

    ofstream archivo("profesores.txt", ios::app);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de profesores." << endl;
        return;
    }

    archivo << cedula << "," << nombre << ","
            << correo << "," << especialidad << ","
            << materia << "\n";

    archivo.close();

    cout << "Profesor registrado correctamente." << endl;
}

// REGISTRAR NOTAS
void registrarNota() {

    string cedula, linea;
    vector<string> alumnos;
bool encontrado = false;
    bool notaRegistrada = false;
    OperacionNota operacion;

    cout << "\n===== REGISTRO DE NOTAS =====" << endl;
    cout << "Ingrese la cedula del alumno: ";
    getline(cin, cedula);

    ifstream archivoLectura("alumnos.txt");

    if (!archivoLectura.is_open()) {
        cout << "No existe el archivo de alumnos." << endl;
        return;
    }

    while (getline(archivoLectura, linea)) {

        stringstream flujo(linea);
        vector<string> datos;
        string campo;

        while (getline(flujo, campo, ',')) {
            datos.push_back(campo);
        }

        if (datos.size() != 7) {
            alumnos.push_back(linea);
            continue;
        }

        if (datos[0] == cedula) {

            encontrado = true;

            cout << "\nAlumno: " << datos[1] << endl;
            cout << "Programa: " << datos[3] << endl;
            cout << "Nota 1: " << datos[4] << endl;
            cout << "Nota 2: " << datos[5] << endl;
            cout << "Nota 3: " << datos[6] << endl;

            int posicion = -1;

            for (int i = 4; i <= 6; i++) {
                if (datos[i] == "0") {
                    posicion = i;
                    break;
                }
            }

            if (posicion == -1) {
                cout << "El alumno ya tiene tres notas." << endl;
                alumnos.push_back(linea);
                continue;
            }

            double nota;

            cout << "Ingrese la nueva nota (0 a 20): ";

            if (!(cin >> nota)) {
                cout << "Error: debe introducir un numero." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                alumnos.push_back(linea);
                archivoLectura.close();
                return;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (nota < 0 || nota > 20) {
                cout << "La nota debe estar entre 0 y 20." << endl;
                alumnos.push_back(linea);
                archivoLectura.close();
                return;
            }

            stringstream conversor;
            conversor << fixed << setprecision(2) << nota;
            string notaAnterior = datos[posicion];
            string notaNueva = conversor.str();

            datos[posicion] = notaNueva;

            operacion.cedula = cedula;
            operacion.posicionNota = posicion;
            operacion.notaAnterior = notaAnterior;
            operacion.notaNueva = notaNueva;

            string nuevaLinea;
            for (size_t i = 0; i < datos.size(); i++) {
                if (i > 0) nuevaLinea += ",";
                nuevaLinea += datos[i];
            }

            alumnos.push_back(nuevaLinea);
            notaRegistrada = true;

            cout << "Nota registrada correctamente." << endl;

        } else {
            alumnos.push_back(linea);
        }
    }

    archivoLectura.close();

    if (!encontrado) {
        cout << "No se encontro un alumno con esa cedula." << endl;
        return;
    }

    if (!notaRegistrada) {
        return;
    }

    ofstream archivoEscritura("alumnos.txt");

    if (!archivoEscritura.is_open()) {
        cout << "Error al guardar las notas." << endl;
        return;
    }

    for (const string& registro : alumnos) {
        archivoEscritura << registro << "\n";
    }

    archivoEscritura.close();

    // Guardar la operacion en la pila
    pilaNotas.push(operacion);

    cout << "Nota guardada en el historial de operaciones." << endl;

}


void deshacerUltimaNota() {

    if (pilaNotas.empty()) {
        cout << "No hay notas para deshacer en esta sesion." << endl;
        return;
    }

    OperacionNota operacion = pilaNotas.top();

    ifstream archivoLectura("alumnos.txt");

    if (!archivoLectura.is_open()) {
        cout << "No se pudo abrir alumnos.txt." << endl;
        return;
    }

    vector<string> alumnos;
    string linea;
    bool encontrado = false;

    while (getline(archivoLectura, linea)) {

        stringstream flujo(linea);
        vector<string> datos;
        string campo;

        while (getline(flujo, campo, ',')) {
            datos.push_back(campo);
        }

        if (datos.size() == 7 &&
            datos[0] == operacion.cedula) {

            if (datos[operacion.posicionNota] != operacion.notaNueva) {
                cout << "No se puede deshacer: la nota fue modificada." << endl;
                archivoLectura.close();
                return;
            }

            datos[operacion.posicionNota] = operacion.notaAnterior;

            string nuevaLinea;

            for (size_t i = 0; i < datos.size(); i++) {
                if (i > 0) nuevaLinea += ",";
                nuevaLinea += datos[i];
            }

            alumnos.push_back(nuevaLinea);
            encontrado = true;

        } else {
            alumnos.push_back(linea);
        }
    }

    archivoLectura.close();

    if (!encontrado) {
        cout << "No se encontro el alumno." << endl;
        return;
    }

    ofstream archivoEscritura("alumnos.txt");

    if (!archivoEscritura.is_open()) {
        cout << "Error al guardar los cambios." << endl;
        return;
    }

    for (const string& registro : alumnos) {
        archivoEscritura << registro << "\n";
    }

    archivoEscritura.close();

    pilaNotas.pop();

    cout << "Ultima nota deshecha correctamente." << endl;
    cout << "Se restauro el valor anterior: "
         << operacion.notaAnterior << endl;
}

// MENU PRINCIPAL
int main() {

    int opcion;

    do {

        cout << "\n========================================" << endl;
        cout << " SGA-DO: SISTEMA DE GESTION ACADEMICA" << endl;
        cout << "========================================" << endl;

        cout << "1. Registrar Alumno" << endl;
        cout << "2. Registrar Profesor" << endl;
        cout << "3. Registrar Notas" << endl;
        cout << "4. Deshacer Ultimo Registro de Nota" << endl;
        cout << "5. Cola de Certificados" << endl;
        cout << "6. Reporte General" << endl;
        cout << "7. Salir" << endl;

        cout << "\nSeleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Debe ingresar un numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {

            case 1:
                registrarAlumno();
                break;

            case 2:
                registrarProfesor();
                break;

            case 3:
                registrarNota();
                break;

            case 4:
                deshacerUltimaNota();
                break;

            case 5:
                cout << "Opcion: Cola de Certificados" << endl;
                break;

            case 6:
                cout << "Opcion: Reporte General" << endl;
                break;

            case 7:
                cout << "Gracias por utilizar el sistema SGA-DO." << endl;
                break;

            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }

    } while (opcion != 7);

    return 0;
}


