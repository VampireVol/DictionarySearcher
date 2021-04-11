#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "searcher.h"
#include "highlight.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updatePattern(const QString &text);
    void appendWord(const QString &word);

signals:
    void search();

private:
    Ui::MainWindow *_ui;
    Searcher *_searcher;
    Highlight *_highlight;
    QThread _searcherThread;
    QThread _highlightThread;
};
#endif // MAINWINDOW_H
