#include "mainwindow.h"
#include "ui_mainwindow.h"


// Constant number representations for the different user types
enum{VS,RU,SU};

// Comparsion function for sorting view amount in book
bool greaterThan (book a, book b)
{
  if ( a.getViews() > b.getViews())
      return true;
  return false;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creates the userList, blackList, bookList for the users of the system
    createUserList();
    createBlackList();
    createBookList();

    // Initialization of the menuWidget, pageWidget, and recommendWdiget being shown in gui
    // and their current index. These are set to the visitor user version.
    menuCurrentIndex = 0;
    pageCurrentIndex = 0;
    recommendCurrentIndex = 0;
    catalogPage();

    //Setting signal/slot connections to navigate through different pages based on the buttons
    //that is being clicked on in the menu widget

    // visitor pages
    connect(ui->catalogButton2, SIGNAL(clicked()), this, SLOT(catalogPage()));
    connect(ui->signinButton, SIGNAL(clicked()), this, SLOT(signInPage()));
    connect(ui->signupButton, SIGNAL(clicked()), this, SLOT(signUpPage()));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(loginPage()));
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(registerButtonClicked()));
    connect(ui->searchButton2, SIGNAL(clicked()), this, SLOT(searchPage()));

    // user pages
    connect(ui->catalogButton, SIGNAL(clicked()), this, SLOT(catalogPage()));
    connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(uploadPage()));
    connect(ui->reportButton, SIGNAL(clicked()), this, SLOT(reportPage()));
    connect(ui->accountButton, SIGNAL(clicked()), this, SLOT(accountPage()));
    connect(ui->signoutButton, SIGNAL(clicked()), this, SLOT(signOut()));
    connect(ui->submitReportButton,SIGNAL(clicked()),this, SLOT(submitReportButtonClicked()));
    connect(ui->reviewIssuesButton,SIGNAL(clicked()),this, SLOT(issuesPage()));
    connect(ui->submitIssuesButton, SIGNAL(clicked()), this, SLOT(submitIssuesButtonClicked()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchPage()));


    //Buttons for the upload page
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browse()));
    connect(ui->uploadFileButton, SIGNAL(clicked()), this, SLOT(uploadFile()));
    connect(ui->browseImgButton, SIGNAL(clicked()), this, SLOT(browseImg()));

    // BookSummary Buttons
    connect(ui->readButton,SIGNAL(clicked()), this, SLOT(readButton()));
    connect(ui->spendPointsButton,SIGNAL(clicked()), this, SLOT(spendPointsButton()));

    // reviewIssuesPage
    connect( ui->bookTableWidget, SIGNAL( cellDoubleClicked (int, int) ),this, SLOT( cellSelected( int, int ) ) );
    connect( ui->complaintTableWidget, SIGNAL( cellDoubleClicked (int, int) ),this, SLOT( complaintCellSelected( int ) ) );

    // accountPage
    connect( ui->messageTableWidget, SIGNAL( cellDoubleClicked (int, int) ),this, SLOT( messageCellSelected( int ) ) );
    connect(ui->wordBox, SIGNAL(activated(int)), this, SLOT(editWordList(int)));

    // catalogPage
    connect(ui->catalogTableWidget, SIGNAL( cellDoubleClicked(int,int) ), this, SLOT ( summaryPage(int)));
    connect(ui->topListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT (findtBookID(QListWidgetItem*)));
    connect(ui->recommendListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT (findrBookID(QListWidgetItem*)));

    // bookSummaryPage
    connect(ui->inviteButton, SIGNAL(clicked()), this, SLOT(sendInviteClicked()));
    connect(ui->acceptButton, SIGNAL(clicked()), this, SLOT(acceptInviteClicked()));
    connect(ui->rejectButton, SIGNAL(clicked()), this, SLOT(rejectInviteClicked()));
    connect(ui->writeReviewButton, SIGNAL(clicked()), this, SLOT(reviewBook()));
    connect(ui->submitReviewButton, SIGNAL(clicked()), this, SLOT(makeReview()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reviewTable()));
    connect(ui->badSearchButton, SIGNAL(clicked()), this, SLOT(badWordSearch()));

    // searchPage
    connect(ui->searchBox, SIGNAL(activated(int)), this, SLOT(searchClicked(int)));

}

// Deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}




// Creates a list of users that can use the system.
void MainWindow::createUserList()
{
    int p = 500;
    user a("name","password");
    a.addPoints(p);
    a.registerUser(this->userList);
    this->userList[0].setType(2);
    user b("name2","password2");
    b.addPoints(p);
    b.registerUser(this->userList);
    user c("name3","password3");
    c.addPoints(p);
    c.registerUser(this->userList);
}

// Creates a list of users that are blacklisted from using the system.
void MainWindow::createBlackList()
{
    this->blackList;
    user a("name4","password4");
    this->blackList.append(a);
    user b("name5","password5");
    this->blackList.append(b);
    user c("name6","password6");
    this->blackList.append(c);
}

