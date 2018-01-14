#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include "psobject.h"

using namespace PSCDP;

class TreeItem
{
public:
    explicit TreeItem(const PSObject &data, TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    PSObject data() const;
    int row() const;
    TreeItem *parentItem();

private:
    QList<TreeItem*> m_childItems;
    PSObject m_itemData;
    TreeItem *m_parentItem;
};

#endif // TREEITEM_H
