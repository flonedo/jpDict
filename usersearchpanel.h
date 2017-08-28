#ifndef USERSEARCHPANEL_H
#define USERSEARCHPANEL_H
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<userContainer.h>
#include<QFormLayout>
#include<QRadioButton>
#include<QComboBox>
#include<QListWidget>
#include<QDialog>
#include<usereditpanel.h>

class userSearchPanel: public QDialog{
    Q_OBJECT
private:
    user* currentUser;
    QFormLayout* layout;
    userContainer& userList;
    //userEditPanel* uEdit;
    void createGui();
    void createButtons();
    void createField();
    QPushButton* searchButton;
    QLineEdit* searchUsername;
    QPushButton* addButton;
    QLabel* jlpt;
    QRadioButton* onlyStudent;
    QComboBox* filterLevel;
    QRadioButton* onlyTeacher;
    QListWidget* results;
    QPushButton* reset;
    QLabel* unSearch;
    QLabel* fSearch;
    void showUser(user*);
public:
    userSearchPanel(user *cUser, userContainer &uc, QWidget *parent=Q_NULLPTR);
public slots:
    void findUser();
    //void editUser();
    //void clear();
    void selectedItem(/*QListWidgetItem**/);
    void clear();
    void newUser();

};

#endif // USERSEARCHPANEL_H