// Creates a list of books in the system.
void MainWindow::createBookList()
{
    int cost = 10;
    int y = 100;

    QString aSummary = "Story of a bitter old miser named Ebenezer Scrooge and his transformation into a gentler, kindlier man after visitations by the ghost of his former business partner Jacob Marley and the Ghosts of Christmas Past, Present and Yet to Come.";
    book a("A Christmas Carol","Charles Dickens",aSummary);
    a.setUploader(userList[1].getUserId());
    a.setWorth(y);
    a.setView(y);
    a.setCost(cost);
    QString s = "Fiction";
    a.setGenre(s);
    QString aPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/A Christmas Carol.txt";
    a.addText(aPath);
    QString aImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/AChristmasCarol.jpg";
    a.loadImage(aImg);
    a.addBook(this->bookList);

    QString bSummary = "Faust is bored and depressed with his life as a scholar. After an attempt to take his own life, he calls on the Devil for further knowledge and magic powers with which to indulge all the pleasure and knowledge of the world. In response, the Devil's representative, Mephistopheles, appears. He makes a bargain with Faust: Mephistopheles will serve Faust with his magic powers for a set number of years, but at the end of the term, the Devil will claim Faust's soul, and Faust will be eternally damned. The term usually stipulated in the early tales is 24 years; one year for each of the hours in a day. During the term of the bargain, Faust makes use of Mephistopheles in various ways. In many versions of the story, particularly Goethe's drama, Mephistopheles helps Faust seduce a beautiful and innocent girl, usually named Gretchen, whose life is ultimately destroyed. However, Gretchen's innocence saves her in the end, and she enters Heaven. In Goethe's rendition, Faust is saved by God's grace via his constant striving—in combination with Gretchen's pleadings with God in the form of the Eternal Feminine. However, in the early tales, Faust is irrevocably corrupted and believes his sins cannot be forgiven; when the term ends, the Devil carries him off to Hell.";
    book b("Faust","Johann Wolfgang von Goethe", bSummary);
    b.setUploader(userList[1].getUserId());
    int z = 200;
    b.setWorth(z);
    b.setView(z);
    b.setCost(cost);
    s = "Fiction";
    b.setGenre(s);
    QString bPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/Faust.txt";
    b.addText(bPath);
    QString bImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/Faust.png";
    b.loadImage(bImg);
    b.addBook(this->bookList);

    QString cSummmary = "A memoir and treatise on abolition written by famous orator and former slave Frederick Douglass. It is generally held to be the most famous of a number of narratives written by former slaves during the same period. In factual detail, the text describes the events of his life and is considered to be one of the most influential pieces of literature to fuel the abolitionist movement of the early 19th century in the United States.";
    book c("Narrative of the Life of Frederick Douglass","Frederick Douglass", cSummmary);
    c.setUploader(userList[2].getUserId());
    c.setWorth(z);
    z = z+50;
    c.setView(z);
    c.setCost(cost);
    s = "Fiction";
    c.setGenre(s);
    QString cPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/Narrative of the Life of Frederick Douglass.txt";
    c.addText(cPath);
    QString cImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/NarrativeofFredrickDouglass.jpg";
    c.loadImage(cImg);
    c.addBook(this->bookList);

    QString dSummary = " story of Dracula's attempt to move from Transylvania to England so he may find new blood and spread the undead curse, and the battle between Dracula and a small group of men and women led by Professor Abraham Van Helsing.";
    book d("Dracula","Bram Stoker", dSummary);
    d.setUploader(userList[2].getUserId());
    int x = 150;
    d.setCost(cost);
    d.setView(x);
    s = "Fiction";
    d.setGenre(s);
    QString dPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/Dracula.txt";
    d.addText(dPath);
    QString dImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/Dracula.jpg";
    d.loadImage(dImg);
    d.addBook(this->bookList);

    QString eSummary = "A story of Ichabod Crane and his hapless attempt to win the heart and hand of Katrina Van Tassel in the context of a comical ghost story.";
    book e("The Legend of the Sleepy Hollow","Washington Irving", eSummary);
    e.setUploader(userList[2].getUserId());
    e.setCost(cost);
    e.setView(x);
    s = "Fiction";
    e.setGenre(s);
    QString ePath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/The Legend of Sleepy Hollow.txt";
    e.addText(ePath);
    QString eImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/SleepyHollow.jpg";
    e.loadImage(eImg);
    QDate eDate(1994, 01, 11);
    e.setLastRead(eDate);
    e.addBook(this->bookList);


    QString fSummary = "The king of the fictional country of Ruritania is drugged on the eve of his coronation and thus unable to attend the ceremony. Political forces are such that in order for the king to retain his crown his coronation must go forward. An English gentleman on holiday, who fortuitously resembles the monarch, is persuaded to act as his political decoy in an attempt to save the situation.";
    book f("The Prisoner of Zenda","Anthony Hope", fSummary);
    f.setUploader(userList[1].getUserId());
    x = x - 100;
    f.setCost(cost);
    f.setView(x);
    s = "Historical";
    f.setGenre(s);
    QString fPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/The Prisoner of Zenda.txt";
    f.addText(fPath);
    QString fImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/PrisonerofZenda.jpg";
    f.loadImage(fImg);
    QDate fDate(2000, 01, 13);
    f.setLastRead(fDate);
    f.addBook(this->bookList);

    QString gSummary = "Sherlock Holmes and Doctor Watson solve the case known as 'A Study in Scarlet.";
    book g("A Study in Scarlet","Arthur Conan Doyle", gSummary);
    g.setUploader(userList[1].getUserId());
    g.setCost(cost);
    g.setView(x);
    s = "Fiction";
    g.setGenre(s);
    QString gPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/A-Study-In-Scarlet-By-Arthur-Conan-Doyle.txt";
    g.addText(gPath);
    QString gImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/AStudyInScarlet.jpg";
    g.loadImage(gImg);
    g.addBook(this->bookList);

    QString hSummary = "I wanted you to be out of pain. I have always thought you happy in the calmness of your temperament; but never did I see the like of the easy, cheerful way in which you bear this calamity. Soc. Why, Crito, when a man has reached my age he ought not to be repining at the prospect...";
    book h("Crito","Plato", hSummary);
    h.setUploader(userList[2].getUserId());
    h.setCost(cost);
    h.setView(x);
    s = "Historical";
    h.setGenre(s);
    QString hPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/Crito-by-Plato.txt";
    h.addText(hPath);
    QString hImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/Crito.jpg";
    h.loadImage(hImg);
    h.addBook(this->bookList);

    QString iSummary = "A classic book. Well Known Everywhere";
    book i("Hamlet","William Shakespeare", iSummary);
    i.setUploader(userList[1].getUserId());
    i.setCost(cost);
    i.setView(x);
    s = "Historical";
    i.setGenre(s);
    QString iPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/Hamlet.txt";
    i.addText(iPath);
    QString iImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/Hamlet.jpg";
    i.loadImage(iImg);
    i.addBook(this->bookList);


    book newBook("The Chimes", "Charles Dickens", "The Chimes Summary The Chimes Summary The Chimes Summary The Chimes Summary");
    newBook.setWorth(cost);
    iPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/The-Chimes.txt";
    iImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/TheChimes.jpg";
    newBook.addText(iPath);
    newBook.setGenre(s);
    newBook.setUploader(userList[2].getUserId());
    newBook.loadImage(iImg);
    newBook.addBook(this->potentialList);

    book newBook2("Tom Sawyer Abroad", "Mark Twain", "Tom Sawyer Summary Tom Sawyer SummaryTom Sawyer SummaryTom Sawyer SummaryTom Sawyer Summary");
    newBook2.setWorth(cost);
    iPath = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/books/Tom-Sawyer-Abroad.txt";
    iImg = "C:/Users/Amy/Desktop/322GroupProject/322GroupProject/img/TomSawyerAbroad.jpg";
    newBook2.addText(iPath);
    newBook2.setGenre(s);
    newBook2.setUploader(userList[1].getUserId());
    newBook2.loadImage(iImg);
    newBook2.addBook(this->potentialList);



    this->bookComplaints.append(0);
    this->bookComplaints.append(0);
    this->bookComplaints.append(0);
    this->bookComplaints.append(1);
    this->desComplaints.append("des01");
    this->desComplaints.append("des02");
    this->desComplaints.append("des03");
    this->desComplaints.append("des14");
}




//Functions to navigate through the pages once a button in the menu widget has been clicked


// Changes to the catalogPage widget in pageWidget (index 0).
void MainWindow::catalogPage()
{
    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding catalogPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(0);

    // Creates the catalogTableWidget
    createCatalogTable();
    // If the current user has read zero books, then the recommendWidget is set to the top 5 viewed books.
    // Otherwise, the recommendWidget shows 5 similar books to the current user read books.

    if (this->currentUser.getHistory().size() == 0)
    {

        ui->recommendWidget->setCurrentIndex(0);
        recommendCurrentIndex = 0;
    }
    else
    {
        ui->recommendWidget->setCurrentIndex(1);
        recommendCurrentIndex = 1;
    }
    createRecommendTable();
}

// Changes to the signinPage widget in pageWidget (index 1).
void MainWindow::signInPage()
{
    // Empties the sign_in widget of any prior user input and messages
    ui->usernameLineEdit->setText("");
    ui->passwordLineEdit->setText("");
    ui->message->setText("");

    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding signinPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(1);
}

// Changes to the signupPage widget in pageWidget (index 2).
void MainWindow::signUpPage()
{
    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding signupPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(2);
}

// Changes to the catalogPage widget in pageWidget (index 0).
// Changes to the menu2 widget in menuWidget (index 1).
void MainWindow::loginPage()
{

    // Gets the user input for the username and password.
    QString u = ui->usernameLineEdit->text();
    QString p = ui->passwordLineEdit->text();

    // Checks to see if the user input was not empty.
    if (u != "" && p != "")
    {
        // Create a temporary user variable to hold the user input.
        user temp(u,p);

        // Checks if the temporary user is really a user of the system.

        // If the username is found on the blackList, then the user is blocked from logging into the system
        // and brought to the catalog page with visitor user rights only.
        if(temp.findUser(this->blackList) != this->blackList.size())
        {
            // Set system to visitor user version.
            ui->menuWidget->setCurrentIndex(0);
            catalogPage();

            // Blocks the user from logging in or registering a new account by hiding the buttons
            // that goes to these pages.
            ui->signinButton->hide();
            ui->signupButton->hide();
        }

        // The temporary user is found in the userList.
        else if(temp.login(this->userList) == 0)
        {
            // Current User is set to this temporary user.
            this->currentUser = temp;

            // User can now use the registered system and will see his account page.
            ui->menuWidget->setCurrentIndex(1);
            menuCurrentIndex = ui->menuWidget->currentIndex();
            accountPage();

            // If user is a RU, then the reviewIssuesButton is hidden, else it's shown if user is a SU.
            if (currentUser.getType() == 1)
                ui->reviewIssuesButton->hide();
            else if (currentUser.getType() == 2)
                ui->reviewIssuesButton->show();
        }
        // The username is found in the userList, however the password does not match.
        else if (temp.login(this->userList) == 1)
        {
            // A message is shown on the page and the user can try to log into the system again.
            ui->message->setText("Wrong Username/Password");
        }
        // The input username doesn't exist in the userList.
        else if (temp.login(this->userList) == 2)
        {
            // A message for this is shown.
            ui->message->setText("User Does Not Exist");
        }
    }
}

// Changes to the uploadPage widget in pageWidget (index 3).
void MainWindow::uploadPage()
{
    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding uploadPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(3);
}

// Changes to the reportPage widget in pageWidget (index 4).
void MainWindow::reportPage()
{
    // Empties all prior user input on page.
    ui->reportTitleLineEdit->setText("");
    ui->descriptionTextEdit->setText("");
    ui->reportAuthorLineEdit->setText("");
    ui->reportMessageLabel->setText("");

    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding reportPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(4);
}

// Changes to the accountPage widget in pageWidget (index 5).
void MainWindow::accountPage()
{
    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding accountPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(5);

    // Displays the current user's stats
    ui->statUsername->setText(currentUser.getUsername());
    ui->statPassword->setText(currentUser.getPassword());
    ui->statPoints->setText(QString::number(currentUser.getPoints()));
    ui->statRead->setText(QString::number(currentUser.getHistory().size()));
    ui->statWarnings->setText(QString::number(currentUser.getWarnings()));
    ui->wordLineEdit->setText("");

    // Copys all the messages for the current user to messageList
    this->messageList = this->currentUser.getMessages();

    // IGNORE:: DEBUGGING
    QString a = "Hello";
    if (this->messageList.size() == 0)
        this->messageList.append(a);
    this->currentUser.setMessages(this->messageList);

    // Create and fills the tables in accountPage widget
    createAccountTables();
    initAccountLists();
    createWordList();
}



