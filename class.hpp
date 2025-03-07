#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int max_limit_St = 3;
int max_limit_Fc = 5;



class User{
     
    public:
        
        int user_roll;
        string user_type;

        User(){}
        User( int roll): user_roll(roll){       
        };



};

class Account{
    protected : 
        string account_id;
        string account_password;
        vector<pair<string,string>> borrowed_books;
        vector<int> overdues;

    public : 

    


};

class Book{
    private :
        string title; 
        string ISBN;
        string author;
        string published_year;
        string publisher;
        
    public:

    string status;    
    int borrowed_user_roll;
        
        Book(string title, 
            string ISBN,
            string author,
            string published_year,
            string publisher,string status){
                this->title = title;
                this->author = author;
                this->ISBN  =  ISBN;
                this->publisher = publisher;
                this->published_year = published_year;

                this->status = status;
            }
        string show_ISBN(){
            return this->ISBN;
        }
        string print_title(){
            return this->title;
        }

        void change_status(string status){
            this->status = status;
        }

        void show_details(){
            cout << "   Title : "<< this->title <<endl;
            cout << "   Author : "<< this->author <<endl;
            cout << "   ISBN : "<< this->ISBN <<endl;
            cout << "   Publsiher : "<< this->publisher <<endl;
            cout << "   Published Year : "<< this->published_year <<endl;
            
        }


};



class Student : public User,private Account{
    
    public:
        Student(){
            this->user_type = "Student";
        }
        Student(int roll, string id, string password){
            this->user_roll = roll;
            this->account_id = id;
            this->account_password = password;
            
        }

        bool verify_account(string id, string password){
            if(account_id == id && account_password == password) return true;
            else {
                cout <<"U have entered wrong Account ID or password!";
                return false;
            }
        }
        
        int return_days(int index){
            return overdues[index];
        }
    

        int number_books_borrowed(){
            return this->borrowed_books.size();
        }

        void print_books(){   
            int size = this->borrowed_books.size(); 
            if(size==0)cout << "U haven't borrowed any book currently.";
            int total_fine =0;
            
            for(int i=0;i<size;i++){
                int fine = 0;
                if(overdues[i] > 15) fine = (overdues[i] - 15) *10; 
                cout << i+1<< ".   " << borrowed_books[i].first << "          Days Borrowed: "<< overdues[i] << "     OverdueFine: Rs. " << fine<<endl;
                total_fine+=fine;
            }
            cout << "\nTotal Overdue Fine :       Rs. " << total_fine <<endl;
        }
        void add_book(pair<string,string> book,int days){
            int size = this->borrowed_books.size();

            this->borrowed_books.push_back(book);
            this->overdues.push_back(days);
        }
        void remove_book(int index){
            borrowed_books.erase(borrowed_books.begin() + index);
            overdues.erase(overdues.begin()+ index);  
        }
        int check_book(string title) {
            int size = this->borrowed_books.size();
            int index = 0;
        
            while (index < size && this->borrowed_books[index].first != title) 
                index++;
        
            if (index == size) return -1;  // Book not found
            return index;  // Found at index
        }
        
        string give_ISBN(int index){
            return borrowed_books[index].second;
        }

    
};

class Faculty : public User, private Account{
    public:
        Faculty(){
            this->user_type = "Faculty";
        }

        Faculty(int roll, string id, string password){
            this->user_roll = roll;
            this->account_id = id;
            this->account_password = password;
            
        }

        int number_books_borrowed(){
            return this->borrowed_books.size();
        }
        int return_days(int index){
            return overdues[index];
        }
    
        bool verify_account(string id, string password){
            if(account_id == id && account_password == password) return true;
            else {
                cout <<"U have entered wrong Account ID or password!";
                return false;
            }
        }
        
        

        void print_books(){   
            int size = this->borrowed_books.size(); 
            if(size==0)cout << "U haven't borrowed any book currently.";
            
            
            for(int i=0;i<size;i++){
                cout << i+1<< ".   " << borrowed_books[i].first <<"          Days Borrowed: "<< overdues[i] <<endl;
                
            }
           
        }

