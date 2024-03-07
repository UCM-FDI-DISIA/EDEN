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


Entities = { Entity1 }