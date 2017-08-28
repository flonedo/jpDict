#ifndef KANJI_H
#define KANJI_H
#include<QString>
#include<QChar>
#include<vector>
#include <QXmlStreamWriter>



class kanji{
private:
    QString character;
    QString radical;
    unsigned int level;
    unsigned int strokeNumber;
    QString onYomi; //lettura sinogiapponese
    QString kunYomi; //lettura giapponese
    QString getLabel()const;
public:
    kanji(QString c="", QString r="",unsigned int l=5, unsigned int s=0,QString o="",QString k=""): character(c), radical(r), level(l), strokeNumber(s),onYomi(o),kunYomi(k){}
    bool operator==(const kanji&)const;
    kanji* clone();
    const QString& getCharacter()const;
    const QString& getOnYomi()const;
    const QString& getKunYomi()const;
    QString getInfo()const;
    const unsigned int& getLevel()const;
    const QString& getRadical()const;
    const unsigned int& getStrokeNumber()const;
    void addOnYomi(QString);
    void addKunYomi(QString);
    void setCharacter(QString);
    void setOnYomi(QString);
    void setKunYomi(QString);
    void setRadical(QString);
    void setLevel(unsigned int);
    void setStrokes(unsigned int);
    void exportData(QXmlStreamWriter&)const;

};

#endif // WORD_H
