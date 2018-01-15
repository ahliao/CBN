#ifndef PSOBJECT_H
#define PSOBJECT_H

#include <QString>
#include <QList>

namespace PSCDP
{
    class PSObject
    {
    public:
        PSObject();
        PSObject(QString id, QString type, QString name, QString desc="");
        PSObject(QString id, QString type, QString name, QString desc, QString layoutImgPath);

        // Accessors
        QString getID() const;
        void setID(QString id);
        QString getType() const;
        void setType(QString type);
        QString getName() const;
        void setName(QString name);
        QString getDescription() const;
        void setDescription(QString desc);
        QString getLayoutImgPath() const;
        void setLayoutImgPath(QString layoutImgPath);
        QString getSystemImgPath() const;
        void setSystemImgPath(QString systemImgPath);
        QString getWiringImgPath() const;
        void setWiringImgPath(QString wiringImgPath);
        double getHeight() const;
        void setHeight(double h);
        double getWidth() const;
        void setWidth(double w);
        QList<QString> getInputs() const;
        void addInput(QString i);
        QList<QString> getOutputs() const;
        void addOutput(QString o);

        QString toString() const;
        bool fromString(QString str);
        bool fromString(QStringList columnStrings);

    protected:
        QString m_id;
        QString m_type;
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
