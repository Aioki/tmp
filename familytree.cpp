#include "familytree.h"

FamilyTree::FamilyTree()
{

}

//==============  SET  ==============================================================================================
void FamilyTree::SetFIO(QString set){
   FIO = set;
}
void FamilyTree::SetB_Day(QDate set){
    B_Day = set;
}
void FamilyTree::SetLive(bool set){
    Live = set;
}
void FamilyTree::SetD_day(QDate set){
    D_Day = set;
}
void FamilyTree::SetSex(QString set){
    Sex = set;
}
void FamilyTree::SetCitizenship(QString set){
    Citizenship = set;
}
void FamilyTree::SetServe(bool set){
    Serve = set;
}
void FamilyTree::SetDad(QString set)
{
    Dad = set;
}
void FamilyTree::SetMum(QString set)
{
    Mum = set;
}


//===================================================================================================================


//==============  GET  ==============================================================================================
QString FamilyTree::GetFIO() const {
    return FIO;
}
QDate FamilyTree::GetB_Day() const {
    return B_Day;
}
bool FamilyTree::GetLive() const {
    return Live;
}
QDate FamilyTree::GetD_day() const {
    return D_Day;
}
QString FamilyTree::GetSex() const {
    return Sex;
}
QString FamilyTree::GetCitizenship() const {
    return Citizenship;
}
bool FamilyTree::GetServe() const {
    return Serve;
}
QString FamilyTree::GetMum() const {
    return Mum;
}
QString FamilyTree::GetDad() const {
    return Dad;
}

bool FamilyTree::operator==(const FamilyTree &right) const
{
    return FIO == right.FIO && Mum == right.Mum && Dad == right.Dad && B_Day == right.B_Day && Sex == right.Sex && Live == right.Live
            && D_Day ==right.D_Day && Citizenship == right.Citizenship && Serve == right.Serve && idChild == right.idChild;
}

bool FamilyTree::operator!=(const FamilyTree &right)
{
    return !(*this == right);
}

bool FamilyTree::operator<(const FamilyTree &right)
{
    if (B_Day < right.B_Day){
        return true;
    }
    if (B_Day == right.B_Day && FIO < right.FIO) {
        return true;
    }
    return false;
}

bool FamilyTree::operator<=(const FamilyTree &right)
{
    return *this < right || (FIO == right.FIO && B_Day == right.B_Day);
}

bool FamilyTree::operator>(const FamilyTree &right)
{
    if (B_Day > right.B_Day){
        return true;
    }
    if (B_Day == right.B_Day && FIO > right.FIO) {
        return true;
    }
    return false;
}

bool FamilyTree::operator>=(const FamilyTree &right)
{
    return *this > right || (FIO == right.FIO && B_Day == right.B_Day);
}

FamilyTree& FamilyTree::operator=(const FamilyTree &right)
{
    FIO = right.FIO;
    Mum = right.Mum;
    Dad = right.Dad;
    B_Day = right.B_Day;
    Sex = right.Sex;
    Live = right.Live;
    D_Day =right.D_Day;
    Citizenship = right.Citizenship;
    Serve = right.Serve;
    idChild = right.idChild;

    return *this;
}



void FamilyTree::clear()
{
    FIO = "";
    Dad = "Не задано";
    Mum = "Не задано";
    B_Day = {2019,01,01};
    Live = true;
    D_Day = {2000,01,01};
    Sex = "Не задано";
    Citizenship = "";
    Serve = false;
    idChild = -1;
}


QDataStream &operator<<(QDataStream &out,const FamilyTree &data)
{
    out << data.GetDad() << data.GetFIO() << data.GetMum() << data.GetSex() <<
           data.GetLive() << data.GetB_Day() << data.GetD_day()
           << data.GetServe() << data.GetCitizenship() << data.idChild;

    return out;
}

QDataStream &operator>>(QDataStream &out, FamilyTree &data)
{

    QString dFIO;
    QString dDad;
    QString dMum;
    QDate dB_Day;
    bool dLive;
    QDate dD_Day;
    QString dSex;
    QString dCitizenship;
    bool dServe;
    bool didChild;

    out >> dDad >> dFIO >> dMum >> dSex >> dLive >> dB_Day >> dD_Day >> dServe >> dCitizenship >> didChild;

    // // out >> didChild >> dCitizenship >> dServe >> dD_Day >> dB_Day >>dLive >> dSex >> dMum >> dFIO >> dDad;
    data.SetDad(dDad);
    data.SetFIO(dFIO);
    data.SetMum(dMum);
    data.SetSex(dSex);
    data.SetLive(dLive);
    data.SetB_Day(dB_Day);
    data.SetD_day(dD_Day);
    data.SetServe(dServe);
    data.SetCitizenship(dCitizenship);
    data.idChild = didChild;

    return out;
}


//===================================================================================================================
