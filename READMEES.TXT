













                                S e n t r y
                                ===========
                                    V6.4

                           Manual de Instrucciones

                           Copyright (C) 1995-1999
                           Cipher Logic Canada Inc.

                           info@cipherlogic.on.ca

                        http://www.cipherlogic.on.ca




                                S e n t r y
                                ===========
                            Tabla de Contenidos

1.0 Introducci¢n
1.1 Prop¢sito de Sentry
1.1.1 En el Hogar
1.1.2 En un ambiente de Negocios
1.1.3 En un ambiente educativo
1.1.4 General
1.2 Caracter¡sticas de Sentry
1.2.1 General
1.2.2 Fechas de Expiraci¢n
1.2.3 Windows
1.2.4 Protecci¢n de Archivos
1.3 Distribuci¢n de Sentry
2.0 Inicializaci¢n
2.1 Instalando Sentry
2.2 El acceso inicial
2.3 Prioridades Iniciales
2.4 Utilizando los Par metros de Inicializaci¢n
2.5 Desinstalando Sentry
2.6 Instalando Sentry en Maquinas M£ltiples
3.0 Asegurando su computadora
3.1 Pasaporte de BIOS
3.2 Secuencia de Arranque (Boot)
3.3 SWITCHES en CONFIG.SYS
3.4 BootKeys en MSDOS.SYS
3.5 BREAK en CONFIG.SYS
3.6 Pasaportes
3.7 Localizaci¢n en AUTOEXEC.BAT
3.8 Mantenga un respaldo
4.0 Accesando el Sistema
4.1 El Procedimiento de Acceso
4.2 Cambiando Pasaportes
5.0 El Men£ de Super Usuario
5.1 Men£ de Mantenimiento de Usuario
5.1.1 Crear Usuario
5.1.2 Borrar Usuario
5.1.3 Ver Usuarios
5.1.4 Cambiar estado de Super Usuario
5.1.5 Cambiar Fecha de expiraci¢n de Cuenta
5.1.6 Cambiar Fecha de Expiraci¢n de Pasaporte
5.1.7 Cambiar Pasaporte de Cuenta
5.1.8 Asignar M ximo de Accesos Inv lidos
5.1.9 Regresar a Men£ de Super Usuario
5.2 Men£ de Mantenimiento de Archivo de Bit cora
5.2.1 Ver Archivo de Bit cora
5.2.2 Ver Respaldo de Archivo de Bit cora
5.2.3 Mover Archivo de Bit cora al Respaldo
5.2.4 Regresar a Men£ de Super Usuario
5.3 Men£ de Mantenimiento de Sistema
5.3.1 Editar Par metros de Inicializaci¢n
5.3.2 Mandar un Mensaje a un Usuario
5.3.3 Proteger un Archivo
5.3.4 Exportar Par metros de Inicializaci¢n
5.3.5 Auditoria de Seguridad
5.3.6 Modificar Comandos de Shell
5.3.7 Regresar a Men£ de Super Usuario
5.4 Interpretador de Comandos de Sentry
5.5 Acerca de Sentry
5.6 Salir
6.0 Utilizando Sentry Con Windows
6.1 Generales
6.2 Procedimiento de Instalaci¢n
6.3 Windows 95
7.0 Asegurando Otros Programas
7.1 Generales
7.2 Inicializaci¢n
7.3 Informaci¢n de Cuentas
7.4 Usando Machotes
7.5 Ejecutando un Archivo Protegido
7.6 Actualizando un Programa Protegido
8.0 Creando una nueva Instancia de Sentry
9.0 Registro
9.1 Generales
9.2 Beneficios de Registrarse
10.0 Los Par metros de Inicializaci¢n
10.1 Localizaci¢n del Archivo de Bit cora
10.2 Localizaci¢n del Archivo de Copia de Seguridad de la Bit cora
10.3 Localizaci¢n del Archivo de Mensajes
10.4 Largo M¡nimo para Pasaportes
10.5 Largo M ximo para Pasaportes
10.6 M ximo de Accesos Inv lidos
10.7 Espera Forzada Despu‚s de Acceso Invalido
10.8 Tama¤o M ximo de la Bit cora
10.9 Tecla para Cambiar Pasaportes
10.10 Car cter de Mascara de Pasaportes
10.11 D¡as de Validez de un Pasaporte
10.12 D¡as para Expiraci¢n de Cuenta
10.13 Tiempo para Activaci¢n de Protector de Pantalla
10.14 Mensaje del Protector de Pantalla
10.15 L¡nea de Comando de Login
10.16 L¡nea de Comando de Pasaporte
10.17 Mensaje para Pasaporte Equivocado
10.18 Mensaje para Nombre de Usuario Equivocado
10.19 Mensaje para Longitud de Pasaporte Equivocada
10.20 Mensaje para Longitud de Nombre de Usuario Equivocado
10.21 Registro para Pasaporte Equivocado
10.22 Registro para Nombre de Usuario Equivocado
10.23 Registro para Pasaporte Equivocado
10.24 Registro para Longitud de Nombre de Usuario Equivocado
10.25 Variable de Ambiente
10.26 Habilitar Sentry con Windows
10.27 Mostrar Pantalla de Introducci¢n
10.28 Formato de Fechas
10.29 Sensitividad de MAYUSCULAS / min£sculas
10.30 Ventanas en Movimiento
10.31 Habilitar Color
10.32 Color de Texto
10.33 Fondo del Texto
10.34 Color de Texto Resaltado
10.35 Fondo de Texto Resaltado
10.36 M ximo de Accesos Inv lidos
10.37 Tecleado Previo a Ejecuci¢n
10.38 Borrar Pantalla
10.39 Pausa sobre Ultimo Acceso
10.40 Borrado de Seguridad
10.41 Ver Resaltado
10.42 Ver Color Resaltado
10.43 Deshabilitar CTRL-C
11.0 Notas T‚cnicas
11.1 Algoritmo de Codificaci¢n
11.2 Acceso de Super Usuario
11.3 Lista de Empaque
11.4 File_id.diz
11.5 Conversi¢n de Fechas
11.6 Variables de Ambiente
11.7 Programas contra Virus
11.8 Borrado de Archivos
11.9 Informaci¢n General
12.0 Amenazas Potenciales a la Seguridad
12.1 Informaci¢n de Cuentas
12.2 Resquicios en el Equipo
13.0 Resoluci¢n de Problemas
13.1 Mensajes de Error
13.1.1 Imposible localizar Ambiente.
13.1.2 Ambiente Agotado - No Hubo Modificaci¢n.
13.1.3 Error Creando el Respaldo de Bit cora!
13.1.4 Error Creando Bit cora!
13.1.5 Error Creando Archivo Temporal!
13.1.6 Error Abriendo Bit cora!
13.1.7 Error Abriendo Archivo de Mensajes!
13.1.8 Error Abriendo Programa Protegido!
13.1.9 Error Abriendo Sentry.INS!
13.1.10 Error Abriendo Archivos de Sistema!
13.1.11 Error Abriendo Archivo Temporal!
13.1.12 Error Leyendo Segmento de Datos! [Open]
13.1.13 Por favor ejecute INSTALL.EXE.
13.1.14 Error Revisando Archivo Temporal!
13.1.15 Error en Informaci¢n de Cuentas!
13.1.16 Error en Par metros de Inicializaci¢n!
13.1.17 Error Interno de Pantalla. (Lectura)
13.1.18 Error Interno de Pantalla. (Escritura)
13.1.19 Memoria Agotada!
13.1.20 Error de Registro - Programa Abortado!
13.1.21 Esta Cuenta Ha Expirado.
13.1.22 No Existe LICENCIA.TXT!
13.1.23 Los Par metros de Inicializaci¢n son Antiguos!
13.1.24 Los Par metros de Inicializaci¢n son Nuevos!
13.2 Otros problemas
14.0 Limitaci¢n de Responsabilidades
15.0 Informaci¢n para Contactos
16.0 Acerca del Autor
17.0 Cr‚ditos








                                 S e n t r y
                                 ===========
                     Seguridad para los Negocios y el Hogar

1.0 Introducci¢n

Actualmente, casi todos los campos de seguridad por computadora est n
creciendo y avanzando, con muy pocas excepciones. Redes, servidores y
acceso p£blico a sistemas est n estrechando su acceso a fin de evitar
problemas potenciales. Pero, qu‚ hay acerca de la PC? La informaci¢n
contenida en las computadoras es menos valiosa? Con frecuencia no, a£n
no existe un adecuado programa de seguridad para las PC. En mi
b£squeda por seguridad, descubr¡ que las PC fueron virtualmente
ignoradas, y aquellos programas que existieron fueron d‚biles y
deficientes. Ante esta situaci¢n, decid¡ escribir mi propio programa
de seguridad desde la l¡nea de partida, incorporando las m s estrechas
medidas de seguridad posibles, a la vez permitiendo flexibilidad y
facilidad de uso.

Despu‚s de que Sentry es invocado antes de que ninguna red sea
detectada, y antes de un "alto nivel" de sistemas operando as¡ como la
inicializaci¢n de  Windows, Sentry provee absoluta seguridad para
estos programas. Las soluciones de seguridad "en red" son
frecuentemente deficientes ya que los usuarios experimentados pueden
obtener acceso a la red local antes de que las medidas de seguridad
entren en funci¢n.

1.1 Prop¢sito de Sentry

Sentry est  pensado para £nicamente un prop¢sito b sico: impedir el
acceso de la gente no autorizada a la informaci¢n "privada". Sentry es
suficientemente flexible que este £nico prop¢sito puede ser usado en
diferentes formas , por muchas diferentes razones. A continuaci¢n
enumero s¢lo algunas.

1.1.1 En el Hogar

Mucha gente tiene algo en su computadora de casa que considera que es
"sensitiva". Puede ser una carta privada, copias de un e-mail, ¢
informaci¢n financiera. O absolutamente posible, o £nicamente usted
desea guardar un registro de qui‚n est  usando su sistema. Sentry
tiene la soluci¢n para todos esos problemas, mediante el acceso
restringido y registro de todos los intentos para usar el sistema.

Alternativamente, en ocasiones usted £nicamente desea impedir el
acceso de personas no autorizadas por un per¡odo. Esta personas
pudieran ser un compa¤ero metiche, su peque¤o hermano, ¢ su jefe en el
trabajo. En cualquier caso, Sentry impedir  el acceso a todos ellos, a
la vez permitiendo el acceso a un grupo seleccionado de personas.

1.1.2 En un ambiente de Negocios

Los negocios encontrar n que Sentry es invaluable para impedir el
acceso a personas no autorizadas para el uso de las PCs. Con Sentry,
usted puede dejar sus terminales solas, sabiendo que la informaci¢n
que ‚stas contienen est  segura. Infinidad de negocios tienen personal
de limpieza u otros empresarios o contratistas independientes entrando
durante horas inh biles. Muchos negocios tienen PCs en  reas abiertas
donde un "transe£nte" podr¡a usarlas. Muchas terminales se dejan sin
atenci¢n durante un per¡odo en el d¡a (almuerzo, durante una comisi¢n,
durante juntas, etc.). No hay garant¡a de que una persona no
autorizada no intentar  usar sus PCs cuando usted no est‚.

Para negocios que trabajan en grupos, Sentry es perfecto para
conservar un registro de qui‚n uso las PCs y cuando. Los supervisores
podr¡an tener un acceso de Super Usuario en todas las PCs en su grupo,
permiti‚ndoles el acceso para el manejo y control requerido. As¡ mismo
el registro que Sentry guarda podr¡a ser una invaluable herramienta
para determinar qui‚n est  haciendo qu‚ y cuando.

Una vez que un miembro deja el proyecto, simplemente expira o borra su
cuenta para evitar cualquier acceso no autorizado.

1.1.3 En un ambiente educativo

Escuelas e institutos educativos encontrar n que Sentry es muy £til
para limitar el acceso a determinadas terminales. Si por ejemplo,
£nicamente un selecto grupo de personas (personal, administradores, o
una determinada clase) deben tener acceso a espec¡ficas PCs,
simplemente d‚ a cada persona una cuenta. Cualquier persona sin una
cuenta no puede accesar la computadora. Sentry tambi‚n le ayudar  a
tener un registro del uso de la misma, intentos para forzar el acceso,
y cualquier otra actividad sospechosa.

Con frecuencia las terminales en las escuelas se dejan sin
supervisi¢n, sin nada para detener al estudiante de "hurgar
alrededor." Sentry puede actuar como protecci¢n de los curiosos ojos
del cuerpo de estudiantes.

1.1.4 General

Probablemente usted no necesite usar Sentry en su sistema. Quiz  usted
nunca tiene problemas de seguridad de qu‚ preocuparse. Pero la verdad
es que Seguridad no es algo que se pueda tomar como suerte. Hoy en d¡a
esto es un serio problema en la sociedad de la computaci¢n, y muchos
leg¡timos usuarios se encuentran as¡ mismos imposibilitados o
confundidos acerca de las reales consecuencias. Es una l stima  que
algunos inmorales hayan arruinado esto por todos los dem s, pero no
podemos dejarlos entrometerse en el camino de nuestros diarios
negocios. Con las herramientas y el conocimiento apropiados, podemos
combatir mediante el cierre total de las comunes aberturas que los
agresores usan.


1.2 Caracter¡sticas de Sentry

1.2.1 General

Sentry permitir  a usted colocar cuentas dentro de su computadora, una
cuenta para cada persona que usted desee que tenga acceso. Si algunos
no tienen una cuenta, ellos no podr n tener acceso. Esto es simple.
Cada persona tiene su propia cuenta con su propio pasaporte, lo que
facilita a usted conocer qui‚n us¢ la computadora y cu ndo. Ya que
Sentry no usa un pasaporte de "acceso maestro", usted puede cancelar
la cuenta de £nicamente algunos usuarios sin afectar a cualquier otro
usuario.

Sentry registra cada intento de entrada en un archivo de entradas el
cual puede ser revisado por el Super Usuario en cualquier momento.

1.2.2 Fechas de Expiraci¢n

Usted puede colocar cuentas que expiren en un una fecha determinada,
efectivamente quitando el acceso del usuario especificado despu‚s de
la misma. Por ejemplo, si usted sabe que Pepe estar  saliendo en Marzo
14, usted puede colocar su cuenta con la fecha de expiraci¢n de Marzo
15. Esto significa que usted no tiene que recordar que tiene que
borrar la cuenta el d¡a 15... por s¡ sola expirar , y usted puede
borrarla en cualquier momento que usted lo recuerde.

Usted tambi‚n puede colocar fechas de expiraci¢n para los pasaportes,
significando que un usuario tendr  que ingresar un nuevo pasaporte una
vez que su antiguo pasaporte haya expirado. En suma, usted puede
colocar el per¡odo de tiempo permitido a los nuevos pasaportes.

1.2.3 Windows

Sentry puede ser usado en conjunto con Windows para hacer un ambiente
m s seguro. Usted puede proteger su icono del MS-DOS entonces
£nicamente los usuarios con una cuenta pueden entrar a DOS. En suma,
usted puede  ajustar el camino de operaci¢n de Windows para tener
mayor protecci¢n para evitar un borrado accidental o modificaci¢n de
importantes art¡culos.

1.2.4 Protecci¢n de Archivos

En adici¢n para asegurar su PC, Sentry puede asegurar archivos
individuales. Si tiene un programa que usted necesita guardar en su
disco duro, pero usted desea restringirlo de las personas que lo usan,
usted puede simplemente proteger ese archivo con Sentry. Un buen
ejemplo es el programa para FORMATEAR. Este es un comando £til, sin
embargo usted probablemente no desea que se encuentre disponible para
todas las personas. La soluci¢n? Protegerlo con Sentry. Una vez
protegido, £nicamente aquellas personas que usted designe estar n
autorizadas para ejecutar el programa.


1.3 Distribuci¢n de Sentry

Sentry es un programa registrado, aunque la distribuci¢n de la versi¢n
Shareware est  permitida y deseable. La £nica estipulaci¢n  es que
‚sta debe ser sin modificaciones y debe contener todos los archivos
originales (sin ninguna adici¢n). Esencialmente el archivo
SentryXX.zip que usted recibi¢ originalmente es el £nico formato que
puede ser distribuido.

NO distribuya ninguna versi¢n registrada. (al distribuir una versi¢n
registrada est  usted dando copias de un esquema de encriptado
espec¡fico que puede ser usado en perjuicio del usuario registrado - y
solo el usuario registrado!).

2.0 Inicializaci¢n


Ya que est  usted leyendo este documento, se puede presumir que ya ha
desempacado Sentry. Adem s, presumiremos que ha creado un sub
directorio para Sentry y que todos los archivos de ‚ste ya se
encuentran all¡. (Si no es as¡, por favor h galo ahora). Le convendr¡a
leer la secci¢n intitulada "Creando una nueva instancia de Sentry" que
se encuentra m s adelante.



2.1 Instalando Sentry

Lo primero que usted debe hacer es crear una copia de los archivos de
Sentry y mantenerla en un lugar seguro. Copiar estos archivos a un
disco flexible y guardarlos es una buena idea.

