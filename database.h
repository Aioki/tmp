#ifndef DATABASE_H
#define DATABASE_H
#include "QObject"
#include "familytree.h"
#include "QMap"
#include "QFile"
#include "QDataStream"

const int MAX_VALUE = 1000;

class database
{

public:
    FamilyTree currentvalue;
    QVector<int> SortItems;

    database();
    //получить кол-во записей
    int count();
    //добавить запись в базу данных; возвращается id
    int append(FamilyTree &record);

    //изменить запись в базе данных; возвращается новая позиция записи в соответствии с порядком сортировки
    int update(int id, FamilyTree& elements);

    //— возвращает запись (только для чтения) по заданному идентификатору
    void record(unsigned int id, FamilyTree &record) const;

    void deleteItem(int id);

    bool save(QString filename);
    bool load(QString filename);
    void clear();

    bool isModified() const;
    int lastID();

    int getID(FamilyTree &);
   void renameParents(QString);
   //mb bug
   //param[in] - sex
   //param[in] - currentID
   QMap<int, QString> listParent(QString set, int id);

   int toSort(FamilyTree&, int id);


private:
    QMap<int,FamilyTree> db;
    int max_uID = 0;

    bool isModifedDataBase; // Была ли изменена база данных


};

///*! Оператор вывода в поток
// * \param out поток
// * \param data данные для вывода
// * \return поток
// */
//QDataStream &operator<<(QDataStream & out,const FamilyTree & data);

///*! Оператор ввода из потока
// * \param out поток
// * \param data данные для ввода
// * \return поток
// */
//QDataStream & operator>>(QDataStream & out, FamilyTree & data);


#endif // DATABASE_H
