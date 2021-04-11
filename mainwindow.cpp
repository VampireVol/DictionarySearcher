#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _searcher = new Searcher();
    connect(_ui->input, &QLineEdit::textChanged,
            this, &MainWindow::updatePattern);
    connect(_searcher, &Searcher::wordFound,
            this, &MainWindow::appendWord);
    connect(this, &MainWindow::search,
            _searcher, &Searcher::start);
    _searcher->moveToThread(&_searcherThread);
    _searcherThread.start();
}

MainWindow::~MainWindow()
{
    delete _searcher;
    delete _ui;
    _searcherThread.exit();
    _searcherThread.wait();
}

void MainWindow::updatePattern(const QString &text)
{
    if (text.isEmpty())
    {
        _ui->output->clear();
        _searcher->stop();
        _searcher->setPattern("");
        return;
    }
    if (text != _searcher->pattern())
    {
        _ui->output->clear();
        _searcher->stop();
        _searcher->setPattern(text);
        emit search();
    }
}

void MainWindow::appendWord(const QString &word)
{
    if (_searcher->isSearch())
    {
        _ui->output->append(word);
    }
}

QString MainWindow::highlightWord(const QString &word)
{
//    QString pattern = _searcher->pattern();
//    QString highlight = word;
//    QVector<int> index;
//    for (int i = 0, j = 0; i < pattern.size(); ++j)
//    {
//        if (pattern[i] == word[j])
//        {
//            index.append(j);
//            ++i;
//        }
//    }
//    for (int i = index.size() - 1; i >= 0; --i)
//    {
//        highlight.insert(index[i] + 1, "</b>");
//        highlight.insert(index[i], "<b>");
//    }
//    return highlight;
    return "";
}

