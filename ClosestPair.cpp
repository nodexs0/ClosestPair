//Programa para determinar el par de puntos mas cercanos en un plano
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

// A structure to represent a Point in 2D plane

// ! Estrcutura que representa un punto en un plano 2d
struct Point
{
	int x, y;
};

/// Following two functions are needed for library function qsort().
/// Refer: http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/

// Needed to sort array of points according to X coordinate

//* Funcion que comprar 2 puntos segun su coordenada X
// ? const void* puntero a una ubicación de memoria que contiene datos cuyo tipo concreto no se especifica de manera explícita
int compareX(const void* a, const void* b)
{
	// ? Conversión de tipo llamada "casting". 
	// ? la conversión de tipo es necesaria porque qsort espera punteros genéricos
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	// ? p1->x Esto accede al campo x de la estructura Point a la que apunta el puntero
	// ? p1->y Esto accede al campo y de la estructura Point a la que apunta el puntero
	// ! p1->x - p2->x calcula la diferencia entre las coordenadas X de dos puntos
	return (p1->x - p2->x);
}

// Needed to sort array of points according to Y coordinate
//* Funcion que comprar 2 puntos segun su coordenada Y
int compareY(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	// ! p1->x - p2->x calcula la diferencia entre las coordenadas y de dos puntos
	return (p1->y - p2->y);
}

// A utility function to find the distance between two points
// * Calcula la distancia Euclidiana entre dos puntos en un plano 2D.
float dist(Point p1, Point p2)
{
	// ? (p1.x - p2.x) obtiene la diferencia horizontal entre los puntos en x
	// ? (p1.x - p2.x)*(p1.x - p2.x) eleva al cuadrado la diferencia horizontal entre los puntos
	// ? La suma de los cuadrados de las diferencias horizontales y verticales es la distancia euclidiana al cuadrado
	// ? sqrt() distancia euclidiana real
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
				(p1.y - p2.y)*(p1.y - p2.y)
			);
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n

// * Fuerza bruta
float bruteForce(Point P[], int n)
{
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (dist(P[i], P[j]) < min)
				min = dist(P[i], P[j]);
	return min;
}

// A utility function to find a minimum of two float values
float min(float x, float y)
{	
	// ? (x < y)? x : y; es un operador ternario
	// ? Si x < y entonces devuelve x, sino devuelve y
	return (x < y)? x : y;
}


// A utility function to find the distance between the closest points of
// strip of a given size. All points in strip[] are sorted according to
// y coordinate. They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 6 times

// * Funcion que calcula la distancia minima entre los puntos de la tira
// * puntos que están a una distancia horizontal menor o igual a d 
// * d es el punto medio de una división en el algoritmo de búsqueda del par de puntos más cercanos en un plano 2D

float stripClosest(Point strip[], int size, float d)
{
	// * Distancia mínima que se conoce
	float min = d; // Initialize the minimum distance as d

	// ? Ordena los puntos de la tira según su coordenada Y
	// ? Esto es necesario para que los puntos estén en orden creciente según sus coordenadas Y 
	// ? antes de realizar el proceso de búsqueda de la distancia mínima.
	qsort(strip, size, sizeof(Point), compareY);


	// Pick all points one by one and try the next points till the difference
	// between y coordinates is smaller than d.
	// This is a proven fact that this loop runs at most 6 times

	//todo: No entiendo esta parte

	// ? Pares de puntos cuya diferencia en coordenadas Y es menor que la distancia mínima actual min
	// ? Si encuentra un par de puntos cuya distancia es menor que min, actualiza el valor de min con esa distancia
	// ? lo que representa la distancia mínima en la tira.

	// ? recorre cada punto en la tira, donde size es la cantidad total de puntos en la tira.
	for (int i = 0; i < size; ++i)


		// ? j = i + 1 - Itera a través de los puntos en la tira a partir del siguiente punto después de i
		// ? j < size - Itera hasta el final de la tira
		// ? (strip[j].y - strip[i].y) < min - Verifica si la distancia entre los puntos es menor que la distancia mínima actual

		//todo: Seria como:
		//todo: for (int j = i+1; j < size; ++j)
		//todo: 	for (int j = i+1; j < n; ++j)
		//todo: 		if (dist(P[i], P[j]) < min)
		//todo: 			min = dist(P[i], P[j]);


		//todo: El objetivo de && (strip[j].y - strip[i].y) < min
		//todo: Es evita calcular la distancia entre todos los puntos de la tira
		//todo: Esto lo hace eficiente
		for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
			// ? Calcula la distancia entre los puntos

			// ! No se puede guardar la distancia en una variable y compararla con min?
			// ! Evitaria calcular la distancia 2 veces
			if (dist(strip[i],strip[j]) < min)
				// ? Actualiza la distancia mínima
				min = dist(strip[i], strip[j]);

	// ? Devuelve la distancia mínima
	return min;
}

