#include "lomtablemodel.h"

using namespace PSCDP;

PSCDP::LOMTableModel::LOMTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int PSCDP::LOMTableModel::rowCount(const QModelIndex &parent) const
{
    return LOM.size();
}

int PSCDP::LOMTableModel::columnCount(const QModelIndex &parent) const
{
    // Col1: ID, Col2: Name, Col3:Description
    return 3;
}

QVariant PSCDP::LOMTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= LOM.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
        PSObject psobj = LOM.at(index.row());
        if (index.column() == 0) return psobj.getID();
        else if (index.column() == 1) return psobj.getName();
        else return psobj.getDescription();
    } else {
        return QVariant();
    }
}

Qt::ItemFlags PSCDP::LOMTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.column() != 2)
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool PSCDP::LOMTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Replace the part being edited with the value
    if (index.isValid() && role == Qt::EditRole) {
        if (index.column() == 0) return false;
        else if (index.column() == 1) return false;
        else if (index.column() == 2) {
            LOM[index.row()].setDescription(value.toString());
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant PSCDP::LOMTableModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == 0) return QString("ID");
        else if (section == 1) return QString("Name");
        else if (section == 2) return QString("Description");
        else return QString("");
    } else {
        return QString("%1").arg(section);
    }
}

bool PSCDP::LOMTableModel::insertRows(int position, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+count-1);

    for (int row = 0; row < count; ++row) {
        //LOM.insert(position, "");
    }

    endInsertRows();
    return true;
}

bool PSCDP::LOMTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        LOM.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool PSCDP::LOMTableModel::insertPSObject(int row, PSObject psobject, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row);

    LOM.insert(row, psobject);

    endInsertRows();
    return true;
}
