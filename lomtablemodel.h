#ifndef LOMTABLEMODEL_H
#define LOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QMimeData>
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
        bool insertPSObject(int row, PSObject psobject, const QModelIndex &parent = QModelIndex());
        bool appendPSObject(PSObject psobject);
        bool clear();

        PSObject getPSObject(int row) const { return LOM.at(row); }
        QVector<PSObject> getPSObjects() const { return LOM; }

    private:
        QVector<PSObject> LOM;
    };
}

#endif // LOMTABLEMODEL_H
