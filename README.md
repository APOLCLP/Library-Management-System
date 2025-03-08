# Library-Management-System
Library Management System (LMS) using Object-Oriented Programming (OOP) concepts in C++. This system  demonstrates key OOP principles such as abstraction, inheritance, polymorphism, and encapsulation to manage the operations of a library effectively.


The System will operate as Command-Line Interface ,i.e. You will have to input commands as per printed texts for using the specific facility you need to.

The datafile won't be updated until the session has completed. because, destruction takes place when the session is completed.

Student must have userROll of 5 digits and faculty of 3 digits.

Librarian , faculty and student are different entities noone is common in both.

Users(pre-stated i have something 50 users) are allowed to enter the library and read the books, but they cant use the facilities to borrow until they register for an account.
all faculties,librarian are registered from the start. some students aren't registered until now( those who have no id and password)
A librarian won't have an id and password rather just an access key.
A librarian can't remove a book until it's returned, and can't remove a User until the user has returned all his borrowed books.
If he adds a faculty he has to make an account 

error handling is only done when input in terminal is wrong
constrainsts: dont give roll out of the range of signed int 

U can check the datafiles for reference of the input

U have to complete the session for updating things in datafiles

, at last in df is necess

You have to pay the fine with the return of book.



U can borrow a returned book in the same session as a mistake or vice-versa.

I have worked in this code like no 2 books with same titles or same ISBNs are present, if u add any book,be sure to search it first.IF u add some book in data file ensure to write proper full name.

students can register for an account(if not registered before),it is assumed that all faculties and librarian have an account already.  

I have restraint a student to be roll having 5 digits and faculty to be having 3 digits.

password should not contains white spaces.
any book or publication should not have "," in between ,try to replace it with "-".
u can pay ur fines while returning the book , by entering the amount.

the fine will show if u have that particular book overdue.

Consider librarian to be 