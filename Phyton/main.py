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
    print("\n--- REGISTRO DE NOTA ---")

    cedula_buscada = input("Ingrese la cédula del alumno: ")

    encontrado = False
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

                elif datos[5] == "0":
                    datos[5] = str(nota)

                elif datos[6] == "0":
                    datos[6] = str(nota)

                else:
                    print("El alumno ya tiene las 3 notas registradas.")

                encontrado = True

            linea_actualizada = ",".join(datos) + "\n"
            lineas_nuevas.append(linea_actualizada)

    if encontrado:
        with open("alumnos.txt", "w", encoding="utf-8") as archivo:
            archivo.writelines(lineas_nuevas)

        print("\nNota registrada correctamente.")

    else:
        print("\nAlumno no encontrado.")
   
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

    if opcion == "7":
        print("Cerrando SGA Diplomados Online")
        break 

3