#ifndef EDEN_ERROR_HANDLER_H
#define EDEN_ERROR_HANDLER_H

#include <iostream>
#include <exception>

#include "Singleton.h"

namespace eden_error {
	class ErrorHandler : public Singleton<ErrorHandler> {
		friend class Singleton<ErrorHandler>;
	private:
		/// @brief Constructora por defecto
		ErrorHandler() = default;

		/// @brief Muestra un mensaje por consola (en Debug) y a�ade a un log dentro de la carpeta bin
		/// de nombre LOG_NAME el warning/error/excepci�n generada
		/// @param messageToLog Mensaje a a�adir
		void AddToLog(std::string messageToLog);

		bool _generateLog = true;
	public:
		/// @brief Caracter que separa en una excepci�n el t�tulo de su descripci�n
		#define TITLE_ERROR_SEPARATOR '|'

		/// @brief Destructora por defecto
		~ErrorHandler() = default;
		
		/// @brief Lanza un warning a la salida est�ndar de errores (consola en Debug y nada en Release)
		/// @param warningMsg El mensaje de warning a lanzar. En este m�todo se dice en qu� l�nea y en qu� archivo
		/// se ha generado el warning
		void Warning(std::string warningMsg);
		
		/// @brief Comprueba una condici�n (Solo en Debug)
		/// @param condition Condici�n a comprobar en el assert. Si falla, el programa cierra
		void Assert(bool condition, std::string errorMessage);
		
		/// @brief Lanza un warning a la salida est�ndar de errores (consola en Debug y nada en Release)
		void Exception(std::string title, std::string definition);

		// @brief Se llama a Handle Exception cuando se lanza una excepci�n desde cualquier punto del c�digo. Este m�todo se encuentra envolviendo
		// al main. Las excepciones, en nuestro caso, ser�n utilizadas para errores de usuario, por lo que este m�todo lo que hace es vaciar toda la 
		// memoria generada y (en windows) mostrar una ventana con el error que lancemos al usuario.
		// @param e Excepci�n a manejar.
		void HandleException(std::exception e);

		/// @brief Borra EdenMaster, y por lo tanto, todo lo generado por el juego
		void CloseApplication();

	};

	#define LOG_NAME "EDEN_ErrorLog.txt"
	#define ERROR_SEPARETOR "--------------------\n"

	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

	#define EDEN_ASSERT_NO_CLEAN(message, condition) assert((message, condition))
	#define EDEN_EXCEPTION(error_definition) throw std::exception(error_definition);

}

#endif // _ERROR_HANDLER_H