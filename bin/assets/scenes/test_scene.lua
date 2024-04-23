Entity1 = {
    Name = "Player", 
    Components = {
        {
            Name = "TRANSFORM", 
            Arguments = {
                Position = "10|-5|0",
                Rotation = "true|-45|0|1|0",
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
        },
        {
			Name = "TEXT",
			Arguments = {
                OverlayName= "textTest",
				XPos = "75",
                YPos = "5",
                Tam = "10",
                Text = "Clicks: ",
                Font = "DejaVuSerifCondensed-Italic.ttf",
                Color = "255|255|255",
                Depth = "1"
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
				Position = "-700|-10|750",
                Rotation = "true|-45|0|1|0",
                Scale = "0.2|0.2|0.2"
			}
		},
		{
			Name = "CAMERA",
			Arguments = {
			}
		},
		{
			Name = "AUDIO_LISTENER",
			Arguments = {
			}
		}
	}	
}

Entity3 = {
	Name = "UI_Text",
	Components = {
		{
			Name = "TEXT",
			Arguments = {
                OverlayName= "text",
				XPos = "25",
                YPos = "5",
                Tam = "10",
                Text = "TEXTO UI",
                Font = "DejaVuSerifCondensed-Italic.ttf",
                Color = "255|255|0",
                Depth = "1"
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
                Width = "25",
                Height = "10",
                Texture1 = "PlayButton_Ini.png",
                Texture2 = "PlayButton_Hover.png",
                Texture3 = "PlayButton_Clicked.png",
                Depth = "1"
			}
		},
        {
            Name = "BEHAVIOUR",
			Arguments = {
                Script= "buttonTest",
			}
        }
	}	
}

Entity5 = {
	Name = "UI_Cursor",
	Components = {
        {
			Name = "IMAGE",
			Arguments = {
                OverlayName= "image",
				XPos = "0",
                YPos = "0",
                Width = "5",
                Height = "5",
                Texture = "Cursor.png",
                Depth = "10"
			}
		},
		{
			Name = "CURSOR",
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
                Rotation = "true|0|0|0|0",
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
                Bounciness = "0",
                Friction = "0"
            }
        }
        
    }
}

Entity7 = {
	Name = "UI_Image",
	Components = {
		
	}	
}

Entity8 = {
	Name = "AudioEmitter",
	Components = {
		{
            Name = "TRANSFORM", 
            Arguments = {
                Position = "-700|0|250",
                Rotation = "true|0|0|0|0",
                Scale = "1|1|1"
            }
        },
		{
			Name = "AUDIO_EMITTER",
			Arguments = {
				SongName = "bell.wav",
				Is3D = "false"
			}
		}
	}
}

Entities = { Entity1, Entity2, Entity3, Entity4, Entity5, Entity6, Entity7, Entity8 }

CollisionLayers = { 
    Layers = {
        RAYCAST = "",
        DEFAULT = "",
        PLAYER = "",
        GROUND = ""
    }
}