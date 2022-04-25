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
  @brief Función que, dado un vector con n elementos distintos todos dos a dos, busca si existe un ínidce i tal que v[i] = i y devuelve dicha posición (Versión Divide y Vencerás).
  @param v[] vector de enteros
  @param izda posición de la primera componente del vector
  @param dcha posición de la última componente del vector
  
*/

int buscaIgualIndiceDYV (vector<int> v) {  // Versión en la que no puede haber   
                                           // elementos repetidos
    int izda = 0;
    int dcha = v.size()-1;
    int half = 0;


    while (izda <= dcha){
    	half = (izda+dcha)/2;
    	if (v[half] > half) dcha = half-1;
    	else if (v[half] < half) izda = half+1;
    	else return half;
    }
	
    return -1;      
}


// Programa principal

int main(int argc, char * argv[])
{

	if (argc != 2)
	{
	   cerr << "Formato " << argv[0] << " <num_elem>" << endl;
	   return -1;
	}
	
/*
   int n = atoi(argv[1]);
   vector <int> v = {-2,-1,0,1,2,3,4,6,8};
   int l = 0;
   int r = 8;
  */
  
	int n = atoi(argv[1]);
	double time_total = 0;

	srand(time(0));
	
  for (int i = 0; i < 15; i++){
  
  	int m=2*n-1;

	int * T = new int[n];
	assert(T);
	int * aux = new int[m];
	assert(aux);
		
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
	
	delete [] aux;
	delete [] T;

	//for (it=myvector.begin(); it!=myvector.end(); ++it)
	  //cout << " " << *it;

	high_resolution_clock::time_point tantes, tdepues;
	duration<double> transcurrido;

	int indice_buscado; 
	

	// Aplicamos la función buscaIgualIndice y medimos tiempos
	tantes = high_resolution_clock::now();
	
	indice_buscado = buscaIgualIndiceDYV(myvector);

	tdepues = high_resolution_clock::now();

	transcurrido = duration_cast<duration<double>>(tdepues - tantes);

	time_total += transcurrido.count();
   }
   
   	time_total /= 15;
	
	/*cout << endl;
	if ((indice_buscado == -1)) cout << "Elemento no encontrado" << endl;
	else cout << "Indice: " << indice_buscado << " elemento:"<< v[indice_buscado]<< endl;
	*/
	
        cout << n << " " << time_total << endl;

	
return 0;

}
