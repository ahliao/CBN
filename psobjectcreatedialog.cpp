// NOTES: first load a library file or create a new one
// Show library entries in a table
// Have dialog to add/edit
// Very similar to the LOMDialog
// Need save/load functions

#include "psobjectcreatedialog.h"
#include <QGridLayout>

using namespace PSCDP;

PSCDP::PSObjectCreateDialog::PSObjectCreateDialog(QWidget *parent)
{
    QLabel *nameLbl = new QLabel("Name");
    QLabel *descLbl = new QLabel("Description");
    QLabel *typeLbl = new QLabel("Type");
    QLabel *input1Lbl = new QLabel("Input 1");
    QLabel *input2Lbl = new QLabel("Input 2");
    QLabel *input3Lbl = new QLabel("Input 3");
    QLabel *input4Lbl = new QLabel("Input 4");
    QLabel *output1Lbl = new QLabel("Output 1");
    QLabel *output2Lbl = new QLabel("Output 2");
    QLabel *output3Lbl = new QLabel("Output 3");
    QLabel *output4Lbl = new QLabel("Output 4");
    QLabel *layoutImgLbl = new QLabel("Layout Image");
    QLabel *systemImgLbl = new QLabel("System Image");
    QLabel *wiringImgLbl = new QLabel("Wiring Image");

    nameTxtEdt = new QLineEdit;
    descTxtEdt = new QLineEdit;
    input1TxtEdt = new QLineEdit;
    input2TxtEdt = new QLineEdit;
    input3TxtEdt = new QLineEdit;
    input4TxtEdt = new QLineEdit;
    output1TxtEdt = new QLineEdit;
    output2TxtEdt = new QLineEdit;
    output3TxtEdt = new QLineEdit;
    output4TxtEdt = new QLineEdit;
    layoutImgTxtEdt = new QLineEdit;
    systemImgTxtEdt = new QLineEdit;
    wiringImgTxtEdt = new QLineEdit;

    typeCmbox = new QComboBox;
    typeCmbox->addItem("General");
    typeCmbox->addItem("IO");
    typeCmbox->addItem("Power");
    typeCmbox->addItem("Network");

    layoutImgBrwBtn = new QPushButton("Browse");
    systemImgBrwBtn = new QPushButton("Browse");
    wiringImgBrwBtn = new QPushButton("Browse");

    acceptBtn = new QPushButton("Accept");
    cancelBtn = new QPushButton("Cancel");

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
    mainLayout->addWidget(input1Lbl,1,0);
    mainLayout->addWidget(input1TxtEdt,1,1,1,2);
    mainLayout->addWidget(output1Lbl,1,4);
    mainLayout->addWidget(output1TxtEdt,1,5,1,2);
    mainLayout->addWidget(input2Lbl,2,0);
    mainLayout->addWidget(input2TxtEdt,2,1,1,2);
    mainLayout->addWidget(output2Lbl,2,4);
    mainLayout->addWidget(output2TxtEdt,2,5,1,2);
    mainLayout->addWidget(input3Lbl,3,0);
    mainLayout->addWidget(input3TxtEdt,3,1,1,2);
    mainLayout->addWidget(output3Lbl,3,4);
    mainLayout->addWidget(output3TxtEdt,3,5,1,2);
    mainLayout->addWidget(input4Lbl,4,0);
    mainLayout->addWidget(input4TxtEdt,4,1,1,2);
    mainLayout->addWidget(output4Lbl,4,4);
    mainLayout->addWidget(output4TxtEdt,4,5,1,2);
    mainLayout->addWidget(layoutImgLbl,5,0);
    mainLayout->addWidget(layoutImgTxtEdt,5,1,1,2);
    mainLayout->addWidget(layoutImgBrwBtn,5,3);
    mainLayout->addWidget(layoutImgPic,5,4);
    mainLayout->addWidget(systemImgLbl,6,0);
    mainLayout->addWidget(systemImgTxtEdt,6,1,1,2);
    mainLayout->addWidget(systemImgBrwBtn,6,3);
    mainLayout->addWidget(systemImgPic,6,4);
    mainLayout->addWidget(wiringImgLbl,7,0);
    mainLayout->addWidget(wiringImgTxtEdt,7,1,1,2);
    mainLayout->addWidget(wiringImgBrwBtn,7,3);
    mainLayout->addWidget(wiringImgPic,7,4);
    mainLayout->addWidget(acceptBtn,8,1);
    mainLayout->addWidget(cancelBtn,8,3);

    this->setLayout(mainLayout);

    setWindowTitle("PS Object Creator");
}
