#include "Guard.h"

Guard::Guard()
    : Resident()
{
}

Guard::~Guard()
{
}

bool Guard::mayBeReadBy(const Resident * const resident) const
{
    if(resident == this)
    {
        return this->privileges() & Resident::MayReadSelf;
    }
    return resident->privileges() & Resident::MayReadGuards;
}

bool Guard::mayBeWrittenBy(const Resident * const resident) const
{
    if(resident == this)
    {
        return this->privileges() & Resident::MayReadSelf;
    }
    return resident->privileges() & Resident::MayWriteGuards;
}

int Guard::privileges() const
{
    return
            MayReadPatients
            | MayReadGuards
            | MayReadSelf
            | MayWriteSelf;
}

QString Guard::className() const
{
    return "Guard";
}
