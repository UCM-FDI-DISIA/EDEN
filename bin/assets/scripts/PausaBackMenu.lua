--Definicion de la clase en Lua
PausaBackMenu = {}

PausaBackMenu.__index = PausaBackMenu

--Constructor de la clase en Lua
function PausaBackMenu:new()
	local obj={}
	setmetatable(obj, PausaBackMenu)
	return obj
end

--Metodo OnButtonClicked
function PausaBackMenu:OnButtonClick()
	
end
function PausaBackMenu:OnButtonReleased()
	Pausa:BackMenu();
end
--Variable global de la clase (para Luabridge)
PausaBackMenuLua = PausaBackMenu:new()