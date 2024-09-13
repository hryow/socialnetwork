#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);
    ui->label_2->hide();
    ui->friends_list->hide();
    ui->posts->hide();
    ui->profile_label->hide();
    ui->suggested_friends_list->hide();
    ui->pushButton_back->hide();
    ui->pushButton_addFriend->hide();
    ui->label_3->hide();
    ui->laugh->hide();
    ui->likes->hide();
    ui->lives->hide();
    ui->loves->hide();


    User* user1 = new User(0, "Sally Kim", 2004, 39208, std::vector<size_t> {1, 4, 3});
    User* user2 = new User(1, "Ashley Cha", 2002, 38247, std::vector<size_t> {0, 4, 3});
    User* user3 = new User(2, "Megan Chua", 2010, 23948, std::vector<size_t> {3, 4});
    User* user4 = new User(3, "Robin Lee", 2002, 87953, std::vector<size_t> {0, 1, 2});
    User* user5 = new User(4, "Joseph Hong", 2003, 89743, std::vector<size_t> {0, 1, 2});
    n.addUser(user1);
    n.addUser(user2);
    n.addUser(user3);
    n.addUser(user4);
    n.addUser(user5);

    std::vector<std::string> plikes = {"Yumiko Tanido", "Beau Tse"};
    std::vector<std::string> ploves = {"Ashley Cha"};
    std::vector<std::string> plaughs = {"Joseph Hong"};
    std::vector<std::string> plives = {};

    std::vector<std::string> p1likes = {"Sally Kim", "Ashley Cha"};
    std::vector<std::string> p1loves = {};
    std::vector<std::string> p1laughs = {"Megan Chua"};
    std::vector<std::string> p1lives = {"Robin Lee"};

    std::vector<std::string> p2likes = {"Theo Cabot", "Yumiko Tanido", "DPR Ian", "Bryan Alexander", "Beau Tse"};
    std::vector<std::string> p2loves = {"Sally Kim", "Ashley Cha", "Megan Chua"};
    std::vector<std::string> p2laughs = {"Robin Lee", "Aara Cha", "Annie Nguyen"};
    std::vector<std::string> p2lives = {"Anna Chen"};

    n.addPost(1, "hi", plikes, plaughs, ploves, plives, true, 2, true);
    n.addPost(1, "wew", p1likes, p1laughs, p1loves, p1lives, false, 0, true);
    n.addPost(1, "wew", p2likes, p2laughs, p2loves, p2lives, false, 0, true);
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}

void SocialNetworkWindow::on_pushButton_login_clicked()
{
    QString username = ui->textEdit->toPlainText();

    // check if the user is in the network
    bool found = false;
    for (std::size_t i = 0; i < n.numUsers(); i++) {
        if (n.getUser(i)->getName() == username.toStdString()) {
            found = true;
        }
    }
    if (found) {
        // if the user is found, hide all the widgets
        ui->label->hide();
        ui->label_2->hide();
        ui->textEdit->hide();
        ui->pushButton_login->hide();

        // get pointers to the currently logged in user
        std::size_t userid = n.getId(username.toStdString());
        currUser = n.getUser(userid);
        loginUser = n.getUser(userid);

        // show the user's profile page
        // show the profile label
        ui->profile_label->setText("My Profile");
        ui->profile_label->show();

        // show all the user's friends
        for (std::size_t i = 0; i < loginUser->getFriends().size(); i++) {
            // add the friends to the QTableWidget
            ui->friends_list->insertRow(ui->friends_list->rowCount());
            User* friends = n.getUser(loginUser->getFriends()[i]);
            QString friendname = QString::fromStdString(friends->getName());
            ui->friends_list->setItem(i, 0, new QTableWidgetItem(friendname));
        }
        ui->friends_list->show();

        // show the user's 5 most recent posts
        QString poststring;
        std::vector<Post*> vector = loginUser->getMessages();
        if (vector.size() < 5) {
            for (std::size_t i = 0; i < vector.size(); i++) {
                // add the user's posts to the QTableWidget
                ui->posts->insertRow(ui->posts->rowCount());
                poststring = QString::fromStdString(vector[i]->getMessage());
                ui->posts->setItem(i, 0, new QTableWidgetItem(poststring));
            }
        }
        else {
            for (std::size_t i = 0; i < 5; i++) {
                // add the user's posts to the QTableWidget
                ui->posts->insertRow(ui->posts->rowCount());
                poststring = QString::fromStdString(vector[i]->getMessage());
                ui->posts->setItem(i, 0, new QTableWidgetItem(poststring));
            }
        }
        ui->posts->setItem(1,1,new QTableWidgetItem("hi"));
        ui->posts->show();

        // show a list of friend suggestions
        std::size_t score;
        std::vector<std::size_t> friendsuggestions = n.suggestFriends(loginUser->getId(), score);
        for (std::size_t i = 0; i < friendsuggestions.size(); i++) {
            // add the suggested friends to the QTableWidget
            ui->suggested_friends_list->insertRow(ui->suggested_friends_list->rowCount());
            User* suggestedfriends = n.getUser(friendsuggestions[i]);
            QString friendname = QString::fromStdString(suggestedfriends->getName());
            ui->suggested_friends_list->setItem(i, 0, new QTableWidgetItem(friendname));
        }
        ui->suggested_friends_list->show();
    }
    else {
        ui->label_2->show();
    }
}


