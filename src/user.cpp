#include "user.h"
#include <QDebug>

enum{VS,RU,SU};


//regular constructor
user::user(){
    this->username = "";
    this->password = "";
    this->type = VS;
    this->warnings = 0;
    this->userID = -1;
}

//constructor given username and password values
user::user(QString u, QString p){
    this->username = u;
    this->password = p;
    this->type = VS;
    this->warnings = 0;
    this->userID = -1;
}

//destructor
user::~user(){}



//return UserID
int user::getUserId(){
    return this->userID;
}

//returns username
QString user::getUsername(){
    return this->username;
}

//returns password
QString user::getPassword(){
    return this->password;
}

//return type of user
int user::getType(){
    return this->type;
}

//return type points
int user::getPoints(){
    return this->points;
}

//return type points
int user::getWarnings(){
    return this->warnings;
}

//return messages
QVector<QString> user::getMessages(){
    return this->messages;
}

//return invites that were recieved by user
QVector<invite> user::getInvites(){
    return this->got;
}

//return sent invites
QVector<invite> user::getSentInvites(){
    return this->send;
}

//return history of books with the points they spent reading it
QVector<QVector<int> > user::getHistory(){
    return this->history;
}

//return QVector filled with books that have been read by the user
QVector<int> user::getBookHistory(){
    QVector<int> bookIDs;
    for(int i=0;i<this->history.size();i++){
        bookIDs.append(this->history[i][0]);
    }
    return bookIDs;
}



int user::getBookHistoryID(int i)
{
    return (this->history[i][0]);
}

int user::historySize()
{
    return this->history.size();
}




//returns stringList containing all the bad words that the user deemed to be bad
QStringList user::getBadWords(){
    return this->badWords;
}



//alter password value
void user::setPassword(const QString& p){
    this->password=p;
}

//alter the type of user. Assumes t is a valid user type
void user::setType(const int &t){
    this->type=t;
}

//alters the ID of the user. Assumes that id is an index in the userList
void user::setUserID(const int &id){
    this->userID=id;
}

// warning count increases by 1
void user::addWarning(){
    this->warnings+=1;
}

// points count increases by p
void user::addPoints(const int& p){
    this->points+=p;
}

// points count decreases by p
void user::decreasePoints(const int& p){
    this->points-=p;
}

// add message s to the list of messages
void user::addMessages(QString s){
    this->messages.append(s);
}

// removes message at index to the list of messages
void user::deleteMessage(int index){
    this->messages.removeAt(index);
}

void user::setMessages (QVector<QString> m){
    this->messages = m;
}



//add a book to the history
//if the book already exists in history the points are simply added to that book
void user::addHistory(const int &bookID, const int &p){
    int histInd;
    for(histInd=0; histInd<this->history.size();histInd++){
        if(bookID==this->history[histInd][0])
            break;
    }
    //book was not in history
    if(histInd == history.size()){
        //create new instance to add to history
        QVector<int> book1;
        book1.append(bookID);
        book1.append(p);
        this->history.append(book1);
    }
    //book was in history now we just need to update the value
    else
        this->history[histInd][1] += p;

}

//inputs a QVector of users. if the username matches one in the list it will return the index. Otherwise the size
//of the userList is returned.
int user::findUser(QVector<user>& userList){
    int i;
    for(i=0; i<userList.size();i++){
        if(userList[i].username==this->username)
            break;
    }
    return i;
}

//checks to see if user's password matches with the one in the user list. If it does all the value of user is set to
//that of the one in userList and returns 0. If not return value will be 1.
//returns 2 if the username was not found int the userList
int user::login(QVector<user> &userList){
    int ind = this->findUser(userList);
    if(ind == userList.size())
        return 2;
    if(userList[ind].password==this->password){
        this->type = userList[ind].type;
        this->userID = userList[ind].userID;
        this->points = userList[ind].points;
        this->read = userList[ind].read;
        this->got = userList[ind].got;
        this->send = userList[ind].send;
        this->warnings = userList[ind].warnings;
        this->history = userList[ind].history;
        this->messages = userList[ind].messages;
        this->badWords= userList[ind].badWords;
        return 0;
    }
    return 1;
}

