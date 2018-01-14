#include "psobject.h"

using namespace PSCDP;

PSCDP::PSObject::PSObject()
{
    m_id = "N/A";
    m_type = PSCDP::General;
    m_name = "Uninitialized PSObject";
    m_layoutImgPath = "";
}

PSCDP::PSObject::PSObject(QString id, ObjectType type, QString name, QString desc)
{
    m_id = id;
    m_type = type;
    m_name = name;
    m_description = desc;
    m_layoutImgPath = "";
}

PSCDP::PSObject::PSObject(QString id, ObjectType type, QString name, QString desc, QString layoutImgPath)
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

ObjectType PSCDP::PSObject::getType() const
{
    return m_type;
}

void PSCDP::PSObject::setType(ObjectType type)
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

QString PSCDP::PSObject::getLayoutImgPath()
{
    return m_layoutImgPath;
}

void PSCDP::PSObject::setLayoutImgPath(QString layoutImgPath)
{
    m_layoutImgPath = layoutImgPath;
}

QString PSCDP::PSObject::getSystemImgPath()
{
    return m_systemImgPath;
}

void PSCDP::PSObject::setSystemImgPath(QString systemImgPath)
{
    m_systemImgPath = systemImgPath;
}

QString PSCDP::PSObject::getWiringImgPath()
{
    return m_wiringImgPath;
}

void PSCDP::PSObject::setWiringImgPath(QString wiringImgPath)
{
    m_wiringImgPath = wiringImgPath;
}

double PSCDP::PSObject::getHeight()
{
    return m_height;
}

void PSCDP::PSObject::setHeight(double h)
{
    m_height = h;
}

double PSCDP::PSObject::getWidth()
{
    return m_width;
}

void PSCDP::PSObject::setWidth(double w)
{
    m_width = w;
}

QList<QString> PSCDP::PSObject::getInputs()
{
    return m_inputs;
}

void PSCDP::PSObject::addInput(QString i)
{
    m_inputs.append(i);
}

QList<QString> PSCDP::PSObject::getOutputs()
{
    return m_outputs;
}

void PSCDP::PSObject::addOutput(QString o)
{
    m_outputs.append(o);
}
