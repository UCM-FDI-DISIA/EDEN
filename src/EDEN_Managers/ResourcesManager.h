#ifndef EDEN_RESURCES_MANAGER_H
#define EDEN_RESOURCES_MANAGER_H

#include <string>
#include <set>
#include <vector>
#include "Singleton.h"

#include "defs.h"

#ifdef _MSC_VER
#define AUDIO_ROUTE "assets\\audio\\"
#define MATERIALS_ROUTE "assets\\mesh\\"
#define FONTS_ROUTE "assets\\fonts\\"
#define DEFAULT_ROUTE  "assets\\default\\"
#endif
#ifdef __APPLE__
#define AUDIO_ROUTE "assets/audio/"
#define MATERIALS_ROUTE "assets/mesh/"
#define FONTS_ROUTE "assets/fonts/"
#define DEFAULT_ROUTE  "assets/default/"
#endif

namespace eden_resources {
    /// @brief Clase encargada de gestionar los recursos de UI
    class ResourcesManager : public Singleton<ResourcesManager> {
        friend Singleton<ResourcesManager>;
    public:

        enum Resources {
            Materials,
            Fonts,
            Audio,
            Default
        };
        /// @brief Constructora
        EDEN_API ResourcesManager();
        
        /// @brief Destructora
        EDEN_API ~ResourcesManager();

        /// @brief Método que comprueba si un archivo existe
        EDEN_API bool FileExist(std::string name, Resources res);
        
        EDEN_API std::set<std::string> GetMaterials();

        EDEN_API std::set<std::string> GetAudios();

        EDEN_API std::set<std::string> GetFonts();

        EDEN_API std::set<std::string> GetRutesMaterials();

        EDEN_API std::set<std::string> GetRutesAudios();

        EDEN_API std::set<std::string> GetRutesFonts();

        EDEN_API static ResourcesManager* getInstance();

    private:

        /// @brief Método que guarda todos los archivos existentes de unas direcciones concretas
        EDEN_API void LoadResources();

        /// @brief Lista de todos recursos
        std::vector<std::set<std::string>>_resourcesGeneral;

        /// @brief Lista de todos recursos
        std::vector<std::set<std::string>>_resourcesRutesGeneral;
    };
}

#endif //UIMANAGER_H
