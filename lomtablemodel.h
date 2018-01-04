#ifndef LOMTABLEMODEL_H
#define LOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "psobject.h"

namespace PSCDP
{
    class LOMTableModel : public QAbstractTableModel
    {
        Q_OBJECT

    public:
        LOMTableModel(QObject *parent = 0);

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value,
                         int role = Qt::EditRole);
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role=Qt::DisplayRole) const;
        bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
        bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
        bool insertPSObject(int row, PSObject psobject, const QModelIndex &parent = QModelIndex());

    private:
        QVector<PSObject> LOM;
    };
}

#endif // LOMTABLEMODEL_H
