#include "../inc/film.hh"


int binar_search(Film arr[],int element,int l, int r)
    {
            int mid = l + (r-l)/2;
            if(l > r) return -1;

            if(arr[mid].id == element){
                return mid;
            }
            else if(arr[mid].id > element){
                return binar_search(arr,element,l,mid-1);
            }
            else{
                return binar_search(arr,element,mid+1,r);
            }
        
        
    }