void SocialNetworkWindow::on_pushButton_back_clicked()
{
    // send the user back to their profile page when clicked
    ui->friends_list->hide();
    ui->posts->hide();
    ui->profile_label->hide();
    ui->suggested_friends_list->hide();
    ui->pushButton_back->hide();
    ui->pushButton_addFriend->hide();

    // show the user's profile page
    // show the profile label
    ui->profile_label->setText("My Profile");
    ui->profile_label->show();

    // show all the user's friends
    for (std::size_t i = 0; i < loginUser->getFriends().size(); i++) {
        // add the friends to the QTableWidget
        ui->friends_list->insertRow(ui->friends_list->rowCount());
        User* friends = n.getUser(loginUser->getFriends()[i]);
        QString friendname = QString::fromStdString(friends->getName());
        ui->friends_list->setItem(i, 0, new QTableWidgetItem(friendname));
    }
    ui->friends_list->show();

    // show the user's 5 most recent posts
    QString post;
    std::vector<Post*> vector = currUser->getMessages();
    if (vector.size() < 5) {
        for (std::size_t i = 0; i < vector.size(); i++) {
            ui->posts->insertRow(ui->posts->rowCount());
            post = QString::fromStdString(vector[i]->getMessage());
            ui->posts->setItem(i, 1, new QTableWidgetItem(post));
        }
    }
    else {
        for (std::size_t i = 0; i < 5; i++) {
            // add the user's posts to the QTableWidget
            ui->posts->insertRow(ui->posts->rowCount());
            post = QString::fromStdString(vector[i]->getMessage());
            ui->posts->setItem(i, 1, new QTableWidgetItem(post));
        }
    }
    ui->posts->show();

    // show a list of friend suggestions
    std::size_t score;
    std::vector<std::size_t> friendsuggestions = n.suggestFriends(loginUser->getId(), score);
    for (std::size_t i = 0; i < friendsuggestions.size(); i++) {
        // add the suggested friends to the QTableWidget
        ui->suggested_friends_list->insertRow(ui->suggested_friends_list->rowCount());
        User* suggestedfriends = n.getUser(friendsuggestions[i]);
        QString friendname = QString::fromStdString(suggestedfriends->getName());
        ui->suggested_friends_list->setItem(i, 0, new QTableWidgetItem(friendname));
    }
    ui->suggested_friends_list->show();
}


void SocialNetworkWindow::on_pushButton_addFriend_clicked()
{
    // add the user as a friend
    loginUser->addFriend(currUser->getId());

}

