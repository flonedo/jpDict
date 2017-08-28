#include <dictionary.h>
#include<QFile>
#include<QXmlStreamWriter>
#include<QXmlStreamReader>
#include<QStringList>
#include<adjective.h>
#include<verb.h>
#include<adverb.h>
#include<noun.h>


bool dictionary::isInContainer(word* w)const{
    for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
        if(*w == **it){
            return true;
        }
    }
    return false;
}

bool dictionary::addWord(word* w){
    if(w && !isInContainer(w)){
        wordList.push_back(w->clone());
        return true;
    }
    return false;
}



bool dictionary::removeWord(word* w){
    for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
        if(*w == **it){
            delete *it;
            wordList.erase(it);
            return true;
        }
    }
    return false;
}

std::list<word*> dictionary::searchJP(const QString& s) const{
    std::list<word*> L;
     for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
         if(s == (*it)->getKanji() || s == (*it)->getKana() || s == (*it)-> getRomaji()){
             L.push_back((*it)->clone());
         }
     }
     return L;
}

std::list<word*> dictionary::searchM(const QString& s) const{
    std::list<word*> L;
     for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
         if((*it)->getMeaning().contains(s)){
             L.push_back((*it)->clone());
         }
     }
     return L;
}

std::list<word*> dictionary::searchLevel(const unsigned int& l) const{
    std::list<word*> L;
     for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
         if((*it)->getLevel() == l){
             L.push_back((*it)->clone());
         }
     }
     return L;
}

std::list<word*> dictionary::searchKana(const QString& s) const{
    std::list<word*> L;
     for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
         if((*it)->getKana() == s){
             L.push_back((*it)->clone());
         }
     }
     return L;
}



std::list<word*> dictionary::searchRomaji(const QString& s) const{
    std::list<word*> L;
     for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
         if((*it)->getRomaji() == s){
             L.push_back((*it)->clone());
         }
     }
     return L;
}

std::list<word*> dictionary::searchKanji(const QString& s) const{
    std::list<word*> L;
     for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
         if((*it)->getKanji() == s){
             L.push_back((*it)->clone());
         }
     }
     return L;
}



int dictionary:: size()const{
    return wordList.size();
}

QString dictionary::getLabel(){
    return "DICTIONARY";
}

QString dictionary::getDefaultFile(){
    return "dictionarydata.xml";
}

void dictionary::fileExport(){
    QFile file (getDefaultFile());
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter output(&file);
    output.setAutoFormatting(true);
    output.writeStartDocument();
    output.writeStartElement(getLabel());
    for(std::list<word*>::const_iterator it=wordList.begin(); it != wordList.end(); ++it){
        (*it)->exportData(output);
    }
    output.writeEndElement();
    output.writeEndDocument();
    file.close();

}

void dictionary::fileImport(){
    clean();
    QFile file(getDefaultFile());
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QXmlStreamReader in(&file);
        while(in.readNextStartElement()){
            if(in.name() == getLabel()){
                while(in.readNextStartElement()){
                    QString className=in.name().toString();
                    word* w=0;
                    QString kana;
                    QString kanji;
                    QString romaji;
                    QString meaning;
                    bool b;
                    bool c;
                    unsigned int level;
                    in.readNextStartElement();
                    if(in.name() =="KANA"){
                        kana=in.readElementText();
                    }
                    in.readNextStartElement();
                    if(in.name() =="ROMAJI"){
                        romaji=in.readElementText();
                    }
                    in.readNextStartElement();
                    if(in.name() =="KANJI"){
                        kanji=in.readElementText();
                    }
                    in.readNextStartElement();
                    if(in.name() =="LEVEL"){
                        level=in.readElementText().toInt();
                    }
                    in.readNextStartElement();
                    if(in.name() =="MEANING"){
                        meaning=in.readElementText();
                    }
                    if(className == "ADJECTIVE"){
                        in.readNextStartElement();
                        if(in.name() =="NAKEYOSHI"){
                            b=in.readElementText().toInt();
                        }
                        w=new adjective(kana, romaji, kanji, level, meaning, b);
                    }
                    if(className == "ADVERB"){
                        in.readNextStartElement();
                        if(in.name() =="PARTICLE"){
                            b=in.readElementText().toInt();
                        }
                        w=new adverb(kana, romaji, kanji, level, meaning, b);
                    }
                    if(className == "NOUN"){
                        in.readNextStartElement();
                        if(in.name() =="FOREIGN"){
                            b=in.readElementText().toInt();
                        }
                        w=new noun(kana, romaji, kanji, level, meaning, b);
                    }
                    if(className == "VERB"){
                        in.readNextStartElement();
                        if(in.name() =="TRANSITIVE"){
                            b=in.readElementText().toInt();
                        }
                        in.readNextStartElement();
                        if(in.name() =="ICHIDAN"){
                            c=in.readElementText().toInt();
                        }
                        w=new verb(kana, romaji, kanji, level, meaning, b, c);
                    }
                    if(w != 0){
                        /*QStringList m=meaning.split(',');
                        for (int i=0; i < m.size(); ++i){
                            w->word::addMeaning(m.at(i));
                        }*/
                       // w->setMeaning(meaning);
                        addWord(w);
                        delete w;
                    }
                    in.skipCurrentElement();
                }
            }
        }
    }
    file.close();
}


void dictionary:: clean(){
    for(std::list<word*>::iterator it=wordList.begin(); it != wordList.end(); ++it){
        delete *it;
        wordList.erase(wordList.begin(),wordList.end());
    }
}

word* dictionary::getPointer(QString& info) const{
    for(std::list<word*>::const_iterator it=wordList.begin(); it!=wordList.end(); ++it){
        if(info == (*it)->getInfo()){
            return *it;
        }
    }
    return 0;
}
