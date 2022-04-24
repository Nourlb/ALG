#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std::chrono;

// generador de ejemplos para el problema del elemento en su posici�n. Para rellenar el vector de tama�o n, genera todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; despu�s obtiene una permutaci�n aleatoria de ese vector, se queda con los n primeros elementos, y los ordena de forma creciente

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

/**
  @brief Función que, dado un vector con n elementos, busca si existe un ínidce i tal que v[i] = i y devuelve dicha posición.
  @param v[] vector de enteros
  @param n número de elementos
  
*/


int buscaIgualIndice (const vector<int> v)
{
    bool continua = true;
    int index = -1;
    
    for (int i = 0; i < v.size() && continua; i++){
    	if (v[i] == i){
          index = i;
          continua = false;
        }
    }

    return index;         
}

// Programa principal

int main(int argc, char * argv[])
{

	if (argc != 2)
	{
	cerr << "Formato " << argv[0] << " <num_elem>" << endl;
	return -1;
	}

	int n = atoi(argv[1]);
	double time_total = 0;
	int m=2*n-1;

	int * T = new int[n];
	assert(T);
	int * aux = new int[m];
	assert(aux);

	srand(time(0));
 
	//genero todos los enteros entre -(n-1) y n-1
	for (int j=0; j<m; j++) aux[j]=j-(n-1);

	//algoritmo de random shuffling the Knuth (permutaci�n aleatoria) 
	for (int j=m-1; j>0; j--) {
	   double u=uniforme();
	   int k=(int)(j*u);
	   int tmp=aux[j];
	   aux[j]=aux[k];
	   aux[k]=tmp;
	}
	//me quedo con los n primeros del vector
	for (int j=0; j<n; j++) T[j]=aux[j];
	//for (int j=0; j<n; j++) cout << T[j] << " ";

	//Y ahora ordeno el vector T
	vector<int> myvector (T, T+n);
	vector<int>::iterator it;

	sort(myvector.begin(),myvector.end());

	//for (it=myvector.begin(); it!=myvector.end(); ++it)
	  // cout << " " << *it;
	high_resolution_clock::time_point tantes, tdepues;
	duration<double> transcurrido;
	int indice_buscado;

	// Aplicamos la función buscaIgualIndice
	tantes = high_resolution_clock::now();

	indice_buscado = buscaIgualIndice(myvector);

	tdepues = high_resolution_clock::now();

	transcurrido = duration_cast<duration<double>>(tdepues - tantes);

	time_total += transcurrido.count();
	/*if (indice_buscado == -1) cout << "Elemento no encontrado" << endl;
	else cout << "Indice: " << indice_buscado << " elemento:"<< myvector[indice_buscado]<< endl;*/

	
	cout << n << " " << time_total << endl;
  
	delete [] aux;

}
