#ifndef WORKPANEL_H
#define WORKPANEL_H

#include<QLabel>
#include<QGridLayout>
#include<QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QListWidget>
#include<QRadioButton>
#include<kanjicontainer.h>
#include<userContainer.h>
#include<dictionary.h>
#include<QScrollArea>
#include<QComboBox>
#include<QCheckBox>
#include<QWidget>
#include<usereditpanel.h>
#include<usersearchpanel.h>
#include<kanjiedit.h>
#include<wordedit.h>


class workPanel: public QWidget{
Q_OBJECT

public:
    workPanel(userContainer& uc, user* u, QWidget* parent=Q_NULLPTR);
private:
    bool reLogin;
    userContainer& userList;
    kanjiContainer kanjiList;
    dictionary wordList;
    userEditPanel* uEdit;
    userSearchPanel* uSearch;
    user* currentUser;
    QGridLayout* layout;
    QListWidget* searchResults;
    QLabel* infoL;
    QScrollArea* info;
    QPushButton* startSearch;
    QLineEdit* searchKeyword;
    QRadioButton* JP;
    QRadioButton* EN;
    QComboBox* type;
    QComboBox* JLPT;
    QRadioButton* radical;
    QRadioButton* sound;
    QLabel* advanced;
    QPushButton* cancel;
    QPushButton* edit;
    QPushButton* addKanji;
    QPushButton* addWord;
    QPushButton* userAdm;
    QPushButton* delWord;
    void createGui();
private slots:
    void addKPanel();
    void addWPanel();
    void editPanel();
    void userAdminPanel();
    void deleteSelected();
    void showInfo();
    void clear();
    void search();
    void showButtons();
};

#endif // WORKPANEL_H
