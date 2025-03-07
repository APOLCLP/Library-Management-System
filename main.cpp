#include <iostream> 
#include <algorithm>  
#include <cctype>
#include "class.hpp"


#define digit_roll_St 5
#define digit_roll_Fc 3
int countDigits(int number) {  
    if (number == 0) {  
        return 1;  
    }  

    int count = 0;  
    unsigned int n = std::abs(number); 

    while (n > 0) {  
        n /= 10;  
        count++;  
    }  
    return count;  
}


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
            

        User* U1 = nullptr;
        Student* St1 = nullptr;
        Faculty* Fc1 = nullptr;
        Librarian* Lb1 = nullptr;
        Book* Search_book = nullptr;
        Book* B1  = nullptr;

        string account_id,confirm_id; 
        string account_password,confirm_password;
        string book_title,book_ISBN;


        U1 = new User(user_roll);

        if(!L.find_user(user_roll) )goto EXIT;
        

        
        
        TYPE :

            getline(cin, U1->user_type);
            
            if(U1->user_type == ""){
                getline(cin, U1->user_type);
            }

            transform(U1->user_type.begin(), U1->user_type.end(), U1->user_type.begin(),  
                [](unsigned char c) { return toupper(c); });
            U1->user_type.erase(remove_if(U1->user_type.begin(), U1->user_type.end(), 
                [](char c) { return c == ' '; }), U1->user_type.end()); 


            if(U1->user_type == "STUDENT") goto STUDENT;
            else if (U1->user_type == "FACULTY") goto FACULTY;
            else if (U1->user_type == "LIBRARIAN") goto LIBRARIAN;

            else { 
                cout << "U have entered a wrong userTYPE. Pls, re-enter ur Preference."<< endl <<"      ---";
                goto TYPE;
            }

        
        STUDENT:
            if(countDigits(U1->user_roll) != digit_roll_St){
                cout << "\n U can't access the Library with Student Account"<<endl;
                goto EXIT;
            }

            
        
           
            cout << "\n Would u like to search for a book ? Y/n"<<endl <<"      ---";

            yesno = take("char").first;
            if(yesno == 'Y'|| yesno == 'y'){
                cout << "\nType the correct book title u want to search. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                getline(cin,book_title);
                cout << endl;
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"){
                    cout << "The library doesn't have this book. If U want to go for any other book. Re-enter title or Re-enter 'NIL'if u want to continue."<< endl <<"      ---";
                    getline(cin,book_title);
                    if(book_title =="NIL")goto START;
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }
                if(book_ISBN[0]=='B') book_ISBN.erase(0, 1);

                Book searched_book = *(L.find_book(book_ISBN));
                searched_book.show_details(); 
            }
    
           
            START:
                St1 = L.find_student(U1->user_roll);
                
                if(St1 == nullptr){
                    cout << "\nU haven't any registered account in the Online Library. Do u want to register ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y'){
                        REGISTER:
                            cout << "\nPlease, set your Account ID."<< endl <<"      ---";
                            getline(cin,account_id);
                            cout << "Please, set your Account Password."<< endl<<"      ---";
                            getline(cin,account_password);
                            cout << "Please, confirm your Account ID and Password as it can't be changed again."<< endl<<"      ---";
                            getline(cin,confirm_id);
                            cout<<"      ---";
                            getline(cin, confirm_password);

                            if(account_id != confirm_id || account_password != confirm_password){
                                cout << "You haven't confirm your details correctly.";
                                goto REGISTER;
                            }

                            
                            //output data
                            L.output_data_register(U1->user_roll,confirm_id,confirm_password);


                    }

                    goto EXIT;
                    
                }
                else goto LOGIN;





            LOGIN:
            
                cout << "\nType your Account details. "<<endl <<"      ID  ---";
                getline(cin,account_id);
                cout <<"      PASSWORD  ---";
                getline(cin,account_password);

                if(!St1->verify_account(account_id,account_password)){
                    goto LOGIN;
                }
                

                cout <<"\nHere are the books u borrowed !!"<< endl ;
                St1->print_books();

                if(St1->number_books_borrowed() == max_limit_St) {
                    cout << "\n !! U have reached the maximum limit of books u can borrow !!\n \nWould u like to return any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y' || yesno == 'y') goto RETURN;
                    else goto EXIT;
                }
                else if(St1->number_books_borrowed() == 0){
                    cout << "\n As U haven't borrorwed any books lately! \n\nWould u like to borrow any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto BORROW;
                    else goto EXIT;

                }
                else{
                    cout << "\n Would u like to borrow any other book? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto BORROW;

                    cout << "\n Would u like to return? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto RETURN;
                    else goto EXIT;

                }

            //updation will start now
            BORROW:
                cout << "\nDo u want to see the list of books available ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno =='y'){
                    if(!L.print_books()){
                       
                        if(St1->number_books_borrowed() >0){
                            cout << "Do u want to return any book ? Y/n"<< endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'Y'|| yesno == 'y')goto RETURN;
                        }
                        else goto EXIT;
                    }
                    
                }

                cout << "\nType the correct book title u want to borrow. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"||book_ISBN == "NUL"){
                    if(book_ISBN=="NIL")cout << "The library doesn't have this book. If U want to go for any other book. Re-enter"<< endl <<"      ---";
                    else if(book_ISBN[0]=='B')cout << "This book has been borrowed by someone and currently not available . If U want to go for any other book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }

                cout << "\n Are u sure U want to borrow " << book_title << " ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;

                if(yesno == 'N'|| yesno =='n')goto EXIT;


                B1 = L.find_book(book_ISBN);
                B1->change_status("Borrowed");
                B1->borrowed_user_roll = St1->user_roll;


                St1->add_book({book_title,book_ISBN},0);

                // update the datafile.
                L.borrow_book(St1->user_roll,book_title,book_ISBN,0);

                
                if(St1->number_books_borrowed() < max_limit_St){
                    cout << "Do u want to borrow any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto BORROW;
                }

                
                cout << "Do u want to return any book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto RETURN;
                

                goto EXIT;



                
            RETURN:
                cout << "\nType the correct book title u want to return. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                while(St1->check_book(book_title) == -1){
                    cout << "U have entered the book title incorrectly, or u haven't borrowed this book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                }

                cout << "\n Are u sure U want to return " << book_title << " ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;

                

                if(yesno == 'N'|| yesno =='n')goto EXIT;

                book_ISBN = St1->give_ISBN(St1->check_book(book_title));
                B1 = L.find_book(book_ISBN);
                B1->change_status("Available");
                B1->borrowed_user_roll = 0;


                St1->remove_book(St1->check_book(book_title));
                

                // update the datafile.
                L.return_book(St1->user_roll,book_title,book_ISBN,St1->return_days(St1->check_book(book_title)));
                
                if(St1->number_books_borrowed() > 0){
                    cout << "Do u want to return any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto RETURN;
                }

                
                cout << "Do u want to borrow any other book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto BORROW;
                

                goto EXIT;
                


                // borrow books;

                
            
        FACULTY:
            if(countDigits(U1->user_roll) != digit_roll_Fc){
                cout << "\n U can't access the Library with Faculty Account"<<endl;
                goto EXIT;
            }
            cout << "\n Would u like to search for a book ? Y/n"<<endl <<"      ---";

            yesno = take("char").first;
            if(yesno == 'Y'|| yesno == 'y'){
                cout << "\nType the correct book title u want to search. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                getline(cin,book_title);
                cout << endl;
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"){
                    cout << "The library doesn't have this book. If U want to go for any other book. Re-enter title or Re-enter 'NIL'if u want to continue."<< endl <<"      ---";
                    getline(cin,book_title);
                    if(book_title =="NIL")goto FSTART;
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }
                if(book_ISBN[0]=='B') book_ISBN.erase(0, 1);

                Book searched_book = *(L.find_book(book_ISBN));
                searched_book.show_details(); 
            }

    
            FSTART:
                Fc1 = L.find_faculty(U1->user_roll);
                
                
                goto FLOGIN;





            FLOGIN:
            
                cout << "\nType your Account details. "<<endl <<"      ID  ---";
                getline(cin,account_id);
                cout <<"      PASSWORD  ---";
                getline(cin,account_password);

                if(!Fc1->verify_account(account_id,account_password)){
                    goto FLOGIN;
                }
                


                cout <<"\nHere are the books u borrowed !!"<< endl ;
                Fc1->print_books();

                if(Fc1->number_books_borrowed() == max_limit_Fc) {
                    cout << "\n !! U have reached the maximum limit of books u can borrow !!\n \nWould u like to return any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y' || yesno == 'y') goto FRETURN;
                    else goto EXIT;
                }
                else if(Fc1->number_books_borrowed() == 0){
                    cout << "\n As U haven't borrorwed any books lately! \n\nWould u like to borrow any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto FBORROW;
                    else goto EXIT;

                }
                else{
                    cout << "\n Would u like to borrow any other book? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto FBORROW;

                    cout << "\n Would u like to return? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto FRETURN;
                    else goto EXIT;

                }
            //updation will start now
            FBORROW:
                cout << "\nDo u want to see the list of books available ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno =='y'){
                    if(!L.print_books()){
                        if(Fc1->number_books_borrowed() >0){
                            cout << "Do u want to return any book ? Y/n"<< endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'Y'|| yesno == 'y')goto FRETURN;
                        }
                        else goto EXIT;
                    }
                    
                }

                cout << "\nType the correct book title u want to borrow. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"||book_ISBN == "NUL"){
                    if(book_ISBN=="NIL")cout << "The library doesn't have this book. If U want to go for any other book. Re-enter"<< endl <<"      ---";
                    else if(book_ISBN[0]=='B')cout << "This book has been borrowed by someone and currently not available . If U want to go for any other book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }

                cout << "\n Are u sure U want to borrow " << book_title << " ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;

                if(yesno == 'N'|| yesno =='n')goto EXIT;


                B1 = L.find_book(book_ISBN);
                B1->change_status("Borrowed");
                B1->borrowed_user_roll = Fc1->user_roll;


                Fc1->add_book({book_title,book_ISBN},0);

                // update the datafile.
                L.borrow_book(Fc1->user_roll,book_title,book_ISBN,0);

                
                if(Fc1->number_books_borrowed() < max_limit_Fc){
                    cout << "Do u want to borrow any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto FBORROW;
                }

                
                cout << "Do u want to return any book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto FRETURN;
                

                goto EXIT;



                
            FRETURN:
                cout << "\nType the correct book title u want to return. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                while(Fc1->check_book(book_title) == -1){
                    cout << "U have entered the book title incorrectly, or u haven't borrowed this book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                }

                cout << "\n Are u sure U want to return " << book_title << " ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;

                

                if(yesno == 'N'|| yesno =='n')goto EXIT;

                book_ISBN = Fc1->give_ISBN(Fc1->check_book(book_title));
                B1 = L.find_book(book_ISBN);
                B1->change_status("Available");
                B1->borrowed_user_roll = 0;


                Fc1->remove_book(Fc1->check_book(book_title));
                

                // update the datafile.
                L.return_book(Fc1->user_roll,book_title,book_ISBN,Fc1->return_days(Fc1->check_book(book_title)));
                
                if(Fc1->number_books_borrowed() > 0){
                    cout << "Do u want to return any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto FRETURN;
                }

                
                cout << "Do u want to borrow any other book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto FBORROW;
                

                goto EXIT;
            

        LIBRARIAN:

            

        

        goto EXIT;
        //User U1;

    







    // User U1;
    // try {U1->valid();}
    // catch(...){
    //     goto end;
    // }

    EXIT : 
        cout << "\nThanks for the sesion using the Library.\n"<< endl;
        delete St1;
        delete Fc1;
        delete Lb1;

    
}
