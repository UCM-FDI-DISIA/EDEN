Entity1 = {
    Name = "Player2", 
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
        },
        {
            Name = "RIGIDBODY", 
            Arguments = {
                Mass = "1",
                AABB = "1|10|1",
                PosOffset = "0|0|0",
                Radius = "0",
                Shape = "BOX",
                CollisionFlag = "DYNAMIC",
                CollisionLayer = "PLAYER",
                Bounciness = "1",
                Friction = "0"
            }
        }
    }
}

Entity2 = {
	Name = "CameraEntity2",
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
    Name = "Ground2", 
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
                Mesh = "cube"
            }
        },
        {
            Name = "RIGIDBODY", 
            Arguments = {
                Mass = "1",
                AABB = "100|10|100",
                PosOffset = "0|0|0",
                Radius = "0",
                Shape = "BOX",
                CollisionFlag = "STATIC",
                CollisionLayer = "GROUND",
                Bounciness = "1",
                Friction = "0"
            }
        }
        
    }
}
Entities = { Entity1, Entity2, Entity6, Entity7 }

CollisionLayers = { 
    Layers = {
        RAYCAST = "",
        DEFAULT = "",
        PLAYER = "",
        GROUND = ""
    }
}