#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

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

void Searcher::stop()
{
    _search = false;
}

bool Searcher::isSearch() const
{
    return _search;
}
