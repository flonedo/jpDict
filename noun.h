#ifndef NOUN_H
#define NOUN_H
#include<word.h>

#endif // NOUN_H

class noun: public word{
private:
    bool foreign;
    QString getLabel()const;
public:
    noun(QString hk, QString r, QString k, unsigned int l, QString m,  bool f): word(hk,r,k,l,m), foreign(f){}
    bool isForeign()const;
    bool operator==(const noun&)const;
    virtual word* clone()const;
    virtual QString info()const;
    virtual void exportWordData(QXmlStreamWriter&)const;
    void setType(bool);
};

