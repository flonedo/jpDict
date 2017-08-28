#ifndef KANJIEDIT_H
#define KANJIEDIT_H
#include<kanji.h>
#include<QDialog>
#include<word.h>
#include<QFormLayout>
#include<QLineEdit>
#include<QComboBox>
#include<QPushButton>
#include<kanjicontainer.h>

class kanjiEdit: public QDialog{
    Q_OBJECT
private:
    kanji* K;
    kanjiContainer& kanjiList;
    QFormLayout* layout;
    QPushButton* yes;
    QPushButton* no;
    QLineEdit* character;
    QLineEdit* onyomi;
    QLineEdit* kunyomi;
    QComboBox* level;
    QLineEdit* strokes;
    QLineEdit* radical;
    void createGui();
    void createField();
    void createButtons();
    bool checkRequest();
public:
    kanjiEdit(kanji* k, kanjiContainer& kl, QWidget* parent=Q_NULLPTR);
public slots:
    void cancel();
    void edit();
};

#endif // KANJIEDIT_H
