--Definicion de la clase en Lua
finishLineTest = {}

finishLineTestTest.__index = finishLineTest

--Constructor de la clase en Lua
function finishLineTest:new()
	local obj={}
	setmetatable(obj, finishLineTest)
	return obj
end

--Metodo OnCollisionEnter
function collisionTest:OnCollisionEnter()
	FinishLine:DestroyEnemies();
end
--Variable global de la clase (para Luabridge)
finishLineTestLua = finishLineTest:new()