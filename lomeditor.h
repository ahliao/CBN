#ifndef SECBOXCREATOR_H
#define SECBOXCREATOR_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include "lomtablemodel.h"
#include "lomdialog.h"

namespace PSCDP
{
    class LOMEditor : public QWidget
    {
        Q_OBJECT
    public:
        explicit LOMEditor(QWidget *parent = nullptr);
        QVector<PSObject> getLOM() const;

    signals:
        void loadedLOM();

    public slots:
        void newLOM();
        void loadLOM();
        void saveLOM();
        void addPSObject();
        void removePSObject();

    private:
        QTableView *LOMTableView;
        QPushButton *newLOMBtn;
        QPushButton *loadLOMBtn;
        QPushButton *saveLOMBtn;
        QPushButton *addPSObjectBtn;
        QPushButton *removePSObjectBtn;

        LOMTableModel *LOMModel;

        LOMDialog lomDialog;
    };
}

#endif // SECBOXCREATOR_H
