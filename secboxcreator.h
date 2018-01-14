#ifndef SECBOXCREATOR_H
#define SECBOXCREATOR_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include "lomtablemodel.h"
#include "lomdialog.h"

namespace PSCDP
{
    class SecBoxCreator : public QWidget
    {
        Q_OBJECT
    public:
        explicit SecBoxCreator(QWidget *parent = nullptr);

    signals:

    public slots:
        void loadLOM();
        void saveLOM();
        void addPSObject();
        void editPSObject();
        void removePSObject();

    private:
        QTableView *LOMTableView;
        QPushButton *loadLOMBtn;
        QPushButton *saveLOMBtn;
        QPushButton *addPSObjectBtn;
        QPushButton *editPSObjectBtn;
        QPushButton *removePSObjectBtn;

        LOMTableModel *LOMModel;

        LOMDialog lomDialog;
    };
}

#endif // SECBOXCREATOR_H
