--Definicion de la clase en Lua
collisionTest = {}

collisionTest.__index = collisionTest

--Constructor de la clase en Lua
function collisionTest:new()
	local obj={}
	setmetatable(obj, collisionTest)
	return obj
end

--Metodo OnCollisionEnter
function collisionTest:OnCollisionEnter()
	--print("Entra colision\n");
	Hito1Prueba:Collide();
end
function collisionTest:OnCollisionStay(Entity)
	print("Se queda colision\n");
end
function collisionTest:OnCollisionExit()
	print("Sale colision");
end
--Variable global de la clase (para Luabridge)
collisionTestLua = collisionTest:new()