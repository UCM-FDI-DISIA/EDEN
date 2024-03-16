--Definicion de la clase en Lua
buttonMenu = {}

buttonMenu.__index = buttonMenu

--Constructor de la clase en Lua
function buttonMenu:new()
	local obj={}
	setmetatable(obj, buttonMenu)
	return obj
end

--Metodo OnButtonClicked
function buttonMenu:OnButtonClick()
	print("Estoy encima del boton");
end
function buttonMenu:OnButtonReleased()
	print("Has dejado de pulsar para ir al menú\n");
	
end
--Variable global de la clase (para Luabridge)
buttonMenuLua = buttonMenu:new()