// Changes to the catalogPage widget in pageWidget (index 0).
// Changes to the menu1 widget in menuWidget (index 0).
void MainWindow::signOut()
{
    QDate timeNow = QDate::currentDate();
    int deduct = 5;
    QVector<int> ids;
    for(int n = 0; n < bookList.size(); n++)
    {
       if(bookList[n].getLastRead().daysTo(timeNow) > 10)
       {
           userList[bookList[n].getUploader()].decreasePoints(deduct);
           bookList[n].removeBook(bookList);
           n--;
       }
    }

    // When a user logs out, the bookList will be checked to see whether any books hasn't been read
    // for the past 10 days within the system. If there is such  a book, the book will be removed
    // 5 points deducted from the uploader/

    // Update the userList with the current user information
    this->currentUser.updateList(this->userList);

    // Finds the current index of pageWidget and menuWidget
    menuCurrentIndex = ui->menuWidget->currentIndex();
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding menu1 widget, then it is set that index.
    if(menuCurrentIndex != ui->menuWidget->count())
        ui->menuWidget->setCurrentIndex(0);

    // If the current index is not holding catalogPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(0);

    // Resets the list widget in catalog page to be the top 5 most viewed books.
    ui->recommendWidget->setCurrentIndex(0);
    recommendCurrentIndex = 0;
    createRecommendTable();

    // Resets the bookSummaryPage to vistor version for all the book visited.
    //for (int i = 0; i < visited.size();i++)
    ui->inviteWidget->setCurrentIndex(0);
    ui->badSearchButton->hide();
    ui->inviteWidget->hide();
    ui->writeReviewButton->hide();
    ui->readButton->hide();
    this->currentUser.setType(VS);

    catalogPage();
}

// Changes to the reviewIssuesPage widget in pageWidget (index 7).
void MainWindow::issuesPage()
{
    // Empties all prior user input on page.
    ui->complainedBookLineEdit->setText("");
    ui->deductLineEdit->setText("");
    ui->reviewIssueMessage->setText("");

    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding reviewIssuesPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(7);

    // Creates and formats tables in tabWidget for the potential book list at the "New Books" tab
    // and the complaintsTable
    createIssuesTables();
    initIssuesLists();
}

// Changes to the booksummarypage in pageWidget (index 6).
// All the information on the bookList at index r is given.
void MainWindow::summaryPage(int r)
{
    ui->badSearchButton->hide();
    ui->inviteWidget->hide();
    ui->writeReviewButton->hide();
    ui->readButton->hide();

    // Sets user input to default values
    ui->usernameInput->setText("Enter Username");
    ui->pointInput->setValue(0);
    ui->pointSpendBox->setMaximum(1000);
    ui->pointSpendBox->setSingleStep(10);
    // Sets the currentBookID to the book being looked at
    this->currentBookID = r;

    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding reviewIssuesPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(6);

    // Set current index of reviewWidget
    ui->reviewWidget->setCurrentIndex(0);
    reviewTable();

    // Shows the book information
    ui->summaryTitleLabel->setText(this->bookList[r].getTitle());
    ui->summaryAuthorLabel->setText(this->bookList[r].getAuthor());
    ui->summaryGenreLabel->setText(this->bookList[r].getGenre());
    ui->summaryTextBrowser->setText(this->bookList[r].getSummary());
    ui->summaryViewLabel->setText(QString::number(this->bookList[r].getViews()));
    ui->summaryRatingLabel->setText(QString::number(this->bookList[r].getRating()));
    ui->summaryCoverLabel->setPixmap(QPixmap::fromImage(this->bookList[r].getCover().scaled(181,171)));
    ui->summaryPointsLabel->setText(QString::number(this->bookList[r].getCost()));

    // If the user is a visitor, then the only function he is allowed to do is read the reviews
    // for the summaryPage for the book.
    if (ui->menuWidget->currentIndex() == 0)
    {
        ui->badSearchButton->hide();
        ui->inviteWidget->hide();
        ui->writeReviewButton->hide();
        ui->readButton->hide();
        reviewTable();
    }
    else
    {
        ui->badSearchButton->show();
        ui->inviteWidget->show();
        invitePageShowed();

        ui->readButton->show();
        if(this->currentUser.reading(this->currentBookID))
            ui->readChoiceWidget->setCurrentIndex(0);
        else
            ui->readChoiceWidget->setCurrentIndex(1);

        reviewTable();

        // Only gives the user an option to write a review if the user has read the book before.
        QVector<int> books = this->currentUser.getBookHistory();
        for (int i = 0; i < books.size(); i++)
        {
            if (this->currentBookID == books[i])
                ui->writeReviewButton->show();
        }
    }
}

// Changes to the searchPage in pageWidget (index 8).
void MainWindow::searchPage()
{
    ui->searchLineEdit->setText("Enter Search Item");
    // Finds the current index of pageWidget
    pageCurrentIndex = ui->pageWidget->currentIndex();

    // If the current index is not holding searchPage widget, then it is set that index.
    if(pageCurrentIndex != ui->pageWidget->count())
        ui->pageWidget->setCurrentIndex(8);

    createSearchTable();
}




// Functionalities of the System



// Actions taken when the user tries to register into the system with the user input of username, password, and re-password.
void MainWindow::registerButtonClicked()
{
    // Gets the user input for the username and password.
    QString u = ui->usernameLineEdit_2->text();
    QString p = ui->passwordLineEdit_2->text();
    QString rp = ui->repasswordLineEdit->text();

    // Checks to see if the user input was not empty.
    if (u != "" && p != "" && rp != "")
    {
        // Create a temporary user variable to hold the user input.
        user temp(u,p);

        // Checks if the temporary user is really a user of the system.

        // If the username is found on the blackList, then the user is blocked from logging into the system
        // and brought to the catalog page with visitor user rights only.
        if(temp.findUser(this->blackList) != blackList.size())
        {
            // Set system to visitor user version.
            ui->menuWidget->setCurrentIndex(0);
            ui->pageWidget->setCurrentIndex(0);

            // Blocks the user from logging in or registering a new account by hiding the buttons
            // that goes to these pages.
            ui->signinButton->hide();
            ui->signupButton->hide();
        }
        // If the password doesn't match with the re-password.
        else if (p != rp)
        {
            // A message is shown on the page and the user can try to register into the system again.
            ui->messageLabel->setText("Passwords Do Not Match. Try Again.");
        }
        else
        {
            // The temporary user is found in the userList.
            // Uses the function to find if the temporary user is registered in the system.
            int result = temp.registerUser(this->userList);

            // The input username already exists and message appears saying this.
            if(result == 1)
                ui->messageLabel->setText("User Already Exist. Try Again.");
            // The input username doesn't exist in the userList.
            else if (result == 0)
            {
                // The temporary user was successfully added to the system.
                // Empties the sign_up widget of any user input and messages
                ui->usernameLineEdit_2->setText("");
                ui->passwordLineEdit_2->setText("");
                ui->repasswordLineEdit->setText("");
                ui->messageLabel->setText("");

                // The temporary user is set as the current user.
                this->currentUser = temp;

                // User can now use the registered system and will see his account page.
                ui->menuWidget->setCurrentIndex(1);
                menuCurrentIndex = ui->menuWidget->currentIndex();
                accountPage();

                // User will see the top five most view books.
                recommendCurrentIndex = 0;
                ui->recommendWidget->setCurrentIndex(0);

                // If user is a RU, then the reviewIssuesButton is hidden, else it's shown if user is a SU.
                if (currentUser.getType() == 1)
                    ui->reviewIssuesButton->hide();
            }
        }
    }
}



// Actions to taken when the user tries to file a complaint/report on a book.
// The book title and author and a description of the complaint must be given.
void MainWindow::submitReportButtonClicked()
{
    // Grabs the user input for the book title and author and complaint description.
    QString bookTitle = ui->reportTitleLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();
    QString author = ui->reportAuthorLineEdit->text();

    // Create a temporary book with the user input for book title and author.
    book temp(bookTitle,author,"");

    // The user input for the book title, author, and the description cannot be empty.
    if(bookTitle != "" && author != "" && description != "")
    {
        // The complaint is filed only if the book title and author matches for a book in bookList.
        int bookIn = temp.findBookTitle(this->bookList);
        if (bookIn != bookList.size())
        {
            this->bookComplaints.append(bookIn);
            this->desComplaints.append(description);
            ui->reportMessageLabel->setText("Message Sent");
        }
        // Displays a message for the wrong book information
        else
            ui->reportMessageLabel->setText("Wrong Book Information. Try Again.");
    }
    else
    {
        // displays a message for missing information
        ui->reportMessageLabel->setText("Missing Information. Try Again.");
    }

    // Empties the report_page widget of any user input and messages
    ui->reportTitleLineEdit->setText("");
    ui->reportAuthorLineEdit->setText("");
    ui->descriptionTextEdit->setText("");
}


