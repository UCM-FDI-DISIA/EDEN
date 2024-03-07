Entity1 = {
    Name = "Player", 
    Components = {
        {
            Name = "TRANSFORM", 
            Arguments = {
                Position = "70|-10|0",
                Rotation = "-45|0|1|0",
                Scale = "0.2|0.2|0.2"
            }
        },
        {
            Name = "MESH_RENDERER",
            Arguments = {
                Mesh = "cube"
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
                Rotation = "-45|0|1|0",
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

Entity3 = {
	Name = "UI",
	Components = {
		{
			Name = "IMAGE",
			Arguments = {
                OverlayName= "image",
				XPos = "50",
                YPos = "50",
                Width = "200",
                Height = "150",
                Texture = "final",
                Depth = "1"
			}
		}
	}	
}


Entities = { Entity1, Entity2, Entity3 }