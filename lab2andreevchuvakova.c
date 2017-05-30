#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct bin_tree {
	int data;
	struct bin_tree * right, *left;
};
typedef struct bin_tree node;

int arrayCreate(int n, int *arrayPointer);
int copyArray(int n, int *arrayPointer);
void printArray(int n, double time, int *arrayPointer);
void printSearch(unsigned long long int comp, unsigned long long int moves, int min, double time);

//sorts
void bubbleSort(int n, int *arrayPointer);
void quickSort(int *arrayPointer, int low, int high);
void insertionSort(int n, int *arrayPointer);
//searches
int linearSearch(int a, int n, int *arrayPointer);
int interpolationSearch(int a, int n, int *arrayPointer);
//tree
void insert(node ** tree, int val);
void print_inorder(node * tree);
void deltree(node * tree);
node* search(node ** tree, int val);



unsigned long long int comp = 0, moves = 0;
double T;

int main(void) {
	int *arrayPointer, choise, array, i, k, n = 10, *tempArray, size, value, minel;
	node *root = NULL, *min;
	double Tstart, Tend;
	printf("If you want to input array by keyboard (n = 10), press 1, for random input press 2: ");
	scanf("%d", &choise);
	switch (choise) {
	case 1:
		arrayPointer = (int*)malloc(n * sizeof(int));
		for (i = 0; i<n; i++) {
			scanf("%d", &arrayPointer[i]);
		}
		printArray(n, 0, arrayPointer); //print unsorted array
		bubbleSort(n, arrayPointer);
		printf("\n Sorted array (bubble sort): \n");
		printArray(n, 0, arrayPointer); //print sorted array (bubblesort)
		printf("\n Sorted array (quicksort): \n");
		quickSort(arrayPointer, 0, n - 1);
		printArray(n, T, arrayPointer);
		free(arrayPointer);
		break;
	case 2:
		for (i = 0; i<5; i++) {
			printf("\n\n Input the size of array %d :   ", i + 1);
			scanf("%d", &n);
			arrayPointer = (int*)malloc(n * sizeof(int));
			arrayCreate(n, arrayPointer); // create an array with random elements
			tempArray = copyArray(n, arrayPointer); //copy array to temporary array
			Tstart = clock();
			bubbleSort(n, tempArray);
			Tend = clock();
			T = (Tend - Tstart) / (double)CLOCKS_PER_SEC;
			printf("\n\nComparisons and moves (bubble sort):\n");
			printcm(T, arrayPointer); 

			printf("\n\nComparisons and moves (quicksort):\n");
			tempArray = copyArray(n, arrayPointer);
			Tstart = clock();
			quickSort(tempArray, 0, n - 1);
			Tend = clock();
			T = (Tend - Tstart) / (double)CLOCKS_PER_SEC;
			printcm(T, arrayPointer);

			printf("\n\nComparisons and moves (insertion search): \n");
			tempArray = copyArray(n, arrayPointer);
			Tstart = clock();
			insertionSort(n, tempArray);
			Tend = clock();
			T = (Tend - Tstart) / (double)CLOCKS_PER_SEC;
			printcm(T, arrayPointer);

			k = tempArray[0]; //random element for searching minimal
			printf("\n\n Linear search: \n");
			Tstart = clock();
			linearSearch(k, n, tempArray);
			Tend = clock();
			T = (Tend - Tstart) / (double)CLOCKS_PER_SEC;
			printSearch(comp, moves, minel, T);
			
			printf("\n\n Interpolation search: \n");
			Tstart = clock();
			value = interpolationSearch(k, n, tempArray);
			if (value != -1)
				printSearch(comp, moves, tempArray[value], T);
			else
				printf("Element not found.");
			Tend = clock();
			T = (Tend - Tstart) / (double)CLOCKS_PER_SEC;
			printSearch(comp, moves, minel, T);

			printf("\n\n Comparisons and moves (tree sort): \n");
			tempArray = copyArray(n, arrayPointer);
			Tstart = clock();
			//Insert unsorted array in our tree;
			for (k = 0; k<n; k++) {
				value = tempArray[k];
				insert(&root, value);
			}
			Tend = clock();
			T = (Tend - Tstart) / (double)CLOCKS_PER_SEC;
			
			if (T != 0) printf("\nEstimated time to sort:  %.3lf sec\n", T);
			else printf("\nEstimated time to sort: <0.001 sec\n");
			printf("\nMoves through array: [%d]", moves);
			printf("\nNumber of comparsions [%d]", comp);
			moves = 0;
			comp = 0;

			printf("\n Tree search: \n");
			printf("Input element to search in array: ");
			scanf("%d", &k);
			Tstart = clock();
			min = search(&root, k);
			Tend = clock();
			T = (Tend - Tstart) / (double)CLOCKS_PER_SEC;
			if (min) {
				printf("Searched node=%d\n", min->data);
				printSearch(comp, moves, min->data, T);
			}
			else {
				printf("Data Not found in tree.\n");
			}

			//free the memory

			
		}
		deltree(root);
		free(arrayPointer);
		free(tempArray);
		break;
	default:
		printf("\nWrong number entered");
	}
}

//random array for n=10 000, 30 000, 50 000, 70 000, 90 000
int arrayCreate(int n, int *arrayPointer) {
	int i;
	srand(time(NULL));
	for (i = 0; i<n; i++) {
		arrayPointer[i] = rand() % 500;
	}
	return (int)arrayPointer;
}

int copyArray(int n, int *arrayPointer) {
	int *tempArray, i;
	tempArray = (int*)malloc(n * sizeof(int));
	for (i = 0; i<n; i++) {
		tempArray[i] = arrayPointer[i];
	}
	return (int*)tempArray;
}

