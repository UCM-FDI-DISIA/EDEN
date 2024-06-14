# --- ENLACES REPOSITORIOS DE JUEGOS DESARROLLADOS CON EDEN ---
- [Damn](https://github.com/UCM-FDI-DISIA/Damn)
- [Cross The Path](https://github.com/UCM-FDI-DISIA/CrossthePath)

# EDEN – Documento de Arquitectura 

## Introducción 

EDEN es un motor dirigido por datos para el desarrollo de aplicaciones interactivas en 3D programado en C++. Implementa soporte para:

- Renderizado de objetos 3D 
- Físicas 3D 
- Interfaz de usuario 
- Input desde teclado y ratón 
- Audio espacial y no espacial 
- Creación de niveles desde Blender
- Definición de objetos básicos instanciables (Ej: *Prefabs* en Unity) 
- Gestión de escenas sencilla

Usa una estructura de Entidad-Componente (EC) básica para definir los objetos de juego y sus comportamientos. Además, estas *Entidades* se encuentran agrupadas en lo que conocemos como *Escenas* dentro de nuestro motor. Solo existe una *escena* activa a la vez, que actualiza las entidades activas, haciendo que se ejecute el comportamiento de sus componentes habilitados.

Además, estas escenas son cargadas a través de la implementación de *Lua*, un lenguaje interpretado  sencillo que nos permite definir las entidades y sus componentes en un archivo .lua, que no necesita de compilación y podemos cambiar incluso durante la ejecución del juego.  

Usando Lua también somos capaces de ejecutar  *Callbacks* para interfaz de usuario y *Colisiones*, de esta forma somos capaces de registrar clases de C++ en una máquina virtual de Lua para poder acceder a métodos desde un archivo .lua.

Se ha aprovechado la potencia de Blender como herramienta para creación de entornos 3D para ayudarnos a generar las escenas del juego. Esto se ha conseguido gracias a un script de Python (BlenderSceneParser.py) que nos permite conseguir parámetros de posición y  *CustomProperties* (propiedades puestas por el usuario a mano para definir argumentos de componentes), además de la malla y sus dimensiones, para generar una escena de forma mucho más sencilla que simplemente con Lua.

## Librerías externas utilizadas 

EDEN reúne una serie de librerías de terceros para implementar su funcionalidad:

- **OGRE**: Motor de renderizado de código abierto utilizado. Utiliza como sistema de renderizado OpenGL. 
- **Bullet3D**: Motor físico de código abierto utilizado para el comportamiento físico de los objetos. 
- **OgreOverlay**: Librería incluida dentro de OGRE, usada específicamente para interfaz. 
- **SDL**: Utilizada dentro de OGRE para generación de ventana, además de recepción de input.** 
- **Luabridge**: Facilita en gran medida la incrustación de Lua dentro de C++. Usado únicamente para gestión de *callbacks.* 

## Estructura y explicación básica del código fuente 

Para el desarrollo del motor se ha utilizado Visual Studio 2022 como IDE. El archivo EDEN.sln permite abrir el código fuente, verlo y modificarlo si fuera necesario. Se organiza en 10 proyectos diferentes: 

|**EDEN\_Audio**|  Contiene las clases necesarias para  envolver las funciones de irrKlang, haciendo más legible el contenido de la librería para clases externas que lo  necesiten.|  
| - | :- |
|**AudioEngine** |*Wrapper* del motor de audio de irrKlang |
|**AudioManager** |Gestor de todos los sonidos presentes en la aplicación a desarrollar |
|**Sound** |Representación del sonido en el motor |
|**SoundClip** |Referencia al archivo de audio utilizado |


|**EDEN\_Input**| Utiliza dos clases para abstraer el comportamiento de SDL con respecto a gestión de Input.|
| - | :- |
|**InputWrapper** |inaccesible por el usuario, solo devuelve un evento de SDL |
|**InputManager** |<p>Trata los eventos de SDL generados por teclado y ventana, ofreciendo métodos para saber cuándo se pulsa </p><p>o se deja de pulsar una tecla, etc</p>|

|**EDEN\_Physics**| Gestiona por completo el comportamiento físico de los objetos del  juego.  Actúa  como  envoltorio  para  Bullet3D  y otorga la  funcionalidad  de colisiones  y  *callbacks*  generados  por  las  mismas. Cualquier actualización del mundo físico y sus objetos se hace en lo que se conoce como un  *FixedUpdate*, que es una actualización de las físicas que se ejecuta  precisamente  cada  X  período  de  tiempo. Durante esta actualización se le dice a Bullet cuál es la posición renderizada de nuestra entidad, además de su rotación y su escala. Bullet calculará los cambios en la física por nosotros al aplicársele o no una fuerza/velocidad al  objeto.  Por último,  los  transformaremos  a  nuestro  componente  de  posición,  rotación  y escala, para que en el renderizado se muestren los cambios sucedidos por estas transformaciones.|
| - | :- |
|**CollisionCallback** |Creado por un RigidBody para gestionar el resultado de una colisión|
|**CollisionLayer** |Guarda la información necesaria para generar una capa de colisión |
|**PhysicsManager** |Llamado en el FixedUpdate con el comportamiento descrito arriba|
|**RayCast** |Clase que genera un rayo desde un punto concreto hasta un final y guarda información acerca de con qué ha colisionado |
|**RigidBody** |Actúa como envoltorio de la clase btRigidBody propia de Bullet3D |
|**ShapeCreator** |Clase estática para crear formas básicas físicas |

|**EDEN\_Render**| Encargado  en  su  totalidad  de  envolver  OGRE  en  funciones  y clases sencillas para su uso en diferentes componentes. Se encarga también de mostrar todas aquellas entidades que puedan necesitar renderizado (GUI, mallas con/sin materiales y partículas)|
| - | :- |
|**Animator** |Envuelve las animaciones esqueletales ya creadas de una malla de Ogre en una clase sencilla |
|**CameraWrapper** |Envuelve la clase Camera de Ogre en un comportamiento sencillo|
|**Canvas** |Encargada de contener los elementos UI de una escena |
|**Light** |Envuelve la clase Light de Ogre en un comportamiento sencillo |
|**MeshRenderer** |Genera una entidad de Ogre y le asocia una malla dada |
|**NodeManager** |Envuelve todas las transformaciones de los objetos renderizados, guardando y gestionando sus nodos asociados. No puede manejar varios nodos con el mismo nombre. |
|**ParticleSystem** |Envuelve la clase ParticleSystem de Ogre en un comportamiento sencillo|
|**RenderManager** |Gestiona todas las entidades renderizables de la aplicación. Aplica las transformaciones necesarias y actualiza Ogre. También contiene métodos generales de gestión del proyecto (métodos para ventana y ratón, por ejemplo) |
|**RenderObject** |Clase base para los objetos de renderizado (Light, Camera, MeshRenderer y ParticleSystem) |
|**UIComponent** |Componente padre de todos los elementos de la UI |

|**EDEN\_Script**| Encargado de la implementación del lenguaje Lua, que es utilizado para lectura de escenas y gestión de *callbacks* de colisión y funciones de botones en UI|
| - | :- |
|**ComponentArguments** |Contenedor de argumentos para los componentes leídos desde un .lua. Los argumentos son guardados en *string* y pueden ser *parseados* a muchos otros tipos. |
|**LuaManager** |Se encarga de gestionar los scripts de *callbacks*, mientras que ScriptManager. |
|**ScriptManager** |Hace una gestión de la lectura y *parseo* de escenas |

|**EDEN\_Utils**| Agrupa clases útiles para el desarrollo de aplicaciones y el motor|
| - | :- |
|**Vector3** |Define  un  vector  de  3  componentes (xyz)** |
|**Quaternion** |Define el concepto de quaternion en una clase, sobre todo implementados pensando para su uso en rotaciones|
|**Singleton** |Definición del patrón Singleton comunmente usado en arquitectura para videojuegos. |
|**ErrorHandler** |Clase usada para gestión de errores (*assert* y excepciones) y advertencias** |

**EDEN\_EC**: Implemente el comportamiento básico de EC con escenas en las siguientes clases: 
- **Entidad**: Actúa como una *caja* vacía de componentes. Si continúa vacía, 

  la entidad no hace absolutamente nada, no se modifica ninguno de sus valores y no aporta nada a la aplicación. Si se le añade algún componente comenzará a tener  comportamiento que se tendrá en cuenta. De esta forma, es el componente el que define lo que hace una entidad, y no la entidad.  

  Existen diferentes métodos a tener en cuenta para las entidades:

  - **Update(float time)** -> Actualiza los componentes de la entidad.
  - **SetAlive(bool alive)** -> El usuario puede decidir si la entidad debe destruirse o no en función de si *alive* es *true* o *false*. 
  - **SetActive(bool  active)**  ->  Si  la  entidad  está  marcada  como desactivada,  no  se  actualizará  el  comportamiento  de  sus componentes. 
  - Además de estos métodos, existen otros que devuelven un componente, lo borran o inicializa su lista completa de componentes.
- **Componente:** Da un comportamiento concreto a la entidad que lo cree y lo  contenga.  Puede  ser  activado,  desactivado  y  borrado. Tiene  varios métodos destacables:
  - **Awake()** -> Método  abstracto  utilizado  para  inicializar  variables importantes que vayan a ser utilizadas por algún otro componente en un futuro cercano por una referencia al mismo. Se llama antes que Start(). 
  - **Start()** -> Método abstracto utilizado para inicializar referencias a otros  componentes,  entidades  y  variables  generales.  Se  llama antes que el primer Update(). 
  - **Init(ComponentArguments\*  info)**  ->  Es  llamado  cuando  un componente se crea desde una escena en un .lua. Es equivalente a la constructora normal del componente, pero esta constructora no  puede  ser  llamada  desde  un  componente  creado  en  una escena. Se llama antes que Awake(). 
  - **Update(float t)** -> Método abstracto que actualiza el componente. Este  va  a  ser  el  método  que  defina  el  comportamiento  del componente, pues se llamará en cada frame.
- **Scene:**  Conjunto  de  entidades  que  comparten  la  misma  escena  de renderizado y de físicas, que serán actualizados a la vez y borrados cuando se  borre  la  escena  (si  no  se  han  borrado  antes).  La  escena  contiene métodos para llamar al Awake() de las entidades y sus componentes, a su Start() y a su Update(), además de métodos para poder añadir entidades durante  ejecución.  Concretamente,  la  forma  de  llamar  al  Awake,  Start  y  Update  de  las entidades es la siguiente: 
  - Se construye la escena y se meten a un mapa desordenado, cuya *Key* es  la  iteración  actual  y  su  valor  es  una  entidad, todas  las entidades creadas.  
  - Al llegar al Update, se hace el Awake de todas las entidades, donde todas las entidades se meten a la lista de entidades actualizables de la escena.  
  - Se  llama  al  Start  de  las  entidades  nuevas después  del  Awake, aumentando el número de iteración y borrando su referencia del mapa de nuevas entidades.
  - Comienza el Update después de finalizar la llamada al Start. En caso de que se generasen nuevas entidades durante el Update de algún componente, estos se meterían al mapa de nuevas entidades en la iteración correspondiente. 
  - Vuelta al primer paso. 

- También define los componentes básicos del motor. Tratan de abstraer todo el comportamiento básico necesario para una entidad que pueda tener  posición,  renderizado,  físicas,  audio,  animaciones,  etc.

Aquí  el  listado  completo  de  los  componentes: 

<table>
<tr><th colspan="1" rowspan="11" valign="top"><b>Renderizado</b> </th>
<tr><td colspan="1" valign="top">CMeshRenderer </td><td colspan="1">Renderizado de malla y sus materiales </td></tr>
<tr><td colspan="1" valign="top">CAnimator </td><td colspan="1">Gestor de animaciones de una malla </td></tr>
<tr><td colspan="1" valign="top">CLight </td><td colspan="1">Emisor y gestor de una luz </td></tr>
<tr><td colspan="1" valign="top">CImage </td><td colspan="1">Imagen 2D mostrada en UI </td></tr>
<tr><td colspan="1" valign="top">CText </td><td colspan="1">Texto 2D mostrado en UI </td></tr>
<tr><td colspan="1" valign="top">CCursor </td><td colspan="1">Sustitución del cursor por una imagen 2D </td></tr>
<tr><td colspan="1" valign="top">CBar </td><td colspan="1">Barra 2D con valor mínimo y máximo </td></tr>
<tr><td colspan="1">CButton </td><td colspan="1">Botón interactuable 2D </td></tr>
<tr><td colspan="1" valign="top">CCamera </td><td colspan="1">Permite que se vean los elementos en pantalla </td></tr>
<tr><td colspan="1" valign="top">CParticleEmitter </td><td colspan="1">Emisor de partículas desde la posición de un CTransform </td></tr>
<tr><td colspan="1" valign="top"><b>Física</b> </td><td colspan="1" valign="top">CRigidBody </td><td colspan="1">Definición de un cuerpo sólido rígido </td></tr>
<tr><td colspan="1" rowspan="2" valign="top"><b>Audio</b> </td><td colspan="1" valign="top">CAudioEmitter </td><td colspan="1" valign="top">Emisor de audio </td></tr>
<tr><td colspan="1" valign="top">CAudioListener </td><td colspan="1">Capaz de escuchar audio en la escena </td></tr>
<tr><td colspan="1" valign="top"><b>Script</b> </td><td colspan="1" valign="top">CLuaBehaviour </td><td colspan="1">Referencia a un script de Lua que da funcionamiento a un botón o a una colisión </td></tr>
<tr><td colspan="1" valign="top"><b>General</b> </td><td colspan="1" valign="top">CTransform </td><td colspan="1">Guarda posición, rotación y escala de una entidad </td></tr>
</table>

Comportamiento más complejo o general del proyecto puede ser modificado a través de los *Managers* específicos de cada proyecto (Audio, Physics, Render...). También implementa la clase  *Scene*, que, como se menciona anteriormente, actúa  como  la  gestora  de  un  grupo  de  entidades  que  deben  coexistir  y actualizarse a la vez. Es capaz de añadir, borrar y actualizar durante la ejecución, y  recibe  la  información  para  ser  creada  de  un  .lua.

|**EDEN\_Managers**| Definición de gestores generales del motor|
| - | - |
|**ComponentFactory** |Factoría  usada  para  la  carga  de componentes  desde  aplicaciones creadas a partir del motor. |
|**ResourcesManager** |Compruebas  las  rutas  marcadas  en su  .h  para  encontrar  los  recursos necesarios  para  la  ejecución  de  la aplicación (.mesh, .png, .wav, etc.). Se guardan  referencias  a  los  archivos para poder comprobar si un recurso existe  o  no  durante  ejecución,  para poder  indicarlo  mediante  un  error  si finalmente no se ha encontrado|
|**SceneManager** |<p>Gestiona  las  escenas  del  juego mediante una pila. Hace que solo se actualice la que esté en el *top* de esta, impidiendo  la  actualización  de  las entidades en escenas que estén por debajo.  Aunque,  existe  una  escena que no se borra al cambiar entre las demás  escenas,  que  es  la “DontDestroyOnLoad”,  a  la  que pueden  meter  entidades  para  hacer que  no  se  destruyan  entre  escenas. Esta  escena  también  es  actualizada junto con la *top* de la pila*.* </p><p>También se encarga de gestionar los *blueprints,*  que  son  objetos  básicos definidos en .lua por el usuario para hacer  más  sencilla  la  creación  de objetos  durante  ejecución  y  en  la generación de escenas a mano o por Blender; de tal forma que es capaz de guardar toda la información acerca de ellos  e  instanciarlos  durante ejecución. </p><p>Además, es capaz de buscar por ID o componente la/s entidad/es entre las escenas activas y las entidades que se hayan  creado  durante  la  iteración actual. </p>|
|**Master** |Tiene referencias a todos los *managers* que deban ser actualizados en cada *frame* (o cada ciertos *frames*, como el motor fisico), ya que gestiona el bucle principal de EDEN |

|**EDEN\_Export**|  Proyecto  que  incluye  todos  los  demás  proyectos  de  EDEN definidos hasta ahora y los compila como un .dll, además de describir un archivo Export.h y Export.cpp que incluyen todos los archivos que se desean exportar a la DLL.  También  define  tres  funciones|
| - | - |
|**RegisterEngineComponents** |Registra los componentes del motor en  la  factoría  de  componentes (ComponentFactory) |
|**RunEDEN** |<p>Carga  explícitamente  la  .dll  de  la aplicación  desarrollada  (llamada genéricamente  game.dll)  y  carga  las únicas dos funciones necesarias: </p><p>- **RegisterGameComponents**: Que  registra  en  la factoría  de componentes  los componentes  definidos  en  el juego. </p><p>- **LoadScene**:  Que  carga  la escena inicial del juego.** </p>|
|**StopEDEN** |Cierra la aplicación y libera la .dll de la aplicación cargada** |


**EDEN\_Main**: Es el punto de entrada de ejecución del motor. Carga los demás proyectos del motor y en su función *main* llama a RunEDEN() y StopEDEN().

## Fallos en la arquitectura 

Hemos visto algunos fallos en la arquitectura del motor que han podido ralentizar el desarrollo de aplicaciones:

- **Falta de OnSceneChanged() en Componentes:** Al cambiar una escena, si una entidad está en una escena DontDestroyOnLoad y tiene referencias a una entidad 

  que se ha creado  la escena activa y también lo está en la siguiente, existe un frame donde el update ejecutado por la entidad no destruída tiene referencias a entidades que, o bien se han borrado y son referencias nulas, o bien se ha vuelto 

  a  conseguir  la  referencia,  pero no  se  ejecutado  su  Awake() o  su  Start(),  que pueden ser claves para otros métodos del componente necesario. 

- **Mala elección de librería de sonido:** En irrKlang, cuando queremos reproducir 

  un sonido, se ha de instanciar un objeto de la clase irrKlang::ISound  no permite modificaciones  una  vez  haya  dejado  de  sonar,  entonces  se  pierde  toda  la configuración que se haya hecho del mismo. irrKlang permite la instancia de un sonido que no se reproduzca en el momento en el que se cree, el problema es 

  que  no  hemos  encontrado  la  manera  de  reproducir  dichos  sonidos  una  vez creados, por lo que nuestra opción era reproducir los sonidos nada más crearse y apenas tener control sobre los mismos. Esto ha causado que los *wrappers* de irrKlang hayan sido tediosos y obtusos, además de dar múltiples fallos que no hemos  podido  solucionar.  Alguna  posible  solución  sería  investigar  otra  librería  de  audio  que  permita reproducir  sonidos  con  más  flexibilidad,  que,  aunque  fuera  más  difícil  de 

  implementar,  nos  hubiera  dado  un  mejor  resultado  en  el  motor. Otra solución pasa por haber planteado el envoltorio de irrKlang de una forma distinta, donde tenemos una clase que guarde toda la configuración de un sonido

  y una referencia a irrKlang::ISoundSource, que permita generar un sonido con la configuración ya guardada desde antes en el momento pedido. 

- **Desaprovechamiento  de  Lua  como  lenguaje  de  scripting:**  Lua  ofrece  un potencial realmente interesante para implementación de comportamientos que no  hemos  sabido  aprovechar.  Se  ha  generado  una  arquitectura  confusa  y demasiado compleja para simplemente llamar a una función que podría haber 

  sido  llamada  sin  problema  desde  C++,  pero  con  una  capa  de  abstracción innecesaria  desde  un  .lua. Como implementación interesante de Lua podríamos haber  aprovechado las capacidades de LuaBridge para registrar clases y métodos en Lua desde C++ y la ejecución  de  funciones  hechas  en  Lua  desde  C++  para  poder  generar  una estructura básica donde hacer el comportamiento de los componentes sin tener 

  que  usar  C++  en  las  aplicaciones  externas  al  motor,  consiguiendo  que  los componentes pasen a ser  *simplemente*  datos que se cargan como escenas o *assets*. 
