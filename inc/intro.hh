#ifndef INTRO
#define INTRO

#pragma once

#include <algorithm>
#include <cmath>

#include "../inc/quick_sort..hh"

/**
 * @brief sortowanie przez scalenie
 * 
 * @tparam T 
 * @param arr 
 * @param start 
 * @param end 
 */
template <typename T>
void insertionSort(T* arr, int start, int end) 
{
    T key;  // klucz (do porownywania)
    int i, j;
    for(i = start + 1; i < end; i++) {
        key = arr[i];  // zaczynamy od 2 elementu arrlicy
        j = i - 1;
        // porownanie klucza z kolejnymi poprzednimi elementami
        while(j >= start && key < arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void heapify(T* arr, int heap_size, int i) 
{
    T temp;
    int largest, l = 2 * i, r = (2 * i) + 1;
    if(l <= heap_size && arr[l] > arr[i])
        largest = l;
    else
        largest = i;
    if(r <= heap_size && arr[r] > arr[largest])
        largest = r;
    if(largest != i) {
        temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
        heapify(arr, heap_size, largest);
    }
}


/**
 * @brief sortowanie przez kopcowanie
 * 
 * @tparam T 
 * @param arr 
 * @param heap_size 
 */
template <typename T>
void heapSort(T* arr, int heap_size) 
{
    T temp;
    for (int i = heap_size / 2; i > 0; i--)
        heapify(arr, heap_size, i);
    for (int i = heap_size; i > 1; i--) {
        temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;
        heap_size--;
        heapify(arr, heap_size, 1);
    }
}


/**
 * @brief sortowanie introspektywne
 * 
 * @tparam T 
 * @param arr 
 * @param start 
 * @param end 
 * @param maxdepth 
 */
template <typename T>
void introSort(T* arr, int start, int end, int maxdepth) 
{
    if(maxdepth <= 0) {
        heapSort(arr, end - start);
        return;
    }
    int i = Partition(arr, start, end);
    if(i > 9)
        introSort(arr, start, i, maxdepth - 1);
    if(end - i > 9)
        introSort(arr, i + 1, end, maxdepth - 1);
}


/**
 * @brief sortowanie introspektywne hybryda
 * 
 * @tparam T 
 * @param arr 
 * @param start 
 * @param end 
 */
template <typename T>
void hybridIntroSort(T* arr, int start, int end) 
{
    introSort(arr, start, end, (2 * log(end - start)));
    insertionSort(arr, start, end);
}

#endif