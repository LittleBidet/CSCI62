#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initializes the network from a file
    social_network = new Network();
    social_network->readUsers("users.txt");
    social_network->readPosts("posts.txt");

    //Hide Everything
    ui->friendList->hide();
    ui->loginButton->hide();
    ui->loginInput->hide();
    ui->loginPrompt->hide();
    ui->post1->hide();
    ui->post2->hide();
    ui->post3->hide();
    ui->post4->hide();
    ui->post5->hide();
    ui->returnButton->hide();
    ui->userLabel->hide();
    ui->recList->hide();
    ui->addButton->hide();
    ui->postButton->hide();
    ui->postInput->hide();

    //initial login state
    loginState();

    //Connectors
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginHandler);
    connect(ui->friendList, &QTableWidget::cellClicked, this, &MainWindow::friendPressed);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::backButtonPressed);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addFriendPressed);
    connect(ui->recList, &QTableWidget::cellClicked, this, &MainWindow::suggestedPressed);
    connect(ui->postButton, &QPushButton::clicked, this, &MainWindow::addPostPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loginState(){
    ui->loginButton->show();
    ui->loginInput->show();
    ui->loginPrompt->show();
}
void MainWindow::profileState(){
    ui->loginButton->hide();
    ui->loginInput->hide();
    ui->loginPrompt->hide();

    ui->userLabel->show();
    ui->friendList->show();
    ui->post1->show();
    ui->post2->show();
    ui->post3->show();
    ui->post4->show();
    ui->post5->show();
    ui->postButton->show();
    ui->postInput->show();
    ui->recList->show();
}
void MainWindow::loginHandler()
{
    std::string name = ui->loginInput->toPlainText().toStdString();
    int userId = social_network->getId("       " + name);

    //Checks for a valid user
    if(userId == -1){
        ui->loginPrompt->setText("User not found. Please Try another User: ");
        ui->loginInput->clear();
    }
    else{
        user = social_network->getUser(userId);
        profile_user = user;
        displayProfile(user);
    }
}

void MainWindow::displayProfile(User* currentUser)
{
    //switches to the profile state
    profileState();
    //Own Profile
    if(currentUser->getId() == user->getId()){
        ui->userLabel->setText("My Profile");
        ui->returnButton->hide();
        ui->addButton->hide();
        ui->recList->show();
    }
    else{
        //Friend profile
        QString name = QString::fromStdString(currentUser->getName());
        ui->userLabel->setText(name + "'s Profile");
        ui->returnButton->show();
        ui->addButton->show();
        ui->recList->hide();
    }

    //Sets up the friend table
    ui->friendList->clearContents();
    std::set<int> friends = currentUser->getFriends();
    ui->friendList->setRowCount(friends.size());
    ui->friendList->setColumnCount(1);

    int currentRow = 0;
    for(int friendId : friends){
        User* friendUser = social_network->getUser(friendId);
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(friendUser->getName()));
        item->setData(Qt::UserRole, friendId);
        ui->friendList->setItem(currentRow, 0, item);
        currentRow++;
    }

    //Sets up the recommended table
    ui->recList->clearContents();
    int score = 2;
    std::vector<int> recommendations = social_network->suggestFriends(currentUser->getId(), score);
    ui->recList->setRowCount(recommendations.size());
    ui->recList->setColumnCount(1);

    int curRow = 0;
    for(int recommendedId : recommendations){
        User* recommendedUser = social_network->getUser(recommendedId);
        QTableWidgetItem* recommendedItem = new QTableWidgetItem(QString::fromStdString(recommendedUser->getName()));
        recommendedItem->setData(Qt::UserRole, recommendedId);
        ui->recList->setItem(curRow, 0, recommendedItem);
        curRow++;
    }

    //Five most recent posts
    QLabel* postLabels[] = {ui->post1, ui->post2, ui->post3, ui->post4, ui->post5};
    std::vector<Post*> posts = social_network->getPosts(currentUser->getId());
    int postCount = 0;
    for(int i = posts.size() - 1; i >= 0 && postCount < 5; i--){
        Post* post = posts[i];
        std::string postText = social_network->postDisplayString(post);
        postLabels[postCount]->setText(QString::fromStdString(postText));
        postLabels[postCount]->show();
        postCount++;
    }
}
void MainWindow::friendPressed(int row)
{
    QTableWidgetItem* item = ui->friendList->item(row, 0);
    int friendId = item->data(Qt::UserRole).toInt();
    //switches to the friend profile
    profile_user = social_network->getUser(friendId);
    displayProfile(profile_user);
}

void MainWindow::backButtonPressed()
{
    profile_user = user;
    displayProfile(user);
}
void MainWindow::suggestedPressed(int row)
{
    QTableWidgetItem* item = ui->recList->item(row, 0);
    int suggestedId = item->data(Qt::UserRole).toInt();

    //Adds the suggested as a friend
    social_network->addConnection(user->getName(), social_network->getUser(suggestedId)->getName());
    //Updates the user file
    social_network->writeUsers("users.txt");
    displayProfile(user);

}
void MainWindow::addFriendPressed()
{
    social_network->addConnection(user->getName(), profile_user->getName());
    //Updates the user file
    social_network->writeUsers("users.txt");
    //refresh profile
    displayProfile(profile_user);
}
void MainWindow::addPostPressed()
{
    std::string message = ui->postInput->toPlainText().toStdString();
    if(!message.empty()){
        int authorId = user->getId();
        int profileId = profile_user->getId();
        Post* newPost = new Post(profileId, authorId, message, 0);
        social_network->addPost(newPost);
        social_network->writePosts("posts.txt");
        ui->postInput->clear();
        displayProfile(profile_user);
    }
}