A partir de aqu¡, la instalaci¢n es relativamente sencilla. Solamente
ejecute el programa llamado INSTALL.EXE y se le preguntar  en qu‚
directorio desea instalar. Si se trata del directorio actual, usted
puede especificarlo con un punto (.) en la l¡nea de comando. Si teclea
otro directorio, los archivos ser n copiados en ese directorio pero no
ser n borrados del actual; eso lo deber  hacer usted.

Si esta es la primera vez que usted instala Sentry ¢ si lo est 
instalando a partir de cero, se le pedir  alguna informaci¢n de
registro (s¢lo en las versiones registradas). Esta informaci¢n se
encuentra en sus documentos originales ¢ en su aviso de actualizaci¢n,
seg£n aplique.

Si previamente export¢ usted sus par metros de inicializaci¢n, ahora
ser n detectados y se le preguntar  si desea usarlos.

Si no existen par metros exportados, el programa de instalaci¢n
autom ticamente buscar  si su instalaci¢n de Sentry ya tiene
par metros de inicializaci¢n. Si es as¡, se le preguntar  si desea
sobre escribirlos. Teclee "S" si desea sobre escribirlos. Si no
existen par metros de inicializaci¢n, el programa de instalaci¢n
utilizar  autom ticamente los valores por omisi¢n.

A continuaci¢n se le preguntar  si desea modificar sus archivos de
sistema. Si usted responde con "S", su AUTOEXEC.BAT, CONFIG.SYS y
MSDOS.SYS (para Windows 95 solamente) ser n respaldados y modificados.
Esta acci¢n har  que Sentry ejecute autom ticamente la pr¢xima vez que
arranque su m quina.

Finalmente se le preguntar  si desea utilizar Sentry con Windows. Si
usted contesta "S", se le preguntar  la ruta de acceso al directorio
de Windows. Tambi‚n se le har n algunas preguntas sobre seguridad en
Windows. Las opciones elegidas ser n autom ticamente instaladas en
Windows. Si usted desea cambiar cualquier opci¢n, solamente tendr  que
volver a ejecutar el programa de instalaci¢n.

Por favor note usted que el programa de instalaci¢n se borra a si
mismo despu‚s de ejecutar. Esto es para impedir que un usuario normal
lo utilice para entrar a Sentry y cambiar par metros. Est‚ seguro de
mantener una copia del programa de instalaci¢n para el caso de
requerirlo.


2.2 El acceso inicial

Su primer acceso a Sentry debe de ser como Super Usuario. Esto le
permitir  a¤adirse usted mismo como usuario y empezar a ajustar su
instalaci¢n. Es importante que ejecute los siguientes pasos tan pronto
le sea posible, ya que abandonar la cuenta de Sentry es un grave
defecto de seguridad.

Tan pronto como est‚ listo, ejecute Sentry desde la l¡nea de comando
(Tecleando "SENTRY" posicionado en el directorio en que ‚ste se
encuentra). Si aparece alg£n mensaje de error, consulte la secci¢n 13.

Para accesar como Super Usuario, sostenga la tecla CTRL mientras
oprime ENTER despu‚s de haber tecleado en la l¡nea de comando de
acceso "Sentry", sin las comillas. A continuaci¢n utilice el pasaporte
Sentry (sentry ¢ SENTRY no son reconocidos). Tanto los nombres de
acceso como los pasaportes tienen habilitada la sensibilidad de
MAYUSCULAS/min£sculas como valor por omisi¢n, as¡ que recuerde
capitalizar las palabras. Usted puede deshabilitar la sensibilidad de
MAYUSCULAS/min£sculas durante el acceso editando los par metros de
inicializaci¢n pero el pasaporte siempre tendr  habilitada esta
caracter¡stica.

Ahora, en vez de regresar a DOS, ¢ inmediatamente si se siguen las
instrucciones de su Autoexec.BAT, usted entrar  al Men£ de Super
Usuario.

Desde aqu¡, seleccione "1.   Men£ de Mantenimiento de Usuarios". Debe
de existir un nuevo usuario (usted). Aqu¡ deber  usted darse
privilegios de acceso como Super Usuario. Esto se efect£a oprimiendo
la tecla CTRL mientras oprime ENTER despu‚s de teclear su nombre de
usuario. Tambi‚n lo puede hacer utilizando la opci¢n de men£ "Cambiar
Acceso de Super Usuario" para conceder privilegios de Super Usuario.

Vea la secci¢n Men£ de Super Usuario para mayor informaci¢n.


2.3 Prioridades Iniciales

Una vez que ha establecido una cuenta, usted deber  borrar la cuenta
llamada Sentry, de manera que nadie la pueda usar. Esto es muy
importante ya que un intruso potencial probablemente trate de accesar
su sistema utilizando la cuenta por omisi¢n. Al borrarla usted suprime
esa posibilidad.

Sentry no le permitir  borrar al £ltimo Super Usuario, por lo que
usted deber  crear primero otra cuenta con privilegios de Super
Usuario antes de poder borrar la cuenta "Sentry".

A partir de este momento, Usted puede crear otros usuarios en su
sistema y definir sus pasaportes iniciales, fechas de vencimiento y
derechos de acceso. Vea la siguiente secci¢n "Men£ de Super Usuario"
para mayor informaci¢n


2.4 Utilizando los Par metros de Inicializaci¢n

Sentry puede ser configurado a sus necesidades utilizando los
par metros de inicializaci¢n. Estos par metros contienen informaci¢n
que usted puede querer cambiar, permitiendo que Sentry se adecue a
diferentes situaciones.

Usted puede editar los par metros de inicializaci¢n en el Men£ de
Super Usuario. Esto se hace seleccionando la opci¢n "Editar Par metros
de Inicializaci¢n" (vea las secciones 5.10 y 10 para m s detalles).
Cada par metro incluye ayuda en informaci¢n para simplificar las
modificaciones. Cualquier cambio tendr  efecto hasta la pr¢xima vez
que ejecute Sentry.


2.5 Desinstalando Sentry

Sentry es muy simple de desinstalar. Simplemente ejecute el programa
INSTALL.EXE (puede ser que lo tenga que copiar de su respaldo, ya que
se borra a si mismo despu‚s de la instalaci¢n inicial). En la l¡nea de
comando "Ruta de Instalaci¢n", teclee un asterisco "*" para
desinstalar.
 
Entonces se le preguntar  si desea usted remover Sentry de su disco
duro. Si usted responde con un "S", todos los archivos ser n borrados
y el sub directorio  de Sentry ser  removido. A continuaci¢n se le
preguntar  el directorio en que se encuentra Windows. Si usted no
instal¢ Sentry para ejecutar con Windows, teclee un asterisco "*" para
saltar el paso.

Cuando el programa termine su ejecuci¢n, usted ya no tendr  Sentry en
su sistema. Si usted cambia de parecer, lo puede reinstalar cuando lo
desee.


2.6 Instalando Sentry en M quinas M£ltiples

En muchos casos es deseable instalar Sentry en m£ltiples m quinas,
para dar seguridad a un  rea de trabajo completa ¢ a un laboratorio.
En ocasiones el administrador del sistema querr  cuentas ¢ par metros
de instalaci¢n espec¡ficos en cada m quina. Para evadir una
instalaci¢n individual, el proceso descrito abajo puede ser seguido.

1. Ejecute Install.EXE. Coloque un disco flexible en su unidad y
especifique "A:\" como ruta de instalaci¢n.

2. Teclee la localizaci¢n de los archivos de bit cora, respaldo de
bit cora y archivo de mensajes. Si la ruta de acceso va a ser la misma
para todas las m quinas, especif¡quela aqu¡ (ie: C:\Sentry.log, etc.).

3. No actualice sus archivos de sistema y no escoja utilizar Sentry
con Windows ¢ Windows 95.

4. C mbiese al disco flexible (ie: "A:"), y ejecute Sentry.EXE. Accese
el sistema como Sentry, y ajuste las cuentas y par metros de
inicializaci¢n como quiera tenerlos en todas las m quinas.