// Actions taken where the SU maintainence of books and complaints takes place when the submit button on the page is pushed.
// Occurs in the reviewIssuespage widget at the "Complaints" tab of the tabWidget.
// The complainedBookLineEdit when converts to an integer must be a bookID for an existing book in the system.
void MainWindow::submitIssuesButtonClicked()
{
    // The user input of bookID cannot be empty.
    if(ui->complainedBookLineEdit->text() != "")
    {
        // Finds the index of where the book is in bookList by using the user input of bookID
        int bookID = ui->complainedBookLineEdit->text().toInt();
        book temp("","","");
        temp.setBookID(bookID);
        int bookIn = temp.findBook(this->bookList);

        // If the book doesn't exist, must give a error message
        if (bookIn == this->bookList.size())
            ui->reviewIssueMessage->setText("Cannot Find Book");

        else
        {
            // Find the index/userID of uploader in userList
            int userIn = this->bookList[bookIn].getUploader();

            // Displays an error message that the book with the user input bookID doesn't exist
            if(bookIn == this->bookList.size())
                ui->reviewIssueMessage->setText("Book Not Found");
            else
            {
                // The user is deducting points from the book uploader.
                if (ui->deductLineEdit->text() != "")
                {
                    // Amount of Points being deducted
                    int dpoints = ui->deductLineEdit->text().toInt();

                    // Amount of Points Uploader has
                    int curPoints = this->userList[userIn].getPoints();

                    // Deduct Points from uploader
                    // If uploader has less points than the deduction, then uploader will have 0 points.
                    // Else the user will have the user input of point deducted from his account.
                    if (curPoints <= dpoints)
                        this->userList[userIn].decreasePoints(curPoints);
                    else
                        this->userList[userIn].decreasePoints(dpoints);
                    ui->reviewIssueMessage->setText("Points Deducted");
                }

                // If the removeButton is checked, then the book is removed from the system and a comfirmation
                // message is displayed. If the book is not found, then an error message is displayed.
                if (ui->removeBookButton->isChecked())
                {
                    temp.removeBook(this->bookList);
                    ui->reviewIssueMessage->setText("Removed Book");

                    // All the complaints on this removed book deleted and complaintTableWidget is re-populated
                    updateComplaints(bookID);
                    updateComplaintTable();

                    // Add a warning to the uploader to keep track of how many books he uploaded were removed.
                    this->userList[userIn].addWarning();

                    // If the uploader has two or more warnings, the uploader is placed in the blackList.
                    if (this->userList[userIn].getWarnings() == 2)
                    {
                        this->blackList.append(this->userList[userIn]);
                        ui->reviewIssueMessage->setText("Removed Book/Blacklisted Uploader");
                    }
                }

                // If the copyrightButton is checked, then the book is removed, display success, complaints on this book removed,
                // and the uploader is blacklisted as well.
                else if (ui->copyrightButton->isChecked())
                {
                    temp.removeBook(this->bookList);
                    ui->reviewIssueMessage->setText("Removed Book");
                    updateComplaints(bookID);
                    this->blackList.append(this->userList[userIn]);

                    // All the complaints on this removed book deleted and complaintTableWidget is re-populated
                    updateComplaints(bookID);
                    updateComplaintTable();
                }

                // If the blacklistButton is checked, then the uploader of the book is blacklisted.
                else if (ui->blacklistButton->isChecked())
                {
                    this->blackList.append(this->userList[userIn]);
                    ui->reviewIssueMessage->setText("Blacklisted Uploader");
                }

                // If the complaintButton is checked, then the complaint is recorded.
                // If there are 3 or more complaints against the book, then the book is removed.
                // The points the uploader gained from this book are removed along with an additional 100 points.
                else if (ui->complaintButton->isChecked())
                {
                    this->bookList[bookIn].addWarning();
                    if (this->bookList[bookIn].getWarning() >= 3)
                    {
                        // Calcuating amount of amounts being removed
                        int removing = this->bookList[bookIn].getWorth() + 100;
                        int curpoints = this->userList[userIn].getPoints();
                        if(curpoints <= removing)
                            this->userList[userIn].decreasePoints(curpoints);
                        else
                            this->userList[userIn].decreasePoints(removing);

                        temp.removeBook(this->bookList);


                        ui->reviewIssueMessage->setText("Removed Book/Points");
                        // All the complaints on this removed book deleted and complaintTableWidget is re-populated
                        updateComplaints(bookID);
                        updateComplaintTable();
                    }
                }
            }
        }
    }
}

// Creates and formats the table widgets in the reviewIssues page.
void MainWindow::createIssuesTables()
{
    // For bookTableWidget
    // Sets the amount of columns to fit width of the widget
    ui->bookTableWidget->setColumnCount(7);
    ui->bookTableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // Sets the header of bookTableWidget
    QHeaderView *header = new QHeaderView(Qt::Horizontal,ui->bookTableWidget);
    ui->bookTableWidget->setHorizontalHeader(header);
    ui->bookTableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" <<
                                                   "User" << "Points Asked" << "Give Points" << "" << "");

    // Formatting of bookTableWidget
    ui->bookTableWidget->setAlternatingRowColors(1);
    ui->bookTableWidget->setShowGrid(1);

    // For complaintTableWidget
    // Sets the amount of columns to fit width of the widget
    ui->complaintTableWidget->setColumnCount(5);
    ui->complaintTableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // Sets the header of complaintTableWidget
    QHeaderView *cheader = new QHeaderView(Qt::Horizontal,ui->complaintTableWidget);
    ui->complaintTableWidget->setHorizontalHeader(cheader);
    ui->complaintTableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" <<
                                                   "BookID" << "Description" << "Delete");
    ui->complaintTableWidget->horizontalHeader()->show();

    // Formatting of complaintTableWidget
    ui->complaintTableWidget->setAlternatingRowColors(1);
    ui->complaintTableWidget->setShowGrid(1);
    ui->complaintTableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);
}

// Initializes the bookTableWidget by filling the table with the potentialList for books.
// Initializes the complaintTableWidget by filling the table with the complaints for books.
// If the table is empty, then there are no potential books or complaints in the system.
void MainWindow::initIssuesLists()
{
    // Make sure that tables are empty
    ui->bookTableWidget->setRowCount(0);
    ui->complaintTableWidget->setRowCount(0);

    // Creates the QTableWidgetItem that will be inserted into a row in the bookTableWidget
    QTableWidgetItem *item[7];
    for(int i = 0; i < this->potentialList.size(); i++)
    {
        ui->bookTableWidget->insertRow(i);
        for(int j = 0; j < 7; j++)
        {
            item[j] = new QTableWidgetItem;
            switch(j)
            {
                // The item added to bookTableWidget[i,0] is the title of the book at potentialList[i]
                // This item can only be read by the user.
                case 0:
                    item[j]->setText(this->potentialList[i].getTitle());
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,1] is the author of the book at potentialList[i]
                // This item can only be read by the user.
                case 1:
                    item[j]->setText(this->potentialList[i].getAuthor());
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,2] is the upload userid of the book at potentialList[i]
                // This item can only be read by the user.
                case 2:
                    item[j]->setText(this->userList[this->potentialList[i].getUploader()].getUsername());
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,3] is the number of points asked by the upload user of the book at
                // potentialList[i]. This item can only be read by the user.
                case 3:
                    item[j]->setText(QString::number(this->potentialList[i].getCost()));
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,4] is editable.
                // Allows the user to enter the number of points givven to the upload user.
                case 4:
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,5] is the word "Submit".
                // The user clicks here after entering the number of points that will be given to the uploader.
                case 5:
                    item[j]->setText("Submit");
                    item[j]->setFlags(item[j]->flags() & ~Qt::ItemIsEditable);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,5] is the word "Copyrighted".
                // This item can be double-clicked by the user.
                case 6:
                    item[j]->setText("Copyrighted");
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;
            }
        }
    }

    // Creates the QTableWidgetItem that will be inserted into a row in the complaintTableWidget
    QTableWidgetItem *citem[5];
    for(int i = 0; i < this->bookComplaints.size(); i++)
    {
        ui->complaintTableWidget->insertRow(i);

        // Finds the index of the complained book in the bookList
        book temp("","","");
        temp.setBookID(this->bookComplaints[i]);
        int bookIn = temp.findBook(this->bookList);
        for(int j = 0; j < 5; j++)
        {
            citem[j] = new QTableWidgetItem;
            switch(j)
            {
                // The item added to complaintTableWidget[i,0] is the title of the book that is complained
                // at bookComplaint[j]. This item can only be read by the user.
                case 0:
                    citem[j]->setText(this->bookList[bookIn].getTitle());
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;

                    // The item added to complaintTableWidget[i,1] is the author of the book that is complained
                    // at bookComplaint[j]. This item can only be read by the user.
                case 1:
                    citem[j]->setText(this->bookList[bookIn].getAuthor());
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;

                // The item added to complaintTableWidget[i,2] is the bookID of the book that is complained
                // at bookComplaint[i]. This item can only be read by the user.
                case 2:
                    citem[j]->setText(QString::number(this->bookComplaints[i]));
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;

                // The item added to bookTableWidget[i,3] is the description of the complaint.
                // This item can be double-clicked by the user.
                case 3:
                    citem[j]->setText(this->desComplaints[i]);
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;

                // The item added to bookTableWidget[i,4] is the word "Delete".
                // This item can be double-clicked by the user.
                case 4:
                    citem[j]->setText("Delete");
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;
            }
        }
    }
}

