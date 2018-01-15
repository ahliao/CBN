#include "scheduletablemodel.h"
#include <QDebug>
#include <QComboBox>

using namespace PSCDP;

PSCDP::ScheduleTableModel::ScheduleTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int PSCDP::ScheduleTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return scheduleList.size();
}

int PSCDP::ScheduleTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 11;
}

QVariant PSCDP::ScheduleTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= scheduleList.size())
        return QVariant();

    if (role == Qt::DisplayRole) {
        QStringList row = scheduleList.at(index.row());
        return row.at(index.column());
    } /*else if (role == Qt::EditRole) {
        PSObject psobj = LOM.at(index.row());
        if (index.column() == 0) return psobj.getID();
        else if (index.column() == 1) return psobj.getName();
        else if (index.column() == 2) return psobj.getType();
        else return psobj.getDescription();
    } */else {
        return QVariant();
    }
    return QVariant();
}

Qt::DropActions PSCDP::ScheduleTableModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList PSCDP::ScheduleTableModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

QMimeData *PSCDP::ScheduleTableModel::mimeData(const QModelIndexList &indexes) const
{
    QList<int> selectedRows;
    foreach (const QModelIndex &index, indexes) {
        if (index.isValid() && selectedRows.contains(index.row())) continue;
        else selectedRows.append(index.row());
    }

    QMimeData *mimeData = new QMimeData();
    /*QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const int &row, selectedRows) {
        PSObject cpypsobj = getPSObject(row);
        stream << cpypsobj.toString();
    }

    mimeData->setData("application/vnd.text.list", encodedData);*/

    return mimeData;
}

bool PSCDP::ScheduleTableModel::canDropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);

    /*if (!data->hasFormat("application/vnd.text.list"))
        return false;

    if (column > 0)
        return false;*/

    return true;
}

bool PSCDP::ScheduleTableModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    /*if (!canDropMimeData(data, action, row, column, parent))
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
    }*/

    return true;
}

Qt::ItemFlags PSCDP::ScheduleTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags returnFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        returnFlags |= Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    else
        returnFlags |= Qt::ItemIsDropEnabled;

    /*if (!index.isValid() || index.column() == 1 || index.column() == 2)
            returnFlags |= Qt::ItemIsEnabled;
    else */returnFlags |= Qt::ItemIsEditable;

    return returnFlags;
}

bool PSCDP::ScheduleTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Replace the part being edited with the value
    if (index.isValid() && role == Qt::EditRole) {
        /*if (index.column() == 0) {
            LOM[index.row()].setID(value.toString());
            emit dataChanged(index, index);
            return true;
        }
        else if (index.column() == 1) return false;
        else if (index.column() == 2) {
            LOM[index.row()].setDescription(value.toString());
            emit dataChanged(index, index);
            return true;
        }*/
        scheduleList[index.row()][index.column()] = value.toString();

        if (index.column() == 7) updateCables();

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant PSCDP::ScheduleTableModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == 0) return QString("FDB");
        else if (section == 1) return QString("BOARD");
        else if (section == 2) return QString("BOARD CONTACT");
        else if (section == 3) return QString("BOARD LABEL");
        else if (section == 4) return QString("BOARD WIRES");
        else if (section == 5) return QString("TERMINAL STRIP");
        else if (section == 6) return QString("SENSOR LABEL");
        else if (section == 7) return QString("SENSOR WIRES");
        else if (section == 8) return QString("DESCRIPTION");
        else if (section == 9) return QString("NORMAL STATE");
        else if (section == 10) return QString("ALARM STATE");
        else return QString("");
    } else {
        return QString("%1").arg(section);
    }
}

bool PSCDP::ScheduleTableModel::insertRows(int position, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), position, position+count-1);

    /*for (int row = 0; row < count; ++row) {
        LOM.insert(position, "");
    }*/

    endInsertRows();
    return true;
}

