#include "scheduleeditor.h"
#include <QHeaderView>
#include <QGridLayout>

using namespace PSCDP;

PSCDP::ScheduleEditor::ScheduleEditor(QWidget *parent) : QWidget(parent)
{
    scheduleTableModel = new ScheduleTableModel;

    lomeditorwidget = new LOMEditor;

    scheduleTableView = new QTableView;
    scheduleTableView->setModel(scheduleTableModel);
    scheduleTableView->horizontalHeader()->setStretchLastSection(true);
    scheduleTableView->resizeColumnsToContents();
    scheduleTableView->setSelectionBehavior(QTableView::SelectRows);
    scheduleTableView->setSelectionMode(QTableView::SingleSelection);
    scheduleTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    /*scheduleTableView->setDragEnabled(true);
    scheduleTableView->setAcceptDrops(true);
    scheduleTableView->setDropIndicatorShown(true);
    scheduleTableView->setDragDropOverwriteMode(false);
    scheduleTableView->setDefaultDropAction(Qt::MoveAction);*/

    ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(scheduleTableView);
    QStringList cableColors;
    cableColors << "WHITE-GREEN" << "BLUE-BLACK" << "RED-BLACK";
    scheduleTableModel->setSensorCableColors(cableColors);
    cbid->setItemOptions(cableColors);
    scheduleTableView->setItemDelegateForColumn(7, cbid);

    //QVector<PSObject> list;
    //list.append(PSObject("ID 1", "General", "Name", "Description"));
    //scheduleTableModel->generateSchedule("FDB-02-001", list);

    connect(lomeditorwidget, SIGNAL(loadedLOM()), this, SLOT(handleLOMChange()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(lomeditorwidget, 0, 0, 1, 1);
    mainLayout->addWidget(scheduleTableView, 0, 1, 1, 1);

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 2);

    setLayout(mainLayout);


}

void PSCDP::ScheduleEditor::handleLOMChange()
{
    QVector<PSObject> lom = lomeditorwidget->getLOM();
    scheduleTableModel->generateSchedule("PERIM-FDB-02-001", lom);
}
