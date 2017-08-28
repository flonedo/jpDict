#ifndef WORD_H
#define WORD_H
#include<QString>
#include<vector>
#include <QChar>
#include <QXmlStreamWriter>



class word{
private:
    QString kanaWriting;
    QString romajiWriting;
    QString kanjiWriting;
    unsigned int level;
    QString meaning;
    virtual QString getLabel()const=0;
public:
    word(QString hk="", QString r="", QString k="", unsigned int l=5,QString m=""):kanaWriting(hk), romajiWriting(r), kanjiWriting(k), level(l), meaning(m){}
    void addMeaning(QString);
    void setKana(QString);
    void setRomaji(QString);
    void setKanji(QString);
    void setLevel(unsigned int);
    void setMeaning(QString);
    virtual ~word(){}
    virtual word* clone()const=0;
    virtual QString getInfo()const;
    const QString& getKana()const; //getter della scrittura kana
    const QString& getRomaji()const; //getter romaji
    const QString& getKanji()const; //getter kanji
    const QString& getMeaning()const; //restituisce una Qstring contenente i significati
    const unsigned int& getLevel()const; //getter livello
    bool operator==(const word&)const;
    bool operator!=(const word&)const;
    void exportData(QXmlStreamWriter&)const;
    virtual void exportWordData(QXmlStreamWriter&)const;
};






#endif // WORD_H
