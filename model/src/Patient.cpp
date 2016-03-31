#include "Patient.h"

Patient::Patient() :
    Resident()
{

}


Patient::~Patient()
{
}

bool Patient::mayBeReadBy(const Resident * const resident) const
{
    bool retval = resident->privileges() & Resident::MayReadPatients;
    return retval;
}

bool Patient::mayBeWrittenBy(const Resident * const resident) const
{
    bool retval = resident->privileges() & Resident::MayWritePatients;
    return retval;
}

int Patient::privileges() const
{
    return 0;
}

QString Patient::className() const
{
    return "Patient";
}
