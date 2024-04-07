Entity1 = {
    Name = "Player", 
    Components = {
        {
            Name = "TRANSFORM", 
            Arguments = {
                Position = "10|-5|0",
                Rotation = "-45|0|1|0",
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
            Name = "ANIMATOR",
            Arguments = {
                AnimNames = "Die|Duck|HitReact|Idle|JumpIdle|JumpLand|JumpStart|No|Punch|Run|Walk|Wave|Weapon|Yes",
                AnimMeshNames = "Frog_Death|Frog_Duck|Frog_HitReact|Frog_Idle|Frog_JumpIdle|Frog_JumpLand|Frog_JumpStart|Frog_No|Frog_Punch|Frog_Run|Frog_Walk|Frog_Wave|Frog_Weapon|Frog_Yes",
                NextAnim = "Idle|Idle|Idle|Idle|JumpLand|Idle|JumpIdle|Idle|Idle|Idle|Idle|Idle|Idle|Idle",
                LoopAnims = "false|false|false|true|false|false|false|false|false|true|true|false|false|false"
			}
        },
        {
            Name = "PRUEBA",
            Arguments = {
			}
        },
        {
            Name = "BEHAVIOUR",
			Arguments = {
                Script= "collisionTest",
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
        -- {
        --     Name = "PARTICLE_EMITTER",
        --     Arguments = {
        --         Name = "Test",
        --         Loop = "true",
        --         Time = "1",
        --         Started = "true"
        --     }
        -- },
        {
			Name = "TEXT",
			Arguments = {
                OverlayName= "textTest",
				XPos = "75",
                YPos = "5",
                Tam = "50",
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
	Name = "UI_Text",
	Components = {
		{
			Name = "TEXT",
			Arguments = {
                OverlayName= "text",
				XPos = "25",
                YPos = "5",
                Tam = "50",
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
                Width = "150",
                Height = "50",
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

Entity6 = {
    Name = "Ground", 
    Components = {
        {
            Name = "TRANSFORM", 
            Arguments = {
                Position = "10|-200|0",
                Rotation = "0|0|0|0",
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

Entity7 = {
	Name = "UI_Image",
	Components = {
		{
			Name = "IMAGE",
			Arguments = {
                OverlayName= "image",
				XPos = "50",
                YPos = "70",
                Width = "300",
                Height = "150",
                Texture = "meme.png",
                Depth = "1"
			}
		}
	}	
}

Entities = { Entity1, Entity2, Entity3, Entity4, Entity5, Entity6, Entity7 }

CollisionLayers = { 
    Layers = {
        RAYCAST = "",
        DEFAULT = "",
        PLAYER = "",
        GROUND = ""
    }
}