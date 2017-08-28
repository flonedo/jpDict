#ifndef KANJICONTAINER_H
#define KANJICONTAINER_H
#include <kanji.h>
#include <list>

class kanjiContainer{
private:
    std::list<kanji*> kanjiList;
    static QString label;
    static QString defaultFile;
    QString getLabel();
    QString getDefaultFile();
public:
    bool add(kanji*);
    //bool remove(kanji*);
    bool removeKanji(QString k);
    bool isInContainer(kanji*)const;
    kanji* searchKanji(kanji*)const;
    std::list<kanji*> search(unsigned int)const;
    std::list<kanji*> searchCharacter(QString)const;
    std::list<kanji*> searchRadical(QString)const;
    std::list<kanji*> searchSound(QString)const;
    kanji* getPointer(QString&)const;
    void fileImport();
    void fileExport();
    void clean();
};

#endif // KANJILIST_H
