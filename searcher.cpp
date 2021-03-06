#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QThread>

#include "searcher.h"

Searcher::Searcher(QObject *parent) : QObject(parent)
{
    openDictionary();
}

void Searcher::openDictionary()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    "Open dictionary",
                                                    QDir::currentPath(),
                                                    "Text files (*.txt)");
    _dictionaryStream = std::ifstream(fileName.toStdString());
    if (!_dictionaryStream)
    {
        QMessageBox messageBox;
        messageBox.setText("Can't open dictionary! Restart app.");
        messageBox.exec();
    }
}

void Searcher::start()
{
    _search = true;
    stringSearch();
    if (_pattern.size() > 1)
    {
        consecutiveSearch();
    }
}

void Searcher::setPattern(const QString &pattern)
{
    _pattern = pattern.toStdString();
}

QString Searcher::pattern() const
{
    return QString::fromStdString(_pattern);
}

void Searcher::stringSearch()
{
    std::string line;
    _dictionaryStream.clear();
    _dictionaryStream.seekg(0);
    while (_search && !_dictionaryStream.eof())
    {
        _dictionaryStream >> line;
        auto found = line.find(_pattern);
        if (found != std::string::npos)
        {
            emit wordFound(QString::fromStdString(line));
            QThread::msleep(1);
        }
    }
}

void Searcher::consecutiveSearch()
{
    std::string line;
    size_t patternSize = _pattern.size();
    _dictionaryStream.clear();
    _dictionaryStream.seekg(0);
    while (_search && !_dictionaryStream.eof())
    {
        _dictionaryStream >> line;
        size_t index = 0;
        bool isRepeat = false;
        bool isLastRepeat = false;
        for (const auto &ch : line)
        {
            if (ch == _pattern[index])
            {
                if (!index)
                {
                     isRepeat = true;
                     isLastRepeat = true;
                }
                if (!isLastRepeat)
                {
                    isRepeat = false;
                }
                ++index;
                if (index == patternSize && !isRepeat)
                {
                    emit wordFound(QString::fromStdString(line));
                    QThread::msleep(1);
                }
            }
            else
            {
                isLastRepeat = false;
            }
        }
    }
}

void Searcher::stop()
{
    _search = false;
}

bool Searcher::isSearch() const
{
    return _search;
}
