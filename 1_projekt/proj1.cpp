#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include <math.h> 

int n;

template <class T>
void randomize_tab(T tab[], int first_to_randomize = 0) {
	tab[0] = rand() % (n * 5);
	for(int i = 1; i < first_to_randomize; i++) {
		tab[i] = tab[i - 1] + (rand() % n);
	}
	for(int i = first_to_randomize; i < n; i++) {
		tab[i] = rand() % (n * 10);
	}
}

template <class T>
void show_tab(T tab[], int first_elem = 0, int last_elem = (n - 1)) {
	for(int i = first_elem; i <= last_elem; i++) {
		cout << tab[i] << " ";
	}
}

template <class T>
void swap_elements(T tab[], int first_elem, int second_elem) {
	int temp = tab[second_elem];
	tab[second_elem] = tab[first_elem];
	tab[first_elem] = temp;
}

ostream& operator << (ostream &out, int tab[]) {
	show_tab(tab);
	return out;
}


template <class T>
class MergeSort {
	T *pom;
	T *tab;

	void merge(T tab[], int left, int mid, int right) {
		int tab_index = left;
		int l = left, m = mid, r = right;

		for(int i = left; i <= right; i++) {
			pom[i] = tab[i];
		}


		while (l <= mid && m + 1 <= right) {
			if(pom[l] < pom[m + 1]) {
				tab[tab_index] = pom[l];
				l++;
			}
			else {
				tab[tab_index] = pom[m + 1];
				m++;
			}
			tab_index++;
		}



		if(l > m) {
			while(m + 1 <= right) {
				tab[tab_index] = pom[m + 1];
				m++;
				tab_index++;
			}
		}
		else {
			while(l <= mid) {
				tab[tab_index] = pom[l];
				l++;
				tab_index++;
			}
		}


	}

	void split(T tab[], int left, int right) {
		if(right <= left) 
			return;

		int mid = (right + left)/2;
		split(tab, left, mid);
		split(tab, mid + 1, right);

		merge(tab, left, mid, right);
	}

public:
	MergeSort(int num_elements, int first_element_to_randomize = 0, bool debug = false) {
		
		n = num_elements;
		tab = new T[n];
		pom = new T[n];

		randomize_tab(tab, first_element_to_randomize);
		if(debug)
			cout << "PRZED: " << tab << endl;
		split(tab, 0, n - 1);
		if(debug)
			cout << "PO: " << tab << endl;
	}

	MergeSort(int num_elements, T tab[], bool debug = false) {
		n = num_elements;
		pom = new int[n];

		if(debug)
			cout << "PRZED: " << tab << endl;
		split(tab, 0, n - 1);
		if(debug)
			cout << "PO: " << tab << endl;	}

	~MergeSort() {
		delete []pom;
	}
};

template <class T>
class Quicksort {
	T *pom;
	T *tab;

	int get_pivot(T tab[], int left, int mid, int right) {

		int pivot = tab[mid];
		int tab_index = left;

		
		swap_elements(tab, mid, right);
		for(int i = left; i < right; i++) {
			if(tab[i] < pivot) {
				swap_elements(tab, tab_index, i);
				tab_index++;
			}
		}

		swap_elements(tab, tab_index, right);
		return tab_index;
	}

	int get_pivot_2(T tab[], int left, int mid, int right) {
		int pivot = tab[mid];
		int tab_index = left;

		int i = left, j = right;
		while(true) {
			while(tab[j] > pivot)
				j--;
			while(tab[i] < pivot)
				i++;

			if(i < j) {
				swap_elements(tab, i, j);
				i++;
				j--;
			}
			else
				return j;
		}
	}

	void split(T tab[], int left, int right) {
		if(right <= left) 
			return;

		int mid = (right + left)/2;
		int pivot = get_pivot_2(tab, left, mid, right);

		split(tab, left, pivot);
		split(tab, pivot + 1, right);
	}

public:
	Quicksort(int num_elements, int first_element_to_randomize = 0, bool debug = false) {
		n = num_elements;
		tab = new int[n];
		pom = new int[n];

		randomize_tab(tab, first_element_to_randomize);
		if(debug) 
			cout << "PRZED: " << tab << endl;
		split(tab, 0, n-1);
		if(debug)
			cout << "PO: " << tab << endl;
	}

	Quicksort(int num_elements, int tab[]) {
		n = num_elements;
		pom = new int[n];

		//cout << "PRZED: " << tab << endl;
		split(tab, 0, n-1);
		//cout << "PO: " << tab << endl;
	}

	~Quicksort() {
		delete[] pom;
	}
};

template <class T>
class Heapsort {
	int heap_size; 
	T *tab;

	inline int get_parent(int i) { return int(i/2); }
	inline int get_right(int i) { return 2 * (i + 1); }
	inline int get_left(int i) { return 2 * (i + 1) - 1; }

	void max_heapify(T tab[], int i) {
		int left = get_left(i);
		int right = get_right(i);
		int largest = i;
		
		if (right < heap_size && tab[right] > tab[i]) {
			largest = right;
		}	
		if (left < heap_size && tab[left] > tab[largest]) {
			largest = left;
		}	

		if(largest != i) {
			swap_elements(tab, i, largest);
			max_heapify(tab, largest);
		}
	} 

	void build_max_heap(T tab[]) {
		heap_size = n;
		for(int i = int(heap_size / 2); i >= 0; i--) {
			max_heapify(tab, i);
		}
	}

