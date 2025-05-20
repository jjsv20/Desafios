#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool iniciarSesion(string& nombreUsuario, string& tipoRol){
    string usuario, contraseña;
    cout << "\nIngrese nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese contraseña: ";
    cin >> contraseña;
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return false;
    }
    string linea;
    while(getline(archivo, linea)){
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        string usuarioArchivo = linea.substr(0, p1);
        string passwordArchivo = linea.substr(p1 + 1, p2 - p1 - 1);
        string rolArchivo = linea.substr(p2 + 1);
        if(usuario == usuarioArchivo && contraseña == passwordArchivo){
            tipoRol = rolArchivo;
            nombreUsuario = usuario;
            return true;
        }
    }
    cout << "Usuario o contraseña incorrectos.";
    return false;
}

void menuHuesped(){
    int opcionHuesped;
    do{
        cout << "\n Menu Huesped" << endl;
        cout << "\n1. Reservar alojamieto" << endl;
        cout << "2. Anular reservacion" << endl;
        cout << "3. Mis reservaciones" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "5. Seleccione una opcion: ";
        cin >> opcionHuesped;
    }while(opcionHuesped != 4);
}

void menuAnfitrion(){
    int opcionAnfitrion;
    do {
        cout << "\n Menu Anfitrion" << endl;
        cout << "1. Consultar reservaciones" << endl;
        cout << "2. Anular reservacion" << endl;
        cout << "3. Actualizar historico" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionAnfitrion;
    }while(opcionAnfitrion != 4);
}

void menuPrincipal(){
    int opcionPrincipal;
    do {
        cout << "\n -=-=-=-= UdeAStay -=-=-=-=" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;
        if(opcionPrincipal == 1){
            string usuario, rol;
            if(iniciarSesion(usuario, rol)){
                cout << "Bienvenido, " << usuario << endl;
                if(rol == "H"){
                    menuHuesped();
                }else if(rol == "A"){
                    menuAnfitrion();
                }else{
                    cout << "Usuario no registrado";
                }
            }
        }
    }while(opcionPrincipal != 2);
}

int main()
{
    menuPrincipal();
    return 0;
}
