#include "CNetwork.h"
#include "ComponentArguments.h"

void eden_ec::CNetwork::Init(eden_script::ComponentArguments* args)
{
	std::string namemode = args->GetValueToString("NetworkMode");
	if (namemode == "TCP") networkManager = new eden_net::NetworkManager(NetworkMode::TCP);
	else networkManager = new eden_net::NetworkManager(NetworkMode::UDP);
}

void eden_ec::CNetwork::Update(float dt)
{
	
}
