#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network.h"
#include "post.h"
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //Pre: N/A
    //Post: Changes the UI to the login state
    void loginState();
    //Pre: N/A
    //Post: Changes the UI to the profile state
    void profileState();

    //Pre: N/A
    //Post: Checks if login is valid and if so switches to the user profile
    void loginHandler();
    //Pre: A user pointer
    //Post: Displays the user's profile
    void displayProfile(User* user);
    //Pre: N/A
    //Post: Returns to the original user's profile
    void backButtonPressed();
    //Pre: the row number of the friend in the list
    //Post: switches the display to the friend
    void friendPressed(int row);
    //Pre: the row number of the suggested in the list
    //Post: Adds the suggested user as a friend
    void suggestedPressed(int row);
    //Pre: N/A
    //Post: Adds the user as a friend
    void addFriendPressed();
    //Pre: N/A
    //Post: Adds a post
    void addPostPressed();
    //Pre: N/A
    //Post: updates the posts file
    void updatePosts();
    //Pre: N/A
    //Post: updates the users file
    void updateUsers();


    //Current logged in user
    User* user;
    //User of the friend we are looking at
    User* profile_user;
    Network* social_network;
};
#endif // MAINWINDOW_H