//looks to see if the user is already in the class. If not, then the user is added and their type is changed to RU
//returns 0 for a successful registration. returns 1 for unsuccessfull registration.
int user::registerUser(QVector<user>& userList){
    if(this->findUser(userList)==userList.size() || userList.size()==0){
        this->type=RU;
        this->points=500;
        this->userID=userList.size();
        userList.push_back(*this);
        return 0;
    }
    return 1;
}

//assumes userID for the user is the index for the user in userList
//assumes that the user previously exisits in the the userList
void user::updateList(QVector<user>& userList){
    userList[this->userID]= *this;
}


//sends invite to the user with the the username name
//the return value will be 1 if the username was not found in the userlist
//if it is successfull 0 is returned
int user::sendInvite(QVector<user>& userList, QString &name, int &bookID, int &points){
    //search for the invitee
    user invitee;
    if(invitee.pullUser(userList,name)==1)
        return 1;
    //add inite to this user
    invite sent(invitee.userID,bookID,points);
    this->send.append(sent);
    //add invite to invitee
    invite recieve(this->userID,bookID,points);
    invitee.got.append(recieve);
    //update users in the list
    this->updateList(userList);
    invitee.updateList(userList);
    return 0;
}



//accepts the invite for the user. Deletes it from the list and makes sure that
//the inviter's sent invite is updated to true
void user::acceptInvite(QVector<user> &userList, invite inv){
    //remove invite from the list of got invites
    user inviter=userList[inv.getUserID()];
    this->got.remove(inv.findInvite(this->got));

    //alter value of the inviter's invite
    invite invit(this->userID, inv.getbookID(), inv.getPoints());
    inviter.send.remove(invit.findInvite(inviter.send));
    inviter.updateList(userList);
    this->updateList(userList);
    this->addSharedBook(inv.getbookID(),inv.getPoints(),inv.getUserID(),userList);
}



//declines the invite for the user. Deletes it from the list and makes sure that
//the inviter's sent invite is updated to false
void user::declineInvite(QVector<user> &userList, invite inv){
    //remove invite from the list of got invites
    user inviter=userList[inv.getUserID()];
    this->got.remove(inv.findInvite(this->got));

    //alter value of the inviter's invite
    invite invit(this->userID, inv.getbookID(), inv.getPoints());
    inviter.send[invit.findInvite(inviter.send)].declineInvite();
    this->updateList(userList);
}

//returns an empty QVector if nothing has been updated
//if some of sent invites have been altered it is removed from send and is put into the returned list
QVector<invite> user::checkInvites(){
    QVector<invite> list;
    int size= send.size();
    for(int i = 0; i< size; i++){
        if(this->send[i].getAccept()!= 0)
            list.append(this->send[i]);
            send.remove(i);
            i--;
            size--;
    }
    return list;
}


//adds a book to the bookID to books that user is reading
//returns 0 if successful
//returns 1 if user doesn't have enought points
//assumes bookID is a valid id
int user::addBook(int &bookID, int &p){
    //check if user has enough points
    if(this->points < p)
        return 1;
    //deduct points and add book into books being read
    this->points-=p;
    QVector<int> book;
    book.append(bookID);
    book.append(p);
    book.append(p);
    this->read.append(book);
    this->addHistory(bookID,p);
    return 0;
}


//checks to see if user is reading a certain book
//returns true if the user is reading a book
//returns false if user is not reading
bool user::reading(int &bookID){
    bool val = false;
    //iterate through and see if bookID is any of the first values in read
    for(int i= 0;i<this->read.size();i++){
        if(bookID==this->read[i][0])
            val=true;
    }
    return val;
}

