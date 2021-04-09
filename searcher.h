#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QThread>

class Searcher : public QObject
{
    Q_OBJECT
public:
    explicit Searcher(QObject *parent = nullptr);
    void setPattern(const QString &pattern);
    QString pattern() const;

public slots:
    void start();

signals:
    void wordFound(const QString &word);

private:
    QString _pattern;
};

#endif // SEARCHER_H
