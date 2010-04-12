#ifndef PHP_INFO_H
#define PHP_INFO_H

#include "zend_include.h"
#include "sc2replay/info.h"

//PlayerDisplay
extern zend_object_handlers player_display_object_handlers;

struct player_display_object {
    zend_object std;
};

zend_class_entry *player_display_ce;
extern function_entry player_display_methods[];

void player_display_free_storage(void *object TSRMLS_DC);
zend_object_value player_display_create_handler(zend_class_entry *type TSRMLS_DC);

PHP_METHOD(PlayerDisplay, __construct);

//Info
extern zend_object_handlers info_object_handlers;

struct info_object {
    zend_object std;
	const sc2replay::Info *info;
};

zend_class_entry *info_ce;
extern function_entry info_methods[];

void info_free_storage(void *object TSRMLS_DC);
zend_object_value info_create_handler(zend_class_entry *type TSRMLS_DC);

PHP_METHOD(Info, __construct);

PHP_METHOD(Info, load);

PHP_METHOD(Info, getPlayerNames);
PHP_METHOD(Info, getNumberOfPlayers);
PHP_METHOD(Info, getNumberOfSlots);
PHP_METHOD(Info, getMapFilename);
PHP_METHOD(Info, getMapName);
PHP_METHOD(Info, getSpeed);
PHP_METHOD(Info, getAllianceLocked);
PHP_METHOD(Info, getNumberOfPlayerDisplays);
PHP_METHOD(Info, getPlayerDisplays);
PHP_METHOD(Info, getBufferSize);
PHP_METHOD(Info, getBuffer);

PHP_METHOD(Info, exportDump);

#endif