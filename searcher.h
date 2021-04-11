#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QThread>
#include <fstream>

class Searcher : public QObject
{
    Q_OBJECT
public:
    explicit Searcher(QObject *parent = nullptr);

    void openDictionary();
    void setPattern(const QString &pattern);
    QString pattern() const;
    void stringSearch();
    //void consecutiveSearch();
    void stop();
    bool isSearch() const;

public slots:
    void start();

signals:
    void wordFound(const QString &word);

private:
    std::string _pattern;
    std::ifstream _dictionaryStream;
    bool _search = false;
};

#endif // SEARCHER_H