void SocialNetworkWindow::on_friends_list_cellClicked(int row, int column)
{
    // update the current User to whichever cell was clicked
    std::size_t currUserid = n.getId((ui->friends_list->item(row, column)->text()).toStdString());
    currUser = n.getUser(currUserid);

    // hide the suggested friends & show the add Friend button
    ui->suggested_friends_list->hide();
    ui->pushButton_addFriend->show();

    // show the profile label
    QString name = QString::fromStdString(currUser->getName());
    ui->profile_label->setText(name + "'s Profile");
    ui->profile_label->show();

    // show all the user's friends
    for (std::size_t i = 0; i < currUser->getFriends().size(); i++) {
        // add the friends to the QTableWidget
        ui->friends_list->insertRow(ui->friends_list->rowCount());
        User* currfriends = n.getUser(currUser->getFriends()[i]);
        QString currfriendname = QString::fromStdString(currfriends->getName());
        ui->friends_list->setItem(i, 0, new QTableWidgetItem(currfriendname));
    }
    ui->friends_list->show();

    // show the user's 5 most recent posts
    QString post;
    std::vector<Post*> vector = currUser->getMessages();
    if (vector.size() < 5) {
        for (std::size_t i = 0; i < vector.size(); i++) {
            ui->posts->insertRow(ui->posts->rowCount());
            post = QString::fromStdString(vector[i]->getMessage());
            ui->posts->setItem(i, 1, new QTableWidgetItem(post));
        }
    }
    else {
        for (std::size_t i = 0; i < 5; i++) {
            // add the user's posts to the QTableWidget
            ui->posts->insertRow(ui->posts->rowCount());
            post = QString::fromStdString(vector[i]->getMessage());
            ui->posts->setItem(i, 1, new QTableWidgetItem(post));
        }
    }
    ui->posts->show();

    // show the button to navigate a user back to their profile page
    ui->pushButton_back->show();
}

void SocialNetworkWindow::on_suggested_friends_list_cellClicked(int row, int column)
{
    // add the person as a friend when the cell is clicked
    std::size_t id = n.getId((ui->suggested_friends_list->item(row, column)->text()).toStdString());
    currUser->addFriend(id);
}


void SocialNetworkWindow::on_posts_cellClicked(int row, int column)
{
    // update the current Post
    currPost = currUser->getMessages()[row];
    // show the users who reacted 
    std::string laughstring;
    std::string lovestring;
    std::string livestring;
    std::string likestring;
    std::vector<Post*> postvector = currUser->getMessages();

    // adjust the button names to fit the post
    laughstring = std::to_string(postvector[row]->getLaughs().size()) + " 🤣";
    ui->laugh->setText(QString::fromStdString(laughstring));

    lovestring = std::to_string(postvector[row]->getLoves().size()) + " 💗";
    ui->loves->setText(QString::fromStdString(lovestring));

    livestring = std::to_string(postvector[row]->getLives().size()) + " 👍";
    ui->lives->setText(QString::fromStdString(livestring));

    likestring = std::to_string(postvector[row]->getLikes().size()) + " 😀";
    ui->likes->setText(QString::fromStdString(likestring));

    // show all the needed items
    ui->laugh->show();
    ui->lives->show();
    ui->loves->show();
    ui->likes->show();
}


void SocialNetworkWindow::on_laugh_clicked()
{
    QString laughs_string;

    for(int i = 0; i < currPost->getLaughs().size(); i++) {
        laughs_string = laughs_string + QString::fromStdString(currPost->getLaughs()[i] + "\n");
    }

    ui->label_3->setText(laughs_string);
    ui->label_3->show();
}


void SocialNetworkWindow::on_likes_clicked()
{
    QString likes_string;

    for(int i = 0; i < currPost->getLikes().size(); i++) {
        likes_string = likes_string + QString::fromStdString(currPost->getLikes()[i] + "\n");
    }

    ui->label_3->setText(likes_string);
    ui->label_3->show();
}


void SocialNetworkWindow::on_lives_clicked()
{
    QString lives_string;

    for(int i = 0; i < currPost->getLives().size(); i++) {
        lives_string = lives_string + QString::fromStdString(currPost->getLives()[i] + "\n");
    }

    ui->label_3->setText(lives_string);
    ui->label_3->show();
}


void SocialNetworkWindow::on_loves_clicked()
{
    QString loves_string;

    for(int i = 0; i < currPost->getLoves().size(); i++) {
        loves_string = loves_string + QString::fromStdString(currPost->getLoves()[i] + "\n");
    }

    ui->label_3->setText(loves_string);
    ui->label_3->show();
}

