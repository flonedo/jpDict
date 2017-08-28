#ifndef ADVERB_H
#define ADVERB_H
#include <word.h>


class adverb: public word{
private:
    bool particle;
    QString getLabel()const;
public:
    adverb(QString hk, QString r, QString k, unsigned int l, QString m,  bool p): word(hk,r,k,l,m), particle(p){}
    bool isParticle()const;
    bool operator==(const adverb&)const;
    virtual word* clone()const;
    virtual QString info()const;
    virtual void exportWordData(QXmlStreamWriter&)const;
    void setType(bool);
};


#endif // ADVERB_H
