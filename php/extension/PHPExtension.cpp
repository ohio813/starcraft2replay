#include "PHPExtension.h"
#include "MPQArchive.h"
#include "MPQFile.h"
#include "MPQBlock.h"

zend_function_entry MPQLibrary_functions[] = {
    {NULL, NULL, NULL}
};

zend_module_entry MPQLibrary_module_entry = {
    STANDARD_MODULE_HEADER,
    "MPQ Library",
    MPQLibrary_functions,
    ZEND_MINIT(libmpq_startup),
	ZEND_MSHUTDOWN(libmpq_shutdown),
	NULL, NULL,
	ZEND_MINFO(libmpq_info),
    NO_VERSION_YET, STANDARD_MODULE_PROPERTIES
};

/* implement standard "stub" routine to introduce ourselves to Zend */
ZEND_GET_MODULE(MPQLibrary)

/****************************
 *   EXTENSION DEFINITIONS  *
 ****************************/

/* Function: libmpq_startup */
ZEND_MINIT_FUNCTION(libmpq_startup) {
	int32_t retval = 0;
	
	//Init libmpq
	retval = libmpq__init();

	zend_class_entry ce;

	//Register MPQArchive
    INIT_CLASS_ENTRY(ce, "MPQArchive", mpqarchive_methods);
    mpqarchive_ce = zend_register_internal_class(&ce TSRMLS_CC);

    mpqarchive_ce->create_object = mpqarchive_create_handler;
    memcpy((void *)&mpqarchive_object_handlers,
        (void *)zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mpqarchive_object_handlers.clone_obj = NULL;

	//Register MPQFile
    INIT_CLASS_ENTRY(ce, "MPQFile", mpqfile_methods);
    mpqfile_ce = zend_register_internal_class(&ce TSRMLS_CC);

    mpqfile_ce->create_object = mpqfile_create_handler;
    memcpy((void *)&mpqfile_object_handlers,
        (void *)zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mpqfile_object_handlers.clone_obj = NULL;

	//Register MPQBlock
    INIT_CLASS_ENTRY(ce, "MPQBlock", mpqblock_methods);
    mpqblock_ce = zend_register_internal_class(&ce TSRMLS_CC);

    mpqblock_ce->create_object = mpqblock_create_handler;
    memcpy((void *)&mpqblock_object_handlers,
        (void *)zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mpqblock_object_handlers.clone_obj = NULL;
	
	//Return
	if(retval == 0)
		return SUCCESS;
	else
		return FAILURE;
}

/* Function: libmpq_shutdown */
ZEND_MSHUTDOWN_FUNCTION(libmpq_shutdown) {
	int32_t retval = 0;
	
	retval = libmpq__shutdown();
	
	if(retval == 0)
		return SUCCESS;
	else
		return FAILURE;
}

/* Function: libmpq_info */
ZEND_MINFO_FUNCTION(libmpq_info)
{
       php_info_print_table_start();
       php_info_print_table_row(2, "libmpq version", libmpq__version());
       php_info_print_table_end();
}