	void sort(T tab[]) {

		build_max_heap(tab);
		for(int i = n - 1; i >= 0; i--) {
			swap_elements(tab, i, 0);
			heap_size--;

			max_heapify(tab, 0);

		}
	}

public:
	Heapsort(int num_elements, int first_element_to_randomize = 0, bool debug = false) {
		n = num_elements;
		tab = new T[n];

		randomize_tab(tab, first_element_to_randomize);

		if(debug)
			cout << "PRZED: " << tab << endl;
		sort(tab);
		if(debug)
			cout << "PO: " << tab << endl;
	}

	Heapsort(int num_elements, T tab[], bool debug = false) {
		n = num_elements;

		if(debug)
			cout << "PRZED: " << tab << endl;
		sort(tab);
		if(debug)
			cout << "PO: " << tab << endl;
	}
};


template <class T>
class Introsort {
	int maxdepth;
	T *tab;
	T *pom;
	
	int get_pivot(T tab[], int left, int mid, int right) {
		int pivot = tab[mid];
		int tab_index = left;

		int i = left, j = right;
		while(true) {
			while(tab[j] > pivot)
				j--;
			while(tab[i] < pivot)
				i++;

			if(i < j) {
				swap_elements(tab, i, j);
				i++;
				j--;
			}
			else
				return j;
		}
	}

	void introsort(T tab[], int left, int right, int maxdepth) {
		int num_elements = right - left;
		int mid = (left + right) / 2;
		int pivot = get_pivot(tab, left, mid, right);
		if(num_elements < 1)
			return;
		else if(maxdepth == 0) {
			pom = new T[num_elements + 1];

			for(int i = left; i <= right; i++) {
				pom[i - left] = tab[i];
			}
			Heapsort<T> sort(num_elements, pom);
			for(int i = left; i <= right; i++) {
				tab[i] = pom[i - left];
			}
			delete[] pom;
		}
		else {
			introsort(tab, left, pivot, maxdepth - 1);
			introsort(tab, pivot + 1, right, maxdepth - 1);	
		}


	}

	void sort(int tab[]) {
		maxdepth = int(log(n)) * 2;
		introsort(tab, 0, n - 1, maxdepth);
	}
public:
	Introsort(int num_elements, int first_element_to_randomize = 0, bool debug = false) {
		n = num_elements;
		tab = new T[n];
		randomize_tab(tab, first_element_to_randomize);
		if(debug)
			cout << "PRZED: " << tab << endl;

		sort(tab);
		n = num_elements;

		if(debug)
			cout << "PO: " << tab << endl;
	}

	Introsort(int num_elements, T tab[], bool debug = false) {
		n = num_elements;

		if(debug)
			cout << "PRZED: " << tab << endl;

		sort(tab);
		n = num_elements;

		if(debug)
			cout << "PO: " << tab << endl;
	}
};

class Tester {
	int tests_num[5] = {10000, 50000, 100000, 500000, 1000000};
	float tests_first_elem_to_random[7] = {0, 0.25, 0.50, 0.75, 0.95, 0.99, 0.997};
	int number_of_tests = 100;
	double duration = 0;
	double total_duration_per_test = 0;
public:

	template <class Type>
	void test_sort(int sort_method) {
		for (int i = 0; i < sizeof(tests_num)/sizeof(tests_num[0]); i++) {
			for (int j = 0; j < sizeof(tests_first_elem_to_random)/sizeof(tests_first_elem_to_random[0]); j++) {
				total_duration_per_test = 0;
				for(int k = 0; k < number_of_tests; k++) {
					clock_t start = clock();

					switch(sort_method) {
						case 0:
						{
							MergeSort<Type> merge(tests_num[i], (int)(tests_num[i] * tests_first_elem_to_random[j]));
						}	break;
						case 1:
						{
							Quicksort<Type> quick(tests_num[i], (int)(tests_num[i] * tests_first_elem_to_random[j]));
						}	break;
						case 2:
						{
							Introsort<Type> intro(tests_num[i], (int)(tests_num[i] * tests_first_elem_to_random[j]));
						}
							break;
						default:
							break;
					}
					duration = ((clock() - start) / (double) CLOCKS_PER_SEC);
					total_duration_per_test += duration;
				}
				duration = total_duration_per_test / number_of_tests;
				cout << "Duration for " << tests_num[i] << " with " << tests_first_elem_to_random[j] << ": " << duration << endl;					
			}	

			Type tab[tests_num[i]];
			for (int j = 1; j <= tests_num[i]; j++) {
				tab[tests_num[i] - j] = j;
			}
			total_duration_per_test = 0;

			for(int k = 0; k < number_of_tests; k++) {
				clock_t start = clock();

				switch(sort_method) {
					case 0:
					{
						MergeSort<Type> merge(tests_num[i], tab);
					}
						break;
					case 1:
					{
						Quicksort<Type> quick(tests_num[i], tab);
					}
						break;
					case 2:
					{
						Introsort<Type> intro(tests_num[i], tab);
					}
						break;
					default:
						break;
				}
				duration = ((clock() - start) / (double) CLOCKS_PER_SEC);
				total_duration_per_test += duration;
			}
			duration = total_duration_per_test / number_of_tests;
			cout << "Duration for " << tests_num[i] << " with reversed order: " << total_duration_per_test << endl;
		
		}
	}
};




int main() {
	srand(time(NULL));
	Tester test;

	bool test_sort = true;
	if(test_sort) {
		cout << endl << endl << " MergeSort " << endl << endl;
		test.test_sort<int>(0);
		cout << endl << endl << " Quicksort " << endl << endl;
		test.test_sort<int>(1);
		cout << endl << endl << " Introsort " << endl << endl;
		test.test_sort<int>(2);
		
	}
	return 0;
}