#include "secboxcreator.h"

#include <QHeaderView>
#include <QGridLayout>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextStream>

using namespace PSCDP;

PSCDP::SecBoxCreator::SecBoxCreator(QWidget *parent) : QWidget(parent)
{
    //LOMModel = new LOMTableModel;
    LOMModel = new LOMTableModel;

    LOMTableView = new QTableView;
    LOMTableView->setModel(LOMModel);
    LOMTableView->horizontalHeader()->setStretchLastSection(true);
    LOMTableView->resizeColumnsToContents();
    LOMTableView->setColumnWidth(0,100);
    /*LOMTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    LOMTableView->setDragEnabled(true);
    LOMTableView->setAcceptDrops(true);
    LOMTableView->setDropIndicatorShown(true);*/

    loadLOMBtn = new QPushButton("Load LOM");
    saveLOMBtn = new QPushButton("Save LOM");
    addPSObjectBtn = new QPushButton("Add Item");
    editPSObjectBtn = new QPushButton("Edit Item");
    removePSObjectBtn = new QPushButton("Remove Item");

    // Connect the button clicked signals
    connect(saveLOMBtn, SIGNAL(clicked(bool)), this, SLOT(saveLOM()));
    connect(addPSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(addPSObject()));
    connect(editPSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(editPSObject()));
    connect(removePSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(removePSObject()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(loadLOMBtn, 0, 0, 1, 1);
    mainLayout->addWidget(saveLOMBtn, 0, 1, 1, 1);
    mainLayout->addWidget(LOMTableView, 1, 0, 1, 3);
    mainLayout->addWidget(addPSObjectBtn, 2, 0, 1, 1);
    mainLayout->addWidget(editPSObjectBtn, 2, 1, 1, 1);
    mainLayout->addWidget(removePSObjectBtn, 2, 2, 1, 1);
    setLayout(mainLayout);

    setWindowTitle("Security Box Creator");
}

void PSCDP::SecBoxCreator::loadLOM()
{
    // Remove all rows from the current list
    LOMModel->removeRows(0, LOMModel->rowCount());


}

void PSCDP::SecBoxCreator::saveLOM()
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
        out << psobj.getID() << '\t' << psobj.getDescription() << '\t';
        if (psobj.getType() == ObjectType::General) out << "General" << '\t';
        else if (psobj.getType() == ObjectType::IO) out << "IO" << '\t';
        else if (psobj.getType() == ObjectType::Network) out << "Network" << '\t';
        else if (psobj.getType() == ObjectType::Power) out << "Power" << '\t';
        out << psobj.getLayoutImgPath() << '\t' << psobj.getSystemImgPath() << '\t' <<
               psobj.getWiringImgPath() << '\t';
        QList<QString> inputs = psobj.getInputs();
        QList<QString> outputs = psobj.getOutputs();
        for (int i = 0; i < 4; ++i) {
            if (inputs.size()-1 > i)
                out << inputs.at(i) << '\t';
            else out << '\t';
        }
        for (int i = 0; i < 4; ++i) {
            if (outputs.size()-1 > i)
                out << outputs.at(i) << '\t';
            else out << '\t';
        }
        out << psobj.getHeight() << '\t' << psobj.getWidth() << "\r\n";
    }
}

void PSCDP::SecBoxCreator::addPSObject()
{
    if (lomDialog.exec() == QDialog::Accepted) {
        PSObject psobj = lomDialog.getPSObject();
        qDebug() << "Returned: " << psobj.getDescription();
        // Add the PSObject to the list
        LOMModel->insertPSObject(LOMModel->rowCount(), psobj);
    }
}

void PSCDP::SecBoxCreator::editPSObject()
{

}

void PSCDP::SecBoxCreator::removePSObject()
{
    LOMModel->removeRow(LOMTableView->currentIndex().row());

}
