#include <QCoreApplication>
#include <QImage>
#include <fstream>
#include <iostream>

using namespace std;

//Funciones**************************************************
unsigned char* cargarImagen(QString input, int &ancho, int &alto);
bool guardarImagen(unsigned char* datosPixel, int ancho, int alto, QString rutaSalida);
unsigned int* cargarMascara(const char* nombreArchivo, int &seed, int &num_pixels);
void aplicarXOR(unsigned char* imagenfinal, unsigned char* idistorcionada, int tamaño);
void rotacionBits(unsigned char* datos, int tamaño, int totalBits);


//Función para cargar los pixeles de una imagen*********************
unsigned char* cargarImagen(QString input, int &ancho, int &alto) {
    QImage imagen(input);
    if (imagen.isNull()) {
        cout << "Error: No se pudo cargar la imagen." << endl;
        return nullptr;
    }
    imagen = imagen.convertToFormat(QImage::Format_RGB888);
    ancho = imagen.width();
    alto = imagen.height();
    int tamañoDatos = ancho * alto * 3;
    unsigned char* datosPixel = new unsigned char[tamañoDatos];
    for (int y = 0; y < alto; ++y) {
        const uchar* lineaOrigen = imagen.scanLine(y);
        unsigned char* lineaDestino = datosPixel + y * ancho * 3;
        memcpy(lineaDestino, lineaOrigen, ancho * 3);
    }
    return datosPixel;
}

//*Función para guardar la imagen procesada**************************
bool guardarImagen(unsigned char* datosPixel, int ancho, int alto, QString rutaSalida) {
    QImage imagenSalida(ancho, alto, QImage::Format_RGB888);
    for (int y = 0; y < alto; ++y) {
        memcpy(imagenSalida.scanLine(y), datosPixel + y * ancho * 3, ancho * 3);
    }
    if (!imagenSalida.save(rutaSalida, "BMP")) {
        cout << "Error: No se pudo guardar la imagen." << endl;
        return false;
    } else {
        cout << "Imagen guardada como " << rutaSalida.toStdString() << endl;
        return true;
    }
}

//Función para cargar una máscara desde archivo*****************
unsigned int* cargarMascara(const char* nombreArchivo, int &semilla, int &num_pixels){
    // Abrir el archivo que contiene la semilla y los valores RGB
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        // Verificar si el archivo pudo abrirse correctamente
        cout << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }
    archivo >> semilla;
    int r, g, b;
    while (archivo >> r >> g >> b) {
        num_pixels++;
    }
    archivo.close();
    archivo.open(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al reabrir el archivo." << endl;
        return nullptr;
    }
    unsigned int* RGB = new unsigned int[num_pixels * 3];
    archivo >> semilla;
    for (int i = 0; i < num_pixels * 3; i += 3) {
        archivo >> r >> g >> b;
        RGB[i] = r;
        RGB[i + 1] = g;
        RGB[i + 2] = b;
    }
    archivo.close();
    cout << "Semilla: " << semilla << endl;
    cout << "Cantidad de píxeles leídos: " << num_pixels << endl;
    return RGB;
}

//Funcon aplicacion formula de la guia (Suma despues de cada XOR o cada Rotacion)******




//*Aplica operación XOR entre imagen y máscara***************************
void aplicarXOR(unsigned char* imagenfinal, unsigned char* idistorcionada, int tamaño) {
    for (int i = 0; i < tamaño; i++) {
        imagenfinal[i] ^= idistorcionada[i];
    }
}

//*Funcion para la rotacion de los bits hacia la izquierda**********
void rotacionBits(unsigned char* datos, int tamaño, int totalBits){
    for(int i = 0; i < tamaño; i++){
        datos[i] = (datos[i] << totalBits) | (datos[i] >> (8 - totalBits));
    }
}




