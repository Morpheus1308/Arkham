#include "Alchemist.h"

Alchemist::Alchemist()
    : Resident()
{
}

Alchemist::~Alchemist()
{
}

bool Alchemist::mayBeReadBy(const Resident * const resident) const
{
    if(resident == this)
    {
        return this->privileges() & Resident::MayReadSelf;
    }

    return resident->privileges() & Resident::MayReadAlchemist;
}

bool Alchemist::mayBeWrittenBy(const Resident * const resident) const
{
    if(resident == this)
    {
        return this->privileges() & Resident::MayWriteSelf;
    }
    return resident->privileges() & Resident::MayWriteAlchemist;

}

int Alchemist::privileges() const
{
    return
            MayReadPatients
            | MayWritePatients
            | MayReadGuards
            | MayWriteGuards
            | MayReadMedicalStaff
            | MayWriteMedicalStaff
            | MayReadSelf
            | MayWriteSelf
            | MayReadAlchemist
            | MayWriteAlchemist;
}

QString Alchemist::className() const
{
    return "Alchemist";
}
