#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <assert.h>

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tama�o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tama�o n para obtener los k vectores. Est�n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}


int * mezcla_FB(int numVectores, int numElementos, int ** m){
	int * fusion = nullptr;
	fusion = new int [numVectores * numElementos];
	
	bool found;
	int k;
	for(int i = 0; i < numElementos; i++){
		fusion[i] = m[0][i];
	}
	for(int i = 1; i < numVectores; i++){ // Iteracion por vector
		for(int j = 0; j < numElementos; j++){ // Iteracion por cada elemento del nuevo vector a insertar
			found = false;
			k = 0;
			while(!found && k < numElementos * i + j){
				if(fusion[k] > m[i][j])
					found = true;
				else
					k++;
			}
			if(found){
				for(int p = numElementos*i+j-1; p >= k; p--){ // Traslacion (uno a la derecha) de los elementos mayores que el elemento a insertar en el vector fusion
					fusion[p+1] = fusion[p];
				}
				fusion[k] = m[i][j];
			}
			if(!found){
				fusion[numElementos * i + j ] = m[i][j];
			}
		}
	}
	
	return fusion;
}



int main(int argc, char * argv[])
{

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }
  
  int n = atoi(argv[1]);
  int k=atoi(argv[2]);

  
  
//VARIABLES UTILIZADAS PARA EL CALCULO DEL TIEMPO
double t_ejecucion = 0, t_transcurrido = 0;

int **T;
T =  new int * [k]; //
  assert(T);


 for (int i = 0; i < k; i++)
      T[i]= new int [n];

int N=k*n;
int * aux = new int[N];
  assert(aux);


srand(time(0));
//genero todos los enteros entre 0 y k*n-1
for (int j=0; j<N; j++) aux[j]=j;


//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
for (int i=0; i<k; i++) {
   int t=0;
   int m=0;
   while (m<n) {
    double u=uniforme();
    if ((N-t)*u >= (n-m)) t++;
    else {
        T[i][m]=aux[t];
	t++;
	m++;
    }
  }
}



//cout <<endl;
/*
for (int i=0; i<k; i++) {
 for (int j=0; j<n; j++)
   cout << T[i][j] << " ";
 cout << " " << endl;
}*/
//cout <<endl;
//cout <<endl;


//CALCULO DE LA EJECUCION DEL ALGORITMO
clock_t tantes, tdespues;
tantes = clock();

aux = mezcla_FB(k,n,T);

tdespues = clock();
t_transcurrido = (double)(tdespues - tantes);

//CALCULO EJECUCION FINAL
t_ejecucion = t_transcurrido / (CLOCKS_PER_SEC);


/*for (int i=0; i<N; i++) {
  cout << aux[i] << " ";
}
*/
//cout <<endl;
//cout <<endl;
cout << n << " " << k << " " <<  t_ejecucion << endl;

delete [] aux;
}