// A recursive function to find the smallest distance. The array P contains
// all points sorted according to x coordinate

// * Funcion recursiva que encuentra la distancia minima
// * Divide y Vencerás
float closestUtil(Point P[], int n)
{
	// If there are 2 or 3 points, then use brute force
	// * umbral
	// * si n es menor o igual al umbral, entonces se usa fuerza bruta
	if (n <= 3)
		return bruteForce(P, n);

	// Find the middle point
	// ? mitad
	int mid = n/2;
	// ? Punto medio 
	Point midPoint = P[mid];

	// Consider the vertical line passing through the middle point
	// calculate the smallest distance dl on left of middle point and
	// dr on right side

	// ? Llamada recursiva
	// ? mitad izquierda del conjunto de puntos 
	// ? (P desde el principio hasta mid)
	// ? Se almacena la distancia mínima en dl
	float dl = closestUtil(P, mid);

	// ? Llamada recursiva
	// ? mitad derecha del conjunto de puntos
	// ? (P desde mid hasta el final)
	// ? Se almacena la distancia mínima en dr
	float dr = closestUtil(P + mid, n-mid);

	// Find the smaller of two distances
	// ? distancia mínima entre los puntos en el conjunto completo.
	float d = min(dl, dr);

	// Build an array strip[] that contains points close (closer than d)
	// to the line passing through the middle point
	// ? conjunto de puntos "strip" de n elementos
	Point strip[n];
	int j = 0;
	// ? itera a través de todos los puntos en el conjunto de puntos P n que es el número total de puntoss
	for (int i = 0; i < n; i++)
		// ? abs(P[i].x - midPoint.x) < d - Verifica si la distancia entre el punto y el punto medio es menor que la distancia mínima actual
		// ? El valor absoluto garantiza que esta diferencia sea siempre positiva
		// ? Permite que la condición if verifique si el punto está lo suficientemente cerca del punto medio en cualquier dirección horizontal
		if (abs(P[i].x - midPoint.x) < d)
			// ? Si el punto está lo suficientemente cerca del punto medio, se agrega a la tira
			strip[j] = P[i], j++;

	// Find the closest points in strip. Return the minimum of d and closest
	// distance is strip[]
	// ? Devuelve la distancia mínima entre los puntos en la tira
	return min(d, stripClosest(strip, j, d) );
}

// The main function that finds the smallest distance
// This method mainly uses closestUtil()
// * Funcion principal que encuentra la distancia minima
float closest(Point P[], int n)
{	

	qsort(P, n, sizeof(Point), compareX);

	// Use recursive function closestUtil() to find the smallest distance
	return closestUtil(P, n);
}


// ? Invoca a la función recursiva closestUtil para encontrar la distancia mínima entre los puntos en el array P

// ? Ordena los puntos en P de sus coordenadas X

	// ? P: Este es el primer argumento y representa el array de puntos que se desea ordenar
	//? En este caso, P es el array de puntos que se quiere ordenar según sus coordenadas X.

	// ? n: El segundo argumento indica el número de elementos en el array P
	// ? En este caso, n representa la cantidad total de puntos en el array.

	// ? El tercer argumento, sizeof(Point), indica el tamaño de cada elemento en el array P
	// ? sizeof(Point) se utiliza para indicar a la función qsort el tamaño de cada elemento en el array.

	// ? compareX: El cuarto argumento es un puntero a una función de comparación
	// ? En este caso, compareX es una función que se utiliza para comparar dos elementos del array y determinar el orden en el que deben estar dispuestos
	// ? La función compareX compara los elementos en función de sus coordenadas X.

	// ?  la función compareX se utiliza como una función de comparación personalizada que proporciona a qsort para 
	// ? determinar el orden en el que se deben organizar los elementos del array P en función de sus coordenadas X
	// ? Esto permite que la función qsort ordene los puntos de acuerdo con un criterio específico, en este caso, en función de sus coordenadas X.
// Driver program to test above functions
int main()
{
	Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
	int n = sizeof(P) / sizeof(P[0]);
	printf("The smallest distance is %f ", closest(P, n));
	return 0;
}