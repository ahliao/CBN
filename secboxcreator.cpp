#include "secboxcreator.h"

#include <QHeaderView>
#include <QGridLayout>
#include <QDebug>

using namespace PSCDP;

PSCDP::SecBoxCreator::SecBoxCreator(QWidget *parent) : QWidget(parent)
{
    //LOMModel = new LOMTableModel;
    LOMModel = new LOMTableModel;

    LOMTableView = new QTableView;
    LOMTableView->setModel(LOMModel);
    LOMTableView->horizontalHeader()->setStretchLastSection(true);
    LOMTableView->resizeColumnsToContents();

    addPSObjectBtn = new QPushButton("Add Item");
    editPSObjectBtn = new QPushButton("Edit Item");
    removePSObjectBtn = new QPushButton("Remove Item");

    // Connect the button clicked signals
    connect(addPSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(addPSObject()));
    connect(editPSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(editPSObject()));
    connect(removePSObjectBtn, SIGNAL(clicked(bool)), this, SLOT(removePSObject()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(LOMTableView, 0, 0, 1, 3);
    mainLayout->addWidget(addPSObjectBtn, 1, 0, 1, 1);
    mainLayout->addWidget(editPSObjectBtn, 1, 1, 1, 1);
    mainLayout->addWidget(removePSObjectBtn, 1, 2, 1, 1);
    setLayout(mainLayout);

    setWindowTitle("Security Box Creator");
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
