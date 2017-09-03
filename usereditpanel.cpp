#include<usereditpanel.h>
#include<QMessageBox>

userEditPanel::userEditPanel(userContainer& uList, user* cUser, user* eUser, QWidget* parent):
    QDialog(parent), currentUser(cUser), toEdit(eUser), userList(uList){
    createGui();

}

void userEditPanel::createGui(){

    createField();
    createButtons();
}

void userEditPanel::createButtons(){
    editButton=new QPushButton;
    if(toEdit != 0){
        editButton->setText("Edit user");
        deleteButton=new QPushButton;
        deleteButton->setText("Delete user");
        layout->addRow(editButton,deleteButton);
        connect(deleteButton,SIGNAL(clicked()), this, SLOT(deleteUser()));
    }
    else{
        editButton->setText("Add user");
        layout->addRow(editButton);
    }
    connect(editButton,SIGNAL(clicked()), this, SLOT(addUser()));

}

void userEditPanel::createField(){
    layout=new QFormLayout(this);
    setWindowTitle("Edit");
    uName=new QLineEdit;
    pWord=new QLineEdit;
    pWord->setEchoMode(QLineEdit::Password);
    level=new QComboBox;
    level->addItem("Select");
    level->addItem("N1");
    level->addItem("N2");
    level->addItem("N3");
    level->addItem("N4");
    level->addItem("N5");
    jlpt=new QLabel;
    jlpt->setText("JLPT");
    if(toEdit != 0){
        uName->setPlaceholderText(QString::fromStdString(toEdit->getUsername()));
        student* sp=dynamic_cast<student*>(toEdit);
        if(sp){
            layout->addRow(new QLabel("STUDENT"));
            if(dynamic_cast<admin*>(currentUser)){
                level->setVisible(true);
                jlpt->setVisible(true);
                level->setCurrentIndex(sp->getLevel());
            }
            else{
                level->setVisible(false);
                jlpt->setVisible(false);
            }
        }
        else{
            level->setVisible(false);
            jlpt->setVisible(false);
            if(dynamic_cast<admin*>(toEdit)){
                layout->addRow(new QLabel("ADMIN"));
            }
            if(dynamic_cast<teacher*>(toEdit)){
                layout->addRow(new QLabel("TEACHER"));
            }
        }
    }
    else{
        stud=new QRadioButton;
        stud->setText("Student");
        teach=new QRadioButton;
        teach->setText("Teacher");
        adm=new QRadioButton;
        adm->setText("Admin");
        uName->setPlaceholderText("Enter username");
        pWord->setPlaceholderText("Enter password");
        layout->addRow(stud);
        layout->addRow(teach);
        layout->addRow(adm);
        level->setVisible(false);
        jlpt->setVisible(false);
        connect(stud,SIGNAL(clicked()),level,SLOT(show()));
        connect(teach,SIGNAL(clicked()),level,SLOT(hide()));
        connect(adm,SIGNAL(clicked()),level,SLOT(hide()));
        connect(stud,SIGNAL(clicked()),jlpt,SLOT(show()));
        connect(teach,SIGNAL(clicked()),jlpt,SLOT(hide()));
        connect(adm,SIGNAL(clicked()),jlpt,SLOT(hide()));

    }
    layout->addRow(new QLabel("Username"),uName);
    layout->addRow(new QLabel("Password"),pWord);
    layout->addRow(jlpt,level);




}


void userEditPanel::addUser(){
    bool acceptable=true;
    if(toEdit != 0){
        bool alreadyTaken=userList.isInContainer(uName->text().toStdString());
        if(uName->text().toStdString() != "" && ((!alreadyTaken) || uName->text().toStdString() == toEdit->getUsername()) ){
            toEdit->setUsername(uName->text().toStdString());
        }
        else if(alreadyTaken){
            acceptable=false;
            QMessageBox error;
            error.setWindowTitle("Error");
            error.setText("Username not available.");
            error.show();
            error.exec();
        }
        if(acceptable && pWord->text().toStdString() != ""){
        toEdit->setPassword(pWord->text().toStdString());
        }
        if(acceptable && dynamic_cast<student*>(toEdit)){
            student* sp=dynamic_cast<student*>(toEdit);
            if(level->currentIndex() != 0){
                sp->setLevel(level->currentIndex());
            }
        }

        if(acceptable){
            userList.fileExport();
            QMessageBox success;
            success.setWindowTitle("User edited");
            success.setText("User has been edited.");
            success.show();
            success.exec();
            userList.fileExport();
            this->close();
        }
}
    else{
        if((pWord->text().toStdString() == "") || (uName->text().toStdString() == "")){
            QMessageBox error;
            error.setWindowTitle("Error");
            error.setText("Please enter a value for username and password.");
            error.show();
            error.exec();
        }
        else{
            if(stud->isChecked()){
                unsigned int l=5;
                if(level->currentIndex() != 0){
                    l=level->currentIndex();
                }
                toEdit=new student(uName->text().toStdString(), pWord->text().toStdString(),l);
            }
            if(adm->isChecked()){
                toEdit=new admin(uName->text().toStdString(),pWord->text().toStdString());
            }
            if(teach->isChecked())
                toEdit=new teacher(uName->text().toStdString(), pWord->text().toStdString());
            }
            if(userList.addUser(toEdit)){
                QMessageBox success;
                success.setWindowTitle("User added");
                success.setText("User has been added.");
                success.show();
                success.exec();
                userList.fileExport();
                this->close();
            }
            else{
                QMessageBox error;
                error.setWindowTitle("Error");
                error.setText("Username not available. Please try a new one.");
                error.show();
                error.exec();
            }
      }
}

void userEditPanel::deleteUser(){
    if(toEdit != 0 && toEdit != currentUser){
        if(userList.removeUser(toEdit->getUsername())){
            userList.fileExport();
            QMessageBox success;
            success.setWindowTitle("User deleted");
            success.setText("User has been deleted.");
            success.show();
            success.exec();
            toEdit=0;
            this->close();
        }
    }
    else{
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("User cannot be deleted.");
        error.show();
        error.exec();
    }
}




