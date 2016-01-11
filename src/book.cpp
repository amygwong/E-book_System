#include "book.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

enum {rating, views};


//regular constructor
book::book(){
    this->title = QString();
    this->author = QString();
    this->summary = QString();
    this->bookId = -1;
    this->uploader = -1;
    this->cost = 10;
    this->stat[0] = 0;
    this->stat[1] = 0;
    this->lastRead = QDate();
    this->text = QStringList();
    this->cover = QImage();
    this->worth = 0;
    this->weight=0;
    this->warning = 0;
    this->genre = QString();
}

//constructor given title, author, and summary
book::book(QString titl, QString auth, QString sum){
    this->title = titl;
    this->author = auth;
    this->summary = sum;
    this->bookId = -1;
    this->uploader = -1;
    this->cost = 10;
    this->stat[0] = 0;
    this->stat[1] = 0;
    this->lastRead = QDate();
    this->text = QStringList();
    this->cover = QImage();
    this->worth = 0;
    this->weight=0;
    this->warning = 0;
    this->genre = QString();
}

book::~book(){}

//all function below return values from the function
QString book::getTitle(){
    return this->title;
}

QString book::getAuthor(){
    return this->author;
}

QString book::getSummary(){
    return this->summary;
}

QString book::getGenre(){
    return this->genre;
}

int book::getBookID(){
    return this->bookId;
}

int book::getCost(){
    return this->cost;
}

int book::getWarning(){
    return this->warning;
}

int book::getRating(){
    return this->stat[rating];
}

int book::getViews(){
    return this->stat[views];
}


int book::getReviwers(){
    return this->reviews.size();
}

QDate book::getLastRead(){
    return this->lastRead;
}

QVector<review> book::getReviews(){
    return this->reviews;
}

QStringList book::getText(){
    return this->text;
}

QImage book::getCover(){
    return this->cover;
}

int book::getWorth(){
    return this->worth;
}

int book::getUploader(){
    return this->uploader;
}

//functions to alter/set values of book
void book::setTitle(QString& titl){
    this->title = titl;
}
void book::setAuthor(QString& auth){
    this->author = auth;
}
void book::setSummary(QString& sum){
    this->summary = sum;
}

void book::setGenre(QString& gen){
    this->genre = gen;
}

void book::setBookID(int& id){
    this->bookId = id;
}

void book::setCost(int& cos){
    this->cost = cos;
}
void book::setRating(int& rate){
    this->stat[rating]=rate;
}

void book::setView(int& view){
    this->stat[views] = view;
}

void book::addView(){
    this->stat[views] += 1;
}

void book::setLastRead(QDate& date){
    this->lastRead = date;
}

//adds a review to the list of reviews then updates the rating for the book
//will return 1 if the user has not read the book
//returns 0 if successfull
//adds according to the weight of time spent reading the book
//updates reviews and points spent rea
int book::addReview(review& r, user& u){
    if(!u.reading(this->bookId))
        return 1;
    QVector<int> id = u.getBookHistory();
    for(int i=0; i<id.size();i++){
        if(id[i] == this->bookId){
            this->stat[rating] = this->stat[rating]* this->weight + u.getHistory()[i][1]*r.getRating();
            this->weight += u.getHistory()[i][1];
            this->stat[rating]= this->stat[rating]/this->weight;
        }
    }
    this->reviews.append(r);
    return 0;
}

void book::setWorth(const int &w){
    this->worth = w;
}

void book::setUploader(const int& uID){
    this->uploader=uID;
}


//makes text equal to the text string
//assumes path is path to a text file
void book::addText(QString &path){
    //load file up
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    //make text stream
    QTextStream in(&file);
    //clear text up
    this->text.clear();
    //load the new text into text
    while(true){
        QString line = in.readLine();
        if (line.isNull())
            break;
        else
            this->text.append(line);
    }
    file.close();
}

//loads image from the file path
void book::loadImage(QString &path){
    this->cover.load(path);
}


//find the index of a book in the bookList using bookID as a reference
//if the book isn't in the list then the size of the list is returned
int book::findBook(QVector<book> &bookList){
    int i;
    for(i=0;i<bookList.size(); i++){
        if(bookList[i].bookId== this->bookId)
            break;
    }
    return i;
}

//find the index of a book in the bookList using book title and author as a reference
//if the book isn't in the list then the size of the list is returned
int book::findBookTitle(QVector<book> &bookList){
    int i;
    for(i=0;i<bookList.size(); i++){
        if(bookList[i].title== this->title)
            if(bookList[i].author==this->author)
                break;
    }
    return i;
}



//bookList should be sorted by bookID to ensure that no duplicate bookID is created
//addBook will add a book to a list with the id that is one larger than that of the
//last book in the list
void book::addBook(QVector<book> &bookList){
    int ind = bookList.size();
    if(ind == 0)
        this->bookId = ind;
    else
        this->bookId = (bookList[ind-1].bookId)+1;
    bookList.append(*this);
}

//finds the book with the same bookID as this book then removes it from the list
//returns 1 if the book is not in the list
//returns 0 if successfull
int book::removeBook(QVector<book> &bookList){
    int ind=this->findBook(bookList);
    if(ind==bookList.size())
        return 1;
    bookList.remove(ind);
    return 0;
}

//assumes that this book is already in the bookList and upadates the book
//to this book
void book::updateBook(QVector<book> &bookList){
    int ind = this->findBook(bookList);
    bookList[ind] = *this;
}

bool book::wordSearch(const QString &word){
    for(int i = 0; i < text.size(); i++)
    {
        if(this->text.at(i).contains(word,Qt::CaseInsensitive))
            return true;
    }
    return false;
}

void book::operator =(const book& b){
    this->title= b.title;
    this->author= b.author;
    this->summary = b.summary;
    this->bookId = b.bookId;
    this->cost = b.cost;
    this->uploader = b.uploader;
    this->stat[0] = b.stat[0];
    this->stat[1] = b.stat[1];
    this->lastRead = b.lastRead;
    this->text = b.text;
    this->cover= b.cover;
    this->reviews=b.reviews;
    this->weight = b.weight;
    this->worth = b.worth;
    this->warning = b.warning;
    this->genre = b.genre;
}

void book::addWarning()
{
    this->warning++;
}

