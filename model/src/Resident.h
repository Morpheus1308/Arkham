#ifndef RESIDENT_H
#define RESIDENT_H

#include <QString>
#include <QDate>

/** A Resident is a person that resides on AA. This may be inmates, guards or other kind of personal. */
class Resident
{

public:

    enum Gender
    {
        Male = 1,
        Female,
        Hermaphrodite,
        NotSure
    };

    enum Privileges
    {
        MayReadPatients      = 0x0001,
        MayWritePatients     = 0x0002,
        MayReadGuards        = 0x0004,
        MayWriteGuards       = 0x0008,
        MayReadMedicalStaff  = 0x0010,
        MayWriteMedicalStaff = 0x0020,
        MayReadSelf          = 0x0040,
        MayWriteSelf         = 0x0080
    };

    Resident();
    Resident(const Resident &other);
    Resident& operator=(Resident &rhs);
    ~Resident();

    int id() const;

    QString name() const;
    void setName(const QString &name);

    QString title() const;
    void setTitle(const QString &title);

    int sanity() const;
    void setSanity(int sanity);

    QDate birthDate() const;
    void setBirthDate(const QDate &birthdate);

    Gender gender() const;
    void setGender(Gender gender);

    int privileges() const;
    void setPrivileges(int privileges);

    void setPassword(const QString &password);

    QString email() const;
    void setEmail(const QString &email);


    bool matchesPassword(const QString &password) const;

    virtual bool mayBeReadBy(Resident const * const resident) const = 0;
    virtual bool mayBeWrittenBy(Resident const * const resident) const = 0;
    bool mayRead(Resident const * const resident) const;
    bool mayWrite(Resident const * const resident) const;



private:
    friend class ResidentPrivate;
    class ResidentPrivate *d;
};

#endif // RESIDENT_H

