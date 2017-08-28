#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <list>
#include <word.h>

class dictionary{
private:
    std::list<word*> wordList;
    static QString getLabel();
    static QString getDefaultFile();
public:
    bool addWord(word*);
    bool removeWord(word*);
    bool isInContainer(word*)const; //cerca se una parola è presente nella lista
    std::list<word*> searchJP(const QString&)const; //restituisce tutte le parole giapponesi con almeno una scrittura corrispondente a quella cercata
    std::list<word*> searchM(const QString&)const; //restituisce tutte le parola con il significato cercato
    std::list<word*> searchLevel(const unsigned int&)const; //restituisce tutte le parole di un determinato livello
    std::list<word*> searchKana(const QString&)const; //cerca solo tra le scritture kana
    std::list<word*> searchRomaji(const QString&)const; //cerca solo tra le scritture in caratteri latini
    std::list<word*> searchKanji(const QString&)const; //cerca solo tra le scritture kanji
    std::list<word*> partialKanji(const QString&)const; //restituisce parole che contengono almeno uno dei kanji cercati
    word* getPointer(QString&)const;
    int size()const; //numero di parole nel dizionario
    void fileExport();
    void fileImport();
    void clean();
};

#endif // DICTIONARY_H
