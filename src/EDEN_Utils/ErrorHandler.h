#ifndef EDEN_ERROR_HANDLER_H
#define EDEN_ERROR_HANDLER_H

#include <iostream>
#include <exception>

#include "Singleton.h"

#include "defs.h"

#define _CRTDBG_MAP_ALLOC

#define LOG_NAME "EDEN_ErrorLog.txt"
#define ERROR_SEPARETOR "--------------------\n"
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define EDEN_ASSERT_NO_CLEAN(message, condition) assert((message, condition))
#ifdef _MSC_VER
	#define EDEN_EXCEPTION(error_definition) throw std::exception(error_definition);
#endif
#ifdef __clang__
	#define EDEN_EXCEPTION(error_definition) throw std::runtime_error(error_definition);
#endif

namespace eden_error {
	class ErrorHandler : public Singleton<ErrorHandler> {
		friend class Singleton<ErrorHandler>;
	public:
		/// @brief Caracter que separa en una excepcion el titulo de su descripcion
#define TITLE_ERROR_SEPARATOR '|'

		/// @brief Destructora por defecto
		~ErrorHandler() = default;

		/// @brief Lanza un warning a la salida estandar de errores (consola en Debug y nada en Release)
		/// @param warningMsg El mensaje de warning a lanzar. En este metodo se dice en que linea y en que archivo
		/// se ha generado el warning
		EDEN_API void Warning(std::string warningMsg);

		/// @brief Comprueba una condici�n (Solo en Debug)
		/// @param condition Condici�n a comprobar en el assert. Si falla, el programa cierra
		EDEN_API void Assert(bool condition, std::string errorMessage);

		/// @brief Lanza un warning a la salida est�ndar de errores (consola en Debug y nada en Release)
		EDEN_API void Exception(std::string title, std::string definition);

		// @brief Se llama a Handle Exception cuando se lanza una excepcion desde cualquier punto del codigo. Este metodo se encuentra envolviendo
		// al main. Las excepciones, en nuestro caso, seran utilizadas para errores de usuario, por lo que este metodo lo que hace es vaciar toda la 
		// memoria generada y (en windows) mostrar una ventana con el error que lancemos al usuario.
		// @param e Excepci�n a manejar.
		EDEN_API void HandleException(std::exception e);

		/// @brief Exactamente lo mismo que HandleException solo que para sistemas en los que
		/// @brief std::exception no acepta como argumento en su constructora un string o una
		/// @brief cadena de C
		/// @param e Excepcion a manejar
		EDEN_API void HandleExceptionNWin(std::runtime_error e);

		/// @brief Borra EdenMaster, y por lo tanto, todo lo generado por el juego
		EDEN_API void CloseApplication();

	private:
		bool _generateLog = true;

		/// @brief Constructora por defecto
		ErrorHandler() = default;

		/// @brief Muestra un mensaje por consola (en Debug) y aniade a un log dentro de la carpeta bin
		/// de nombre LOG_NAME el warning/error/excepcion generada
		/// @param messageToLog Mensaje a aniadir
		void AddToLog(std::string messageToLog);
	};

}
#endif // _ERROR_HANDLER_H