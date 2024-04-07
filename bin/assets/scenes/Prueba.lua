Entity1 = {
	Name = "Camera",
	Components = {
		{
			Name = "TRANSFORM",
			Arguments = {
				Position = "7.358891487121582|4.958309173583984|6.925790786743164",
				Rotation = "0.7804827094078064|0.483536034822464|-0.33687159419059753|0.20870360732078552",
				Scale = "1.0|1.0|1.0"
			}
		},
		{
			Name = "CAMERA",
			Arguments = {
			}
		}
	}
}

Entity2 = {
	Name = "Frog",
	Components = {
		{
			Name = "MESH_RENDERER",
			Arguments = {
				Mesh = "Cube.057"
			}
		},
		{
			Name = "TRANSFORM",
			Arguments = {
				Position = "0.0|-0.954870343208313|-0.0",
				Rotation = "1.0|0.0|-0.0|0.0",
				Scale = "10.0|10.0|10.0"
			}
		}
	}
}

Entities = { Entity1, Entity2 }

CollisionLayers = {
	Layers = {
		DEFAULT = "DEFAULT"
	}
}