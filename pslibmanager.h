#ifndef PSLIBMANAGER_H
#define PSLIBMANAGER_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include "lomtablemodel.h"

namespace PSCDP
{
    class PSLibManager : public QWidget
    {
        Q_OBJECT

    public:
        PSLibManager(QWidget *parent = 0);

    public slots:
        void newLibClicked();
        void loadLibClicked();
        void saveLibClicked();
        void addPSLibClicked();
        void editPSLibClicked();
        void removePSLibClicked();

    private:
        QTableView *LOMTableView;
        QPushButton *newLibBtn;
        QPushButton *loadLibBtn;
        QPushButton *saveLibBtn;
        QPushButton *addPSLibBtn;
        QPushButton *editPSLibBtn;
        QPushButton *removePSLibBtn;

        QLabel *libNameLbl;

        LOMTableModel *LOMModel;

        QString libName;
    };
}

#endif // PSLIBMANAGER_H
