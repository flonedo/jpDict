#include<usersearchpanel.h>
#include<list>
#include<QListWidgetItem>
#include<QMessageBox>



userSearchPanel::userSearchPanel(user *cUser, userContainer &uc, QWidget *parent):
    QDialog(parent), currentUser(cUser), userList(uc){
    createGui();
}

void userSearchPanel::createGui(){
    createField();
    createButtons();
    //searchButton->setFocus();
}

void userSearchPanel::createField(){
    layout=new QFormLayout(this);
    setWindowTitle("User administration");
    searchUsername=new QLineEdit();
    searchUsername->setPlaceholderText("Enter username");
    onlyStudent=new QRadioButton("Students");
    onlyTeacher=new QRadioButton("Teachers");
    filterLevel=new QComboBox();
    filterLevel->addItem("All");
    filterLevel->addItem("N1");
    filterLevel->addItem("N2");
    filterLevel->addItem("N3");
    filterLevel->addItem("N4");
    filterLevel->addItem("N5");
    filterLevel->hide();
    results=new QListWidget(this);
    layout->addRow(new QLabel("Search by username:"), searchUsername);
    layout->addRow(new QLabel("Get all"));
    layout->addRow(onlyStudent, onlyTeacher);
    jlpt=new QLabel;
    jlpt->setText("JLPT level");
    layout->addRow(jlpt,filterLevel);
    jlpt->setVisible(false);
    layout->addRow(results);
    connect(onlyStudent,SIGNAL(clicked()),filterLevel,SLOT(show()));
    connect(onlyTeacher,SIGNAL(clicked()),filterLevel,SLOT(hide()));
    connect(onlyStudent,SIGNAL(clicked()),jlpt,SLOT(show()));
    connect(onlyTeacher,SIGNAL(clicked()),jlpt,SLOT(hide()));
    connect(results, SIGNAL(doubleClicked(QModelIndex)),this,SLOT(selectedItem()));
}


void userSearchPanel::createButtons(){
    searchButton=new QPushButton();
    searchButton->setText("Search");
    reset=new QPushButton();
    reset->setText("Reset");
    addButton=new QPushButton();
    addButton->setText("Add new user");
    layout->addRow(searchButton,reset);
    if(dynamic_cast<admin*>(currentUser)){
        layout->addRow(addButton);
    }
    connect(addButton, SIGNAL(clicked()),this,SLOT(newUser()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(findUser()));
    connect(reset,SIGNAL(clicked()),this,SLOT(clear()));
}

void userSearchPanel::clear(){
    searchUsername->clear();
    results->clear();
}

void userSearchPanel::findUser(){
    user* found=0;
    QString uName=searchUsername->text();
    clear();
    if(uName != ""){
        found=userList.search(uName.toStdString());
        showUser(found);
    }
    else{
        if(onlyStudent->isChecked()){
            allStudents();
        }
        if(onlyTeacher->isChecked()){
            allTeachers();
        }
    }
}

void userSearchPanel::allStudents(){
    std::list<user*> L=userList.search(filterLevel->currentIndex());
    for(std::list<user*>::const_iterator it=L.begin(); it != L.end(); ++it){
        showUser(*it);
    }
}

void userSearchPanel::allTeachers(){
    std::list<user*> L=userList.searchTeachers();
    for(std::list<user*>::const_iterator it=L.begin(); it != L.end(); ++it){
        showUser(*it);
    }
}

void userSearchPanel::showUser(user* u){
    if(u != 0){
        QListWidgetItem* row=new QListWidgetItem;
        row->setText(QString::fromStdString(u->getUsername()));
        QString info=QString::fromStdString(u->getInfo());
        row->setData(1,info);
        results->addItem(row);

    }
    else{
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("User not found.");
        error.show();
        error.exec();
    }
}

void userSearchPanel::selectedItem(){
    if(dynamic_cast<teacher*>(currentUser)){
        QMessageBox info;
        info.setText(results->currentItem()->data(1).toString());
        info.setWindowTitle("User information");
        info.show();
        info.exec();
    }
    else{
        userEditPanel* uEdit;
        user* u=userList.search(results->currentItem()->text().toStdString());
        if(u != 0){
            uEdit=new userEditPanel(userList,currentUser,u,this);
            uEdit->show();
            uEdit->exec();
        }
    }
}

void userSearchPanel::newUser(){
    user* u=0;
    userEditPanel* uEdit;
    uEdit=new userEditPanel(userList,currentUser,u,this);
    uEdit->show();
    uEdit->exec();
}



