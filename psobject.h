#ifndef PSOBJECT_H
#define PSOBJECT_H

#include <QString>

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

    protected:
        QString m_id;
        ObjectType m_type;
        QString m_name;
        QString m_description;
        QString m_layoutImgPath;
        QString m_systemImgPath;
        QString m_wiringImgPath;
    };
}

#endif // PSOBJECT_H
