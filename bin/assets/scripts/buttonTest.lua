--Definicion de la clase en Lua
buttonTest = {}

buttonTest.__index = buttonTest

--Constructor de la clase en Lua
function buttonTest:new()
	local obj={}
	setmetatable(obj, buttonTest)
	return obj
end

--Metodo OnButtonClicked
function buttonTest:OnButtonClick()
	print("Estoy encima del boton");
	Hito1Prueba:SetJump();
	--InputManager:SetCloseWindow();
end
function buttonTest:OnButtonReleased()
	print("Has dejado de pulsar para ir al menú\n");
	Hito1Prueba:SetClick();
end
--Variable global de la clase (para Luabridge)
buttonTestLua = buttonTest:new()