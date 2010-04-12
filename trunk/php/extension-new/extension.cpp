#include "extension.h"
#include "mpq.h"
#include "replay.h"
#include "info.h"

PHP_MINIT_FUNCTION(starcraft2replay)
{
	//MPQ Archive
	zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "MPQArchive", mpq_archive_methods);
    mpq_archive_ce = zend_register_internal_class(&ce TSRMLS_CC);
	mpq_archive_ce->create_object = mpq_archive_create_handler;
    memcpy(&mpq_archive_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mpq_archive_object_handlers.clone_obj = NULL;

	//MPQ File
    INIT_CLASS_ENTRY(ce, "MPQFile", mpq_file_methods);
    mpq_file_ce = zend_register_internal_class(&ce TSRMLS_CC);
	mpq_file_ce->create_object = mpq_file_create_handler;
    memcpy(&mpq_file_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mpq_file_object_handlers.clone_obj = NULL;

	//Replay
    INIT_CLASS_ENTRY(ce, "Replay", replay_methods);
    replay_ce = zend_register_internal_class(&ce TSRMLS_CC);
	replay_ce->create_object = replay_create_handler;
    memcpy(&replay_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    replay_object_handlers.clone_obj = NULL;

	//PlayerDisplay
	INIT_CLASS_ENTRY(ce, "PlayerDisplay", player_display_methods);
    player_display_ce = zend_register_internal_class(&ce TSRMLS_CC);
	player_display_ce->create_object = player_display_create_handler;
    memcpy(&player_display_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    player_display_object_handlers.clone_obj = NULL;

	//Info
    INIT_CLASS_ENTRY(ce, "Info", info_methods);
    info_ce = zend_register_internal_class(&ce TSRMLS_CC);
	info_ce->create_object = info_create_handler;
    memcpy(&info_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    info_object_handlers.clone_obj = NULL;

	zval *SLOW;
    MAKE_STD_ZVAL(SLOW);
	ZVAL_LONG(SLOW, 0x00);
	zend_hash_add(&(info_ce->constants_table), "SLOW", strlen("SLOW")+1, (void *)&SLOW, sizeof(zval *), NULL);

	zval *SLOWER;
    MAKE_STD_ZVAL(SLOWER);
	ZVAL_LONG(SLOWER, 0x01);
	zend_hash_add(&(info_ce->constants_table), "SLOWER", strlen("SLOWER")+1, (void *)&SLOWER, sizeof(zval *), NULL);

	zval *NORMAL;
    MAKE_STD_ZVAL(NORMAL);
	ZVAL_LONG(NORMAL, 0x02);
	zend_hash_add(&(info_ce->constants_table), "NORMAL", strlen("NORMAL")+1, (void *)&NORMAL, sizeof(zval *), NULL);

	zval *FAST;
    MAKE_STD_ZVAL(FAST);
	ZVAL_LONG(FAST, 0x03);
	zend_hash_add(&(info_ce->constants_table), "FAST", strlen("FAST")+1, (void *)&FAST, sizeof(zval *), NULL);

	zval *FASTER;
    MAKE_STD_ZVAL(FASTER);
	ZVAL_LONG(FASTER, 0x04);
	zend_hash_add(&(info_ce->constants_table), "FASTER", strlen("FASTER")+1, (void *)&FASTER, sizeof(zval *), NULL);


    return SUCCESS;
}

/* compiled module information */
zend_module_entry starcraft2replay_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_STARCRAFT2REPLAY_EXTNAME,
    NULL,        /* Functions */
    PHP_MINIT(starcraft2replay), /* MINIT */
    NULL,        /* MSHUTDOWN */
    NULL,        /* RINIT */
    NULL,        /* RSHUTDOWN */
    ZEND_MINFO(starcraft2replay), /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_STARCRAFT2REPLAY_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

/* implement standard "stub" routine to introduce ourselves to Zend */
//#ifdef COMPILE_DL_STARCRAFT2REPLAY
extern "C" {
ZEND_GET_MODULE(starcraft2replay)
}
//#endif

ZEND_MINFO_FUNCTION(starcraft2replay)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Stacraft 2 Replay");
	php_info_print_table_row(2, "Version:", "0.0");
	php_info_print_table_end();
}