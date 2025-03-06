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
        int overdue_days;

    public : 



};

class Book{
    private :
        string title; 
        string ISBN;
        string author;
        int published_year;
        string publisher;
        

        string status;

    public:

        Book(string title, 
            string ISBN,
            string author,
            int published_year,
            string publisher,string status){
                this->title = title;
                this->author = author;
                this->ISBN  =  ISBN;
                this->publisher = publisher;
                this->published_year = published_year;

                this->status = status;
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

        void verify_account(string id, string password){
            if(account_id == id && account_password == password) return;
            else throw "U have entered wrong Account ID or password!";
        }
        
        bool is_registered(){
            
        }

        int number_books_borrowed(){
            return this->borrowed_books.size();
        }

        void print_books(){   
            int size = this->borrowed_books.size(); 
            if(size==0)cout << "U haven't borrowed any book currently.";
            for(int i=0;i<size;i++){
                cout << i+1<< ".   " << borrowed_books[i].first << endl;
            }
        }
        void add_books(pair<string,string> book){
            int size = this->borrowed_books.size();
            if(size==max_limit_St) throw "U have to retursize first to gain one";
            this->borrowed_books.push_back(book);
        }
        void remove_books(){
            this->borrowed_books.pop_back();
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

        void verify_account(string id, string password){
            if(account_id == id && account_password == password) return;
            else throw "U have entered wrong Account ID or password!";
        }
        

        void print_books(){   
            int size = this->borrowed_books.size(); 
            for(int i=0;i<size;i++){
                cout << i+1<< ".   " << borrowed_books[i].first << endl;
            }
        }
        void add_books(pair<string,string> book){
            int size = this->borrowed_books.size();
            if(size==max_limit_Fc) throw "U have to return first to gain one";
            this->borrowed_books.push_back(book);
        }
        void remove_books(){
            this->borrowed_books.pop_back();
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
        void input_data(){
            //users
            ifstream file("users.csv");
            

            string line,roll,id,password;

            getline(file,line);
            while (getline(file, line)) {
                stringstream ss(line);

                User U;
                U.user_type = "Student";
                getline(ss,roll,',');
                getline(ss,id,',');
                getline(ss,password,',');
                
                if(id != ""){
                    Student St(stoi(roll),id,password);
                    library_students.push_back(St);
                }

                U.user_roll = stoi(roll);
                library_users.push_back(U);
            }

            file.close(); 

            //books
            ifstream file1("books.csv");

            string  title,ISBN,author,published_year,publisher,status;
            getline(file1,line);
            while (getline(file1, line)) {
                stringstream ss(line);

                
                getline(ss,title,',');
                getline(ss,ISBN,',');
                getline(ss,author,',');
                getline(ss,published_year,',');
                getline(ss,publisher,',');
                getline(ss,status,',');
                

                
                Book B(title,ISBN,author,stoi(published_year),publisher,status);
                library_books.push_back(B);
            }
            file1.close();

            // borrowed_books
            ifstream file2("users_books.csv");


            getline(file2,line);
            
            while(getline(file2,line)){
                int index_vector = 0;
                stringstream ss(line);

                getline(ss,roll,',');
                
                while(library_students[index_vector].user_roll != stoi(roll))index_vector++;

                while(getline(ss,title,',')){
                    
                    
                    getline(ss,ISBN,',');
                    library_students[index_vector].add_books({title,ISBN});
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
        void find_user(int roll){
            if(search_roll(roll)){ 
                cout << "\n What do u recognize urself with ? \n     Student / Faculty / Librarian"<< endl << "      ---";
            }
            else{
                throw "I am afraid u cant go further as u are not eligible to enter library.";
                
            }
            
        }

        Student find_student(int roll){
            int index = 0;
            while(index < library_students.size() && roll != library_students[index].user_roll ) index++;
    
            return library_students[index];
        }


        void output_data(){

        }

};















