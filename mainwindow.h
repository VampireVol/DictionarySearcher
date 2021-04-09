#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "searcher.h"

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
    QString highlightWord(const QString &word);

signals:
    void search();

private:
    Ui::MainWindow *_ui;
    Searcher *searcher;
    QThread searcherThread;
    bool test = true;
};
#endif // MAINWINDOW_H
