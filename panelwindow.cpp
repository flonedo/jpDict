#include<panelwindow.h>
#include<QMessageBox>
#include<usereditpanel.h>

panelWindow::panelWindow(userContainer& uc, user* u, bool& r, QWidget* parent):
QMainWindow(parent), userList(uc), currentUser(u), reLog(r){
    setWindowTitle("Japanese dictionary");
    wPanel=new workPanel(userList, currentUser);
    setCentralWidget(wPanel);
    connect(wPanel,SIGNAL(reLogin()),this, SLOT(reLogin()));
    menu=new QMenuBar();
    file=new QMenu("File");
    logOut=new QAction("Log out");
    exit=new QAction("Exit");
    changePassword=new QAction("Account");
    file->addAction(changePassword);
    file->addSeparator();
    file->addAction(logOut);
    file->addSeparator();
    file->addAction(exit);
    menu->addMenu(file);
    help=new QMenu("Help");
    viewHelp=new QAction("Help");
    help->addAction(viewHelp);
    about=new QMenu("About");
    viewAbout=new QAction("About");
    about->addAction(viewAbout);
    menu->addMenu(help);
    menu->addMenu(about);
    setMenuBar(menu);
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));
    connect(logOut,SIGNAL(triggered()),this,SLOT(reLogin()));
    connect(viewAbout,SIGNAL(triggered()),this,SLOT(getAbout()));
    connect(viewHelp,SIGNAL(triggered()),this,SLOT(getHelp()));
    connect(changePassword, SIGNAL(triggered()),this,SLOT(setPassword()));
}


QString panelWindow::helpText="Welcome to Japanese & kanji dictionary!"
                              "\nFor students: search vocabulary and kanji in accordance to your JLPT level."
                              "\nFor teachers: manage vocabulary and watch your student's achievements."
                              "\nEasy administration panel to update student levels and manage vocabulary.";

QString panelWindow::aboutText="Created by Francesca Lonedo"
                           "\nBachelor's degree in Japan Studies, Università Ca' Foscari Venezia."
                           "\nCurrently Computer Science student at Università di Padova."
                           "\nProgrammazione ad Oggetti 2016-2017.";

void panelWindow::reLogin(){
    reLog=true;
    this->close();
}

void panelWindow::getAbout(){
    QMessageBox* about=new QMessageBox;
    about->setWindowTitle("About");
    about->setText(aboutText);
    about->show();
    about->exec();
}

void panelWindow::getHelp(){
    QMessageBox* Help=new QMessageBox;
    Help->setWindowTitle("Help");
    Help->setText(helpText);
    Help->show();
    Help->exec();
}

void panelWindow::setPassword(){
    userEditPanel* edituser=new userEditPanel(userList,currentUser,currentUser,this);
    edituser->show();
    edituser->exec();
}
