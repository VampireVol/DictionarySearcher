#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QObject>
#include <QMutex>

class Highlight : public QObject
{
    Q_OBJECT
public:
    explicit Highlight(QObject *parent = nullptr);

    void setPattern(const QString &pattern);
    void stop();

public slots:
    void highlighting(const QString &word);

signals:
    void highlightedWord(const QString &word);

private:
    QMutex _mutex;
    QString _pattern;
    bool _runing = false;
};

#endif // HIGHLIGHT_H
