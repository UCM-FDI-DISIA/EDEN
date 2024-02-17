# EDEN Game Engine
<br>
## Estructura de la solución y proyectos
### Repositorios y proyectos
Utilizaremos 3 repositorios, cada uno con una solución. En el caso del motor, tendremos varios proyectos. La solución se dividirá en proyectos dependiendo de la funcionalidad que aporten (ej: Físicas, Render, Input…).
<br>
### Soluciones
La estructura de las soluciones tendrá la siguiente forma:

#### Archivo .sln
#### bin
Ejecutable (.exe, .lib, .dll) (gitignore)
##### Carpeta Assets
Carpetas para diferentes tipos de assets (meshes, audio, etc)
<br>
#### projects
##### Carpeta por cada proyecto
.vcxproj
.vcxproj.filters
.vcxproj.user (gitignore)
<br>
#### src
##### Carpeta por cada proyecto
.h
.cpp
<br>
#### tmp (gitignore)
##### Carpeta por cada proyecto
###### Carpeta por cada opción de compilación
Archivos temporales del proyecto (.log, .obj, etc)
<br>
#### dependencies
Bibliotecas externas
<br><br>
## Estructura de las clases
Usaremos la estructura Entity-Component. Las entidades tendrán contenidos los componentes, que aportan la funcionalidad. Por otro lado, tendremos un gestor de escenas, que funciona como una pila donde se van almacenando las escenas, y se renderiza y actualiza la última escena añadida.
<br><br>
## Estructura de componentes del motor y juegos
En el motor existirá una clase “ComponentManager” que sigue un patrón de diseño factoría y singleton. Esta factoría tiene una estructura de datos de tipo mapa, que guarda para cada identificador de tipo string una función encargada de construir un tipo de una clase derivada de la clase padre “Component”. La factoría tendrá un método para registrar nuevos métodos constructores asociados a un id único y un método que dado un identificador devuelve una instancia de un objeto de la clase asociada a dicho identificador, siempre y cuando ese identificador esté presente en el mapa.

Al inicializar el motor, se añaden los componentes del mismo (transform, …) al mapa del ComponentManager. Los componentes creados para el juego deberán heredar de la clase Component del motor. De esta manera, al cargar el juego se añaden todos sus componentes al mapa de la clase Factoría usando el método register. 
Para cargar los componentes se hará a través del archivo .lua, que dará forma a una entidad con una serie de componentes definidos según la id usada en el mapa de la factoría y los parámetros que el componente requiera para ser creado. Los archivos Lua describirán las escenas con las entidades que las contienen, los componentes de cada entidad y los parámetros de esos componentes, mediante el uso de la estructura “Table”, propia de Lua.

### Bibliotecas:
<table>
	<tr>
		<th><b>Físicas</b></th>
		<th>Bullet Physics SDK</th>
	</tr>
	<tr>
		<th><b>Render</b></th>
		<th>Ogre</th>
	</tr>
	<tr>
		<th><b>Interfaz / Input</b></th>
		<th>SDL</th>
	</tr>
	<tr>
		<th><b>Scripting y escenas</b></th>
		<th>Luabridge</th>
	</tr>
	<tr>
		<th><b>Audio</b></th>
		<th>FMOD Core</th>
	</tr>
</table>
Cada biblioteca tiene su propio manager para encapsularlas y que puedan ser usadas en el resto del código, implementadas mediante el patrón Singleton (ej: PhysicsManager). De esta manera, el motor no depende de ninguna biblioteca en específico, ya que usa la abstracción dada por los managers. 

### Componentes del motor
<table>
<tr>
	<th>
		<ul>
				<li>Transform</li>
				<li>RigidBody</li>
				<li>Collider</li>
				<li>Animator</li>
				<li>Mesh renderer</li>
				<li>Camera</li>
				<li>Light</li>
				<li>ParticleSystem</li>
				<li>Button</li>
				<li>Image</li>
		</ul>
	</th>
<th>
		<ul>
<li>Text</li>
<li>AudioPlayer</li>
<li>AudioListener</li>
<li>InputManager</li>
<li>PhysicsManager</li>
<li>RenderManager</li>
<li>UIManager</li>
<li>SoundManager</li>
<li>LuaManager</li>
<li>ComponentManager</li>
</ul>
	</th>
</tr>
</table>

<br><br>
## Pipeline de generación de contenido
### Objetos 3D
Creación de assets 3D propios en blender o importación de assets de terceros.
Uso del addon “blender2ogre” para exportar los modelos 3D a archivos “.mesh” que se pueden abrir en Ogre usando un componente “mesh renderer”.

### Sonido
Uso de MP3 (música de fondo)/ WAV (efectos de sonido) de creación propia o de uso libre para la reproducción de sonidos. El sonido se implementará en el juego mediante el componente “audio player”. Usaremos FMOD para editar los audios.

### Imágenes
Imágenes PNG y JPG importadas al proyecto y gestionadas por el componente “image” o por Ogre para materiales y texturas.