int main()
{
    QString rutaP3 = "I_D.bmp";
    QString rutaI_M = "I_M.bmp";
    QString rutafinal = "ResultadoTu.bmp";

    //Dimensiones de las imagenes
    int anchoP3 = 0;
    int altoP3 = 0;

    //Llamado de la funcion para cargar P3 con sus parametros
    unsigned char* datosP3 = cargarImagen(rutaP3, anchoP3, altoP3);
    if(!datosP3){
        cout << "Error al cargar la imagen P3" << endl;
        delete[] datosP3;
        return 1;
    }
    cout << "Imagen P3 cargada correctamente: " << anchoP3 << " x " << altoP3 << " pixels" << endl;


    //Llamado de la funcion para cargar IM con sus parametros
    int anchoI_M = 0;
    int altoI_M = 0;
    unsigned char* datosI_M = cargarImagen(rutaI_M, anchoI_M, altoI_M);
    if(!datosI_M){
        cout << "Error al cargar la imagen I_M" << endl;
        delete[] datosP3;
        return -1;
    }
    cout << "Imagen I_M cargada correctamente: " << anchoI_M << " x " << altoI_M << " pixels" << endl;

    int anchoM = 0;
    int altoM = 0;
    unsigned char* mascara = cargarImagen("M.bmp", anchoM , altoM);
    if(!mascara){
        cout << "Error al cargar M.bmp" << endl;
        delete[] datosP3;
        return -1;
    }

    int semilla = 0;
    int num_pixels = 0;
    unsigned int *maskingData = cargarMascara("M0.txt", semilla, num_pixels);
    if (!maskingData) {
        cout << " No se pudo leer M1.txt\n";
        return -1;
    }





    if(anchoP3 != anchoI_M || altoP3 != altoI_M){
        cout << "Las diemensiones no coinciden" << endl;
        delete[] datosP3;
        delete[] datosI_M;
        return -1;
    }


    /*/Lamado de la funcion para cargar M (mascar)
    const char* rutaM = "M1.txt";
    int semilla = 0;
    int numPixeles = 0;
    unsigned int* datosM = cargarMascara(rutaM, semilla, numPixeles);
    if(!datosM){
        cout << "Error al cargar la mascara M1" << endl;
        delete[] datosP3;
        delete[] datosI_M;
        return 1;
    }
    cout << "Mascara M1 cargada correctamente" << endl;/*/

    int tamañoDatos = anchoP3 * altoP3 * 3;

    //XOR a P3 con ayuda de I_M
    aplicarXOR(datosP3, datosI_M, tamañoDatos);
    cout << "XOR aplicado I_D - I_M" << endl;//1

    //rotacion de los bit de P3 luego de aplicar el XOR
    const int bitsRotados = 2;
    rotacionBits(datosP3, tamañoDatos, bitsRotados);
    cout << "Rotacion aplicada a P3 luego del XOR" << endl;//2

    /*/Lo mismo de cargar M1 pero con M2
    const char* rutaM2 = "M2.txt";
    int semillaM2 = 0;
    int numPixelesM2 = 0;
    unsigned int* datosM2 = cargarMascara(rutaM2, semillaM2, numPixelesM2);
    if(!datosM2){
        cout << "Error al cargar la mascara M2" << endl;
        delete[] datosP3;
        delete[] datosI_M;
        delete[] datosM;
        return 1;
    }
    cout << "Mascara M2 cargada correctamente" << endl;
    delete[] datosM2;/*/

    //aplicacion de suma mascaras para P3 con ayuda de la imagen M y la semilla M2
    //formulaInversa(datosP3, datosM, semillaM2, tamañoDatos);

    //aplicar nuevamente el XOR entre P3 e I_M modificados
    aplicarXOR(datosP3, datosI_M, tamañoDatos);//3
    const int bitsRotados1 = 5;
    rotacionBits(datosP3, tamañoDatos, bitsRotados1);
    cout << "Rotacion aplicada a P3 luego del XOR" << endl;//4

    unsigned char* datosTemp = new unsigned char[tamañoDatos];
    memcpy(datosTemp, datosP3, tamañoDatos);
    aplicarXOR(datosP3, datosI_M, tamañoDatos);//5
    const int bitsRotados2 = 4;
    rotacionBits(datosP3, tamañoDatos, bitsRotados2);//6
    //unsigned char* p2_inv = new unsigned char[tamañoTotal];
    aplicarXOR(datosP3, datosI_M, tamañoDatos);

    bool formula = true;
    for (int i = 0; i < tamañoDatos; i++) {
        if ((semilla + i) >= tamañoDatos) break;

        int suma = int(datosTemp[semilla + i]) + int(datosI_M[i]);
        if (suma != int(mascara[i])) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(mascara[i])
                 << ", obtenido " << suma << endl;
            formula = false;
            break;
        }
    }
    if(formula == true)
        cout << "ResultadoTu.bmp coincide con M1.txt" << endl;
    else
        cout << "ResultadoTu.bmp NO coincide con M1.txt" << endl;


    //exportacion
    bool reconstruccion = guardarImagen(datosP3, anchoP3, altoP3, rutafinal);
    // cout << "Reconstruccion: " << (reconstruccion ? "Exitosa" : "Fallida") << endl;
    if(reconstruccion){
        cout << "Reconstruccion exitosa" << endl;
    } else {
        cout << "Error" << endl;
    }

    delete[] datosP3;
    delete[] datosI_M;
    //delete[] datosM;
    //delete[] datosM2;

    return 0;

}
