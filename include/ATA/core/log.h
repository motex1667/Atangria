/*
 * Approach taken from SMFL
 */
#ifndef ATA_LOG_H
#define ATA_LOG_H
#include "ATA/config.h"
#include <ostream>
#include <iomanip>

namespace ata
{
	ATA_API std::ostream& err();
}

#endif