// The user decides if the potential book on the row r is accepted to the system, rejected, or copyrighted.
void MainWindow::cellSelected(int r, int c)
{
    // User submitted the points that will be given to the upload user.
    if (c == 5)
    {
        // If the points given are greater than or equal to the asking points, then the user will have the
        // given points added to his account and a message of approval is sent to the upload user. The book
        // is added to the bookList of the system.
        QTableWidgetItem * gpoint = ui->bookTableWidget->item(r,4);
        int gpoints = gpoint->text().toInt();
        if (gpoints >= ui->bookTableWidget->item(r,3)->text().toInt())
        {
            this->potentialList[r].setWorth(gpoints);
            this->potentialList[r].addBook(this->bookList);
            this->userList[this->potentialList[r].getUploader()].addPoints(gpoints);

            // must give a message to user
            userList[this->potentialList[r].getUploader()].addMessages("Approved Contribution.");
        }
        else
        {
            // must a message to user
            // Send message to tell user of the rejection due to the asking points being too high.
            userList[this->potentialList[r].getUploader()].addMessages("Upload Rejected. Asking Points too high.");
        }

        // Remove the book from potentialList which should be at the index r.
        this->potentialList[r].removeBook(this->potentialList);

        // The bookTableWidget is updated to show the new potentialList update.
        updateBookTable();
    }

    // "Copyrighted" is clicked for the book at potentialList[r].
    else if (c == 6)
    {
        // Find the upload user and add the user to the blackList.
        this->blackList.append(userList[this->potentialList[r].getUploader()]);

        // Remove the book from potentialList which should be at the index r.
        this->potentialList[r].removeBook(this->potentialList);

        // The bookTableWidget is updated to show the new potentialList update.
        updateBookTable();
    }
}

// Re-populate the bookTableWidget in the "New Books" tab for the tabWidget in the reviewIssues widget to show the changed list
// for potentialList i.e. book was removed from the list
void MainWindow::updateBookTable()
{
    // Clear the table
    ui->bookTableWidget->setRowCount(0);

    // Creates the QTableWidgetItem that will be inserted int a row in the table
    QTableWidgetItem *item[7];
    for(int i = 0; i < this->potentialList.size(); i++)
    {
        ui->bookTableWidget->insertRow(i);
        for(int j = 0; j < 7; j++)
        {
            item[j] = new QTableWidgetItem;
            switch(j)
            {
                // The item added to bookTableWidget[i,0] is the title of the book at potentialList[i]
                // This item can only be read by the user.
                case 0:
                    item[j]->setText(this->potentialList[i].getTitle());
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,1] is the author of the book at potentialList[i]
                // This item can only be read by the user.
                case 1:
                    item[j]->setText(this->potentialList[i].getAuthor());
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,2] is the upload userid of the book at potentialList[i]
                // This item can only be read by the user.
                case 2:
                    item[j]->setText(this->userList[this->potentialList[i].getUploader()].getUsername());
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,3] is the number of points asked by the upload user of the book at
                // potentialList[i]. This item can only be read by the user.
                case 3:
                    item[j]->setText(QString::number(this->potentialList[i].getCost()));
                    item[j]->setFlags(Qt::NoItemFlags);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,4] is editable.
                // Allows the user to enter the number of points givven to the upload user.
                case 4:
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,5] is the word "Submit".
                // The user clicks here after entering the number of points that will be given to the uploader.
                case 5:
                    item[j]->setText("Submit");
                    item[j]->setFlags(item[j]->flags() & ~Qt::ItemIsEditable);
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;

                // The item added to bookTableWidget[i,5] is the word "Copyrighted".
                // This item can be double-clicked by the user.
                case 6:
                    item[j]->setText("Copyrighted");
                    item[j]->setTextAlignment(Qt::AlignCenter);
                    ui->bookTableWidget->setItem(i,j,item[j]);
                    break;
            }
        }
    }
}

// Action taken when a "Delete" cell is selected in the complaintTableWidget.
// The complaint corresponding in the row of the cell clicked is deleted.
// The complaint table is re-populated to show this change with call to updateComplaintTable().
void MainWindow::complaintCellSelected(int r)
{
    // Remove the complaint at index r for the complaint vectors
    this->bookComplaints.remove(r);
    this->desComplaints.remove(r);

    updateComplaintTable();
}

// The complaintTableWidget is repopulated with the current complaints
void MainWindow::updateComplaintTable()
{
    //Clear the table
    ui->complaintTableWidget->setRowCount(0);

    // Creates the QTableWidgetItem that will be inserted into a row in the complaintTableWidget
    QTableWidgetItem *citem[5];
    for(int i = 0; i < this->bookComplaints.size(); i++)
    {
        ui->complaintTableWidget->insertRow(i);
        // finds the index of the complained book in the bookList
        book temp("","","");
        temp.setBookID(this->bookComplaints[i]);
        int bookIn = temp.findBook(this->bookList);

        for(int j = 0; j < 5; j++)
        {
            citem[j] = new QTableWidgetItem;
            switch(j)
            {
                // The item added to complaintTableWidget[i,0] is the title of the book that is complained
                // at bookComplaint[j]. This item can only be read by the user.
                case 0:
                    citem[j]->setText(this->bookList[bookIn].getTitle());
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;

                    // The item added to complaintTableWidget[i,1] is the author of the book that is complained
                    // at bookComplaint[j]. This item can only be read by the user.
                case 1:
                    citem[j]->setText(this->bookList[bookIn].getAuthor());
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;


                // The item added to complaintTableWidget[i,2] is the bookID of the book that is complained
                // at bookComplaint[i]. This item can only be read by the user.
                case 2:
                    citem[j]->setText(QString::number(this->bookComplaints[i]));
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;

                // The item added to bookTableWidget[i,3] is the description of the complaint.
                // This item can be double-clicked by the user.
                case 3:
                    citem[j]->setText(this->desComplaints[i]);
                    citem[j]->setFlags(Qt::NoItemFlags);
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;

                // The item added to bookTableWidget[i,4] is the word "Delete".
                // This item can be double-clicked by the user.
                case 4:
                    citem[j]->setText("Delete");
                    citem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->complaintTableWidget->setItem(i,j,citem[j]);
                    break;
            }
        }
    }
}

// If a book is removed from the system, the corresponding complaints are removed as well.
void MainWindow::updateComplaints(int removed)
{
    for(int i = 0; i < bookComplaints.size(); i++)
    {
        if(bookComplaints[i] == removed)
        {
           bookComplaints.removeAt(i);
           desComplaints.removeAt(i);
           i-=1;
        }
    }
}


// Creates and formats the table widgets in the accountPage widget
void MainWindow::createAccountTables()
{
    // For messageTableWidget
    // Sets the amount of columns to fit width of the widget
    ui->messageTableWidget->setColumnCount(2);
    ui->messageTableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // Sets the header of messageTableWidget
    QHeaderView *mheader = new QHeaderView(Qt::Horizontal,ui->messageTableWidget);
    ui->messageTableWidget->setHorizontalHeader(mheader);
    ui->messageTableWidget->setHorizontalHeaderLabels(QStringList() << "Message" << "Delete");
    ui->messageTableWidget->horizontalHeader()->show();

    // Formatting of messageTableWidget
    ui->messageTableWidget->setAlternatingRowColors(1);
    ui->messageTableWidget->setShowGrid(1);
    ui->messageTableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);

    // For historyTableWidget
    // Sets the amount of columns to fit width of the widget
    ui->historyTableWidget->setColumnCount(4);
    ui->historyTableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // Sets the header of historyTableWidget
    QHeaderView *hheader = new QHeaderView(Qt::Horizontal,ui->historyTableWidget);
    ui->historyTableWidget->setHorizontalHeader(hheader);
    ui->historyTableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Points Left" << "Last Read");
    ui->historyTableWidget->horizontalHeader()->show();

    // Formatting of historyTableWidget
    ui->historyTableWidget->setAlternatingRowColors(1);
    ui->historyTableWidget->setShowGrid(1);
    ui->historyTableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);
    ui->historyTableWidget->horizontalHeader()->setDefaultSectionSize(200);
}

