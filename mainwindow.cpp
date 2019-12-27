#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//==============  CONNECT  ========================================================================
    connect(ui->dateBirth,SIGNAL(dateChanged(QDate)),this,SLOT(setMinimumDDay(QDate)));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(changeItemInList(QListWidgetItem*)));
    connect(ui->ButtonAdd,SIGNAL(clicked()),this,SLOT(click_add()));
    connect(ui->ButtonDelete,SIGNAL(clicked()),this,SLOT(click_delete()));
    connect(ui->createFile, SIGNAL(triggered()), this, SLOT(createFile()));
    connect(ui->openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->saveAsFile, SIGNAL(triggered()), this, SLOT(saveAsFile()));
//=================================================================================================
    //Установка валидатора
    QValidator *ev = new ValidatorFIO(this);
    ui->InputFIO->setValidator(ev);


    ui->listWidget->currentItem()->setData(Qt::UserRole,-1);


    //Настройка дат
    ui->dateBirth->setMaximumDate(QDate::currentDate());
    ui->dateDie->setMaximumDate(QDate::currentDate());
//=================================================================================================



}

//===== SLOTS =====================================================================================


void MainWindow::click_add()
{
    if (ui->InputFIO->hasAcceptableInput()){
    int indexItem = db.append(db.currentvalue); // Хранит позицию строки
    insertItemInList(indexItem);
    ui->listWidget->item(indexItem)->setData(Qt::UserRole,db.lastID());
    ui->listWidget->setCurrentRow(indexItem);//выделяет добавленную строку
  //  ui->listWidget->currentItem()->setData(Qt::UserRole,db.lastID());
    validFIO = true;
    ui->ButtonAdd->setDisabled(1);
    } else
    QMessageBox::warning(this,"Корректность строки", "Строка введена неправильно");
    validFIO = false;



}

void MainWindow::click_delete()
{
    int id = ui->listWidget->currentItem()->data(Qt::UserRole).toInt();
    if (id != -1){
    db.deleteItem(id);
    ui->listWidget->takeItem(ui->listWidget->currentRow());
    //нужно удалять из вектора
    if (ui->listWidget->currentItem()->data(Qt::UserRole).toInt()) {
        db.record(ui->listWidget->currentItem()->data(Qt::UserRole).toInt(),db.currentvalue);
    } else db.currentvalue.clear();
    loadInWindow();
    }
}


void MainWindow::changedfocus(QWidget * old,QWidget * __new){

    if (!ui->InputFIO->hasAcceptableInput() && ui->InputFIO == old){

        QMessageBox::warning(this,"Корректность строки", "Строка введена неправильно");
        validFIO = false;
    } else {

    validFIO  =true;
    if (db.currentvalue.GetFIO() != ui->InputFIO->text()){
        db.renameParents(ui->InputFIO->text());
    }


    int curID = db.getID(db.currentvalue);



    db.currentvalue.SetDad(ui->cb_Dad->currentText());


    FamilyTree tmp;
    int ID_Parent =ui->cb_Dad->currentData().toInt();
    if (ID_Parent >= 0){
    db.record(ID_Parent,tmp);
    tmp.idChild = curID;

    db.update(ID_Parent,tmp);
    }

    db.currentvalue.SetMum(ui->cb_Mum->currentText());
    ID_Parent =ui->cb_Mum->currentData().toInt();
    if (ID_Parent >= 0){
    db.record(ID_Parent,tmp);
    tmp.idChild = curID;

    db.update(ID_Parent,tmp);
    }



    //Сохранение ФИО

    db.currentvalue.SetFIO(ui->InputFIO->text());
    //Добавить реализацию проверки родителей
    if (ui->ButtonMale->isChecked()){
        db.currentvalue.SetSex("Мужской");
    }
    if (ui->ButtonFemale->isChecked()){
        db.currentvalue.SetSex("Женский");
    }

    if (ui->ButtonPoland->isChecked()){
        db.currentvalue.SetCitizenship("Польша");
    }

    if (ui->ButtonRussia->isChecked()){
        db.currentvalue.SetCitizenship("Россия");
    }

    if (ui->ButtonGermany->isChecked()){
        db.currentvalue.SetCitizenship("Германия");
    }

    if (ui->ButtonUkraine->isChecked()){
        db.currentvalue.SetCitizenship("Украина");
    }
    db.currentvalue.SetLive(ui->checkLive->isChecked());
    db.currentvalue.SetB_Day(ui->dateBirth->date());
    db.currentvalue.SetD_day(ui->dateDie->date());
    db.currentvalue.SetServe(ui->checkServe->isChecked());

    //ListWidgetItem change
    if (ui->listWidget->currentRow() > 0 )
    {

     ui->listWidget->currentItem()->setText(ui->InputFIO->text() + "\t" + ui->dateBirth->date().toString("dd.MM.yyyy") + "\t" + ui->dateDie->date().toString("dd.MM.yyyy") + "\t"
                                       + ui->cb_Dad->currentText() + " , " + ui->cb_Mum->currentText());

     int current_id = ui->listWidget->currentItem()->data(Qt::UserRole).toInt();

     db.update(current_id,db.currentvalue);
    }
}
}



