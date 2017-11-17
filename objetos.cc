#include <objetos.h>
#include <cmath>

using namespace std;

Objeto3D::Objeto3D(int obj){

	switch(obj){
		case 1:
			CrearPiramide(1);
			break;
		case 2:
			CrearCubo(1);
			break;
		case 3:			// Cargo el ply correspondiente a la hormiga
			CrearObjetoConPLY("/media/tatiana/DATA/IG/Prácticas/practica2/read_ply/ant.ply");	
			break;
		case 4:
			CrearObjetoConPLY("/media/tatiana/DATA/IG/Prácticas/practica2/read_ply/perfil_st.ply");
			Revolucion(50);
			break;
	}
}


void Objeto3D::RevolucionDiavolo(int puntos){

	int tInf=-1,tSup=-1;
   	double angulo=(2*M_PI)/puntos, radianes;
   	vector <_vertex3f> eje_x(puntos);
    _vertex3f puntoDeEngancheTS,puntoDeEngancheTI; 
  	vector <_vertex3f> punt_a_rep(this->vertices.size());
  	int c=0, p1=(int)puntos;
    int radi, prueba=0;

    for(int i=0;i<(int)this->vertices.size();i++){
        if(this->vertices[i].x==0){
            eje_x[c].x=0;
            eje_x[c].y=this->vertices[i].y;
            eje_x[c].z=this->vertices[i].z;
             
            if(this->vertices[i].y<0){
                if(i==(int)this->vertices.size()-1){
                    puntoDeEngancheTI.x=this->vertices[i-1].x;
                    puntoDeEngancheTI.y=this->vertices[i-1].y;
                    puntoDeEngancheTI.z=this->vertices[i-1].z;
                }else{                     
                    puntoDeEngancheTI.x=this->vertices[i+1].x;
                    puntoDeEngancheTI.y=this->vertices[i+1].y;
                    puntoDeEngancheTI.z=this->vertices[i+1].z;
                }
            }else {
                if(i==(int)this->vertices.size()-1){
                    puntoDeEngancheTS.x=this->vertices[i-1].x;
                    puntoDeEngancheTS.y=this->vertices[i-1].y;
                    puntoDeEngancheTS.z=this->vertices[i-1].z;
                }else{
                    puntoDeEngancheTS.x=this->vertices[i+1].x;
                    puntoDeEngancheTS.y=this->vertices[i+1].y;
                    puntoDeEngancheTS.z=this->vertices[i+1].z;
                }                     
            }
             
            c++;
        }else {
            punt_a_rep[i-c].x=this->vertices[i].x;
            punt_a_rep[i-c].y=this->vertices[i].y;
            punt_a_rep[i-c].z=this->vertices[i].z;   
        }
    }
    eje_x.resize(c);
     
    punt_a_rep.resize(this->vertices.size()-c);
    vector<_vertex3f> v2((punt_a_rep.size()*puntos)+c);
    int c2=0, i=0;

    while(i<v2.size()-c){
        if(i % p1 == 0){ 
            v2[i].x=punt_a_rep[c2].x;
            v2[i].y=punt_a_rep[c2].y;
            v2[i].z=punt_a_rep[c2].z;
            if( v2[i].x== puntoDeEngancheTI.x &&
                v2[i].y== puntoDeEngancheTI.y
                && v2[i].z==puntoDeEngancheTI.z){
                  
                tInf=i;
            }else if( v2[i].x== puntoDeEngancheTS.x &&
                v2[i].y== puntoDeEngancheTS.y
                && v2[i].z==puntoDeEngancheTS.z){
                
                tSup=i;
            }
            
            c2++;

            }else { 
                angulo=360/puntos;
                angulo= (i%p1)*angulo;
                radianes=angulo * M_PI/180;
                v2[i].x=punt_a_rep[c2-1].x*cos(radianes)+punt_a_rep[(c2-1)].z*sin(radianes);                   
                v2[i].y=punt_a_rep[(c2-1)].y;
                v2[i].z=-punt_a_rep[c2-1].x*sin(radianes)+punt_a_rep[(c2-1)].z*cos(radianes);
            }

            i++;
     	}

     	this->triangulos.resize(v2.size()*c2);
     	int p=0, b=0, filas=(puntos)*punt_a_rep.size();
    	for(int f=0;p<v2.size()-puntos-c;f++,p++){
            this->triangulos[p]._0=f;
            this->triangulos[p]._1=f+puntos;
            if((f+(int)puntos+1)%(int)puntos==0){
                 
                this->triangulos[p]._2=f+puntos+1-(puntos);
            }else this->triangulos[p]._2=f+puntos+1;
    }
     
    for(int f=0;f<v2.size()-puntos-c;f++,p++){ 
        this->triangulos[p]._0=f;
        if((f+1)%(int)puntos==0){
            this->triangulos[p]._1=f-(puntos-1);
        }else this->triangulos[p]._1=f+1;
        if((f+(int)puntos+1)%(int)puntos==0){
            this->triangulos[p]._2=f+puntos+1-(puntos);
        }else this->triangulos[p]._2=f+puntos+1;
    }

    if(tSup!=-1 || tInf!=-1){
		b=p;
		p=0;
        this->triangulos.resize(this->triangulos.size()+(puntos*c));
        for(int i2=i,c3=0;i2<v2.size() && c3<eje_x.size();i2++,c3++){
            if(eje_x[c3].y>0){
                for(;p<(puntos)&&tSup!=-1;p++,b++){
                    this->triangulos[b]._0=i2;
                    this->triangulos[b]._1=tSup+p;

                    if(tSup+p+1==puntos){
                        this->triangulos[b]._2=tSup;
                    }else  
                    	this->triangulos[b]._2=tSup+1+p;    
                }
            }else{
                for(p=0;p<(puntos)&&tInf!=-1;p++,b++){
                    this->triangulos[b]._0=i2;
                    this->triangulos[b]._1=tInf+p;

                    if(tInf+p+1==puntos*2){
                        this->triangulos[b]._2=tInf;
                    }else
                    	this->triangulos[b]._2=tInf+1+p;   
                }
            }
            v2[i2].x=eje_x[c3].x;
            v2[i2].y=eje_x[c3].y;
            v2[i2].z=eje_x[c3].z;
        }
    }
    this->vertices=v2;v2.clear(); punt_a_rep.clear();
    eje_x.clear();

   	rellenarLados();
}


