#include <iostream>
#include <string>

using namespace std;

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
        cin >> opcion;

        switch (opcion) {

            case 1:
                cout << "Opcion: Registrar Alumno" << endl;
                break;

            case 2:
                cout << "Opcion: Registrar Profesor" << endl;
                break;

            case 3:
                cout << "Opcion: Registrar Notas" << endl;
                break;

            case 4:
                cout << "Opcion: Deshacer Ultimo Registro de Nota" << endl;
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


