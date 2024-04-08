--Definicion de la clase en Lua
PausaResume = {}

PausaResume.__index = PausaResume

--Constructor de la clase en Lua
function PausaResume:new()
	local obj={}
	setmetatable(obj, PausaResume)
	return obj
end

--Metodo OnButtonClicked
function PausaResume:OnButtonClick()
	print("Estoy encima del boton");
end
function PausaResume:OnButtonReleased()
	print("Estoy encima del boton");
	Pausa:Resume();
end
--Variable global de la clase (para Luabridge)
PausaResumeLua = PausaResume:new()