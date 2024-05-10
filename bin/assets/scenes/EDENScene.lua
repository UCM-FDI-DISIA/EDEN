Entity1 = {
	Name = "Camera",
	Components = {
		{
			Name = "TRANSFORM",
			Arguments = {
				Position = "0|6|0",
				Rotation = "false|1.0|0|0|0",
				Scale = "1.0|1.0|1.0"
			}
		},
		{
			Name = "CAMERA",
			Arguments = {
			}
		},
        {
            Name = "CEDEN_SCENE_COMP",
            Arguments = {
                
            }
        }
	}
}

Entity2 = {
	Name = "CubeStudiosLogo",
	Components = {
		{
			Name = "IMAGE",
			Arguments = {
				OverlayName = "cubestudioslogo",
				XPos = "50",
                YPos = "30",
                Width = "10",
                Height = "15",
                Texture = "cubestudioslogo.png",
                Depth = "0"
			}
		}
	}	
}

Entity3 = {
	Name = "RunsOnText",
	Components = {
		{
			Name = "TEXT",
			Arguments = {
                OverlayName= "runsontext",
				XPos = "42",
                YPos = "50",
                Tam = "9",
                Text = "This game runs on",
                Font = "Audiowide-Regular.ttf",
                Color = "255|255|255",
                Depth = "0"
			}
		}
	}	
}

Entity4 = {
	Name = "EdenLogo",
	Components = {
		{
			Name = "IMAGE",
			Arguments = {
				OverlayName = "edenlogo",
				XPos = "69",
                YPos = "52",
                Width = "10",
                Height = "15",
                Texture = "edenlogo.png",
                Depth = "0"
			}
		}
	}	
}

Entities = {Entity1, Entity2, Entity3, Entity4}

CollisionLayers = {
	Layers = {
		DEFAULT = ""
	}
}