#include<kanjiedit.h>
#include<QMessageBox>
#include<QLabel>

kanjiEdit::kanjiEdit(kanji* k, kanjiContainer& kl, QWidget* parent):
    QDialog(parent), K(k), kanjiList(kl){
    createGui();
    if(K == 0){
        setWindowTitle("New kanji");
    }
    else{
        setWindowTitle("Kanji edit");
        character->setPlaceholderText(K->getCharacter());
        onyomi->setPlaceholderText(K->getOnYomi());
        kunyomi->setPlaceholderText(K->getKunYomi());
        strokes->setPlaceholderText(QString::number(K->getStrokeNumber()));
        radical->setPlaceholderText(K->getRadical());

    }
}


void kanjiEdit:: createGui(){
    createField();
    createButtons();
}

void kanjiEdit:: createField(){
    layout=new QFormLayout(this);
    setLayout(layout);
    character=new QLineEdit();
    character->setPlaceholderText("例: Enter character");
    onyomi=new QLineEdit();
    onyomi->setPlaceholderText("例: Separate,readings,with,comma");
    kunyomi=new QLineEdit();
    kunyomi->setPlaceholderText("例: Separate,readings,with,comma");
    level=new QComboBox;
    level->addItem("Select");
    level->addItem("N1");
    level->addItem("N2");
    level->addItem("N3");
    level->addItem("N4");
    level->addItem("N5");
    strokes=new QLineEdit();
    strokes->setPlaceholderText("例: Enter stroke number");
    radical=new QLineEdit();
    radical->setPlaceholderText("例: Enter radical");
    radical->setMaxLength(1);
    QValidator* v=new QIntValidator(1,100);
    character->setMaxLength(1);
    strokes->setValidator(v);
    layout->addRow(new QLabel("Character:"), character);
    layout->addRow(new QLabel("On'yomi:"),onyomi);
    layout->addRow(new QLabel("Kun'yomi:"),kunyomi);
    layout->addRow(new QLabel("JLPT:"),level);
    layout->addRow(new QLabel("Stroke number:"),strokes);
    layout->addRow(new QLabel("Radical:"),radical);

}

void kanjiEdit:: createButtons(){
    yes=new QPushButton();
    if(K != 0){
        yes->setText("Edit");
    }
    else{
        yes->setText("Add");
    }
    no=new QPushButton();
    no->setText("Reset");
    layout->addRow(yes, no);
    connect(no, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(yes, SIGNAL(clicked()), this, SLOT(edit()));
}

bool kanjiEdit:: checkRequest(){
    if(character->text() == ""){
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("You must enter a character.");
        error.show();
        error.exec();
        return false;
    }
    if(level->currentText() == "Select"){
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("You must select a JLPT level");
        error.show();
        error.exec();
        return false;
    }
    return true;
}

void kanjiEdit:: edit(){
    if(K != 0){
        if(character->text() != ""){
            K->setCharacter(character->text());
        }
        if(onyomi->text() != ""){
            K->setOnYomi(onyomi->text());
        }
        if(kunyomi->text() != ""){
            K->setKunYomi(kunyomi->text());
        }
        if(strokes->text() != ""){
        K->setStrokes(strokes->text().toInt());
        }
        if(radical->text() != ""){
            K->setRadical(radical->text());
        }
        if(level->currentIndex() != 0){
            K->setLevel(level->currentIndex());
        }
        QMessageBox success;
        success.setWindowTitle("Kanji edited.");
        success.setText("Kanji has been edited.");
        success.show();
        success.exec();
        kanjiList.fileExport();
        this->close();
    }
    else{
        unsigned int l=1;
        if(level->currentIndex() != 0){
            l=level->currentIndex();
        }
        K=new kanji(character->text(),radical->text(),l,strokes->text().toInt(), onyomi->text(),kunyomi->text());
        if(kanjiList.add(K)){ //da controllare
            QMessageBox success;
            success.setWindowTitle("Kanji added.");
            success.setText("Kanji has been added.");
            success.show();
            success.exec();
            kanjiList.fileExport();
            this->close();
        }
    }

}

void kanjiEdit:: cancel(){
    character->clear();
    kunyomi->clear();
    onyomi->clear();
    radical->clear();
    level->clear();
    strokes->clear();
}