void printcm(double time, int *arrayPointer) {
	if (time != 0) printf("\nEstimated time to sort:  %.3lf sec\n", time);
	else printf("\nEstimated time to sort: <0.001 sec\n");
	printf("\nNumber of compares is: [%llu]", comp);
	printf("\nNumber of moves through array is: [%llu] ", moves);
	comp = 0;
	moves = 0;
	time = 0;
}

void printArray(int n, double time, int *arrayPointer) {
	int i;
	for (i = 0; i<n; i++) {
		printf("[%d]", arrayPointer[i]);
	}
	if (time != 0) printf("\nEstimated time to sort:  %.3lf sec\n", time);
	else printf("\nEstimated time to sort: <0.001 sec\n");
	printf("\nNumber of compares is: [%llu]", comp);
	printf("\nNumber of moves through array is: [%llu] ", moves);
	comp = 0;
	moves = 0;
	time = 0;
}

void printSearch(unsigned long long int comp, unsigned long long int moves, int min, double time) {
	printf("\nMinimal element in array is : %d ", min);
	printf("\nMoves through array: %d", moves);
	printf("\nNumber of comparsions %d", comp);
	if (time != 0) printf("\nEstimated time to sort:  %.3lf sec\n", time);
	else printf("\nEstimated time to sort: <0.001 sec\n");
	comp = 0;
	moves = 0;
}

void bubbleSort(int n, int *arrayPointer) {
	int i, j, tmp;
	for (i = 0; i<n - 1; i++) {
		for (j = 0; j<n - (1 + i); j++) {
			if (arrayPointer[j] > arrayPointer[j + 1]) {
				tmp = arrayPointer[j];
				arrayPointer[j] = arrayPointer[j + 1];
				arrayPointer[j + 1] = tmp;
				comp++;
			}
			moves++;
		}
	}
}

void quickSort(int *arrayPointer, int low, int high) {
	int l = low, r = high;
	static int i, sred, min, max;
	int temp = 0;
	min = l;
	max = r;
	for (i = l; i<r; ++i) {
		if (arrayPointer[i] > arrayPointer[max]) max = i;
		if (arrayPointer[i] < arrayPointer[min]) min = i;
	}
	sred = (arrayPointer[max] + arrayPointer[min]) / 2;
	while (l <= r) {
		while (arrayPointer[l] < sred)
		{
			++l;
			moves++;
		}
		while (arrayPointer[r] > sred)
		{
			--r;
			moves++;
		}
		if (l <= r)
		{
			temp = arrayPointer[l];
			arrayPointer[l] = arrayPointer[r];
			arrayPointer[r] = temp;
			--r;
			++l;
			comp++;
		}
		moves++;
	}
	if (low < r)
		quickSort(arrayPointer, low, r);
	comp++;
	if (high > l)
		quickSort(arrayPointer, l, high);
	comp++;
}


void insertionSort(int n, int *arrayPointer) {
	int newElement, location, i;
	for (i = 1; i < n; i++) {
		newElement = arrayPointer[i];
		location = i - 1;
		while (location >= 0 && arrayPointer[location] > newElement) {
			arrayPointer[location + 1] = arrayPointer[location];
			location = location - 1;
			moves++;
			comp++;
		}
		arrayPointer[location + 1] = newElement;
		moves++;
	}
}

//--------------------------TREE----------------------------------------------
void insert(node ** tree, int val) {
	node *temp = NULL;
	if (!(*tree))
	{
		temp = (node *)malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->data = val;
		*tree = temp;
		comp++;
		return;
	}

	if (val <= (*tree)->data)
	{
		insert(&(*tree)->left, val);
		comp++;
		moves++;
	}
	else if (val >= (*tree)->data)
	{
		insert(&(*tree)->right, val);
		comp++;
		moves++;
	}

}

void print_inorder(node * tree) {
	if (tree)
	{
		print_inorder(tree->left);
		printf("[%d]", tree->data);
		print_inorder(tree->right);
	}
}

void deltree(node * tree) {
	if (tree)
	{
		deltree(tree->left);
		deltree(tree->right);
		free(tree);
	}
}

node* search(node ** tree, int val) {
	if (!(*tree))
	{
		return NULL;
		comp++;
	}

	if (val < (*tree)->data)
	{
		comp++;
		moves++;
		search(&((*tree)->left), val);
	}
	else if (val >(*tree)->data)
	{
		comp++;
		moves++;
		search(&((*tree)->right), val);
	}
	else if (val == (*tree)->data)
	{
		comp++;
		return *tree;
	}
}


//-------------------------SEARCHES--------------------------------------------
int linearSearch(int a, int n, int *arrayPointer) {
	int i, min, index;
	for (i = 0; i<n; i++) {
		if (a>arrayPointer[i]) {
			a = arrayPointer[i];
			comp++;
		}
		moves++;
	}
	printSearch(comp, moves, a, T);
}

int interpolationSearch(int a, int n, int *arrayPointer) {
	// Find indexes of two corners
	int lo = 0, hi = (n - 1);

	// Since array is sorted, an element present
	// in array must be in range defined by corner
	while (lo <= hi && a >= arrayPointer[lo] && a <= arrayPointer[hi])
	{
		// Probing the position with keeping
		// uniform distribution in mind.
		int pos = lo + (((double)(hi - lo) /
			(arrayPointer[hi] - arrayPointer[lo]))*(a - arrayPointer[lo]));

		// Condition of target found
		if (arrayPointer[pos] == a) {
			comp++;
			return pos;
		}

		// If x is larger, x is in upper part
		if (arrayPointer[pos] < a) {
			lo = pos + 1;
			comp++;
		}
		// If x is smaller, x is in lower part
		else {
			hi = pos - 1;
			comp++;
		}

		moves++;
	}
	return -1;
}
