#include "../src/Resident.h"

class MockResident : public Resident
{
    Q_OBJECT

public:
    MockResident();
    bool mayBeReadBy(Resident const * const ) const;
    bool mayBeWrittenBy(Resident const * const ) const;
    int privileges() const;
    QString className() const;
};

