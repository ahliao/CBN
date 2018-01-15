// NOTES: first load a library file or create a new one
// Show library entries in a table
// Have dialog to add/edit
// Very similar to the LOMDialog
// Need save/load functions

#include "psobjectcreatedialog.h"
#include <QGridLayout>
#include <QFileDialog>

using namespace PSCDP;

PSCDP::PSObjectCreateDialog::PSObjectCreateDialog(QWidget *parent)
{
    QLabel *nameLbl = new QLabel("Name");
    QLabel *descLbl = new QLabel("Description");
    QLabel *typeLbl = new QLabel("Type");
    QLabel *heightLbl = new QLabel("Height (in)");
    QLabel *widthLbl = new QLabel("Width (in)");
    QLabel *layoutImgLbl = new QLabel("Layout Image");
    QLabel *systemImgLbl = new QLabel("System Image");
    QLabel *wiringImgLbl = new QLabel("Wiring Image");

    QList<QLabel*> inputLbls;
    QList<QLabel*> outputLbls;

    nameTxtEdt = new QLineEdit;
    descTxtEdt = new QLineEdit;
    for (int i = 0; i < 4; ++i) {
        QLabel *inputLbl = new QLabel("Input " + QString::number(i+1));
        inputLbls.append(inputLbl);
        QLabel *outputLbl = new QLabel("Output " + QString::number(i+1));
        outputLbls.append(outputLbl);
        QLineEdit *txtEdt = new QLineEdit;
        inputTxtEdt.append(txtEdt);
        QLineEdit *txtEdt2 = new QLineEdit;
        outputTxtEdt.append(txtEdt2);
    }
    layoutImgTxtEdt = new QLineEdit;
    systemImgTxtEdt = new QLineEdit;
    wiringImgTxtEdt = new QLineEdit;

    widthSpnBox = new QDoubleSpinBox;
    widthSpnBox->setMinimum(0);
    heightSpnBox = new QDoubleSpinBox;
    heightSpnBox->setMinimum(0);

    typeCmbox = new QComboBox;
    typeCmbox->addItem("General");
    typeCmbox->addItem("IO");
    typeCmbox->addItem("Power");
    typeCmbox->addItem("Network");

    layoutImgBrwBtn = new QPushButton("Browse");
    systemImgBrwBtn = new QPushButton("Browse");
    wiringImgBrwBtn = new QPushButton("Browse");

    connect(layoutImgBrwBtn, SIGNAL(clicked(bool)), this, SLOT(handleLayoutBrw()));
    connect(systemImgBrwBtn, SIGNAL(clicked(bool)), this, SLOT(handleSystemBrw()));
    connect(wiringImgBrwBtn, SIGNAL(clicked(bool)), this, SLOT(handleWiringBrw()));

    acceptBtn = new QPushButton("Done");
    cancelBtn = new QPushButton("Cancel");

    connect(acceptBtn, SIGNAL(clicked(bool)), this, SLOT(handleDoneBtn()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));

    layoutImgPic = new QLabel;
    layoutImgPic->setFixedHeight(100);
    layoutImgPic->setFixedWidth(100);
    layoutImgPic->setScaledContents(true);
    systemImgPic = new QLabel;
    systemImgPic->setFixedHeight(100);
    systemImgPic->setFixedWidth(100);
    systemImgPic->setScaledContents(true);
    wiringImgPic = new QLabel;
    wiringImgPic->setFixedHeight(100);
    wiringImgPic->setFixedWidth(100);
    wiringImgPic->setScaledContents(true);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLbl,0,0);
    mainLayout->addWidget(nameTxtEdt,0,1);
    mainLayout->addWidget(descLbl,0,2);
    mainLayout->addWidget(descTxtEdt,0,3,1,2);
    mainLayout->addWidget(typeLbl,0,5);
    mainLayout->addWidget(typeCmbox,0,6);
    mainLayout->addWidget(heightLbl,1,0);
    mainLayout->addWidget(heightSpnBox,1,1);
    mainLayout->addWidget(widthLbl,1,2);
    mainLayout->addWidget(widthSpnBox,1,3);

    // Put this into some HLayout
    for (int i = 0; i < inputTxtEdt.size(); ++i) {
        mainLayout->addWidget(inputLbls.at(i),i+2,0);
        mainLayout->addWidget(inputTxtEdt.at(i),i+2,1,1,2);
        mainLayout->addWidget(outputLbls.at(i),i+2,4);
        mainLayout->addWidget(outputTxtEdt.at(i),i+2,5,1,2);
    }

    mainLayout->addWidget(layoutImgLbl,6,0);
    mainLayout->addWidget(layoutImgTxtEdt,6,1,1,3);
    mainLayout->addWidget(layoutImgBrwBtn,6,4);
    mainLayout->addWidget(layoutImgPic,6,5);
    mainLayout->addWidget(systemImgLbl,7,0);
    mainLayout->addWidget(systemImgTxtEdt,7,1,1,3);
    mainLayout->addWidget(systemImgBrwBtn,7,4);
    mainLayout->addWidget(systemImgPic,7,5);
    mainLayout->addWidget(wiringImgLbl,8,0);
    mainLayout->addWidget(wiringImgTxtEdt,8,1,1,3);
    mainLayout->addWidget(wiringImgBrwBtn,8,4);
    mainLayout->addWidget(wiringImgPic,8,5);
    mainLayout->addWidget(acceptBtn,9,1);
    mainLayout->addWidget(cancelBtn,9,3);

    this->setLayout(mainLayout);

    setWindowTitle("PS Object Creator");
}

