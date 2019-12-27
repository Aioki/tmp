#ifndef FAMILYTREE_H
#define FAMILYTREE_H
#include "QString"
#include "QDate"
#include "QDataStream"


class FamilyTree
{
private:

    QString FIO;
    QString Dad = "Не задано";
    QString Mum = "Не задано";
    QDate B_Day = {2019,01,01};
    bool Live = true;
    QDate D_Day = {2000,01,01};
    QString Sex = "Не задано";
    QString Citizenship;
    bool Serve = false;
public:
    FamilyTree();
//====== ID  ======================================================================================o
      int idChild = -1;
//====== Set ======================================================================================
    void SetFIO(QString set);
    void SetB_Day(QDate);
    void SetLive(bool);
    void SetD_day(QDate);
    void SetSex(QString);
    void SetCitizenship(QString);
    void SetServe(bool);
    void SetDad(QString);
    void SetMum(QString);


//====== Get ======================================================================================
    QString GetFIO()const;
    QDate GetB_Day()const;
    bool GetLive()const;
    QDate GetD_day()const;
    QString GetSex()const;
    QString GetCitizenship()const;
    bool GetServe()const;
    QString GetMum()const;
    QString GetDad()const;

//===== Operator ================================================================================
    bool operator==(const FamilyTree& right) const;
    bool operator!=(const FamilyTree& right);
    bool operator<(const FamilyTree& right);
    bool operator<=(const FamilyTree& right);
    bool operator>(const FamilyTree& right);
    bool operator>=(const FamilyTree& right);
    FamilyTree& operator=(const FamilyTree& right);


//===============================================================================================
    void clear();




};


/*! Оператор вывода в поток
 * \param out поток
 * \param data данные для вывода
 * \return поток
 */
QDataStream &operator<<(QDataStream & out,const FamilyTree & data);

/*! Оператор ввода из потока
 * \param out поток
 * \param data данные для ввода
 * \return поток
 */
QDataStream & operator>>(QDataStream & out, FamilyTree & data);


#endif // FAMILYTREE_H
