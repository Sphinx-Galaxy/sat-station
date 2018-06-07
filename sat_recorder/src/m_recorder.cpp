#include "m_recorder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

m_recorder::m_recorder(struct m_sat sat, const char * audio_directory)
{
    /* IMPORTANT: structure must be copied */
    this->sat = sat;

    strcpy(this->audio_directory, audio_directory);
}

m_recorder::~m_recorder()
{
    //dtor
}
const char * m_recorder::generate_filename() {
    DateTime myTime = sat.next_rising_time.AddMinutes(10);

    sprintf(filename, "%s/%s_%d%02d%02d-%02d%02d.%s", audio_directory, sat.name,
            myTime.Year(), myTime.Month(), myTime.Day(),
            myTime.Hour(), myTime.Minute(),
            "wav");

    return filename;
}

const bool m_recorder::record_sat() {
    char system_call[MAX_SYSTEM_CALL_SIZE];

	DateTime my_time = sat.next_rising_time.AddMinutes(0);
	int ppm_offset = 72;

    //The 600 seconds of recording time could be calculated if the 'struct sat' had also the declining time or passing time
    sprintf(system_call, "timeout %d rtl_fm -M fm -f %d -s %d -p %d -F 9 - | sox -t raw -r %d -es -b16 -c1 -V1 - %s rate 11025",
            600, sat.frequency, 2*sat.bandwidth, ppm_offset, 2*sat.bandwidth, generate_filename());

    printf("* System call: %s\n", system_call);

    system(system_call);

    return true;
}
