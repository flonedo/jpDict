#include<adverb.h>


bool adverb:: isParticle()const{
    return particle;
}

bool adverb:: operator==(const adverb& w)const{
    return(word::operator==(w) && particle == w.particle);
}

word* adverb::clone()const{
    return new adverb(*this);
}

QString adverb::info()const{
    QString info=word::getInfo();
    info.prepend("-ADV-\n");
    if(isParticle()){
        info.prepend("助詞");
    }
    else{
        info.prepend("副詞");
    }
    return info;
}

QString adverb::getLabel()const{
    return "ADVERB";
}

void adverb::exportWordData(QXmlStreamWriter& out)const{
    word::exportWordData(out);
    out.writeTextElement("PARTICLE", QString::number(particle));

}

void adverb::setType(bool b){
    particle=b;
}
