Entity1 = {
	Name = "Camera",
	Components = {
		{
			Name = "TRANSFORM",
			Arguments = {
				Position = "-5.921108245849609|-11.02579116821289|1.858309268951416",
				Rotation = "0.646895170211792|0.6883831024169922|-0.23910118639469147|-0.22469086945056915",
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
	Name = "Cube",
	Components = {
		{
			Name = "MESH_RENDERER",
			Arguments = {
				Mesh = "PruebaCubo"
			}
		},
		{
			Name = "TRANSFORM",
			Arguments = {
				Position = "0.0|0.0|0.0",
				Rotation = "1.0|0.0|0.0|0.0",
				Scale = "1.0|1.0|1.0"
			}
		}
	}
}

Entities = { Entity1, Entity2 }

CollisionLayers = {
	Layers = {
		DEFAULT = ""
	}
}