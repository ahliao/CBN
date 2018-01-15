#include "lomeditor.h"

#include <QHeaderView>
#include <QGridLayout>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextStream>

using namespace PSCDP;

PSCDP::LOMEditor::LOMEditor(QWidget *parent) : QWidget(parent)
{
    //LOMModel = new LOMTableModel;
    LOMModel = new LOMTableModel;

    LOMTableView = new QTableView;
    LOMTableView->setModel(LOMModel);
    LOMTableView->horizontalHeader()->setStretchLastSection(true);
    LOMTableView->resizeColumnsToContents();
    LOMTableView->setColumnWidth(0,100);
    LOMTableView->setSelectionBehavior(QTableView::SelectRows);
    LOMTableView->setSelectionMode(QTableView::SingleSelection);
    LOMTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    LOMTableView->setDragEnabled(true);
    LOMTableView->setAcceptDrops(true);
    LOMTableView->setDropIndicatorShown(true);
    LOMTableView->setDragDropOverwriteMode(false);
    LOMTableView->setDefaultDropAction(Qt::MoveAction);

    newLOMBtn = new QPushButton("New LOM");
    loadLOMBtn = new QPushButton("Load LOM");
    saveLOMBtn = new QPushButton("Save LOM");
    addPSObjectBtn = new QPushButton("Add Item");
    removePSObjectBtn = new QPushButton("Remove Item");

    // Connect the button clicked signals
    connect(newLOMBtn, SIGNAL(clicked(bool)), this, SLOT(newLOM()));
    connect(loadLOMBtn, SIGNAL(clicked(bool)), this, SLOT(loadLOM()));
    connect(saveLOMBtn, SIGNAL(clicked(bool)), this, SLOT(saveLOM()));
    connect(addPSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(addPSObject()));
    connect(removePSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(removePSObject()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(newLOMBtn, 0, 0, 1, 1);
    mainLayout->addWidget(loadLOMBtn, 0, 1, 1, 1);
    mainLayout->addWidget(saveLOMBtn, 0, 2, 1, 1);
    mainLayout->addWidget(LOMTableView, 1, 0, 1, 3);
    mainLayout->addWidget(addPSObjectBtn, 2, 0, 1, 1);
    mainLayout->addWidget(removePSObjectBtn, 2, 2, 1, 1);
    setLayout(mainLayout);

    setWindowTitle("LOM Editor");
}

void PSCDP::LOMEditor::newLOM()
{
    // Remove all rows from the current list
    if (LOMModel->rowCount() > 0)
        LOMModel->removeRows(0, LOMModel->rowCount());
}

void PSCDP::LOMEditor::loadLOM()
{
    // Remove all rows from the current list
    if (LOMModel->rowCount() > 0)
        LOMModel->removeRows(0, LOMModel->rowCount());

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load LOM"), "",
            tr("LOM (*.txt);;All Files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }
    QTextStream in(&file);
    QStringList lines = in.readAll().split('\n', QString::SkipEmptyParts);

    int row = 0;
    for (QString line : lines) {
        PSObject psobj;
        psobj.fromString(line);
        LOMModel->insertPSObject(row, psobj);
        ++row;
    }

    emit loadedLOM();
}

void PSCDP::LOMEditor::saveLOM()
{
    QVector<PSObject> psobjs = LOMModel->getPSObjects();
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save LOM"), "",
            tr("LOM (*.txt);;All Files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to save file"),
            file.errorString());
        return;
    }
    QTextStream out(&file);

    for (PSObject psobj : psobjs) {
        out << psobj.toString() << "\n";
    }
}

void PSCDP::LOMEditor::addPSObject()
{
    if (lomDialog.exec() == QDialog::Accepted) {
        PSObject psobj = lomDialog.getPSObject();
        qDebug() << "Returned: " << psobj.getDescription();
        // Add the PSObject to the list
        LOMModel->insertPSObject(LOMModel->rowCount(), psobj);
    }
}

void PSCDP::LOMEditor::removePSObject()
{
    LOMModel->removeRow(LOMTableView->currentIndex().row());

}

QVector<PSObject> PSCDP::LOMEditor::getLOM() const
{
    return LOMModel->getPSObjects();
}
