#ifndef SCHEDULEEDITOR_H
#define SCHEDULEEDITOR_H

#include <QWidget>
#include "psobject.h"
#include "lomeditor.h"
#include "scheduletablemodel.h"

namespace PSCDP
{
    class ScheduleEditor : public QWidget
    {
        Q_OBJECT
    public:
        explicit ScheduleEditor(QWidget *parent = nullptr);

    signals:

    public slots:
        void handleLOMChange();

    private:
        LOMEditor *lomeditorwidget;
        QTableView *scheduleTableView;

        ScheduleTableModel *scheduleTableModel;
    };
}

#endif // SCHEDULEEDITOR_H