5. Copie el programa Install.EXE a la unidad A:\. Probablemente tendr 
que hacerlo desde el disco original ¢ el archivo .ZIP, ya que este
programa se borra despu‚s de ejecutarse (ie: "COPY c:INSTALL.EXE
A:\"). Proteja el disco contra escritura para que el programa INSTALL
no sea borrado con cada ejecuci¢n.

6. Ahora lleve el disco a la m quina en la que desea instalar Sentry.

7. C mbiese a la unidad de disco flexible(ie: "A:") y ejecute el
programa de instalaci¢n nuevamente. Proporcione la ruta de acceso
donde quiera instalarlo (ie: "C:\SENTRY"). No sobre escriba los
valores por omisi¢n pero no actualice los archivos de arranque.
Instale Sentry para operarse con Windows o Windows 95 si as¡ lo desea.

8. C mbiese al disco duro (ie: "C:") y ejecute Sentry. Actualice las
cuentas y par metros de inicializaci¢n que sean espec¡ficos para esa
m quina.

9. Repita los pasos 6-8 para cada m quina que se requiera.

Una vez que los pasos est‚n completos, cada m quina en la que Sentry
est‚ instalada tendr  los valores especificados en el paso 5. Esto
puede ahorrarle una considerable cantidad de tiempo cuando se instala
en m£ltiples m quinas..

3.0 Asegurando su computadora
=============================

Sentry es esencialmente inservible a menos que usted tome las
adicionales y apropiadas medidas de seguridad para su m quina. A
continuaci¢n describo algunas de las cosas que usted puede hacer para
incrementar la seguridad de su sistema.


3.1 Pasaporte de BIOS

Proteja su BIOS! Este tiene una construcci¢n en pasaporte, entonces
col¢quelo! Sin el pasaporte, cualquier usuario puede entrar en su BIOS
y cambiar sus instalaciones cr¡ticas del sistema. He visto algunos
tipos diferentes de instalaci¢n de BIOS, pero generalmente, usted usa
el comando CAMBIAR PASAPORTE (algunas veces listado con PASAPORTE DE
SUPERVISOR) desde el men£ principal e instalar la OPCION DE SEGURIDAD
para "Setup" (como contrario a "System") en la pantalla BIOS FEATURES
SETUP. Dependiendo de la conformaci¢n de su BIOS, usted puede tener
una opci¢n correcta en el CHANGE SETUP PASSWORD dentro del men£
principal.


3.2 Secuencia de Arranque (Boot)

Cambie su secuencia de arranque (boot). De nuevo, en su BIOS, debajo
de la pantalla BIOS FEATURES SETUP, instale su secuencia de arranque
(BOOT SEQUENCE) para que ‚ste se efect£e desde su disco duro en
primera instancia. (Esto usualmente significa colocarlo a C,A como
contrario a A,C). Esto impedir  que alguien se brinque la protecci¢n
de Sentry utilizando un disco de arranque en disco flexible (floppy).


3.3 SWITCHES en CONFIG.SYS

Este paso no es requerido para usuarios de Windows 95.

Agregar "switches /n/f" como la primera l¡nea de su archivo
CONFIG.SYS. El par metro /n deshabilitar  las tecleas F8 y F5. F8 le
permite a los usuarios ejecutar los comandos paso por paso en el
CONFIG.SYS y AUTOEXEC.BAT y F5 les da la opci¢n de no ejecutarlos.
Esto significa que los usuarios no podr n utilizar este m‚todo para
brincarse a Sentry. El par metro /f es opcional, solamente agiliza el
proceso de arranque (por aproximadamente 2 segundos).

Esto es ejecutado autom ticamente si usted actualiza su sistema a
trav‚s del programa de instalaci¢n.


3.4 BootKeys en MSDOS.SYS

Este paso es exclusivo para los usuarios de Windows 95.

A¤ada la l¡nea "BootKeys=0" a su MSDOS.SYS. Esto deshabilitar  el uso
de F8, F4 ¢ SHIFT para brincarse el CONFIG.SYS y AUTOEXEC.BAT. A¤adir
esta l¡nea es por tanto, vital, de otra manera los usuarios ser n
capaces de evadir a Sentry con s¢lo oprimir una tecla. Para editar su
MSDOS.SYS, usted puede requerir ejecutar el comando "attrib -h -s
c:\msdos.sys" para hacerlo legible. Cuando haya terminado la edici¢n,
usted tendr  que ejecutar el comando "attrib +h +s c:\msdos.sys"
para regresar el archivo a sus atributos previos.

Esto es ejecutado autom ticamente si usted actualiza su sistema a
trav‚s del programa de instalaci¢n.


3.5 BREAK en CONFIG.SYS

Usted tambi‚n deber  revisar su CONFIG.SYS y si existe un comando
BREAK=ON, b¢rrelo! Este comando permite a los usuarios salirse de la
ejecuci¢n de CONFIG.SYS, lo que es riesgoso! Si el comando existe bajo
el formato BREAK=OFF, est  correcto (‚ste es el valor por omisi¢n de
DOS y es seguro). Pero est‚ seguro de retirar cualquier comando
BREAK=ON.

Esto es ejecutado autom ticamente si usted actualiza su sistema a
trav‚s del programa de instalaci¢n.


3.6 Pasaportes

Escoja un buen pasaporte. Los pasaportes cortos son una mala idea, as¡
como lo son las fechas de cumplea¤os, nombres de c¢nyuges, etc.
Cualquier cosa que sea sencilla de adivinar debe de ser evitada. Los
buenos pasaportes no son palabras sino frases "mnem¢nicas". Por
ejemplo, la frase "yo te voy a esperar" se convertir¡a en "ytvae".
Mezclar letras en may£scula y min£scula as¡ como n£meros incrementa la
seguridad de un pasaporte y los pasaportes de este tipo son
virtualmente imposibles de adivinar o resolver. No escriba usted su
pasaporte mucho menos cerca de su computadora. Trate de memorizarlo si
es posible. Cambie su pasaporte, pero no muy seguido (menos de seis
meses) o no le permitir  memorizarlo y usted tender  a escribirlo lo
cual es un riesgo mayor. No teclee su pasaporte si alguien esta viendo
por encima de su hombro. Si alguien se encuentra en el mismo cuarto,
bloquee la visibilidad desde ese  ngulo o esp‚rese a que se retire.


3.7 Localizaci¢n en AUTOEXEC.BAT

Cuando est  usted instalando Sentry, aseg£rese de que sea el primer
comando en el AUTOEXEC.BAT! de otra manera un usuario puede conseguir
salirse mientras otro programa est  ejecutando y de esta manera evadir
a Sentry por completo!

Esto es ejecutado autom ticamente si usted actualiza su sistema a
trav‚s del programa de instalaci¢n.

3.8 Mantenga un respaldo

Mantenga un respaldo de todos sus archivos de Sentry! Si algo le
sucediera a estos archivos usted puede quedar bloqueado y sin acceso a
su computadora sin este respaldo. Lo mas conveniente es copiar todo el
directorio de Sentry a un disco flexible aproximadamente una vez a la
semana de tal manera de no quedarse corto en su protecci¢n.


4.0 Accesando el Sistema
========================

4.1 El Procedimiento de Acceso

Cuando usted ejecuta por primera vez Sentry, usted debe de ver la
pantalla inicial b sica. Su informaci¢n de registro est  contenida
aqu¡ (la versi¢n Shareware marca como nombre de registro "Shareware").
Usted tambi‚n deber  ver una l¡nea de comando pidi‚ndole que ingrese
su nombre de usuario (Login). Si en vez de esto usted ve un mensaje de
error debe usted de consultar las secciones al fin de este documento
para encontrar ayuda al respecto.

Cuando teclee su nombre de usuario, si usted tiene privilegios de
Super Usuario, usted puede ganar acceso como tal. Usted hace esto
oprimiendo la tecla CTRL mientras oprime la tecla ENTER (CTRL-ENTER).
Si usted no tiene acceso de Super Usuario o no quiere ingresar al
sistema como tal, simplemente oprima ENTER. En cualquiera de los dos
casos esto har  que se le muestre la l¡nea de comando para pasaporte.

Una vez que haya usted llegado a la l¡nea de comando de pasaporte,
simplemente teclee su pasaporte y oprima ENTER al terminar. Su
pasaporte NO ser  mostrado en la pantalla.

El largo m¡nimo y m ximo tanto del nombre de usuario como del
pasaporte son fijados en los par metros de inicializaci¢n. Si usted
desea cambiar estos, deber  hacerlo desde el men£ de Super Usuario.

Despu‚s de teclear correctamente su pasaporte, Sentry buscar  mensajes
dirigidos a usted. Si usted tiene un mensaje esper ndolo, ‚ste ser 
mostrado. Al oprimir la letra "d" el mensaje ser  borrado y "c" lo
contestar . Despu‚s de contestarlo se le preguntar  si desea borrar el
mensaje original. Cada mensaje es desplegado individualmente.
 
A continuaci¢n se desplegar  la fecha y hora de su £ltimo acceso. Si
ha habido alg£n intento inv lido de acceso a su cuenta desde el £ltimo
acceso v lido, esta informaci¢n ser  desplegada. Si el n£mero de
intentos inv lidos a su cuenta ha excedido el m ximo permitido, su
cuenta se encontrar  cancelada hasta que un Super Usuario la
rehabilite.

Si su cuenta ha expirado, se le har  saber y a continuaci¢n quedar 
usted bloqueado. Si su pasaporte ha expirado tambi‚n se lo har  saber
pero se le pedir  que ingrese un nuevo pasaporte. No se le permitir 
reutilizar su pasaporte anterior, y el nuevo pasaporte deber  tener
una longitud correspondiente a los l¡mites indicados en los par metros
de inicializaci¢n. Una vez que usted haya ingresado y verificado su
nuevo pasaporte, le ser  asignada una nueva fecha de expiraci¢n dentro
de los l¡mites determinados en los par metros de inicializaci¢n.

Si usted acces¢ el sistema como Super Usuario y tiene privilegios de
Super Usuario, usted se encontrar  ahora en el men£ de Super Usuario
(vea la siguiente secci¢n). De otra manera usted se encontrar  en la
l¡nea de comando de DOS y el procedimiento de acceso habr  terminado.


4.2 Cambiando Pasaportes

Si usted desea en cualquier momento cambiar su pasaporte usted lo
puede hacer tecleando el c¢digo de cambio. Este c¢digo de cambio est 
definido en los par metros de inicializaci¢n y es mostrado cuando
Sentry arranca. El valor por omisi¢n para el c¢digo de cambio es la
palabra "Passwd". Para cambiar su pasaporte teclee su nombre de
usuario en forma normal y cuando se le pregunte el pasaporte teclee el
c¢digo de cambio. En este momento se le preguntar  el pasaporte actual
(para asegurarse de la validez del usuario), y se le preguntar  su
nuevo pasaporte, el cual, una vez verificado ser  grabado a disco. Su
nuevo pasaporte expirar  dentro del per¡odo designado por los
par metros de inicializaci¢n.

Cambiar su pasaporte no tiene ning£n efecto en los privilegios de
Super Usuario.


5.0 El Men£ de Super Usuario
============================

El men£ de Super Usuario es donde suceden las acciones m s
importantes. Desde aqu¡ es sencillo realizar trabajos de
administraci¢n del sistema y mantener cuentas de usuarios. Las
siguientes opciones est n disponibles en el men£ de Super Usuario:

1. Men£ de Mantenimiento de Usuarios
2. Men£ de Mantenimiento de Archivos de Bit cora
3. Men£ de Mantenimiento de Sistema
4. Interpretador de Comandos de Sentry
5. Acerca de Sentry
6. Salir

Hay combinaciones de teclas que pueden ser usadas para brincar a
cualquier sub-men£ en cualquier momento, ‚stas son:
 
U - Men£ de Mantenimiento de Usuarios
L - Men£ de Mantenimiento de Archivos de Bit cora
S - Men£ de Mantenimiento de Sistema

N¢tese que para evitar conflictos con otras combinaciones, las
disponibles en el men£ son todas may£sculas.

Cada opci¢n en el men£ de Super Usuario se describe a continuaci¢n.


5.1 Men£ de Mantenimiento de Usuario

El Men£ de Mantenimiento de Usuarios contiene todas las acciones que
afectan a los Usuarios. Las siguientes opciones pueden ser accesadas
en este Men£:

1. Crear Usuario
2. Borrar Usuario
3. Revisar Usuarios
4. Modificar derechos de Super Usuario
5. Cambiar Fecha de Expiraci¢n de Cuenta
6. Cambiar Fecha de Expiraci¢n de Pasaporte
7. Cambiar Pasaporte de Cuenta 
8. Asignar M ximo de Accesos Inv lidos
9. Regresar a Men£ de Super Usuario

Cada funci¢n es descrita a continuaci¢n.

5.1.1 Crear Usuario

Esta opci¢n le permite crear Usuario(s) en su Sistema. Antes que nada,
usted debe proporcionar el nombre que desea asignar a ese Usuario. Si
Usted desea crear un Usuario con privilegios de Super Usuario, teclee
el nombre y oprima la tecla CONTROL al tiempo que oprime [ENTER]. Una
vez que ha hecho esto, Sentry le pedir  el Pasaporte. El Usuario debe
escoger y teclear su Pasaporte. Los Super Usuarios no necesitan
conocer estos Pasaportes ya que pueden manejar las cuentas de
cualquier manera. El Pasaporte se captura dos veces para eliminar
errores de tecleado y luego es grabado en forma encriptada. La tecla
ESCAPE abortar  esta operaci¢n en cualquier momento.

Nota: El sistema est  limitado a cien usuarios pero hay una versi¢n
sin restricciones disponible bajo pedido.


5.1.2 Borrar Usuario

La opci¢n de borrar usuarios es muy sencilla. Le presenta una pantalla
de todos los Usuarios, y Usted s¢lo resalta con el cursor el Usuario
que desea borrar. Los Super Usuarios son mostrados con un asterisco
(*) a la derecha de su nombre. Oprima [Enter] para seleccionar el que
desea borrar. Si el Usuario seleccionado es un Super Usuario, Sentry
le advertir  y, sin importar el tipo, si confirma Usted la acci¢n, ese
usuario ser  borrado. Cualquier tecla distinta a "S" NO ejecutar  el
borrado. La tecla ESCAPE abortar  esta operaci¢n en cualquier momento.


5.1.3 Ver Usuarios

Esta acci¢n le permite ver todos los Usuarios con cuentas en su
Sistema. Los Super Usuarios son mostrados con un asterisco(*) junto al
nombre. El £ltimo acceso (Login), d¡a, fecha, cuenta, Fecha de
Expiraci¢n de cuenta y Fecha de Expiraci¢n de Pasaporte son tambi‚n
mostrados a la derecha del nombre del usuario. Adicionalmente, el
n£mero de intentos frustrados desde el £ltimo acceso v lido y el
m ximo de accesos v lidos antes de cancelar la cuenta, son tambi‚n
mostrados. Una "X" en el "Max Inv Log" (m ximo de accesos validos)
significa que no hay limite de accesos inv lidos. Usted puede usar
PAGE UP y PAGE DOWN para navegar por las paginas que pueda haber de
usuarios. Las flechas de cursor tambi‚n estar n disponibles. La tecla
ESCAPE abortar  esta operaci¢n en cualquier momento.

Alguna informaci¢n en la pantalla puede verse resaltada si la opci¢n
de resaltado est  activada. A continuaci¢n est  una lista de la
informaci¢n que es resaltada por Sentry en forma autom tica:

- Super Usuarios 
- Cuentas no usadas recientemente
- Cuentas expiradas
- Pasaportes expirados
- L¡mite m ximo de accesos inv lidos excedido

En cualquier momento, mientras est‚ revisando la lista de usuarios,
usted puede oprimir DEL para borrar el usuario resaltado u oprimir la
tecla INS para insertar un nuevo usuario al final de la lista.

Tendr  uso de las flechas si hay p ginas adicionales arriba ¢ abajo.
La tecla ESC lo lleva de regreso al men£ principal.


5.1.4 Cambiar estado de Super Usuario

Cuando se selecciona esta opci¢n, primero muestra un listado de todos
los usuarios del sistema. Nuevamente los Super Usuarios son marcados
con asterisco (*). Una vez que ha seleccionado un Usuario, Sentry
preguntar  si desea otorgar/retirar privilegios de Super Usuario al
Usuario. Cualquier tecla diferente a "S" NO cambiar  el estado del
Usuario. Ahora el Usuario debe teclear un Pasaporte. (Ya que el estado
de Super Usuario se codifica en el Pasaporte y el Pasaporte no puede
ser decodificado, no es posible cambiar el estado de la cuenta sin
cambiar tambi‚n el Pasaporte).

El Usuario puede usar su anterior Pasaporte o uno nuevo (el anterior
ser  sobrescrito). En el peor escenario el Super Usuario puede
reasignar un nuevo Pasaporte al Usuario si ‚ste no se encuentra
presente para teclear su Pasaporte. (Un Usuario hostil puede perder
los privilegios de Super Usuario sin tener que teclear su Pasaporte;
Usted lo puede hacer por ‚l).


5.1.5 Cambiar Fecha de expiraci¢n de Cuenta

Esta opci¢n le permite definir cuando expira una cuenta en su sistema.
Las cuentas expiradas ya no tienen acceso al sistema. Esta opci¢n es
conveniente cuando un usuario se retira ya que no tienen que acordarse
de dar de baja su cuenta antes de retirarse. Usted puede dejarla
expirar y removerla cuando pueda.

Esta opci¢n trabaja a conjunto con la opci¢n "Asignar M ximo de
Accesos Inv lidos. Una vez que una Cuenta alcanza su m ximo de accesos
inv lidos secuenciales, expira. La £nica manera de reactivarla es
cambiar la Fecha de Expiraci¢n de la Cuenta con esta opci¢n.

Una vez que selecciona esta opci¢n, informaci¢n sobre esta cuenta ser 
mostrada. Si es cuenta de Super Usuario, Sentry se lo har  saber.
Despu‚s le mostrar  la fecha de expiraci¢n actual. Sentry le
preguntar  si desea cambiar la Fecha de Expiraci¢n del Usuario.
Cualquier tecla diferente a "S" NO cambiar  el estado del Usuario, de
otra manera se le preguntar  el a¤o de vencimiento. Este debe ser en 4
d¡gitos (ej: 1997). Si Usted teclea 'N' en el campo de a¤o esta cuenta
ser  permanentemente valida (sin Fecha de Expiraci¢n), Si Usted
proporciona un a¤o v lido se le preguntar  el mes de expiraci¢n en 2
d¡gitos (ej: 06 para Junio) y el d¡a, tambi‚n de 2 d¡gitos. Las
cuentas expiran un segundo despu‚s de entrar al d¡a indicado.


5.1.6 Cambiar Fecha de Expiraci¢n de Pasaporte

Esta opci¢n le permite definir cuando expira el Pasaporte  de un
Usuario. Una vez que este expira, el Usuario debe teclear uno nuevo.
Esto obliga al Usuario a cambiar su Pasaporte. Una vez que un
Pasaporte ha expirado, la siguiente vez que el Usuario accese, ser 
obligado a teclear un nuevo Pasaporte. El nuevo Pasaporte es v lido
por el n£mero de d¡as especificado en los Par metros de
Inicializaci¢n. Una vez que el Pasaporte ha expirado, el Usuario no
puede usarlo otra vez y debe seleccionar uno nuevo. (NOTA: Sentry no
mantiene registro hist¢rico de Pasaportes, as¡ que un Usuario puede
alternar dos pasaportes sin problemas. Esta no es una pr ctica segura
y debe ser evitada).

Una vez que selecciona esta opci¢n, informaci¢n sobre esta cuenta ser 
mostrada. Si es cuenta de Super Usuario, Sentry se lo har  saber.
Despu‚s le mostrar  la fecha de expiraci¢n del Pasaporte. Sentry le
preguntar  si desea cambiar la Fecha de Expiraci¢n del Pasaporte.
Cualquier tecla diferente a "S" NO cambiar  el estado del Usuario, de
otra manera se le preguntar  el a¤o de vencimiento. Este debe ser en 4
d¡gitos (ej: 1997). Si Usted teclea 'N' en el campo de a¤o esta cuenta
ser  permanentemente v lida (sin Fecha de Expiraci¢n), Si Usted
proporciona un a¤o valido se le preguntar  el mes de expiraci¢n en 2
d¡gitos (ej: 06 para Junio) y el d¡a, tambi‚n de 2 d¡gitos. Los
pasaportes expiran un segundo despu‚s de entrar al d¡a indicado.


5.1.7 Cambiar Pasaporte de Cuenta

Esta opci¢n permite al Super Usuario cambiar el Pasaporte de una
cuenta, en caso que el Usuario lo olvide ¢ alguna otra cosa extra¤a
haya pasado. Al asignar un nuevo Pasaporte a una cuenta, Usted debe
especificarle una Fecha de Expiraci¢n  inmediata para forzar al
Usuario a escoger uno nuevo. Si el Pasaporte previo no ten¡a Fecha de
Expiraci¢n, ninguna ser  asignada al nuevo Pasaporte. De otra forma el
Pasaporte expira en el n£mero de d¡as asignado en los Par metros de
Inicializaci¢n. La tecla ESCAPE abortar  esta operaci¢n en cualquier
momento.


5.1.8 Asignar M ximo de Accesos Inv lidos

Esto le permite establecer el n£mero M ximo de Accesos Inv lidos
permitido antes que una Cuenta sea deshabilitada. El valor por omisi¢n
se define en los Par metros de Inicializaci¢n , y es asignado a todas
las cuentas cuando son usadas por primera vez.

Para asignar un nuevo m ximo, simplemente seleccione "Asignar M ximos
Accesos Inv lidos en el men£ de Super Usuario. All¡ se le mostrar  la
lista de Usuarios y se le pedir  que seleccione el Usuario que desea
cambiar. La tecla ESCAPE abortar  esta operaci¢n en cualquier momento.

Una vez que seleccione al Usuario, Se le informar  en caso que ese
Usuario sea un Super Usuario.

NOTA: Usted NO debe asignar un m ximo de Accesos Inv lidos a la £ltima
cuenta de Super Usuario en el sistema. Si lo hace y alguien intenta
entrar en esa cuenta, Usted podr¡a quedar bloqueado fuera del men£ de
Super Usuario!

A continuaci¢n se le dir  cu l es el m ximo de ese Usuario y si desea
Usted cambiarlo. Cualquier tecla distinta a "S" abortar  la operaci¢n.
Ahora se le preguntar  el n£mero m ximo de accesos inv lidos antes de
que una cuenta sea deshabilitada. Teclear "N" o cero (0) har  el
n£mero ilimitado.

Est‚ consciente que un n£mero menor a 10 le causar  demasiados
problemas. Gastar¡a Usted mucho tiempo rehabilitando cuentas de gente
poco cuidadosa. Considere el asunto cuidadosamente. Adem s est‚
consciente que cuando se cancela el acceso de una cuenta, lo que se
est  haciendo realmente es hacerla expirar de inmediato y si la desea
reactivar, tendr  Usted que cambiar la Fecha de Expiraci¢n. Esto es
conveniente para saber cuando fue que la cuenta fue realmente
cancelada ya que la Fecha de Expiraci¢n ser  la del d¡a que fue
cancelada.

Cada vez que hay un acceso v lido a una cuenta, el contador de accesos
inv lidos es regresado a cero. Esto quiere decir que una Cuenta  no
ser  cancelada si hay un acceso v lido antes de que se alcance el
l¡mite de accesos inv lidos. (Por ejemplo, digamos que una Cuenta
tiene un m ximo de 10 accesos inv lidos. Si hay 7 accesos inv lidos
antes de un v lido y luego 5 inv lidos m s, la cuenta no ser 
cancelada. Deben ser 10 accesos inv lidos secuenciales los que ocurran
antes de que la cuenta sea cancelada).

Una vez que haya realizado los cambios, Usted puede revisar la lista
de Usuarios para asegurarse que todo sea aceptable.


5.1.9 Regresar a Men£ de Super Usuario

Esta opci¢n sencillamente lo regresa al Men£ de Super Usuario men£. Es
lo mismo que teclear ESCAPE.


5.2 Men£ de Mantenimiento de Archivo de Bit cora

El Men£ de Mantenimiento de Archivo de Bit cora contiene todas las
acciones requeridas para el manejo del Archivo de Bit cora. Las
siguientes opciones pueden ser accesadas en este Men£:

1. Revisar Archivo de Bit cora
2. Revisar Respaldo de Bit cora
3. Mover Archivo de Bit cora al Respaldo
4. Regresar a Men£ de Super Usuario

Cada funci¢n es descrita a continuaci¢n.


5.2.1 Ver Archivo de Bit cora

Cada vez que un Usuario accesa el sistema, un registro es escrito a
disco. Si Usted desea ver el registro en l¡nea, seleccione esta
opci¢n. Se le preguntar  si desea ver el Archivo de Bit cora para uno
¢ varios Usuarios. Teclear "u" (Un Usuario ) lo llevar  al listado de
Usuarios, donde puede seleccionar el Usuario que desee. Cualquier otra
tecla le mostrar  todos los Usuarios.

El Archivo de Bit cora ser  mostrado pantalla por pantalla y Usted
puede oprimir ESCAPE en cualquier momento para ir al final del
archivo. Una vez que todo el Archivo de Bit cora ha sido mostrado,
Sentry le preguntar  si desea borrarlo. Si Usted estaba revisando un
solo Usuario, Sentry le preguntar  si desea borrar la informaci¢n de
bit cora de ese Usuario.

Cualquier tecla distinta a "S" lo sacar  de la opci¢n dejando el
Archivo de Bit cora intacto. Si Usted teclea un "S", Sentry borrar 
todos los registros. Si Usted est  viendo la bit cora de todos los
Usuarios, todos los registros ser n borrados. Si est  viendo la
bit cora para un solo Usuario, solamente los registros de ese Usuario
ser n borrados.

El Archivo de Bit cora por s¡ mismo no ocupa mucho espacio en disco y
por tanto deber¡a ser mantenido como registro hist¢rico. Usted puede
necesitar referirse al Archivo de Bit cora para verificar algunos
eventos. Si el espacio en disco es un problema, Usted puede usar la
opci¢n "Mover Archivo a Respaldo" descrita m s adelante.

Usted debe siempre revisar el Archivo de Bit cora, ya que ‚ste le dir 
si hay alg£n problema en su sistema. Todos los mensajes de error son
guardados en la bit cora y esto le dir  si Sentry ha encontrado
algunos problemas. Adem s, registra la hora y el nombre del Usuario
tratando de accesar. Esto le permite identificar ataques potenciales
al sistema. El archivo de bit cora est  escondido por Sentry, pero
Usted tambi‚n deber¡a ponerlo donde est‚ a salvo de manipulaci¢n por
los Usuarios. Usted puede establecer su localizaci¢n en Par metros de
Inicializaci¢n.


5.2.2 Ver Respaldo de Archivo de Bit cora

Esta opci¢n es igual a Ver Archivo de Bit cora salvo que le permite
revisar la informaci¢n que ha respaldado. Esto es con prop¢sitos
estrictamente hist¢ricos para no perder la informaci¢n del Archivo de
Bit cora.


5.2.3 Mover Archivo de Bit cora al Respaldo

Esta opci¢n mueve la informaci¢n del Archivo de Bit cora al Archivo de
Respaldo. El Archivo de Respaldo no es sobrescrito, la informaci¢n es
a¤adida al final de ‚ste. Esto lo hace mas f cil de manejar cuando el
Archivo de Bit cora empieza a estar muy grande pero Usted no quiere
borrarlo.


5.2.4 Regresar a Men£ de Super Usuario

Esta opci¢n simplemente lo regresa al men£ de Super Usuario. Es lo
mismo que oprimir la tecla ESC.


5.3 Men£ de Mantenimiento de Sistema

El Men£ de Mantenimiento de Sistema contiene funciones que permiten al
Super Usuario realizar funciones especiales o relativas al Sistema.
Las siguientes opciones pueden ser accesadas en este Men£:

1. Editar Par metros de Inicializaci¢n 
2. Mandar un Mensaje a un Usuario 
3. Proteger un Archivo
4. Exportar Par metros de Inicializaci¢n 
5. Realizar Auditoria de Seguridad 
6. Modificar Comandos del Shell 
7. Regresar a Men£ de Super Usuario

Cada funci¢n es descrita a continuaci¢n.

5.3.1 Editar Par metros de Inicializaci¢n

Esta opci¢n le permite editar los Par metros de Inicializaci¢n.

Despu‚s de la instalaci¢n, es cr¡tico que Usted revise cada atributo,
y se asegure de que estos se conformen a sus deseos. Muchos de los
Par metros de Inicializaci¢n  tienen serias implicaciones de
seguridad. Una vez que esta opci¢n es seleccionada, todos los
atributos son mostrados. Simplemente seleccione el atributo que desee
modificar y la siguiente informaci¢n ser  mostrada:

- Una l¡nea de descripci¢n del atributo.
- Una corta descripci¢n del atributo y sus usos.
- Valores v lidos para el atributo, si existen.
- Notas sobre seguridad, si existen.
- El valor por omisi¢n del atributo.
- El valor actual del atributo.

En este momento se le preguntar  cu l es el nuevo valor para el
atributo. Oprimir ENTER en una l¡nea en blanco ¢ oprimir la tecla ESC
aborta cualquier cambio al valor.

Sentry revisa estrictamente los valores que Usted proporcione y no
guardar  ning£n valor invalido.

Lea la Secci¢n 10 del Manual de Usuario para ver detallas de los
valores individuales.


5.3.2 Mandar un Mensaje a un Usuario

Esta opci¢n permite al Super Usuario mandar un mensaje de una l¡nea a
cualquier Usuario del Sistema (ellos mismos incluidos). Una vez que
esta opci¢n es seleccionada, Usted debe escoger el Usuario al que le
mandar  el mensaje. Esto se hace desde la lista de Usuarios. Una vez
hecho esto, se le preguntar  cu l es el mensaje. Si desea Usted mandar
m s de una l¡nea, deber  mandar dos ¢ mas mensajes al mismo Usuario.

Una vez escrito su mensaje, se le regresar  al men£ de Super Usuario.
En el siguiente acceso de esa persona, su mensaje ser  mostrado,
incluyendo:

- Qui‚n manda el mensaje 
- Fecha y Hora en que se mand¢
- El mensaje

El Usuario tiene ahora la opci¢n de borrar el mensaje. Si no lo borra,
este ser  mostrado nuevamente en su siguiente acceso.

NOTA: Los Mensajes son mostrados antes de cualquier informaci¢n de
Login. De esta manera puede Usted mandarle mensajes a personas cuyas
cuentas han sido canceladas. As¡, si lo desea, puede darles una
explicaci¢n sobre la cancelaci¢n.


5.3.3 Proteger un Archivo

Esta opci¢n le permite proteger archivos ejecutables (.EXE, .COM y
.BAT). Cuando esta opci¢n es seleccionada, le pide el nombre del
archivo. Usted debe proporcionar la ruta de acceso v lida y el archivo
debe de ser ejecutable. Si el nombre del archivo es correcto, Sentry
procesa el archivo y lo "protege". La protecci¢n significa que la
siguiente vez que el archivo sea ejecutado, Sentry tambi‚n ser 
ejecutado. Si el Usuario teclea un nombre y pasaporte v lido, el
programa protegido se ejecutar . De otra manera, no ejecutar .

Aseg£rese de hacer un respaldo de cualquier archivo que Usted proteja
ya que no hay manera de echar atr s esta protecci¢n - es permanente!

Esto es £til para proteger programas individuales. Si una persona
logr¢ entrar en su sistema, ya tiene manos libres para todo lo que hay
en ‚l. Esta opci¢n le permite reducir acceso a programas individuales.

El m‚todo de protecci¢n actualmente usado no funciona con todos los
programas. Se han hecho pruebas con algunos que no funcionan
correctamente una vez protegidos (aparentemente problemas de memoria ¢
de v¡deo). Actualmente hay una p‚rdida de memoria disponible bastante
significativa con respecto al programa original. Adem s, la protecci¢n
de programas de Windows no funciona actualmente).

