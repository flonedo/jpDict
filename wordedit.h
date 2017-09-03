#ifndef WORDEDIT_H
#define WORDEDIT_H

#include<word.h>
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QCheckBox>
#include<QComboBox>
#include<QFormLayout>
#include<QRadioButton>
#include<QPushButton>
#include<dictionary.h>
#include<QButtonGroup>

class wordEdit: public QDialog{
    Q_OBJECT
private:
    word* W;
    dictionary& dict;
    QFormLayout* layout;
    QRadioButton* adj;
    QRadioButton* adv;
    QRadioButton* nou;
    QRadioButton* ver;
    QLineEdit* kana;
    QLineEdit* kanji;
    QLineEdit* romaji;
    QLineEdit* meaning;
    QPushButton* yes;
    QPushButton* no;
    QComboBox* level;
    QCheckBox* foreign;
    QRadioButton* nak;
    QRadioButton *ik;
    QCheckBox* trans;
    QCheckBox* ichi;
    QCheckBox* part;
    QLabel* choice;
    QButtonGroup* adjType;
    bool checkRequest();
    void createGui();
    void newWordGui();
    void editWordGui();
public:
    wordEdit(word* w, dictionary& dict, QWidget* parent=Q_NULLPTR);
public slots:
    //void createL();
    void edit();
    void clear();
};

#endif // WORDEDIT_H
