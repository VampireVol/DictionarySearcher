#include "searcher.h"

Searcher::Searcher(QObject *parent) : QObject(parent)
{

}

void Searcher::start()
{
    for (int i = 0; i < 1000; ++i)
    {
        emit wordFound("hello");
        QThread::msleep(2);
    }
}

void Searcher::setPattern(const QString &pattern)
{
    _pattern = pattern;
}

QString Searcher::pattern() const
{
    return _pattern;
}
