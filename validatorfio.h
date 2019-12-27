#ifndef VALIDATORFIO_H
#define VALIDATORFIO_H

#include "QValidator"

class ValidatorFIO : public QValidator
{
    Q_OBJECT
public:
    ValidatorFIO(QObject *parent);
    ~ValidatorFIO();

    QValidator::State validate(QString & string, int & pos) const;
};


#endif // VALIDATORFIO_H
