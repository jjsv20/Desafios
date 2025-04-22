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
}

// Aplica operación XOR entre imagen y máscara
void aplicarXOR(unsigned char* imagen, unsigned char* mascara, int tamaño) {
    for (int i = 0; i < tamaño; i++) {
        imagen[i] ^= mascara[i % tamaño];
    }
}

int main()
{

}
