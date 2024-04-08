Entity1 = {
    Name = "Player", 
    Components = {
        {
            Name = "TRANSFORM", 
            Arguments = {
                Position = "10|-5|0",
                Rotation = "true|1|0|0|0",
                Scale = "30|30|30"
            }
        },
        {
            Name = "MESH_RENDERER",
            Arguments = {
                Mesh = "Cube.057"
            }
        }
    }
}

Entity2 = {
	Name = "CameraEntity",
	Components = {
		{
			Name = "TRANSFORM",
			Arguments = {
				Position = "-700|-10|250",
                Rotation = "true|-45|0|1|0",
                Scale = "0.2|0.2|0.2"
			}
		},
		{
			Name = "CAMERA",
			Arguments = {
			}
		}
	}	
}

Entity6 = {
    Name = "Ground", 
    Components = {
        {
            Name = "TRANSFORM", 
            Arguments = {
                Position = "10|-200|0",
                Rotation = "true|1|0|0|0",
                Scale = "0.2|0.05|0.2"
            }
        },
        {
            Name = "MESH_RENDERER",
            Arguments = {
                Mesh = "Cube.057"
            }
        }
        
    }
}
Entities = { Entity1, Entity2, Entity6 }

CollisionLayers = { 
    Layers = {
        RAYCAST = "",
        DEFAULT = "",
        PLAYER = "",
        GROUND = ""
    }
}