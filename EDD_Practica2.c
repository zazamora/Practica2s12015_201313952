#include <stdlib.h>
#include <stdio.h>
#include <windows.h>




/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

typedef struct _nodo {
   int valor;
   struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

/* Funciones con listas: */
void Insertar(Lista *l, int v);
void Borrar(Lista *l, int v);
int primerDato(Lista lista);
int ultimoDato(Lista lista);
//pNodo buscarDato(Lista *lista, int index);
//void quicksort(Lista *lista, int ini, int fin);
int ListaVacia(Lista l);

void BorrarLista(Lista *);
void MostrarLista(Lista l);
void ordBurbuja(Lista lista);
/******************************EMPIEZA AVL**************************/

// An AVL tree node
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node* newNode(int key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 	int a = height(y->left);
 	int b = height(y->right);
    // Update heights
    y->height = ((a > b)? a : b)+1;
    a = height(x->left);
    b = height(x->right);
    x->height = ((a > b)? a : b)+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 	int a = height(x->left);
 	int b = height(x->right);
 	
    //  Update heights
    x->height = ((a > b)? a : b)+1;
    a = height(y->left);
    b = height(y->right);
    y->height = ((a > b)? a : b)+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
struct node* insert(struct node* node, int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
 	int a = height(node->left);
 	int b = height(node->right);
    /* 2. Update height of this ancestor node */
    node->height = ((a > b)? a : b) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
		inOrder(root->right);
    }
}

void getInordenTiempo(struct node *raiz) {
	if (raiz != NULL) {

		getInordenTiempo(raiz->left);
		getInordenTiempo(raiz->right);
	}
}


/*****************************FINALIZA AVL**************************/
/***********************METODOS ORDENAMIENTO************************/

void bubbleSort(int arrayBubble[], int n) {
	int i, j, aux;
	for (i = 0; i < (n - 1); i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (arrayBubble[j] > arrayBubble[j + 1]) {
				aux = arrayBubble[j];
				arrayBubble[j] = arrayBubble[j + 1];
				arrayBubble[j + 1] = aux;
			}
		}
	}
}

void mergeSort(int x[], int low, int mid, int high) {
	int i, mi, k, lo, temp[50];

	lo = low;
	i = low;
	mi = mid + 1;
	while ((lo <= mid) && (mi <= high)) {
		if (x[lo] <= x[mi]) {
			temp[i] = x[lo];
			lo++;
		} else {
			temp[i] = x[mi];
			mi++;
		}
		i++;
	}
	if (lo > mid) {
		for (k = mi; k <= high; k++) {
			temp[i] = x[k];
			i++;
		}
	} else {
		for (k = lo; k <= mid; k++) {
			temp[i] = x[k];
			i++;
		}
	}

	for (k = low; k <= high; k++) {
		x[k] = temp[k];
	}
}

void partition(int x[], int low, int high) {
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		partition(x, low, mid);
		partition(x, mid + 1, high);
		mergeSort(x, low, mid, high);
	}
}
/************************FIN METODOS ORDEN***************************/
int main()
{

	FILE *fichero = NULL;
	char *nombreArchivo = "ejemplo.txt";
	char lectura[80];
	int lec;
	
	LARGE_INTEGER t_ini, t_fin;
	double secs;
	struct node *root = NULL;
	int n = 0;
	QueryPerformanceCounter(&t_ini);

	int endoffile = 0;
	
	
	fichero = fopen(nombreArchivo, "r");
	if(fichero == NULL)return -1;
	Lista lista = NULL;
	Lista lista2 = NULL;
	//fscanf(fichero, " %[^\n]", &lectura);
	//printf("Lectura: %s\n", lectura);
	/*printf("La lectura es:\n\n");
	fscanf(fichero,"%d-",&lec);
	Insertar(&lista, lec);
	printf("La primera linea es: %d\n", lec);
	fscanf(fichero,"%d-",&lec);
	Insertar(&lista, lec);
	printf("La segunda linea es: %d\n", lec);
	fscanf(fichero, " %[^\n]", &lectura);*/
	endoffile = fscanf(fichero,"%d-",&lec);
	
	while(endoffile != EOF){
		//printf("%s\n", lectura);
		//fscanf(fichero,"%d-",&lec);
		//Insertar(&lista, lec);
		//Insertar(&lista2, lec);
		n = n + 1;
		root = insert(root, lec);
		endoffile = fscanf(fichero,"%d-",&lec);
	}
	
	
	fclose(fichero);	

	
	//MostrarLista(lista);
	QueryPerformanceCounter(&t_fin);
	
	secs = performancecounter_diff(&t_fin, &t_ini);
	printf("Tiempo de ingreso al AVL:\n");
	printf("% 10lf segundos\n", secs);
	//BorrarLista(&lista);
	printf("\n");
	QueryPerformanceCounter(&t_ini);
  		getInordenTiempo(root);
  	QueryPerformanceCounter(&t_fin);
  	secs = performancecounter_diff(&t_fin, &t_ini);
		printf("\nMetodo de preOrden AVL tardo:\n");
		printf("% 10lf segundos\n", secs);
	
	printf("\n");	
	//MostrarLista(lista);
	
	int arrayBubble[n], i, contador, arrayQuick[n];
	fichero = fopen(nombreArchivo, "r");
	if(fichero == NULL)return -1;
	contador = 0;
	endoffile = fscanf(fichero,"%d-",&lec);
	while(endoffile != EOF){
		arrayBubble[contador] = lec;
		arrayQuick[contador] = lec;
		contador = contador + 1;
		endoffile = fscanf(fichero,"%d-",&lec);
	}
	fclose(fichero);
  	
	  
	QueryPerformanceCounter(&t_ini);
  		//ordBurbuja(lista);
  		bubbleSort(arrayBubble, n);
	QueryPerformanceCounter(&t_fin);
	secs = performancecounter_diff(&t_fin, &t_ini);
		printf("Metodo burbuja tardo:\n");
		printf("% 10lf segundos\n", secs);
  		//MostrarLista(lista);
  	QueryPerformanceCounter(&t_ini);
  		partition(arrayQuick, 0, (n - 1));
	QueryPerformanceCounter(&t_fin);
	secs = performancecounter_diff(&t_fin, &t_ini);
		printf("Metodo Quicksort tardo:\n");
		printf("% 10lf segundos\n", secs);
  	
	printf("Elementos del quicksort:\n");
	for (i = 0; i < n; i++) {
		printf("%d ", arrayQuick[i]);
	}

	printf("\nLista de numeros ordenados por el bubble sort:\n");
	for (i = 0; i < n; i++) {
		printf("%d ", arrayBubble[i]);
	}
	
	printf("\nEl recorrido inorden es: \n", n);
	inOrder(root); 
	
	/****************GRAFICAR*****************/
	// Open a pipe to gnuplot
	/*FILE *gnuplotPipe = popen("C:\\Program Files\\gnuplot\\bin\\pgnuplot -persist","w");
	// If gnuplot is found
	if (gnuplotPipe) {
	  // using fprintf on the gnuplotPipe, we can directly issue commands in gnuplot
	  fprintf(gnuplotPipe, "set style data lines\n");
	  fprintf(gnuplotPipe, "cd 'C:\\Program Files\\gnuplot\\bin'\n");
	  // assuming your data file is placed in the gnuplot bin directory
	  fprintf(gnuplotPipe, "plot \"datos.dat\" using 1:2\n");
	  fflush(gnuplotPipe);
	  fprintf(stderr,"Press enter to continue...");
	  fflush(stderr);
	  getchar();
	  // exit gnuplot
	  fprintf(gnuplotPipe,"exit \n");
	  pclose(gnuplotPipe);
	}*/

	/******************FIN*******************/ 
	  	
  	system("PAUSE");
	return 0;
}

