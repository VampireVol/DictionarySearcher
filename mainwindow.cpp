#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    searcher = new Searcher();
    connect(_ui->input, &QLineEdit::textChanged,
            this, &MainWindow::updatePattern);
    connect(searcher, &Searcher::wordFound,
            this, &MainWindow::appendWord);
    connect(this, &MainWindow::search,
            searcher, &Searcher::start);
    searcher->moveToThread(&searcherThread);
    searcherThread.start();
}

MainWindow::~MainWindow()
{
    delete searcher;
    delete _ui;
    searcherThread.exit();
    searcherThread.wait();
}

void MainWindow::updatePattern(const QString &text)
{
    if (text.isEmpty())
    {
        _ui->output->clear();
        //stop
        searcher->setPattern("");
        return;
    }
    if (text != searcher->pattern())
    {
        _ui->output->clear();
        //stop
        searcher->setPattern(text);
        emit search();
    }
}

void MainWindow::appendWord(const QString &word)
{
    _ui->output->append(highlightWord(word));

}

QString MainWindow::highlightWord(const QString &word)
{
    QString pattern = searcher->pattern();
    QString highlight = word;
    QVector<int> index;
    for (int i = 0, j = 0; i < pattern.size(); ++j)
    {
        if (pattern[i] == word[j])
        {
            index.append(j);
            ++i;
        }
    }
    for (int i = index.size() - 1; i >= 0; --i)
    {
        highlight.insert(index[i] + 1, "</b>");
        highlight.insert(index[i], "<b>");
    }
    return highlight;
}

