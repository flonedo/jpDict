#include <kanji.h>

bool kanji:: operator==(const kanji& k)const{
    return character == k.character;
}

kanji* kanji::clone(){
    return new kanji(*this);
}

const QString& kanji:: getCharacter()const{
    return character;
}

const QString& kanji:: getOnYomi()const{
    return onYomi;
}

const QString& kanji:: getKunYomi()const{
    return kunYomi;
}

const QString& kanji:: getRadical()const{
    return radical;
}

const unsigned int& kanji:: getStrokeNumber()const{
    return strokeNumber;
}

QString kanji:: getInfo()const{
    QString info="-KANJI-\n";
    info.append("漢字: ");
    info.append(character);
    info.append("\n部首: ");
    info.append(radical);
    info.append("\n音読み: ");
    info.append(getOnYomi());
    info.append("\n総画: ");
    info.append(QString::number(strokeNumber,10));
    info.append("\nJLPT: N");
    info.append(QString::number(level,10));
    return info;
}


void kanji::addKunYomi(QString k){
    kunYomi.append(',');
    kunYomi.append(k);
}

void kanji::addOnYomi(QString o){
    onYomi.append(',');
    onYomi.append(o);
}

QString kanji::getLabel()const{
    return "KANJI";
}

const unsigned int& kanji::getLevel()const{
    return level;
}

void kanji::exportData(QXmlStreamWriter& out) const{
    out.writeStartElement(getLabel());
    out.writeTextElement("CHARACTER", character);
    out.writeTextElement("RADICAL", radical);
    out.writeTextElement("LEVEL",QString::number(level,10));
    out.writeTextElement("STROKES", QString::number(strokeNumber, 10));
    out.writeTextElement("ONYOMI", getOnYomi());
    out.writeTextElement("KUNYOMI", getKunYomi());
    out.writeEndElement();
}

void kanji::setCharacter(QString c){
    character=c;
}

void kanji::setRadical(QString c){
    radical=c;
}

void kanji::setStrokes(unsigned int i){
    strokeNumber=i;
}

void kanji::setLevel(unsigned int i){
    level=i;
}

void kanji::setKunYomi(QString s){
    kunYomi=s;
}

void kanji::setOnYomi(QString s){
    onYomi=s;
}
