#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>

#include "../inc/quick_sort..hh"
#include "../inc/merge_sort.hh"
#include "../inc/intro.hh"
#include "../inc/binary_search.hh"
#include "../inc/film.hh"
#include "../inc/film.hh"

#include <vector>
#define SIZE 9735227


void run_sort_menu()
{
    int size=0;
    int elements[5] = {10000,100000,500000,1000000,1295779};
                    std::cout << "----------------------------------" << std::endl;
                    std::cout << "Stopien posortowania bazy danych: " << std::endl;
                    std::cout << "1. 10000 " << std::endl;
                    std::cout << "2. 100000 " << std::endl;
                    std::cout << "3. 500000 " << std::endl;
                    std::cout << "4. 1000000 " << std::endl;
                    std::cout << "5. caly plik " << std::endl;
                    std::cout << "----------------------------------" << std::endl;
                    std::cout << "Twoj wybor: ";
                    
                    std::cin >> size;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        
        struct Film *film_test = new Film[elements[size-1]];
            
        

    //tu wczytam plik

    //struct Film film_test[10000];
    int iterator=0;
    int filtered=0;
    int sort_type=0;
    float sum=0;
    float avg=0;
    float median=0;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "wczytanie pliku" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    std::ifstream inputFile;       //plik wejsciowy
    inputFile.open("../data.tsv");
    std::string line = "";
    std::string skip;              //string do pominiecia
    std::getline(inputFile,skip);  //pominiecie nazw kolumn

    while (getline(inputFile, line) && iterator < elements[size-1]) { // i iteratorr rozny odd element[n]

        std::stringstream inputString(line);

        int file_id;
        float file_rating=0;
        int file_votes=0;
        std::string tempString;
        std::string remove = "tt";

        //inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
        getline(inputString, tempString, '\t');
        tempString.erase(0,remove.length());
        file_id = atoi(tempString.c_str());


        getline(inputString, tempString, '\t');
        file_rating = atof(tempString.c_str());

        getline(inputString, tempString, '\t');
        file_votes = atoi(tempString.c_str());
        if(file_rating > 0){

        film_test[iterator].rating = file_rating;
        }
        else{
            film_test[iterator].rating = -1;
            filtered++;
            }
        film_test[iterator].id = file_id; 
        film_test[iterator].votes = file_votes;
        
        line = "";
        iterator++;
        sum = sum+file_rating;
    }
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Po filtrowaniu" << elements[size-1] - filtered << std::endl;
    std::cout << "----------------------------------" << std::endl;

    avg = sum /( elements[size-1] - filtered );
    if((elements[size-1] - filtered )% 2 != 0){
        median = film_test[(elements[size-1] - filtered)/2].rating;
    }
    else{
        median = (film_test[(elements[size-1] - filtered - 1)/2].rating + film_test[(elements[size-1] - filtered)/2].rating)/2;

    }
    std::cout << "----------------------------------" << std::endl;
    std::cout <<"sredni wynik: " << avg << std::endl;
    std::cout <<"mediana: " << median << std::endl;
    std::cout << "----------------------------------" << std::endl;



                std::cout << "Typ sortowania" << std::endl;
                std::cout << "1. merge " << std::endl;
                std::cout << "2. intro " << std::endl;
                std::cout << "3. quick " << std::endl;
                std::cout << "Twoj wybor: ";
                std::cin >> sort_type;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    switch(sort_type){
        case 1:{
            std::cout << " Wybrana opcja: merge" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            mergeSort(film_test,0,elements[size-1] -1);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::milli>(stop-start);
            std::cout << "czas sortowania " << duration.count() << std::endl;
            break;
        }    
        case 2:{
            std::cout << " Wybrana opcja: introsort" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            hybridIntroSort(film_test,0,elements[size-1] - 1);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::milli>(stop-start);
            std::cout << "czas sortowania " << duration.count() << std::endl;
            break;
        }
        case 3:{
            std::cout << " Wybrana opcja: quicksort" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            Quicksort(film_test,0,elements[size-1] - 1);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::milli>(stop-start);
            std::cout << "czas sortowania [ms]" << duration.count() << std::endl;
            break;
        }
        default:
            std::cout << " niepoprawna opcja " << std::endl;
            break;       
    }
    
   
    std::ofstream output_file;
    output_file.open("../out.tsv");

    output_file << "tconst" << '\t' << "averageRating" << '\t' << "numVotes" << std::endl; 
    for(int i=0;i<elements[size-1];i++){
        output_file << film_test[i].id << '\t' << film_test[i].rating << '\t' << film_test[i].votes << std::endl;
    }
    output_file.close();
    inputFile.close();
}

