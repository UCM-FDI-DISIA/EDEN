#ifndef EDEN_COMPONENT_ARGUMENTS_H
#define EDEN_COMPONENT_ARGUMENTS_H

#include <string>
#include <unordered_map>

namespace eden_utils {
	class Vector3;
	class Quaternion;
}

namespace eden_script {
	class ScriptManager;

	/// @brief Da forma y es capaz de parsear los componentes leidos desde los mapas .lua generados por un usuario.
	class ComponentArguments
	{
		friend ScriptManager;
	public:
		/// @brief Constructora por defecto
		ComponentArguments() = default;

		/// @brief Da valor a la ID del componente que queremos representar. Crea un mapa vacio de argumentos
		/// @param id ID del componente
		inline ComponentArguments(std::string id) : _args() { _id = id; }

		/// @brief Parsea un valor del mapa _args a Vector3
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		eden_utils::Vector3 GetValueToVector3(std::string id);

		/// @brief Parsea un valor del mapa _args a std::vector<Vector3>
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		std::vector<eden_utils::Vector3> GetValueToVector3Vector(std::string id);

		/// @brief Parsea un valor del mapa _args a bool
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		bool GetValueToBool(std::string id);

		/// @brief Parsea un valor del mapa _args a vector<bool>
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		std::vector<bool> GetValueToBoolVector(std::string id);

		/// @brief Parsea un valor del mapa _args a int
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		int GetValueToInt(std::string id);

		/// @brief Parsea un valor del mapa _args a vector<int>
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		std::vector<int> GetValueToIntVector(std::string id);

		/// @brief Parsea un valor del mapa _args a float
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		float GetValueToFloat(std::string id);

		/// @brief Parsea un valor del mapa _args a vector<float>
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		std::vector<float> GetValueToFloatVector(std::string id);

		/// @brief Parsea un valor del mapa _args a double
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		double GetValueToDouble(std::string id);

		/// @brief Parsea un valor del mapa _args a vector<double>
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		std::vector<double> GetValueToDoubleVector(std::string id);
		
		/// @brief Devuelve el string asociado al valor dado en el mapa
		/// @param id Valor del mapa _args a recibir
		/// @return string asociado a id
		std::string GetValueToString(std::string id);

		/// @brief Devuelve el vector<string> asociado al valor dado en el mapa
		/// @param id Valor del mapa _args a recibir
		/// @return vector<string> asociado a id
		std::vector<std::string> GetValueToStringVector(std::string id);

		/// @brief Parsea un valor del mapa _args a Quaternion
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		eden_utils::Quaternion GetValueToQuaternion(std::string id);

		/// @brief Parsea un valor del mapa _args a Quaternion
		/// @param id Valor del mapa _args a parsear
		/// @return valor parseado
		std::vector<eden_utils::Quaternion> GetValueToQuaternionVector(std::string id);

		/// @brief Devuelve la id del componente
		inline std::string GetID() { return _id; }
		
		/// @brief Devuelve una copia de los argumentos del componente
		inline std::unordered_map<std::string, std::vector<std::string>> GetArgs() { return _args; }
	private:

		/// @brief Se ocupa de los errores cuando el valor leido de un mapa no tiene exactamente 'numArgs' argumentos
		/// @param id Valor que da error
		/// @param type Tipo del valor que da error
		/// @param numArgs Numero de argumentos exactos que deberia tener el tipo 'type' para poder ser parseado
		void HandleArgumentError(std::string id, std::string type, int numArgs);

		/// @brief Conversion de string a bool
		bool ToBool(std::string value);

		/// @brief Conversion de string a int
		int ToInt(std::string value);

		/// @brief Conversion de string a float
		float ToFloat(std::string value);

		/// @brief Conversion de string a double
		double ToDouble(std::string value);

		/// @brief Conversion de string a Vector3
		eden_utils::Vector3 ToVector3(std::string xValue, std::string yValue, std::string zValue);

		/// @brief Conversion de string a Quaternion
		eden_utils::Quaternion ToQuaternion(std::string angleValue, std::string xValue, std::string yValue, std::string zValue);

		/// @brief Devuelve el vector de strings asociado a una id en el mapa _args y comprueba que sea de tamanno 'numArgs'. 
		/// En caso negativo, se llama a HandleArgumentError()
		/// @param id Valor en el mapa a conseguir
		/// @param type Tipo del valor a conseguir
		/// @param numArgs Numero de argumentos que debe tener para ser parseado
		std::vector<std::string> GetKey(std::string id, std::string type, int numArgs);

		/// @brief Igual que GetKey(string, string, int), pero no comprueba tamanno ni lanza error
		std::vector<std::string> GetKey(std::string id, std::string type);

		/// @brief _id Debe definirse en la constructora
		std::string _id = "DEFAULT_ID_CHANGE_THIS";

		/// @brief Mapa que guarda los argumentos y los asocia a un vector de strings que es parseado segun necesite el usuario con 
		/// las funciones publicas de la clase
		std::unordered_map<std::string, std::vector<std::string>> _args;
	};
}

#endif // COMPONENT_ARGUMENTS_H
