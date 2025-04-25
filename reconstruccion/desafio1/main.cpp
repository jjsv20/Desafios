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
    QString rutaID = "I_D.bmp";
    QString rutaIM = "I_M.bmp";
    QString rutafinal = "I_DO.bmp";

    //Dimensiones de las imagenes
    int anchoID = 0;
    int altoID = 0;

    //Llamado de la funcion para cargar P3 con sus parametros
    cout << "\n===== Imagen ID Cargada =====" << endl;
    unsigned char* datosID = cargarImagen(rutaID, anchoID, altoID);
    if(!datosID){
        cout << "Error al cargar la imagen I_D" << endl;
        delete[] datosID;
        return 1;
    }
    cout << "Imagen I_D cargada correctamente: " << anchoID << " x " << altoID << " pixels" << endl;


    //Llamado de la funcion para cargar IM con sus parametros
    cout << "\n===== Imagen I_M Cargada =====" << endl;
    int anchoIM = 0;
    int altoIM = 0;
    unsigned char* datosIM = cargarImagen(rutaIM, anchoIM, altoIM);
    if(!datosIM){
        cout << "Error al cargar la imagen I_M" << endl;
        delete[] datosID;
        return -1;
    }
    cout << "Imagen I_M cargada correctamente: " << anchoIM << " x " << altoIM << " pixels" << endl;


    cout << "\n===== MASCARA cargada desde M.bmp =====" << endl;
    int anchoM = 0;
    int altoM = 0;
    unsigned char* mascara = cargarImagen("M.bmp", anchoM , altoM);
    if(!mascara){
        cout << "Error al cargar la mascara M.bmp" << endl;
        delete[] datosID;
        return -1;
    }

    //cargar archivo M0.txt que se compara con el primer XOR
    cout << "\n===== MASCARA 0 (M0.txt) =====" << endl;
    int semilla0 = 0;
    int num_pixels0 = 0;
    unsigned int *maskingData0 = cargarMascara("M0.txt", semilla0, num_pixels0);
    if (!maskingData0) {
        cout << " No se pudo leer M1.txt\n";
        delete[] datosID;
        delete[] datosIM;
        delete[] mascara;
        return -1;
    }


    cout << "\n===== MASCARA 1 (M1.txt) =====" << endl;
    int semilla1 = 0;
    int num_pixels1 = 0;
    unsigned int *maskingData1 = cargarMascara("M1.txt", semilla1, num_pixels1);
    if (!maskingData1) {
        cout << " No se pudo leer M1.txt\n";
        delete[] datosID;
        delete[] datosIM;
        delete[] mascara;
        return -1;
    }


    cout << "\n===== MASCARA 2 (M2.txt) =====" << endl;
    int semilla2 = 0;
    int num_pixels2 = 0;
    unsigned int *maskingData2 = cargarMascara("M2.txt", semilla2, num_pixels2);
    if (!maskingData2) {
        cout << " No se pudo leer M2.txt\n";
        delete[] datosID;
        delete[] datosIM;
        delete[] mascara;
        return -1;
    }


    if(anchoID != anchoIM || altoID != altoIM){
        cout << "Las diemensiones no coinciden" << endl;
        delete[] datosID;
        delete[] datosIM;
        delete[] mascara;
        delete[] maskingData0;
        delete[] maskingData1;
        delete[] maskingData2;
        return -1;
    }

    int tamañoDatos = anchoID * altoID * 3;


    cout << "\n===== Aplicando XOR (I_D - I_M) =====" << endl;
    //Primer XOR - XOR a P3 con ayuda de I_M
    aplicarXOR(datosID, datosIM, tamañoDatos);
    cout << "Operación XOR realizada correctamente." << endl;

    /*/for (int i = 0; i < num_pixels2 * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData2[i] << ", "
             << maskingData2[i + 1] << ", "
             << maskingData2[i + 2] << ")" << endl;
    }
    cout << endl;/*/

    bool formula2 = true;
    for (int i = 0; i < num_pixels2 * 3; i++) {
        int suma2 = int(datosID[semilla2 + i]) + int(mascara[i]);
        if (suma2 != maskingData2[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData2[i])
                 << ", obtenido " << suma2 << endl;
            formula2 = false;
            break;
        }
    }
    if (formula2)
        cout << "El resultado del primer XOR conincide con M2.txt" << endl;
    else
        cout << "El resultado del primer XOR NO conincide con M2.txt" << endl;



    cout << "\n===== Rotación de bits =====" << endl;
    //rotacion de los bit de P3 luego de aplicar el XOR
    const int bitsRotados = 3;
    rotacionBits(datosID, tamañoDatos, bitsRotados);
    cout << "Bits rotados a la izquierda: " << bitsRotados << endl;

    /*/for (int i = 0; i < num_pixels1 * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData1[i] << ", "
             << maskingData1[i + 1] << ", "
             << maskingData1[i + 2] << ")" << endl;
    }
    cout << endl;/*/

    bool formula1 = true;
    for (int i = 0; i < num_pixels1 * 3; i++) {
        int suma1 = int(datosID[semilla1 + i]) + int(mascara[i]);
        if (suma1 != maskingData1[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData1[i])
                 << ", obtenido " << suma1 << endl;
            formula1 = false;
            break;
        }
    }
    if (formula1)
        cout << "El resultado despues de la rotacion conincide con M1.txt" << endl;
    else
        cout << "El resultado despues de la rotacion NO conincide con M1.txt" << endl;


    cout << "\n===== Aplicando segundo XOR (I_D modificado - I_M) =====" << endl;
    //aplicar nuevamente el XOR entre P3 e I_M modificados
    aplicarXOR(datosID, datosIM, tamañoDatos);//3

    /*/for (int i = 0; i < num_pixels0 * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData0[i] << ", "
             << maskingData0[i + 1] << ", "
             << maskingData0[i + 2] << ")" << endl;
    }
    cout << endl;/*/


    bool formula0 = true;
    for (int i = 0; i < num_pixels0 * 3; i++) {
        int suma0 = int(datosID[semilla0 + i]) + int(mascara[i]);
        if (suma0 != maskingData0[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData0[i])
                 << ", obtenido " << suma0 << endl;
            formula0 = false;
            break;
        }
    }
    if (formula0)
        cout << "El resultado final conincide con M0.txt" << endl;
    else
        cout << "El resultado final NO conincide con M0.txt" << endl;


    cout << "\n===== Guardando Imagen Final =====" << endl;
    //exportacion
    bool reconstruccion = guardarImagen(datosID, anchoID, altoID, rutafinal);
    if(reconstruccion){
        cout << "**** Reconstruccion exitosa ****" << endl;
    } else {
        cout << "Error" << endl;
    }

#ifdef _WIN32
    system("start I_DO.bmp");
#elif __APPLE__
    system("open I_DO.bmp");
#elif __linux__
    system("xdg-open I_DO.bmp");
#else
    cout << "No se puede abrir automáticamente en este sistema operativo." << endl;
#endif



    delete[] datosID;
    delete[] datosIM;
    //delete[] datosM;
    return 0;

}