Lea la Secci¢n 7 para detalles espec¡ficos sobre protecci¢n de
programas.


5.3.4 Exportar Par metros de Inicializaci¢n

Seleccionar esta opci¢n exportar  los Par metros de Inicializaci¢n.
Esto le permitir  usar los mismos par metros y estructura de cuentas
cuando mejore su versi¢n. Este proceso es sencillo. Seleccione esta
opci¢n y los par metros ser n exportados. Ahora simplemente
descomprima el nuevo Sentryxx.zip en su directorio y corra el programa
install.exe. Install encontrar  autom ticamente la informaci¢n
exportada y le preguntar  si desea usted usarla. Si su respuesta es
afirmativa, los par metros ser n autom ticamente actualizados en la
nueva versi¢n y cargados.

Por favor tome nota: No debe usted exportar los par metros a menos que
tenga usted la intenci¢n de importarlos de inmediato a una nueva
versi¢n (esto podr¡a causar un riesgo de seguridad).


5.3.5 Auditor¡a de Seguridad

Esta es una de las opciones m s potentes de Sentry. Al seleccionar
esta opci¢n usted har  que Sentry autom ticamente busque debilidades
en su sistema. Esta auditor¡a se efect£a b sicamente en tres  reas:

- Su Sistema 
- Sus Par metros de Inicializaci¢n 
- Su Estructura de Cuentas

Conforme cada una de estas secciones es probada, el usuario ser 
informado por Sentry sobre la detecci¢n. Si una secci¢n no tiene
debilidades, entonces un "OK" ser  mostrado. De otra manera, Sentry
describir  la debilidad y le preguntar  si desea usted corregirla.
Oprimir "S" provocar  la correcci¢n autom tica del problema o le
pedir  que teclee un nuevo valor, dependiendo de la situaci¢n.

En cada secci¢n, los siguientes puntos ser n checados durante una
auditor¡a:

    Sistema 

    An lisis de los siguientes puntos:
- no existe l¡nea "switches" en CONFIG.SYS (fuera de Win95 solamente)
- no hay comando "BootKeys" en MSDOS.SYS (Win 95 solamente)
- no existe llamada a Sentry en el AUTOEXEC.BAT 
- existe un comando "break on" en CONFIG.SYS 

    Par metros de Inicializaci¢n 

 An lisis de los siguientes puntos: 
- un largo de pasaporte muy corto o muy largo
- un n£mero muy alto para m ximo de accesos inv lidos
- un valor bajo para espera forzada 
- despliegue de Pasaporte debe ser enmascarado o deshabilitado 
- La Fecha de Expiraci¢n de Pasaporte es de m s de 365 d¡as 
- Una Fecha de Expiraci¢n de Cuenta no usada de m s de 365 d¡as 
- Una espera de m s de 600 segundos para el protector de pantalla
- Sensibilidad de MAYUSCULAS / min£sculas deshabilitada 

    Cuentas

    Buscar lo siguiente:
- Cuentas que han expirado 
- Cuentas de Super Usuario con un par metro de accesos inv lidos habilitado 
- Cuentas normales con un par metro de accesos inv lidos deshabilitado 
- Cuentas donde excede el n£mero de intentos de acceso inv lido 
- Cuentas sin Fecha de Expiraci¢n 
- Pasaportes sin Fecha de Expiraci¢n 

Como un Super Usuario, usted debe ejecutar la auditor¡a con
frecuencia. Si todo marcha como debe, ‚sta se terminar  en unos
cuantos segundos y le alertar  a problemas potenciales o actividad
sospechosa de la que de otra manera usted no estar¡a consciente.

El mensaje "Auditor¡a Terminada", aparecer  cuando se haya terminado
‚sta. En este momento el usuario deber  oprimir cualquier tecla para
regresar al men£ de Super Usuarios.


5.3.6 Modificar Comandos de Shell

Esta opci¢n le permite a un Super Usuario controlar los comandos que
est n disponibles para el Usuario en el DOS prompt. Esta opci¢n puede
ser invaluable cuando se implementa un plan total de seguridad.

Para empezar, se le pregunta al Super Usuario la localizaci¢n del
interpretador de comandos. Este generalmente se encuentra en el
directorio ra¡z (C:\) o en el directorio (C:\DOS) para instalaciones
normales de DOS. O en el directorio (C:\Windows) para usuarios de
Windows 95. Sentry utilizar  la ruta de acceso que se encuentra en la
variable de ambiente COMSPEC como el valor por omisi¢n, haciendo m s
f cil para usted encontrar el archivo correcto.

Una vez que se teclee la localizaci¢n del interpretador de comandos,
Sentry lo revisa intentando descubrir los comandos que ‚ste controla.
Si Sentry no puede encontrar comandos validos, le informar  al Super
Usuario y nada ser  modificado.

Si Sentry puede localizar algunos comandos, estos ser n desplegados en
un formato de men£. En este momento el usuario puede deshabilitar o
editar cualquiera de los comandos mostrados.

NOTA: Se sugiere enf ticamente que se cree un disco de arranque antes
de intentar cualquier cambio a su interpretador de comandos. A£n
cuando Sentry ha sido probado con ‚xito con varios interpretadores de
comandos (como DOS 6.22, Windows 95 y Norton DOS), puede actuar en una
forma inconsistente si encuentra un formato desconocido.

Para deshabilitar un comando, sencillamente oprima una vez la tecla
"d". Si se oprime "d" nuevamente el comando ser  rehabilitado. Para
editar un comando oprima la tecla "e", y se le preguntar  cu l es el
nuevo comando.

OTRA NOTA: Es muy aconsejable que el nombre del nuevo comando tenga el
mismo tama¤o que el anterior. Cambiar el largo del nombre de un
comando puede tener resultados impredecibles y es m s f cil que no
funcione.

En el men£, los comandos que han sido deshabilitados son marcados con
una "x", los comandos que han sido editados son marcados con un "*" y
los comandos que no han sido modificados son marcados con un "- ".

Una vez que todos los cambios han sido efectuados, simplemente oprima
Enter. Todos los cambios ser n sumarizados para verificar que no se
hayan cometido errores. En este momento el Super Usuario debe
asegurarse que todos los cambios est‚n correctos y proceder a
aceptarlos o rechazarlos.

Si los cambios son aceptados, Sentry ejecutar  el interpretador de
comandos modificado antes de reemplazar el original por el modificado.
Esto quiere decir que si hay alg£n problema, usted puede descartar los
cambios, y empezar otra vez.

Cuando el nuevo interpretador sea ejecutado, pru‚belo exhaustivamente.
No realice operaciones grandes o complicadas ni corra programas muy
grandes ya que esto puede desestabilizar el proceso. Una vez que est‚
satisfecho teclee "EXIT" para regresar al men£ de Sentry, donde se le
preguntar  si tuvo alg£n problema.

Si usted contesta "N" a esta pregunta, su interpretador de comandos
ser  reemplazado por el modificado, haciendo sus cambios permanentes.
Oprimir cualquier otra tecla descartar  estos cambios.

UNA NOTA FINAL: Se sugiere mantener una copia "limpia" de su
COMMAND.COM en alg£n lugar seguro ya que podr¡a requerirla m s tarde.
Muchos de los cambios que usted haga a trav‚s de Sentry tambi‚n pueden
ser deshechos, pero es mucho m s seguro simplemente copiar su original
del respaldo. Mientras m s veces modifique usted su interpretador de
comandos, m s oportunidades hay de que algo salga mal.


5.3.7 Regresar a Men£ de Super Usuario

Esta opci¢n sencillamente lo regresa al men£ de Super Usuario. Es lo
mismo que oprimir la tecla ESC.


5.4 Interpretador de Comandos de Sentry

Seleccionar esta opci¢n le llevar  temporalmente a una l¡nea de
comando de DOS donde puede ejecutar cualquiera de los comandos
normales del sistema operativo. Este Shell tiene memoria y ambientes
limitados, por lo que s¢lo debe ser usado en forma b sica y se debe
evitar ejecutar programas muy grandes ¢ complicados.

Oprima "EXIT" para regresar al Men£ de Super Usuario.


5.5 Acerca de Sentry


Esta opci¢n simplemente le muestra informaci¢n interesante ¢ £til
sobre Sentry.


5.6 Salir

Esta opci¢n simplemente le regresa a la l¡nea de comando. Tiene
exactamente la misma funci¢n que oprimir la tecla ESCAPE.


6.0 Utilizando Sentry Con Windows
=================================

6.1 Generales

Sentry tambi‚n es adaptable a Windows, permiti‚ndole mantener a sus
usuarios lejos de DOS. Esto puede ser deseable si se ingresa a Windows
durante el arranque (en su AUTOEXEC.BAT existe un comando "win"). Si
usted quiere limitar el acceso a su sistema en general usted puede
instalar Sentry en la forma normal.  Esto mantendr¡a a usuarios no
deseados bloqueados fuera de su sistema. Si usted adem s quiere
limitar el acceso a la l¡nea de comando de DOS desde Windows, usted
tambi‚n puede hacerlo. Todo lo que se requiere es crear una nueva
instancia de Sentry (vea siguiente secci¢n) y luego simplemente
instruir a Windows para ejecutar Sentry antes del acceso a DOS. El
siguiente ejemplo asume que usted ha instalado una instancia de Sentry
en C:\Sentry\Inst1, pero usted puede sustituir los nombres de estos
directorios por aquellos que realmente est‚n en uso en su sistema.


6.2 Procedimiento de Instalaci¢n

Instalar Sentry en el ambiente de Windows es sencillo. Incluidos en el
paquete de Sentry encontrar  usted dos archivos:

Sentry.grp
Sentry.pif

Ambos ser n copiados a su directorio de Windows durante su
instalaci¢n. Ingrese a Windows y desde el manejador de programas
(Program Manager), seleccione archivo (file), nuevo (new), a
continuaci¢n seleccione grupo de programas (program group). Cuando se
le pregunte teclee "Sentry" como nombre y descripci¢n del grupo. Ahora
debe usted de tener un nuevo grupo de programas llamado Sentry. Este
grupo de programas debe de contener un solo icono, etiquetado MS-DOS.
Este icono realmente ejecuta Sentry.PIF, el cual contiene informaci¢n
espec¡fica para la ejecuci¢n de Sentry.

Usted puede editar el nuevo icono (esc¢jalo y oprima ALT-ENTER) y
cambiar el directorio de trabajo o ruta de acceso hacia sus archivos
de Sentry.

Ej: c:\Sentry, o c:\Sentry\Inst1, etc.

Ahora ejecute el Editor de PIFs (el icono es una peque¤a etiqueta), y
abra Sentry.PIF. Ahora cambie el nombre de archivo de manera de
indicar su Sentry.exe

Ej: c:\Sentry\Sentry.exe, o c:\Sentry\Inst1\Sentry.exe, etc.

Adicionalmente, cambie el directorio de trabajo para que quede igual
al directorio de trabajo para el icono (vea arriba). Una vez que grabe
el archivo .PIF usted ha terminado.

En este momento usted deber  probar el nuevo icono de Sentry para
asegurarse de que funciona. Cuando usted presiona doble-click sobre el
icono, usted deber  encontrarse directamente en Sentry. Una vez que
usted haya proporcionado nombre de usuario y pasaporte correctos,
usted se encontrar  en un Shell normal de DOS. Usted puede teclear
"exit" para regresar a Windows en cualquier momento.

Una vez que est‚ seguro de que funciona, borre usted su antiguo icono
de MS-DOS, de tal manera que los usuarios no puedan utilizarlo para
salir directamente a la l¡nea de comandos de DOS. Usted puede
arrastrar su nuevo icono a la misma localizaci¢n que ten¡a el antiguo
de manera que todo parezca igual.

