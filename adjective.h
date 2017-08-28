#ifndef ADJECTIVE_H
#define ADJECTIVE_H
#include<word.h>

class adjective: public word{
private:
    bool naKeiyoushi;
    QString getLabel()const;
public:
    adjective(QString hk, QString r, QString k, unsigned int l, QString m,  bool nk): word(hk,r,k,l,m),naKeiyoushi(nk){}
    bool isNaKeiyoushi()const;
    bool operator==(const adjective&)const;
    virtual word* clone()const;
    virtual QString getInfo() const;
    virtual void exportWordData(QXmlStreamWriter&)const;
    void setType(bool);
};


#endif // ADJECTIVE_H

