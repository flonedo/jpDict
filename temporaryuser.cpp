
void student::setLevel(unsigned int l){
    level=l;
}

student* student::clone()const{
    return new student(*this);

}

void student::exportUserData(QXmlStreamWriter& out) const{
    user::exportUserData(out);
    out.writeTextElement("Livello JLPT: N", QString::number(level,10));
}

QString student::getLabel()const{
    return "STUDENTE";
}
