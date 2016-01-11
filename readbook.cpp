#include "readbook.h"
#include "ui_readbook.h"

readBook::readBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readBook)
{
    ui->setupUi(this);
}

// Opens the text of book b
readBook::readBook(book b) :
    QDialog(0),
    ui(new Ui::readBook)
{
    ui->setupUi(this);
    QString bookContent = b.getText().join("\n");
    ui->textBrowser->setText(bookContent);
}



readBook::~readBook()
{
    delete ui;
}
