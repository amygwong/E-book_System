#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QTimer>
#include "user.h"
#include "book.h"
#include "readbook.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Creates a list of users, books
    void createUserList();
    void createBlackList();
    void createBookList();

    // Create and update tables in reviewIssues page
    void createIssuesTables();
    void initIssuesLists();
    void updateBookTable();
    void updateComplaintTable();
    void updateComplaints(int removed);

    // Create and update tables in account page
    void createAccountTables();
    void initAccountLists();
    void createWordList();

    // Create tables in catalog page
    void createCatalogTable();
    void createRecommendTable();

    // Functions for book summary page
    void invitePageShowed();

    // Create and empty table in searchPage
    void createSearchTable();


private slots:
    // signals/slots for all users
    void catalogPage();

    // signals/slots for visitors
    void signInPage();
    void signUpPage();
    void loginPage();
    void registerButtonClicked();

    // signals/slots for users
    void uploadPage();
    void reportPage();
    void accountPage();
    void signOut();
    void submitReportButtonClicked();
    void issuesPage();
    void submitIssuesButtonClicked();

    // signals/slots for tables widgets in reviewIssuesPage widget
    void cellSelected(int r, int c);
    void complaintCellSelected(int r);

    // signals/slots for tables widgets in accountPage widget
    void messageCellSelected(int r);
    void editWordList(int i);

    // signals/slots for bookSummaryPage widget
    void summaryPage(int r);
    void reviewBook();
    void makeReview();
    void reviewTable();
    void badWordSearch();

    // signals/slots for recommendWidget
    void findtBookID(QListWidgetItem *);
    void findrBookID(QListWidgetItem *);

    // signals/slots for inviteWidget
    void sendInviteClicked();
    void acceptInviteClicked();
    void rejectInviteClicked();

    // signals/slots for searchPage widget
    void searchPage();
    void searchClicked(int in);


    // signals/slots for reading a book
    void readButton();
    void spendPointsButton();


    // signals/slots for uploading a book
    void browse();
    void uploadFile();
    void browseImg();

private:
    Ui::MainWindow *ui;

    // Stacked Widget Indexes
    int menuCurrentIndex;
    int pageCurrentIndex;
    int recommendCurrentIndex;


    // Users
    QVector<user> userList;
    QVector<user> blackList;
    user currentUser;

    // Complaints
    QVector<int> bookComplaints;
    QVector<QString> desComplaints;

    // Books
    QVector<book> bookList;
    QVector<book> potentialList;
    int currentBookID;
    QVector<book> fiveBooks;

    // Current User Information
    QVector<QString> messageList;
    invite currentInvite;

};

#endif // MAINWINDOW_H
