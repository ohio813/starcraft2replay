#include "info.h"
#include <iostream>
#include <fstream>

//PlayerDisplay
zend_object_handlers player_display_object_handlers;

function_entry player_display_methods[] = {
	PHP_ME(PlayerDisplay, __construct,	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)

	{NULL, NULL, NULL}
};

PHP_METHOD(PlayerDisplay, __construct)
{
	char *name, *race, *color;
	int name_len, race_len, color_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &name, &name_len, &race, &race_len, &color, &color_len) == FAILURE) {
        RETURN_NULL();
    }

	add_property_stringl(getThis(), "name", name, name_len, TRUE);
	add_property_stringl(getThis(), "race", race, race_len, TRUE);
	add_property_stringl(getThis(), "color", color, color_len, TRUE);
}

void player_display_free_storage(void *object TSRMLS_DC)
{
    player_display_object *obj = (player_display_object *)object;
	//delete obj->info;

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value player_display_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    player_display_object *obj = (player_display_object *)emalloc(sizeof(player_display_object));
    memset(obj, 0, sizeof(player_display_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        player_display_free_storage, NULL TSRMLS_CC);
    retval.handlers = &player_display_object_handlers;
	
    return retval;
}

//Info
zval *info_constants_array;
zend_object_handlers info_object_handlers;

function_entry info_methods[] = {
	PHP_ME(Info, __construct,					NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)

	PHP_ME(Info, load,							NULL, ZEND_ACC_PUBLIC)

	PHP_ME(Info, getPlayerNames,				NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getNumberOfPlayers,			NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getNumberOfSlots,				NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getMapFilename,				NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getMapName,					NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getSpeed,						NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getAllianceLocked,				NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getNumberOfPlayerDisplays,		NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getPlayerDisplays,				NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getBufferSize,					NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Info, getBuffer,						NULL, ZEND_ACC_PUBLIC)

	PHP_ME(Info, exportDump,					NULL, ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

void info_free_storage(void *object TSRMLS_DC)
{
    info_object *obj = (info_object *)object;
	//delete obj->info; 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value info_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    info_object *obj = (info_object *)emalloc(sizeof(info_object));
    memset(obj, 0, sizeof(info_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        info_free_storage, NULL TSRMLS_CC);
    retval.handlers = &info_object_handlers;
	
    return retval;
}

PHP_METHOD(Info, __construct)
{
	sc2replay::Info *info = NULL;
    zval *object = getThis();

    info = new sc2replay::Info();
    info_object *obj = (info_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->info = info;
}

PHP_METHOD(Info, load)
{
	/*TODO*/
	RETURN_STRING("Not implemented", TRUE);
}

PHP_METHOD(Info, getPlayerNames)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		sc2replay::Info::PlayerNames names = info->getPlayerNames();
		
		array_init(return_value);

		for (sc2replay::Info::PlayerNames::iterator it = names.begin(); it < names.end(); it++)
		{
			add_next_index_string(return_value, it->c_str(), TRUE);
		}

		return;
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getNumberOfPlayers)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_LONG(info->getNumberOfPlayers());
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getNumberOfSlots)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_LONG(info->getNumberOfSlots());
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getMapFilename)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_STRING(info->getMapFilename().c_str(), TRUE);
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getMapName)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_STRING(info->getMapName().c_str(), TRUE);
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getSpeed)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_LONG(info->getSpeed());
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getAllianceLocked)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_BOOL(info->getAllianceLocked());
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getNumberOfPlayerDisplays)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_LONG(info->getNumberOfPlayerDisplays());
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getPlayerDisplays)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		sc2replay::Info::PlayerDisplays displays = info->getPlayerDisplays();

		array_init(return_value);

		zval *functionName;
		MAKE_STD_ZVAL(functionName);
		ZVAL_STRING(functionName, "__construct", TRUE);
		
		for(sc2replay::Info::PlayerDisplays::iterator it = displays.begin(); it < displays.end(); it++)
		{
			zval *display;
			MAKE_STD_ZVAL(display);
			if(object_init_ex(display, player_display_ce) == FAILURE)
			{
				//TODO
			}
			
			char *name = const_cast<char *>(it->name.c_str());
			add_property_stringl(display, "name", name, it->name.size(), TRUE);

			char *race = const_cast<char *>(it->race.c_str());
			add_property_stringl(display, "race", race, it->race.size(), TRUE);

			char *color = const_cast<char *>(it->color.c_str());
			add_property_stringl(display, "color", color, it->color.size(), TRUE);

			add_next_index_zval(return_value, display);
		}

		return;
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getBufferSize)
{
	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		RETURN_LONG(info->getBufferSize());
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, getBuffer)
{
	std::string retval;

	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		const sc2replay::uint8_t *buffer = info->getBuffer();
		for(int i = 0; i < info->getBufferSize(); i++)
		{
			retval.append(1, buffer[i]);
		}

		RETURN_STRINGL(retval.c_str(), info->getBufferSize(), TRUE);
	}

	RETURN_FALSE;
}

PHP_METHOD(Info, exportDump)
{
	char *filename;
	int filename_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
        RETURN_NULL();
    }

	const sc2replay::Info *info;
	info_object *file_obj = (info_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    info = file_obj->info;

	if (info != NULL) {
		std::fstream dumpFile(filename, (std::ios_base::out | std::ios_base::binary));

		if(dumpFile.is_open())
		{
			const sc2replay::uint8_t *buffer = info->getBuffer();
			for(int i = 0; i < info->getBufferSize(); i++)
			{
				dumpFile << buffer[i];
			}

			dumpFile.close();

			RETURN_TRUE;
		}
	}

	RETURN_FALSE;
}