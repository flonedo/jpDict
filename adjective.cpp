#include <adjective.h>

bool adjective:: isNaKeiyoushi()const{
    return naKeiyoushi;
}

bool adjective:: operator==(const adjective& w)const{
    return(word::operator==(w), naKeiyoushi == w.naKeiyoushi);
}

word* adjective::clone()const{
    return new adjective(*this);
}

QString adjective::getInfo()const{
    QString info=word::getInfo();
    info.prepend("-ADJ-\n");
    if(naKeiyoushi){
        info.prepend("な形容詞 ");
    }
    else{
        info.prepend("い形容詞 ");
    }
    return info;

}

QString adjective::getLabel()const{
    return "ADJECTIVE";
}

void adjective::exportWordData(QXmlStreamWriter& out) const{
    word::exportWordData(out);
    out.writeTextElement("NAKEYOSHI", QString::number(naKeiyoushi,10));
}

void adjective:: setType(bool b){
    naKeiyoushi=b;
}
