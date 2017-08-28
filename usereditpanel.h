#ifndef USEREDITPANEL_H
#define USEREDITPANEL_H

#include<QFormLayout>
#include<QComboBox>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<userContainer.h>
#include<user.h>
#include<QDialog>
#include<QRadioButton>

class userEditPanel: public QDialog{
    Q_OBJECT
private:
    QPushButton* deleteButton;
    QPushButton* editButton;
    userContainer& userList;
    user* currentUser;
    QFormLayout* layout;
    QLabel* jlpt;
    user* toEdit;
    QLineEdit* uName;
    QLineEdit* pWord;
    QComboBox* level;
    QRadioButton* stud;
    QRadioButton* teach;
    QRadioButton* adm;
    void createGui();
    void createButtons();
    void createField();
public:
    userEditPanel(userContainer&, user*, user*, QWidget* parent=Q_NULLPTR);
public slots:
    void addUser();
    void deleteUser();

};


#endif // USEREDITPANEL_H
