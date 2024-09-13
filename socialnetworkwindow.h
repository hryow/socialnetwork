#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkWindow; }
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();
    void enterName();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_addFriend_clicked();

    void on_friends_list_cellClicked(int row, int column);

    void on_suggested_friends_list_cellClicked(int row, int column);

    void on_posts_cellClicked(int row, int column);

    void on_laugh_clicked();

    void on_likes_clicked();

    void on_lives_clicked();

    void on_loves_clicked();

private:
    Ui::SocialNetworkWindow *ui;
    User* currUser;
    User* loginUser;
    Post* currPost;
    Network n;
};
#endif // SOCIALNETWORKWINDOW_H 