        void add_book(pair<string,string> book,int days){
            int size = this->borrowed_books.size();
            
            this->borrowed_books.push_back(book);
            this->overdues.push_back(days);
        }
        void remove_book(int index){
            borrowed_books.erase(borrowed_books.begin() + index);
            overdues.erase(overdues.begin()+ index);   
        }

        int check_book(string title) {
            int size = this->borrowed_books.size();
            int index = 0;
        
            while (index < size && this->borrowed_books[index].first != title) 
                index++;
        
            if (index == size) return -1;  // Book not found
            return index;  // Found at index
        }
        
        string give_ISBN(int index){
            return borrowed_books[index].second;
        }
    
};

class Librarian : public User{
    public:
    Librarian(){
        this->user_type = "Librarian";
    }
    
};

class Library{
    vector<Book> library_books;
    vector<Student> library_students;
    vector<Faculty> library_faculties;
    vector<User> library_users;

    public:
        
    
    
    
    
    void input_data() {
        string line, roll, id, password,days;
    
        // --- Process students.csv ---
        ifstream file("students.csv");
        if (!file) {
            cout << "Error opening students.csv" << endl;
            return;
        }
        // Skip header
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            User U;
            U.user_type = "Student";
            getline(ss, roll, ',');
            getline(ss, id, ',');
            getline(ss, password, ',');
            
            if(id!="" && password!=""){
                    int roll_num = stoi(roll);
                    Student St(roll_num, id, password);
                    library_students.push_back(St);
            }
            
                    U.user_roll = stoi(roll);
               
            library_users.push_back(U);
        }
        file.close();
    
        // --- Process faculties.csv ---
        ifstream file8("faculties.csv");
        if (!file8) {
            cout << "Error opening faculties.csv" << endl;
            return;
        }
        getline(file8, line);
        while (getline(file8, line)) {
            stringstream ss(line);
            User U;
            U.user_type = "Faculty";
            getline(ss, roll, ',');
            getline(ss, id, ',');
            getline(ss, password, ',');
            
            
                    int roll_num = stoi(roll);
                    Faculty Fc(roll_num, id, password);
                    library_faculties.push_back(Fc);
                
            
                    U.user_roll = stoi(roll);
                
            library_users.push_back(U);
        }
        file8.close();
    
        // --- Process books.csv ---
        ifstream file1("books.csv");
        if (!file1) {
            cerr << "Error opening books.csv" << endl;
            return;
        }
        string title, ISBN, author, published_year, publisher, status;
        getline(file1, line);
        while (getline(file1, line)) {
            stringstream ss(line);
            getline(ss, title, ',');
            getline(ss, ISBN, ',');
            getline(ss, author, ',');
            getline(ss, published_year, ',');
            getline(ss, publisher, ',');
            getline(ss, status, ',');
            
            
            
                    
                
            Book B(title, ISBN, author, published_year, publisher, status);
            library_books.push_back(B);
        }
        file1.close();
    
