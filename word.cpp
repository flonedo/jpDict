#include<word.h>
#include <QStringList>


void word::addMeaning(QString m){
    meaning.append(',');
    meaning.append(m);
}

void word:: setKana(QString k){
    kanaWriting=k;
}

void word:: setRomaji(QString r){
    romajiWriting=r;
}
void word::setKanji(QString k){
    kanjiWriting=k;
}

void word::setLevel(unsigned int l){
    level=l;
}



void word::setMeaning(QString m){
    meaning=m;
}

QString word:: getInfo()const{
    QString info=getLabel();
    info.append("\n漢字: ");
    info.append(kanjiWriting);
    info.append("\n仮名: ");
    info.append(kanaWriting);
    info.append("\nRoumaji: ");
    info.append(romajiWriting);
    info.append("\nMeaning: ");
    info.append(getMeaning());
    info.append("\nJLPT level: N");
    info.append(QString::number(level,10));
    return info;
}

const QString& word:: getKana()const{
    return kanaWriting;
}

const QString& word:: getRomaji()const{
    return romajiWriting;
}

const QString& word:: getKanji()const{
    return kanjiWriting;
}



const QString& word::getMeaning()const{
    return meaning;
}

const unsigned int& word:: getLevel()const{
    return level;
}

bool word:: operator==(const word& w)const{
    return(kanaWriting == w.kanaWriting && kanjiWriting == w.kanjiWriting && romajiWriting == romajiWriting);
}


bool word:: operator!=(const word& w)const{
    return(kanaWriting != w.kanaWriting || kanjiWriting != w.kanjiWriting);
}

QString word::getLabel()const{
    return "WORD";
}

void word::exportData(QXmlStreamWriter& out)const{
    out.writeStartElement(getLabel());
    exportWordData(out);
    out.writeEndElement();
}

void word::exportWordData(QXmlStreamWriter& out)const{
    out.writeTextElement("KANA", kanaWriting);
    out.writeTextElement("ROMAJI", romajiWriting);
    out.writeTextElement("KANJI", kanjiWriting);
    out.writeTextElement("LEVEL", QString::number(level,10));
    out.writeTextElement("MEANING", getMeaning());
}
