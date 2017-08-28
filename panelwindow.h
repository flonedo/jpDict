#ifndef PANELWINDOW_H
#define PANELWINDOW_H

#include<QMainWindow>
#include<QMenuBar>
#include<QString>
#include<QMenu>
#include<userContainer.h>
#include<workpanel.h>

class panelWindow: public QMainWindow{
    Q_OBJECT
public:
    panelWindow(userContainer& uc, user* u, bool& r, QWidget*parent=Q_NULLPTR);
private:
    userContainer& userList;
    user* currentUser;
    bool& reLog;
    workPanel* wPanel;
    QMenuBar* menu;
    QMenu* help;
    QMenu* about;
    QMenu* file;
    QAction* changePassword;
    QAction* viewHelp;
    QAction* viewAbout;
    QAction* exit;
    QAction* logOut;
    static QString helpText;
    static QString aboutText;
public slots:
    void reLogin();
    void getHelp();
    void getAbout();
    void setPassword();

};


#endif // PANELWINDOW_H
