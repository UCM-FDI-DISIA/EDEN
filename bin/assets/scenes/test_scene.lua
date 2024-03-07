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
	Name = "UI_Image",
	Components = {
		{
			Name = "IMAGE",
			Arguments = {
                OverlayName= "image",
				XPos = "50",
                YPos = "70",
                Width = "250",
                Height = "150",
                Texture = "meme",
                Depth = "0"
			}
		}
	}	
}

Entity4 = {
	Name = "UI_Button",
	Components = {
		{
			Name = "BUTTON",
			Arguments = {
                OverlayName= "button",
				XPos = "50",
                YPos = "25",
                Width = "150",
                Height = "50",
                Texture1 = "iniMat",
                Texture2 = "hoverMat",
                Texture3 = "clickedMat",
                Depth = "1"
			}
		}
	}	
}

Entity5 = {
	Name = "UI_Cursor",
	Components = {
		{
			Name = "CURSOR",
			Arguments = {
                Width = "20",
                Height = "20",
                Texture = "cursor",
                Depth = "10"
			}
		}
	}	
}

Entities = { Entity1, Entity2, Entity3, Entity4, Entity5 }