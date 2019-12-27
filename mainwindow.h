#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "validatorfio.h"
#include "database.h"
#include "QMessageBox"
#include "QDebug"
#include "QFileDialog"





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:

    Ui::MainWindow *ui;

    bool validFIO =false;
    bool addstring = false;
    int currentRowIsList = 0;

    database db;
    QString currentFileName;    // Имя открытого файла


    void loadInWindow();

    void UpdateList();
    void closeEvent(QCloseEvent *event);


    void insertItemInList(int); //Добавление строки в ListWidget из currentvalue (было бы неплохо использовать структуру)

    /*! Изменён ли текущий файл.
     * \return true если изменён, иначе false.
     */
    bool isCurrentFileModifed();

    /*! Запрос на согласие сохранения файла
     * \return true если пользлователь согласился, иначе false
     */
    bool isAcceptSaveFile();




private slots:

    void click_add();
    void click_delete();
    void changedfocus(QWidget *,QWidget *);
    void changeItemInList(QListWidgetItem *);
    /// Заполняет значения ComboBox родителями
    void insertParents(QWidget *,QWidget *);
    void setMinimumDDay(QDate);
    void createFile();
    void openFile();
    void saveFile();
    void saveAsFile();




};
#endif // MAINWINDOW_H
