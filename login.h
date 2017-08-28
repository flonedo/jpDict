#ifndef LOGIN_H
#define LOGIN_H
#include <userContainer.h>
#include <user.h>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include<QDialog>


class login: public QDialog{

Q_OBJECT

private:
    const userContainer& userList;
    user** logUser;
    void createGui();
    void createButtons();
    void createFields();
    QLineEdit* logUsername;
    QLineEdit* logPassword;
    QFormLayout* layout;
    QPushButton* log;
private slots:
    void check();
public:
    login(userContainer& uList, user**lUser, QWidget* parent=Q_NULLPTR);



public slots:
    void clear();
};


#endif // LOGIN_H
