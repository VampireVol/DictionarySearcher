#include "highlight.h"
#include <QThread>

Highlight::Highlight(QObject *parent) : QObject(parent)
{

}

void Highlight::setPattern(const QString &pattern)
{
    _mutex.lock();
    _pattern = pattern;
    _mutex.unlock();
    QThread::msleep(5);
    _runing = true;
}

void Highlight::stop()
{
    _runing = false;
}

void Highlight::highlighting(const QString &word)
{
    if (!_runing)
        return;
    _mutex.lock();
    QString highlight = word;
    QVector<int> index;
    for (int i = 0, j = 0; i < _pattern.size() && j < word.size(); ++j)
    {
        if (_pattern[i] == word[j])
        {
            index.append(j);
            ++i;
        }
    }
    _mutex.unlock();
    for (int i = index.size() - 1; i >= 0; --i)
    {
        highlight.insert(index[i] + 1, "</b>");
        highlight.insert(index[i], "<b>");
    }
    emit highlightedWord(highlight);
    QThread::msleep(10);
}