void Insertar(Lista *lista, int v)
{
   pNodo nuevo, anterior;

   /* Crear un nodo nuevo */
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->valor = v;
   nuevo->siguiente = *lista;
   *lista = nuevo;
}

void ordBurbuja(Lista lista)
{
	Lista actual, siguiente;
	int t;
	
	actual = lista;
	
	while(actual->siguiente != NULL) 
	{
		siguiente = actual->siguiente;
		
		while(siguiente != NULL)
		{
			if(actual->valor > siguiente->valor)
			{
				t = siguiente->valor;
				siguiente->valor = actual->valor;
				actual->valor = t;
			}
			siguiente = siguiente->siguiente;
		}
		actual = actual->siguiente;
		siguiente = actual->siguiente;
	}
}

void Borrar(Lista *lista, int v)
{
   pNodo anterior, nodo;
   
   nodo = *lista;
   anterior = NULL;
   while(nodo && nodo->valor < v) {
      anterior = nodo; 
      nodo = nodo->siguiente;
   }
   if(!nodo || nodo->valor != v) return;
   else { /* Borrar el nodo */
      if(!anterior) /* Primer elemento */
         *lista = nodo->siguiente;
      else  /* un elemento cualquiera */
         anterior->siguiente = nodo->siguiente;
      free(nodo);
   }   
}

int ListaVacia(Lista lista)
{
   return (lista == NULL);
}

void BorrarLista(Lista *lista)
{
   pNodo nodo;

   while(*lista) {
      nodo = *lista;
      *lista = nodo->siguiente;
      free(nodo);
   }
}

void MostrarLista(Lista lista)
{
   pNodo nodo = lista;

   if(ListaVacia(lista)) printf("Lista vacía\n");
   else {
      while(nodo) {
         printf("%d -> ", nodo->valor);
         nodo = nodo->siguiente;
     }
     printf("\n");
   }
}

int primerDato(Lista lista){
	pNodo actual = lista;
	return actual->valor;
}
int ultimoDato(Lista lista){
	pNodo actual = lista;
	int a = -1;
	while(actual)
	{
		a++;
		actual = actual->siguiente;			
	}
	return a;
}
/*pNodo buscarDato(Lista *lista, int index)
{
	pNodo actual = *lista;
	int a = 0;
	while(actual)
	{
		if(a == index)
			return actual;
		a++;
		actual = actual->siguiente;
	}
	return NULL;
}*/

/*void quicksort(Lista *lista, int ini, int fin)
{
	int t, i = ini, h = fin, mid;
	if(fin > ini)
	{
		mid = buscarDato(lista,(ini+fin)/2)->valor;
		while(i < h)
		{
			while((i<fin)&&(buscarDato(lista,i)->valor<mid))i++;
			while((h>ini)&&(buscarDato(lista,i)->valor>mid))h--;
			if(i<=h)
			{
				t = buscarDato(lista,i)->valor;
				buscarDato(lista,i)->valor = buscarDato(lista,h)->valor;
				buscarDato(lista,h)->valor = t;
				i++;
				h--;
			}
		}
		if(ini<h) quicksort(lista, ini,h);
		if(i<fin) quicksort(lista,i,fin);
	}
}*/







