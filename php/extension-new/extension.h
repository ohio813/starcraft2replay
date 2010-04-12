#ifndef EXTENSION_H
#define EXTENSION_H

/* include standard header */
#include "zend_include.h"

#define PHP_STARCRAFT2REPLAY_EXTNAME "Starcraft 2 Replay"
#define PHP_STARCRAFT2REPLAY_EXTVER NO_VERSION_YET

PHP_MINIT_FUNCTION(starcraft2replay);

/* compiled module information */
extern zend_module_entry starcraft2replay_module_entry;

ZEND_MINFO_FUNCTION(starcraft2replay);

#endif