#include <QCoreApplication>
#include <QImage>
#include <fstream>
#include <iostream>

using namespace std;

// Función para cargar los pixeles de una imagen
unsigned char* cargarImagen(QString rutaImagen, int &ancho, int &alto) {
    QImage imagen(rutaImagen);

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

// Función para guardar la imagen procesada
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

// Función para cargar una máscara desde archivo
unsigned int* cargarMascara(const char* rutaArchivo, int &semilla, int &numPixeles) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo de máscara: " << rutaArchivo << endl;
        return nullptr;
    }

    archivo >> semilla;
    int r, g, b;
    numPixeles = 0;

    while (archivo >> r >> g >> b) {
        numPixeles++;
    }
    archivo.close();
    archivo.open(rutaArchivo);

    if(!archivo.is_open()){
        cout << "Error al reabrir el archivo de mascara" << endl;
        return nullptr;
    }
    archivo >> semilla;
    unsigned int* resultado = new unsigned int[numPixeles * 3];

    for(int i = 0; i < numPixeles * 3; i += 3){
        archivo >> r >> g >> b;
        resultado[i] = r;
        resultado[i + 1] = g;
        resultado[i + 2] = b;
    }
    archivo.close();
    cout << "Semilla: " << semilla << endl;
    cout << "Pixeles: " << numPixeles << endl;

    return resultado;
}

// Aplica operación XOR entre imagen y máscara
void aplicarXOR(unsigned char* imagenfinal, unsigned char* idistorcionada, int tamaño) {
    for (int i = 0; i < tamaño; i++) {
        imagenfinal[i] ^= idistorcionada[i];
    }
}

//Funcion para la rotacion de los bits hacia la izquierda
void rotacionBits(unsigned char* datos, int tamaño, int totalBits){
    for(int i = 0; i < tamaño; i++){
        datos[i] = (datos[i] << totalBits) | (datos[i] >> (8 - totalBits));
    }
}


// Funcion para la Aplicar la formula de manera inversa ************ Falta revisar e inplementar******************
void formulaInversa(unsigned char* imagen, unsigned int* mascara, int semilla, int tamaño){
    for(int i = 0; i < tamaño; i++){
        int indiceMascara = (i + semilla) % tamaño;
        int newvalor = imagen[i] + mascara[indiceMascara % (tamaño / 3) * 3 + i % 3];
        imagen[i] = newvalor % 256;
    }
}

int main()
{
    QString rutaP3 = "P3.bmp";
    QString rutaI_M = "I_M.bmp";
    QString rutafinal = "ResultadoT.bmp";

    //Dimensiones de las imagenes
    int anchoP3 = 0, altoP3 = 0;
    int anchoI_M = 0, altoI_M = 0;

    //Llamado de la funcion para cargar P3 con sus parametros
    unsigned char* datosP3 = cargarImagen(rutaP3, anchoP3, altoP3);
    if(!datosP3){
        cout << "Error al cargar la imagen P3" << endl;
        //delete[] datosP3;
        return 1;
    }
    cout << "Imagen P3 cargada correctamente: " << anchoP3 << " x " << altoP3 << " pixels" << endl;

    //Llamado de la funcion para cargar IM con sus parametros
    unsigned char* datosI_M = cargarImagen(rutaI_M, anchoI_M, altoI_M);
    if(!datosI_M){
        cout << "Error al cargar la imagen I_M" << endl;
        delete[] datosP3;
        return 1;
    }
    cout << "Imagen I_M cargada correctamente: " << anchoI_M << " x " << altoI_M << " pixels" << endl;


    if(anchoP3 != anchoI_M || altoP3 != altoI_M){
        cout << "Las diemensiones no coinciden" << endl;
        delete[] datosP3;
        delete[] datosI_M;
        return 1;
    }



    Lamado de la funcion para cargar M (mascar)
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
    cout << "Mascara M1 cargada correctamente" << endl;

    int tamañoDatos = anchoP3 * altoP3 * 3;

    //XOR a P3 con ayuda de I_M
    aplicarXOR(datosP3, datosI_M, tamañoDatos);
    cout << "XOR aplicado" << endl;

    //rotacion de los bit de P3 luego de aplicar el XOR
    const int bitsRotados = 3;
    rotacionBits(datosP3, tamañoDatos, bitsRotados);
    cout << "Rotacion aplicada a P3 luego del XOR" << endl;

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
    aplicarXOR(datosP3, datosI_M, tamañoDatos);

    //formulaInversa(datosP3, datosM, semillaM2, tamañoDatos);

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
    delete[] datosM;
    //delete[] datosM2;

    return 0;

}