// Le paso el número de veces que voy a rotar cada punto
void Objeto3D::Revolucion(int veces){

	vector<_vertex3f> vertices_auxiliares = vertices;   // Vertices finales le hago una copia antes de transformarlos

	float angulo = (2*M_PI)/veces;
	_vertex3f aux;
	_vertex3i cara;

  	for(int i=0; i<veces; i++){ // Todas las veces que tengo que rotar un mismo punto

	    for(int j=0; j<vertices_auxiliares.size(); j++){
	      	_vertex3f a = vertices_auxiliares[j];
	     	aux = aplicarTransformacionVertice_Y(angulo,a);
	     	vertices.push_back(aux);
	     	vertices_auxiliares[j] = aux;   // guardo el nuevo vertice para usarlo al calcular otro nuevo
	    }

	    // recorro los perfiles para ir uniéndolos y formando las caras

	    unsigned int inicioPerfil, finPerfil;
	    inicioPerfil = i * vertices_auxiliares.size();
	    finPerfil = inicioPerfil + vertices_auxiliares.size();

	    for (unsigned int i = inicioPerfil+1, j = finPerfil+1; i < finPerfil; i++, j++){

			cara._0=i-1;
			cara._1=j-1;
			cara._2=j;
			triangulos.push_back(cara);

			cara._0=i-1;
			cara._1=j;
			cara._2=i;
			triangulos.push_back(cara);
	    			
	    }
	}

    if (vertices.front().x){ // si la coord X=0, x toca el eje Y y por tanto no necesita tapa
		// Agregamos el punto central, aunque no es necesario porque solo pintamos las caras
		_vertex3f centro;
		_vertex3i inferior;
		centro.x=0.0;
		centro.y=vertices.front().y;
		centro.z=0.0;
		vertices.push_back(centro);

		for (int cnt = 0; cnt < veces; cnt++){
			int perfilactual = cnt * vertices_auxiliares.size();
			int siguientePerfil = perfilactual + vertices_auxiliares.size();
			inferior._0=vertices.size()-1;
			inferior._1=siguientePerfil;
			inferior._2=perfilactual;
			triangulos.push_back(inferior);
		}
    }

    if (vertices[vertices_auxiliares.size()-1].x){
     	//Añadimos el punto central de arriba

     	_vertex3f centro1;
    	_vertex3i superior;

     	centro1.x=0.0;
     	centro1.y=vertices[vertices_auxiliares.size()-1].y;
     	centro1.z=0.0;
     	vertices.push_back(centro1);

     	//Añadimos las caras de la tapa superior

		for (int cnt =0; cnt < veces; cnt++){
			int perfilactual = (cnt+1) * vertices_auxiliares.size()-1;
			int siguientePerfil = perfilactual + vertices_auxiliares.size();
			superior._0=vertices.size()-1;
			superior._1=perfilactual;
			superior._2=siguientePerfil;
			triangulos.push_back(superior);
		}
	}

   	rellenarLados();

}


