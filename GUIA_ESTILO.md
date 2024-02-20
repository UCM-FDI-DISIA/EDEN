# GUÍA DE ESTILO - EDEN/CUBE STUDIOS
## **Base y referencias**
Tomaremos como guía de estilo base la [**guía de estilo de C++ de Google**](https://google.github.io/styleguide/cppguide.html), con algunas modificaciones para adaptarse a la manera de programar que tenemos y que quizás pueda ser la más adecuada a la hora de programar un videojuego.

## **Versión de C++**
Tras un consenso con todo el grupo se decidió que la versión a utilizar para el proyecto será C++20, ya que incluye bastantes mejoras con respecto a C++17 que nos pueden ser útiles a la hora de la creación del motor.

## **Aspectos importantes y modificaciones**
Aquí incluiremos todos los aspectos que haya que recalcar o modificar acerca de la guía de estilo base.
### **Archivos de encabezado**
- Tras consenso con el grupo, se ha decidido descartar la directiva
```CPP
#pragma once
```
de Visual Studio en pro de
```CPP
#ifndef NOMBRE_DEL_ARCHIVO_H
#define NOMBRE_DEL_ARCHIVO_H

//Código

#endif //NOMRBE_DEL_ARCHIVO_H
```
utilizada más comunmente en otros entornos de desarrollo, y que puede ayudar a la hora de evitar errores de compatibilidad en caso de que algún miembro del equipo decida usar otro editor o IDE, como por ejemplo, XCode.
- Todos los includes irán **EXCLUSIVAMENTE en los archivos .cpp** (*la única excepción para los .h, es para romper dependencias circulares que puedan surgir en el código*), **SIEMPRE INTENTANDO MINIMIZAR EL NÚMERO TOTAL DE INCLUDES** y solo se incluirán aquellos includes necesarios, evitando repetir includes que ya puedan estar en otros archivos que hayamos incluido.
- Usar declaraciones previas (forward declaration, https://www.geeksforgeeks.org/what-are-forward-declarations-in-c/) donde sea **ESTRICTAMENTE NECESARIO**, es decir, evitar usar los forward declarations lo máximo posible. *Se podrán utilizar declaraciones previas en caso de querer romper alguna dependencia circular que pueda ocurrir en el código*.
- Métodos inline: serán inline **todos los getters y setters** (accessors y mutators, en C++), y funciones de **MENOS DE 4 LÍNEAS** que no sean recursivas, o cuenten con un switch o con un bucle, ya que no es eficiente para el compilador tenerlas como inline.
- Orden de los includes **EN ARCHIVOS .cpp**: primero cabeceras de librerías C, luego cabeceras de librerías C++, cabeceras de librerías adicionales (estas tres deberán ir entre <>), cabeceras de archivos del proyecto, defines y using. Todos estos saltos entre librerías tendrán que tener un espacio entre ello.
- Includes **EN ARCHIVOS.h**: Se evitará poner includes en archivos .h, excepto *que se necesite en caso de querer romper alguna dependencia circular que pueda surgir*. En el caso de que se necesiten varios includes en archivos .h, se usará la misma metodología que en los archivos .cpp: primero includes de C, luego de C++, luego de otras librerías, y finalmente de nuestros propios archivos. Los define para constantes y using **SÍ** que irán en los .h, y se pondrán justo después del #ifndef - #define inicial de la cabecera, o, si hubiese algún include, debajo de los includes.

Por ejemplo, para una clase "MiClase", tendremos el siguiente aspecto:
```CPP
// Ejemplo del archivo MiClase.h

#ifndef MI_CLASE_H
#define MI_CLASE_H

//Includes de librerías de C++
#include <string>

//Includes de otras librerías que no son de C ni de C++
#include <PxVector3>

//defines
#define MAX 125
#define MIN 22

//using
using Punto = Vector3;

class MiClase {
public:
  MiClase(int a, int b, std::string s)
  
protected:
  void ImprimePorPantalla() const;

private:
  int _a, _b;
  Punto _pt;
  std::string _s;
}

#endif //MI_CLASE_h
```
```CPP
// Ejemplo del archivo MiClase.cpp
#include <stdlib.h> //librería de C puro

//librerías de C++
#include <unordered_map>
#include <list>

//librerías que no son ni de C ni de C++
#include <PxTransform.h>
#include <PxRigidbody.h>

//nuestros archivos
#include "MiClase.h"
#include "Componente.h"
#include "Componente2.h"

MiClase::MiClase(int a, int b, std::string s): _a(a), _b(b), _s(s) {
  ...
}

void MiClase::ImprimePorPantalla() {
  ...
}
```

### **Namespaces**
- **PROHIBIDO ROTUNDAMENTE USAR LA DIRECTIVA:**
 
```CPP
//PROHIBIDO ESTO
using namespace nombre_del_namespace
```

Siempre que se quiera hacer referencia a un método/clase de algún namespace en específico se hará de la siguiente manera, por muy feo que quede:
```CPP
nombre_del_namespace::NombreDeLaFuncion()...
std::unordered_map<std::string, std::function<std::string(std::string)>> mi_diccionario;
```
- Los namespaces **DEBEN** ser declarados en archivos .h
#### Nombres de namespaces
- Los nombres de  deben ir todos en minúscula, separados por barras bajas en caso de que esté compuesto por varias palabras. Por ejemplo:
```CPP
namespace componentes_juego {
  //Código
}

namespace entidad_componente {
  //Código
}
```

### **Variables**
#### **Variables locales**
- Para favorecer la legibilidad, todas las variables locales se inicializarán una vez declaradas, es decir:
```CPP
int Funcion() {
// Evitar esta práctica:  
  int i;
  i = Funcion2();

// Esta práctica es mejor:
  int b = Funcion2();

//---------------------

// Evitar esta práctica: declarar una variable que se va a usar posteriormente en la llamada a alguna función, etc... y meter código entre medias de la declaración de la variable y su uso:
  int i = 0;
  variableAnterior++;
  otraVariable = 72;
  ... //código
  ... //código
  Funcion3(i);

// Esta práctica es mejor: declarar la variable justo en la línea anterior donde se vaya a usar.
  variableAnterior++;
  otraVariable = 72;
  ...
  ...
  int i = 0;
  Funcion3(i);

//---------------------

//Evitar esta práctica: bucle con std::vector::push_back() o sucesivas llamadas a std::vector::push_back() si se van a introducir pocos elementos (5 o menos) cuando se inicialice un vector de tipos base, como enteros, floats, bools, etc..., siempre que no sea estrictamente necesario:
  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(150);
  ...

// Esta práctica es mejor (siempre que sea posible):
  std::vector<int> vec = {10, 150, ...};

//---------------------

// Animar a usar esta práctic SIEMPRE QUE SE PUEDA: en bucles o en if statements (si es que fuera necesario en un if), inicializar las variables --principalmente de tipos básicos-- directamente en la declaración del statement de la siguiente forma, en lugar de hacerlo fuera:
  while(const char* p = FuncionQueDevuelveUnChar()) algo += p;

//---------------------

//ABSOLUTAMENTE PROHIBIDO LO SIGUIENTE A NO SER QUE SEA ESTRICTAMENTE NECESARIO:
  for(int i = 0; i < 1500000; ++i)
    Clase c;
    c.HazAlgo(i);
  }


//SINO HACER LO SIGUIENTE:
  Clase c;
  for(int i = 0; i < 1500000; ++i) {
    c.HazAlgo(i);
  }
```

#### **Variables globales**
- Evitar usar lo máximo posible el uso de variables globales o variables constantes que definan algún tipo de valor numérico. En su lugar usaremos #define, **SIEMPRE EN LOS .h** (*Esto queda a la espera de que Pedro Pablo nos de más información en un laboratorio, pero de momento usaremos esta metodología*)

#### **Nombres de variables**
- Para los nombres de las variables usaremos *lower camelcase*, esto es:
```CPP
int esteEsElNombreDeMiVariable = 178;
```

- Para las variables privadas/protegidas en una clase, usaremos una barra baja inicial, para las públicas, nada:
```CPP
class Clase {  
public:
  int intPublico;
  std::string stringPublico;

private:
  int _intPrivado;
  std::string _stringPrivada;
}
```

### **Clases y Structs**
#### **Clases vs. Structs**
- Se usarán structs para todos aquellos objetos pasivos que simplemente almacenen o lleven datos, o en el caso de funciones/métodos cuyo argumento o valor de devolución sea excesivamente largo. Para el resto de objetos, se usarán clases.

#### **Herencia**
- Siempre pública.
-  Las funciones virtuales deben declararse siempre de la siguiente manera para ayudar a la legibilidad:
```CPP
class B: public A {
protected:
  virtual int Funcion1(); //Si funcion1 es una FUNCIÓN PROPIA DE LA CLASE B, que queremos que hereden clases hijas.
  int Funcion2() override; //Si funcion2 es una FUNCIÓN PROPIA DE A que la clase B sobreescribe, y clases que hereden de B puedan sobreescribir.
  int Funcion3() final; // Si funcion3 es una FUNCIÓN PROPIA DE A que la clase B sobreescribe pero NO QUEREMOS que clases que hereden de B puedan sobreescribir.

//EVITAR LO SIGUIENTE AL SOBREESCRIBIR UNA FUNCIÓN:
  virtual int FuncionDefinidaEnClaseA(); // Esto sería int funcionDefinidaEnClaseA() override;
}
```
- Para ayudar a la legibilidad y entender de dónde viene cada clase heredada, se usará, al principio del nombre de la clase heredada, una letra que indique la clase padre (someter a votación en un futuro y poner más ejemplos). Por ejemplo:
```CPP
// Como PlayerController hereda de Component, se le pone una c minúscula pequeña, indicando que es un componente, en lugar de tener que escrbir el nombre "PlayerControllerComponent". Esto lo implementaremos en las clases "base" que veamos oportunas.
class cPlayerController : public Component {
 ...   
}
```
#### **Orden en las clases**
- Pondremos siempre en la parte superior de la clase las variables y métodos públicos, luego los protegidos y por último los privados, y siempre poniendo primero variables y después funciones (comenzando aquí por la constructora y destructora). También, pondremos un espacio entre cada sección, diferenciándose claramente qué es público, qué es protegido y qué es privado, de la siguiente manera:
```CPP
class MiClase {
public:
  int numeroPublico;
  std::string stringPublica;

  MiClase();
  ~MiClase();

  inline void SetValor(int valor);
  inline int GetValor() const;

protected:
  int _numeroProtegido;

  virtual void HazAlgo();
  void HazOtraCosa() const override;
  void OtraCosaMas() const final;

private:
  int _numeroPrivado;
  
  void CrearAlgo();
  void CrearOtraCosa();
}
```

#### **Detalles y nombres de clases**
- Los nombres de las clases usarán el formato *upper camelcase*, esto es, el *camelcase* mencionado anteriormente, con la primera letra de la primera palabra en mayúscula, por ejemplo:
```CPP
class EstaEsMiClaseDeEjemplo;
class EstaEsMiOtraClase;

//Como se ha mencionado anteriormente, romperemos esta regla con clases que hereden de clases "importantes" del motor:
class cMovmientoDelJugador;
class mManagerDeEscenas;
```
- Todos los métodos que sean constantes deben ser marcados como tal, ya que optimizan bastante la labor del compilador. También se anima a los integrantes del equipo a descubrir y usar otro tipo de especificadores de funciones/métodos (https://duckduckgo.com/?sites=cppreference.com&q=specifier&ia=web)

### **Punteros y punteros inteligentes**
#### **Punteros y creación de memoria**
- Recordad borrar toda la memoria creada usando correctamente los destructores, y, si es posible, que sea la clase que crea memoria la misma que la borre.
- Recordad también que en clases heredadas, poner la destructora de la clase padre como virtual.
- Añadir en todas las clases el define de Visual Studio que permite ver si alguna clase deja alguna fuga de memoria.
#### **Punteros inteligentes**
- Intentaremos adoptar, si es posible, y los profesores nos dejan, punteros inteligentes, que simplifican mucho el que no nos dejemos fugas de memoria. [Para entender su funcionamiento, aquí una guía, creada por Microsoft donde se explica bien el uso de punteros inteligentes](https://learn.microsoft.com/es-es/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170) y [aquí la referencia en cppreference](https://en.cppreference.com/w/cpp/memory#Smart_pointers).

### **Nombres de archivo**
- Los nombres de archivo principalmente deberían llamarse exactamente como la clase única o la clase principal que contenga ese archivo, por ejemplo:
```CPP
MiClase.h
MiClase.cpp

cControladorDeJugador.h
cControladorDeJugador.cpp
```

### **Comentarios**
Para los comentarios usaremos [Doxygen](https://www.doxygen.nl/index.html), puesto que nos permitirá crear una página web que podremos alojar en el propio repositorio del motor con todos los métodos comentados de manera más legible y más interactiva.

- Para ello, se ha hecho una guía a todos los miembros del equipo explicando la activación de Doxygen dentro de Visual Studio, y el código, quedará comentado finalmente de la siguiente manera:
```CPP
/// @brief breve descripción del método
/// @brief puede haber varias descripciones breves pero al final se juntan cuando se genere la página HTML
/// Descripción más larga, si fuese necesaria, del método
/// @param[in] a Descripción de cada uno de los parámetros del método. Al poner in signfica que este es de entrada.
/// @param[out] b este de salida
/// @param[in, out] c este de entrada-salida
/// @param d este no se especifica
/// @warning esto advierte de algún código que pueda dar fallos, aparecerá en rojo en la página generada
/// @return Este es el valor de retorno de la función
int Funcion(int* a, int& const b, int* c, int d);
```
- Doxygen cuenta también con soporte para Markdown, en caso de que querramos usarlo, así como [muchos otros comandos para comentar métodos o variables](https://www.doxygen.nl/manual/commands.html)