void MainWindow::changeItemInList(QListWidgetItem * _new)
{

  if (ui->InputFIO->hasAcceptableInput() || currentRowIsList == 0)
  {

        currentRowIsList = ui->listWidget->currentRow();

        if(ui->listWidget->currentRow() >=0)
        {
            ui->ButtonAdd->setDisabled(ui->listWidget->currentRow());
            int id = ui->listWidget->currentItem()->data(Qt::UserRole).toInt();

            if (id == -1) {
                db.currentvalue.clear();
            }
            else
            {
                db.record(id,db.currentvalue);
            }
            loadInWindow();
        }
    }
   else {
        ui->listWidget->setCurrentRow(currentRowIsList);
        QMessageBox::warning(this,"Корректность строки", "Строка введена неправильно");
   }
}

//mb bug
void MainWindow::insertParents(QWidget *_old = nullptr, QWidget *_new = nullptr)
{

    if (_old == ui->dateBirth || (_old == NULL && _new == NULL)) {

        int curID;
        if (ui->listWidget->currentRow() >= 0) {
            curID = ui->listWidget->currentItem()->data(Qt::UserRole).toInt();
        } else curID = 0;
        QMap<int, QString> listDad = db.listParent("Мужской",curID);
        QMap<int, QString> listMum = db.listParent("Женский",curID);


        QMap<int, QString>::iterator listIndex;

        //Очистка комбо боксов
        ui->cb_Dad->clear();
        ui->cb_Mum->clear();
        ui->cb_Dad->addItem("Не задано",-1);
        ui->cb_Mum->addItem("Не задано",-1);

        for (listIndex = listDad.begin(); listIndex != listDad.constEnd(); listIndex++) {
            int tmp =listIndex.key();
            ui->cb_Dad->addItem(listIndex.value(),tmp);
        }
        for (listIndex = listMum.begin(); listIndex != listMum.constEnd(); listIndex++) {
            int tmp =listIndex.key();
            ui->cb_Mum->addItem(listIndex.value(),tmp);
        }
    }
}

//===============================================================================================


//Устанавливает Минимальную дату для Даты смерти SLOTs
void MainWindow::setMinimumDDay(QDate set){
    ui->dateDie->setMinimumDate(set);
}


void MainWindow::openFile()
{
    if(isCurrentFileModifed())
    {// Если текущий файл был модифицирован...
        if(isAcceptSaveFile())
        { // Если пользователь согласился на сохранения файла...
            saveFile(); // ...сохранить файл
        }
    }

    // Получаем имя открываемого файла.
    QString newFileName = QFileDialog::getOpenFileName(this, "Открыть файл", "/", "База данных пользователей (*.userdb)");

    if(!newFileName.isEmpty())
    {// Если новое имя файла не пустое...
        currentFileName = newFileName; //... текущему имени файла присваиваем новое.
        db.clear(); // Чистим БД.
        db.load(currentFileName); // Загружаем файл в БД.
        UpdateList(); // Обновляем UI.
        this->setWindowTitle("Текущий файл: "+ currentFileName); // Устанавливаем в статус бар имя текущего файла.
    }
}

void MainWindow::saveFile()
{
    if(!currentFileName.isEmpty())
    {// Если имя текущего файла не пустое...
        db.save(currentFileName); // ...сохраняем БД в текущий файл.
    }
    else
    {// Иначе..
        saveAsFile(); // ...Выполняем сохранение с запросом имени файла.
    }

    this->setWindowTitle("Текущий файл: "+ currentFileName); // Устанавливаем в статус бар имя текущего файла.}
}
void MainWindow::saveAsFile()
{
    // Получаем имя сохраняемого файла.
    QString newFileName = QFileDialog::getSaveFileName(this, "Сохранить как", "/", "База данных пользователей (*.userdb)");
    if(!newFileName.isEmpty())
    {// Если новое имя файла не пустое...
        currentFileName = newFileName;  //... текущему имени файла присваиваем новое.
        db.save(currentFileName);  // ...сохраняем БД в текущий файл.
        this->setWindowTitle("Текущий файл: "+ currentFileName); // Устанавливаем в статус бар имя текущего файла.    }
    }
}