Ahora hay un £ltimo paso. Si un usuario saliera de Windows, se
encontrar¡a en la l¡nea de comando de DOS, que no es lo que queremos.
Dado que su AUTOEXEC.BAT est  ejecutando Windows durante el arranque,
usted puede bloquear la salida de los usuarios oblig ndolos a salir a
trav‚s de Sentry. Usted puede hacer esto a¤adiendo una llamada a
Sentry despu‚s del comando win en su AUTOEXEC.BAT

Por ejemplo, las ultimas l¡neas de su AUTOEXEC.BAT se ver¡an as¡:

----------------- CORTE ----------------
win
\Sentry\Inst1\Sentry
----------------- CORTE ----------------

Alternativamente, usted puede a¤adir las medidas de seguridad
ofrecidas por el programa  de instalaci¢n.

Si esto le parece un procedimiento complicado, trate de efectuar los
pasos uno por uno y aseg£rese de que todo funcione correctamente. El
resultado final debe de ser que, si usted acciona el icono de MS-DOS,
se ejecute Sentry antes de que el usuario llegue a la l¡nea de
comando. Esto quiere decir que usted puede limitar el acceso al
sistema operativo sin tener que hacer maravillas en Windows. Ya que
Usted ha creado una nueva instancia de Sentry, usted puede tener una
instancia ejecutando cuando arranca (dando acceso a Windows) y tener
otra instancia ejecutando cuando usted acciona el icono de MS-DOS
(dando acceso al sistema operativo). De esta forma, un usuario que
tiene acceso a su PC puede no tener la capacidad de accesar el sistema
operativo.

Est‚ usted consciente que Sentry bloquear  la terminal si un usuario
falla en accesar correctamente. Si esto sucede en Windows, usted puede
recuperarse de regreso a Windows oprimiendo CTRL-ALT-DELETE y cerrando
la ventana de DOS. Esto no le dar  acceso a DOS pero al menos no
perder  nada de su trabajo en Windows.


6.3 Windows 95

Sentry es f cilmente adaptable a usar en un ambiente de Windows 95. En
gran parte, el proceso es el mismo que para una instalaci¢n de DOS /
Windows 3.11.

La diferencia primaria con Windows 95 es que, en vez de a¤adir la
l¡nea "switches /n/f" a su CONFIG.SYS, usted debe a¤adir la siguiente
l¡nea a su MSDOS.SYS:

BootKeys=0

Esto deshabilitar  el uso de F8, F4 o SHIFT para brincarse sus
archivos CONFIG.SYS y AUTOEXEC.BAT. A¤adir esta l¡nea es, por tanto,
obligatorio. De otra manera los usuarios ser n capaces de evadir a
Sentry con s¢lo oprimir una tecla. Para editar su MSDOS.SYS usted
puede requerir ejecutar el comando "attrib -h - s c:\msdos.sys" para
hacerlo legible. Cuando haya terminado la edici¢n, usted tendr  que
ejecutar el comando "attrib +h +s c:\msdos.sys"   para regresar el
archivo a sus atributos previos.

Como se dijo anteriormente, aseg£rese de llamar Sentry al principio de
su AUTOEXEC.BAT. El archivo Sentry.PIF y Sentry.GRP funcionar n
perfectamente con Windows 95 a£n cuando, hasta este momento, no se han
escrito instrucciones espec¡ficas para su instalaci¢n.

A£n no se efect£an pruebas exhaustivas en el ambiente de Windows 95
pero ‚stas aparecer n en una revisi¢n futura de Sentry.


7.0 Asegurando Otros Programas
==============================

7.1 Generales

En algunos casos puede ser ben‚fico el asegurar un solo programa. Este
puede ser un procesador de textos, Windows, ¢ un programa
potencialmente peligroso, como Format.COM. En cualquier caso, usted
puede asegurarlo con Sentry a£n si usted no usa Sentry durante el
arranque.


7.2 Inicializaci¢n

Para tener ‚xito al proteger un programa, usted debe realizar una
copia de respaldo (Sentry no puede revertir el proceso de protecci¢n
de un programa!). Este respaldo no debe estar en ning£n lugar
accesible (haga una copia en un disco flexible y gu rdela en un lugar
seguro). Despu‚s de todo, si un usuario puede ejecutar una versi¢n no
protegida del programa, para que nos preocupamos de protegerla? Es
conveniente probar el programa protegido para asegurarse de que
funcione correctamente.

Para proteger un archivo, sencillamente escoja "Proteger un Archivo"
en el men£ de Super Usuario. Sentry le preguntar  el nombre del
archivo a proteger. Este archivo debe de ser ejecutable (ej: con
terminaci¢n .EXE, .COM ¢ .BAT). Los archivos BATCH son autom ticamente
convertidos en .EXEs. Una vez que usted ha proporcionado un nombre
v lido, Sentry le preguntar  si se trata de un programa de Windows ¢
de DOS. Oprima la letra "W" para Windows y "D" para DOS (son programas
de Windows aquellos que s¢lo ejecutan dentro del ambiente Windows, un
programa de DOS es aqu‚l que usualmente se ejecuta dentro de ese
ambiente).

Sentry NO puede proteger programas basados en Windows 3.x aunque puede
perfectamente proteger todos los programas de Windows (tanto 16 como
32-bit) en Windows 95.

Ahora Sentry proceder  a proteger el archivo. Cuando termine, usted
ser  devuelto al Men£ de Super Usuario. Su programa ahora se encuentra
protegido!

Las aplicaciones para este tipo de protecci¢n son casi ilimitadas.
Utilice su imaginaci¢n y si tiene usted alguna idea imaginativa, nos
interesar¡a mucho o¡r al respecto.


7.3 Informaci¢n de Cuentas

La estructura de cuentas para un archivo protegido es copiada de la
versi¢n de Sentry usada para proteger el archivo pero es £nica. Esto
es, una vez que el programa ha sido protegido, un Super Usuario puede
a¤adir / borrar / modificar cualquier cuenta para ese archivo
protegido sin afectar ninguna otra copia de Sentry. Los par metros de
inicializaci¢n son tratados del mismo modo. Cada programa protegido
tiene su copia £nica e individual.

Para cambiar la informaci¢n de cuentas de un archivo protegido,
sencillamente ejec£telo y cuando Sentry se ejecute, acc‚selo como
Super Usuario. Ahora puede ejecutar todas las operaciones de un Super
Usuario en la forma normal.


7.4 Usando Machotes

Es posible establecer instancias "machote" de Sentry para ser usadas
en la protecci¢n de programas. Esto puede ser sumamente £til ya que le
ahorra al administrador un monto considerable de tiempo y reduce las
posibilidades de cometer errores.

Para usar machotes, usted debe crear varias instancias de Sentry (una
para cada machote que desee usar). Vea la secci¢n 8 para instrucciones
de creaci¢n de instancias de Sentry.

Un ejemplo muestra ser¡a:

c:\Sentry
|
+----+------- Privado
|
+------- P£blico
|
+------- SemiPub

Cada una de las instancias mostradas arriba contiene una copia
completa de Sentry. Ahora s¢lo modifique la estructura de cuentas de
cada instancia para crear su machote. Esto es, la instancia Privado
contendr¡a s¢lo a los Super Usuarios, la instancia P£blico puede
contener a todos los usuarios y la SemiPub contendr¡a a los Super
Usuarios y algunos usuarios. Los machotes pueden ser creados para
ajustarse a las necesidades de su instalaci¢n espec¡fica.

Ahora usted utilizar¡a la instancia Privado como machote para proteger
ejecutables exclusivos, como FORMAT.COM. Cuando utiliza usted la
instancia Privado, el programa protegido es autom ticamente modificado
para s¢lo aceptar la ejecuci¢n por parte de los Super Usuarios.

De la misma manera, el machote SemiPub puede ser usado en programas
que s¢lo los Super Usuarios y un n£mero selecto de usuarios est‚n
autorizados a usar.

La ventaja de utilizar machotes es que el administrador s¢lo tiene que
establecer la estructura de cuentas y par metros de inicializaci¢n una
sola vez. A partir de ese momento se convierte en el valor por omisi¢n
(default) para todos los programas protegidos usando ese machote.


7.5 Ejecutando un Archivo Protegido


Para usar un archivo protegido, sencillamente c¢rralo en la forma
usual. Ahora, en lugar de ejecutar el programa, Sentry ejecutar . El
usuario estar  confrontando un acceso r pido, y ‚l debe ingresar un
acceso y pasaporte correctos para continuar.

Un acceso err¢neo resultar  para el usuario el no poder ingresar en el
sistema (con Sentry en uso normal). Un acceso correcto sencillamente
correr  el archivo protegido, Si el archivo protegido estaba designado
como un programa de DOS, cuando la ejecuci¢n del archivo protegido es
terminada, el usuario ser  retornado a cualquier lugar donde ‚l estuvo
previamente a la ejecuci¢n (Ej. DOS prompt, etc.)

Los programas basados en Windows operan un poco diferente. Ya que
Sentry no puede detectar cuando un programa basado en Windows termina
su ejecuci¢n, Sentry necesita una se¤al por parte del usuario para
indicarle que el programa ha terminado. Un archivo protegido que ha
sido designado como basado en Windows se ejecutar  normalmente durante
su uso, pero en lugar de finalizar, Sentry continuar  activo
(usualmente en una ventana de DOS) y espera las indicaciones del
usuario.

En estos casos es importante asegurarse de que el programa protegido
haya terminado su ejecuci¢n antes de presionar ninguna tecla en Sentry
dentro de la ventana de DOS. Indicarle a Sentry que el programa ha
terminado su ejecuci¢n cuando a£n no lo ha hecho causar  un "Error de
Archivo Compartido" (Sharing violation) y puede comprometer la
seguridad de su sistema (ej: un usuario experimentado podr¡a ejecutar
el programa sin tener una cuenta activa). Por esta raz¢n usted debe
asegurarse de que el programa ha terminado su ejecuci¢n  antes de
permitir a Sentry efectuar las labores de limpieza que requiere..

Si usted encuentra problemas al ejecutar programas de Windows
protegidos por Sentry, revise la secci¢n 13 para ayuda al respecto.

Se puede pasar argumentos en la l¡nea de comando de estos programas en
la manera normal. Para ejecutar FORMAT con el argumento A:, ‚ste se
escribir¡a de la siguiente manera:

format a:

Lo que es id‚ntico a la forma tradicional de especificar argumentos.


7.6 Actualizando un Programa Protegido

Aun cuando no es necesario hacerlo siempre que usted actualice su
instalaci¢n primaria de Sentry, los programas protegidos tambi‚n
pueden ser actualizados a nuevas versiones de Sentry, si usted as¡ lo
desea.

Cuidado: A diferencia de Sentry, los par metros de inicializaci¢n no
pueden ser exportados fuera de un programa protegido.

Igual que con la protecci¢n inicial de programas (ver punto 7.3), la
estructura de cuentas ser  copiada de la versi¢n de Sentry que usted
utilice para proteger el programa. El Super Usuario tendr  entonces
que modificar los par metros de inicializaci¢n y listas de usuarios
para obtener el arreglo deseado.

La actualizaci¢n tambi‚n puede ser usada para "copiar" los par metros
de inicializaci¢n y estructura de cuentas de un programa protegido, en
caso de que usted desee empezar otra vez ¢ hacer cambios radicales a
los niveles de acceso.

La actualizaci¢n tambi‚n puede convertir un programa convencional
basado en DOS a un programa basado en Windows, si as¡ se requiere.


8.0 Creando una nueva Instancia de Sentry
=========================================

En algunos de los escenarios descritos anteriormente, se le puede
requerir el crear una nueva instancia de Sentry. Esto es, una copia
completamente nueva de Sentry, que trabaje independientemente de las
dem s copias. Este es un proceso relativamente sencillo, que usted
puede realizar tantas veces como lo requiera.

La primera acci¢n que debe de tomar al crear una nueva instancia, es
crear el directorio donde desea instalarlo, Si usted planea tener
varias instancias, usted puede crear un directorio principal de
Sentry, con cada instancia instalada por debajo de este. Por ejemplo:

c:\Sentry
|
+----+------- Inst1
|
+------- Inst2

Esto le permitir  mantener todos sus archivos de Sentry bien
organizados y separados de sus dem s programas. Cree usted un
directorio para cada instancia que usted considere que va a necesitar.
De ah¡, simplemente copie TODOS los archivos de Sentry a cada
directorio.

El paso final es establecer las cuentas de cada instancia, de acuerdo
a sus necesidades. Para hacer esto usted debe de accesar cada
directorio individualmente y ejecutar Sentry. Ahora accese como Super
Usuario y establezca todas las cuentas requeridas. Recuerde que cada
instancia es totalmente independiente de las dem s. Su informaci¢n de
cuentas no ser  la misma entre dos instancias (de otra manera no tiene
objeto el tener dos instancias).

Usted siempre debe probar cada instancia y asegurarse de que funcione
como lo espera antes de utilizarla.


9.0 Registro
============

9.1 Generales

Si usted utiliza Sentry en su(s) m quina(s), le sugiero registrar este
programa. Mucho tiempo y esfuerzo han sido gastados para hacer de
Sentry un programa de seguridad viable. Con su ayuda, Sentry puede
continuar adapt ndose a nuevas situaciones y manteni‚ndose al tanto de
nuevos desarrollos en el campo de la seguridad en computadoras.

Por otro lado, me doy cuenta que no todo mundo puede darse el lujo de
registrarse. En tal caso, por favor si‚ntase en la entera libertad de
continuar usando la versi¢n Shareware. No hay limitaciones en cuanto
al n£mero de veces que puede ser usado. Mi intenci¢n con Sentry fue
hacer una contribuci¢n a la seguridad en el mundo de las computadoras
y hacerla disponible a todo mundo. Todo lo que yo pido es que si usted
utiliza Sentry y puede pagarlo, por favor se registre.

La versi¢n Shareware de Sentry tiene toda la funcionalidad de la
versi¢n registrada, salvo una excepci¢n: No codifica los pasaportes.
Esto le permitir  probar todas las funciones de Sentry antes de que se
comprometa a comprarlo. La versi¢n Shareware por s¡ misma es un
programa muy seguro, de cualquier forma, si usted toma la seguridad
seriamente, los pasaportes de texto abierto no son una opci¢n viable.

Para ordenar simplemente llene la forma de orden provista (ORDEN.FRM)
y rem¡tala por e-mail o m ndeme una copia por correo.


9.2 Beneficios de Registrarse

Como un usuario registrado, usted recibir :

? El programa de Sentry completo (con codificaci¢n de pasaportes) y
archivos relacionados, en un disco flexible de 3.5".

? La utiler¡a adicional SDEL, que le permite borrar cualquier tipo de
archivo en una forma segura.

? Un manual de usuario impreso (esencialmente este archivo, con
algunos cambios en formato y contenido).

? Soporte ilimitado de instalaci¢n para ayudarle a funcionar
r pidamente.

? Actualizaciones gratuitas tan pronto como se encuentren disponibles,
por medio de internet.

? Avisos sobre cualquier riesgo potencial de seguridad, e
instrucciones sobre la manera de protegerse.

? La habilidad de solicitar caracter¡sticas espec¡ficas en versiones
futuras de Sentry.

? Una conciencia limpia, sabiendo que ha pagado usted por sus
programas.

NOTA: Las versiones registradas no son compatibles entre s¡. Esto es,
la informaci¢n de cuentas de un usuario est  encriptada en forma
distinta a la de cualquier otro usuario. La versi¢n de Sentry que
usted recibe es buena para usted y s¢lo para usted y sus archivos (de
la misma manera nadie m s puede utilizar su copia de Sentry con la
informaci¢n de cuentas de usted).


10.0 Los Par metros de Inicializaci¢n
=====================================

Abajo se muestran todos los par metros de inicializaci¢n que pueden
ser cambiados dentro de Sentry. Una peque¤a descripci¢n de cada
par metro se incluye junto con cualquier comentario de seguridad y el
valor por omisi¢n de ese par metro.

10.1 Localizaci¢n del Archivo de Bit cora

Aqu¡ se contiene la localizaci¢n del archivo de bit cora. La bit cora
debe ser mantenida en un lugar seguro, apartada de mirones y
entrometidos

Nota: Usted deber  cambiar el nombre del archivo. En vez de SENTRY.LOG
a otro nombre menos llamativo. Un intruso potencial buscar  el nombre
SENTRY.LOG ¢ similares. Usted puede disfrazarlo con nombres como
file_id.diz, chklist.ms, warm.com, etc, etc.

Default: c:\Sentry.log


10.2 Localizaci¢n del Archivo de Copia de Seguridad de la Bit cora

Aqu¡ se contiene la localizaci¢n del archivo de copia de seguridad de
la bit cora. Cuando se ha alcanzado el tama¤o m ximo del archivo de
bit cora (max log file size), la mitad de este archivo es movida
autom ticamente al archivo de respaldo. Esto previene el que el
archivo de bit cora se vuelva muy grande y poco manejable.

Default: c:\backup.log


10.3 Localizaci¢n del Archivo de Mensajes

