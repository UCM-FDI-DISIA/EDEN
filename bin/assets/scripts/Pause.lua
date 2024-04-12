--Definicion de la clase en Lua
Pause = {}

Pause.__index = Pause

--Constructor de la clase en Lua
function Pause:new()
	local obj={}
	setmetatable(obj, Pause)
	return obj
end

--Metodo OnButtonClicked
function Pause:OnButtonClick()
	print("Estoy encima del boton");
end
function Pause:OnButtonReleased()
	print("Estoy encima del boton");
	Game:Pause();
end
--Variable global de la clase (para Luabridge)
PauseLua = Pause:new()