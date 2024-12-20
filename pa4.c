#include <stdio.h>
#include <stdlib.h>
#include <math.h>

This program is written by: Nagel Poulose */

typedef struct {
    int x, y;
} Point;

int userX, userY; 

// Functions to be used
int compareTo(const void *a, const void *b);
void readData(Point **garages, int *n, int *s, int *t, Point **queries);
void mergeSort(Point *array, int left, int right, int t);
void insertionSort(Point *array, int left, int right);
void sort(Point *array, int n, int t);
int binarySearch(Point *array, int left, int right, Point target);

int main() {
    int n, s, t;
    Point *garages, *queries;
    
    
    readData(&garages, &n, &s, &t, &queries);
    
    // calls the sort function to sort the garages by their distance to user's location
    sort(garages, n, t);

    // prints the sorted garages
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", garages[i].x, garages[i].y);
    }
    
    // processes each query
    for (int i = 0; i < s; i++) {
        int pos = binarySearch(garages, 0, n - 1, queries[i]);
        if (pos != -1) {
            printf("%d %d garage found at position %d in the order\n", queries[i].x, queries[i].y, pos + 1);
        } else {
            printf("%d %d no garage found\n", queries[i].x, queries[i].y);
        }
    }

    
    free(garages);
    free(queries);
    return 0;
}

// Function that calculates the squared distance 
int distanceSquared(Point p) {
    return (p.x - userX) * (p.x - userX) + (p.y - userY) * (p.y - userY);
}

// function that compares for sorting
int compareTo(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    int dist1 = distanceSquared(*p1);
    int dist2 = distanceSquared(*p2);
    
    if (dist1 != dist2) return dist1 - dist2; 
    if (p1->x != p2->x) return p1->x - p2->x; 
    return p1->y - p2->y; 
}

// takes in the data from the input
void readData(Point **garages, int *n, int *s, int *t, Point **queries) {
    scanf("%d %d %d %d %d", &userX, &userY, n, s, t);
    *garages = (Point *)malloc((*n) * sizeof(Point));
    *queries = (Point *)malloc((*s) * sizeof(Point));
    
    for (int i = 0; i < *n; i++) {
        scanf("%d %d", &(*garages)[i].x, &(*garages)[i].y);
    }
    for (int i = 0; i < *s; i++) {
        scanf("%d %d", &(*queries)[i].x, &(*queries)[i].y);
    }
}

// the wrapper for the sorting function
void sort(Point *array, int n, int t) {
    mergeSort(array, 0, n - 1, t);
}

// the merge sort and insertion done recursively 
void mergeSort(Point *array, int left, int right, int t) {
    if (right - left + 1 <= t) {
        insertionSort(array, left, right);
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(array, left, mid, t);
    mergeSort(array, mid + 1, right, t);
    
    // merges the sorted halves
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Point *L = (Point *)malloc(n1 * sizeof(Point));
    Point *R = (Point *)malloc(n2 * sizeof(Point));
    for (int i = 0; i < n1; i++) L[i] = array[left + i];
    for (int i = 0; i < n2; i++) R[i] = array[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareTo(&L[i], &R[j]) <= 0) array[k++] = L[i++];
        else array[k++] = R[j++];
    }
    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];
    
    free(L);
    free(R);
}

// inserting sort function
void insertionSort(Point *array, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Point key = array[i];
        int j = i - 1;
        while (j >= left && compareTo(&array[j], &key) > 0) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// function that uses binary search within a sorted array
int binarySearch(Point *array, int left, int right, Point target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compareTo(&array[mid], &target);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // Target not found
}