Aqu¡ se contiene la localizaci¢n del archivo de mensajes. El archivo
de mensajes debe ser mantenido en un lugar seguro, apartada de mirones
y entrometidos


Nota: Usted deber  cambiar el nombre del archivo. En vez de SENTRY.LOG
a otro nombre menos llamativo. Un intruso potencial buscara el nombre
SENTRY.MSG ¢ similares. Usted puede disfrazarlo con nombres como
file_id.diz, chklist.ms, warm.com, etc, etc.

Default: c:\Sentry.msg


10.4 Largo M¡nimo para Pasaportes

Ordena el largo m¡nimo para pasaportes e identificaciones (Login)

Nota: Un valor de 4 debe ser el m¡nimo absoluto para Largo M¡nimo de
Pasaporte (MinPasswordLen). Un valor de 5 ¢ 6 ser¡a mucho mejor. Los
pasaportes cortos son mucho m s f ciles de quebrar ya que se tienen
que hacer muchos menos intentos para lograr quebrarlos.

Default: 4


10.5 Largo M ximo para Pasaportes

Ordena el largo m ximo para pasaportes e identificaciones

Default: 20


10.6 M ximo de Accesos Inv lidos

Ordena el m ximo de intentos que un usuario puede tratar de ingresar
al sistema antes de ser rechazado

NOTA: Este valor no debe de ser muy alto. Es muy raro que un usuario
leg¡timo se equivoque en el ingreso tres veces seguidas. Un intruso
potencial tendr  que intentar en muchas ocasiones antes de llegar a
ning£n lado. Ajustar Intentos M ximos (MaxTries) al derredor de 3
impedir  su avance notablemente ya que tendr  que reiniciar la m quina
cada tercer intento fallado.

Default: 3


10.7 Espera Forzada Despu‚s de Acceso Inv lido

Ordena el intervalo en segundos de espera despu‚s de que el usuario
falla en ingresar al sistema (LOGIN). 

NOTA: Ordenar el Per¡odo de Espera a 3 ¢ m s incrementa el tiempo que
le tomar  a un intruso entrar al sistema siguiendo una rutina met¢dica
para adivinar ¢ descubrir pasaportes. Realmente no crea mucha
inconveniencia para el usuario leg¡timo pero incrementa la seguridad
notablemente

Default: 3


10.8 Tama¤o M ximo de la Bit cora

Aqu¡ se ordena el tama¤o m ximo de la bit cora antes de que la mitad
m s vieja sea movida autom ticamente al archivo de respaldo. El tama¤o
se especifica en n£mero de kilobytes (1024 bytes).

Un valor de 0 indica que no se haga respaldo de la bit cora.

Default: 20


10.9 Tecla para Cambiar Pasaportes

Ordena el s¡mbolo a usar como pasaporte para cambiar pasaportes.

Indique el asterisco "*" para deshabilitar cambios de pasaportes por
los usuarios

Default: passwd


10.10 Car cter de M scara de Pasaportes

Ordena el s¡mbolo que se mostrar  en pantalla durante el ingreso del
pasaporte

Ingrese '?' para NO desplegar ning£n caracter. Ingrese '!' para
desplegar el caracter tecleado (no se recomienda).

Default: *


10.11 D¡as de Validez de un Pasaporte

Indica el n£mero de d¡as de validez de un pasaporte antes de que
expire. Este es el valor por omisi¢n usado cada vez que un pasaporte
es cambiado. La fecha de expiraci¢n de pasaportes individuales puede
ser especificada en el men£ "Super Usuario".

NOTA: Es una buena idea darle vigencia de entre 180 y 365. M s de un
a¤o de vigencia es un riesgo de seguridad por su duraci¢n. Menos de
seis meses es un riesgo porque la gente empezar  a olvidar sus nuevos
pasaportes y los escribir  en alg£n lado. Esta cifra debe de depender
realmente de qu‚ tan ocupado est‚ el sistema.

Cero (0) indica sin fecha de expiraci¢n.

Default: 365


10.12 D¡as para Expiraci¢n de Cuenta

Indica el n£mero de d¡as que una cuenta no usada es v lida antes de
que expire autom ticamente. Este es el valor por omisi¢n utilizado
durante la creaci¢n de una nueva cuenta. La expiraci¢n de las cuentas
individuales puede ser especificada en el men£ "Super Usuario".

NOTA: Esta cifra deber  depender del nivel de actividad de su sistema.
Los sistemas activos se pueden permitir una cifra m s baja que los
sistemas con poca actividad. Usted deber  tambi‚n tener en
consideraci¢n la probabilidad de un intruso utilizando una cuenta
vieja y sin uso.

Cero (0) indica: Nunca invalidar cuentas viejas.

Default: 365


10.13 Tiempo para Activaci¢n de Protector de Pantalla

Indica el tiempo de inactividad (en segundos) que deber  pasar antes
de que se active el protector de pantalla.

Default: 300


10.14 Mensaje del Protector de Pantalla

Este es el mensaje que se mostrar  aleatoriamente en la pantalla
cuando el protector de pantalla se active.

Default: This is a Secure Terminal.


10.15 L¡nea de Comando de Login

Aqu¡ se indica el valor de la l¡nea de comando que es mostrada cuando
se espera que el usuario teclee su nombre de usuario (Login).
Modificar este valor le permite ajustar su ambiente de trabajo como
mejor le acomode.

Default: Login:


10.16 L¡nea de Comando de Pasaporte

Aqu¡ se indica el valor de la l¡nea de comando que es mostrada cuando
se espera que el usuario teclee su pasaporte. Modificar este valor le
permite ajustar su ambiente de trabajo como mejor le acomode.

Default: Password:


10.17 Mensaje para Pasaporte Equivocado

Aqu¡ se indica el mensaje a mostrar cuando el usuario teclea el
pasaporte equivocado.

NOTA: Es una buena idea mantener el mismo mensaje para nombre
equivocado y pasaporte equivocado. De otra manera, un intruso sabr 
cuando YA encontr¢ una cuenta (por ejemplo: si SENTRY responde con
"Pasaporte Inv lido", el intruso ya sabe que el nombre del usuario
est  correcto). Mantener los dos mensajes iguales no le permite saber
si es el nombre del usuario ¢ el pasaporte el que est  equivocado.

Default: Invalid Login.


10.18 Mensaje para Nombre de Usuario Equivocado

Aqu¡ se indica el mensaje a mostrar cuando el usuario teclea el nombre
de usuario (Login) equivocado.

NOTA: Es una buena idea mantener el mismo mensaje para nombre
equivocado y pasaporte equivocado. De otra manera, un intruso sabr 
cuando YA encontr¢ una cuenta (por ejemplo: si SENTRY responde con
"Pasaporte Invalido", el intruso ya sabe que el nombre del usuario
est  correcto). Mantener los dos mensajes iguales no le permite saber
si es el nombre del usuario ¢ el pasaporte el que est  equivocado.

Default: Invalid Login.


10.19 Mensaje para Longitud de Pasaporte Equivocada

Aqu¡ se indica el mensaje que ser  mostrado cuando un usuario teclea
un pasaporte de largo invalido.

NOTA: Es prudente mantener el mismo mensaje para los casos de
Pasaporte Equivocado, Nombre Equivocado, Largo de Pasaporte Equivocado
y Largo de Nombre Equivocado. Esto prevendr  que un intruso conozca el
m¡nimo y m ximo permitidos para nombres y pasaportes en su sistema.
Conocer la longitud v lida de un pasaporte puede reducir enormemente
el tiempo necesario para encontrarlo ¢ adivinarlo.

Default: Invalid Login.


10.20 Mensaje para Longitud de Nombre de Usuario Equivocado

Aqu¡ se indica el mensaje que ser  mostrado cuando un usuario teclea
un nombre de usuario (Login) de largo inv lido.

NOTA: Es prudente mantener el mismo mensaje para los casos de
Pasaporte Equivocado, Nombre Equivocado, Largo de Pasaporte Equivocado
y Largo de Nombre Equivocado. Esto prevendr  que un intruso conozca el
m¡nimo y m ximo permitidos para nombres y pasaportes en su sistema.
Conocer la longitud v lida de un pasaporte puede reducir enormemente
el tiempo necesario para encontrarlo ¢ adivinarlo.

Default: Invalid Login.


10.21 Registro para Pasaporte Equivocado

Aqu¡ se indica el mensaje que ser  grabado en la bit cora cuando un
usuario teclea el pasaporte equivocado.

Default: User entered the wrong password.


10.22 Registro para Nombre de Usuario Equivocado

Aqu¡ se indica el mensaje que ser  grabado en la bit cora cuando un
usuario teclea el nombre de usuario equivocado.

Default: User entered the wrong Login.


10.23 Registro para Pasaporte Equivocado

Aqu¡ se indica el mensaje que ser  grabado en la bit cora cuando un
usuario teclea un pasaporte de longitud inv lida.

Default: Invalid Password Length.


10.24 Registro para Longitud de Nombre de Usuario Equivocado

Aqu¡ se indica el mensaje que ser  grabado en la bit cora cuando un
usuario teclea un nombre de usuario (Login) de longitud inv lida.

Default: Invalid Login Length.


10.25 Variable de Ambiente

Aqu¡ se indica el nombre de la variable de ambiente utilizada para
guardar el nombre de usuario una vez que ha efectuado un ingreso
correcto (Login).

NOTA: La variable de ambiente USUARIO ¢ USER es utilizada por muchos
programas de red, tales como Novell. Al utilizar esta variable, Sentry
puede ser utilizado en conjunci¢n con estos sistemas.

Default: USER


10.26 Habilitar Sentry con Windows

La bandera WINDOWS es especificada si Usted desea correr Sentry desde
Windows. T‚cnicamente, esto permite a Sentry abrir una ventana de DOS
despu‚s de un acceso correcto (Login). Indicar este valor como Uno (1)
no tiene ning£n efecto en el uso normal y no constituye un riesgo de
seguridad

(0= No Correr En Windows, 1=Correr En Windows)

Default: 1


10.27 Mostrar Pantalla de Introducci¢n

Aqu¡ se determina si la pantalla de introducci¢n es desplegada ¢ no.
Usted puede elegir no desplegarla si Usted no desea que los usuarios
sepan qu‚ programa est  siendo utilizado. Por otro lado, la
informaci¢n de registro deber  ser desplegada para prop¢sitos de
autentificaci¢n. Esta opci¢n fue agregada ya que la seguridad est  por
encima de todo.

(0-No Desplegar, 1=Desplegar)

Default: 1


10.28 Formato de Fechas

Esto le permitir  desplegar fechas en distintos formatos. Algunas
personas prefieren unos formatos en vez de otros y aqu¡ se le permite
escoger el que mejor se adecue a sus necesidades.

(0 = MM/DD/YYYY, 1 = DD/MM/YYYY)

Default: 1


10.29 Sensitividad de MAYUSCULAS / min£sculas

Aqu¡ se indica la sensitividad de MAYUSCULAS/min£sculas. Si se escoge
el valor "Insensitivo" las palabras Sentry, SENTRY y sentry ser n
tratadas por igual en la l¡nea de comando de Login. Si se escoge el
valor "Sensitivo" las tres palabras ser n tratadas como distintos
nombres de usuario.

(0 = Sensitivo,  1 = Insensitivo)

NOTA: Usar "Insensitivo" reduce el n£mero de Logins permitidos e
incrementa la posibilidad de que un intruso encuentre el nombre de
usuario correcto. Pese a esto, hay gente que prefiere utilizar el
valor "Insensitivo".

Default: 0


10.30 Ventanas en Movimiento

Aqu¡ se le permite escoger entre ventanas normales ¢ ventanas con
movimiento. Es estrictamente visual y no tiene ning£n efecto en la
seguridad.

(1 = Modo Normal,  2 = Modo de ventanas en movimiento)

Default: 2


10.31 Habilitar Color

Esto determina si Sentry se despliega en color ¢ no. Algunos usuarios
de computadoras port tiles pueden preferir Blanco y Negro para mejor
despliegue en sus pantallas.

(0 = Blanco y Negro,  1 = Color)

Default: 1


10.32 Color de Texto

Usted puede especificar el contenido de TextoColor (TextColour) al
valor del color en que desea que el texto normal aparezca. Los valores
para distintos colores aparecen en la tabla que se muestra abajo.

COLORES:
0   Negro        4   Rojo           8   Gris Oscuro   12 Rojo Claro
1   Azul         5   Morado         9   Azul Claro    13 Morado Claro
2   Verde        6   Caf‚           10 Verde Claro    14 Amarillo
3   Siena        7   Gris Claro     11 Siena Claro    15 Blanco

Default: 15


10.33 Fondo del Texto

Usted puede fijar el contenido de FondoTexto (TextBackground) al valor
del color que desee como fondo de la pantalla. Los valores de los
distintos colores se muestran en la tabla desplegada a continuaci¢n.

COLORES:
0   Negro        4   Rojo           8   Gris Oscuro   12 Rojo Claro
1   Azul         5   Morado         9   Azul Claro    13 Morado Claro
2   Verde        6   Caf‚           10 Verde Claro    14 Amarillo
3   Siena        7   Gris Claro     11 Siena Claro    15 Blanco

Default: 1


10.34 Color de Texto Resaltado

Usted puede indicar el contenido de ColorResaltado (HighColour) como
el valor del color que Usted desee para texto resaltado. Los valores
de los distintos colores son mostrados en la tabla que a continuaci¢n
se muestra.

COLORES:
0   Negro        4   Rojo           8   Gris Oscuro   12 Rojo Claro
1   Azul         5   Morado         9   Azul Claro    13 Morado Claro
2   Verde        6   Caf‚           10 Verde Claro    14 Amarillo
3   Siena        7   Gris Claro     11 Siena Claro    15 Blanco

Default: 1


10.35 Fondo de Texto Resaltado

Usted puede indicar el contenido de FondoResaltado (HighBackground)
como el valor del color que Usted desee para fondo resaltado. Los
valores de los distintos colores son mostrados en la tabla que a
continuaci¢n se muestra.

COLORES:
0   Negro        4   Rojo
1   Azul         5   Morado
2   Verde        6   Caf‚
3   Siena        7   Gris Claro

Default: 7


10.36 M ximo de Accesos Inv lidos

Aqu¡ se indica el valor por omisi¢n para el n£mero de ingresos (Login)
inv lidos consecutivos antes de que una cuenta sea cancelada. S¢lo un
Super Usuario puede volver a rehabilitar una cuenta que ha sido
cancelada.

Default: 10


10.37 Tecleado Previo a Ejecuci¢n

Aqu¡ se le permite determinar si Sentry har  caso de cualquier
caracter que sea tecleado antes de que se inicie su ejecuci¢n. Con
esta opci¢n habilitada, el usuario puede teclear su nombre de usuario
(Login) y pasaporte antes de que Sentry inicie su operaci¢n y ser 
autom ticamente usado. Esto es £til para ahorrar tiempo durante el
ingreso.

(0 = Ignorar caracteres, 1 = Aceptar caracteres)

NOTA: Algunos administradores de sistemas inhiben esta opci¢n ya que
puede confundir a los usuarios y provocar accesos equivocados.

Default: 1


10.38 Borrar Pantalla

Este indicador determina si la pantalla es borrada antes de correr
Sentry. Algunos usuarios prefieren activar esta opci¢n ya que la
pantalla puede verse abarrotada de otra manera.

(0 = NO Borrar Pantalla, 1 = Borrar Pantalla)

Default: 0


10.39 Pausa sobre Ultimo Acceso

Aqu¡ se indica durante cu nto tiempo se muestra la informaci¢n del
£ltimo acceso (Login) antes de borrar la pantalla. Un valor de cero
(0) indica que no habr  pausa y la informaci¢n del £ltimo acceso no
ser  borrada de la pantalla. Cualquier otro valor ser  el n£mero de
segundos elapsados antes de borrar la pantalla.

Default: 0


10.40 Borrado de Seguridad

Esta opci¢n permite al Super Usuario la activaci¢n ¢ desactivacion del
Borrado de Seguridad. Si la opci¢n se encuentra activada, cualquier
archivo borrado por Sentry NO ser  recuperable.

(0 = Borrado Normal, 1 = Borrado de Alta Seguridad, 2 = Borrado de
R pida Seguridad)

Default: 1


10.41 Ver Resaltado

Este ajuste controla c¢mo se muestra la informaci¢n de los usuarios en
el men£ del Super Usuario. Con la opci¢n activada, los siguientes
datos son resaltados, haci‚ndolos m s f ciles de notar:- Super
Usuarios

- Cuentas inactivas
- Cuentas expiradas
- Pasaportes expirados
- M ximo de Logins inv lidos alcanzado

Dado que esta opci¢n provoca algunos retrasos en el proceso, Usted
puede elegir el deshabilitarla.

(0 = Desactivar Resaltado, 1 = Activar Resaltado)


10.42 Ver Color Resaltado

Usted puede indicar el valor del color deseado como fondo del texto
normal. Los valores de los distintos colores se muestran en la
siguiente tabla.

COLORES:
0   Negro        4   Rojo           8   Gris Oscuro   12 Rojo Claro
1   Azul         5   Morado         9   Azul Claro    13 Morado Claro
2   Verde        6   Caf‚           10 Verde Claro    14 Amarillo
3   Siena        7   Gris Claro     11 Siena Claro    15 Blanco


