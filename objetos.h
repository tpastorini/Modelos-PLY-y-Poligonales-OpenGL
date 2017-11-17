#include <vertex.h>
#include <iostream>
#include <vector>
#include <file_ply_stl.h>

using namespace std;

class Objeto3D{
private: 
	vector<_vertex3f> vertices;
	vector<_vertex3i> triangulos;
	vector<_vertex2i> lados;
	vector<_vertex3f> colores;	// modificacion para examen P1

public:
	Objeto3D(int obj);	// Constructor para crear el cubo y la pirámide dependiendo de obj

	/* Creación de los objetos de la práctica */
	void CrearCubo(float lado);
	void CrearPiramide(float lado);
	void CrearTetraedro(float lado);
	void CrearObjetoConPLY(char* nombreArchivo);	// Carga los puntos del PLY
	void CrearDiavolo(float lado);	// defensa

	/* Métodos para generar por revolución */
	void Revolucion(int puntos);
	void Revolucion_puntos(vector<_vertex3f> puntos, int veces);
	void RevolucionDiavolo(int veces);

	_vertex3f aplicarTransformacionVertice_X(float angulo, _vertex3f v);
	_vertex3f aplicarTransformacionVertice_Y(float angulo, _vertex3f v);
	_vertex3f aplicarTransformacionVertice_Z(float angulo, _vertex3f v);
	/* ----------------------------------- */

	vector<_vertex3f> getVertices();
	vector<_vertex3i> getTriangulos();
	vector<_vertex2i> getLados();
	vector<_vertex3f> getColores();

	void rellenaVertices(vector<float> &verticesPLY);	// Pasa los vértices del PLY a vertex3f
	void rellenaCaras(vector<int> &carasPLY);			// Pasa los triángulos del PLY a vertex3f
	void rellenarLados();								// Rellena los lados para poder dibujar en modo línea
};