#include "lomdialog.h"
#include <QGridLayout>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

using namespace PSCDP;

PSCDP::LOMDialog::LOMDialog(QWidget *parent)
{
    Q_UNUSED(parent)
    //label = new QLabel("Dialog to add/edit a PSObject");


    QStringList libList;
    QByteArray allLibsData;

    // Read the library list file
    qDebug() << QCoreApplication::applicationDirPath() + "/partlibs.txt";
    QFile libFile(QCoreApplication::applicationDirPath() + "\\partlibs.txt");
    libFile.open(QIODevice::ReadOnly);
    libList = QString(libFile.readAll()).split(QString("\n"));
    libFile.close();

    for (QString path : libList) {
        QFile file(QCoreApplication::applicationDirPath() + path);
        file.open(QIODevice::ReadOnly);
        allLibsData.append(file.readAll());
        file.close();
    }

    model = new TreeModel(allLibsData);

    partsTree = new QTreeView;
    partsTree->setModel(model);
    connect(partsTree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(handeDoneBtn()));

    layoutImageTopLbl = new QLabel("Layout Drawing");
    layoutImageLbl = new QLabel;
    layoutImageLbl->setFixedHeight(100);
    layoutImageLbl->setFixedWidth(100);
    layoutImageLbl->setScaledContents(true);

    sysImageTopLbl = new QLabel("System Drawing");
    sysImageLbl = new QLabel;
    sysImageLbl->setFixedHeight(100);
    sysImageLbl->setFixedWidth(100);
    sysImageLbl->setScaledContents(true);

    wiringImageTopLbl = new QLabel("Wiring Drawing");
    wiringImageLbl = new QLabel;
    wiringImageLbl->setFixedHeight(100);
    wiringImageLbl->setFixedWidth(100);
    wiringImageLbl->setScaledContents(true);

    doneBtn = new QPushButton("Done");
    manageLibsBtn = new QPushButton("Manage Libs");
    manageLibsBtn->setEnabled(false);
    cancelBtn = new QPushButton("Cancel");

    connect(doneBtn, SIGNAL(clicked(bool)), this, SLOT(handeDoneBtn()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(partsTree, 0, 0, 1, 3);
    mainLayout->addWidget(layoutImageTopLbl, 1, 0);
    mainLayout->addWidget(sysImageTopLbl, 1, 1);
    mainLayout->addWidget(wiringImageTopLbl, 1, 2);
    mainLayout->addWidget(layoutImageLbl, 2, 0);

    mainLayout->addWidget(sysImageLbl, 2, 1);
    mainLayout->addWidget(wiringImageLbl, 2, 2);
    mainLayout->addWidget(doneBtn, 3, 0);
    mainLayout->addWidget(manageLibsBtn, 3, 1);
    mainLayout->addWidget(cancelBtn, 3, 2);
    this->setLayout(mainLayout);

    connect(partsTree->selectionModel(), SIGNAL(currentChanged(const QModelIndex&,const QModelIndex&)), this, SLOT(handleTreeSelection(const QModelIndex&,const QModelIndex&)));
}

PSObject PSCDP::LOMDialog::getPSObject() const
{
    return returnPSObject;
}

void PSCDP::LOMDialog::handleTreeSelection(const QModelIndex &current,const QModelIndex &/*previous*/)
{
    //if (model->columnCount(current) >= 5) {
        PSObject psobj = model->getData(current);
        QString layoutImagePath = psobj.getLayoutImgPath();
        QPixmap layoutImage(layoutImagePath);
        layoutImageLbl->setPixmap(layoutImage);
        QString sysImagePath = psobj.getSystemImgPath();
        QPixmap sysImage(sysImagePath);
        sysImageLbl->setPixmap(sysImage);
        QString wiringImagePath = psobj.getWiringImgPath();
        QPixmap wiringImage(wiringImagePath);
        wiringImageLbl->setPixmap(wiringImage);
    //}
}

// File layout (Name, Description, Type, Layout, System, Wiring)
void PSCDP::LOMDialog::handeDoneBtn()
{
    returnPSObject = model->getData(partsTree->selectionModel()->currentIndex());
    accept();
}