// Initializes the messageTableWidget by filling the table with the user's messages.
// Initializes the historyTableWidget by filling the table with the books the user has purchased.
// If the table is empty, then the user does not have any messages or purchased any books.
void MainWindow::initAccountLists()
{
    // Make sure that tables are empty
    ui->messageTableWidget->setRowCount(0);
    ui->historyTableWidget->setRowCount(0);

    // Creates the QTableWidgetItem that will be inserted into a row in messageTableWidget
    QTableWidgetItem *mitem[2];
    for(int i = 0; i < this->messageList.size(); i++)
    {
        ui->messageTableWidget->insertRow(i);
        for(int j = 0; j < 2; j++)
        {
            mitem[j] = new QTableWidgetItem;
            switch(j)
            {
                // The item added to messageTableWidget[i,0] is the message at this->currentUser.getMessages()[i]
                // This item can only be read by the user.
                case 0:
                    mitem[j]->setText(this->messageList[i]);
                    mitem[j]->setFlags(Qt::NoItemFlags);
                    mitem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->messageTableWidget->setItem(i,j,mitem[j]);
                    break;

                // The item added to messageTableWidget[i,1] is the word "Delete".
                // The user clicks here to delete the message.
                case 1:
                    mitem[j]->setText("Delete");
                    mitem[j]->setFlags(mitem[j]->flags() & ~Qt::ItemIsEditable);
                    mitem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->messageTableWidget->setItem(i,j,mitem[j]);
                    break;
            }
        }
    }

        QTableWidgetItem *hitem[4];
        for(int k=0; k< currentUser.getHistory().size(); k++)
        {
             ui->historyTableWidget->insertRow(k);
             for(int l = 0; l < 4; l++) {
                 hitem[l] = new QTableWidgetItem;
                 switch(l)
                 {
                     case 0:
                         hitem[l]->setText(bookList[currentUser.getBookHistory()[k]].getTitle());
                         hitem[l]->setTextAlignment(Qt::AlignCenter);
                         ui->historyTableWidget->setItem(k, l, hitem[l]);
                         break;
                     case 1:
                         hitem[l]->setText(bookList[currentUser.getBookHistory()[k]].getAuthor());
                         hitem[l]->setTextAlignment(Qt::AlignCenter);
                         ui->historyTableWidget->setItem(k, l, hitem[l]);
                         break;
                     case 2:
                         if(this->currentUser.reading(currentUser.getBookHistory()[k]))
                             hitem[l]->setText(QString::number(currentUser.bookPoints(currentUser.getBookHistory()[k])));
                         else
                             hitem[l]->setText("0");
                         hitem[l]->setTextAlignment(Qt::AlignCenter);
                         ui->historyTableWidget->setItem(k, l, hitem[l]);
                         break;
                     case 3:
                         hitem[l]->setText(bookList[currentUser.getBookHistory()[k]].getLastRead().toString("yyyy.MM.dd"));
                         hitem[l]->setTextAlignment(Qt::AlignCenter);
                         ui->historyTableWidget->setItem(k, l, hitem[l]);
                         break;




                 }
             }
        }
}

// Action taken when a "Delete" cell is selected in the messageTableWidget.
// The message corresponding in the row of the cell clicked is deleted as well current user.
// The message table is re-populated to show this change.
void MainWindow::messageCellSelected(int r)
{
    // Remove the message at index r for the messageList and updates the messageList of the user.
    this->messageList.removeAt(r);
    this->currentUser.setMessages(this->messageList);
    this->currentUser.updateList(userList);

    // Make sure that tables are empty
    ui->messageTableWidget->setRowCount(0);

    // Creates the QTableWidgetItem that will be inserted into a row in messageTableWidget
    QTableWidgetItem *mitem[2];
    for(int i = 0; i < this->messageList.size(); i++)
    {
        ui->messageTableWidget->insertRow(i);
        for(int j = 0; j < 2; j++)
        {
            mitem[j] = new QTableWidgetItem;
            switch(j)
            {
                // The item added to messageTableWidget[i,0] is the message at this->currentUser.getMessages()[i]
                // This item can only be read by the user.
                case 0:
                    mitem[j]->setText(this->messageList[i]);
                    mitem[j]->setFlags(Qt::NoItemFlags);
                    mitem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->messageTableWidget->setItem(i,j,mitem[j]);
                    break;

                // The item added to messageTableWidget[i,1] is the word "Delete".
                // The user clicks here to delete the message.
                case 1:
                    mitem[j]->setText("Delete");
                    mitem[j]->setFlags(mitem[j]->flags() & ~Qt::ItemIsEditable);
                    mitem[j]->setTextAlignment(Qt::AlignCenter);
                    ui->messageTableWidget->setItem(i,j,mitem[j]);
                    break;
            }
        }
    }
}


// Create and fill the catalogTableWidget with a list of all the books in the system
void MainWindow::createCatalogTable()
{
    // Format the catalogTableWidget
    ui->catalogTableWidget->setColumnCount(3);
    QHeaderView *header = new QHeaderView(Qt::Horizontal,ui->catalogTableWidget);
    header->resizeSections(QHeaderView::Stretch);
    ui->catalogTableWidget->setHorizontalHeader(header);
    ui->catalogTableWidget->setHorizontalHeaderLabels(QStringList() <<"Cover" << "Title" << "Author");
    ui->catalogTableWidget->horizontalHeader()->show();
    ui->catalogTableWidget->verticalHeader()->hide();
    ui->catalogTableWidget->setAlternatingRowColors(1);
    ui->catalogTableWidget->setShowGrid(1);
    ui->catalogTableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);
    ui->catalogTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->catalogTableWidget->horizontalHeader()->setDefaultSectionSize(200);
    ui->catalogTableWidget->verticalHeader()->setDefaultSectionSize(200);


    // Clear the table of any items
    ui->catalogTableWidget->setRowCount(0);

    // Fills the table with the current bookList, where each row gives one book information
    // Each row will contain the book's cover page, title, and author.
    QTableWidgetItem *item[3];
    for(int i=0; i<this->bookList.size(); i++) {
         ui->catalogTableWidget->insertRow(i);
         for(int j = 0; j < 3; j++) {
             item[j] = new QTableWidgetItem;
             switch(j)
             {
                 case 0:
                     item[j]->setData(Qt::DecorationRole, this->bookList[i].getCover().scaled(200, 200));
                     ui->catalogTableWidget->setItem(i, j, item[j]);
                     break;
                 case 1:
                     item[j]->setText(this->bookList[i].getTitle());
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->catalogTableWidget->setItem(i, j, item[j]);
                     break;
                 case 2:
                     item[j]->setText(this->bookList[i].getAuthor());
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->catalogTableWidget->setItem(i, j, item[j]);
                     break;
             }
         }
     }
}

// Create and fill the table widget that is being shown in recommendWidget
void MainWindow::createRecommendTable()
{
    // The topListWidget is shown on the catalogPage
    if (recommendCurrentIndex == 0)
    {
        // Format and clear the list widget
        ui->topListWidget->clear();
        ui->topListWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);

        // Create a list of all the books in the sytem and sorts it according the books with most views.
        QVector<book> tempList = this->bookList;
        qStableSort(tempList.begin(), tempList.end(), greaterThan);

        // Clear the fiveBooks of previously stored books
        fiveBooks.clear();

        // The first five books are stored in fiveBooks
        for(int i = 0; i < 5 && i < tempList.size(); i ++)
        {
            fiveBooks.append(tempList[i]);
        }

        // Show the list of the top five most viewed books in the system.
        for(int i = 0; i < fiveBooks.size(); i++)
        {
            ui->topListWidget->addItem(fiveBooks[i].getTitle());
        }
    }

    // The recommendListWidget is shown on the catalogPage
    else
    {
        // Format and clear the list widget
        ui->recommendListWidget->clear();
        ui->recommendListWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);

        // Finds first five books in the system that has the same genres as the ones in the user's book history
        // and stores them in fiveBooks.
        QVector<int> history = this->currentUser.getBookHistory();

        // Clear the fiveBooks of previously stored books
        fiveBooks.clear();


        for(int i = 0; i < history.size() && fiveBooks.size() <= 5; i++)
        {
            for(int j = 0; j < this->bookList.size() && fiveBooks.size() <= 5; j++)
            {
                if (this->bookList[history[i]].getGenre() == this->bookList[j].getGenre() && !(history.contains(j)))
                    fiveBooks.append(this->bookList[j]);
            }
        }

        QVector<book> tempList = this->bookList;
        qStableSort(tempList.begin(), tempList.end(), greaterThan);

        int cursize = fiveBooks.size();
        if (cursize != 0)
            cursize--;
        // The first five books are stored in fiveBooks
        for(int i = cursize; i < 5 && i < tempList.size(); i ++)
        {
            if (tempList[i].findBook(fiveBooks) == fiveBooks.size())
                fiveBooks.append(tempList[i]);
        }


        // Show the list of the five recommended books in the system.
        // If the lsit is empty, then no matches were found.
        for(int i = 0; i < fiveBooks.size(); i++)
        {
            ui->recommendListWidget->addItem(fiveBooks[i].getTitle());
        }
    }
}

// The user is taken to the book summary page of the specific book that was clicked in topListWidget
void MainWindow::findtBookID(QListWidgetItem*)
{
    int row = ui->topListWidget->currentRow();
    summaryPage(fiveBooks[row].findBook(this->bookList));
}

// The user is taken to the book summary page of the specific book that was clicked in recommendListWidget
void MainWindow::findrBookID(QListWidgetItem*)
{
    int row = ui->recommendListWidget->currentRow();
    summaryPage(fiveBooks[row].findBook(this->bookList));
}


