#include<verb.h>

bool verb::isTransitive()const{
    return transitive;
}

bool verb::isIchidan()const{
    return ichidan;
}

bool verb::operator==(const verb& w)const{
    return(word::operator==(w) && transitive == w.transitive && ichidan == w.ichidan);
}

word* verb::clone() const{
    return new verb(*this);
}

QString verb::info()const{
    QString info=word::getInfo();
    info.prepend("-VER-\n");
    if(ichidan){
        info.prepend("一段　");
    }
    else{
        info.prepend("五段　");
    }
    if(transitive){
        info.prepend("他動詞");
    }
    else{
        info.prepend("自動詞　");
    }
    return info;
}

QString verb::getLabel()const{
    return "VERB";
}

void verb::exportWordData(QXmlStreamWriter& out)const{
    word::exportWordData(out);
    out.writeTextElement("TRANSITIVE", QString::number(transitive));
    out.writeTextElement("ICHIDAN", QString::number((ichidan)));

}

void verb::setTrans(bool b){
    transitive=b;
}

void verb::setType(bool b){
    ichidan=b;
}
