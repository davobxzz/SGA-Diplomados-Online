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

    if opcion == "7":
        print("Cerrando SGA Diplomados Online")
        break 
