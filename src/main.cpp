#include <iostream> 
#include <algorithm>  
#include <cctype>
#include "class.hpp"


#define digit_roll_St 5
#define digit_roll_Fc 3
#define digit_roll_Lb 7


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
        
        Book* B1  = nullptr;
        Book* searched_book = nullptr;

        string user_type;
        string account_id,confirm_id; 
        string account_password,confirm_password;
        string book_title,book_ISBN,book_author,book_publisher,book_publishedyear;
        string access_key;
        string cmd;

        int overdue,fine, payment;


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
                cout << "You have entered a wrong userTYPE. Pls, re-enter your Preference."<< endl <<"      ---";
                goto TYPE;
            }

        
        STUDENT:
            if(countDigits(U1->user_roll) != digit_roll_St){
                cout << "\n You can't access the Library with Student Account"<<endl;
                goto EXIT;
            }

            
        
           
            cout << "\n Would You like to search for a book ? Y/n"<<endl <<"      ---";

            yesno = take("char").first;
            if(yesno == 'Y'|| yesno == 'y'){
                cout << "\nType the correct book title You want to search. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                getline(cin,book_title);
                cout << endl;
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"){
                    cout << "The library doesn't have this book. If You want to go for any other book. Re-enter title or Re-enter 'NIL'if You want to continue."<< endl <<"      ---";
                    getline(cin,book_title);
                    if(book_title =="NIL")goto START;
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }
                if(book_ISBN[0]=='B') book_ISBN.erase(0, 1);

                searched_book = (L.find_book(book_ISBN));
                searched_book->show_details(); 
            }
    
           
            START:
                St1 = L.find_student(U1->user_roll);
                
                if(St1 == nullptr){
                    cout << "\nU haven't any registered account in the Online Library. Do You want to register ? Y/n"<< endl <<"      ---";
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

                            L.add_student(U1->user_roll,account_id ,account_password);
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
                

                cout <<"\nHere are the books You borrowed !!"<< endl ;
                St1->print_books();
                cout <<"\nDo u want to see your browsing history ? Y/n"<< endl<<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y' || yesno == 'y') {
                    
                    St1->browse();
                }
                

                if(St1->number_books_borrowed() == max_limit_St) {
                    cout << "\n !! You have reached the maximum limit of books You can borrow !!\n \nWould You like to return any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y' || yesno == 'y') goto RETURN;
                    else goto EXIT;
                }
                else if(St1->number_books_borrowed() == 0){
                    cout << "\n As You haven't borrorwed any books lately! \n\nWould You like to borrow any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto BORROW;
                    else goto EXIT;

                }
                else{
                    cout << "\n Would You like to borrow any other book? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto BORROW;

                    cout << "\n Would You like to return? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto RETURN;
                    else goto EXIT;

                }

            //updation will start now
            BORROW:
                //overdue = St1->check_overdues();
                if(St1->fine()){cout << "\nYou haven't returned your overdue book and paid your overdues fine yet. Do u want to return now ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno =='y')goto RETURN;
                else {cout << "You have to first clear your dues to borrow any other book.\n";
                    goto EXIT;}}
                cout << "\nDo You want to see the list of books available ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno =='y'){
                    if(!L.print_books()){
                       
                        if(St1->number_books_borrowed() >0){
                            cout << "Do You want to return any book ? Y/n"<< endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'Y'|| yesno == 'y')goto RETURN;
                        }
                        else goto EXIT;
                    }
                    
                }

                cout << "\nType the correct book title You want to borrow. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"||book_ISBN[0]=='B'){
                    if(book_ISBN=="NIL")cout << "The library doesn't have this book. If You want to go for any other book. Re-enter"<< endl <<"      ---";
                    else if(book_ISBN[0]=='B')cout << "This book has been borrowed/reserved by someone and currently not available . If You want to go for any other book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }

                cout << "\n Are You sure You want to borrow " << book_title << " ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;

                if(yesno == 'N'|| yesno =='n')goto EXIT;


                B1 = L.find_book(book_ISBN);
                B1->change_status("Borrowed");
                B1->borrowed_user_roll = St1->user_roll;


                St1->add_book({book_title,book_ISBN},0);

                // update the datafile.
                L.borrow_book(St1->user_roll,book_title,book_ISBN,0);

                
                if(St1->number_books_borrowed() < max_limit_St){
                    cout << "Do You want to borrow any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto BORROW;
                }

                
                cout << "Do You want to return any book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto RETURN;
                

                goto EXIT;



                
            RETURN:
                cout << "\nType the correct book title You want to return. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                while(St1->check_book(book_title) == -1){
                    cout << "You have entered the book title incorrectly, or You haven't borrowed this book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                }

                cout << "\n Are You sure You want to return " << book_title << " ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;

                

                if(yesno == 'N'|| yesno =='n')goto EXIT;
                
                if(St1->return_days(St1->check_book(book_title)) > 15){
                    cout << "You have to pay overdues of Rs. "<< 10*(St1->return_days(St1->check_book(book_title)) - 15)<< " for this book.\n";
                    cout <<"-------------------$$$$$$$$    TRANSACTION  $$$$$$$$$-------------------\n"<<endl;
                }

                book_ISBN = St1->give_ISBN(St1->check_book(book_title));
                B1 = L.find_book(book_ISBN);
                B1->change_status("Available");
                B1->borrowed_user_roll = 0;


                St1->remove_book(St1->check_book(book_title));
                

                // update the datafile.
                L.return_book(St1->user_roll,book_title,book_ISBN,St1->return_days(St1->check_book(book_title)));
                
                if(St1->number_books_borrowed() > 0){
                    cout << "Do You want to return any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto RETURN;
                }

                
                cout << "Do You want to borrow any other book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto BORROW;
                

                goto EXIT;
                


                // borrow books;

                
            
        FACULTY:
            if(countDigits(U1->user_roll) != digit_roll_Fc){
                cout << "\n You can't access the Library with Faculty Account"<<endl;
                goto EXIT;
            }
            cout << "\n Would You like to search for a book ? Y/n"<<endl <<"      ---";

            yesno = take("char").first;
            if(yesno == 'Y'|| yesno == 'y'){
                cout << "\nType the correct book title You want to search. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                getline(cin,book_title);
                cout << endl;
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"){
                    cout << "The library doesn't have this book. If You want to go for any other book. Re-enter title or Re-enter 'NIL'if You want to continue."<< endl <<"      ---";
                    getline(cin,book_title);
                    if(book_title =="NIL")goto FSTART;
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }
                if(book_ISBN[0]=='B') book_ISBN.erase(0, 1);

                searched_book = L.find_book(book_ISBN);
                searched_book->show_details(); 
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
                


                cout <<"\nHere are the books You borrowed !!"<< endl ;
                Fc1->print_books();
                cout <<"\nDo u want to see your browsing history ? Y/n"<< endl<<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y' || yesno == 'y') {
                    
                    Fc1->browse();
                }

                if(Fc1->number_books_borrowed() == max_limit_Fc) {
                    cout << "\n !! You have reached the maximum limit of books You can borrow !!\n \nWould You like to return any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y' || yesno == 'y') goto FRETURN;
                    else goto EXIT;
                }
                else if(Fc1->number_books_borrowed() == 0){
                    cout << "\n As You haven't borrorwed any books lately! \n\nWould You like to borrow any book? Y/n" << endl <<"      ---"; 
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto FBORROW;
                    else goto EXIT;

                }
                else{
                    cout << "\n Would You like to borrow any other book? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto FBORROW;

                    cout << "\n Would You like to return? Y/n" << endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno =='y') goto FRETURN;
                    else goto EXIT;

                }
            //updation will start now
            FBORROW:
                if(Fc1->fine()){cout << "\nYou haven't returned your overdue book for over 60 days. Do u want to return now ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno =='y')goto RETURN;
                else {cout << "You have to first return book/s to borrow any other book.\n";
                    goto EXIT;}}
                
                cout << "\nDo You want to see the list of books available ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno =='y'){
                    if(!L.print_books()){
                        if(Fc1->number_books_borrowed() >0){
                            cout << "Do You want to return any book ? Y/n"<< endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'Y'|| yesno == 'y')goto FRETURN;
                        }
                        else goto EXIT;
                    }
                    
                }

                cout << "\nType the correct book title You want to borrow. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                book_ISBN = L.check_book_ISBN(book_title) ;
                while(book_ISBN == "NIL"||book_ISBN[0]=='B'){
                    if(book_ISBN=="NIL")cout << "The library doesn't have this book. If You want to go for any other book. Re-enter"<< endl <<"      ---";
                    else if(book_ISBN[0]=='B')cout << "This book has been borrowed/reserved by someone and currently not available . If You want to go for any other book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                    book_ISBN = L.check_book_ISBN(book_title) ;
                }

                cout << "\n Are You sure You want to borrow " << book_title << " ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;

                if(yesno == 'N'|| yesno =='n')goto EXIT;


                B1 = L.find_book(book_ISBN);
                B1->change_status("Borrowed");
                B1->borrowed_user_roll = Fc1->user_roll;


                Fc1->add_book({book_title,book_ISBN},0);

                // update the datafile.
                L.borrow_book(Fc1->user_roll,book_title,book_ISBN,0);

                
                if(Fc1->number_books_borrowed() < max_limit_Fc){
                    cout << "Do You want to borrow any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto FBORROW;
                }

                
                cout << "Do You want to return any book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto FRETURN;
                

                goto EXIT;



                
            FRETURN:
                cout << "\nType the correct book title You want to return. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                
                getline(cin,book_title);
                while(Fc1->check_book(book_title) == -1){
                    cout << "You have entered the book title incorrectly, or You haven't borrowed this book. Re-enter"<< endl <<"      ---";
                    getline(cin,book_title);
                }

                cout << "\n Are You sure You want to return " << book_title << " ? Y/n"<< endl <<"      ---";
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
                    cout << "Do You want to return any other book ? Y/n"<< endl <<"      ---";
                    yesno = take("char").first;
                    if(yesno == 'Y'|| yesno == 'y')goto FRETURN;
                }

                
                cout << "Do You want to borrow any other book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto FBORROW;
                

                goto EXIT;
            

        LIBRARIAN:
            if(countDigits(U1->user_roll) != digit_roll_Lb){
                cout << "\n You can't access the Library with Librarian Account"<<endl;
                goto EXIT;
            }

            
            Lb1 = L.find_librarian(U1->user_roll); 
            goto LLOGIN;





            LLOGIN:
            
                cout << "\nAccess Key. "<<endl <<"      ---";
                getline(cin,access_key);

                if(!Lb1->verify_account(access_key)){
                    goto LLOGIN;
                }

                cout << "If You want to manage any book ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto BOOK;

                cout << "If You want to manage any user ? Y/n"<< endl <<"      ---";
                yesno = take("char").first;
                if(yesno == 'Y'|| yesno == 'y')goto USER;



                BOOK:
                    cout << "\n Do search the book if it is in the Library or not."<<endl;
                    
                        cout << "\nType the correct book title You want to search. Please, be careful with spelling and whitespaces."<< endl <<"      ---";
                        getline(cin,book_title);
                        cout << endl;
                        book_ISBN = L.check_book_ISBN(book_title) ;
                        while(book_ISBN == "NIL"){
                            cout << "The library doesn't have this book. If You want to go for any other book or spelling mistak Re-enter title. or Re-enter 'ADD'if You want to add this book."<< endl <<"      ---";
                            getline(cin,book_title);
                            if(book_title =="ADD")goto ADD_BOOK;
                            book_ISBN = L.check_book_ISBN(book_title) ;
                        }
                        if(book_ISBN[0]=='B') book_ISBN.erase(0, 1);

                        searched_book = L.find_book(book_ISBN);
                        searched_book->show_details();
                        
                        if(searched_book->status == "Available"){
                            cout <<"The book is "<<searched_book->status;
                            cout << "\n Do you want to reserve this book ? Y/n"<<endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'Y'|| yesno == 'y'){ goto RESERVE;}

                            cout << "\n Do you want to remove this book ? Y/n"<<endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'Y'|| yesno == 'y'){ goto REMOVE_BOOK;}

                        }
                        else if (searched_book->status == "Reserved"){
                            cout <<"The book is "<<searched_book->status;
                            cout << "\n Do you want to un-reserve this book ? Y/n"<<endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'Y'|| yesno == 'y'){ goto RESERVE;}

                        }
                        else{
                            cout <<"The book is "<<searched_book->status;
                        }

                        cout << "\n Do you want to manage any other book ? Y/n"<<endl <<"      ---";
                        yesno = take("char").first;
                        if(yesno == 'N' || yesno =='n') goto EXIT;
                        else goto BOOK;
                        
                    
                    

                    ADD_BOOK:
                        cout << "\n Do you want to add this book for sure ? Y/n"<<endl <<"      ---";
                        yesno = take("char").first;
                        if(yesno == 'Y' || yesno =='y'){
                            cout << "Enter the details of the book carefully."<<endl;
                            cout << "Title" <<"      ---";
                            getline(cin,book_title);
                            book_ISBN = L.check_book_ISBN(book_title);
                            if(book_ISBN != "NIL"){
                                cout <<"Looks like this book is already in Library. Please search again.";
                                goto BOOK;
                            }
                            cout << "ISBN" <<"      ---";
                            getline(cin,book_ISBN);
                            cout << "Author" <<"      ---";
                            getline(cin,book_author);
                            cout << "Publisher" <<"      ---";
                            getline(cin,book_publisher);
                            cout << "Published Year" <<"      ---";
                            getline(cin,book_publishedyear);

                            L.add_book(book_title,book_ISBN,book_author,book_publishedyear,book_publisher,"Available");
                            
                        }


                        

                        cout << "\n Do you want to manage any other book ? Y/n"<<endl <<"      ---";
                        yesno = take("char").first;
                        if(yesno == 'N' || yesno =='n') goto EXIT;
                        else goto BOOK;
                    


                    RESERVE :
                        searched_book->status = searched_book->status == "Reserved" ? "Available": "Reserved";
                        L.change_stats(searched_book->status,book_title);
                        cout << "\n Do you want to manage any other book ? Y/n"<<endl <<"      ---";
                        yesno = take("char").first;
                        if(yesno == 'N' || yesno =='n') goto EXIT;
                        else goto BOOK;

                    REMOVE_BOOK :
                        
                        L.delete_book(book_title);
                        cout << "\n Do you want to manage any other book ? Y/n"<<endl <<"      ---";
                        yesno = take("char").first;
                        if(yesno == 'N' || yesno =='n') goto EXIT;
                        else goto BOOK;
                        
                        
                    USER:
                        cout<<"\nType ADD if u want to add a user or REMOVE to remove a user or NIL if u wan to exit"<<endl <<"      ---"; 
                        getline(cin,cmd);
                        while(cmd!="ADD" && cmd!= "REMOVE" && cmd != "NIL"){
                            cout << "Please type a valid command."<<endl <<"      ---";
                            getline(cin,cmd);
                        }  
                        
                        if(cmd == "ADD")goto ADD_USER;
                        else if(cmd == "NIL") goto EXIT;
                        else goto REMOVE_USER;


                        ADD_USER:
                            cout << "\nType new userROLL."<<endl <<"      ---";
                            user_roll = take("int").second;
                            if(!L.unfind_user(user_roll) )goto EXIT;
                            getline(cin, user_type);
                
                            if(user_type == ""){
                                getline(cin, user_type);
                            }
                
                            transform(user_type.begin(), user_type.end(), user_type.begin(),  
                                [](unsigned char c) { return toupper(c); });
                            U1->user_type.erase(remove_if(user_type.begin(), user_type.end(), 
                                [](char c) { return c == ' '; }), U1->user_type.end()); 
                
                
                            if(user_type == "STUDENT"){
                                if(countDigits(user_roll) != digit_roll_St) {
                                    cout << "Invalid count of digits in Roll !";
                                    goto ADD_USER;
                                }
                                L.output_add_student(user_roll);
                            }
                            else if (user_type == "FACULTY"){
                                if(countDigits(user_roll) != digit_roll_Fc) {
                                    cout << "Invalid count of digits in Roll !";
                                    goto ADD_USER;
                                }
                                cout <<"Account ID"<<endl <<"      ---";
                                getline(cin, account_id);
                                cout << "Account Password"<<endl <<"      ---";
                                getline(cin, account_password);
                                L.output_add_faculty(user_roll,account_id,account_password);
                            }
                            else if (user_type == "LIBRARIAN"){
                                if(countDigits(user_roll) != digit_roll_Lb) {
                                    cout << "Invalid count of digits in Roll !";
                                    goto ADD_USER;
                                }
                                cout <<"Access Key"<<endl <<"      ---";
                                getline(cin, access_key);
                                
                                L.output_add_librarian(user_roll,access_key);
                            }
                
                            else { 
                                cout << "You have entered a wrong userTYPE. Pls, re-enter the Preference."<< endl <<"      ---";
                                goto ADD_USER;
                            }
                            goto EXIT;


                        REMOVE_USER:
                            cout << "\nType the userROLL."<<endl <<"      ---";
                            user_roll = take("int").second;
                            cout << "\n Are you sure you wnt to remove this user ? Y/n"<<endl <<"      ---";
                            yesno = take("char").first;
                            if(yesno == 'N' || yesno =='n') goto EXIT;

                            if(countDigits(user_roll)==digit_roll_St){
                               St1 = (L.find_student(user_roll));
                               if(St1 ==nullptr)  L.output_remove_user(to_string(user_roll));
                               if(St1->number_books_borrowed() > 0){
                                    cout << "The User hasn't returned all his borrowed books, so , can't be removed.";
                                    goto EXIT;
                               }
                            }
                            else if(countDigits(user_roll)==digit_roll_Fc){
                                Fc1 = (L.find_faculty(user_roll));
                                if(Fc1->number_books_borrowed() > 0){
                                     cout << "The User hasn't returned all his borrowed books, so , can't be removed.";
                                     goto EXIT;
                                }
                            }

                            L.output_remove_user(to_string(user_roll));

                            goto EXIT;
        

        goto EXIT;
    

    EXIT : 
        cout << "\nThanks for the sesion using the Library.\n"<< endl;
        delete St1;
        delete Fc1;
        delete Lb1;
        delete B1;
        delete searched_book;
        delete U1;
        

    
}
