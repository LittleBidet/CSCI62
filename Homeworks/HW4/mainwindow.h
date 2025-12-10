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
    //Pre: N/A
    //Post: Switches the theme for the current user
    void themeTogglePressed();
    //Pre: A QString text pointer
    //Post: Updates the search suggestions after every change to the QString
    void searchTextChanged(const QString &text);
    //Pre: A row and column corresponding to the location in the table that was clicked.
    //Post: Changes the screen to the clicked user's profile
    void searchSuggestionClicked(int row, int col);
    //Pre: n/a
    //Post: Increments the like counter for the corresponding post.
    void likePost1();
    void likePost2();
    void likePost3();
    void likePost4();
    void likePost5();
    //Pre: n/a
    //Post: Applies the User's saved theme
    void applyTheme();



    //Current logged in user
    User* user;
    //User of the friend we are looking at
    User* profile_user;
    Network* social_network;
    std::vector<Post*> displayedPosts;
};
#endif // MAINWINDOW_H
