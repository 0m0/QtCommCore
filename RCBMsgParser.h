#ifndef RCBMSGPARSER_H
#define RCBMSGPARSER_H

#include <QObject>
#include <QMap>
#include <QMap>

class CommServer;

struct DeviceSpec {
    QString domain;
    QString address;
};

typedef QMap<QString, QString> DataAttribute;
typedef QMap<DeviceSpec, QMap<QString, DataAttribute> > DataTable;

class RCBMsgParser : public QObject
{
    Q_OBJECT
public:
    enum ParsingMode { DefaultMode, NewMode };

    explicit RCBMsgParser(CommServer *parent = 0);
    virtual ~RCBMsgParser();

    bool parse(const QString &, ParsingMode = DefaultMode);
    const DataAttribute &rcb(const QString &domain, const QString &address);

    static QStringList patterns;

signals:

public slots:

private:

    QHash<QString, QString> *my_map;
    void addAddress(const QString, const QString);
    DataTable my_rcbTable;
};

#endif // RCBMSGPARSER_H
