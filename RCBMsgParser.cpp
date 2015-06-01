
#include <QRegularExpression>
#include <regex>
#include <QDebug>
#include "CommServer.h"
#include "RCBMsgParser.h"
#include "utc2gmt.h"
#include "time.h"

QStringList RCBMsgParser::patterns;

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
        << "(?:(\\((?:\w+)\\)\\{(?:(?:\\((?:\\w+)\\)(?:\\w+)),?)+\\})|(?:\\((\w+)\\gi)(\w+)))";

    my_map = new QHash<QString, QString>();

    *my_map = {
        {"Bool", "(\\d)"},
        {"Bcd", "([^(\\n)]*)"},
    	{"Bstring", "([^(\\n)]*)"},
    	{"Btime", "([^(\\n)]*)"},
    	{"BVstring13", "([01]{13})"},
    	{"BVstring2", "([01]{2})"},
    	{"BVstring1", "([01])"},
    	{"Byte", "(\\d+)"},
    	{"Double", "((?:[1-9]\\d*)+(?:\\.\\d+))"},
    	{"Float", "((?:[1-9]\\d*)+(?:\\.\\d+))"},
    	{"Fstring", "([^(\\n)]*)"},
    	{"Gtime", "([^(\\n)]*)"},
    	{"Int64", "([^(\\n)]*)"},
    	{"Long", "([^(\\n)]*)"},
    	{"Qstring", "([^(\\n)]*)"},
    	{"OVstring", "([^(\\n)]*)"},
    	{"Short", "([^(\\n)]*)"},
    	{"UByte", "([^(\\n)]*)"},
    	{"UInt64", "([^(\\n)]*)"},
    	{"ULong", "([^(\\n)]*)"},
    	{"UShort", "([^(\\n)]*)"},
    	{"Utctime", "UTC TIME seconds=(?<seconds>[1-9]\\d*), fraction=(?<fraction>[1-9]\\d*), qflags=(?<qflags>[1-9]\\d*)"},
    	{"UTF8string", "([^(\\n)]*)"},
    	{"UTF8Vstring", "([^(\\n)]*)"},
    	{"Vstring", "([^(\\n)]*)"}
    };
}

bool RCBMsgParser::parse(const QString &msg, ParsingMode parseMode)
{
    QRegularExpression regex;
    QRegularExpressionMatch match;
    static char timeBuffer[200];

    regex.setPatternOptions(QRegularExpression::DotMatchesEverythingOption);

    regex.setPattern(parseMode == DefaultMode ? patterns[0] : patterns[1]);
    match = regex.match(msg);

    if (!match.hasMatch())
        return false;

    regex.setPattern(patterns[1]);
    QRegularExpressionMatchIterator mit1 = regex.globalMatch(match.captured(3));

    while (mit1.hasNext()) {
        regex.setPattern(patterns[2]);

        QString str = mit1.next().captured(1);
        QRegularExpressionMatch m2 = regex.match(str);

        QString variables = m2.captured(1);
        QString values = m2.captured(2);
        QString domain = m2.captured(3);
        QString address = m2.captured(4);

        regex.setPattern(patterns[3]);
        QRegularExpressionMatchIterator mit2 = regex.globalMatch(variables);

        regex.setPattern(patterns[4]);
        QRegularExpressionMatchIterator mit3 = regex.globalMatch(values);

        while (mit2.hasNext()) {

            QRegularExpressionMatch mVar, mVal;
            QString attrName, attrType, attrValue;

            mVar = mit2.next();
            mVal = mit3.next();

            attrName = mVar.captured(1);
            attrType = mVar.captured(2);
            attrValue = mVal.captured(1);

            regex.setPattern(my_map->value(attrType));
            QRegularExpressionMatch m3 = regex.match(attrValue);

            if (attrType == "Utctime") {
                qDebug() << m3.captured(1).toLong() << m3.captured(2).toLong() << m3.captured(3).toLong();
                time_t t = m3.captured(1).toLong();
                ;

                //qDebug() << utctogmt(timeBuffer, m3.captured(1).toLong(), m3.captured(2).toLong(), m3.captured(3).toLong());
            }
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
