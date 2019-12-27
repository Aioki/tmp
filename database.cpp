#include "database.h"

database::database()
{

}


void database:: renameParents(QString textInUI)
{
    if (currentvalue.idChild != -1) {
        if (db[currentvalue.idChild].GetDad() == currentvalue.GetFIO()){
            db[currentvalue.idChild].SetDad(textInUI);
        }
        if (db[currentvalue.idChild].GetMum() == currentvalue.GetFIO()){
            db[currentvalue.idChild].SetMum(textInUI);
        }
    }
}

QMap<int, QString> database::listParent(QString set, int id)
{
    QMap<int, QString> listDad;
    QMap<int, QString> listMum;

    QMap<int,FamilyTree>::iterator curDB_Item;

    for (curDB_Item = db.begin();curDB_Item != db.end();curDB_Item++){
        if (curDB_Item->GetB_Day().daysTo(currentvalue.GetB_Day()) >= 5479 && curDB_Item.key() != id ){
            if(curDB_Item->GetSex() == "Мужской"){
               listDad.insert(curDB_Item.key(),curDB_Item->GetFIO());//добавляем в список
            }
            if(curDB_Item->GetSex() == "Женский"){
               listMum.insert(curDB_Item.key(),curDB_Item->GetFIO());//добавляем в список
            }
        }
    }

    if (set == "Мужской") {
        return listDad;
    } else if (set == "Женский") {
        return listMum;
    }
}

int database::toSort(FamilyTree & record, int id)
{
    int returnIndex = -1;
    if (SortItems.size() ==  0) {
        SortItems.append(id);
        return 1;
    } else

    for (int i = 0; i != SortItems.size() && returnIndex == -1;i++)
    {

        if (db[SortItems[i]] > record){
            SortItems.insert(i,id);
            returnIndex = i;
        }


    }
    if (returnIndex == -1) {
        returnIndex = SortItems.size();
        SortItems.insert(SortItems.size(),id);
    }
    return returnIndex + 1;
}


int database::count()
{
    return db.size();
}

int database::append(FamilyTree &record)
{
    int pos = toSort(record,max_uID);
    db.insert(max_uID,record);
    record = db[max_uID];
    max_uID++;
    isModifedDataBase = true;
    return pos;
}


int database::update(int id, FamilyTree &elements)
{
  if(db[id] != elements){
      isModifedDataBase = true;
      db[id] = elements;
  }

}

void database::record(unsigned int id, FamilyTree &record) const
{
    record = db[id];
}

void database::deleteItem(int id)
{
    db.remove(id);//Удаление из бд
    SortItems.removeOne(id);//Удаление из списка
}

bool database::save(QString filename)
{
    bool opened = false;
    if(!filename.isEmpty())
    {
        QFile file(filename);
        opened = file.open(QIODevice::WriteOnly);
        isModifedDataBase = false;
        QDataStream outputData(&file);

        outputData << db;



        file.close();
    }
    return opened;
}

bool database::load(QString filename)
{
    bool opened = false;
    if(!filename.isEmpty())
    {
        QFile file(filename);
        opened = file.open(QIODevice::ReadOnly);

        if(opened)
        {
            isModifedDataBase = false;
            QDataStream outputData(&file);
            db.clear();
            outputData >> db;

            file.close();
        }
    }
    return opened;
}




void database::clear()
{
    max_uID = 0;
    db.clear();
    SortItems.clear();
}

bool database::isModified() const
{
    return isModifedDataBase;
}

int database::lastID()
{
    return max_uID - 1;
}

int database::getID(FamilyTree & set)
{
    return  db.key(set);
}


//QDataStream &operator<<(QDataStream &out,const FamilyTree &data)
//{
//    out << data.GetDad() << data.GetFIO() << data.GetMum() << data.GetSex() <<
//           data.GetLive() << data.GetB_Day() << data.GetD_day()
//           << data.GetServe() << data.GetCitizenship() << data.idChild;

//    return out;
//}

//QDataStream &operator>>(QDataStream &out, FamilyTree &data)
//{

//    QString dFIO;
//    QString dDad;
//    QString dMum;
//    QDate dB_Day;
//    bool dLive;
//    QDate dD_Day;
//    QString dSex;
//    QString dCitizenship;
//    bool dServe;
//    bool didChild;

//    out >> dDad >> dFIO >> dMum >> dSex >> dLive >> dB_Day >> dD_Day >> dServe >> dCitizenship >> didChild;

//    // // out >> didChild >> dCitizenship >> dServe >> dD_Day >> dB_Day >>dLive >> dSex >> dMum >> dFIO >> dDad;
//    data.SetDad(dDad);
//    data.SetFIO(dFIO);
//    data.SetMum(dMum);
//    data.SetSex(dSex);
//    data.SetLive(dLive);
//    data.SetB_Day(dB_Day);
//    data.SetD_day(dD_Day);
//    data.SetServe(dServe);
//    data.SetCitizenship(dCitizenship);
//    data.idChild = didChild;

//    return out;
//}


//tmp ui->InputFIO->text()
