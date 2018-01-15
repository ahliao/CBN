#ifndef SCHEDULETABLEMODEL_H
#define SCHEDULETABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QMimeData>
#include "psobject.h"

#include <QStyledItemDelegate>

namespace PSCDP
{
    class ComboBoxItemDelegate : public QStyledItemDelegate
    {
        Q_OBJECT
    public:
        ComboBoxItemDelegate(QObject* parent=0);
        ~ComboBoxItemDelegate();

        virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
        virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
        virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

        void setItemOptions(QStringList list);

    private:
        QStringList comboBoxItems;
    };

    class ScheduleTableModel : public QAbstractTableModel
    {
        Q_OBJECT

    public:
        ScheduleTableModel(QObject *parent = 0);

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        Qt::DropActions supportedDropActions() const;
        QStringList mimeTypes() const;
        QMimeData *mimeData(const QModelIndexList &indexes) const;
        bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
                             int row, int column, const QModelIndex &parent) const;
        bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                          int row, int column, const QModelIndex &parent);
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value,
                         int role = Qt::EditRole);
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role=Qt::DisplayRole) const;
        bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
        bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
        //bool insertPSObject(int row, PSObject psobject, const QModelIndex &parent = QModelIndex());
        //bool appendPSObject(PSObject psobject);

        //PSObject getPSObject(int row) const { return LOM.at(row); }
        //QVector<PSObject> getPSObjects() const { return LOM; }

        bool generateSchedule(QString FDBName, QVector<PSObject> psobjs);
        void setSensorCableColors(QStringList str) { sensorCableColors = str; }

    private:
        void addBoard(int startRow, QString FDBName, QString boardName, QStringList boardWireColors,
                      QStringList boardContacts, int boardNumInputs, int boardNumOutputs);
        void updateCables();

        QVector<QStringList> scheduleList;
        QString m_FDBName;
        QStringList sensorCableColors;
    };
}

#endif // SCHEDULETABLEMODEL_H
