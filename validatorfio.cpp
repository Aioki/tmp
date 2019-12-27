#include "validatorfio.h"
#include "QDebug"

ValidatorFIO::ValidatorFIO(QObject* parent)
: QValidator (parent)
{

}

ValidatorFIO::~ValidatorFIO()
{

}

QValidator::State ValidatorFIO::validate(QString &string, int &pos) const
{
    QRegExp rx("[А-Я][а-я]+\\s[А-Я][а-я]+\\s[А-Я][а-я]+");
    QRegExp rx1("[А-Я]?[а-я]*\\s?[А-Я]?[а-я]*\\s?[А-Я]?[а-я]*");
if (string.size() > 45) return QValidator::Invalid;

if (rx.exactMatch(string)) return QValidator::Acceptable;
if (rx1.exactMatch(string)) return QValidator::Intermediate;
else return  QValidator::Invalid;
}
