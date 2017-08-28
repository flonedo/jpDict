#ifndef VERB_H
#define VERB_H
#include <word.h>

class verb: public word{
private:
    bool transitive;
    bool ichidan;
    QString getLabel()const;
public:
    verb(QString hk, QString r, QString k, unsigned int l, QString m,  bool t, bool i): word(hk,r,k,l,m), transitive(t), ichidan(i){}
    bool isTransitive()const;
    bool isIchidan()const;
    bool operator==(const verb&)const;
    virtual word* clone()const;
    virtual QString info()const;
    virtual void exportWordData(QXmlStreamWriter&)const;
    void setTrans(bool);
    void setType(bool);
};

#endif // VERB_H
