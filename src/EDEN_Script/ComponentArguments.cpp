#include <iostream>
#include <vector>
#include <exception>

#include "ComponentArguments.h"
#include "Vector3.h"
#include <Quaternion.h>

namespace eden_script {

	void ComponentArguments::HandleArgumentError(std::string id, std::string type, int numArgs) {
		std::string errorMsg = "Error while constructing '" + _id + "' component. Argument '" + id + "' has more or less than " + std::to_string(numArgs) + " value(s), so it can't be converted to " + type;
		std::cerr << errorMsg;
#ifdef _MSC_VER
		throw(std::exception(errorMsg.c_str()));
#endif
#ifdef __clang__
		throw std::exception();
#endif
	};

	std::vector<std::string> ComponentArguments::GetKey(std::string id, std::string type, int numArgs) {
		auto arg = _args.find(id);
		if (arg != _args.end()) {
			if (arg->second.size() != numArgs) {
				HandleArgumentError(id, type, numArgs);
			}
			else {
				return arg->second;
			}
		}
		else {
			// error
			std::cerr << '\'' << id << "' was not found while constructing '" << _id <<'\'' << '\n';
			// deber�amos tirar excepci�n aqu� o algo?
#ifdef _MSC_VER
			throw(std::exception("\n\n"));
#endif
#ifdef __clang__
			throw std::exception();
#endif
			return std::vector<std::string>();
		}
	}

	std::vector<std::string> ComponentArguments::GetKey(std::string id, std::string type) {
		auto arg = _args.find(id);
		if (arg != _args.end()) {
			return arg->second;
		}
		else {
			// error
			std::cerr << '\'' << id << "' was not found while constructing '" << _id << '\'' << '\n';
			// deber�amos tirar excepci�n aqu� o algo?
#ifdef _MSC_VER
			throw(std::exception("\n\n"));
#endif
#ifdef __clang__
			throw std::exception();
#endif
			return std::vector<std::string>();
		}
	}

	eden_utils::Vector3 ComponentArguments::ToVector3(std::string xValue, std::string yValue, std::string zValue) {
		float x = std::stof(xValue);
		float y = std::stof(yValue);
		float z = std::stof(zValue);

		return eden_utils::Vector3(x, y, z);
	}

	eden_utils::Vector3 ComponentArguments::GetValueToVector3(std::string id) {
		auto arg = GetKey(id, "Vector3", 3);

		return ToVector3(arg[0], arg[1], arg[2]);
	}

	std::vector<eden_utils::Vector3> ComponentArguments::GetValueToVector3Vector(std::string id) {
		auto arg = GetKey(id, "Vector3 vector");

		int n = arg.size();

		std::vector<eden_utils::Vector3> value(n/3);

		for (int i = 0; i < n; i++) {
			value[i] = ToVector3(arg[i*3], arg[i*3+1], arg[i*3+2]);
		}

		return value;
	}

	eden_utils::Quaternion ComponentArguments::ToQuaternion(std::string angleValue, std::string xValue, std::string yValue, std::string zValue) {
		float angle = std::stof(angleValue);

		return eden_utils::Quaternion(angle, ToVector3(xValue, yValue, zValue));
	}

	eden_utils::Quaternion ComponentArguments::GetValueToQuaternion(std::string id) {
		auto arg = GetKey(id, "Quaternion", 4);

		return ToQuaternion(arg[0], arg[1], arg[2], arg[3]);
	}

	std::vector<eden_utils::Quaternion> ComponentArguments::GetValueToQuaternionVector(std::string id) {
		auto arg = GetKey(id, "Quaternion vector");

		int n = arg.size();

		std::vector<eden_utils::Quaternion> value(n / 4);

		for (int i = 0; i < n; i++) {
			value[i] = ToQuaternion(arg[i * 4], arg[i * 4 + 1], arg[i * 4 + 2], arg[i*4 +3]);
		}

		return value;
	}

	bool ComponentArguments::ToBool(std::string value) {
		for (int i = 0; i < value.size(); ++i) {
			value[i] = std::tolower(value[i]);
		}

		return value == std::string("true");
	}

	bool ComponentArguments::GetValueToBool(std::string id) {
		std::string value = GetKey(id, "bool", 1)[0];

		return ToBool(value);
	}

	std::vector<bool> ComponentArguments::GetValueToBoolVector(std::string id) {
		auto arg = GetKey(id, "vector bool");

		int n = arg.size();
		std::vector<bool> value(n);

		for (int i = 0; i < n; ++i) {
			value[i] = ToBool(arg[i]);
		}

		return value;
	}

	int ComponentArguments::ToInt(std::string value) {
		return std::stoi(value);
	}

	int ComponentArguments::GetValueToInt(std::string id) {
		auto arg = GetKey(id, "int", 1);

		return ToInt(arg[0]);
	}

	std::vector<int> ComponentArguments::GetValueToIntVector(std::string id) {
		auto arg = GetKey(id, "vector int");

		int n = arg.size();
		std::vector<int> value(n);

		for (int i = 0; i < n; ++i) {
			value[i] = ToInt(arg[i]);
		}

		return value;
	}

	float ComponentArguments::ToFloat(std::string value) {
		return std::stof(value);
	}

	float ComponentArguments::GetValueToFloat(std::string id) {
		auto arg = GetKey(id, "float", 1);

		return ToFloat(arg[0]);
	}

	std::vector<float> ComponentArguments::GetValueToFloatVector(std::string id) {
		auto arg = GetKey(id, "vector float");

		int n = arg.size();
		std::vector<float> value(n);

		for (int i = 0; i < n; ++i) {
			value[i] = ToFloat(arg[i]);
		}

		return value;
	}

	double ComponentArguments::ToDouble(std::string value) {
		return std::stod(value);
	}

	double ComponentArguments::GetValueToDouble(std::string id) {
		auto arg = GetKey(id, "double", 1);

		return ToDouble(arg[0]);
	}

	std::vector<double> ComponentArguments::GetValueToDoubleVector(std::string id) {
		auto arg = GetKey(id, "vector double");

		int n = arg.size();
		std::vector<double> value(n);

		for (int i = 0; i < n; ++i) {
			value[i] = ToDouble(arg[i]);
		}

		return value;
	}

	std::string ComponentArguments::GetValueToString(std::string id) {
		auto arg = GetKey(id, "string", 1);

		return arg[0];
	}

	std::vector<std::string> ComponentArguments::GetValueToStringVector(std::string id) {
		return GetKey(id, "vector string");
	}
}