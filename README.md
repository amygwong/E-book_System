# E-book_System
An application to read, share, upload, and review e-books.

Academic Project at The City College of New York

Course: Software Engineering

Term: Fall 2015

Team Members: Shawn Mathew and Anthony Tan

Three types of users:

Super-users (SU): all RU’s allowed operations, book approvals/updates and complaints processing, set up the points for different reading durations.

Registered users (RU): all VS’s allowed operations, contribute books, read and rate/review books/reviews, send complaints to SU on book contents.

Visitors (VS): browse available E-book catalog and the reviews/ratings, apply to be a new RU.

Required system features:

1.	Provide a catalog of available E-books, each E-book should have a cover-page and summary to be displayed in the catalog, and the number of points needed to read the book for a certain time, e.g., 10 pts for 10 min, 20 for 30 min and 30 for 1 hour (in your system the time units should be seconds instead of minutes to make it easy to test).

2.	For any RU to read a book, s/he should have points in the system >= the pts asked by the book for a certain amount of time. Once the RU start to read the book, a timer is set according to the time the RU purchased, the book can be closed by the RU before the purchased time, or the system will close it when the time comes. The duration of the reading time for one book by one RU is accumulative.

3.	The RU can review and rate a book only if s/he read it before, each review and rating is weighted by the amount of time the reviewer reads the book—the rating of an RU who reads the book with 2 hours should have a larger confidence that that by another RU who only read it 10 min.

4.	The RU can contribute a book to the system and asks for a certain number A of points to be deposited to his/her account (this is the only way an RU can get points), the SU decides the number B of points to be rewarded to the contributing user. If B < A, the RU will be notified for approval, if not, the contribution will be denied.

5.	Your system should have a function to search for bad words in the books. Any RU can have their own choice of bad words, the RU can complain the book based on his/her search. An RU can also complain a book after s/he read the book. A book receiving 3 complaints will be removed automatically, the point B for this book when the RU contributed this book will be deducted from his/her account with additional -100 points as penalty. If the complaint is very serious, e.g., copyright violations, the SU can choose to punish the contributing RU even with only 1 complaint. An RU whose books are removed twice or who contributed one copyrighted book will be ejected from the system and put in the blacklist who can never register again.

6.	Every time an RU log into the system, 5 books that are similar to the ones s/he read before will be recommended. If an RU never read any book, then the top five books that were most read in the system will be recommended.

7.	An RU can invite another RU to read a book, once accepted, they both can read the book for their purchased time, and they split the asking points.

8.	Each RU can check his/her reading history/stats; any one, including a VS, can browse the stats for each book.

9.	A book that no one read for a certain time will be removed and 5 points are deducted from the contributing RU.

10.	A new creative feature worth 10% of the total project credit based on each team’s own choice.

General:
Should have one user-friendly GUI holding all features together (don’t pop up many windows for different features)
The system need not be Internet based, a stand-alone app is fine. 


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
