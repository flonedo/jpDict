#include <kanjicontainer.h>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>

QString kanjiContainer::label="KANJIDATA";

QString kanjiContainer::defaultFile="kanjidata.xml";

QString kanjiContainer::getLabel(){
    return label;
}

QString kanjiContainer::getDefaultFile(){
    return defaultFile;
}

bool kanjiContainer::isInContainer(kanji* k)const{
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        if(*k == **(it)){
            return true;
        }
    }
    return false;
}

kanji* kanjiContainer::searchKanji(kanji* k)const{
    if(k){
        for (std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
            if(*k == **(it)){
                return (*it)->clone();
            }
        }
    }
    return 0;
}

std::list<kanji*> kanjiContainer::searchCharacter(QString c)const{
    std::list<kanji*> res;
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        if(c == (*it)->getCharacter()){
            res.push_back((*it)->clone());
        }
    }
    return res;
}

std::list<kanji*> kanjiContainer::search(unsigned int l)const{
    std::list<kanji*> res;
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        if(l == (*it)->getLevel()){
            res.push_back((*it)->clone());
        }
    }
    return res;
}

std::list<kanji*> kanjiContainer::searchRadical(QString c)const{
    std::list<kanji*> res;
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        if(c == (*it)->getRadical()){
            res.push_back((*it)->clone());
        }
    }
    return res;
}

std::list<kanji*> kanjiContainer::searchSound(QString c)const{
    std::list<kanji*> res;
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        QString soundK=(*it)->getKunYomi();
        QString soundO=(*it)->getOnYomi();
        if(soundK.contains(c) || soundO.contains(c)){
            res.push_back((*it)->clone());
        }
    }
    return res;
}


bool kanjiContainer::add(kanji* k){
    if(k && !isInContainer(k)){
        kanjiList.push_back(k->clone());
        return true;
    }
    return false;
}


bool kanjiContainer::removeKanji(QString k){
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        if(k == (*it)->getCharacter()){
            delete *it;
            kanjiList.erase(it);
            return true;
        }
    }
    return 0;
}


void kanjiContainer::fileImport(){
    clean();
    QFile file(getDefaultFile());
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QXmlStreamReader in(&file);
        while(in.readNextStartElement()){
            if(in.name() == getLabel()){
                while(in.readNextStartElement()){
                    kanji* k=0;
                    QString character;
                    QString radical;
                    QString kun;
                    QString on;
                    unsigned int strokes;
                    unsigned int level;
                    if(in.name() == "KANJI"){
                        in.readNextStartElement();
                        if(in.name() == "CHARACTER"){
                            character=in.readElementText();
                        }
                        in.readNextStartElement();
                        if(in.name() == "RADICAL"){
                            radical=in.readElementText();
                        }
                        in.readNextStartElement();
                        if(in.name() == "LEVEL"){
                            level=in.readElementText().toInt();
                        }
                        in.readNextStartElement();
                        if(in.name() == "STROKES"){
                            strokes=in.readElementText().toInt();
                        }
                        in.readNextStartElement();
                        if(in.name() == "ONYOMI"){
                            on=in.readElementText();
                        }
                        in.readNextStartElement();
                        if(in.name() == "KUNYOMI"){
                            kun=in.readElementText();
                        }
                        k=new kanji(character, radical, level, strokes, on, kun);
                    }
                    if(k != 0){
                        add(k);
                        delete k;
                    }
                    in.skipCurrentElement();

                }
            }
        }
    }
    file.close();
}


void kanjiContainer::fileExport(){
    QFile file (getDefaultFile());
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter output (&file);
    output.setAutoFormatting(true);
    output.writeStartDocument();
    output.writeStartElement(getLabel());
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        (*it)->exportData(output);
    }
    output.writeEndElement();
    output.writeEndDocument();
    file.close();
}

void kanjiContainer:: clean(){
    for(std::list<kanji*>::iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        delete *it;
        kanjiList.erase(kanjiList.begin(),kanjiList.end());
    }
}

kanji* kanjiContainer::getPointer(QString& info)const{
    for(std::list<kanji*>::const_iterator it=kanjiList.begin(); it != kanjiList.end(); ++it){
        if(info == (*it)->getInfo()){
            return *it;
        }
    }
    return 0;
}
