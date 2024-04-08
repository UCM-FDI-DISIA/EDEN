--Definicion de la clase en Lua
PausaExit = {}

PausaExit.__index = PausaExit

--Constructor de la clase en Lua
function PausaExit:new()
	local obj={}
	setmetatable(obj, PausaExit)
	return obj
end

--Metodo OnButtonClicked
function PausaExit:OnButtonClick()
	
end
function PausaExit:OnButtonReleased()
	Pausa:Exit();
end
--Variable global de la clase (para Luabridge)
PausaExitLua = PausaExit:new()