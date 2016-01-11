#ifndef USER
#define USER

#include <QVector>
#include <QString>
#include <QStringList>
#include "invite.h"


class user{


public:
    //! Constructors.
    user();                                             //for visitors
    user(QString u,QString p);                          //for people who input username and password

    //! Destructor.
    ~user();

    //!get values from class
    int getUserId();
    int getType();
    QString getUsername();
    QString getPassword();
    int getPoints();
    int getWarnings();
    QVector<invite> getSentInvites();
    QVector<invite> getInvites();
    QVector<QVector<int> > getHistory();
    QVector<int> getBookHistory();
    QVector<QString> getMessages();
    QStringList getBadWords();
    int getBookHistoryID(int i);
    int historySize();


    //!alter values from class
    void setUserID(const int& id);
    void setType(const int& t);
    void setPassword(const QString& p);
    void addWarning();                          //GOING TO HAVE TO ADD BLACKLISTING HERE
    void addPoints(const int& p);
    void decreasePoints(const int& p);
    void addMessages(QString s);
    void deleteMessage(int index);
    void setMessages (QVector<QString> m);
    void addHistory(const int& bookID, const int& p);



    //!functions for login and registration
    int findUser(QVector<user>& userList);                  //find user index in userList
    int login(QVector<user>& userList);                     //set user values equal to those of user in userList
    int registerUser(QVector<user>& userList);              //registers user
    void updateList(QVector<user>& userList);                 //updates user in userList. Must be called if exiting altered user after changes



    //!functions for dealing with invites
    int sendInvite(QVector<user>& userList, QString& name, int& bookID, int& points);            //will send invite to user with the username
    void acceptInvite(QVector<user>& userList, invite inv);                                       //accepts invite
    void declineInvite(QVector<user>& userList, invite inv);                                      //declines invite
    QVector<invite> checkInvites();                                                            //returns a list of invites that have been responded to




    //!functions dealing with books
    int addBook(int& bookID, int& p);                   //adds book to books user is reading
    bool reading(int& bookID);                          //checks whether user is reading a certain book
    int bookPoints(int& bookID);
    bool deductReading(int& bookID, int& p, QVector<user>& userList);            //deducts points for reading book even if book is shared
    int addSharedBook(const int& bookID,const int& p,const int& userID, QVector<user>& userList);               //adds a book to both user and makes them share it
    void removeBook(int& bookID);

    //! functions dealing with the bad words
    void addBadWord(const QString& word);
    void removeBadWord(const int& index);



    //!overloaded operators
    void operator=( const user& u);




private:

    int pullUser(QVector<user>& userList, QString& name);                   //will find user in userList in



int userID;                         //represents user index in array
int type;                           //what type of user?
QString username;
QString password;
int points;
int warnings;
QVector<invite> send;
QVector<invite> got;
QVector<QVector<int> > history;                  //first value in list is the bookID, second number is points spent
QVector<QVector<int> > read;                     //size will be 3 if not being shared, size will be 4 if it is shared
                                                 //the first number is bookID,points left, points spent, userID
QVector<QString> messages;
QStringList badWords;

};


#endif // USER

