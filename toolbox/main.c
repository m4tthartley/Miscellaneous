
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define array_size(arr) (sizeof(arr)/sizeof(arr[0]))

typedef struct {
	int key;
	char *str;
} Item;
Item items[] = {
	/*1, "Ruby Rose",
	2, "Weiss Schnee",
	3, "Blake Belladonna",
	4, "Yang Xiao Long",
	5, "Jaune Arc",
	6, "Pyrrha Nikos",
	7, "Ozpin",
	8, "Glynda Goodwitch",
	9, "Lie Ren",
	10, "Nora Valkyrie",
	11, "Sun Wukong",
	12, "Cinder Fall",
	13, "Roman Torchwick",
	14, "Penny Polendina",
	15, "Neptune Vasilias",
	16, "James Ironwood",
	17, "Peter Port",
	18, "Bartholomew Oobleck",
	19, "Emerald Sustrai",
	20, "Mercury Black",
	21, "Qrow Branwen",
	22, "Mysterious Narrator",
	23, "Taiyang Xiao Long",*/

	19,	"Emerald Sustrai",
	22,	"Mysterious Narrator",
	10,	"Nora Valkyrie",
	5,	"Jaune Arc",
	11,	"Sun Wukong",
	16,	"James Ironwood",
	2,	"Weiss Schnee",
	7,	"Ozpin",
	17,	"Peter Port",
	6,	"Pyrrha Nikos",
	15,	"Neptune Vasilias",
	3,	"Blake Belladonna",
	9,	"Lie Ren",
	21,	"Qrow Branwen",
	8,	"Glynda Goodwitch",
	23,	"Taiyang Xiao Long",
	18,	"Bartholomew Oobleck",
	1,	"Ruby Rose",
	20,	"Mercury Black",
	13,	"Roman Torchwick",
	12,	"Cinder Fall",
	14,	"Penny Polendina",
	4,	"Yang Xiao Long",
};

bool int_compare_proc(void *a, void *b) {
	int aa = *(int*)a;
	int bb = *(int*)b;
	if (bb < aa) {
		return true;
	} else {
		return false;
	}
}

void bubble_sort(void *array, int len, int stride, bool (*compare)(void*, void*)) {
	char *arr = array;
	for (int i = 0; i < len-1; ++i) {
		bool repeat = false;
		for (int j = 0; j < len-1; ++j) {
			char *a = arr+(stride*j);
			char *b = arr+(stride*(j+1));
			if (compare(a, b)) {
				repeat = true;
				for (int k = 0; k < stride; ++k) {
					char swap = *(a+k);
					*(a+k) = *(b+k);
					*(b+k) = swap;
				}
			}
		}
		if (!repeat) break;
	}
}

/*
	Insertion sort is the same except instead of swapping
	you insert in the correct place and shift
	the rest of the array up to make room.
*/
void selection_sort(void *array, int len, int stride, bool (*compare)(void*, void*)) {
	char *arr = array;
	for (int i = 0; i < len-1; ++i) {
		char *min = arr+(i*stride);
		for (int j = i+1; j < len; ++j) {
			char *b = arr+(j*stride);
			if (compare(min, b)) {
				for (int k = 0; k < stride; ++k) {
					char swap = *(min+k);
					*(min+k) = *(b+k);
					*(b+k) = swap;
				}
			}
		}
	}
}

// todo: Heap sort?

#define copy_sort_item(dest, src)\
	{for (int ii = 0; ii < stride; ++ii)\
		*(dest+ii) = *(src+ii);}

void inner_merge_sort(char *array, int len, int stride, bool (*compare)(void*, void*), char *scratch) {
	int l = len/2;
	if (l > 0) {
		inner_merge_sort(array, l, stride, compare, scratch);
		inner_merge_sort(array+(l*stride), len-l, stride, compare, scratch+(l*stride));

		char *a = scratch;
		char *b = scratch+(l*stride);
		int ai = 0;
		int bi = 0;
		for (int k = 0; k < len; ++k) {
			if (ai < l && (bi >= len-l || compare(b+(bi*stride), a+(ai*stride)))) {
				copy_sort_item(array+(k*stride), a+(ai*stride));
				++ai;
			} else {
				copy_sort_item(array+(k*stride), b+(bi*stride));
				++bi;
			}
		}
		memcpy(scratch, array, len*stride);
	}
}
void merge_sort (void *array, int len, int stride, bool (*compare)(void*, void*)) {
	void *scratch = malloc(len*stride);
	memcpy(scratch, array, len*stride);
	inner_merge_sort(array, len, stride, compare, scratch);
	free(scratch);
}

// should key be void* ?
void *linear_search(int key, void *array, int len, int stride) {
	char *ptr = array;
	for (int i = 0; i < len; ++i) {
		int k = *(int*)ptr;
		if (k == key) return ptr;
		ptr += stride;
	}

	return NULL;
}

void *binary_search(int key, void *array, int len, int stride) {
	char *arr = array;
	int low = 0;
	int high = len-1;
	int index = high/2;
	while (low <= high) { // <= ?
		int k = *(int*)(arr+(stride*index));
		if (key < k) {
			high = index-1;
		} else if (key > k) {
			low = index+1;
		} else {
			// found it
			return arr+(stride*index);
		}
		index = low + (high-low)/2;
	}

	return NULL;
}

// todo: Interpolated binary search

int main() {
#if 0
	bool used[array_size(items)] = {0};
	for (int i = 0; i < array_size(items); ++i) {
		int r = rand()%array_size(items);
		while (used[r]) {
			r = rand()%array_size(items);
		}

		printf("%i,\t\"%s\",\n", items[r].key, items[r].str);
		used[r] = true;
	}
#endif

	printf("%lu items\n", sizeof(items)/sizeof(Item));

	FILE *out = fopen("out.txt", "w");

	#define print_items()\
		fprintf(out, "{\n");\
		for (int i = 0; i < array_size(items); ++i) {\
			fprintf(out, "\t%i %s\n", items[i].key, items[i].str);\
		}\
		fprintf(out, "}\n");

	print_items();
	// bubble_sort(items, array_size(items), sizeof(Item), int_compare_proc);
	// selection_sort(items, array_size(items), sizeof(Item), int_compare_proc);
	merge_sort(items, array_size(items), sizeof(Item), int_compare_proc);
	print_items();

	// Item *i = linear_search(57, items, array_size(items), sizeof(Item));
	int key = 1;
	Item *i = binary_search(key, items, array_size(items), sizeof(Item));
	if (i) {
		printf("item %i is '%s'\n", key, i->str);
	}

	// system("pause");
}