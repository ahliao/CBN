#include "psobject.h"
#include <QDebug>

using namespace PSCDP;

PSCDP::PSObject::PSObject()
{
    m_id = "N/A";
    m_type ="General";
    m_name = "Uninitialized PSObject";
    m_layoutImgPath = "";
}

PSCDP::PSObject::PSObject(QString id, QString type, QString name, QString desc)
{
    m_id = id;
    m_type = type;
    m_name = name;
    m_description = desc;
    m_layoutImgPath = "";
}

PSCDP::PSObject::PSObject(QString id, QString type, QString name, QString desc, QString layoutImgPath)
{
    m_id = id;
    m_type = type;
    m_name = name;
    m_description = desc;
    m_layoutImgPath = layoutImgPath;
}

QString PSCDP::PSObject::getID() const
{
    return m_id;
}

void PSCDP::PSObject::setID(QString id)
{
    m_id = id;
}

QString PSCDP::PSObject::getType() const
{
    return m_type;
}

void PSCDP::PSObject::setType(QString type)
{
    m_type = type;
}

QString PSCDP::PSObject::getName() const
{
    return m_name;
}

void PSCDP::PSObject::setName(QString name)
{
    m_name = name;
}

QString PSCDP::PSObject::getDescription() const
{
    return m_description;
}

void PSCDP::PSObject::setDescription(QString desc)
{
    m_description = desc;
}

QString PSCDP::PSObject::getLayoutImgPath() const
{
    return m_layoutImgPath;
}

void PSCDP::PSObject::setLayoutImgPath(QString layoutImgPath)
{
    m_layoutImgPath = layoutImgPath;
}

QString PSCDP::PSObject::getSystemImgPath() const
{
    return m_systemImgPath;
}

void PSCDP::PSObject::setSystemImgPath(QString systemImgPath)
{
    m_systemImgPath = systemImgPath;
}

QString PSCDP::PSObject::getWiringImgPath() const
{
    return m_wiringImgPath;
}

void PSCDP::PSObject::setWiringImgPath(QString wiringImgPath)
{
    m_wiringImgPath = wiringImgPath;
}

double PSCDP::PSObject::getHeight() const
{
    return m_height;
}

void PSCDP::PSObject::setHeight(double h)
{
    m_height = h;
}

double PSCDP::PSObject::getWidth() const
{
    return m_width;
}

void PSCDP::PSObject::setWidth(double w)
{
    m_width = w;
}

QList<QString> PSCDP::PSObject::getInputs() const
{
    return m_inputs;
}

void PSCDP::PSObject::addInput(QString i)
{
    m_inputs.append(i);
}

QList<QString> PSCDP::PSObject::getOutputs() const
{
    return m_outputs;
}

void PSCDP::PSObject::addOutput(QString o)
{
    m_outputs.append(o);
}

QString PSCDP::PSObject::toString() const
{
    QString str;
    str = getID() + '\t';
    str += getName() + '\t' + getDescription() + '\t';
    str += getType() + '\t';
    str += getLayoutImgPath() + '\t' + getSystemImgPath() + '\t' +
           getWiringImgPath() + '\t';
    QList<QString> inputs = getInputs();
    QList<QString> outputs = getOutputs();
    for (int i = 0; i < 4; ++i) {
        if (i < inputs.size())
            str += inputs.at(i) + '\t';
        else str += '\t';
    }
    for (int i = 0; i < 4; ++i) {
        if (i < outputs.size())
            str += outputs.at(i) + '\t';
        else str += '\t';
    }
    str += QString::number(getHeight()) + '\t' + QString::number(getWidth());

    return str;
}

bool PSCDP::PSObject::fromString(QString str)
{
    QStringList columnStrings = str.split("\t", QString::KeepEmptyParts);

    if (columnStrings.size() < 15)
        return false;

    setID(columnStrings.at(0));
    setName(columnStrings.at(1));
    setDescription(columnStrings.at(2));
    setType(columnStrings.at(3));
    setLayoutImgPath(columnStrings.at(4));
    setSystemImgPath(columnStrings.at(5));
    setWiringImgPath(columnStrings.at(6));
    if (!columnStrings.at(7).isEmpty()) addInput(columnStrings.at(7));
    if (!columnStrings.at(8).isEmpty()) addInput(columnStrings.at(8));
    if (!columnStrings.at(9).isEmpty()) addInput(columnStrings.at(9));
    if (!columnStrings.at(10).isEmpty()) addInput(columnStrings.at(10));
    if (!columnStrings.at(11).isEmpty()) addOutput(columnStrings.at(11));
    if (!columnStrings.at(12).isEmpty()) addOutput(columnStrings.at(12));
    if (!columnStrings.at(13).isEmpty()) addOutput(columnStrings.at(13));
    if (!columnStrings.at(14).isEmpty()) addOutput(columnStrings.at(14));
    setHeight(columnStrings.at(15).toDouble());
    setWidth(columnStrings.at(16).toDouble());

    return true;
}

bool PSCDP::PSObject::fromString(QStringList columnStrings)
{
    //qDebug() << columnStrings.size();
    if (columnStrings.size() < 9)
        return false;

    setName(columnStrings.at(0));
    setDescription(columnStrings.at(1));
    setType(columnStrings.at(2));
    setLayoutImgPath(columnStrings.at(3));
    setSystemImgPath(columnStrings.at(4));
    setWiringImgPath(columnStrings.at(5));
    addInput(columnStrings.at(6));
    addOutput(columnStrings.at(7));
    setHeight(columnStrings.at(8).toDouble());
    setWidth(columnStrings.at(9).toDouble());

    return true;
}
