#include "MedicalStaff.h"

MedicalStaff::MedicalStaff()
    : Resident()
{
}

MedicalStaff::~MedicalStaff()
{
}

bool MedicalStaff::mayBeReadBy(const Resident * const resident) const
{
    if(resident == this)
    {
        return this->privileges() & Resident::MayReadSelf;
    }

    bool retval = resident->privileges() & Resident::MayReadMedicalStaff;
    return retval;
}

bool MedicalStaff::mayBeWrittenBy(const Resident * const resident) const
{
    if(resident == this)
    {
        return this->privileges() & Resident::MayWriteSelf;
    }
    bool retval = resident->privileges() & Resident::MayWriteMedicalStaff;
    return retval;
}


int MedicalStaff::privileges() const
{
    return
            MayReadPatients
            | MayWritePatients
            | MayReadGuards
            | MayReadMedicalStaff
            | MayReadSelf
            | MayWriteSelf;

}

QString MedicalStaff::className() const
{
    return "MedicalStaff";
}
