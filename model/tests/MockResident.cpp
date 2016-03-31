#include "MockResident.h"

MockResident::MockResident() : Resident()
{
}

bool MockResident::mayBeReadBy(Resident const * const ) const
{
    return false;
}

bool MockResident::mayBeWrittenBy(Resident const * const ) const
{
    return true;
}

int MockResident::privileges() const
{
    return 1;
}

QString MockResident::className() const
{
    return this->staticMetaObject.className();

}

