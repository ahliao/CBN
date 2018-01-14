#ifndef PSOBJECTCREATOR_H
#define PSOBJECTCREATOR_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include "psobject.h"

namespace PSCDP
{
    class PSObjectCreateDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit PSObjectCreateDialog(QWidget *parent = 0);

        void loadPSObject(PSObject p);
        PSObject getPSObject() const;

    signals:

    public slots:
        void handleDoneBtn();
        void handleLayoutBrw();
        void handleSystemBrw();
        void handleWiringBrw();

    private:
        QLineEdit *nameTxtEdt;
        QLineEdit *descTxtEdt;
        QList<QLineEdit*> inputTxtEdt;
        QList<QLineEdit*> outputTxtEdt;
        QLineEdit *layoutImgTxtEdt;
        QLineEdit *systemImgTxtEdt;
        QLineEdit *wiringImgTxtEdt;
        QDoubleSpinBox *widthSpnBox;
        QDoubleSpinBox *heightSpnBox;

        QComboBox *typeCmbox;

        QPushButton *layoutImgBrwBtn;
        QPushButton *systemImgBrwBtn;
        QPushButton *wiringImgBrwBtn;
        QPushButton *acceptBtn;
        QPushButton *cancelBtn;

        QLabel *layoutImgPic;
        QLabel *systemImgPic;
        QLabel *wiringImgPic;

        PSObject psobj;
    };
}

#endif // PSOBJECTCREATOR_H
