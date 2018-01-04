#ifndef PSOBJECTCREATOR_H
#define PSOBJECTCREATOR_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

namespace PSCDP
{
    class PSObjectCreateDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit PSObjectCreateDialog(QWidget *parent = 0);

    signals:

    public slots:

    private:
        QLineEdit *nameTxtEdt;
        QLineEdit *descTxtEdt;
        QLineEdit *input1TxtEdt;
        QLineEdit *input2TxtEdt;
        QLineEdit *input3TxtEdt;
        QLineEdit *input4TxtEdt;
        QLineEdit *output1TxtEdt;
        QLineEdit *output2TxtEdt;
        QLineEdit *output3TxtEdt;
        QLineEdit *output4TxtEdt;
        QLineEdit *layoutImgTxtEdt;
        QLineEdit *systemImgTxtEdt;
        QLineEdit *wiringImgTxtEdt;

        QComboBox *typeCmbox;

        QPushButton *layoutImgBrwBtn;
        QPushButton *systemImgBrwBtn;
        QPushButton *wiringImgBrwBtn;
        QPushButton *acceptBtn;
        QPushButton *cancelBtn;

        QLabel *layoutImgPic;
        QLabel *systemImgPic;
        QLabel *wiringImgPic;
    };
}

#endif // PSOBJECTCREATOR_H
