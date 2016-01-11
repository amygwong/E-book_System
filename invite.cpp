#include "invite.h"


enum{unknown, t, f};


//! Constructors
invite::invite(){
    this->accept = unknown;
    this->userId = -1;
    this->bookId = -1;
    this->points = 0;
}


invite::invite(int uID, int bID, int p){
    this->accept = unknown;
    this->userId = uID;
    this->bookId = bID;
    this->points = p;
}

//! Destructor.
invite::~invite(){}

//!functions to pull values from class
int invite::getAccept(){
    return this->accept;
}

int invite::getUserID(){
    return this->userId;
}

int invite::getbookID(){
    return this->bookId;
}

int invite::getPoints(){
    return this->points;
}

//!fuctions to set values
void invite::setUserID(int& uID){
    this->userId = uID;
}

void invite::setBookID(int& bID){
    this->bookId = bID;
}

void invite::setPoints(int& p){
    this->points = p;
}

void invite::acceptInvite(){
    this->accept = t;
}

void invite::declineInvite(){
    this->accept = f;
}

//inputs a QVector of invites. if the username matches one in the list it will return the index. Otherwise the size
//of the userList is returned.
int invite::findInvite(QVector<invite> inviteList){
    int i;
    for(i=0; i<inviteList.size();i++){
        if(inviteList[i].userId==this->userId || inviteList[i].bookId==this->bookId || inviteList[i].points==this->points)
            break;
    }
    return i;
}


//!overloaded operator
void invite::operator=(const invite& i){
     this->accept = i.accept;
     this->userId = i.userId;
     this->bookId = i.bookId;
     this->points = i.points;

 }
