#include <QCoreApplication>
#include <QImage>
#include <fstream>
#include <iostream>

using namespace std;

//Funciones**************************************************
unsigned char* cargarImagen(QString input, int &ancho, int &alto);
bool guardarImagen(unsigned char* datosPixel, int ancho, int alto, QString rutaSalida);
unsigned int* cargarMascara(const char* nombreArchivo, int &seed, int &num_pixels);
//funcion aplicar enmascaramiento***************************
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

//Función para guardar la imagen procesada*************************
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

//Aplica operación XOR entre imagen y máscara**************************
void aplicarXOR(unsigned char* imagenfinal, unsigned char* idistorcionada, int tamaño) {
    for (int i = 0; i < tamaño; i++) {
        imagenfinal[i] ^= idistorcionada[i];
    }
}

//Funcion para la rotacion de los bits hacia la izquierda*********
void rotacionBits(unsigned char* datos, int tamaño, int totalBits){
    for(int i = 0; i < tamaño; i++){
        datos[i] = (datos[i] << totalBits) | (datos[i] >> (8 - totalBits));
    }
}




int main()
{
    QString rutaP3 = "I_D.bmp";
    QString rutaI_M = "I_M.bmp";
    QString rutafinal = "I_DO.bmp";

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

    //cargar archivo M0.txt que se compara con el primer XOR
    int semilla0 = 0;
    int num_pixels0 = 0;
    unsigned int *maskingData0 = cargarMascara("M6.txt", semilla0, num_pixels0);
    if (!maskingData0) {
        cout << " No se pudo leer M1.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }


    int semilla1 = 0;
    int num_pixels1 = 0;
    unsigned int *maskingData1 = cargarMascara("M5.txt", semilla1, num_pixels1);
    if (!maskingData1) {
        cout << " No se pudo leer M1.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }

    int semilla2 = 0;
    int num_pixels2 = 0;
    unsigned int *maskingData2 = cargarMascara("M4.txt", semilla2, num_pixels2);
    if (!maskingData2) {
        cout << " No se pudo leer M2.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }

    int semilla3 = 0;
    int num_pixels3 = 0;
    unsigned int *maskingData3 = cargarMascara("M3.txt", semilla3, num_pixels3);
    if (!maskingData3) {
        cout << " No se pudo leer M2.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }

    int semilla4 = 0;
    int num_pixels4 = 0;
    unsigned int *maskingData4 = cargarMascara("M2.txt", semilla4, num_pixels4);
    if (!maskingData4) {
        cout << " No se pudo leer M2.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }

    int semilla5 = 0;
    int num_pixels5 = 0;
    unsigned int *maskingData5 = cargarMascara("M1.txt", semilla5, num_pixels5);
    if (!maskingData5) {
        cout << " No se pudo leer M2.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }

    int semilla6 = 0;
    int num_pixels6 = 0;
    unsigned int *maskingData6 = cargarMascara("M0.txt", semilla6, num_pixels6);
    if (!maskingData6) {
        cout << " No se pudo leer M2.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }

    /*/for (int i = 0; i < num_pixels * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData[i] << ", "
             << maskingData[i + 1] << ", "
             << maskingData[i + 2] << ")" << endl;
    }/*/


    if(anchoP3 != anchoI_M || altoP3 != altoI_M){
        cout << "Las diemensiones no coinciden" << endl;
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        delete[] maskingData0;
        delete[] maskingData1;
        delete[] maskingData2;
        return -1;
    }

    int tamañoDatos = anchoP3 * altoP3 * 3;

    aplicarXOR(datosP3, datosI_M, tamañoDatos);
    cout << "Rotacion aplicada" << endl;//2
    bool formula0 = true;
    for (int i = 0; i < num_pixels0 * 3; i++) {
        int suma0 = int(datosP3[semilla0 + i]) + int(mascara[i]);
        if (suma0 != maskingData0[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData0[i])
                 << ", obtenido " << suma0 << endl;
            formula0 = false;
            break;
        }
    }
    if (formula0)
        cout << "El resultado conincide con M6.txt" << endl;
    else
        cout << "El resultado NO conincide con M6.txt" << endl;

    const int bitsRotados = 6;
    rotacionBits(datosP3, tamañoDatos, bitsRotados);
    cout << "Rotacion aplicada" << endl;//2
    bool formula1 = true;
    for (int i = 0; i < num_pixels1 * 3; i++) {
        int suma1 = int(datosP3[semilla1 + i]) + int(mascara[i]);
        if (suma1 != maskingData1[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData1[i])
                 << ", obtenido " << suma1 << endl;
            formula1 = false;
            break;
        }
    }
    if (formula1)
        cout << "El resultado coincide con M5.txt" << endl;
    else
        cout << "El resultado NO conincide con M5.txt" << endl;


    aplicarXOR(datosP3, datosI_M, tamañoDatos);
    cout << "XOR aplicado" << endl;//
    bool formula2 = true;
    for (int i = 0; i < num_pixels2 * 3; i++) {
        int suma2 = int(datosP3[semilla2 + i]) + int(mascara[i]);
        if (suma2 != maskingData2[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData2[i])
                 << ", obtenido " << suma2 << endl;
            formula2 = false;
            break;
        }
    }
    if (formula2)
        cout << "El resultado conincide con M4.txt" << endl;
    else
        cout << "El resultado NO conincide con M4.txt" << endl;


    const int bitsRotados1 = 6;
    rotacionBits(datosP3, tamañoDatos, bitsRotados1);
    cout << "Rotacion aplicada" << endl;//2
    bool formula3 = true;
    for (int i = 0; i < num_pixels3 * 3; i++) {
        int suma3 = int(datosP3[semilla3 + i]) + int(mascara[i]);
        if (suma3 != maskingData3[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData3[i])
                 << ", obtenido " << suma3 << endl;
            formula3 = false;
            break;
        }
    }
    if (formula3)
        cout << "El resultado conincide con M3.txt" << endl;
    else
        cout << "El resultado NO conincide con M3.txt" << endl;

    aplicarXOR(datosP3, datosI_M, tamañoDatos);
    cout << "XOR aplicado" << endl;//
    bool formula4 = true;
    for (int i = 0; i < num_pixels4 * 3; i++) {
        int suma4 = int(datosP3[semilla4 + i]) + int(mascara[i]);
        if (suma4 != maskingData4[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData4[i])
                 << ", obtenido " << suma4 << endl;
            formula4 = false;
            break;
        }
    }
    if (formula4)
        cout << "El resultado conincide con M2.txt" << endl;
    else
        cout << "El resultado NO conincide con M2.txt" << endl;

    const int bitsRotados4 = 8;
    rotacionBits(datosP3, tamañoDatos, bitsRotados4);
    cout << "Rotacion aplicada" << endl;//2
    bool formula5 = true;
    for (int i = 0; i < num_pixels5 * 3; i++) {
        int suma5 = int(datosP3[semilla5 + i]) + int(mascara[i]);
        if (suma5 != maskingData5[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData5[i])
                 << ", obtenido " << suma5 << endl;
            formula5 = false;
            break;
        }
    }
    if (formula5)
        cout << "El resultado conincide con M1.txt" << endl;
    else
        cout << "El resultado NO conincide con M1.txt" << endl;

    aplicarXOR(datosP3, datosI_M, tamañoDatos);
    cout << "XOR aplicado" << endl;//
    bool formula6 = true;
    for (int i = 0; i < num_pixels6 * 3; i++) {
        int suma6 = int(datosP3[semilla6 + i]) + int(mascara[i]);
        if (suma6 != maskingData6[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData6[i])
                 << ", obtenido " << suma6 << endl;
            formula6 = false;
            break;
        }
    }
    if (formula6)
        cout << "El resultado conincide con M0.txt" << endl;
    else
        cout << "El resultado NO conincide con M0.txt" << endl;

    //exportacion
    bool reconstruccion = guardarImagen(datosP3, anchoP3, altoP3, rutafinal);
    if(reconstruccion){
        cout << "Reconstruccion exitosa" << endl;
    } else {
        cout << "Error" << endl;
    }

#ifdef _WIN32
    system("start I_DO.bmp");
#elif APPLE
    system("open I_DO.bmp");
#elif linux
    system("xdg-open I_DO.bmp");
#else
    cout << "No se puede abrir automáticamente en este sistema operativo." << endl;
#endif

    delete[] datosP3;
    delete[] datosI_M;
    //delete[] datosM;
    //delete[] datosM2;

    return 0;

}