10.43 Deshabilitar CTRL-C

Esta opci¢n le permite deshabilitar CTRL-C, CTRL-BREAK, y
CTRL-ALT-DELETE. Usted puede desear hacerlo ya que el uso de estas
combinaciones de teclas pueden en ocasiones permitir la evasi¢n de los
sistemas de seguridad. Esta opci¢n s¢lo debe ser habilitada en copias
de Sentry que corren durante la inicializaci¢n de la m quina.
Habilitar esta opci¢n utiliza menos de 1 K de memoria convencional y
se mantiene activa aun despu‚s de que Sentry ha terminado su
ejecuci¢n.

(0 = Habilitar CRTL-C, 1 = Deshabilitar CTRL-C)


11.0 Notas T‚cnicas
===================

11.1 Algoritmo de Codificaci¢n

El algoritmo de codificaci¢n usado es el normalmente conocido como
Crypt() de UNIX. Es un algoritmo de codificaci¢n de un solo sentido
que incorpora el Est ndar para Encriptado de Datos (DES) y tecnolog¡a
RSA. Este es usado en sistemas de UNIX para asegurar pasaportes. (Como
comentario, el c¢digo de encriptado no se incluye en la versi¢n
Shareware, por lo que a£n una revisi¢n concienzuda del c¢digo no
revelar  el algoritmo).

Los pasaportes de usuario nunca son descodificados. Son grabados a
disco y se encuentran en memoria en un formato codificado. Los
pasaportes tecleados son codificados utilizando el mismo algoritmo y
comparados en su forma codificada. Esto previene el uso de programas
de revisi¢n de disco y memoria para descubrir los pasaportes.

Algunas pruebas realizadas para probar la debilidad de los pasaportes
revelan lo siguiente.

Largo de pasaporte Per¡odo de tiempo para descifrarlo 4 22 d¡as 5 1368
d¡as o 3.75 a¤os 6 232.4 a¤os 7 14,409 a¤os 8 893,357 a¤os

Estos c lculos son los aproximados para el uso de una Pentium a 90 MHz
y un pasaporte alfanum‚rico.

Estos c lculos pueden ser ajustados conforme las pruebas realizadas
sean m s exactas. Las cifras mencionadas anteriormente tambi‚n asumen
que usted conoce el largo del pasaporte, lo cual no puede ser
determinado viendo la versi¢n encriptada. El resultado es que el
tiempo requerido para encontrar el pasaporte correcto pudiera ser
bastante m s largo.


11.2 Acceso de Super Usuario

Los privilegios de Super Usuario tambi‚n est n codificados en el
pasaporte. Se intentaron m£ltiples maneras de hacerlo antes de decidir
usar ‚ste. Es el m‚todo m s seguro. De hecho. Los privilegios de Super
Usuario est n codificados en el pasaporte (que despu‚s es codificado),
y posteriormente guardados nuevamente en el pasaporte codificado. Este
se ver¡a as¡:

pasaporte <-- Pasaporte como fue tecleado..

super(pasaporte) <-- Pasaporte con etiqueta de Super Usuario. * Esta
es la etiqueta que es usada para determinar el acceso.

crypt(super(pasaporte)) <-- Pasaporte codificado con etiqueta de Super
Usuario.

super(crypt(super(pasaporte))) <-- Pasaporte etiquetado como Super
        Usuario con etiqueta de Super Usuario * Esta es la etiqueta
        usada para ver qui‚n tiene privilegios de Super Usuario.

De esta manera, cuando usted utiliza el comando "Ver Usuarios", usted
puede ver quienes son Super Usuarios. De cualquier manera ya que la
etiqueta de Super Usuario no codificada puede ser editada, es
solamente usada para revisiones. La etiqueta de Super Usuario
codificada es utilizada para accesar el sistema. Si alguien intentara
alterar la etiqueta de Super Usuario, un mensaje ser  desplegado en la
bit cora cada vez que ese usuario accese el sistema.


11.3 Lista de Empaque

Los siguientes archivos forman parte de esta versi¢n de Sentry:

Sentry.exe 	Este es el archivo ejecutable.
Install.exe 	El programa de instalaci¢n.
Sdel.exe 	Una utiler¡a para el borrado seguro de archivos.*
Cbreak.sys 	Usado para deshabilitar CTRL-C.
File_id.diz 	Archivo corto de descripci¢n.
History.txt 	La historia de revisiones de Sentry.
License.txt 	El contrato de licencia.
Order.frm 	La forma de pedido.
Qstart.txt 	Instrucciones de arranque r pido.
Readme.com 	Despliega este archivo.
Readme.txt 	Este archivo.
Sentry.ins 	Descripci¢n de los par metros de inicializaci¢n.
Sentry.hlp 	Archivo de ayuda de Sentry.
Sentry.grp 	El archivo de grupo de Sentry para Windows.
Sentry.pif 	El archivo .PIF de Sentry para Windows.
Sentry.w95 	El archivo .PIF de Sentry para Windows 95.
Whatsnew.txt 	Una descripci¢n corta de las modificaciones a la £ltima versi¢n.

Si usted no tiene todos estos archivos, Sentry pudiera no trabajar.
Usted puede encontrar una versi¢n completa de Sentry (y
actualizaciones conforme se encuentren disponibles) en:

     http://www.cipherlogic.on.ca

* SDEL.EXE est  incluido solamente en las versiones registradas.


11.4 File_id.diz

El contenido real de file_id.diz se muestra abajo. Si se ha hecho
cualquier modificaci¢n al archivo original, por favor c¢pielo de la
siguiente secci¢n.

NOTA: Esto est  destinado primariamente para operadores de BBS's. Los
dem s usuarios pueden borrar este archivo si as¡ lo desean (aunque
este archivo debe de estar presente en cualquier caso de distribuci¢n
del programa).

-------------------CORTAR-----------------------
(V6.0) Sentry - DOS/Win/95 Security Program Extremely flexible
security program allows complete customization to fit your needs.
Protect system, O/S, and/or individual files and support up to 100
users with normal and "SuperUser" access. Detailed log files, a
message system, auditing, expiry dates, and non- recoverable deletion
help with security and system administration. Network/DESQview
compatible.
-------------------CORTAR-----------------------


11.5 Conversi¢n de Fechas

Un problema adicional con la conversi¢n de fechas es que el rango
v lido parece ser que se extiende s¢lo hasta el 18 de enero de 2038.
Esto no es un problema inmediato ya que todav¡a tenemos 40 a¤os hasta
que el plazo se cumpla, de cualquier manera lo consideramos
suficientemente importante como para incluirlo en las instrucciones.
De la misma manera se recomienda a los administradores de sistemas no
especificar fechas mayores a este l¡mite, ya que son consideradas
durante el proceso como fechas en el pasado, lo cual causar  graves
problemas.


11.6 Variables de Ambiente

Cuando un usuario ejecuta un acceso v lido, una variable de ambiente
de DOS es asignada con el nombre de usuario. Esto puede ser muy £til
ya que permite que programas especializados funcionen a conjunto con
Sentry.

Por ejemplo, si est  usted ejecutando Sentry de un archivo .BAT, usted
puede revisar qui‚n fue quien acceso el sistema y tomar las acciones
apropiadas.

Abajo se muestra un peque¤o archivo .BAT que puede ser utilizado para
realizar este tipo de funci¢n.

-----------CORTAR-----------
@echo off
rem *** Ejecutar Sentry.
c:\sentry\sentry
rem *** Revisar qui‚n acceso el sistema.
rem *** Utilizar el nombre de usuario en la l¡nea siguiente.
if %user% == Mike goto mike
if %user% == Danny goto dan
rem *** Utilice una l¡nea como las de arriba para cada usuario.
goto end
:mike
rem *** N¢tese que cada usuario individual tiene sus propios comandos.
echo Acceso de Super Usuario.
defrag c:
rem *** Otros comandos aqu¡.
goto end
:dan
echo Daniel accesando el sistema.
goto end
rem *** A¤ada mas usuarios conforme usted lo requiera
:end
rem *** A¤ada aqu¡ los comandos que ser n ejecutados.
rem *** Sin importar qui‚n accese el sistema.
-----------CORTAR-----------

NOTA: Los archivos .BAT no son seguros! Ninguna funci¢n cr¡tica debe
de ser llamada desde estos a menos que sea absolutamente necesario.

Un m‚todo alterno (y m s seguro) es escribir un programa en otro
lenguaje (como "C") y compilarlo. La mayor¡a de los lenguajes de
programaci¢n le permiten leer variables de ambiente. Esto quiere decir
que usted puede escribir sus propias extensiones personalizadas de la
funcionalidad de Sentry para ejecutarse una vez que el usuario haya
accesado el sistema.

Tambi‚n note usted que los nombres de usuario en las variables de
ambiente est n escritas todas en may£sculas (Sentry se convierte en
SENTRY cuando es escrito a una variable de ambiente).

** NOTA: A£n cuando las variables de ambiente son seguras
inmediatamente despu‚s de que Sentry es ejecutado, pueden no ser tan
seguras una vez que otros programas han sido ejecutados. Esto quiere
decir que otro programa pudo alterar la variable de ambiente para
hacerla parecer como que otro usuario acces¢ el sistema. Como
resultado, trate usted de realizar todos sus chequeos inmediatamente
despu‚s de la ejecuci¢n de Sentry.


11.7 Programas contra Virus

Si usted revisa su sistema con alg£n programa de protecci¢n contra
virus tal como Microsoft Anti-Virus o Norton Anti-Virus, usted va a
encontrar que Sentry aparece con frecuencia. La raz¢n para esto es que
algunos programas contra virus mantienen estad¡sticas de archivos
ejecutables. Cuando se ejecuta la siguiente revisi¢n, si el archivo
ejecutable no empata con las estad¡sticas, el protector de virus se
espanta. Esto puede EN ALGUNAS OCASIONES ser evidencia de un virus en
su sistema. Sentry se modifica a s¡ mismo (en una manera muy similar a
un virus) y por tanto puede ser reportado en algunas ocasiones, sin
embargo est‚ usted seguro que Sentry no presenta amenaza alguna.

SENTRY NO ES UN VIRUS!

Cada vez que usted utiliza Sentry, el ejecutable es modificado para
permitir un ambiente de operaci¢n m s seguro. Esto har  que muchos
programas contra virus se vuelvan locos. No se alarme, ya que ‚sta es
la forma normal de operaci¢n de Sentry.


11.8 Borrado de Archivos

En muchas ocasiones, informaci¢n clasificada puede ser obtenida
mediante la recuperaci¢n de archivos borrados y el examen de los
mismos. Esta es una pr ctica com£n y requiere muy pocas habilidades
t‚cnicas para lograrlo. Un usuario no autorizado recuperando archivos
puede causarle al administrador del sistema muchos problemas si la
informaci¢n recuperada es clasificada. As¡ mismo el usuario puede
estudiar la informaci¢n y desarrollar un plan de ataque basado en la
forma en la que el sistema opera.

As¡, cuando Sentry borra un archivo, este archivo no puede ser
recuperado para extraerle informaci¢n clasificada. Sentry logra este
objetivo turnando todas las peticiones de recuperaci¢n de archivos a
trav‚s de una funci¢n especial. Esta funci¢n esencialmente llena el
archivo deseado con basura (caracteres aleatorios) antes de borrarlo.
Una vez borrado, el archivo puede ser recuperado pero la informaci¢n
disponible en este archivo recuperado es la basura escrita por Sentry
y no datos reales. Como resultado, un usuario no autorizado no ser 
capaz de recuperar nada m s que caracteres aleatorios de la ejecuci¢n
de Sentry. Sentry utiliza este m‚todo de borrado en todos los
archivos, independientemente de su nivel de sensibilidad.

El valor por omisi¢n para esta opci¢n es habilitado, a£n cuando puede
ser deshabilitado en los par metros de inicializaci¢n.

El mismo nivel de seguridad puede ser encontrado en el programa
externo SDEL. Cualquier archivo borrado con SDEL no puede ser
recuperado, por lo que se debe ejercer cuidado en cuanto a qui‚n tenga
acceso a SDEL. Prot‚jalo con Sentry, y s¢lo los usuarios autorizados
ser n capaces de ejecutarlo.


11.9 Informaci¢n General

Sentry fue escrito en C++, con la mayor¡a de su c¢digo siguiendo el
estilo normal de "C". Sentry fue compilado con Borland C++ V5.0, y
actualmente se compone de 9,000 l¡neas de c¢digo. La portabilidad
entre m quinas no es un problema ya que Sentry ha sido dise¤ado y
probado en m quinas del tipo est ndar MS-DOS.

Sentry ha sido verificado para compatibilidad con Windows 3.x y
Windows 95. Funcionar  con todos los procesadores a partir e
incluyendo el 80286.


12.0 Amenazas Potenciales a la Seguridad
========================================

Nunca subestime a sus usuarios. Nunca est‚ usted satisfecho de la
seguridad de su sistema. Los usuarios son incre¡blemente adeptos para
encontrar resquicios en la seguridad, y una vez encontrados estos
resquicios pueden ser explotados. Por esto abajo se listan todos los
riesgos a la seguridad de los que se tiene conocimiento.


12.1 Informaci¢n de Cuentas

Con la publicaci¢n de Sentry V3.0, la informaci¢n de cuentas es mucho
m s segura. A£n es POSIBLE que un usuario pueda encontrar y disecar la
informaci¢n de cuentas. La probabilidad de esto es remota ya que la
informaci¢n no es f cilmente entendida o editada. As¡ mismo todos
estos m‚todos requieren un conocimiento interno de la forma en la que
Sentry opera y ‚sta no est  f cilmente disponible. El mejor origen
para esa informaci¢n ser¡a a partir de este documento, el cual
deliberadamente omite partes importantes de la informaci¢n t‚cnica
necesaria.

Si un usuario lograra descifrar la informaci¢n de cuentas, ser¡a capaz
de realizar las siguientes acciones:

A¤adir - Borrar una fecha de expiraci¢n (de cuenta o pasaporte). Esto
no es un problema serio para pasaportes ya que un usuario tiene que
teclear el pasaporte anterior antes de que se le notifique que ‚ste ha
expirado. Un atacante NO puede hacer que expire un pasaporte y luego
accesar esa cuenta.

Editar un nombre de usuario Esto efectivamente bloquear¡a el acceso de
ese usuario, a menos que pudieran figurarse el nuevo nombre de
usuario.

Borrar un usuario.
Los usuarios pueden ser borrados pero no creados.

Destruir un pasaporte.
Ya que los pasaportes est n codificados, no hay manera de cambiar un
pasaporte para que sea de ning£n uso. Un pasaporte editado bloquear 
el acceso del usuario de esa cuenta, hasta que el pasaporte sea
rehabilitado.

Cambiar informaci¢n sobre el £ltimo acceso.
No es cr¡tica, pero podr¡a ser usada para cubrir las acciones de un
atacante.

Cambiar la informaci¢n sobre n£mero de accesos inv lidos.
Igual que el punto anterior.

A¤adir / Remover restricciones al n£mero m ximo de accesos inv lidos.
Podr¡a permitir un ataque por "fuerza bruta" al pasaporte de una
cuenta si la restricci¢n fuera removida. Tambi‚n, si un atacante
estableciera la restricci¢n a un solo intento inv lido, esa cuenta
ser¡a bloqueada con un solo intento fallido. Esto ser¡a muy molesto
para el Super Usuario, ya que tendr¡a que restablecer la cuenta con
frecuencia.

Es importante saber que un usuario mal intencionado no puede otorgarse
privilegios de Super Usuario ni tampoco puede intentar efectivamente
el modificar un pasaporte. Para realizar cualquiera de estas funciones
el usuario debe de haber accesado como Super Usuario. Adicionalmente
NADIE (ni los Super Usuarios) pueden ver los pasaportes (recuerde que
no pueden ser descodificados). Finalmente, usted debe mantener
vigilancia sobre su sistema y tratar de encontrar cualquier anomal¡a
tan pronto como esto sea posible.

En esencia:

Sentry hace su parte a favor de la seguridad, pero usted debe hacer la
suya as¡mismo. TENGA A BUEN RECAUDO SUS PASAPORTES DE SUPER USUARIO.

12.2 Resquicios en el Equipo

A£n cuando es poco probable que un usuario haga esto, hay un riesgo
potencial de seguridad para Sentry. Afortunadamente s¢lo puede ser
implementado por usuarios con grandes conocimientos t‚cnicos. Si un
usuario realmente quiere meterse en su sistema, lo puede desensamblar
y quitarle la bater¡a al BIOS. Esto har  que el BIOS se reinicialice a
la configuraci¢n b sica, que no incluye un pasaporte. Ya aqu¡, el
usuario puede entrar al BIOS y cambiar la secuencia de arranque de C,A
a A,C. Esto quiere decir que la computadora arrancar  de un disco
flexible, si ‚ste se encuentra presente, y  accesar el disco duro sin
m s problemas u obst culos.

Posible pero no probable. Si usted quiere cerrar esta posibilidad,
usted puede modificar el cableado del disco flexible para que nunca
sea usado durante el arranque. Aun no se tienen instrucciones para
este paso pero ser n incluidas en la documentaci¢n tan pronto como
est‚n disponibles.

