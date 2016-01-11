#ifndef INVITE
#define INVITE

#include <QString>
#include <QVector>
class invite{


public:
    //! Constructor.
    invite();//need to figure out constructor here dn input values
    invite(int uID, int bID, int p);

    //! Destructor.
    ~invite();

    //!functions to pull values from class
    int getAccept();
    int getUserID();
    int getbookID();
    int getPoints();

    //!fuctions to set values
    void setUserID(int& uID);
    void setBookID(int& bID);
    void setPoints(int& p);
    void acceptInvite();
    void declineInvite();

    //! functions dealing with list of functions
    int findInvite(QVector<invite> inviteList);


    //!overloaded operator
     void operator=(const invite& i);

private:

int accept;             //accept if 0 if not resonded to, 1 if accepted, 2 if declined
int userId;
int bookId;
int points;
};

#endif // INVITE

