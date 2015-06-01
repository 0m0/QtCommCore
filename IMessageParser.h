#ifndef IMESSAGEPARSER_H
#define IMESSAGEPARSER_H

#include <QObject>

class IMessageParser : public QObject
{
    Q_OBJECT
public:
    explicit IMessageParser(QObject *parent = 0);

signals:

public slots:

};

#endif // IMESSAGEPARSER_H
