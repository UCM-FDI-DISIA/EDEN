#ifndef NETWORK_UTILITIES_H_
#define NETWORK_UTILITIES_H_

#include <string>
#include <vector>

namespace eden_net {
    class NetworkUtilities {
    public:
        static std::vector<char> compressData(const std::vector<char>& data);
        static std::vector<char> decompressData(const std::vector<char>& data);

        static std::string serializeData(const std::vector<char>& data);
        static std::vector<char> deserializeData(const std::string& data);
    };
}

#endif // NETWORK_UTILITIES_H_