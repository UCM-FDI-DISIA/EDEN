// This file is part of the course TPV2@UCM - Samir Genaim
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef EDEN_SINGLETON_H
#define EDEN_SINGLETON_H

#include <memory>
#include <cassert>

#include "defs.h"

/// @brief Una clase que herede de esta clase tiene que implementar un constructor sin argumentos. 
/// @brief Los argumentos necesarios para construir una clase se pasarán en el método Init() de la clase, que se ejecuta cuando se llama el método Instance() por primera vez.
/*
 * >>> Usage:
 *
 * class A : public Singleton<A> {
 *
 *    friend Singleton<A>; // this way Singleton can call the constructor of A
 *
 * private: // constructors are private
 *    A() {
 *      //....
 *    }
 *
 * public: // the rest of the functionality
 *    virtual ~A() {
 *    }
 * }
 */

template<typename T>
class __declspec(dllexport) Singleton {

public:
	/// @brief No se pueden copiar objetos de este tipo
	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton(const Singleton<T>& o) = delete;
	/// @brief La destructora libera el puntero único
	virtual ~Singleton() {
		//_instance.release();
	}

	/// @brief Este método se puede usar para llamar a la constructora de una clase heredera de Singleton con parámetros. 
	/// @brief Evitar llamar a este método directamente, es preferible llamar al método "Instance".
	/// @param args Son los parámetros que se usan para construir a la clase
	template<typename ...Targs>
	inline static T* Init(Targs &&...args) {
		assert(_instance.get() == nullptr);
		_instance.reset(new T(std::forward<Targs>(args)...));
		return _instance.get();
	}

	/// @brief A veces los singletons dependen entre ellos y han de cerrarse en un orden especifico por lo que tenemos este metodo
	/// @brief Si se quiere borrar una instancia de singleton sin importar el orden, mejor usar la destructora
	inline static void Close() {
		_instance.reset();
	}

	/// @brief El método instance devuelve la instancia única de la clase que herede de Singleton.
	/// @brief La primera vez que se llama a este método, se construye la instancia de la clase y se guarda en un puntero estático.
	/// @brief Las próximas llamadas al método devuelven este puntero. Si se quiere construir una nueva instancia de la clase se puede hacer con el método Init.
	/// @param args Son los parámetros que se usan para construir a la clase
	/// @return El puntero a la instancia del singleton
	template<typename ...Targs>
	inline static T* Instance(Targs &&...args) {
		/// @brief puedes sustituir el "if" por assert(_instance.get() != nullptr) para forzar la incializacion al principio
		if (_instance.get() == nullptr) {
			Init(std::forward<Targs>(args)...);
		}
		return _instance.get();
	}
protected:
	Singleton() {
	}

private:
	static std::unique_ptr<T> _instance;
};

/// @brief Instancia globalmente accesible del singleton
template<typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;

#endif //SINGLETON_H