        // --- Process distributed_books.csv (borrowed_books) ---
        ifstream file2("distributed_books.csv");
        if (!file2) {
            cerr << "Error opening distributed_books.csv" << endl;
            return;
        }
        getline(file2, line);
        while (getline(file2, line)) {
            int index_vector = 0;
            stringstream ss(line);
            getline(ss, roll, ',');
            
            if(roll == "Roll No" || roll =="")continue;
            int roll_num = 0;
            
            roll_num = stoi(roll);
                
            
            // Try to find a matching student
            bool found_student = false;
            for (size_t i = 0; i < library_students.size(); i++) {
                if (library_students[i].user_roll == roll_num) {
                    index_vector = i;
                    found_student = true;
                    break;
                }
            }
            if (found_student) {
                while (getline(ss, title, ',')) {
                    
                    getline(ss, ISBN, ',');
                    
                    getline(ss,days,',');
                    if(ISBN =="")continue;
                    if(days=="")days ="0";
                    library_students[index_vector].add_book({title, ISBN},stoi(days));
                }
            } else {
                // If not found among students, try faculties
                bool found_faculty = false;
                for (size_t i = 0; i < library_faculties.size(); i++) {
                    if (library_faculties[i].user_roll == roll_num) {
                        index_vector = i;
                        found_faculty = true;
                        break;
                    }
                }
                if (found_faculty) {
                    while (getline(ss, title, ',')) {
                        getline(ss, ISBN, ',');
                        getline(ss,days,',');
                        if(ISBN =="")continue;
                        if(days=="")days ="0";
                        library_faculties[index_vector].add_book({title, ISBN},stoi(days));
                    }
                } else {
                    cout << "Roll number " << roll_num << " not found among students or faculties." << endl;
                }
             }
        }
        file2.close();
    }



        
        
        bool search_roll(int roll){
            int index = 0;
            while(index < library_users.size() && roll != library_users[index].user_roll ) index++;
            if(index==library_users.size())return false;
            return true;
        }

         // check the criteria if he is registered or not
        bool find_user(int roll){
            if(search_roll(roll)){ 
                cout << "\n What do u recognize urself with ? \n     Student / Faculty / Librarian"<< endl << "      ---";
                return true;
            }
            else{
                cout<< "I am afraid u cant go further as u are not eligible to enter library.";
                return false;
                
            }
            
        }

        bool print_books(){
            int index = 0;
            int sub_index = 1;
            int size = library_books.size();
            if(size == 0) {
                cout<< "\nNo books are currently available !!\n"; 
                return false;
            } 
            while( index < size ){
                if(library_books[index].status == "Available"){
                    cout << sub_index<< ".   " << library_books[index].print_title() << endl;
                    sub_index++;
                }
                index++;
            }
            return true;
        }
        string check_book_ISBN(string title){
            int index = 0;
            while(index < library_books.size() && title != library_books[index].print_title() ) index++;
            if(index == library_books.size()) return "NIL";
            if(library_books[index].status == "BORROWED") return "B"+library_books[index].show_ISBN();
            return library_books[index].show_ISBN();
        }
        Book* find_book(string ISBN){
            int index = 0;
            while(index < library_books.size() && ISBN != library_books[index].show_ISBN() ) index++;

            return &library_books[index];
        }

        Student* find_student(int roll){
            int index = 0;
            while(index < library_students.size() && roll != library_students[index].user_roll ) index++;
            if(index == library_students.size()) return nullptr;
    
            return &library_students[index];
        }

        Faculty* find_faculty(int roll){
            int index = 0;
            while(index < library_faculties.size() && roll != library_faculties[index].user_roll ) index++;
            if(index == library_faculties.size()) return nullptr;
    
            return &library_faculties[index];

        }


        
        void output_data_register(int roll_no, string new_ID, string new_password) {
            ifstream file_in("students.csv");
            ostringstream updated_data;
            string line, roll;
            bool updated = false;
        
            getline(file_in, line);  
            updated_data << line << "\n";  // Keep header
        
            while (getline(file_in, line)) {
                stringstream ss(line);
                getline(ss, roll, ',');
                updated_data << ((isdigit(roll[0]) && stoi(roll) == roll_no && line.find(",,") != string::npos) 
                    ? roll + "," + new_ID + "," + new_password + "," : line) << "\n";
                updated |= (isdigit(roll[0]) && stoi(roll) == roll_no);
            }
            file_in.close();
        
            if (updated) {
                ofstream("students.csv") << updated_data.str();
                cout << "Account registered successfully." << endl;
            }
        }

       
        void borrow_book(int roll_no, const string& book_title, const string& isbn,int days) {
            ifstream file_in("distributed_books.csv");
            ostringstream updated_data;
            string line, roll;
            bool found = false, book_updated = false;
        
            getline(file_in, line);
            updated_data << line << "\n";  // Keep header
        
            while (getline(file_in, line)) {
                stringstream ss(line);
                getline(ss, roll, ',');
                
        
                if (!roll.empty() && isdigit(roll[0]) && stoi(roll) == roll_no) {
                    vector<string> items;
                    string item;
                    while (getline(ss, item, ',')) {
                        if (!item.empty()) items.push_back(item);
                    }
                    updated_data <<roll;
                    for (size_t i = 0; i < items.size(); i += 1) {                
                        updated_data  <<","<< items[i];
                    }
                    // Append new book and ISBN to this user's row
                    updated_data << ","<< book_title << "," << isbn << ","<<"0";
                    int comma_count = item.size() +4;
                    updated_data << string(16 - comma_count, ',') ;

                    found = true;
                } else {
                    updated_data << line;  // Keep other rows unchanged
                }
                updated_data << "\n";
            }
            file_in.close();
        
            // If roll number was not found, add a new row for this user
            if (!found) {
                updated_data << roll_no << "," << book_title << "," << isbn << ","<< "0"<<",";
                int comma_count = 4;
                updated_data << string(16 - comma_count, ',') ;
                updated_data << "\n";

            }
        
            // Rewrite the file with updated data
            ofstream file_out("distributed_books.csv", ios::trunc);
            file_out << updated_data.str();
            file_out.close();
        
            // Update book status in books.csv (this part is unchanged)
            ifstream book_file("books.csv");
            ostringstream book_data;
            string title, book_isbn, author, year, publisher, status;
        
            getline(book_file, line);
            book_data << line << "\n";  // Keep header
        
            while (getline(book_file, line)) {
                stringstream ss(line);
                getline(ss, title, ',');
                getline(ss, book_isbn, ',');
                getline(ss, author, ',');
                getline(ss, year, ',');
                getline(ss, publisher, ',');
                getline(ss, status, ',');
        
                if (title == book_title && book_isbn == isbn && status == "Available") {
                    book_data << title << "," << book_isbn << "," << author << "," 
                              << year << "," << publisher << ",Borrowed,\n";
                    book_updated = true;
                } else {
                    book_data << line << "\n";
                }
            }
            book_file.close();
        
            if (book_updated) {
                ofstream book_out("books.csv", ios::trunc);
                book_out << book_data.str();
                book_out.close();
                cout << "Book borrowed successfully." << endl;
            }
        }


        void return_book(int roll_no, const string& book_title, const string& isbn,const int& days) {
            // Update user_books.csv
            ifstream file_in("distributed_books.csv");
            ostringstream updated_data;
            string line, roll;
            bool found = false;
        
            getline(file_in, line);
            updated_data << line << "\n";  // Keep header
        
            while (getline(file_in, line)) {
                stringstream ss(line);
                getline(ss, roll, ',');
        
                if (stoi(roll) == roll_no) {
                    found = true;
                    vector<string> items;
                    string item;
                    while (getline(ss, item, ',')) {
                        if(!item.empty())items.push_back(item);
                    }
        
                    updated_data << roll;
                    for (size_t i = 0; i < items.size(); i += 3) {
                        if (items[i+1] == isbn ) {
                            continue;
                        } else {
                            updated_data << "," << items[i] << "," << items[i + 1] << "," << items[i + 2];
                        }
                    }
                    int comma_count = items.size()-3;
                    updated_data << string(16 - comma_count, ',') ;

                    updated_data << "\n";
                } else {
                    updated_data << line << "\n";
                }
            }
            file_in.close();
        
            if (!found) {
                cout << "Error: Roll number not found." << endl;
                return;
            }
        
            ofstream file_out("distributed_books.csv", ios::trunc);
            file_out << updated_data.str();
            file_out.close();
        
            // Update books.csv
            ifstream book_file("books.csv");
            ostringstream book_data;
            string title, book_isbn, author, year, publisher, status;
            bool book_updated = false;
        
            getline(book_file, line);
            book_data << line << "\n";  // Keep header
        
            while (getline(book_file, line)) {
                stringstream ss(line);
                getline(ss, title, ',');
                getline(ss, book_isbn, ',');
                getline(ss, author, ',');
                getline(ss, year, ',');
                getline(ss, publisher, ',');
                getline(ss, status, ',');
        
                if (title == book_title && book_isbn == isbn && status == "Borrowed") {
                    book_data << title << "," << book_isbn << "," << author << "," 
                              << year << "," << publisher << ",Available,\n";
                    book_updated = true;
                } else {
                    book_data << line << "\n";
                }
            }
            book_file.close();
        
            if (book_updated) {
                ofstream book_out("books.csv", ios::trunc);
                book_out << book_data.str();
                book_out.close();
                cout << "Book returned successfully." << endl;
            } else {
                cout << "Error: Book not found or already available." << endl;
            }
        }
        
        

};




