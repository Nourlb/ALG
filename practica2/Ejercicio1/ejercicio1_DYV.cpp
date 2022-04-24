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
  @brief Función que, dado un vector con n elementos, busca si existe un ínidce i tal que v[i] = i y devuelve dicha posición (Versión Divide y Vencerás).
  @param v[] vector de enteros
  @param l posición de la primera componente del vector
  @param r posición de la última componente del vector
  
*/

/*
int buscaIgualIndiceDYV (const vector<int> v, int l, int r)
{
    
   int i = -1;
   int indexl, indexr;
   
   
    if(l<=r) {
        if (r - l <= 1) {
            if (v[l] == l){
            	i= l;
            }
            else if (v[r] == r){
            	i= r;
             }
             else if ((v[l] == l) && (v[r] == r)){
             	i = l; // por convenio
             }
        }
        else
        {
           int m    = (l + r)/2;
           indexl = buscaIgualIndiceDYV(v, l, m);
           indexr = buscaIgualIndiceDYV(v, m + 1, r);
           
           if ((indexl == -1) && (indexr != -1)) i = indexr;
     	   else
     	   {
     	      if ((indexr == -1) && (indexl != -1)) i = indexl;
     	      else
     	   	 if ((indexl != -1) && (indexr != -1)) i = indexl; // por convenio
     	   }
          
         }
     }
    
     return i;
}
*/

int buscaIgualIndiceDYV (const vector<int> v, int l, int r)
{
   
   if ((l > r) || (l<0) || (r > v.size())) return -1;
   if (l == r){
   	if (v[l] == l) return l;
   	else return -1;
   }
   else{
   	int m = (l+r)/2;
   	
   	if (m == v[m]) return m;
   	
   	else{
   	     return buscaIgualIndiceDYV(v, l, m);
   	     return buscaIgualIndiceDYV(v, m+1, r);
   	 }
   	
   }       
   
}



/*int buscaIgualIndiceDYV (vector<int> v, int a, int b) {

    int m = (a+b)/2;
   
    if ((b - a) < 1) return -1;
    if (v[a] == a) return a;
    else if (v[b] == b) return b;
    else if (v[b] != b && v[a] != a){
    	return buscaIgualIndiceDYV(v, a, m);
    	return buscaIgualIndiceDYV(v,m+1,b);
    } 
}

*/

// Programa principal

int main(int argc, char * argv[])
{

	if (argc != 2)
	{
	   cerr << "Formato " << argv[0] << " <num_elem>" << endl;
	   return -1;
	}

   int n = atoi(argv[1]);
   vector <int> v = {-1,0,3,4,5,6,7,8,8};
   int l = 0;
   int r = 8;


/*
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
	
	delete [] aux;
	delete [] T;

	//for (it=myvector.begin(); it!=myvector.end(); ++it)
	 //cout << " " << *it;

	high_resolution_clock::time_point tantes, tdepues;
	duration<double> transcurrido;

	int indice_buscado,l,r;
	l = 0;
	r = n-1;
*/
	// Aplicamos la función buscaIgualIndice y medimos tiempos
	//tantes = high_resolution_clock::now();

	//int indice_buscado = 
	
	int indice = buscaIgualIndiceDYV(v,l,r);

	//tdepues = high_resolution_clock::now();

	//transcurrido = duration_cast<duration<double>>(tdepues - tantes);

	//time_total += transcurrido.count();
	
	cout << endl;
	if ((indice == -1)) cout << "Elemento no encontrado" << endl;
	else cout << "Indice: " << indice << " elemento:"<< v[indice]<< endl;
	
       // cout << n << " " << time_total << endl;

	
return 0;

}