// Determines which page should be shown in the inviteWidget
void MainWindow::invitePageShowed()
{
    bool checked = false;
    // If the current user has sent an invite to another user to read this book and is waiting for a reply.
    // The current index of inviteWidget is set to 2, which shows a message "waiting for invite reply"
    for(int i = 0; i < this->currentUser.getSentInvites().size(); i++)
    {
        if(this->currentUser.getSentInvites()[i].getbookID() == this->currentBookID)
        {
            ui->inviteWidget->setCurrentIndex(2);
            checked = true;
            break;
        }
    }

    // If the current user was invited to to read this book by another user, the current index of inviteWidget
    // is set to 1, which gives an option to the user to accept or decline the invite.
    for(int i = 0; i < this->currentUser.getInvites().size(); i++)
    {
        if(this->currentUser.getInvites()[i].getbookID() == this->currentBookID)
        {
            ui->inviteWidget->setCurrentIndex(1);
            this->currentInvite = this->currentUser.getInvites()[i];
            checked = true;
            break;
        }
    }

    // If the current user does not have any pending invites or been invited to read the book.
    // The user has the option to invite another user to split the cost. (Index 0)
    if(!checked)
        ui->inviteWidget->setCurrentIndex(0);
    checked = false;
}

// Actions taken when the user chooses to send an invite for the current book to another user.
void MainWindow::sendInviteClicked(){

    // Takes the user input for the invitee and the points being split.
    QString username = ui->usernameInput->text();
    int points = ui->pointInput->value();

    // Message box that will open
    QMessageBox msgBox;

    // The current user tried to send an invite to himself.
    if(this->currentUser.getUsername() == username)
    {
        msgBox.setText("Error");
        msgBox.setDetailedText("You entered your username.");
        msgBox.exec();
    }

    // The current user tried to set the asking split points to 0.
    else if (points == 0)
    {
        msgBox.setText("Error");
        msgBox.setDetailedText("Points cannot be set to 0.");
        msgBox.exec();
    }

    // The current user tried to set the asking split points to an odd number.
    else if (points%2 != 0)
    {
        msgBox.setText("Error");
        msgBox.setDetailedText("Points cannot be odd. Must be even.");
        msgBox.exec();
    }

    // The invite is sent to the user with the user input for the username. If the function call
    // to sendInvite is 1, then the username couldn't be found, a message window displays this.
    else if (this->currentUser.sendInvite(this->userList,username,this->currentBookID,points) == 1)
    {
         msgBox.setText("Error");
         msgBox.setDetailedText("Username could not be found.");
         msgBox.exec();
    }

    // Otherwise, the invite was successfully sent and the user gets a confimation message on a pop
    // window and a message to his account. The invited user gets a message of the invite. The
    // inviteWidget is set to the page with the message, waiting for reply.
    else{
        // Confirmation message
        msgBox.setText("Message Sent");
        msgBox.exec();

        // Confirmation message to user's account
        QString message = "You invited " + username + " to read " + this->bookList[this->currentBookID].getTitle() +
                ". Points split: " + QString::number(points);
        this->currentUser.addMessages(message);

        // Message sent to invited
        message = this->currentUser.getUsername() + " invites you to read " +
                this->bookList[this->currentBookID].getTitle() + ". Points split: " + QString::number(points);
        user temp(username, "");
        int userIn = temp.findUser(this->userList);
        this->userList[userIn].addMessages(message);

        // Set the inviteWidget to waiting page
        ui->inviteWidget->setCurrentIndex(2);
    }
}

// The current user accepts the invite to read the current book together. A message is sent to both users.
// Both users should have the book added to their history.
void MainWindow::acceptInviteClicked()
{
    // User accepted invite by clicking accept button and the inviteWidget goes back to the invite page.
    this->currentUser.acceptInvite(this->userList, currentInvite);
    ui->inviteWidget->setCurrentIndex(0);

    // Message is sent to the inviter.
    QString message = this->userList[this->currentInvite.getUserID()].getUsername() + " accepted invite to read" +
            this->bookList[this->currentBookID].getTitle() + ". Points split: " + QString::number(currentInvite.getPoints());
    this->userList[this->currentInvite.getUserID()].addMessages(message);

    // Message sent to this user.
    message = "You accepted" + this->userList[this->currentInvite.getUserID()].getUsername() + "'s invite to read " +
            this->bookList[this->currentBookID].getTitle() + ". Points split: " + QString::number(this->currentInvite.getPoints());
    this->currentUser.addMessages(message);
}

// The current user rejects the invite to read the current book together. A message is sent to both users.
void MainWindow::rejectInviteClicked()
{
    // User rejected invite by clicking accept button and the inviteWidget goes back to the invite page.
    this->currentUser.acceptInvite(this->userList, currentInvite);
    ui->inviteWidget->setCurrentIndex(0);
    ui->readChoiceWidget->setCurrentIndex(0);

    // Message is sent to the inviter.
    QString message = this->userList[this->currentInvite.getUserID()].getUsername() + " rejected invite to read " +
            this->bookList[this->currentBookID].getTitle() + ". Points split: " + QString::number(currentInvite.getPoints());
    this->userList[this->currentInvite.getUserID()].addMessages(message);

    // Message sent to this user.
    message = "You rejected" + this->userList[this->currentInvite.getUserID()].getUsername() + "'s invite to read " +
            this->bookList[this->currentBookID].getTitle() + ". Points split: " + QString::number(this->currentInvite.getPoints());
    this->currentUser.addMessages(message);
}


// Create and format the searchTableWidget
void MainWindow::createSearchTable()
{
    // Format the catalogTableWidget
    ui->searchTableWidget->setColumnCount(3);
    QHeaderView *header = new QHeaderView(Qt::Horizontal,ui->searchTableWidget);
    header->resizeSections(QHeaderView::Stretch);
    ui->searchTableWidget->setHorizontalHeader(header);
    ui->searchTableWidget->horizontalHeader()->show();
    ui->searchTableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Genre");
    ui->searchTableWidget->setAlternatingRowColors(1);
    ui->searchTableWidget->setShowGrid(1);
    ui->searchTableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);
    ui->searchTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Clear the table of any items
    ui->searchTableWidget->setRowCount(0);
}

// The search table is updated to show the matching item being searched by the user.
// The searchTableWidget is filled with the matching information.
void MainWindow::searchClicked(int in)
{
    // Grabs the the usr inputs and empties the table
    ui->searchTableWidget->setRowCount(0);
    bool search = true;
    QVector<int> match;
    QString searching = (ui->searchLineEdit->text()).toLower();

    // If the user picekd the "Search for..." option then a serach is not conducted
    if (in == 0)
        search = false;

    // All the matching book titles with the user input are noted with the book's index in the bookList
    else if (in == 1)
    {
        for (int i = 0; i < this->bookList.size(); i++)
        {
            if( (this->bookList[i].getTitle()).toLower().contains(searching))
                match.append(i);
        }
    }

    // All the matching book authors with the user input are noted with the book's index in the bookList
    else if (in == 2)
    {
        for (int i = 0; i < this->bookList.size(); i++)
        {
            if( (this->bookList[i].getAuthor()).toLower().contains(searching))
                match.append(i);
        }
    }

    // All the matching book genre with the user input are noted with the book's index in the bookList
    else
    {
        for (int i = 0; i < this->bookList.size(); i++)
        {
            if( (this->bookList[i].getGenre()).toLower().contains(searching))
                match.append(i);
        }
    }
    // Determines which book information the user is searching for.
    // Fills the table with the current bookList, where each row gives one book information
    // Each row will contain the book's cover page, title, and author.
    QTableWidgetItem *item[3];

    for(int i=0; i < match.size(); i++)
    {
        int in = match[i];
         ui->searchTableWidget->insertRow(i);
         for(int j = 0; j < 3; j++)
         {
             item[j] = new QTableWidgetItem;
             switch(j)
             {
                 case 0:
                     item[j]->setText(this->bookList[in].getTitle());
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->searchTableWidget->setItem(i, j, item[j]);
                     break;
                 case 1:
                     item[j]->setText(this->bookList[in].getAuthor());
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->searchTableWidget->setItem(i, j, item[j]);
                     break;
                 case 2:
                     item[j]->setText(this->bookList[in].getGenre());
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->searchTableWidget->setItem(i, j, item[j]);
                     break;
             }
         }
     }
}

// The user clicked on the writeReviewButton and the review table is replaced with a form for the user to rate/review the book.
void MainWindow::reviewBook()
{
    ui->reviewWidget->setCurrentIndex(1);
    ui->reviewTextEdit->clear();
    ui->ratingBox->setCurrentIndex(0);
    ui->errorMessageLabel->setText("");
}

// The user must enter both the rating and review to submit a review successfully.
// After submitting the review, the reviewWidget goes back to the page showing the review table and it is updated
// to show the new review made.
void MainWindow::makeReview()
{
    QString reviewText = ui->reviewTextEdit->toPlainText();
    int ratingChoice = ui->ratingBox->currentIndex() - 1;
    if (reviewText == "")
        ui->errorMessageLabel->setText("Error. No Review Made.");
    else if (ratingChoice == -1)
        ui->errorMessageLabel->setText("Error. No Rating Made.");
    else
    {
        review temp(this->currentUser.getUsername(),reviewText,ratingChoice);
        this->bookList[currentBookID].addReview(temp, this->currentUser);
        ui->summaryRatingLabel->setText(QString::number(this->bookList[currentBookID].getRating()));
    }

    reviewTable();
}