//assumes that user is already readingt the book and returns the amount of points
//left that the user has for reading the book
int user::bookPoints(int& bookID){
    for(int i=0; i<this->read.size();i++){
        if(bookID==this->read[i][0])
            return read[i][1];
    }
}

//assumes that user has this book in read and has enough points
//dedects the user points by p for reading the book
//returns true if user still has points
//returns false if user has run out of points to read the book
bool user::deductReading(int &bookID, int &p, QVector<user> &userList){
    //iterate through list
    for(int i= 0;i<this->read.size();i++){
        //found the book
        if(bookID==this->read[i][0]){
            this->read[i][1]-=p;

            //deduct points from other user if it is being shared
            if(this->read[i].size()==4){
                user share;
                share = userList[this->read[i][3]];
                //find book here
                for(int k=0; k<share.read.size();k++){
                    if(bookID==share.read[k][0]){
                        //alter amount of points
                        share.read[k][1]-=p;
                    }
                }
                //remove books if either is doner reading
                if(this->read[i][1] <= 0){
                    this->removeBook(bookID);
                    share.removeBook(bookID);
                    //update lists
                    this->updateList(userList);
                    share.updateList(userList);
                    return false;
                }
                share.updateList(userList);
            }
            //check if it is user is done reading  and removes if true
            if(this->read[i][1] <= 0){
                this->removeBook(bookID);
                //update list
                this->updateList(userList);
                return false;
            }
            //update list and break out of loop because we are done
            this->updateList(userList);
            break;
        }
    }
    return true;
}


//adds a shared book to both this user and the user with the userID
//returns 1 if either user does not have enough points for the book
//returns 0 if successfull
//p should be the sum of points for both users
int user::addSharedBook(const int& bookID, const int& p, const int& userID, QVector<user>& userList){
    QVector<int> book;
    //create user that is being shared
    user share = userList[userID];
    //check if both users have enough points and if so deduct the points
    if(this->points < p/2 || share.points<p/2)
        return 1;
    this->points-= p/2;
    share.points -= p/2;
    //add book to this user
    book.append(bookID);
    book.append(p);
    book.append(p);
    book.append(userID);
    this->read.append(book);
    //add the book to this user's history
    this->addHistory(bookID,p);
    //add book to other user
    book[3]= this->userID;
    share.read.append(book);
    //add book to user's history
    share.addHistory(bookID,p);
    //update the users
    this->updateList(userList);
    share.updateList(userList);
    return 0;
}

//function to add new word to bad word list
void user::addBadWord(const QString &word){
    this->badWords.append(word);
}

//function that removes the indexth string from the badWords list
void user::removeBadWord(const int &index){
    this->badWords.removeAt(index);
}



//overloaded user = operation
void user::operator=(const user& u){
    //set all variables equal to the one in our u
    this->userID = u.userID;
    this->type = u.type;
    this->username = u.username;
    this->password = u.password;
    this->points = u.points;
    this->warnings = u.warnings;
    this->send=u.send;
    this->got=u.got;
    this->read= u.read;
    this->history=u.history;
    this->messages = u.messages;
    this->badWords = u.badWords;
}

//assumes that the book is a book that is being read by the user
//removes the book for this user with the matching userID
//if user is rereading a book the the points are added to their history otherwise a new history value is added
void user::removeBook(int &bookID){
    //find index of book in read
    int ind;
    for(ind=0; ind<this->read.size();ind++){
        if(bookID== this->read[ind][0])
            break;
    }
    //remove the book from read
    this->read.remove(ind);
}



//create user without having password
//returns 1 if the user wasn't found
//returns 0 when successfull
int user::pullUser(QVector<user> &userList, QString &name){
    int ind;
    for(ind=0; ind<userList.size(); ind++){
        if(name==userList[ind].username)
            break;
    }
    if(ind == userList.size())
        return 1;
    //invitee found now create and add invites to both parties
    *this=userList[ind];
    return 0;

}



