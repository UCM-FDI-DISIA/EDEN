#ifndef EDEN_ERROR_HANDLER_H
#define EDEN_ERROR_HANDLER_H

#include <iostream>
#include <exception>

#include "Singleton.h"

#define _CRTDBG_MAP_ALLOC

#define LOG_NAME "EDEN_ErrorLog.txt"
#define ERROR_SEPARETOR "--------------------\n"
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define EDEN_ASSERT_NO_CLEAN(message, condition) assert((message, condition))
#define EDEN_EXCEPTION(error_definition) throw std::exception(error_definition);

namespace eden_error {
	class ErrorHandler : public Singleton<ErrorHandler> {
		friend class Singleton<ErrorHandler>;
	public:
		/// @brief Caracter que separa en una excepción el título de su descripción
#define TITLE_ERROR_SEPARATOR '|'

		/// @brief Destructora por defecto
		~ErrorHandler() = default;

		/// @brief Lanza un warning a la salida estándar de errores (consola en Debug y nada en Release)
		/// @param warningMsg El mensaje de warning a lanzar. En este método se dice en qué línea y en qué archivo
		/// se ha generado el warning
		void Warning(std::string warningMsg);

		/// @brief Comprueba una condición (Solo en Debug)
		/// @param condition Condición a comprobar en el assert. Si falla, el programa cierra
		void Assert(bool condition, std::string errorMessage);

		/// @brief Lanza un warning a la salida estándar de errores (consola en Debug y nada en Release)
		void Exception(std::string title, std::string definition);

		// @brief Se llama a Handle Exception cuando se lanza una excepción desde cualquier punto del código. Este método se encuentra envolviendo
		// al main. Las excepciones, en nuestro caso, serán utilizadas para errores de usuario, por lo que este método lo que hace es vaciar toda la 
		// memoria generada y (en windows) mostrar una ventana con el error que lancemos al usuario.
		// @param e Excepción a manejar.
		void HandleException(std::exception e);

		/// @brief Borra EdenMaster, y por lo tanto, todo lo generado por el juego
		void CloseApplication();

	private:
		bool _generateLog = true;

		/// @brief Constructora por defecto
		ErrorHandler() = default;

		/// @brief Muestra un mensaje por consola (en Debug) y añade a un log dentro de la carpeta bin
		/// de nombre LOG_NAME el warning/error/excepción generada
		/// @param messageToLog Mensaje a añadir
		void AddToLog(std::string messageToLog);

		
	};


}

#endif // _ERROR_HANDLER_H