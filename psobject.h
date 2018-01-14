#ifndef PSOBJECT_H
#define PSOBJECT_H

#include <QString>
#include <QList>

namespace PSCDP
{
    enum ObjectType
    {
        IO,
        Network,
        Power,
        General
    };

    class PSObject
    {
    public:
        PSObject();
        PSObject(QString id, ObjectType type, QString name, QString desc="");
        PSObject(QString id, ObjectType type, QString name, QString desc, QString layoutImgPath);

        // Accessors
        QString getID() const;
        void setID(QString id);
        ObjectType getType() const;
        void setType(ObjectType type);
        QString getName() const;
        void setName(QString name);
        QString getDescription() const;
        void setDescription(QString desc);
        QString getLayoutImgPath();
        void setLayoutImgPath(QString layoutImgPath);
        QString getSystemImgPath();
        void setSystemImgPath(QString systemImgPath);
        QString getWiringImgPath();
        void setWiringImgPath(QString wiringImgPath);
        double getHeight();
        void setHeight(double h);
        double getWidth();
        void setWidth(double w);
        QList<QString> getInputs();
        void addInput(QString i);
        QList<QString> getOutputs();
        void addOutput(QString o);

    protected:
        QString m_id;
        ObjectType m_type;
        QString m_name;
        QString m_description;
        QString m_layoutImgPath;
        QString m_systemImgPath;
        QString m_wiringImgPath;
        QList<QString> m_inputs;
        QList<QString> m_outputs;
        double m_height;
        double m_width;
    };
}

#endif // PSOBJECT_H
