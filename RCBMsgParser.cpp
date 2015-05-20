
#include <QRegularExpression>
#include <regex>
#include <QDebug>
#include "CommServer.h"
#include "RCBMsgParser.h"

QStringList RCBMsgParser::patterns;
QList<DataTypeParse> RCBMsgParser::dataTypes;

RCBMsgParser::RCBMsgParser(CommServer *parent) :
    QObject(parent)
{
    if (parent) setParent(parent);

    RCBMsgParser::patterns
        << "<(\\w+)><(\\d+)><([^>]*)>"
        << "\\[([^\\]]*)\\]"
        << "\\{([^\\}]*)\\};\\{([^\\}]*)\\};([^;]*);(.*)"
        << "\\((\\w+)\\)(\\w+)"
        << "\\n([^(\\n)]*)"
        << "UTC TIME seconds=(\\d+), fraction=(\\d+), qflags=(\\d+)";

    RCBMsgParser::dataTypes
        << *new DataTypeParse(T_BOOL, "Bool", "(\\d)")
        << *new DataTypeParse(T_BCD, "Bcd", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_BSTRING, "Bstring", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_BTIME, "Btime", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_BVSTRING, "BVstring", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_BYTE, "Byte", "(\\d+)")
        << *new DataTypeParse(T_DOUBLE, "Double", "((?:\\d+)([.\\d]*)?)")
        << *new DataTypeParse(T_FLOAT, "Float", "((?:\\d+)([.\\d]*)?)")
        << *new DataTypeParse(T_FSTRING, "Fstring", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_GTIME, "Gtime", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_INT64, "Int64", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_LONG, "Long", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_OSTRING, "Qstring", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_OVSTRING, "OVstring", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_SHORT, "Short", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_UBYTE, "UByte", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_UINT64, "UInt64", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_ULONG, "ULong", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_USHORT, "UShort", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_UTCTIME, "Utctime", "UTC TIME seconds=(\\d+), fraction=(\\d+), qflags=(\\d+)")
        << *new DataTypeParse(T_UTF8STRING, "UTF8string", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_UTF8VSTRING, "UTF8Vstring", "\\n([^(\\n)]*)")
        << *new DataTypeParse(T_VSTRING, "Vstring", "\\n([^(\\n)]*)");
}

bool RCBMsgParser::parse(const QString &msg, ParsingMode parseMode)
{
    QRegularExpression regex;
    QRegularExpressionMatch match;

    regex.setPatternOptions(QRegularExpression::DotMatchesEverythingOption);

    regex.setPattern(parseMode == DefaultMode ? patterns[0] : patterns[1]);
    match = regex.match(msg);

    if (!match.hasMatch())
        return false;

    regex.setPattern(patterns[1]);

    QString lstDevices = match.captured(3);
    QRegularExpressionMatchIterator it = regex.globalMatch(lstDevices);

    while (it.hasNext()) {

        QRegularExpressionMatch m1 = it.next(), m2, m3;

        regex.setPattern(patterns[2]);

        m2 = regex.match(m1.captured(1));

        regex.setPattern(patterns[3]);
        QRegularExpressionMatchIterator m3it = regex.globalMatch(m2.captured(1));

        regex.setPattern(patterns[4]);
        QRegularExpressionMatchIterator m4it = regex.globalMatch(m2.captured(2));

        qDebug() << "Device:" << m2.captured(3) << "Address:" << m2.captured(4);
        while (m3it.hasNext()
               && !(m3 = m3it.next()).captured(1).isNull()
               && !m3.captured(1).isEmpty()) {

            if (m3.captured(1) == "t") {
                regex.setPattern(patterns[5]);
                QRegularExpressionMatch m4 = regex.match(m4it.next().captured(1));

                if (!m4.hasMatch()) return false;

                qDebug() << "\t" << m3.captured(1) << "=>"
                         << "seconds =" << m4.captured(1)
                         << "fraction =" << m4.captured(2)
                         << "qflags =" << m4.captured(3);
            }
            //else m4it.next();
            else qDebug() << "\t" << m3.captured(1) << "=>" << m4it.next().captured(1);
        }
        qDebug() << "\n..........................................\n";
    }

    return true;
}

RCBMsgParser::~RCBMsgParser()
{
}

const DataAttribute &RCBMsgParser::rcb(const QString &domain, const QString &address)
{
    ;
}
