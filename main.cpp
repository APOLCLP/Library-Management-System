#include <iostream> 
#include <algorithm>  
#include <cctype>
#include "class.hpp"


pair<char,int> take (string datatype){
    pair<char,int> result = {'0',0};
    bool option = datatype == "char" ? true : false;
    if(option){
        char input;

        cin >> input;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // the input here will take the first letter as account.
        while(input !='Y'&& input != 'y'&&  input != 'N'&&  input !='n'){
            cout << "Please, enter a valid input" << endl <<"      ---";
            cin >> input;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        
        result.first = input;
    }
    else {
        int input;
        cin >> input;

        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease, enter a valid input"<<endl<<"      ---";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        result.second = input;

    }
    return result;
}
    



int main(){
    Library L;


    L.input_data();
    
    
    char yesno;
    

    // i am starting from the interaction thing first and will do library intitial condition later.

   

    ENTER:
        cout << "\n     Hello, Welcome to online Library !\n";
                    
        cout << "\nType your userROLL."<<endl <<"      ---";
        int user_roll = take("int").second;

        // the input will be accepted if a number is given , else re-enter.
            

        User U1;
        Student* St1 = nullptr;
        Faculty* Fc1 = nullptr;
        Librarian* Lb1 = nullptr;


        try {User U1(user_roll);}
        catch(const char* msg){
            cout << msg<< endl;
            goto EXIT;
        }

        
        
        TYPE :

            getline(cin, U1.user_type);
            
            if(U1.user_type == ""){
                getline(cin, U1.user_type);
            }

            transform(U1.user_type.begin(), U1.user_type.end(), U1.user_type.begin(),  
                [](unsigned char c) { return toupper(c); });
            U1.user_type.erase(remove_if(U1.user_type.begin(), U1.user_type.end(), 
                [](char c) { return c == ' '; }), U1.user_type.end()); 


            if(U1.user_type == "STUDENT") goto STUDENT;
            else if (U1.user_type == "FACULTY") goto FACULTY;
            else if (U1.user_type == "LIBRARIAN") goto LIBRARIAN;

            else { 
                cout << "U have entered a wrong userTYPE. Pls, re-enter ur Preference."<< endl <<"      ---";
                goto TYPE;
            }

        
        STUDENT:
        
            St1 = new Student();
            goto PROFILE;
            
            // St1->user_roll = U1.user_roll;
            
            // if(St1->is_registered()){
            //         goto PROFILE;
            // }
            // else //register





            PROFILE:
            
                *St1 = L.find_student(U1.user_roll);
                cout <<"Would u want to check the books u borrowed? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y' || yesno == 'y')St1->print_books();

                if(St1->number_books_borrowed() == max_limit_St) {
                    cout << "U have reached the maximum limit of books u can borrowed. \nWould u like to return any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    //if(yesno == 'Y' || yesno == 'y') goto RETURN;
                }


                // borrow books;

                
            
        FACULTY:
            

        LIBRARIAN:

            

        

        goto EXIT;
        //User U1;

    







    // User U1;
    // try {U1.valid();}
    // catch(...){
    //     goto end;
    // }

    EXIT : 
        cout << "Thanks for the session."<< endl;
        delete St1;
        delete Fc1;
        delete Lb1;

    
}
