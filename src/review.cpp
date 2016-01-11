#include "review.h"

review::review(){
    this->username = "";
    this->rev = "";
    this->rating = 0;
}

review::review(QString name, QString review, int rate){
    this->username = name;
    this->rev = review;
    this->rating = rate;
}

//! Destructor.
review::~review(){}

//! pull values functions
QString review::getUsername(){
    return this->username;
}
QString review::getReview(){
    return this->rev;
}
int review::getRating(){
    return this->rating;
}

//!alter values functions
void review::setUsername(QString& name){
    this->username = name;
}
void review::setReview(QString& review){
    this->rev = review;
}
void review::setRating(int& rate){
    this->rating = rate;
}

review review::operator=(const review& r){
    this->username = r.username;
    this->rev = r.rev;
    this->rating = r.rating;
    return *this;

}
