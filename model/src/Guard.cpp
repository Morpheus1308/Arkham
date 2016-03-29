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
    return resident->privileges() && Resident::MayReadGuards;
}

bool Guard::mayBeWrittenBy(const Resident * const resident) const
{
    return resident->privileges() && Resident::MayWriteGuards;
}

QString Guard::className() const
{
    return "Guard";
}
