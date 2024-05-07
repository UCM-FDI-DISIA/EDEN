#ifndef EDEN_RESURCES_MANAGER_H
#define EDEN_RESOURCES_MANAGER_H

#include <string>
#include <set>
#include <vector>
#include "Singleton.h"

#include "defs.h"

#ifdef _MSC_VER
#define AUDIO_ROUTE "assets\\audio\\"
#define MESH_ROUTE "assets\\meshes\\"
#define MATERIALS_ROUTE "assets\\materials\\"
#define UI_ROUTE "assets\\textures\\"
#define FONTS_ROUTE "assets\\fonts\\"
#define DEFAULT_ROUTE  "assets\\default\\"
#define BIN_ROUTE  ".\\"
#endif
#ifdef __APPLE__
#define AUDIO_ROUTE "assets/audio/"
#define MESH_ROUTE "assets/meshes/"
#define MATERIALS_ROUTE "assets/materials/"
#define UI_ROUTE "assets/textures/"
#define FONTS_ROUTE "assets/fonts/"
#define DEFAULT_ROUTE  "assets/default/"
#define BIN_ROUTE  "./"
#endif

namespace eden_resources {
    /// @brief Clase encargada de gestionar los recursos de UI
    class ResourcesManager : public Singleton<ResourcesManager> {
        friend Singleton<ResourcesManager>;
    public:

        enum Resources {
            Mesh,
            Materials,
            UI,
            Fonts,
            Audio,
            Default,
            Bin
        };
        /// @brief Constructora
        EDEN_API ResourcesManager();
        
        /// @brief Destructora
        EDEN_API ~ResourcesManager();

        /// @brief Metodo que comprueba si un archivo existe
        EDEN_API bool FileExist(std::string name, Resources res);
        
        EDEN_API std::set<std::string> GetMeshes();


        EDEN_API std::set<std::string> GetMaterials();

        EDEN_API std::set<std::string> GetUIElements();

        EDEN_API std::set<std::string> GetAudios();

        EDEN_API std::set<std::string> GetFonts();
        
        EDEN_API std::set<std::string> GetRoutesMeshes();

        EDEN_API std::set<std::string> GetRoutesMaterials();

        EDEN_API std::set<std::string> GetRoutesUIElements();

        EDEN_API std::set<std::string> GetRoutesAudios();

        EDEN_API std::set<std::string> GetRoutesFonts();

        EDEN_API static ResourcesManager* getInstance();

        /// @brief Metodo que guarda todos los archivos existentes de unas direcciones concretas
        EDEN_API void LoadResources();

    private:

        /// @brief Lista de todos recursos
        std::vector<std::set<std::string>> _resourcesGeneral;

        /// @brief Lista de todos recursos
        std::vector<std::set<std::string>> _resourcesRutesGeneral;

        /// @brief Vector de rutas de directorios
        std::vector<std::string> _routes { MESH_ROUTE, MATERIALS_ROUTE, UI_ROUTE, FONTS_ROUTE, AUDIO_ROUTE, DEFAULT_ROUTE, BIN_ROUTE };
    };
}

#endif //UIMANAGER_H
