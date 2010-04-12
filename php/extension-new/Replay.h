#ifndef PHP_REPLAY_H
#define PHP_REPLAY_H

#include "zend_include.h"
#include "sc2replay/replay.h"

//Replay
extern zend_object_handlers replay_object_handlers;

struct replay_object {
    zend_object std;
	sc2replay::Replay *replay;
};

zend_class_entry *replay_ce;
extern function_entry replay_methods[];

void replay_free_storage(void *object TSRMLS_DC);
zend_object_value replay_create_handler(zend_class_entry *type TSRMLS_DC);

PHP_METHOD(Replay, __construct);

PHP_METHOD(Replay, load);
PHP_METHOD(Replay, isValid);

PHP_METHOD(Replay, getInfo);
PHP_METHOD(Replay, getGameEvents);
PHP_METHOD(Replay, getMessageEvents);
PHP_METHOD(Replay, getSyncEvents);
PHP_METHOD(Replay, getFilename);
PHP_METHOD(Replay, getImageBuffer);
PHP_METHOD(Replay, getImageSize);

PHP_METHOD(Replay, exportImage);

#endif