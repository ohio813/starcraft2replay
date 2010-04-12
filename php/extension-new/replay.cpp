#include "replay.h"
#include "info.h"
#include <iostream>
#include <fstream>

zend_object_handlers replay_object_handlers;

function_entry replay_methods[] = {
	PHP_ME(Replay,	__construct,	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)

	PHP_ME(Replay,	load,				NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Replay,	isValid,			NULL, ZEND_ACC_PUBLIC)

	PHP_ME(Replay,	getInfo,			NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Replay,	getGameEvents,		NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Replay,	getMessageEvents,	NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Replay,	getSyncEvents,		NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Replay,	getFilename,		NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Replay,	getImageBuffer,		NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Replay,	getImageSize,		NULL, ZEND_ACC_PUBLIC)

	PHP_ME(Replay, exportImage,			NULL, ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

void replay_free_storage(void *object TSRMLS_DC)
{
    replay_object *obj = (replay_object *)object;
	delete obj->replay; 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value replay_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    replay_object *obj = (replay_object *)emalloc(sizeof(replay_object));
    memset(obj, 0, sizeof(replay_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        replay_free_storage, NULL TSRMLS_CC);
    retval.handlers = &replay_object_handlers;

    return retval;
}

PHP_METHOD(Replay, __construct)
{
	char *filename;
	int filename_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
        RETURN_NULL();
    }

	sc2replay::Replay *replay = NULL;
    zval *object = getThis();

    replay = new sc2replay::Replay(filename);
    replay_object *obj = (replay_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->replay = replay;
}

PHP_METHOD(Replay, load)
{
	char *filename;
	int filename_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
        RETURN_NULL();
    }

	sc2replay::Replay *replay;
    replay_object *obj = (replay_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    replay = obj->replay;
    
	if (replay != NULL) {
        replay->load(filename);
		RETURN_TRUE;
    }

	RETURN_FALSE;
}

PHP_METHOD(Replay, isValid)
{
	const sc2replay::Replay *replay;
	replay_object *file_obj = (replay_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    replay = file_obj->replay;

	if (replay != NULL) {
		RETURN_BOOL(replay->isValid());
	}

	RETURN_FALSE;
}

PHP_METHOD(Replay, getInfo)
{
	const sc2replay::Replay *replay;
	replay_object *file_obj = (replay_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    replay = file_obj->replay;

	if (replay != NULL) {
		zval *info_zval;

		MAKE_STD_ZVAL(info_zval);

		if(object_init_ex(info_zval, info_ce) == SUCCESS)
		{
			const sc2replay::Info *info = &replay->getInfo();
			info_object *info_obj = (info_object *)zend_object_store_get_object(info_zval TSRMLS_CC);
			info_obj->info = info;
			
			RETVAL_ZVAL(info_zval, NULL, NULL);
			
			return;
		}
    }

	RETURN_FALSE;
}

PHP_METHOD(Replay, getGameEvents)
{
	RETURN_STRING("Not implemented", TRUE);
}

PHP_METHOD(Replay, getMessageEvents)
{
	RETURN_STRING("Not implemented", TRUE);
}

PHP_METHOD(Replay, getSyncEvents)
{
	RETURN_STRING("Not implemented", TRUE);
}

PHP_METHOD(Replay, getFilename)
{
	const sc2replay::Replay *replay;
	replay_object *file_obj = (replay_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    replay = file_obj->replay;

	if (replay != NULL) {
		RETURN_STRING(replay->getFilename().c_str(), TRUE);
	}

	RETURN_FALSE;
}

PHP_METHOD(Replay, getImageBuffer)
{
	std::string retval;

	const sc2replay::Replay *replay;
	replay_object *file_obj = (replay_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    replay = file_obj->replay;

	if (replay != NULL) {
		const sc2replay::uint8_t *buffer = replay->getImageBuffer();
		for(int i = 0; i < replay->getImageSize(); i++)
		{
			retval.append(1, buffer[i]);
		}

		RETURN_STRINGL(retval.c_str(), replay->getImageSize(), TRUE);
	}

	RETURN_FALSE;
}

PHP_METHOD(Replay, getImageSize)
{
	const sc2replay::Replay *replay;
	replay_object *file_obj = (replay_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    replay = file_obj->replay;

	if (replay != NULL) {
		RETURN_LONG(replay->getImageSize());
	}

	RETURN_FALSE;
}

PHP_METHOD(Replay, exportImage)
{
	char *filename;
	int filename_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
        RETURN_NULL();
    }

	const sc2replay::Replay *replay;
	replay_object *file_obj = (replay_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    replay = file_obj->replay;

	if (replay != NULL) {
		std::fstream imageFile(filename, (std::ios_base::out | std::ios_base::binary));

		if(imageFile.is_open())
		{
			const sc2replay::uint8_t *buffer = replay->getImageBuffer();
			for(int i = 0; i < replay->getImageSize(); i++)
			{
				imageFile << buffer[i];
			}

			imageFile.close();

			RETURN_TRUE;
		}
	}

	RETURN_FALSE;
}