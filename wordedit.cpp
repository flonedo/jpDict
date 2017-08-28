#include<wordedit.h>
#include<QString>
#include<QMessageBox>
#include<QLabel>
#include<adjective.h>
#include<noun.h>
#include<verb.h>
#include<adverb.h>


wordEdit::wordEdit(word* w, dictionary& d, QWidget* parent):
    QDialog(parent), W(w), dict(d){
    layout=new QFormLayout;
    setLayout(layout);
    if(W == 0){
        setWindowTitle("New word");
        choice=new QLabel;
        choice->setText("Select word type:");
        adj=new QRadioButton;
        adj->setText("Adjective");
        adv=new QRadioButton;
        adv->setText("Adverb");
        nou=new QRadioButton;
        nou->setText("Noun");
        ver=new QRadioButton;
        ver->setText("Verb");
        layout->addRow(choice);
        layout->addRow(adj,adv);
        layout->addRow(nou,ver);
        createGui();
        connect(adj, SIGNAL(clicked()),ik,SLOT(show()));
        connect(adj, SIGNAL(clicked()),nak,SLOT(show()));
        connect(adv, SIGNAL(clicked()),part,SLOT(show()));
        connect(nou, SIGNAL(clicked()),foreign,SLOT(show()));
        connect(ver, SIGNAL(clicked()),trans,SLOT(show()));
        connect(ver, SIGNAL(clicked()),ichi,SLOT(show()));
        connect(adj, SIGNAL(clicked()),part,SLOT(hide()));
        connect(adj, SIGNAL(clicked()),foreign,SLOT(hide()));
        connect(adj, SIGNAL(clicked()),trans,SLOT(hide()));
        connect(adj, SIGNAL(clicked()),ichi,SLOT(hide()));
        connect(adv, SIGNAL(clicked()),ik,SLOT(hide()));
        connect(adv, SIGNAL(clicked()),nak,SLOT(hide()));
        connect(adv, SIGNAL(clicked()),foreign,SLOT(hide()));
        connect(adv, SIGNAL(clicked()),trans,SLOT(hide()));
        connect(adv, SIGNAL(clicked()),ichi,SLOT(hide()));
        connect(nou, SIGNAL(clicked()),ik,SLOT(hide()));
        connect(nou, SIGNAL(clicked()),nak,SLOT(hide()));
        connect(nou, SIGNAL(clicked()),part,SLOT(hide()));
        connect(nou, SIGNAL(clicked()),trans,SLOT(hide()));
        connect(nou, SIGNAL(clicked()),ichi,SLOT(hide()));
        connect(ver, SIGNAL(clicked()),foreign,SLOT(hide()));
        connect(ver, SIGNAL(clicked()),ik,SLOT(hide()));
        connect(ver, SIGNAL(clicked()),nak,SLOT(hide()));
        connect(ver, SIGNAL(clicked()),part,SLOT(hide()));
    }
    else{
        setWindowTitle("Word edit");
        createGui();
        yes->setText("Edit");
        kana->setPlaceholderText(W->getKana());
        romaji->setPlaceholderText(W->getRomaji());
        kanji->setPlaceholderText(W->getKanji());
        meaning->setPlaceholderText(W->getMeaning());
    }
}


void wordEdit::createGui(){
    kana=new QLineEdit();
    kana->setPlaceholderText("例: ひらがな");
    romaji=new QLineEdit();
    romaji->setPlaceholderText("例: Romaji");
    kanji=new QLineEdit();
    kanji->setPlaceholderText("例: 漢字");
    level=new QComboBox;
    level->addItem("Select");
    level->addItem("N1");
    level->addItem("N2");
    level->addItem("N3");
    level->addItem("N4");
    level->addItem("N5");
    meaning=new QLineEdit();
    meaning->setPlaceholderText("例: Separate,meanings,with,comma");
    yes=new QPushButton();
    yes->setText("Add");
    no=new QPushButton();
    no->setText("Reset");
    foreign=new QCheckBox;
    foreign->setText("Foreign word");
    nak=new QRadioButton;
    nak->setText("Na-Keiyoushi");
    ik=new QRadioButton;
    ik->setText("I-Keiyoushi");
    adjType=new QButtonGroup;
    adjType->addButton(ik);
    adjType->addButton(nak);
    trans=new QCheckBox;
    trans->setText("Transitive");
    ichi=new QCheckBox;
    ichi->setText("Ichidan");
    part=new QCheckBox;
    part->setText("particle");
    layout->addRow(new QLabel("Hiragana/Katakana:"), kana);
    layout->addRow(new QLabel("Romaji:"),romaji);
    layout->addRow(new QLabel("Kanji:"),kanji);
    layout->addRow(new QLabel("JLPT"),level);
    layout->addRow(new QLabel("Meaning"),meaning);
    layout->addRow(nak,ik);
    layout->addRow(trans,ichi);
    layout->addRow(part);
    layout->addRow(foreign);
    layout->addRow(yes, no);
    foreign->hide();
    ik->hide();
    nak->hide();
    ichi->hide();
    trans->hide();
    part->hide();
    connect(yes,SIGNAL(clicked()),this,SLOT(edit()));
    connect(no,SIGNAL(clicked()),this, SLOT(clear()));
}

bool wordEdit:: checkRequest(){
    if(W == 0 && !adj->isChecked() && !adv->isChecked() && !nou->isChecked() && !ver->isChecked()){
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("Your must select a type.");
        error.show();
        error.exec();
        return false;
    }
    if((kana->text() == "") || (romaji->text() == "")){
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("Your word must have both kana writing and romaji writing.");
        error.show();
        error.exec();
        return false;
    }
    if(meaning->text() == ""){
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("Your word must have at least one meaning.");
        error.show();
        error.exec();
        return false;
    }
    return true;
}

void wordEdit:: edit(){
    if(W != 0){
        if(kana->text() !=""){
            W->setKana(kana->text());
        }
        if(romaji->text() !=""){
            W->setRomaji(romaji->text());
        }
        if(kanji->text() !=""){
            W->setKanji(kanji->text());
        }
        if(meaning->text() !=""){
            W->setMeaning(meaning->text());
        }
        if(level->currentIndex() !=0){
            W->setLevel(level->currentIndex());
        }
        dict.fileExport();
        QMessageBox success;
        success.setWindowTitle("Word edited");
        success.setText("Word has been edited.");
        success.show();
        success.exec();
        this->close();
    }
    else{
        if(checkRequest()){
            unsigned int l=1;
            if(level->currentIndex() != 0){
                l=level->currentIndex();
            }
            if(adj->isChecked()){
                W=new adjective(kana->text(),romaji->text(),kanji->text(),l,meaning->text(), nak->isChecked());
            }
            if(adv->isChecked()){
                W=new adverb(kana->text(),romaji->text(),kanji->text(),l,meaning->text(), part->isChecked());
            }
            if(nou->isChecked()){
                W=new noun(kana->text(),romaji->text(),kanji->text(),l,meaning->text(),foreign->isChecked());
            }
            if(ver->isChecked()){
                W=new verb(kana->text(),romaji->text(),kanji->text(),l,meaning->text(),trans->isChecked(),ichi->isChecked());
            }
            dict.addWord(W);
            dict.fileExport();
            QMessageBox success;
            success.setWindowTitle("New word added");
            success.setText("Word has been added to dictionay.");
            success.show();
            success.exec();
            this->close();
        }

    }
}

void wordEdit:: clear(){
    kana->clear();
    romaji->clear();
    kanji->clear();
    meaning->clear();
}


