#ifndef EDEN_MACOSMESSAGEBOXHELPER_H
#define EDEN_MACOSMESSAGEBOXHELPER_H

#include <string>

/// [IGNORAR ESTE METODO EN WINDOWS] Crea una ventana modal para los errores, igual que en Windows, para Mac
/// solo que es necesario crearla usando Objective-C y C++ (Objective-C++), de ahí el archivo
/// MacOSMessageBoxHelper.mm
/// @param errorTitle Titulo de la ventana con el error
/// @param errorDescription Descripcion del error
void ShowErrorMessageBox(const std::string& errorTitle, const std::string& errorDescription);

#endif //MACOSMESSAGEBOXHELPER_H
