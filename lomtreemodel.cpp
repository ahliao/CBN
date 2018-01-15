/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include "lomtreeitem.h"
#include "lomtreemodel.h"

#include <QStringList>
#include <QDebug>

TreeModel::TreeModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    PSObject rootData("", "General", "Name", "Description");
    rootItem = new TreeItem(rootData);
    qDebug() << rootData.getDescription();
    setupModelData(data.split(QString("\n")), rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    /*if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();*/
    return 2;
}

PSObject TreeModel::getData(const QModelIndex &index) const
{
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    //qDebug() << item->data().getName();
    if (index.column() == 0)
        return item->data().getName();
    else if (index.column() == 1)
        return item->data().getDescription();

    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0)
            return rootItem->data().getName();
        else if (section == 1)
            return rootItem->data().getDescription();
    }

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    int position = 0;
    QString lineData = lines[number].mid(position).trimmed();
    QStringList colHeaders = lineData.split("\t", QString::SkipEmptyParts);
    qDebug() << colHeaders;

    while (number < lines.count()) {
        while (position < lines[number].length()) {
            if (lines[number].at(position) != '\t')
                break;
            position++;
        }

        QString lineData = lines[number];
        // TODO: Check if format is correct
        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::KeepEmptyParts);
            qDebug() << columnStrings;
            //qDebug() << columnStrings;
            PSObject psdata;
            for (int i = 1; i < colHeaders.size(); ++i) {
                if (colHeaders.at(i) == "Name") psdata.setName(columnStrings[i]);
                else if (colHeaders.at(i) == "Description") psdata.setDescription(columnStrings[i]);
                else if (colHeaders.at(i) == "Type") {
                    psdata.setType(columnStrings.at(i));
                } else if (colHeaders.at(i) == "Layout Image") {
                    qDebug() << "Layout Image: " << columnStrings.at(i);
                    psdata.setLayoutImgPath(columnStrings.at(i));
                }
                else if (colHeaders.at(i) == "System Image") psdata.setSystemImgPath(columnStrings.at(i));
                else if (colHeaders.at(i) == "Wiring Image") psdata.setWiringImgPath(columnStrings.at(i));
                else if (colHeaders.at(i).contains("Input")) psdata.addInput(columnStrings.at(i));
                else if (colHeaders.at(i).contains("Output")) psdata.addOutput(columnStrings.at(i));
                else if (colHeaders.at(i).contains("Height")) psdata.setHeight(columnStrings.at(i).toDouble());
                else if (colHeaders.at(i).contains("Width")) psdata.setWidth(columnStrings.at(i).toDouble());
            }

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(psdata, parents.last()));
        }

        ++number;
    }

    qDebug() << number;
}
