#include "pslibmanager.h"
#include "psobjectcreatedialog.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextStream>

#include <QDebug>

using namespace PSCDP;

PSCDP::PSLibManager::PSLibManager(QWidget *parent) : QWidget(parent)
{
    LOMModel = new LOMTableModel;
    LOMTableView = new QTableView;
    LOMTableView->setModel(LOMModel);
    LOMTableView->horizontalHeader()->setStretchLastSection(true);
    LOMTableView->resizeColumnsToContents();
    LOMTableView->hideColumn(0);

    libNameLbl = new QLabel("Library Name: ");

    newLibBtn = new QPushButton("New Library");
    loadLibBtn = new QPushButton("Load Library");
    saveLibBtn = new QPushButton("Save Library");

    addPSLibBtn = new QPushButton("Add Item");
    editPSLibBtn = new QPushButton("Edit Item");
    removePSLibBtn = new QPushButton("Remove Item");
    addPSLibBtn->setEnabled(false);
    editPSLibBtn->setEnabled(false);
    removePSLibBtn->setEnabled(false);

    connect(newLibBtn, SIGNAL(clicked(bool)), this, SLOT(newLibClicked()));
    connect(loadLibBtn, SIGNAL(clicked(bool)), this, SLOT(loadLibClicked()));
    connect(saveLibBtn, SIGNAL(clicked(bool)), this, SLOT(saveLibClicked()));
    connect(addPSLibBtn, SIGNAL(clicked(bool)), this, SLOT(addPSLibClicked()));
    connect(editPSLibBtn, SIGNAL(clicked(bool)), this, SLOT(editPSLibClicked()));
    connect(removePSLibBtn, SIGNAL(clicked(bool)), this, SLOT(removePSLibClicked()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(libNameLbl, 0, 0, 1, 1);
    mainLayout->addWidget(newLibBtn, 1, 0, 1, 1);
    mainLayout->addWidget(loadLibBtn, 1, 1, 1, 1);
    mainLayout->addWidget(saveLibBtn, 1, 2, 1, 1);
    mainLayout->addWidget(LOMTableView, 2, 0, 1, 3);
    mainLayout->addWidget(addPSLibBtn, 3, 0, 1, 1);
    mainLayout->addWidget(editPSLibBtn, 3, 1, 1, 1);
    mainLayout->addWidget(removePSLibBtn, 3, 2, 1, 1);
    setLayout(mainLayout);

    setWindowTitle("PSObject Library Manager");
}

void PSCDP::PSLibManager::newLibClicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("Library name:"), QLineEdit::Normal,
                                             "", &ok);
    if (ok && !text.isEmpty()) {
        libName = text;
        libNameLbl->setText("Library Name: " + libName);
        LOMModel->clear();
    }

    addPSLibBtn->setEnabled(true);
    editPSLibBtn->setEnabled(true);
    removePSLibBtn->setEnabled(true);
}

void PSCDP::PSLibManager::loadLibClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load Library"), "",
            tr("PS Library (*.txt);;All Files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }
    QTextStream in(&file);

    // Read in the library name
    QStringList colNames = in.readLine().split('\t');
    libName = colNames.at(0);

    QStringList line;
    PSObject psobj;

    while(!in.atEnd()) {
        line = in.readLine().split('\t');
        qDebug() << line;
        for (int i = 0; i < colNames.size(); ++i) {
            if (colNames.at(i) == "Name") psobj.setName(line.at(i));
            else if (colNames.at(i) == "Description") psobj.setDescription(line.at(i));
            else if (colNames.at(i) == "Type") {
                psobj.setType(line.at(i));
            } else if (colNames.at(i) == "Layout Image") psobj.setLayoutImgPath(line.at(i));
            else if (colNames.at(i) == "System Image") psobj.setLayoutImgPath(line.at(i));
            else if (colNames.at(i) == "Wiring Image") psobj.setLayoutImgPath(line.at(i));
            else if (colNames.at(i).contains("Input")) psobj.addInput(line.at(i));
            else if (colNames.at(i).contains("Output")) psobj.addOutput(line.at(i));
            else if (colNames.at(i).contains("Height")) psobj.setHeight(line.at(i).toDouble());
            else if (colNames.at(i).contains("Width")) psobj.setWidth(line.at(i).toDouble());
        }
        LOMModel->appendPSObject(psobj);
    }
    file.close();
    libNameLbl->setText("Library Name: " + libName);

    addPSLibBtn->setEnabled(true);
    editPSLibBtn->setEnabled(true);
    removePSLibBtn->setEnabled(true);
}

void PSCDP::PSLibManager::saveLibClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Library"), "",
            tr("PS Library (*.txt);;All Files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to save file"),
            file.errorString());
        return;
    }
    QTextStream out(&file);
    out << libName << '\t' << "Name" << '\t' << "Description" << '\t' << "Type" <<
           '\t' << "Layout Image" << '\t' << "System Image" << '\t' <<
           "Wiring Image" << '\t' << "Input 1" << '\t' << "Input 2" <<
           '\t' << "Input 3" << '\t' << "Input 4" << '\t' << "Output 1" <<
           '\t' << "Output 2" << '\t' << "Output 3" << '\t' << "Output 4" <<
           '\t' << "Height" << '\t' << "Width" << '\n';
    QVector<PSObject> psobjs = LOMModel->getPSObjects();

    for (PSObject obj : psobjs) {
        out << '\t' << obj.getName() << '\t' << obj.getDescription() << '\t';
        out << obj.getType() << '\t';
        out << obj.getLayoutImgPath() << '\t' << obj.getSystemImgPath() << '\t' <<
               obj.getWiringImgPath() << '\t';
        QList<QString> inputs = obj.getInputs();
        QList<QString> outputs = obj.getOutputs();
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
        out << obj.getHeight() << '\t' << obj.getWidth() << '\n';
    }
    file.close();
}

void PSCDP::PSLibManager::addPSLibClicked()
{
    PSObjectCreateDialog psdialog;

    if (psdialog.exec() == QDialog::Accepted) {
        PSObject psobj = psdialog.getPSObject();
        LOMModel->appendPSObject(psobj);
        //qDebug() << "Returned: " << psobj.getName();
    }
}

void PSCDP::PSLibManager::editPSLibClicked()
{
    if (LOMModel->rowCount() <= 0) return;
    int selectedRow = LOMTableView->selectionModel()->currentIndex().row();
    if (selectedRow < 0) return;
    PSObjectCreateDialog psdialog;
    PSObject psobj = LOMModel->getPSObject(selectedRow);
    psdialog.loadPSObject(psobj);

    if (psdialog.exec() == QDialog::Accepted) {
        psobj = psdialog.getPSObject();
        LOMModel->removeRow(selectedRow);
        LOMModel->insertPSObject(selectedRow, psobj);
        //qDebug() << "Returned: " << psobj.getName();
    }
}

void PSCDP::PSLibManager::removePSLibClicked()
{
    int selectedRow = LOMTableView->selectionModel()->currentIndex().row();
    if (selectedRow < 0) return;
    LOMModel->removeRow(selectedRow);
}
