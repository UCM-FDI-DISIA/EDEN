// This file is part of the course TPV2@UCM - Samir Genaim

#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <cassert>

/*
 * The class that inherits this class must implement a constructor
 * with no arguments, this is because of the call 'Init()' in method
 * 'instance()'. In the case that defining such a constructor is against
 * your design, just define one that throws and exception.
 *
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
protected:
	Singleton() {
	}

public:

	/// @brief No se pueden copiar objetos de este tipo
	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton(const Singleton<T>& o) = delete;

	virtual ~Singleton() {
		_instance.release();
	}

	/// @brief Algunos singletons necesitan inicializarse con parametros. Se llama a este metodo al principio del programa
	template<typename ...Targs>
	inline static T* Init(Targs &&...args) {
		assert(_instance.get() == nullptr);
		_instance.reset(new T(std::forward<Targs>(args)...));
		return _instance.get();
	}

	/// @brief A veces los singletons dependen entre ellos y han de cerrarse en un orden especifico por lo que tenemos este metodo
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

private:
	static std::unique_ptr<T> _instance;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;

#endif //SINGLETON_H