void Objeto3D::Revolucion_puntos(vector<_vertex3f> puntos, int veces){
	vertices = puntos;

	vector<_vertex3f> vertices_auxiliares = vertices;   // Vertices finales le hago una copia antes de transformarlos

	float angulo = (2*M_PI)/veces;
	_vertex3f aux;
	_vertex3i cara;

	for(int i=0; i<veces; i++){ // Todas las veces que tengo que rotar un mismo punto

		for(int j=0; j<vertices_auxiliares.size(); j++){
			_vertex3f a = vertices_auxiliares[j];
			aux = aplicarTransformacionVertice_Y(angulo,a);
			vertices.push_back(aux);
			vertices_auxiliares[j] = aux;   // guardo el nuevo vertice para usarlo al calcular otro nuevo
		}

		unsigned int inicioPerfil, finPerfil;
		inicioPerfil = i * vertices_auxiliares.size();
		finPerfil = inicioPerfil + vertices_auxiliares.size();

		for (unsigned int i = inicioPerfil+1, k = finPerfil+1; i < finPerfil; i++, k++){
			cara._0 = i-1;
			cara._1 = k-1;
			cara._2 = k;
			triangulos.push_back(cara);
			cara._0 = i-1;
			cara._1 = k;
			cara._2 = i;
			triangulos.push_back(cara);
		}
	}

	if (vertices.front().x){ // si la coord X=0, x toca el eje Y y por tanto no necesita tapa
		// Agregamos el punto central, aunque no es necesario porque solo pintamos las caras
		_vertex3f centro;
		_vertex3i inferior;
		centro.x = 0.0;
		centro.y = vertices.front().y;
		centro.z = 0.0;
		vertices.push_back(centro);

		for (int cnt = 0; cnt < veces; cnt++){
			int perfilactual = cnt * vertices_auxiliares.size();
			int siguientePerfil = perfilactual + vertices_auxiliares.size();
			inferior._0 = vertices.size()-1;
			inferior._1 = siguientePerfil;
			inferior._2 = perfilactual;
			triangulos.push_back(inferior);
		}
	}

	if (vertices[vertices_auxiliares.size()-1].x){
		//Añadimos el punto central de arriba

		_vertex3f centro1;
		_vertex3i superior;

		centro1.x = 0.0;
		centro1.y = vertices[vertices_auxiliares.size()-1].y;
		centro1.z = 0.0;
		vertices.push_back(centro1);

		//Añadimos las caras de la tapa superior

		for (int cnt =0; cnt < veces; cnt++){
			int perfilactual = (cnt+1) * vertices_auxiliares.size()-1;
			int siguientePerfil = perfilactual + vertices_auxiliares.size();
			superior._0 = vertices.size()-1;
			superior._1 = perfilactual;
			superior._2 = siguientePerfil;
			triangulos.push_back(superior);
		}
	}

	rellenarLados();

}


// Devuelve la transformación del vertice V en el eje X
_vertex3f Objeto3D::aplicarTransformacionVertice_X(float angulo, _vertex3f v){
	_vertex3f nuevoPunto;

	nuevoPunto.x = cos(angulo)*v.x + sin(angulo)*v.z;
	nuevoPunto.y = v.y;
	nuevoPunto.z = -sin(angulo)*v.x + cos(angulo)*v.z;

   return nuevoPunto;
}


