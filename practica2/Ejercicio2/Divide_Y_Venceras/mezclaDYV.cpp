#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
//#include <algorithm>
//#include <vector>

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tama�o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tama�o n para obtener los k vectores. Est�n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

void mezclaVectores(int * vec1, int * vec2, int dim1, int dim2, int * &mezcla){

	for(int i=0; i<dim1; i++)
		mezcla[i] = vec1[i];
		
	bool found;
	int k;
	
	for(int j=0; j<dim2; j++){
		k=0; found = false;
		while(!found && k<(dim1+dim2)){
			if(mezcla[k] >= vec2[j])
				found = true;
			else
				k++;
		}
		
		if(found){
			for(int p = dim1+j-1; p >= k; p--){
				mezcla[p+1] = mezcla[p];
			}
			mezcla[k] = vec2[j];
		}
		if(!found){
			mezcla[dim1+j] = vec2[j];
		}
	}
}


void mezcla_DYV_recursivo(int vec_inicial, int vec_final, int numElementos, int ** m, int
* &mezcla){

	//PASO1: COMPROBAMOS QUE SIEMPRE VEC_FINAL > VEC_INICIAL
	if(vec_inicial < vec_final){
		//PASO2: OBTENEMOS EL NUMERO DE VECTORES QUE TENEMOS, ASI COMO EL VECTOR MEDIO
		int numVectores = vec_final-vec_inicial+1;
		int vec_medio = (vec_final+vec_inicial)/2;
		//OBTENEMOS DIMENSION PARA VECTORES AUXILIARES DE MEZCLA
		int dim2 = numVectores/2;
		int dim1 = numVectores - dim2;
		//PASO3: DECLARAMOS VECTORES AUXILIARES DONDE GUARDAREMOS RESULTADOS PREVIOS
		int * mezcla1 = nullptr; int * mezcla2 = nullptr;
		mezcla1 = new int [numElementos*(dim1)];
		mezcla2 = new int [numElementos*(dim2)];
		
		//LLAMADA RECURSIVA A FUNCION: CALCULA LA MEZCLA PARA K/2 VECTORES (DESDE 0 HASTA VEC_MEDIO)
		mezcla_DYV_recursivo(vec_inicial,vec_medio,numElementos,m,mezcla1);
		//LLAMADA RECURSIVA A FUNCION: CALCULA LA MEZCLA PARA K/2 VECTORES (DESDE VEC_MEDIO HASTA VEC_FINAL)
		mezcla_DYV_recursivo(vec_medio+1,vec_final,numElementos,m,mezcla2);
		//PASO 4: MEZCLAMOS LOS VECTORES OBTENIDOS ANTERIORMENTE
		mezclaVectores(mezcla1,mezcla2,dim1*numElementos,dim2*numElementos,mezcla);
		//PASO 5: LIBERAMOS MEMORIA
		
		delete [] mezcla1;
		mezcla1 = nullptr;
		
		delete [] mezcla2;
		mezcla2 = nullptr;
	
	}
	//EN CASO CONTRARIO AL PASO1: CASO BASE (SOLO MEZCLAMOS 1 VECTOR)
	else{
		for(int i=0; i<numElementos;i++)
		mezcla[i] = m[vec_inicial][i];
		}
}

void mezcla_DYV(int numVectores, int numElementos, int ** m, int * &mezcla){
	mezcla_DYV_recursivo(0,numVectores-1,numElementos,m,mezcla);
}


int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n=8;
  //int n = atoi(argv[1]);
  int k=atoi(argv[1]);


int **T;
T =  new int * [k];
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


/*
for (int i=0; i<k; i++) {
 for (int j=0; j<n; j++)
   cout << T[i][j] << " ";
 cout << " " << endl;
}
*/
//VARIABLES UTILIZADAS PARA EL CALCULO DEL TIEMPO
double t_ejecucion = 0, t_transcurrido = 0;
clock_t tantes, tdespues;
//CALCULO DE LA EJECUCION DEL ALGORITMO
tantes = clock();
mezcla_DYV(k,n,T, aux);
tdespues = clock();
t_transcurrido = (double)(tdespues - tantes);
//CALCULO EJECUCION FINAL
t_ejecucion = t_transcurrido / (CLOCKS_PER_SEC);


cout <<endl;
/*
for (int i=0; i<N; i++) {
  cout << aux[i] << " ";
}
*/
//cout <<endl;
//cout <<endl;
cout <<  k << " " <<  t_ejecucion << endl;

delete [] aux;

}
