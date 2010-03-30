#pragma once
#ifndef PHPEXTENSION_H
#define PHPEXTENSION_H

#include "Includes.h"

/* declaration of functions to be exported */
/* Startup & Shutdown */
ZEND_MINIT_FUNCTION(libmpq_startup);
ZEND_MSHUTDOWN_FUNCTION(libmpq_shutdown);

/* Info */
ZEND_MINFO_FUNCTION(libmpq_info);

#endif