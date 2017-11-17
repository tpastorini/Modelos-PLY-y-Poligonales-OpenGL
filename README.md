# Modelos PLY y Poligonales OpenGL
Lectura de ficheros en formato PLY y modelado de objetos sólidos poligonales.

En este segundo proyecto tenemos dos objetivos a complir.

1. Leer modelos guardados en ficheros externos en formato PLY y la visualización de los mismos.
2. Modelas objetos sólidos poligonales de forma sencilla utilizando la técnica de modelado por revolución basado en un perfil y al rededor de un eje de rotación.

El perfil a modelar escogido es el de un peón de ajedrez y se hará el modelado por revolución sobre el eje de coordenadas Y.

El modelo ply escogido será el ant.ply, vértices que formar como objeto una hormiga en 3D.

Partiendo de la base presentada en https://github.com/tpastorini/Modelado-Sencillo-3D---OpenGL , añadiremos lo necesario para este proyecto. El contenido de estos ficheros se pueden añadir a la implementación que contiene el enlace anteriormente citado sin problemas, simplemente copiando su contenido donde corresponda en los ficheros anteriores.

Modificaciones:

1. En el fichero objetos.cc añadimos tres opciones 'case' más al contructor por parámetros. Una es para cargar el fichero PLY según una ruta completa que le demos, la siguiente es para, dado un fichero PLY, poder realizar la revolución en base al eje Y de los puntos del perfil de ese fichero.

2. En el fichero objetos.cc, añadimos el método que nos hace falta para generar el objeto3D por revolución. Tendremos el que realiza la revolución en función del eje Y, pudiendose cambiar el eje de rotación utilizando cualquiera de los métodos destinados a generar la rotación en función del eje que queramos en ese momento. Dada nuestra implementación de la clase que modela los objetos, debemos añadir tres métodos adicionales para que conviertan los valores de los vértices, triángulos y lados a nuestros vectores de la clase Objeto3D.

3. En el fichero objetos.cc también añadimos el método necesario para cargar la información de un fichero ply a nuestro objeto de la clase objeto3D.

Los modos de visualización se mantienen.
