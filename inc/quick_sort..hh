#ifndef QUICK_SORT
#define QUICK_SORT
#pragma once

#include <iostream>


/**
 * @brief funkcja dzielaca 
 * 
 * @tparam T typ zmiennej
 * @param arr tablica
 * @param left lewy indeks 
 * @param right prawy indeks
 * @return int pivot
 */
template <typename T>
int Partition(T* arr, int left, int right) 
{
    T temp, pivot = arr[(left + right) / 2];  // element srodkowy
    int l = left, r = right;                    // iteratory dla podtablic lewej i prawej
    while(1){
        while (arr[l] < pivot) l++;  // dopoki po lewej sa mniejsze od srodkowego
        while (arr[r] > pivot) r--;  // dopoki po prawej sa wieksze od srodkowego

        if(l >= r)
            return r;  // element osiowy

        // zamien elementy - mniejszy na lewo, wiekszy na prawo
        temp = arr[l];
        arr[l++] = arr[r];
        arr[r--] = temp;
    }
}


/**
 * @brief funkcja quicksorta
 * 
 * @tparam T typ zmiennej
 * @param arr tablicca do posortowania
 * @param left lewy indeks
 * @param right prawy indeks
 */
template <typename T>
void Quicksort(T* arr, int left, int right) 
{
    // dziele na 2 tablice az beda jednoelementowe
    if(left >= 0 && left < right) {
        int pivot = Partition(arr, left, right);  // pivot
        Quicksort(arr, left, pivot);            // lewa podtablica
        Quicksort(arr, pivot + 1, right);          // prawa podtablica
    }
}
#endif