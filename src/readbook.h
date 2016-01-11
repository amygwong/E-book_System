#ifndef READBOOK_H
#define READBOOK_H
#include "book.h"
#include "user.h"

#include <QDialog>

namespace Ui {
class readBook;
}

class readBook : public QDialog
{
    Q_OBJECT

public:
    explicit readBook(QWidget *parent = 0);
    readBook(book b);

    ~readBook();

private:
    Ui::readBook *ui;
};

#endif // READBOOK_H