Por el mismo rumbo, un usuario puede reemplazar su disco duro (el que
contiene Sentry) por otro en el que no est‚ Sentry instalado. De esta
manera puede arrancar desde el nuevo disco duro y nunca preocuparse
por Sentry. Tambi‚n, si mantuviera el disco original en el sistema
(configurado como D: por ejemplo), ‚l podr¡a accesar sus datos. Este
tipo de trucos son altamente improbables pero no imposibles.

Los dos m‚todos anteriores requieren m s conocimientos y habilidades
t‚cnicas que las que posee el usuario com£n y no se deben considerar
un riesgo serio. Se incluyen solamente para que est‚ usted consciente
del riesgo. Si est  usted preocupado por este tipo de ataque, usted
debe de buscar la manera de colocar candados ¢ chapas al gabinete ¢
soldar los tornillos al gabinete.

Es cr¡tico darse cuenta de que es EXTREMADAMENTE dif¡cil evadir un
ataque determinado y bien organizado. Utilizar Sentry no garantiza la
seguridad de su sistema. Lo que si hace es reducir enormemente la
posibilidad de un ataque exitoso y, m s importante, le puede alertar
de riesgos potenciales antes de que se conviertan en algo m s serio.
Su capacidad de defensa es mayor una vez que sabe que est  siendo
atacado. Sentry le puede mantener informado de acciones dudosas en su
PC as¡ como servir como una poderosa herramienta para evadir la
mayor¡a de los riesgos.


13.0 Resoluci¢n de Problemas
============================

13.1 Mensajes de Error 

Abajo se listan todos los posibles mensajes de error que usted pueda
recibir usando Sentry. Con cada uno se encuentra una breve descripci¢n
de su significado, causas probables y la manera de solucionarlos.

Est‚ consciente de que todos estos errores bloquean la ejecuci¢n de
Sentry, excepto donde se diga lo contrario. Esto puede a veces ser
inconveniente pero se hace por motivos de seguridad ya que de esta
manera un atacante no puede inducir un error en la operaci¢n y
aprovecharlo para ingresar al sistema.

13.1.1 Imposible localizar Ambiente.

Esto indica un error con su ambiente de DOS. Aseg£rese que est  usando
el ambiente normal ¢ que este est  correctamente configurado. Esto es
s¢lo un aviso y no abortar  la ejecuci¢n.


13.1.2 Ambiente Agotado - No Hubo Modificaci¢n.

Hubo un error tratando de modificar la configuraci¢n del ambiente de
DOS. Esto puede ocurrir si usted trata de ejecutar Sentry desde su
propia ventana de DOS. (ej: tratar de ejecutar Sentry desde Windows y,
cuando se encuentre en la ventana de DOS de Sentry, tratar de
ejecutarlo otra vez). Si este error ocurriera, usted est  generalmente
usando demasiadas variables de ambiente para el espacio asignado. Vea
su manual de usuario de DOS para la manera de incrementar el espacio
de ambiente. Esto es s¢lo un aviso y no abortar  la ejecuci¢n.


13.1.3 Error Creando el Respaldo de Bit cora!

Se detect¢ un problema con el respaldo de la bit cora. Aseg£rese de
que el archivo mencionado en los par metros de inicializaci¢n no tenga
el atributo S¢lo-Lectura u Oculto ¢ Sistema activados.


13.1.4 Error Creando Bit cora!

El archivo en que se escriben todas las transacciones de su
computadora no pudo ser creado. Aseg£rese de tener la correcta ruta de
acceso en este par metro y que tenga disponibles m s de 80k de espacio
libre en su disco. Si un archivo de bit cora ya existe, los registros
le ser n a¤adidos. De otra manera un nuevo archivo ser  creado.


13.1.5 Error Creando Archivo Temporal!

Sentry no puede crear un archivo temporal. Aseg£rese de tener al menos
80k de espacio libre en el disco que contiene a Sentry antes de
intentar ejecutarlo.


13.1.6 Error Abriendo Bit cora!

Se encontr¢ un problema con la bit cora. Aseg£rese de que el archivo
mencionado en los par metros de inicializaci¢n no tenga el atributo
S¢lo-Lectura u Oculto ¢ Sistema activados.


13.1.7 Error Abriendo Archivo de Mensajes!

Este error indica que el archivo de mensajes no puede ser abierto.
Aseg£rese de que sus par metros de inicializaci¢n para el archivo de
mensajes est‚n correctos y que el archivo no tenga el atributo
S¢lo-Lectura u Oculto ¢ Sistema activados.


13.1.8 Error Abriendo Programa Protegido!

Este error puede ocurrir cuando se est  protegiendo un programa en el
men£ de Super Usuario. Aseg£rese de que el programa que desea proteger
sea legible.


13.1.9 Error Abriendo Sentry.INS!

Este error ocurre cuando Sentry no puede encontrar el archivo que
contiene las descripciones para los par metros de inicializaci¢n.
Aseg£rese que Sentry.INS se encuentre en el mismo directorio donde se
encuentra Sentry.EXE.


13.1.10 Error Abriendo Archivos de Sistema!

Existe un error al abrir alguno de sus archivos de sistema. Si este
error llegara a ocurrir, aseg£rese de que su AUTOEXEC.BAT, CONFIG.SYS
y MSDOS.SYS (S¢lo usuarios de Windows 95) sean legibles, si es que
existen.


13.1.11 Error Abriendo Archivo Temporal!

Un archivo de almacenaje temporal no pudo ser abierto. Aseg£rese de
tener al menos 80k de espacio libre en disco antes de ejecutar Sentry.


13.1.12 Error Leyendo Segmento de Datos! [Open]

Esto ocurre cuando los par metros de inicializaci¢n ¢ informaci¢n de
cuentas no est n actuando como se espera. Aseg£rese de tener al menos
80k de espacio libre en disco antes de ejecutar Sentry y que
Sentry.EXE no tenga activado el atributo SOLO-LECTURA.


13.1.13 Por favor ejecute INSTALL.EXE.

Esto normalmente indica que no existen los par metros de
inicializaci¢n. La forma m s sencilla de remediar esta situaci¢n es
instalar Sentry (vea la Secci¢n 2 para mayor detalle). Esto crear  los
par metros de inicializaci¢n o sobre escribir  los antiguos, si son
inv lidos.


13.1.14 Error Revisando Archivo Temporal!

Este error no debe de ocurrir jam s. Si sucediera, por favor
inf¢rmenos acerca del escenario dentro del cual ocurri¢.


13.1.15 Error en Informaci¢n de Cuentas!

Esto significa que hay un problema con la informaci¢n de cuenta de un
usuario. Usted puede ¢ tratar de restablecer su Sentry.EXE del
respaldo ¢ puede reinstalarlo (Vea la Secci¢n 2 para mayor
informaci¢n). Si usted continua usando informaci¢n corrupta,
encontrar  que se queda bloqueado muy frecuentemente. Debe de ser de
alta prioridad el corregir la informaci¢n de cuentas.


13.1.16 Error en Par metros de Inicializaci¢n!

Sus par metros de inicializaci¢n est n corruptos ¢ no pudieron ser
le¡dos. Su mejor opci¢n es reinstalar Sentry por completo y sobre
escribir los par metros actuales. Si usted encuentra que esto sucede
con frecuencia, rep¢rtelo a nosotros ya que probablemente sea un error
de programa.


13.1.17 Error Interno de Pantalla. (Lectura)

Este error no debe de ocurrir jam s. Dicho esto, si llegara a ocurrir,
usted debe de revisar su modo de v¡deo. Sentry ha sido probado  en
modo 80 x 25. Verifique que es el que est  siendo usado. Si el error
sucediera, favor de comunic rnoslo.


13.1.18 Error Interno de Pantalla. (Escritura)

Igual que el error anterior


13.1.19 Memoria Agotada!

Cuando este error aparece, significa que por alguna raz¢n Sentry no
tiene suficiente memoria para ejecutar. Esto es sumamente raro ya que
Sentry requiere muy poca. Si este error ocurriera, intente liberar
memoria reinicializando su m quina ¢ cerrando algunos programas en
uso.


13.1.20 Error de Registro - Programa Abortado!

Este error significa que la informaci¢n de registro no fue capturada
correctamente. Borre la copia de Sentry y reinstale. Este error no
sucede en la versi¢n Shareware.


13.1.21 Esta Cuenta Ha Expirado.

Mala Suerte. El Super Usuario ha hecho expirar su cuenta y ya expir¢.
Si usted ES el Super Usuario, qu‚ vergenza! (usted no debe permitir
que su cuenta expire). En cuyo caso, usted tendr  que restablecer
Sentry.EXE del respaldo y efectuar los cambios necesarios para que su
sistema vuelva a funcionar.


13.1.22 No Existe LICENCIA.TXT!

El archivo LICENCIA.TXT no se encontr¢ durante la instalaci¢n. Este
archivo debe de estar presente para la correcta instalaci¢n. Si no lo
tiene, lea la secci¢n 11.3 para saber d¢nde buscarlo.

13.1.23 Los Par metros de Inicializaci¢n son Antiguos!

Por alguna raz¢n sus par metros de inicializaci¢n no coinciden con la
versi¢n en uso de Sentry. La mejor soluci¢n es exportar los par metros
y reinstalar la versi¢n m s actualizada de Sentry.


13.1.24 Los Par metros de Inicializaci¢n son Nuevos!

Igual que el p rrafo anterior.


13.2 Otros problemas

Problema: Windows 95 manda el error Imposible localizar Ambiente
(CANNOT LOCATE ENVIRONMENT).

Algunos usuarios han reportado problemas al ejecutar Sentry bajo
Windows 95. El problema es que, cuando Sentry es ejecutado, el usuario
recibe un error IMPOSIBLE LOCALIZAR AMBIENTE (CANNOT LOCATE
ENVIRONMENT). La causa del error es que el .PIF no tiene el ambiente
inicial asignado correctamente. Hay una soluci¢n r pida y sencilla
para esto.

Primero, abra Explorador de Windows (Windows Explorer) y dir¡jase a su
directorio de Sentry. Haga click derecho sobre el archivo llamado
"Sentry.PIF" (Puede s¢lo llamarse "Sentry" pero, de cualquier manera,
se le reconoce por tener un icono de MS-DOS). Ahora seleccione del
men£ "Propiedades" (Properties) y, cuando abra la pantalla de
propiedades, haga click en "Memoria" (Memory). Ahora busque la
propiedad "Ambiente Inicial" (Initial Environment) en la caja llamada
"Memoria Convencional" (Conventional Memory) y cambie el valor de
"Auto" a cualquier otro valor. Inclusive un valor tan bajo como 256
puede llegar a funcionar pero usted puede requerir valores m s altos,
dependiendo del sistema.


Problema: Sentry est  ejecutando sumamente lento.

En algunas m quinas lo hace. Todo depende del procesador y disco duro.
Si desea hacerlo ejecutar m s r pido, intente utilizar una utiler¡a de
"disk caching" como Smart Drive. Alternativamente, usted puede
deshabilitar el par metro "Borrado de Seguridad" en los par metros de
Inicializaci¢n.


Problema: Instale Sentry, pero ahora mi computadora me pide nombre y
pasaporte cuando la arranco.

Si, esto es lo que hace Sentry. El valor por omisi¢n para nombre de
usuario (Login) y pasaporte es en ambos casos "Sentry". N¢tese el uso
de May£scula Inicial. RTFM


Problema: Cuando ejecuto Sentry, muestra un aviso que dice que tengo
nuevos / viejos par metros de inicializaci¢n.

Probablemente usted deba conseguir la nueva versi¢n de Sentry (vea la
secci¢n 11.3 para informaci¢n sobre c¢mo conseguirla). Reemplace todos
sus archivos con los nuevos. Este aviso puede no ser un problema en
s¡, de cualquier manera no es una buena idea usar par metros de
inicializaci¢n de versiones diferentes a la actual.


Problema: Recibo un aviso acerca de usuarios manipulados en la
bit cora.

Obviamente, alguien est  manipulando la bit cora. Este individuo crey¢
que pod¡a cambiar el acceso de Super Usuario en su m quina y no logr¢
hacerlo. El £nico efecto secundario es que algunos usuarios aparecer n
como si tuvieran acceso de Super Usuario sin realmente tenerlo (y
viceversa) cuando revisa el listado en el Men£ de Super Usuario. Los
accesos reales de los usuarios no han cambiado. Para remediar esta
situaci¢n usted puede hacer que el usuario cambie su pasaporte (s¢lo
haga expirar el actual). Tan pronto como el nuevo pasaporte sea
tecleado, el problema desaparecer .


Problema: No puedo accesar mi sistema.

Es usted un usuario en el sistema? Est n sus par metros de
inicializaci¢n correctos? Ha ejecutado el programa de instalaci¢n?


Problema: No puedo accesar como Super Usuario.

Se concedi¢ a s¡ mismo privilegios de Super Usuario? Est  usted
oprimiendo CTRL al momento de oprimir Enter?


Problema: Mi informaci¢n de cuentas est  corrupta o borrada.

Espero que tenga un respaldo a la mano. Al menos, usted debe de tener
el programa de instalaci¢n que recibi¢ con Sentry. En este caso,
reinstale Sentry y accese como "Sentry". Ya que Sentry es inicialmente
un Super Usuario, usted puede rehacer sus usuarios (No olvide borrar
la cuenta Sentry cuando termine).


Problema: No puedo crear un directorio c:\Sentry en mi m quina.

Si est  usando la utiler¡a de MS-DOS UNDELETE, ‚sta puede crear un
directorio llamado "Sentry" en el directorio ra¡z de su disco. Este
directorio tiene atributo "Oculto" (Hidden) y s¢lo puede ser visto con
el comando "dir /a" (Esto s¢lo ocurre si usted est  usando la opci¢n
"delete sentry"). Algunas soluciones son: Dejar de utilizar el modo
"delete sentry" ¢ crear el directorio en que va a residir Sentry con
un nombre distinto (ej: c:\Sentry2, c:\Secur\Sentry, etc etc).


14.0 Limitaci¢n de Responsabilidades
====================================

No se acepta ninguna responsabilidad por p‚rdida, da¤o ¢
inconveniencia causados directa ¢ indirectamente por ning£n material
contenido en este paquete.

Los usuarios inexpertos deben de tener cuidado con este programa ya
que pueden bloquear su acceso al sistema ¢ hacer peor da¤o que ese.

Si usted considera poder usarlo pero no se siente totalmente seguro,
deje una "puerta secreta" para usarla en caso extremo (ej: No
implemente todas las medidas de seguridad mencionadas en "Asegurando
su Computadora'), de manera que, si se queda usted bloqueado fuera de
su computadora, usted todav¡a tiene manera de entrar en ella. Una vez
que est‚ usted satisfecho de que todo funciona correctamente, cierre
tambi‚n esa puerta.

Por favor lea el documento titulado "LICENCIA.TXT" para todo lo
relacionado con este contrato..


15.0 Informaci¢n para Contactos
===============================

Cualquier comentario que tenga usted sobre este programa ser 
debidamente apreciado (Tanto si es positivo como si es negativo). Si
encuentra usted cualquier problema ¢ tiene alguna sugerencia para
hacerlo mejor, por favor h ganoslo saber y trataremos de incluirlo en
una siguiente versi¢n. Esperamos o¡r de ustedes.

Los contactos se pueden realizar por Internet mandando e-mail a:

info@cipherlogic.on.ca

Y se les responder  tan r pido como sea posible. Si no cuenta con
e-mail, usted puede contactarnos v¡a correo normal dirigi‚ndose a:

Cipher Logic Canada Inc.
PO Box 412
Munster, ON
K0A 3P0
Canada


16.0 Acerca del Autor
=====================

Mike Bobbitt es actualmente un Analista de Sistemas de C¢mputo para
Mott Community College en Flint, Michigan. Se grad£o de Acadia
University, donde obtuvo su t¡tulo de Ingeniero en Ciencias de la
Computaci¢n con Especializaci¢n en Programaci¢n. Sus intereses
principales giran en el  rea de seguridad computacional, que es en
parte el motivo para la creaci¢n de Sentry.



17.0 Cr‚ditos
===============

Mis agradecimientos para:

Todos los usuarios de Sentry, que lo han hecho popular por todo el
mundo.

Todos aquellos que han registrado su copia de Sentry, por su
honestidad.

Mark Saarinen, por la implementaci¢n del algoritmo crypt() de UNIX.

Richard Brittain, por el uso de su c¢digo de DOS para variables de
ambiente.

Dexter J. Caldwell, por sugerencias acerca de varias opciones,
incluyendo el m‚todo de machotes para protecci¢n de programas.

L.D. Best, por sugerencias, comentarios y reportes de errores as¡ como
explicaciones detalladas de situaciones de prueba. L.D. ha contribuido
muchas buenas ideas y comentarios £tiles con respecto a Sentry y ha
sido de invaluable asistencia en el ajuste de muchas opciones tales
como la protecci¢n de programas.

Bret Jacobsen, por encontrar serios errores en la primera versi¢n, as¡
como por continuamente hacer sugerencias para mejoras. Bret ha sido
una invaluable ayuda en el desarrollo de Sentry.

...Y a mi esposa, por escucharme hablar incesantemente acerca de ‚l.
