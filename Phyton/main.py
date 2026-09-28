pila_notas = []
def registrar_alumno():

    print("/n Registro de Alumno")
    cedula = input("Ingrese la cedula:")
    nombre = input("Ingrese el nombre:")
    correo = input("Ingrese el correo:")
    programa = input("Ingrese el programa:")

    nota1 = 0
    nota2 = 0
    nota3 = 0

    with open("alumnos.txt","a",
              encoding="utf-8") as archivo:
                        archivo.write(f"{cedula},{nombre},{correo},{programa},{nota1},{nota2},{nota3}\n")

                            
    print("Alumno registrado con exito")
def registrar_profesor():
        
        print("/n Registro de Profesor")
        cedula = input("Ingrese la cedula:")
        nombre = input("Ingrese el nombre:")
        correo = input("Ingrese el correo:")
        especialidad = input("Ingrese la especialidad:")

        with open("profesores.txt","a", encoding="utf-8") as archivo:
            archivo.write(f"{cedula},{nombre},{correo},{especialidad}\n")

        print("Profesor registrado con exito")


        encontrado = True
def registrar_nota():

    print("/n Registro de Notas")

    cedula_buscada = input("Ingrese la cédula del alumno: ")

    encontrado = False
    posicion_nota = None
    lineas_nuevas = []

    with open("alumnos.txt", "r", encoding="utf-8") as archivo:
        lineas = archivo.readlines()

        for linea in lineas:
            datos = linea.strip().split(",")

            if datos[0] == cedula_buscada:
                print("\nAlumno encontrado.")
                print("Nombre:", datos[1])
                print("Programa:", datos[3])
                print("Notas actuales:", datos[4], datos[5], datos[6])

                nota = float(input("Ingrese la nueva nota: "))

                if datos[4] == "0":
                    datos[4] = str(nota)
                    posicion_nota = 4

                elif datos[5] == "0":
                    datos[5] = str(nota)
                    posicion_nota = 5

                elif datos[6] == "0":
                    datos[6] = str(nota)
                    posicion_nota = 6

                else:
                    print("El alumno ya tiene las 3 notas registradas.")

                encontrado = True

            linea_actualizada = ",".join(datos) + "\n"
            lineas_nuevas.append(linea_actualizada)

    if encontrado:

        with open("alumnos.txt", "w", encoding="utf-8") as archivo:
            archivo.writelines(lineas_nuevas)

        # Guardamos la acción en la pila
        if posicion_nota is not None:
            pila_notas.append(
                (cedula_buscada, posicion_nota, str(nota))
            )

        print("\nNota registrada correctamente.")

    else:
        print("\nAlumno no encontrado.")
def deshacer_nota():

    # Verificamos si la pila está vacía
    if not pila_notas:
        print("\nNo hay notas para deshacer.")
        return

    # Sacamos la última acción de la pila
    ultima_accion = pila_notas.pop()

    # Recuperamos los datos guardados
    cedula = ultima_accion[0]
    posicion = ultima_accion[1]

    lineas_nuevas = []

    # Abrimos el archivo para leerlo
    with open("alumnos.txt", "r", encoding="utf-8") as archivo:
        lineas = archivo.readlines()

        for linea in lineas:

            datos = linea.strip().split(",")

            # Buscamos al alumno correspondiente
            if datos[0] == cedula:

                # Eliminamos la última nota registrada
                datos[posicion] = "0"

            # Reconstruimos la línea
            linea_actualizada = ",".join(datos) + "\n"
            lineas_nuevas.append(linea_actualizada)

    # Guardamos nuevamente el archivo
    with open("alumnos.txt", "w", encoding="utf-8") as archivo:
        archivo.writelines(lineas_nuevas)

    print("\nÚltimo registro de nota deshecho correctamente.")
while True:
    print("SGA Diplomados Online")
    print("1. Registrar Alumno")
    print("2. Registrar Profesor")
    print("3. Registrar Notas")
    print("4. Deshacer ultimo registro de notas")
    print("5. Generar cola de certificados")
    print("6. Mostrar reporte general")
    print("7. Salir")

    opcion = input("Seleccione una opcion del 1 al 7: ")


    if opcion == "1":
            registrar_alumno()


    if opcion == "2":
        registrar_profesor()

    if opcion == "3":
              registrar_nota()

    if opcion == "4":
             deshacer_nota()

    if opcion == "7":
        print("Cerrando SGA Diplomados Online")
        break 


