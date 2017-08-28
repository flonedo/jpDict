#include <noun.h>

bool noun::isForeign()const{
    return foreign;
}

bool noun::operator==(const noun& w)const{
    return(word::operator==(w) && foreign == w.foreign);
}

word* noun::clone()const{
    return new noun(*this);
}

QString noun::info()const{
    QString info=word::getInfo();
    info.prepend("-NOU-\n");
    if(isForeign()){
        info.prepend("普通名詞(外語)");
    }
    else{
        info.prepend("普通名詞");
    }
    return info;
}

QString noun::getLabel()const{
    return "NOUN";
}

void noun::exportWordData(QXmlStreamWriter& out)const{
    word::exportWordData(out);
    out.writeTextElement("FOREIGN", QString::number(foreign));

}

void noun::setType(bool b){
    foreign=b;
}
