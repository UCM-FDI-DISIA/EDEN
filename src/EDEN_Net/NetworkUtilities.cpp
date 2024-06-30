#include "NetworkUtilities.h"
#include <zlib.h>

std::vector<char> eden_net::NetworkUtilities::compressData(const std::vector<char>& data) {
    // Implementación de compresión usando zlib u otra biblioteca
    std::vector<char> compressedData;
    // Comprimir data y almacenar en compressedData
    return compressedData;
}

std::vector<char> eden_net::NetworkUtilities::decompressData(const std::vector<char>& data) {
    // Implementación de descompresión
    std::vector<char> decompressedData;
    // Descomprimir data y almacenar en decompressedData
    return decompressedData;
}

std::string eden_net::NetworkUtilities::serializeData(const std::vector<char>& data) {
    // Serialización simple, como ejemplo
    return std::string(data.begin(), data.end());
}

std::vector<char> eden_net::NetworkUtilities::deserializeData(const std::string& data) {
    // Deserialización simple
    return std::vector<char>(data.begin(), data.end());
}