void PSCDP::PSObjectCreateDialog::handleDoneBtn()
{
    psobj.setID("N/A");
    psobj.setName(nameTxtEdt->text());
    psobj.setDescription(descTxtEdt->text());
    psobj.setLayoutImgPath(layoutImgTxtEdt->text());
    psobj.setSystemImgPath(systemImgTxtEdt->text());
    psobj.setWiringImgPath(wiringImgTxtEdt->text());
    psobj.setWidth(widthSpnBox->value());
    psobj.setHeight(heightSpnBox->value());
    for (int i = 0; i < inputTxtEdt.size(); ++i) {
        if (!inputTxtEdt.at(i)->text().isEmpty()) psobj.addInput(inputTxtEdt.at(i)->text());
    }
    for (int i = 0; i < outputTxtEdt.size(); ++i) {
        if (!outputTxtEdt.at(i)->text().isEmpty()) psobj.addInput(outputTxtEdt.at(i)->text());
    }

    psobj.setType(typeCmbox->currentText());

    accept();
}

void PSCDP::PSObjectCreateDialog::handleLayoutBrw()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Layout Image"), "",
            tr("Image Files (*.png *.jpg *.bmp);;All Files (*)"));
    QPixmap layoutImage(fileName);
    layoutImgPic->setPixmap(layoutImage);
    layoutImgTxtEdt->setText(fileName);
}

void PSCDP::PSObjectCreateDialog::handleSystemBrw()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("System Image"), "",
            tr("Image Files (*.png *.jpg *.bmp);;All Files (*)"));
    QPixmap systemImage(fileName);
    systemImgPic->setPixmap(systemImage);
    systemImgTxtEdt->setText(fileName);
}

void PSCDP::PSObjectCreateDialog::handleWiringBrw()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Wiring Image"), "",
            tr("Image Files (*.png *.jpg *.bmp);;All Files (*)"));
    QPixmap wiringImage(fileName);
    wiringImgPic->setPixmap(wiringImage);
    wiringImgTxtEdt->setText(fileName);
}

void PSCDP::PSObjectCreateDialog::loadPSObject(PSObject p)
{
    nameTxtEdt->setText(p.getName());
    descTxtEdt->setText(p.getDescription());
    widthSpnBox->setValue(p.getWidth());
    heightSpnBox->setValue(p.getHeight());
    layoutImgTxtEdt->setText(p.getLayoutImgPath());
    QPixmap layoutImage(p.getLayoutImgPath());
    layoutImgPic->setPixmap(layoutImage);
    systemImgTxtEdt->setText(p.getSystemImgPath());
    QPixmap systemImage(p.getSystemImgPath());
    systemImgPic->setPixmap(systemImage);
    wiringImgTxtEdt->setText(p.getWiringImgPath());
    QPixmap wiringImage(p.getWiringImgPath());
    wiringImgPic->setPixmap(wiringImage);
    int index;
    index = typeCmbox->findText(p.getType());
    if (index != -1) typeCmbox->setCurrentIndex(index);

    QList<QString> inputs = p.getInputs();
    // Should check the size of inputTxtEdts
    for (int i = 0; i < inputs.size(); ++i) {
        inputTxtEdt[i]->setText(inputs.at(i));
    }

    QList<QString> outputs = p.getOutputs();
    // Should check the size of inputTxtEdts
    for (int i = 0; i < outputs.size(); ++i) {
        outputTxtEdt[i]->setText(outputs.at(i));
    }
}

PSObject PSCDP::PSObjectCreateDialog::getPSObject() const
{
    return psobj;
}
