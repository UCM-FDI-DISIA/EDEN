Entity1 = {
	Name = "Camera",
	Components = {
		{
			Name = "TRANSFORM",
			Arguments = {
				Position = "-9.600000381469727|4.0|14.0",
				Rotation = "1.0|0|0|0",
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
	Name = "UI_Button",
	Components = {
		{
			Name = "BUTTON",
			Arguments = {
                OverlayName= "button",
				XPos = "50",
                YPos = "80",
                Width = "125",
                Height = "75",
                Texture1 = "MenuButton_Ini.png",
                Texture2 = "MenuButton_Over.png",
                Texture3 = "MenuButton_Clicked.png",
                Depth = "2"
			}
		},
        {
            Name = "BEHAVIOUR",
			Arguments = {
                Script= "buttonTest",
			}
        },
		{
            Name = "PRUEBA",
            Arguments = {
			}
        }
	}	
}

Entity3 = {
	Name = "UI_Cursor",
	Components = {
		{
			Name = "CURSOR",
			Arguments = {
                Width = "20",
                Height = "20",
                Texture = "Cursor.png",
                Depth = "10"
			}
		}
	}	
}
Entity4 = {
	Name = "UI_Image",
	Components = {
		{
			Name = "IMAGE",
			Arguments = {
                OverlayName= "image",
				XPos = "50",
                YPos = "50",
                Width = "650",
                Height = "500",
                Texture = "MainMenuBackground.png",
                Depth = "1"
			}
		}
	}	
}

Entities = { Entity1, Entity2, Entity3,Entity4}

CollisionLayers = {
	Layers = {
		Carretera = "DEFAULT",
		Decoracion = "DEFAULT",
		Edificios = "DEFAULT"
	}
}