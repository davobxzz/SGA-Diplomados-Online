import java.util.Scanner;
import java.util.Stack;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class Main {

    public static void main(String[] args) {

        Scanner entrada = new Scanner(System.in);
        int opcion;

        do {
            System.out.println("\n======================================");
            System.out.println("   SGA-DO: SISTEMA DIPLOMADOSONLINE");
            System.out.println("======================================");
            System.out.println("1. Registrar Alumno");
            System.out.println("2. Registrar Profesor");
            System.out.println("3. Registrar Notas a un Alumno");
            System.out.println("4. Deshacer Último Registro de Nota");
            System.out.println("5. Generar Cola de Certificados");
            System.out.println("6. Mostrar Reporte General");
            System.out.println("7. Salir");
            System.out.println("======================================");
            System.out.print("Seleccione una opción: ");

            while (!entrada.hasNextInt()) {
                System.out.println("Error: debe introducir un número.");
                entrada.nextLine();
                System.out.print("Seleccione una opción: ");
            }

            opcion = entrada.nextInt();
            entrada.nextLine();

            switch (opcion) {
                case 1:
                    registrarAlumno(entrada);
                    break;

                case 2:
                    registrarProfesor(entrada);
                    break;

                case 3:
                    registrarNota(entrada);
                    break;
                case 4:
                    deshacerUltimaNota();
                    break;

                case 5:
                    System.out.println("Cola de certificados pendiente.");
                    break;

                case 6:
                    System.out.println("Reporte general pendiente.");
                    break;

                case 7:
                    System.out.println("Cerrando el sistema SGA-DO. ¡Hasta pronto!");
                    break;

                default:
                    System.out.println("Opción inválida. Seleccione del 1 al 7.");
            }

        } while (opcion != 7);

        entrada.close();
    }
static Stack<OperacionNota> pilaNotas = new Stack<>();

static class OperacionNota {
    String cedula;
    int posicionNota;
    String notaAnterior;
    String notaNueva;

    public OperacionNota(String cedula, int posicionNota,
                         String notaAnterior, String notaNueva) {
        this.cedula = cedula;
        this.posicionNota = posicionNota;
        this.notaAnterior = notaAnterior;
        this.notaNueva = notaNueva;
    }
}


    public static void registrarAlumno(Scanner entrada) {

        System.out.println("\n--- REGISTRO DE ALUMNO ---");

        System.out.print("Ingrese la cédula: ");
        String cedula = entrada.nextLine().trim();

        if (cedula.isEmpty() || cedula.contains(",")) {
            System.out.println("Error: cédula vacía o no válida.");
            return;
        }

        // Comprobar si la cédula ya está registrada.
        try {
            Path ruta = Path.of("alumnos.txt");

            if (Files.exists(ruta)) {
                List<String> lineas = Files.readAllLines(ruta);

                for (String linea : lineas) {
                    String[] datos = linea.split(",", -1);

                    if (datos.length > 0
                            && datos[0].equals(cedula)) {
                        System.out.println(
                            "Error: ya existe un alumno con esa cédula."
                        );
                        return;
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("Error al consultar los alumnos.");
            return;
        }

        System.out.print("Ingrese el nombre completo: ");
        String nombre = entrada.nextLine().trim();

        System.out.print("Ingrese el correo electrónico: ");
        String correo = entrada.nextLine().trim();

        if (nombre.isEmpty() || correo.isEmpty()
                || nombre.contains(",") || correo.contains(",")) {
            System.out.println(
                "Error: los datos no pueden estar vacíos ni contener comas."
            );
            return;
        }

        String programa;

        while (true) {
            System.out.println("Seleccione el programa académico:");
            System.out.println("1. Curso");
            System.out.println("2. Diplomado");
            System.out.println("3. Bootcamp");
            System.out.print("Opción: ");

            String opcionPrograma = entrada.nextLine().trim();

            switch (opcionPrograma) {
                case "1":
                    programa = "Curso";
                    break;
                case "2":
                    programa = "Diplomado";
                    break;
                case "3":
                    programa = "Bootcamp";
                    break;
                default:
                    System.out.println("Opción inválida. Intente otra vez.");
                    continue;
            }

            break;
        }

        // Cada alumno comienza con tres notas en cero.
        String registro = cedula + "," + nombre + "," + correo + ","
                + programa + ",0,0,0";

        // Guardar el alumno al final del archivo.
        try (FileWriter escritor = new FileWriter("alumnos.txt", true)) {
            escritor.write(registro + System.lineSeparator());

            System.out.println("\n¡Alumno registrado correctamente!");
            System.out.println("Nombre: " + nombre);
            System.out.println("Programa: " + programa);

        } catch (IOException e) {
            System.out.println("Error al guardar el alumno.");
            System.out.println("Detalle: " + e.getMessage());
        }
    }

    public static void registrarProfesor(Scanner entrada) {

    System.out.println("\n--- REGISTRO DE PROFESOR ---");

    System.out.print("Ingrese la cédula: ");
    String cedula = entrada.nextLine().trim();

    if (cedula.isEmpty() || cedula.contains(",")) {
        System.out.println("Error: cédula vacía o no válida.");
        return;
    }

    // Comprobar que la cédula no esté registrada.
    try {
        Path ruta = Path.of("profesores.txt");

        if (Files.exists(ruta)) {
            List<String> lineas = Files.readAllLines(ruta);

            for (String linea : lineas) {
                String[] datos = linea.split(",", -1);

                if (datos.length > 0 && datos[0].equals(cedula)) {
                    System.out.println(
                        "Error: ya existe un profesor con esa cédula."
                    );
                    return;
                }
            }
        }
    } catch (IOException e) {
        System.out.println("Error al consultar los profesores.");
        return;
    }

    System.out.print("Ingrese el nombre completo: ");
    String nombre = entrada.nextLine().trim();

    System.out.print("Ingrese el correo electrónico: ");
    String correo = entrada.nextLine().trim();

    System.out.print("Ingrese la especialidad: ");
    String especialidad = entrada.nextLine().trim();

    System.out.print("Ingrese la materia asignada: ");
    String materia = entrada.nextLine().trim();

    if (nombre.isEmpty() || correo.isEmpty()
            || especialidad.isEmpty() || materia.isEmpty()
            || nombre.contains(",") || correo.contains(",")
            || especialidad.contains(",") || materia.contains(",")) {

        System.out.println(
            "Error: los campos no pueden estar vacíos ni contener comas."
        );
        return;
    }

    // Organizar los datos en el formato del archivo.
    String registro = cedula + "," + nombre + "," + correo + ","
            + especialidad + "," + materia;

    // Guardar el profesor sin borrar los registros anteriores.
    try (FileWriter escritor =
            new FileWriter("profesores.txt", true)) {

        escritor.write(registro + System.lineSeparator());

        System.out.println("\n¡Profesor registrado correctamente!");
        System.out.println("Nombre: " + nombre);
        System.out.println("Especialidad: " + especialidad);
        System.out.println("Materia: " + materia);

    } catch (IOException e) {
        System.out.println("Error al guardar el profesor.");
        System.out.println("Detalle: " + e.getMessage());
    }
}
    public static void registrarNota(Scanner entrada) {

    System.out.println("\n--- REGISTRO DE NOTAS ---");

    File archivo = new File("alumnos.txt");

    if (!archivo.exists()) {
        System.out.println("No existe el archivo de alumnos.");
        return;
    }

    System.out.print("Ingrese la cédula del alumno: ");
    String cedula = entrada.nextLine().trim();

    try {
        List<String> lineas = Files.readAllLines(archivo.toPath());

        boolean encontrado = false;
        boolean actualizado = false;

        for (int i = 0; i < lineas.size(); i++) {

            String[] datos = lineas.get(i).split(",", -1);

            if (datos.length != 7) {
                continue;
            }

            if (datos[0].equals(cedula)) {

                encontrado = true;

                System.out.println("Alumno: " + datos[1]);
                System.out.println("Programa: " + datos[3]);
                System.out.println("Nota 1: " + datos[4]);
                System.out.println("Nota 2: " + datos[5]);
                System.out.println("Nota 3: " + datos[6]);

                int posicion = -1;

                // Buscar el primer espacio de nota disponible.
                for (int j = 4; j <= 6; j++) {
                    if (datos[j].equals("0")) {
                        posicion = j;
                        break;
                    }
                }

                if (posicion == -1) {
                    System.out.println(
                        "El alumno ya tiene sus tres notas registradas."
                    );
                    break;
                }

                System.out.print("Ingrese la nueva nota (0 a 20): ");

                String entradaNota = entrada.nextLine().trim();
                double nota;

                try {
                    nota = Double.parseDouble(
                        entradaNota.replace(',', '.')
                    );
                } catch (NumberFormatException e) {
                    System.out.println("Error: debe introducir un número.");
                    break;
                }

                if (nota < 0 || nota > 20) {
                    System.out.println(
                        "Error: la nota debe estar entre 0 y 20."
                    );
                    break;
                }

                String notaAnterior = datos[posicion];
                String notaNueva = String.valueOf(nota);

                  datos[posicion] = notaNueva;
                  lineas.set(i, String.join(",", datos));

                  try {
                  Files.write(archivo.toPath(), lineas);

                   pilaNotas.push(new OperacionNota(
                 cedula,
                 posicion,
                 notaAnterior,
                 notaNueva
    ));

    System.out.println("¡Nota registrada correctamente!");

} catch (IOException e) {
    System.out.println("Error al guardar la nota.");
}

return;

            }
        }

        if (!encontrado) {
            System.out.println("No se encontró un alumno con esa cédula.");
            return;
        }

        if (actualizado) {
            Files.write(archivo.toPath(), lineas);
            System.out.println("¡Nota registrada correctamente!");
        }

    } catch (IOException e) {
        System.out.println("Error al leer o actualizar alumnos.txt.");
        System.out.println("Detalle: " + e.getMessage());
    }
}
    public static void deshacerUltimaNota() {

    if (pilaNotas.empty()) {
        System.out.println(
            "No hay notas registradas en esta sesión para deshacer."
        );
        return;
    }

    OperacionNota operacion = pilaNotas.peek();
    File archivo = new File("alumnos.txt");

    try {
        List<String> lineas = Files.readAllLines(archivo.toPath());
        boolean encontrado = false;

        for (int i = 0; i < lineas.size(); i++) {
            String[] datos = lineas.get(i).split(",", -1);

            if (datos.length == 7
                    && datos[0].equals(operacion.cedula)) {

                // Evitar deshacer si la nota fue modificada por otro medio.
                if (!datos[operacion.posicionNota]
                        .equals(operacion.notaNueva)) {
                    System.out.println(
                        "No se puede deshacer: la nota cambió."
                    );
                    return;
                }

                datos[operacion.posicionNota] =
                    operacion.notaAnterior;

                lineas.set(i, String.join(",", datos));
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            System.out.println("No se encontró el alumno.");
            return;
        }

        Files.write(archivo.toPath(), lineas);
        pilaNotas.pop();

        System.out.println("Última nota deshecha correctamente.");
        System.out.println(
            "Se restauró el valor anterior: "
            + operacion.notaAnterior
        );

    } catch (IOException e) {
        System.out.println("Error al deshacer la nota.");
        System.out.println("Detalle: " + e.getMessage());
    }
}




        }
    



    