// Devuelve la transformación del vertice V en el eje Y
_vertex3f Objeto3D::aplicarTransformacionVertice_Y(float angulo, _vertex3f v){
	_vertex3f nuevoPunto;

	nuevoPunto.x = cos(angulo)*v.x + sin(angulo)*v.z;
	nuevoPunto.y = v.y;
	nuevoPunto.z = -sin(angulo)*v.x + cos(angulo)*v.z;

   return nuevoPunto;
}


// Devuelve la transformación del vertice V en el eje Z
_vertex3f Objeto3D::aplicarTransformacionVertice_Z(float angulo, _vertex3f v){
	_vertex3f nuevoPunto;

	nuevoPunto.x = cos(angulo)*v.x -sin(angulo)*v.y;
	nuevoPunto.y = sin(angulo)*v.x + cos(angulo)*v.y;
	nuevoPunto.z = v.z;

	return nuevoPunto;
}

/*******************************
			DEFENSA
*******************************/

void Objeto3D::CrearDiavolo(float lado){
	vertices.resize(3);
	colores.resize(5);

	vertices[0].x = 0.5;
	vertices[0].y = lado;
	vertices[0].z = 0.5;

	vertices[1].x = 0.5;
	vertices[1].y = 0;
	vertices[1].z = 0.5;

	vertices[2].x = 0.5;
	vertices[2].y = -lado;
	vertices[2].z = 0.5;

	colores[0].r = 1;
	colores[0].g = 0;
	colores[0].b = 1;

	colores[1].r = 0;
	colores[1].g = 0.5;
	colores[1].b = 0.5;

	colores[2].r = 1;
	colores[2].g = 1;
	colores[2].b = 0;

	colores[3].r = 0;
	colores[3].g = 0;
	colores[3].b = 0;

	colores[4].r = 0.1;
	colores[4].g = 0.9;
	colores[4].b = 0.8;

}

/*******************************
	       FIN DEFENSA
*******************************/

void Objeto3D::CrearObjetoConPLY(char* nombreArchivo){
	_file_ply ply;

	// Vectores temporales para los vértices y triángulos
	vector<float> vertices_ply;
	vector<int> triangulos_ply;

	ply.open(nombreArchivo);					// abro el archivo ply
	ply.read(vertices_ply, triangulos_ply);		// leo los vértices y triángulos y los guardo
	ply.close();								// cierro el archivo

	// Ahora tengo que meter los vértices y triángulos recién guardados en unos vectores
	// pertenecientes a la clase "objetos", para luego poder tener los métodos de dibujo, etc

	vertices.resize(vertices_ply.size()/3);
	triangulos.resize(triangulos_ply.size()/3);

	rellenaVertices(vertices_ply);
	rellenaCaras(triangulos_ply);
	rellenarLados();
}

void Objeto3D::rellenaVertices(vector<float> &verticesPLY){
	int i=0;
	for(int j=0; j < verticesPLY.size(); j+=3){
		vertices[i].x = verticesPLY[j];
		vertices[i].y = verticesPLY[j+1];
		vertices[i].z = verticesPLY[j+2];

		i++;
	}

}

void Objeto3D::rellenaCaras(vector<int> &carasPLY){
	int i=0;
	for(int j=0; j < carasPLY.size(); j+=3){
		triangulos[i]._0 = carasPLY[j];
		triangulos[i]._1 = carasPLY[j+1];
		triangulos[i]._2 = carasPLY[j+2];

		i++;
	}

}

void Objeto3D::rellenarLados(){
    lados.resize(triangulos.size()*3);
    int j = 0;

    for (int i = 0; i < triangulos.size(); i++) {
        lados[j]._0 = triangulos[i]._0;
        lados[j++]._1 = triangulos[i]._1;

        lados[j]._0 = triangulos[i]._1;
        lados[j++]._1 = triangulos[i]._2;

        lados[j]._0 = triangulos[i]._2;
        lados[j++]._1 = triangulos[i]._0;
    }
}

vector<_vertex3f> Objeto3D::getVertices(){
	return vertices;
}

vector<_vertex3i> Objeto3D::getTriangulos(){
	return triangulos;
}

vector<_vertex2i> Objeto3D::getLados(){
	return lados;
}

vector<_vertex3f> Objeto3D::getColores(){
	return colores;
}