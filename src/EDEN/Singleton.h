// This file is part of the course TPV2@UCM - Samir Genaim

#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <cassert>

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
class Singleton {

public:
	/// @brief No se pueden copiar objetos de este tipo
	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton(const Singleton<T>& o) = delete;

	/// @brief La destructora libera el puntero único
	virtual ~Singleton() {
		_instance.release();
	}

	/// @brief Algunos singletons necesitan inicializarse con parametros. Se llama a este metodo al principio del programa
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

	/// @return El puntero a la instancia del singleton
	static T* Instance() {
		/// @brief puedes sustituir el "if" por assert(_instance.get() != nullptr) para forzar la incializacion al principio
		if (_instance.get() == nullptr) {
			Init();
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