
#include <QRegularExpression>
#include <regex>
#include <QDebug>
#include "CommServer.h"
#include "RCBMsgParser.h"

QStringList RCBMsgParser::patterns;
QHash<QString, QString> RCBMsgParser::mapTypePattern;

RCBMsgParser::RCBMsgParser(CommServer *parent) :
    QObject(parent)
{
    if (parent) setParent(parent);

    RCBMsgParser::mapTypePattern.insert("Bool", "(\\d)");
    RCBMsgParser::mapTypePattern.insert("Bcd", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Bstring", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Btime", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("BVstring", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Byte", "(\\d+)");
    RCBMsgParser::mapTypePattern.insert("Double", "([1-9][\\d])+(\\.\\d+)?");
    RCBMsgParser::mapTypePattern.insert("Float", "([1-9][\\d])+(\\.\\d+)?");
    RCBMsgParser::mapTypePattern.insert("Fstring", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Gtime", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Int64", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Long", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Qstring", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("OVstring", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Short", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("UByte", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("UInt64", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("ULong", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("UShort", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Utctime", "UTC TIME seconds=([1-9][\\d]*), fraction=([1-9][\\d]*), qflags=([1-9][\\d]*)");
    RCBMsgParser::mapTypePattern.insert("UTF8string", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("UTF8Vstring", "\\n([^(\\n)]*)");
    RCBMsgParser::mapTypePattern.insert("Vstring", "\\n([^(\\n)]*)");

    RCBMsgParser::patterns
        << "<(\\w+)><(\\d+)><([^>]*)>"
        << "\\[([^\\]]*)\\]"
        << "\\{([^\\}]*)\\};\\{([^\\}]*)\\};([^;]*);(.*)"
        << "\\((\\w+)\\)(\\w+)";
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
        QRegularExpressionMatchIterator m4it = regex.globalMatch(m2.captured(2));

        regex.setPattern(patterns[3]);
        QRegularExpressionMatchIterator m3it = regex.globalMatch(m2.captured(1));

        while (m3it.hasNext()
               && !(m3 = m3it.next()).captured(1).isNull()
               && !m3.captured(1).isEmpty()) {

            regex.setPattern(RCBMsgParser::mapTypePattern.value(m2.captured(1)));
            QRegularExpressionMatch m4 = regex.match(m4it.next().captured(1));

            qDebug() << m3.captured(1) << m4.capturedTexts() << "\n......................\n";
        }
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
