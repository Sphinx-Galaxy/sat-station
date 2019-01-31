#ifndef M_TLE_INCLUDED
#define M_TLE_INCLUDED

#include "SGP4.h"
#include "Util.h"
#include "DateTime.h"
#include "TleException.h"
#include "Tle.h"

#define NUMBER_OF_SATS 4

//NOAA 15
static Tle noaa15_tle = {"NOAA15",
 "1 25338U 98030A   19031.60104166  .00000021  00000-0  27503-4 0  9993",
 "2 25338  98.7578  53.0372 0009486 285.6003  74.4129 14.25893213 77568"};

//NOAA 18
static Tle noaa18_tle = {"NOAA18",
 "1 28654U 05018A   19031.56927239  .00000049  00000-0  51464-4 0  9993",
 "2 28654  99.1172  76.3330 0014046 202.6829 157.3722 14.12401332706025"};
//NOAA 19
static Tle noaa19_tle = {"NOAA19",
 "1 33591U 09005A   19031.61551584  .00000068  00000-0  62314-4 0  9998",
 "2 33591  99.1686  19.4783 0014733  48.3965 311.8465 14.12331965514426"};

//Meteor
static Tle meteor_tle = {"Meteor-M2",
 "1 40069U 14037A   17300.19951363 -.00000018  00000-0  11868-4 0  9994",
 "2 40069  98.6393 352.0282 0005276 181.7278 178.3888 14.20646288171299"};

 //ISS
static Tle iss_tle = {"ISS (ZARYA)",
 "1 25544U 98067A   19031.65427531  .00001112  00000-0  24786-4 0  9993",
 "2 25544  51.6427 320.2427 0004959 336.6408 101.7160 15.53211757154041"};


#endif // M_TLE_INCLUDED
