#include "../inc/menu.hh"



void run_menu(){

    int choice=0;
    int option=0;
    int elements[5] = {10000,100000,500000,1000000,1295779};


    //tu wczytam plik

struct Film film_test[10000];
int iterator=0;
int filtered=0;
int sort_type=0;
std::cout << "wczytanie pliku" << std::endl;

    std::ifstream inputFile;       //plik wejsciowy
    inputFile.open("../data.tsv");
    std::string line = "";
    std::string skip;              //string do pominiecia
    std::getline(inputFile,skip);  //pominiecie nazw kolumn

    while (getline(inputFile, line)) { // i iteratorr rozny odd element[n]

        std::stringstream inputString(line);

        //int file_id;
        float file_rating=0;
        int file_votes=0;
        std::string tempString;

        inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
        //getline(inputString, tempString, '\t');
        //file_id = atoi(tempString.c_str());


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
        film_test[iterator].id = iterator + 1; 
        film_test[iterator].votes = file_votes;
        
        line = "";
        iterator++;
    }




     do{
        std::cout << "----------------------------------" << std::endl;
        std::cout << "|              Menu               |" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << "|             Opcje:              |" << std::endl;
        std::cout << "| 1. Posortuj plik                |" << std::endl;
        std::cout << "| 2. Wyszukaj tytul               |" << std::endl;
        std::cout << "| 3. Koniec                       |" << std::endl;       
        std::cout << "-----------------------------------" << std::endl;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        switch(choice)
        {
            case 1:
            {
                while(sort_type != 1 || sort_type != 2 || sort_type != 3){
                std::cout << "Typ sortowania" << std::endl;
                std::cout << "1. 10000 " << std::endl;
                std::cout << "2. 100000 " << std::endl;
                std::cout << "3. 500000 " << std::endl;
                std::cin >> sort_type;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                }

                    std::cout << "Stopien posortowania bazy danych: " << std::endl;
                    std::cout << "1. 10000 " << std::endl;
                    std::cout << "2. 100000 " << std::endl;
                    std::cout << "3. 500000 " << std::endl;
                    std::cout << "4. 1000000 " << std::endl;
                    std::cout << "5. caly plik " << std::endl;
                    
                    std::cin >> option;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

                    switch(option){
                        case 1:{
                            //sortowanie 10000 i wyswietlenei czasu 
                            
                            mergeSort(film_test,0,elements[0]);
                            break;
                        }
                        case 2:{
                            // sortowanie 100000
                            break;
                        }
                        case 3:{
                            //sortowanie 500000
                            break;
                        }
                        case 4:{
                            //sortowanie 1000000
                            break;
                        }
                        case 5:{
                            //sortowanie calego
                            break;
                        }
                        default:{
                            break;
                        }
                    }

                break;
            }
            case 2:
            {
                // biore oryginalny plik i szukam id
                std::cout << "Wpisz id filmu, ktory chcesz znalezc: " << std::endl;
                std::cin >> option; 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

                // binary search w pliku duzym po id 

                break;
            }
            default:
            {
                if(choice !=3)
                    std::cout << "Niepoprawna opcja" << std::endl;
                break;
            }
        }
     }while(choice != 3);

    std::ofstream output_file;
    output_file.open("../out.tsv");

    output_file << "tconst" << '\t' << "averageRating" << '\t' << "numVotes" << std::endl; 
    for(int i=0;i<9;i++){
        output_file << film_test[i].id << '\t' << film_test[i].rating << '\t' << film_test[i].votes << std::endl;
    }
    output_file.close();
    inputFile.close();
}

