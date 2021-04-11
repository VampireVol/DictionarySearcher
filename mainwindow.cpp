#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _searcher = new Searcher();
    _highlight = new Highlight();

    connect(_ui->input, &QLineEdit::textChanged,
            this, &MainWindow::updatePattern);
    connect(_searcher, &Searcher::wordFound,
            _highlight, &Highlight::highlighting);
    connect(_highlight, &Highlight::highlightedWord,
            this, &MainWindow::appendWord);
    connect(this, &MainWindow::search,
            _searcher, &Searcher::start);

    _searcher->moveToThread(&_searcherThread);
    _searcherThread.start();
    _highlight->moveToThread(&_highlightThread);
    _highlightThread.start();
}

MainWindow::~MainWindow()
{
    delete _searcher;
    delete _highlight;
    delete _ui;
    _searcherThread.exit();
    _searcherThread.wait();
    _highlightThread.exit();
    _highlightThread.wait();
}

void MainWindow::updatePattern(const QString &text)
{
    _searcher->stop();
    _highlight->stop();
    _highlightThread.exit();
    _highlightThread.wait();
    _highlightThread.start();
    _searcher->setPattern(text);
    _highlight->setPattern(text);
    _ui->output->clear();

    if (!text.isEmpty())
    {
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