void run_search_menu()
{
    struct Film *film_search = new Film[SIZE];
    int iterator=0;
    std::cout << "wczytanie pliku" << std::endl;

    std::ifstream inputFile;       //plik wejsciowy
    inputFile.open("../referencyjne.txt");
    std::string line = "";
    std::string skip;              //string do pominiecia
    std::getline(inputFile,skip);  //pominiecie nazw kolumn

    while (getline(inputFile, line))         //wczytanie pliku z tytulami
     { 
        std::stringstream inputString(line);
        std::string tempString;
        std::string file_title;
        std::string skiper;
        int file_id;
        std::string remove = "tt";

        //inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
        getline(inputString, tempString, '\t');
       // std::cout << tempString << std::endl;
        tempString.erase(0,remove.length());
        //std::cout << tempString << std::endl;
        file_id = atoi(tempString.c_str());
        //std::cout << file_id << std::endl;
        film_search[iterator].id = file_id;
        
        getline(inputString, skiper, '\t');
        getline(inputString, skiper, '\t');

        //inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
        //inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');

        getline(inputString, file_title, '\t');
        film_search[iterator].title = file_title;
        
        line = "";
        iterator++;
    }
    inputFile.close();

    std::cout << "wczytanie ratingu" << std::endl;
    std::ifstream inputFile2;       //plik wejsciowy
    inputFile2.open("../data.tsv");
    std::string line2 = "";
    std::string skip2;              //string do pominiecia
    std::getline(inputFile2,skip2);  //pominiecie nazw kolumn
    struct Film *film_test = new Film[1295779];
    iterator = 0;

    while (getline(inputFile2, line2)) 
    { // i iteratorr rozny odd element[n]

        std::stringstream inputString(line2);

        int file_id;
        float file_rating=0;
        int file_votes=0;
        std::string tempString;
        std::string remove = "tt";

        //inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
        getline(inputString, tempString, '\t');
        tempString.erase(0,remove.length());
        file_id = atoi(tempString.c_str());



        getline(inputString, tempString, '\t');
        file_rating = atof(tempString.c_str());

        getline(inputString, tempString, '\t');
        file_votes = atoi(tempString.c_str());
        

        film_test[iterator].rating = file_rating;
        film_test[iterator].id = file_id; 
        film_test[iterator].votes = file_votes;
        
        line2 = "";
        iterator++;
    }

    

    /*
        std::cout << "Wpisz id do wyszukania tytulu: ";          
        std::cin >> searchfor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        int result = binar_search(film_search,searchfor,0,SIZE -1);
        std::cout << "Tytul filmu: " << film_search[result].title << std::endl;
    */
   int sort_type=0;
   std::cout << "Algorytm sortowania: " <<std::endl;
   std::cout << "1. merge 2. intro 3.quick " << std::endl;
   std::cin >> sort_type;
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    switch(sort_type){
        case 1:{
            std::cout << " Wybrana opcja: merge" << std::endl;
            mergeSort(film_test,0,1295779 - 1);
            break;
        }    
        case 2:{
            std::cout << " Wybrana opcja: introsort" << std::endl;
            
            hybridIntroSort(film_test,0,1295779 - 1);
            
            break;
        }
        case 3:{
            std::cout << " Wybrana opcja: quicksort" << std::endl;
            Quicksort(film_test,0,1295779 - 1);
            break;
        }
        default:
            std::cout << " niepoprawna opcja " << std::endl;
            break;       
    }
    
    
    for(int i=0; i < 1295779; i++)
    {
        int result = binar_search(film_search,film_test[i].id,0,SIZE-1);
        if(result >= 0)
            film_test[i].title = film_search[result].title;
        else{
            film_test[i].title = "untitled";
        }
    }
     


    std::ofstream output_file;
    output_file.open("../out2.tsv");

    output_file << "tconst" << '\t' << "averageRating" << '\t' << "numVotes"  << '\t' << "title" << std::endl; 
    for(int i=0;i<1295779;i++){
        output_file << film_test[i].id << '\t' << film_test[i].rating << '\t' << film_test[i].votes << '\t' << film_test[i].title << std::endl;
    }
    output_file.close();
    inputFile2.close();

    

     //zapis do pliku dla sprawedzenia

     /*
        std::ofstream output_file;
        output_file.open("../out1.tsv");

        output_file << "tconst" << '\t' << "title" << std::endl; 
        for(int i=0;i<SIZE -1;i++){
            output_file << film_search[i].id << '\t' << film_search[i].title << '\t' << std::endl;
        }
        */
        
        //output_file.close();
}


int main()
{
    int choice;
 do{
        std::cout << "----------------------------------" << std::endl;
        std::cout << "|              Menu               |" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << "|             Opcje:              |" << std::endl;
        std::cout << "| 1. Posortuj plik                |" << std::endl;
        std::cout << "| 2. Wyszukaj tytul               |" << std::endl;
        std::cout << "| 3. Koniec                       |" << std::endl;       
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Twoj wybor: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        switch(choice)
        {
            case 1:
            {
                run_sort_menu();
                return 0;
            }
            case 2:
            {
                run_search_menu();
                return 0;
            }
            default:
            {
                if(choice !=3)
                    std::cout << "Niepoprawna opcja" << std::endl;
                break;
            }
        }
     }while(choice != 3);

}

