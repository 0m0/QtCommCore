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

//enum {
//    T_BOOL, T_BVSTRING, T_BSTRING, T_BYTE, T_SHORT, T_LONG,
//    T_INT64, T_UBYTE, T_USHORT, T_ULONG, T_UINT64, T_FLOAT,
//    T_DOUBLE, T_OVSTRING, T_OSTRING, T_VSTRING, T_FSTRING,
//    T_GTIME, T_BTIME, T_BCD, T_UTCTIME, T_UTF8VSTRING,
//    T_UTF8STRING
//};

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
