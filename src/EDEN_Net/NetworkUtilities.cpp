#include "NetworkUtilities.h"

std::vector<char> eden_net::NetworkUtilities::compressData(const std::vector<char>& data) {
    // Implementaci�n de compresi�n usando zlib u otra biblioteca
    std::vector<char> compressedData;
    // Comprimir data y almacenar en compressedData
    return compressedData;
}

std::vector<char> eden_net::NetworkUtilities::decompressData(const std::vector<char>& data) {
    // Implementaci�n de descompresi�n
    std::vector<char> decompressedData;
    // Descomprimir data y almacenar en decompressedData
    return decompressedData;
}

std::string eden_net::NetworkUtilities::serializeData(const std::vector<char>& data) {
    // Serializaci�n simple, como ejemplo
    return std::string(data.begin(), data.end());
}

std::vector<char> eden_net::NetworkUtilities::deserializeData(const std::string& data) {
    // Deserializaci�n simple
    return std::vector<char>(data.begin(), data.end());
}