void MainWindow::createFile()
{
    if(isCurrentFileModifed())
    {// Если текущий файл был модифицирован...
        if(isAcceptSaveFile())
        { // Если пользователь согласился на сохранения файла...
            saveFile(); // ...сохранить файл
        }
    }

    currentFileName = ""; // Текущее имя файла
    db.clear(); // Чистим БД.
    UpdateList(); // Обновляем UI.
    this->setWindowTitle("Текущий файл: "+ currentFileName); // Устанавливаем в статус бар имя текущего файла.

}

bool MainWindow::isCurrentFileModifed()
{
    // Если файл не модифицирован и не является только что созданным и пустым.
    return db.isModified() && !(currentFileName.isEmpty() && db.count() == 0);
}

bool MainWindow::isAcceptSaveFile()
{
    // Запрос на согласие сохранения файла...
    bool result;
    QMessageBox msgBox;
            msgBox.setText("Файл не сохранён");
            msgBox.setInformativeText("Данный файл был изменён, хотите ли вы сохранить файл? "
                                      "\nВ противном случае все изменения будут потеряны.");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
            int ret = msgBox.exec();

            switch(ret)
            {
                case QMessageBox::Save:
                    result = true;
                    break;
                case QMessageBox::Discard:
                    result = false;
                    break;
                default:
                    result = false;
            }

    // Возвращаем результат ответа пользователя
    return result;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(isCurrentFileModifed())
    {  // Если текущий файл был модифицирован...
        if(isAcceptSaveFile())
        {   // Если пользователь согласился на сохранения файла...
            saveFile(); // ...сохранить файл
        }
    }
    // Закрыть окно.
    QMainWindow::closeEvent(event);
}




//Загружает из записи значения
void MainWindow::loadInWindow()
{
//Устанавливает RadioButton в дефолтные значения
    ui->ButtonMale->setChecked(1);
    ui->ButtonRussia->setChecked(1);
//Загрузка ФИО
    ui->InputFIO->setText(db.currentvalue.GetFIO());

    qDebug() << "<><><><>";
    qDebug() << db.currentvalue.GetDad();
    qDebug() << db.currentvalue.GetMum();
    qDebug() << "<><><><>";
//mb bug ==================================================================
    insertParents(NULL,NULL);



    ui->cb_Dad->setCurrentText(db.currentvalue.GetDad());
    ui->cb_Mum->setCurrentText(db.currentvalue.GetMum());

//=========================================================================


//Загрузка пола
    ui->ButtonMale->setChecked(db.currentvalue.GetSex() == "Мужской");
    ui->ButtonFemale->setChecked(db.currentvalue.GetSex() == "Женский");
//Загрузка гражданства
    ui->ButtonPoland->setChecked(db.currentvalue.GetCitizenship() == "Польша");
    ui->ButtonRussia->setChecked(db.currentvalue.GetCitizenship() == "Россия");
    ui->ButtonGermany->setChecked(db.currentvalue.GetCitizenship() == "Германия");
    ui->ButtonUkraine->setChecked(db.currentvalue.GetCitizenship() == "Украина");
//Загрузка чекбоксов и даты
    ui->checkLive->setChecked(db.currentvalue.GetLive());
    ui->dateDie->setDisabled(db.currentvalue.GetLive());
    ui->checkServe->setChecked(db.currentvalue.GetServe());
    ui->dateBirth->setDate(db.currentvalue.GetB_Day());
    ui->dateDie->setDate(db.currentvalue.GetD_day());
    ui->dateDie->setMinimumDate(db.currentvalue.GetB_Day());
}

void MainWindow::UpdateList()
{
    //Хранит сортированную копию listWidget из бд
    //param[in] - uId
    QVector<int> SortList = db.SortItems;

    ui->listWidget->clear();
    ui->listWidget->addItem("По умолчанию");
    ui->listWidget->item(0)->setData(Qt::UserRole,-1);

    QVector<int>::Iterator pos;
    int index = 1;

    db.currentvalue.clear();
    for (pos = SortList.begin();pos != SortList.end();pos++) {
        db.record(*pos,db.currentvalue);
        insertItemInList(index);
    }
    loadInWindow();
}


void MainWindow::insertItemInList(int indexItem)
{
    ui->listWidget->insertItem(indexItem,db.currentvalue.GetFIO() + QString("\t") + db.currentvalue.GetB_Day().toString("dd.MM.yyyy") + QString("\t") + db.currentvalue.GetD_day().toString("dd.MM.yyyy") + QString("\t")
                               + db.currentvalue.GetDad() + " , " + db.currentvalue.GetMum());//добавление строки

}




MainWindow::~MainWindow()
{
    delete ui;
}

