#include "lomtablemodel.h"
#include <QDebug>

using namespace PSCDP;

PSCDP::LOMTableModel::LOMTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int PSCDP::LOMTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return LOM.size();
}

int PSCDP::LOMTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // Col1: ID, Col2: Name, Type, Col4:Description
    return 4;
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
        else if (index.column() == 2) return psobj.getType();
        else return psobj.getDescription();
    } else if (role == Qt::EditRole) {
        PSObject psobj = LOM.at(index.row());
        if (index.column() == 0) return psobj.getID();
        else if (index.column() == 1) return psobj.getName();
        else if (index.column() == 2) return psobj.getType();
        else return psobj.getDescription();
    } else {
        return QVariant();
    }
}

Qt::DropActions PSCDP::LOMTableModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList PSCDP::LOMTableModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

QMimeData *PSCDP::LOMTableModel::mimeData(const QModelIndexList &indexes) const
{
    QList<int> selectedRows;
    foreach (const QModelIndex &index, indexes) {
        if (index.isValid() && selectedRows.contains(index.row())) continue;
        else selectedRows.append(index.row());
    }

    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const int &row, selectedRows) {
        //if (index.isValid()) {
            //QString text = data(index, Qt::DisplayRole).;
            PSObject cpypsobj = getPSObject(row);
            //stream << cpypsobj.getName() << '\t' << cpypsobj.getDescription() << '\t' <<
            //          cpypsobj.g() << '\t' << cpypsobj.getDescription() << '\t' <<;
            stream << cpypsobj.toString();

            //qDebug() << cpypsobj.toString();
        //}
    }

    mimeData->setData("application/vnd.text.list", encodedData);

    return mimeData;
}

bool PSCDP::LOMTableModel::canDropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);

    if (!data->hasFormat("application/vnd.text.list"))
        return false;

    if (column > 0)
        return false;

    return true;
}

bool PSCDP::LOMTableModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    if (action == Qt::IgnoreAction)
        return true;

    int beginRow;

    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;

    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;
        ++rows;
    }

    PSObject cpypsobj;
    foreach (const QString text, newItems) {
        cpypsobj.fromString(text);
        insertPSObject(beginRow, cpypsobj);
        beginRow++;
    }

    return true;
}

Qt::ItemFlags PSCDP::LOMTableModel::flags(const QModelIndex &index) const
{
    //if (!index.isValid() || index.column() == 1)
    //    return Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

    //return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

    Qt::ItemFlags returnFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        returnFlags |= Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    else
        returnFlags |= Qt::ItemIsDropEnabled;

    if (!index.isValid() || index.column() == 1 || index.column() == 2)
            returnFlags |= Qt::ItemIsEnabled;
    else returnFlags |= Qt::ItemIsEditable;

    return returnFlags;
}

bool PSCDP::LOMTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Replace the part being edited with the value
    if (index.isValid() && role == Qt::EditRole) {
        if (index.column() == 0) {
            LOM[index.row()].setID(value.toString());
            emit dataChanged(index, index);
            return true;
        }
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
        else if (section == 2) return QString("Type");
        else if (section == 3) return QString("Description");
        else return QString("");
    } else {
        return QString("%1").arg(section);
    }
}

bool PSCDP::LOMTableModel::insertRows(int position, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), position, position+count-1);

    /*for (int row = 0; row < count; ++row) {
        LOM.insert(position, "");
    }*/

    endInsertRows();
    return true;
}

bool PSCDP::LOMTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        LOM.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool PSCDP::LOMTableModel::insertPSObject(int row, PSObject psobject, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), row, row);

    LOM.insert(row, psobject);

    endInsertRows();
    return true;
}

bool PSCDP::LOMTableModel::appendPSObject(PSObject psobject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    LOM.insert(rowCount(), psobject);

    endInsertRows();
    return true;
}

bool PSCDP::LOMTableModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());

    LOM.clear();

    endRemoveRows();

    return true;
}
