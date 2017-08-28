#include <login.h>
#include <QLabel>
#include <QMessageBox>
#include<QVBoxLayout>

login::login(userContainer& uList, user** lUser, QWidget* parent):QDialog(parent), userList(uList), logUser(lUser){

createGui();

}



void login::createGui(){
    setWindowTitle("Japanese dictionary - Login");
    createFields();
    createButtons();
    connect(log, SIGNAL(clicked()), this, SLOT(check()));
}

void login::createFields(){
    layout=new QFormLayout(this);
    logUsername=new QLineEdit();
    logUsername->setPlaceholderText("Enter username");
    logPassword=new QLineEdit();
    logPassword->setPlaceholderText("Enter password");
    layout->addRow(new QLabel("Username"), logUsername);
    layout->addRow(new QLabel("Password"), logPassword);

}

void login:: createButtons(){
    log=new QPushButton();
    log->setText("LOG IN");
    log->setFocus();
    layout->addRow(log);

}


void login:: check(){
    *logUser=userList.search(logUsername->text().toStdString());
    if((*logUser) && ((*logUser)->getPassword() == logPassword->text().toStdString())){
            this->close();

    }
    else{
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("User not found. Please check your username and password before trying again.");
        error.show();
        error.exec();

    }
}

void login::clear(){
    logUsername->clear();
    logPassword->clear();
    logUsername->setFocus();
}



