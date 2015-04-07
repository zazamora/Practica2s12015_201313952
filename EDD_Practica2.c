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
	char nombreArchivo[500];
	char lectura[80];
	int lec;
	int ejeX[500];
	double ejeY[500];
	
	int ejeXA[500];
	double ejeYA[500];
	
	int ejeXB[500];
	double ejeYB[500];
	
	int ejeXM[500];
	double ejeYM[500];
	
	
	int index = 0;
	LARGE_INTEGER t_ini, t_fin;
	double secs;
	int whatToDo = 1;
	do{
		printf("/*********************************/\n");
		struct node *root = NULL;
		int n = 0;
		puts("Ingrese direccion del archivo: ");
		scanf("%s", &nombreArchivo);
		QueryPerformanceCounter(&t_ini);
	
		int endoffile = 0;
		
		
		fichero = fopen(nombreArchivo, "r");
		if(fichero == NULL)return -1;
		endoffile = fscanf(fichero,"%d-",&lec);
		
		while(endoffile != EOF){
			n = n + 1;
			root = insert(root, lec);
			endoffile = fscanf(fichero,"%d-",&lec);
		}
		
		
		fclose(fichero);	
	
		
		QueryPerformanceCounter(&t_fin);
		
		secs = performancecounter_diff(&t_fin, &t_ini);
		ejeX[index] = n;
		ejeY[index] = secs;
		//index++;
		printf("Tiempo de ingreso al AVL:\n");
		printf("% 10lf segundos\n", secs);
		printf("\n");
		QueryPerformanceCounter(&t_ini);
	  		getInordenTiempo(root);
	  	QueryPerformanceCounter(&t_fin);
	  	secs = performancecounter_diff(&t_fin, &t_ini);
	  	ejeXA[index] = n;
		ejeYA[index] = secs;
		//index++;
			printf("\nMetodo de preOrden AVL tardo:\n");
			printf("% 10lf segundos\n", secs);
		
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
	  		bubbleSort(arrayBubble, n);
		QueryPerformanceCounter(&t_fin);
		secs = performancecounter_diff(&t_fin, &t_ini);
		ejeXB[index] = n;
		ejeYB[index] = secs;
		//index++;
			printf("Metodo burbuja tardo:\n");
			printf("% 10lf segundos\n", secs);
	  	printf("\n");
	  	QueryPerformanceCounter(&t_ini);
	  		partition(arrayQuick, 0, (n - 1));
		QueryPerformanceCounter(&t_fin);
		secs = performancecounter_diff(&t_fin, &t_ini);
		ejeXM[index] = n;
		ejeYM[index] = secs;
		index++;
			printf("Metodo Mergesort tardo:\n");
			printf("% 10lf segundos\n", secs);
	  	printf("\n");
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
		printf("\n");
		printf("Que desea hacer?");
		scanf(" %d", &whatToDo);
	}while(whatToDo != 0);
	printf("/*********************************/\n");
	FILE *archivo;
	archivo = fopen("Archivo.txt","w");
	fprintf(archivo,"0		0.0\n");
	FILE *archivoA;
	archivoA = fopen("ArchivoA.txt","w");
	fprintf(archivoA,"0		0.0\n");
	FILE *archivoB;
	archivoB = fopen("ArchivoB.txt","w");
	fprintf(archivoB,"0		0.0\n");
	FILE *archivoM;
	archivoM = fopen("ArchivoM.txt","w");
	fprintf(archivoM,"0		0.0\n");
	int j = 0;
	for(j = 0; j < index;j++)
	{
		printf("Los valores de X: %d y los valores de Y: %f\n",ejeX[j],ejeY[j]);
		fprintf(archivo,"%d		%f\n",ejeX[j],ejeY[j]);
	}
	for(j = 0; j < index;j++)
	{
		printf("Los valores de X: %d y los valores de Y: %f\n",ejeXA[j],ejeYA[j]);
		fprintf(archivoA,"%d		%f\n",ejeXA[j],ejeYA[j]);
	}
	for(j = 0; j < index;j++)
	{
		printf("Los valores de X: %d y los valores de Y: %f\n",ejeXB[j],ejeYB[j]);
		fprintf(archivoB,"%d		%f\n",ejeXB[j],ejeYB[j]);
	}
	for(j = 0; j < index;j++)
	{
		printf("Los valores de X: %d y los valores de Y: %f\n",ejeXM[j],ejeYM[j]);
		fprintf(archivoM,"%d		%f\n",ejeXM[j],ejeYM[j]);
	}
	fclose(archivo);
	fclose(archivoA);
	fclose(archivoB);
	fclose(archivoM);
	/****************GRAFICAR*****************/
	FILE *gnuplotPipe = popen("gnuplot -persist", "w");
		if (gnuplotPipe) {
			fprintf(gnuplotPipe, "set style data lines\n");
			fprintf(gnuplotPipe, "set title 'Grafica de Insercion AVL'\n");
			fprintf(gnuplotPipe, "plot [:][:0.005] 'Archivo.txt' title 'Caso 1'\n");
			fflush(gnuplotPipe);
			//fflush(stderr);
			getchar();
			// exit gnuplot
			fprintf(gnuplotPipe, "exit \n");
			pclose(gnuplotPipe);
		}

	FILE *gnuplotPipeA = popen("gnuplot -persist", "w");
		if (gnuplotPipeA) {
			fprintf(gnuplotPipeA, "set style data lines\n");
			fprintf(gnuplotPipeA, "set title 'Grafica de ORDENAMIENTO AVL'\n");
			fprintf(gnuplotPipeA, "plot [:][:0.000005] 'ArchivoA.txt' title 'Caso 2'\n");
			fflush(gnuplotPipeA);
			//fflush(stderr);
			getchar();
			// exit gnuplot
			fprintf(gnuplotPipeA, "exit \n");
			pclose(gnuplotPipeA);
		}
		
		
	FILE *gnuplotPipeB = popen("gnuplot -persist", "w");
		if (gnuplotPipeB) {
			fprintf(gnuplotPipeB, "set style data lines\n");
			fprintf(gnuplotPipeB, "set title 'Grafica de ORDENAMIENTO BURBUJA'\n");
			fprintf(gnuplotPipeB, "plot [:][:0.000008] 'ArchivoB.txt' title 'Caso 3'\n");
			fflush(gnuplotPipeB);
			//fflush(stderr);
			getchar();
			// exit gnuplot
			fprintf(gnuplotPipeB, "exit \n");
			pclose(gnuplotPipeB);
		}	
	
	
	FILE *gnuplotPipeM = popen("gnuplot -persist", "w");
		if (gnuplotPipeM) {
			fprintf(gnuplotPipeM, "set style data lines\n");
			fprintf(gnuplotPipeM, "set title 'Grafica de Merge Sort'\n");
			fprintf(gnuplotPipeM, "plot [:][:0.000008] 'ArchivoM.txt' title 'Caso 4'\n");
			fflush(gnuplotPipeM);
			//fflush(stderr);
			getchar();
			// exit gnuplot
			fprintf(gnuplotPipeM, "exit \n");
			pclose(gnuplotPipeM);
		}
			
	/******************FIN*******************/ 
	return 0;
}








