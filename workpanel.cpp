#include<workpanel.h>
#include<QFormLayout>
#include<user.h>
#include<QInputDialog>
#include<QMessageBox>




workPanel::workPanel(userContainer& uc, user* u, QWidget* parent):
    QWidget(parent), userList(uc), currentUser(u){
  kanjiList.fileImport();
  wordList.fileImport();
  createGui();

}


void workPanel:: createGui(){
    layout=new QGridLayout();
    setLayout(layout);
    searchResults=new QListWidget(this);
    searchResults->setMinimumWidth(210);
    searchResults->setMinimumHeight(300);
    searchResults->adjustSize();
    infoL=new QLabel;
    infoL->setText("");
    infoL->setMinimumWidth(200);
    info=new QScrollArea;
    info->setWidget(infoL);
    info->setMinimumWidth(210);
    info->setMinimumHeight(200);
    searchKeyword=new QLineEdit;
    searchKeyword->setPlaceholderText("Enter keyword");
    JP=new QRadioButton;
    JP->setText("Japanese - English");
    JP->setChecked(true);
    EN=new QRadioButton;
    EN->setText("English - Japanese");
    type=new QComboBox;
    type->setWindowTitle("Select type");
    type->addItem("Word");
    type->addItem("Kanji");
    advanced=new QLabel;
    advanced->setText("Advanced search options:");
    advanced->setVisible(false);
    radical=new QRadioButton;
    radical->setText("Search by radical");
    radical->setVisible(false);
    sound=new QRadioButton;
    sound->setText("Search by reading");
    sound->setVisible(false);
    cancel=new QPushButton;
    cancel->setText("Reset");
    startSearch=new QPushButton;
    startSearch->setText("Search");
    JLPT=new QComboBox;
    JLPT->addItem("All");
    JLPT->addItem("N1");
    JLPT->addItem("N2");
    JLPT->addItem("N3");
    JLPT->addItem("N4");
    JLPT->addItem("N5");
    edit=new QPushButton;
    edit->setText("Edit");
    addWord=new QPushButton;
    addWord->setText("Add new word");
    addKanji=new QPushButton;
    addKanji->setText("Add new kanji");
    userAdm=new QPushButton;
    userAdm->setText("Open user administration panel");
    delWord=new QPushButton;
    delWord->setText("Delete");
    layout->addWidget(searchResults, 0,3,7,1);
    layout->addWidget(info,0,0);
    layout->addWidget(searchKeyword,2,0);
    layout->addWidget(type, 2,1);
    layout->addWidget(JP,3,0);
    layout->addWidget(EN, 3,1);
    layout->addWidget(advanced,4,0);
    layout->addWidget(radical,5,0);
    layout->addWidget(sound,5,1);
    startSearch->setFocus();

    student* sp=dynamic_cast<student*>(currentUser);
    if(sp){
        layout->addWidget(startSearch, 6,0);
        layout->addWidget(cancel,6,1);
    }
    else{

        layout->addWidget(JLPT, 6,0);
        layout->addWidget(startSearch,7,0);
        layout->addWidget(cancel, 7,1);
        layout->addWidget(addKanji,9,1);
        layout->addWidget(addWord, 9,0);
        layout->addWidget(userAdm,9,2);
        layout->addWidget(edit, 8,0);
        layout->addWidget(delWord, 8,1);

    }
    connect(startSearch, SIGNAL(clicked()), this , SLOT(search()));
    connect(delWord, SIGNAL(clicked()), this, SLOT(deleteSelected()));
    connect(addWord, SIGNAL(clicked()), this, SLOT(addWPanel()));
    connect(addKanji, SIGNAL(clicked()), this, SLOT(addKPanel()));
    connect(edit, SIGNAL(clicked()), this, SLOT(editPanel()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(clear()));
    connect(userAdm, SIGNAL(clicked()), this, SLOT(userAdminPanel()));
    connect(searchResults,SIGNAL(currentTextChanged(QString)),this,SLOT(showInfo()));
    connect(type,SIGNAL(currentIndexChanged(QString)),this,SLOT(showButtons()));

}

void workPanel::showButtons(){
    if(type->currentText() == "Word"){
        radical->setVisible(false);
        sound->setVisible(false);
        JP->setVisible(true);
        JP->setChecked(true);
        EN->setVisible(true);
        advanced->setVisible(false);
    }
    if(type->currentText() == "Kanji"){
        radical->setVisible(true);
        sound->setVisible(true);
        JP->setVisible(false);
        EN->setVisible(false);
        advanced->setVisible(true);
    }
}

void workPanel::clear(){
    searchKeyword->clear();
    searchResults->clear();
    infoL->clear();
    startSearch->setFocus();
    radical->setChecked(false);
    sound->setChecked(false);
    JP->setChecked(true);
}

void workPanel::showInfo(){
    if(searchResults->currentRow() > 0){
        QString data=(searchResults->currentItem()->data(1).toString());
        infoL->setText(data);
        infoL->adjustSize();
    }
}

void workPanel::search(){
    unsigned int lev;
    bool totalAccess=false;
    std::list<word*> resW;
    std::list<kanji*> resK;
    //QListWidgetItem* row=new QListWidgetItem;
    student* sp=dynamic_cast<student*>(currentUser);
    if(sp){
        lev=sp->getLevel();
    } //accesso limitato dal livello dello studente
    else{
        totalAccess=true;
        lev=JLPT->currentIndex();
    }
    if(type->currentText() == "Word"){ //voglio cercare tra le parole
        if(JP->isChecked() && searchKeyword->text() != ""){
            resW=wordList.searchJP(searchKeyword->text());
        }
        if(EN->isChecked() && searchKeyword->text() != ""){
            resW=wordList.searchM(searchKeyword->text());
        }
        if(!dynamic_cast<student*>(currentUser) && (JLPT->currentIndex() != 0) && searchKeyword->text() == ""){
            resW=wordList.searchLevel(JLPT->currentIndex());
        }
        for(std::list<word*>::const_iterator it=resW.begin(); it != resW.end(); ++it){
            QListWidgetItem* row=new QListWidgetItem;
            if((totalAccess && (lev != 0) && ((*it)->getLevel() == lev)) || (totalAccess && (lev == 0)) || (!totalAccess && ((*it)->getLevel() >= lev))){
                row->setText((*it)->getKana());
                QString info=(*it)->getInfo();
                row->setData(1,info);
                searchResults->addItem(row);
                searchResults->setCurrentItem(row);
            }
        }
    }
    if(type->currentText() == "Kanji"){
        if(radical->isChecked() && searchKeyword->text() != ""){
            resK=kanjiList.searchRadical((searchKeyword->text()));
        }
        if(sound->isChecked() && searchKeyword->text() != ""){
            resK=kanjiList.searchSound((searchKeyword->text()));
        } 
        else{
            if(!dynamic_cast<student*>(currentUser) && (JLPT->currentIndex() != 0) && searchKeyword->text() == ""){
                resK=kanjiList.search(JLPT->currentIndex());
            }
            else{
                resK=kanjiList.searchCharacter((searchKeyword->text()));
            }
        }
        for(std::list<kanji*>::const_iterator it=resK.begin(); it != resK.end(); ++it){
            QListWidgetItem* row=new QListWidgetItem;
             if((totalAccess && (lev != 0) && ((*it)->getLevel() == lev)) || (totalAccess && (lev == 0)) || (!totalAccess && ((*it)->getLevel() >= lev))){
                row->setText((*it)->getCharacter());
                QString info=(*it)->getInfo();
                row->setData(1,info);
                searchResults->addItem(row);
                searchResults->setCurrentItem(row);
            }
        }
    }
    resK.clear();
    resW.clear();

}

void workPanel::editPanel(){
    if(searchResults->currentRow() != -1){
        QString type=searchResults->currentItem()->data(1).toString();
        if (type.contains("-KANJI-")){
            kanji* kp=kanjiList.getPointer(type);
            if(kp != 0){
                kanjiEdit* kEdit;
                kEdit=new kanjiEdit(kp,kanjiList,this);
                kEdit->show();
                kEdit->exec();
            }
        }
        else{
            word* wp=wordList.getPointer(type);
            if(wp != 0){
                wordEdit* wAdd=new wordEdit(wp,wordList,this);
                wAdd->show();
                wAdd->exec();
            }
        }
    }
    else{
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("Please select an item.");
        error.show();
        error.exec();
    }
}


void workPanel::addKPanel(){
    kanji* kp=0;
    kanjiEdit* kAdd=new kanjiEdit(kp,kanjiList,this);
    kAdd->show();
    kAdd->exec();


}

void workPanel::addWPanel(){
    word* wp=0;
    wordEdit* wAdd=new wordEdit(wp,wordList,this);
    wAdd->show();
    wAdd->exec();
}


void workPanel::deleteSelected(){
    if(searchResults->currentRow() != -1){
        QString type=searchResults->currentItem()->data(1).toString();
        if (type.contains("-KANJI-")){
            kanji* kp=kanjiList.getPointer(type);
            if(kp != 0 && kanjiList.removeKanji(kp->getCharacter())){
                QMessageBox success;
                success.setWindowTitle("Kanji deleted");
                success.setText("Kanji has been deleted.");
                success.show();
                success.exec();
                kanjiList.fileExport();
                clear();
            }
        }
        else{
            word* wp=wordList.getPointer(type);
            if(wp != 0 && wordList.removeWord(wp)){
                QMessageBox success;
                success.setWindowTitle("Word deleted");
                success.setText("Word has been deleted.");
                success.show();
                success.exec();
                wordList.fileExport();
                clear();
          }
        }
    }
    else{
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("Please select an item.");
        error.show();
        error.exec();
    }
}

void workPanel::userAdminPanel(){
    uSearch=new userSearchPanel(currentUser,userList,this);
    uSearch->show();
    uSearch->exec();
}


