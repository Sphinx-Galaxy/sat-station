#ifndef M_TLE_INCLUDED
#define M_TLE_INCLUDED

#include "SGP4.h"
#include "Util.h"
#include "DateTime.h"
#include "TleException.h"
#include "Tle.h"

#define NUMBER_OF_SATS 3

/* Mach hier lieber eine Klasse daraus
* Vielleicht sogar so, dass sie ihre eigenen Berechnungsmethoden mitbringen?
* Oder bei satellite einfach zufüngen?
*/

struct m_sat {
    Tle *tle;//("NOAA 18",
    //"1 28654U 05018A   17333.82739219  .00000004  00000-0  27382-4 0  9997",
    //"2 28654  99.1692 359.9851 0013783 330.2584  29.7802 14.12358852645541");

    char name[7];
    long frequency;
    DateTime next_rising_time;
    long next_rising_time_utc;
    double elevation;
};

//NOAA 15
static Tle noaa15_tle = {"NOAA15",
 "1 25338U 98030A   18128.96469807  .00000038  00000-0  35031-4 0  9997",
 "2 25338  98.7716 145.3665 0010119 347.7970  12.2963 14.25849988 39171"};

static struct m_sat noaa15 = {&noaa15_tle,
  "NOAA15", 137620000, 0, 0};

//NOAA 18
static Tle noaa18_tle = {"NOAA18",
 "1 28654U 05018A   18128.93080935 -.00000004  00000-0  23199-4 0  9999",
 "2 28654  99.1487 163.5774 0013479 234.9687 125.0220 14.12374647668147"};

static struct m_sat noaa18 = {&noaa18_tle,
  "NOAA18", 137912500, 0, 0};

//NOAA 19
static Tle noaa19_tle = {"NOAA19",
 "1 33591U 09005A   18128.89124556  .00000078  00000-0  67495-4 0  9995",
 "2 33591  99.1392 106.1444 0015034  78.0836 282.2019 14.12276112476368"};

static struct m_sat noaa19 = {&noaa19_tle,
  "NOAA19", 137100000, 0, 0};

#endif // M_TLE_INCLUDED
