#include "others.h"

bool Email_check (QString email) {
    QRegExp mailREX("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);

    return mailREX.exactMatch(email);
}
