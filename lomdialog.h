#ifndef LOMDIALOG_H
#define LOMDIALOG_H

#include <QDialog>
#include <QTreeView>
#include <QPushButton>
#include <QLabel>
#include "lomtreemodel.h"
#include "lomtreeitem.h"
#include "psobject.h"

namespace PSCDP
{
    class LOMDialog : public QDialog
    {
        Q_OBJECT

    public:
        LOMDialog(QWidget *parent = 0);

        PSObject getPSObject() const;

    public slots:
        void handleTreeSelection(const QModelIndex &current,const QModelIndex &previous);
        void handeDoneBtn();

    private:
        QTreeView *partsTree;
        QLabel *layoutImageTopLbl;
        QLabel *layoutImageLbl;
        QLabel *sysImageTopLbl;
        QLabel *sysImageLbl;
        QLabel *wiringImageTopLbl;
        QLabel *wiringImageLbl;

        QPushButton *doneBtn;
        QPushButton *manageLibsBtn;
        QPushButton *cancelBtn;

        TreeModel *model;

        PSObject returnPSObject;
    };
}

#endif // LOMDIALOG_H
