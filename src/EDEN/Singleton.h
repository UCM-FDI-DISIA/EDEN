// This file is part of the course TPV2@UCM - Samir Genaim

#ifndef EDEN_SINGLETON_H
#define EDEN_SINGLETON_H

#include <memory>
#include <cassert>

/// @brief Una clase que herede de esta clase tiene que implementar un constructor sin argumentos. 
/// @brief Los argumentos necesarios para construir una clase se pasar�n en el m�todo Init() de la clase, que se ejecuta cuando se llama el m�todo Instance() por primera vez.
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
	/// @brief La destructora libera el puntero �nico
	virtual ~Singleton() {
		_instance.release();
	}

	/// @brief Este m�todo se puede usar para llamar a la constructora de una clase heredera de Singleton con par�metros. 
	/// @brief Evitar llamar a este m�todo directamente, es preferible llamar al m�todo "Instance".
	/// @param args Son los par�metros que se usan para construir a la clase
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

	/// @brief El m�todo instance devuelve la instancia �nica de la clase que herede de Singleton.
	/// @brief La primera vez que se llama a este m�todo, se construye la instancia de la clase y se guarda en un puntero est�tico.
	/// @brief Las pr�ximas llamadas al m�todo devuelven este puntero. Si se quiere construir una nueva instancia de la clase se puede hacer con el m�todo Init.
	/// @param args Son los par�metros que se usan para construir a la clase
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