bool PSCDP::ScheduleTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        //LOM.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool PSCDP::ScheduleTableModel::generateSchedule(QString FDBName, QVector<PSObject> psobjs)
{
    // Clear the schedule
    if (rowCount() > 0) removeRows(0, rowCount());
    scheduleList.clear();

    int rowNum = 0;
    int numBoards = 0;

    m_FDBName = FDBName;
    QString boardName = FDBName + "-Board-" + ('A'+numBoards++);

    // Board variables
    QStringList boardWireColors;
    boardWireColors << "BROWN-BLACK" << "RED-BLACK" << "ORANGE-BLACK" << "YELLOW-BLACK" <<
                       "GREEN-BLACK" << "BLUE-BLACK" << "WHITE-BLACK" << "RED-WHITE";

    QStringList boardContacts;
    boardContacts << "J1-1" << "J1-2" << "J1-3" << "J1-4" <<
                     "J2-1" << "J2-2" << "J2-3" << "J2-4" <<
                     "J4-1" << "J4-2" << "J4-3" << "J4-4" <<
                     "J3-1" << "J3-2" << "J3-3" << "J3-4";

    //sensorCableColors << "WHITE-GREEN" << "BLUE-BLACK" << "RED-BLACK";

    int boardNumInputs = 16;
    int boardNumOutputs = 0;

    rowNum = 0;
    addBoard(rowNum, FDBName, boardName, boardWireColors, boardContacts, boardNumInputs, boardNumOutputs);

    //for (rowNum = 0; rowNum < psobjs.size(); ++rowNum) {
    for (PSObject psobj : psobjs) {
        QList<QString> inputs = psobj.getInputs();

        for (QString input : inputs) {
            // Add boards if past the number of inputs
            if (rowNum >= scheduleList.size()) {
                boardName = FDBName + "-Board-" + ('A'+numBoards++);
                addBoard(rowNum, FDBName, boardName, boardWireColors, boardContacts, boardNumInputs, boardNumOutputs);
            }
            scheduleList[rowNum][6] = psobj.getID().toUpper();
            scheduleList[rowNum][7] = sensorCableColors.at(0);
            scheduleList[rowNum][8] = (psobj.getID() + " - " + input).toUpper();
            scheduleList[rowNum][9] = "CLOSED - 383";
            scheduleList[rowNum][10] = "OPEN - 548";
            scheduleList[rowNum][11] = psobj.getID().toUpper();
            ++rowNum;
        }
    }

    // Determine cabling based on the colors selected
    updateCables();

    return true;
}

void PSCDP::ScheduleTableModel::addBoard(int startRow, QString FDBName, QString boardName,
                                         QStringList boardWireColors, QStringList boardContacts,
                                         int boardNumInputs, int boardNumOutputs)
{
    for (int i = 0; i < boardNumInputs; ++i) {
        QStringList row;
        row << FDBName << boardName << boardContacts.at(i%boardContacts.size()) << ("INPUT " + QString::number(i+1))
            << boardWireColors[i%boardWireColors.size()] << ("TB1-" + QString::number(i+1))
            << "SPARE" << "SPARE" << "SPARE"
            << "SPARE" << "SPARE" << "PSObject ID";
        insertRows(startRow+i, 1);
        scheduleList.append(row);
    }
}

void PSCDP::ScheduleTableModel::updateCables()
{
    // Check that the sensor cable has been set
    if (sensorCableColors.size() <= 0) return;

    int cableNum = 0;
    QStringList tempCableColors = sensorCableColors;
    for (int i = 0; i < scheduleList.size(); ++i) {
        if (scheduleList[i][6] == "SPARE") continue;
        QString cableNumStr;

        if (i == 0) {
            tempCableColors.removeAll(scheduleList.at(i).at(7));
        } if (i > 0 && scheduleList.at(i-1).at(11) == scheduleList.at(i).at(11) &&
                tempCableColors.contains(scheduleList.at(i).at(7))) {
            //++cableNum;
            tempCableColors.removeAll(scheduleList.at(i).at(7));
        } else if (i > 0) {
            ++cableNum;
            tempCableColors = sensorCableColors;
            tempCableColors.removeAll(scheduleList.at(i).at(7));
        }
        cableNumStr = QString::number(cableNum+1).rightJustified(3, '0');

        scheduleList[i][6] = scheduleList.at(i).at(11).toUpper() + "-C" + cableNumStr;
    }
}

PSCDP::ComboBoxItemDelegate::ComboBoxItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}


PSCDP::ComboBoxItemDelegate::~ComboBoxItemDelegate()
{
}


QWidget* PSCDP::ComboBoxItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // ComboBox ony in column 2
    //if (index.column() != 1)
    //    return QStyledItemDelegate::createEditor(parent, option, index);

    // Create the combobox and populate it
    QComboBox* cb = new QComboBox(parent);
    for (QString s : comboBoxItems) {
        cb->addItem(s);
    }
    return cb;
}


void PSCDP::ComboBoxItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
       // get the index of the text in the combobox that matches the current value of the itenm
       QString currentText = index.data(Qt::EditRole).toString();
       int cbIndex = cb->findText(currentText);
       // if it is valid, adjust the combobox
       if (cbIndex >= 0)
           cb->setCurrentIndex(cbIndex);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}


void PSCDP::ComboBoxItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor))
        // save the current text of the combo box as the current value of the item
        model->setData(index, cb->currentText(), Qt::EditRole);
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void PSCDP::ComboBoxItemDelegate::setItemOptions(QStringList list)
{
    comboBoxItems = list;
}
