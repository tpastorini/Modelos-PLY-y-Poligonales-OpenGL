# Modelos PLY y Poligonales OpenGL
Lectura de ficheros en formato PLY y modelado de objetos sólidos poligonales.

En este segundo proyecto tenemos dos objetivos a complir.

1. Leer modelos guardados en ficheros externos en formato PLY y la visualización de los mismos.
2. Modelas objetos sólidos poligonales de forma sencilla utilizando la técnica de modelado por revolución basado en un perfil y al rededor de un eje de rotación.

El perfil a modelar escogido es el de un peón de ajedrez y se hará el modelado por revolución sobre el eje de coordenadas Y.

El modelo ply escogido será el ant.ply, vértices que formar como objeto una hormiga en 3D.

Partiendo de la base presentada en https://github.com/tpastorini/Modelado-Sencillo-3D---OpenGL , añadiremos lo necesario para este proyecto sin tener duplicados. Estos ficheros se pueden añadir a la implementación que contiene el enlace anteriormente citado sin problemas.

Modificaciones:

1. En el fichero objetos.cc añadimos tres opciones 'case' más. Una es para cargar el fichero PLY según una ruta completa que le demos, la siguiente es para, dado un fichero PLY, poder realizar la revolución en base al eje Y de los puntos del perfil de ese fichero. El fichero objetos.h quedaría con el método como sigue:

Objeto3D::Objeto3D(int obj){
   switch(obj){
      case 1:
         break;
      case 2:
         break;
      case 3:
         break;
      case 4:
         break;
      case 5:
         break;
