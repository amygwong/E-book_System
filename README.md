# E-book_System
An application to read, share, upload, and review e-books.

Team Members: Shawn Mathew and Anthony Tan

Testing Information:

Users (name/password):
SU: name/password
RU: name2/password2, name3/password3
Blacklisted: name4/password4, name5/password5, name6/password6

Books Uploaded by name2: A Christmas Carol, Faust, The Prisoner of Zenda,	A Study in Scarlet, Hamlet		
Books Uploaded by name3: Narrative of the Life of Frederick Douglass, Dracula, The Legend of the Sleepy Hollow, Crito, The Chimes, Tom Sawyer Abroad

Notes:
- The paths of the example books and cover images must be reset according to the location it is located in in the createBookList function in the MainWindow.cpp file. The example books and cover images can be found in the folders labeled books and img in the zip folder you downloaded for this. 

- The SU doesn't need to approve of new users being registered. A VS can register on his own by completing the register form as long as the VS doesn't type a username that already exists. If the username already exists and is on the blacklist, the VS doesn't have any access to the login and register pages and can only browse the books.

- When a RU tries to upload a book and it gets rejected by the SU for asking too many points, the RU gets a message of the rejection and can try again by uploading the book and its information again, but asking for less points this time.

- When the RU or SU is reading a book, the SU cannot see the timer but it is running in the background. The user can check how many points are left for reading a book by checking his history in the account page. 

- The creative feature of the project is the search function. It allows the user to search through the catalog by title, author, or genre. 

- When a book hasn't been read after 10 days, the book is removed from the system. This checking is done whenever a RU/SU signs out of his account. Two books were made to have dates that were last read more than 10 days ago. They are "The Prisoner of Zenda" and "The Legend of the Sleepy Hollow. They are removed automatically from the book catalog after the first RU/SU signed out. 

- After clicking on the read button, the window that opens the text takes a while to appear. You must wait for the window to appear. Spend at least 100 points so that the window will be open for 10 seconds at least for the books that have 10 points per sec. Instead of having a timer the user can check many points are left for the book by clicking on the account page and reading the history table.

- The recommendation table for a RU/SU will be filled with books similar to books the user has read before. If there are less than 5 books, then the rest of the books recommendations will be pulled from the top viewed books (genre will not matter here).