// The review table is shown on the bookSummaryPage widget. It contains all the reviews that were
// given to the current book.
void MainWindow::reviewTable()
{
    // Show the page with the reviewTableWidget.
    ui->reviewWidget->setCurrentIndex(0);

    // Format the reviewTableWidget.
    ui->reviewTableWidget->setColumnCount(3);
    QHeaderView *header = new QHeaderView(Qt::Horizontal,ui->reviewTableWidget);
    header->resizeSections(QHeaderView::Stretch);
    ui->reviewTableWidget->setHorizontalHeader(header);
    ui->reviewTableWidget->setHorizontalHeaderLabels(QStringList() << "User" << "Rating" << "Review");
    ui->reviewTableWidget->horizontalHeader()->show();
    ui->reviewTableWidget->verticalHeader()->hide();
    ui->reviewTableWidget->setAlternatingRowColors(1);
    ui->reviewTableWidget->setShowGrid(1);
    ui->reviewTableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);

    // Clear the table of any items
    ui->reviewTableWidget->setRowCount(0);

    // Get the list of reviews for this book.
    QVector<review> temp = this->bookList[currentBookID].getReviews();

    // Fills the table with the current book'List's reviews, where each row gives one reviewer's information.
    QTableWidgetItem *item[3];
    for(int i=0; i < temp.size(); i++) {
         ui->reviewTableWidget->insertRow(i);

         for(int j = 0; j < 3; j++) {
             item[j] = new QTableWidgetItem;
             switch(j)
             {
                 case 0:
                     item[j]->setText(temp[i].getUsername());
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->reviewTableWidget->setItem(i, j, item[j]);
                     break;
                 case 1:
                     item[j]->setText(QString::number(temp[i].getRating()));
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->reviewTableWidget->setItem(i, j, item[j]);
                     break;
                 case 2:
                     item[j]->setText(temp[i].getReview());
                     item[j]->setTextAlignment(Qt::AlignCenter);
                     ui->reviewTableWidget->setItem(i, j, item[j]);
                     break;
             }
         }
     }
}

// The user edits his bad word list by adding or removing a word.
void MainWindow::editWordList(int i)
{
    QString word = ui->wordLineEdit->text();
    if (word != "")
    {
        // Adding a word to the list
        if(i == 1)
            this->currentUser.addBadWord(word);

        // Removes the word from the list
        else if (i == 2)
            this->currentUser.removeBadWord(this->currentUser.getBadWords().indexOf(word, 0));
    }

    // Show updated wordList
    createWordList();

    // Reset the user input
    ui->wordLineEdit->setText("");
    ui->wordBox->setCurrentIndex(0);
}

// Shows the list of bad words the user made.
void MainWindow::createWordList()
{
    // Format and clear the list widget
    ui->wordListWidget->clear();
    ui->wordListWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);

    // Gets the list of bad words.
    QStringList badWords = this->currentUser.getBadWords();

    // Shows the list of bad words the user made.
    for(int i = 0; i < badWords.size(); i++)
    {
        ui->wordListWidget->addItem(badWords.at(i));
    }
}

// Searches through the current book's text for the user's bad words.
// If no bad words are found, then a message appears with a message for this.
// If bad words were found, then the user is automatically taken to the report page with the form filled out.
// The user has the choice to send the report or not.
void MainWindow::badWordSearch()
{
    //this->bookList[currentBookID].setText();
    QStringList words = this->currentUser.getBadWords();
    QStringList foundBad;

    // Looks through the text of the current book for bad words.
    for(int i = 0; i < words.size(); i++)
    {
        if(this->bookList[currentBookID].wordSearch(words.at(i)))
        {
            foundBad.append(words);
            i++;
        }
    }

    // Message box appears with the result if none of the bad words were found.
    if (foundBad.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("No Results");
        msgBox.setDetailedText("None of the words on your list of bad words were found in the text.");
        msgBox.exec();
    }
    else
    {
        // Fills out the book information of the complaint.
        ui->reportTitleLineEdit->setText(this->bookList[currentBookID].getTitle());
        ui->reportAuthorLineEdit->setText(this->bookList[currentBookID].getAuthor());
        ui->reportMessageLabel->setText("");

        // Description is written to have all the bad words found in the text.
        QString description = "The following bad words were found: \n";
        for(int i = 0; i < foundBad.size(); i++)
        {
            description += (foundBad.at(i) + "\n");
        }

        ui->descriptionTextEdit->setText(description);

        // User is sent to the reportPage with all the information filled out.
        ui->pageWidget->setCurrentIndex(4);
    }
}




// Function for when a user clicks on the read Button
void MainWindow::readButton()
{
    QTime c;
    int timeSpent;

    // Update stats for the book and user
    QDate timeRead = QDate::currentDate();
    this->bookList[this->currentBookID].addView();
    this->bookList[this->currentBookID].setLastRead(timeRead);
    ui->writeReviewButton->show();

    // Based on the amount of points the user has left on the book, the time of how long the text should be shown
    // is calculated.
    int pointsLeft = this->currentUser.bookPoints(this->currentBookID);
    int timeToRead = (pointsLeft /this->bookList[this->currentBookID].getCost()) * 1000;

    // Create a new window that opens which shows the current book's text until the user runs out of points
    // or the user chooses to close the window
    readBook w(bookList[currentBookID]);
    w.setModal(true);
    QTimer::singleShot(timeToRead,&w,SLOT(close()));
    c.start();
    w.exec();

    // The time that text window was opened is calculated.
    if(w.close())
        timeSpent= c.elapsed();

    // The time left is calculated to be the value of timeToRead.
    timeToRead = timeToRead-timeSpent;

    // If the new timeToRead is positive, then the user still can read the book,
    // the amount of points left is noted. Otherwise, the user gets the book removed
    // from his reading list and the readChoiceWidget switches back to points page.
    if(timeToRead > 0)
    {
        int newtime = (timeSpent/1000) * this->bookList[this->currentBookID].getCost();

        if(this->currentUser.deductReading(this->currentBookID, newtime, this->userList))
        {
            ui->readChoiceWidget->setCurrentIndex(0);
        }
    }
    else
    {
        if(!(this->currentUser.deductReading(this->currentBookID, pointsLeft, this->userList)))
        {
            ui->readChoiceWidget->setCurrentIndex(1);
        }
    }
}


// Function for user to indicate the amount of points he/she would like to spend on to read a book
// Opens a QDialog with a textBrowser that displays the book content
void MainWindow::spendPointsButton()
{
    int pointsToSpend = ui->pointSpendBox->value();

    if(pointsToSpend > currentUser.getPoints())
        QMessageBox::information(this, tr("Error"), tr("Not Enough Points to read Book."));
    else if (pointsToSpend == 0)
        QMessageBox::information(this, tr("Error"), tr("Using 0 Points."));
    else
    {
        ui->readChoiceWidget->setCurrentIndex(0);
        this->currentUser.addBook(this->currentBookID,pointsToSpend);
    }
}


//Function to browse for a file on the user's computer
//When the browse button is clicked
//a window will open in which the user can browse
//through their computer for the file they wish to upload
void MainWindow::browse()
{
    QString filePathName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/");
    ui->fileLineEdit->setText(filePathName);
}

//Function to browse for a image on the user's computer
//When the browse button is clicked
//a window will open in which the user can browse
//through their computer for the image they wish to upload
void MainWindow::browseImg()
{
    QString filePathName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/");
    ui->thing->setText(filePathName);
}

//Function for when the upload button I clicked on
//If any of the fields are empty, then an error message is
//triggered through an if statement
//Else all the text in each lineEdit is taken as
//parameters to be used to create a new book
//this book is then added onto the a list of potential books
void MainWindow::uploadFile()
{
    if( ui->titleLineEdit->text() == "" || ui->authorLineEdit->text() == "" || ui->pointsLineEdit->text() == "" || ui->genreLineEdit->text() == "" || ui->fileLineEdit->text() == "")
        QMessageBox::information(this, tr("Error"), tr("Some information has not been provided."));
    else
    {
        QString titleOfBook = ui->titleLineEdit->text();
        QString authorOfBook = ui->authorLineEdit->text();
        int worthOfBook = ui->pointsLineEdit->text().toInt();
        QString genreOfBook = ui->genreLineEdit->text();
        QString pathOfBook = ui->fileLineEdit->text();
        QString imgPathOfBook = ui->thing->text();
        book newBook(titleOfBook, authorOfBook, "");
        newBook.setWorth(worthOfBook);
        newBook.addText(pathOfBook);
        newBook.setGenre(genreOfBook);
        newBook.setUploader(currentUser.getUserId());
        newBook.loadImage(imgPathOfBook);
        newBook.addBook(this->potentialList);

        QMessageBox::information(this, tr("Done."), tr("Your book has been uploaded to be review by a super user."));
        ui->titleLineEdit->setText("");
        ui->authorLineEdit->setText("");
        ui->pointsLineEdit->setText("");
        ui->genreLineEdit->setText("");
        ui->fileLineEdit->setText("");
        ui->thing->setText("");
    }
}
