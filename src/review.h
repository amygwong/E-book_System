#ifndef REVIEW
#define REVIEW


#include <QString>
class review{


public:
    //! Constructor.
    review();
    review(QString name, QString review, int rate);

    //! Destructor.
    ~review();

    //! pull values functions
    QString getUsername();
    QString getReview();
    int getRating();

    //!alter values functions
    void setUsername(QString& name);
    void setReview(QString& review);
    void setRating(int& rate);

    //! overloaded operator
    review operator=(const review& r);




private:

QString username;
QString rev;
int rating; // 0-5
};
#endif // REVIEW

