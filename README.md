# libnmea-cpp
NMEA parser library for c++ for Windows
Implemented only *GPGGA* profile

## How to Use

```
#include "nmea.h"

int main(int argc, char* argv[])
{
  auto pData = nmea::GPSDataInterface::Parse("$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76\r\n");
  if (!pData) return 1; // Invalid sentence type (profile)
  if (pData->GetValidateState() != nmea::ValidationStatus::OK) return 2; // incorrect sentence parameters
  
  return 0;
}
```

## How to Build

Just open *libnmea-cpp.sln* and press build button
