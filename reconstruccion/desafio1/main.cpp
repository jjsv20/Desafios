#include <QCoreApplication>
#include <QImage>
#include <fstream>
#include <iostream>

using namespace std;

//Funciones**************************************************
unsigned char* cargarImagen(QString input, int &ancho, int &alto);
bool guardarImagen(unsigned char* datosPixel, int ancho, int alto, QString rutaSalida);
unsigned int* cargarMascara(const char* nombreArchivo, int &seed, int &num_pixels);
//*************funcion aplicar enmascaramiento****************************
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

/*/Funcon aplicacion formula de la guia (Suma despues de cada XOR o cada Rotacion)******
//void aplicarMascara(unsigned char* datos, unsigned int* mascara, int semilla, int tamañoDatos, int numPixelesMascara) {
    int totalPixeles = tamañoDatos / 3;
    for (int i = 0; i < numPixelesMascara; ++i) {
        int indiceID = ((i + semilla) % totalPixeles) * 3;
        datos[indiceID] = (datos[indiceID] - mascara[i * 3]) % 256;
        datos[indiceID + 1] = (256 + datos[indiceID + 1] + mascara[i * 3 + 1]) % 256;
        datos[indiceID + 2] = (256 + datos[indiceID + 2] + mascara[i * 3 + 2]) % 256;
    }
}/*/


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
    unsigned int *maskingData0 = cargarMascara("M0.txt", semilla0, num_pixels0);
    if (!maskingData0) {
        cout << " No se pudo leer M1.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }


    int semilla1 = 0;
    int num_pixels1 = 0;
    unsigned int *maskingData1 = cargarMascara("M1.txt", semilla1, num_pixels1);
    if (!maskingData1) {
        cout << " No se pudo leer M1.txt\n";
        delete[] datosP3;
        delete[] datosI_M;
        delete[] mascara;
        return -1;
    }

    int semilla2 = 0;
    int num_pixels2 = 0;
    unsigned int *maskingData2 = cargarMascara("M2.txt", semilla2, num_pixels2);
    if (!maskingData2) {
        cout << " No se pudo leer M1.txt\n";
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

    //Primer XOR - XOR a P3 con ayuda de I_M
    aplicarXOR(datosP3, datosI_M, tamañoDatos);
    cout << "XOR aplicado I_D - I_M" << endl;//

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
        cout << "El resultado del primer XOR conincide con M2.txt" << endl;
    else
        cout << "El resultado del primer XOR NO conincide con M2.txt" << endl;




    //rotacion de los bit de P3 luego de aplicar el XOR
    const int bitsRotados = 3;
    rotacionBits(datosP3, tamañoDatos, bitsRotados);
    cout << "Rotacion aplicada a P3 luego del XOR" << endl;//2

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
        cout << "El resultado despues de la rotacion conincide con M1.txt" << endl;
    else
        cout << "El resultado despues de la rotacion NO conincide con M1.txt" << endl;



    //aplicar nuevamente el XOR entre P3 e I_M modificados
    aplicarXOR(datosP3, datosI_M, tamañoDatos);//3
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
        cout << "El resultado final conincide con M0.txt" << endl;
    else
        cout << "El resultado final NO conincide con M0.txt" << endl;



    /*/bool formula = true;
    for (int i = 0; i < num_pixels * 3; i++) {
        int suma = int(datosP3[semilla + i]) + int(mascara[i]);
        if (suma != maskingData[i]) {
            cout << "Diferencia en el índice " << i
                 << ": esperado " << int(maskingData[i])
                 << ", obtenido " << suma << endl;
            formula = false;
            break;
        }
    }

    if (formula)
        cout << "La imagen reconstruida coincide con el archivo original (M1.txt o similar)." << endl;
    else
        cout << "La imagen reconstruida NO coincide con el archivo original." << endl;/*/








    /*/const int bitsRotados1 = 5;
    rotacionBits(datosP3, tamañoDatos, bitsRotados1);
    cout << "Rotacion aplicada a P3 luego del XOR" << endl;//4

    unsigned char* datosTemp = new unsigned char[tamañoDatos];
    memcpy(datosTemp, datosP3, tamañoDatos);

    aplicarXOR(datosP3, datosI_M, tamañoDatos);//5

    aplicarMascara(datosP3, maskingData, semilla, tamañoDatos, num_pixels);
    cout << "1a. Máscara aplicada después del primer XOR" << endl;

    const int bitsRotados2 = 4;
    rotacionBits(datosP3, tamañoDatos, bitsRotados2);//6
    aplicarXOR(datosP3, datosI_M, tamañoDatos);

    aplicarMascara(datosP3, maskingData, semilla, tamañoDatos, num_pixels);
    cout << "1a. Máscara aplicada después del primer XOR" << endl;/*/

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
