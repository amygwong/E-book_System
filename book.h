#ifndef BOOK
#define BOOK

#include "review.h"
#include <QString>
#include <QStringList>
#include <QDate>
#include <QImage>
#include "user.h"

class book{



public:
    //! Constructor.
    book();
    book(QString, QString, QString);

    //! Destructor.
    ~book();

    //!function to pull values
    QString getTitle();
    QString getAuthor();
    QString getSummary();
    int getBookID();
    int getCost();
    int getRating();
    int getViews();
    int getReviwers();          //returns number of ppl that have reviewed the book
    QDate getLastRead();        //returns a QDate. User daysTo memeber function to find difference in days
    QVector<review> getReviews();
    QStringList getText();
    QImage getCover();
    int getWorth();
    int getUploader();
    int getWarning();
    QString getGenre();

    //!functions to call to set/alter values
    void setTitle(QString& titl);
    void setAuthor(QString& auth);
    void setSummary(QString& sum);
    void setBookID(int& id);
    void setCost(int& cos);
    void setRating(int& rate);
    void setLastRead(QDate& date);
    int addReview(review& r, user& u);                                  //willl also update the value of rating and reviewers
    void addText(QString& path);
    void loadImage(QString& path);
    void setWorth(const int& w);
    void setUploader(const int& uID);

    void addView();
    void setView(int& view);
    void addWarning();
    void setGenre(QString& gen);

    //!functions to deal with books and lists
    int findBook(QVector<book>& bookList);
    int findBookTitle(QVector<book>& bookList);
    void addBook(QVector<book>& bookList);
    int removeBook(QVector<book>& bookList);
    void updateBook(QVector<book>&  bookList);
    bool wordSearch(const QString& word);


    //! overloaded operators
    void operator=( const book& b);


private:



QString title;
QString author;
QString summary;
QString genre;
int bookId;
int uploader;              //userID who contributed
int cost;
int worth;                  //keeps track of how many points user recieved for the book
int weight;
int warning;
int stat[2];            //stat[0] = rating, stat[1] = views
QDate lastRead;
QStringList text;
QImage cover;
QVector<review> reviews;

};
//still need to add something for cover and text here

#endif // BOOK

