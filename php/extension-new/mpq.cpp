#include "mpq.h"

//MPQ Archive
zend_object_handlers mpq_archive_object_handlers;

function_entry mpq_archive_methods[] = {
	PHP_ME(MPQArchive,	__construct,	NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)

	PHP_ME(MPQArchive,	load,			NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQArchive,	getFile,		NULL, ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

void mpq_archive_free_storage(void *object TSRMLS_DC)
{
    mpq_archive_object *obj = (mpq_archive_object *)object;
	delete obj->mpq_archive; 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value mpq_archive_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    mpq_archive_object *obj = (mpq_archive_object *)emalloc(sizeof(mpq_archive_object));
    memset(obj, 0, sizeof(mpq_archive_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        mpq_archive_free_storage, NULL TSRMLS_CC);
    retval.handlers = &mpq_archive_object_handlers;

    return retval;
}

//MPQ File
zend_object_handlers mpq_file_object_handlers;

function_entry mpq_file_methods[] = {
	PHP_ME(MPQFile,	__construct,		NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)

	PHP_ME(MPQFile,	load,				NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,	getArchive,			NULL, ZEND_ACC_PUBLIC)

	PHP_ME(MPQFile,	getFileSize,		NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,	getFileName,		NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,	getFileContent,		NULL, ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

void mpq_file_free_storage(void *object TSRMLS_DC)
{
    mpq_file_object *obj = (mpq_file_object *)object;
	delete obj->mpq_file; 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value mpq_file_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    mpq_file_object *obj = (mpq_file_object *)emalloc(sizeof(mpq_file_object));
    memset(obj, 0, sizeof(mpq_file_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        mpq_file_free_storage, NULL TSRMLS_CC);
    retval.handlers = &mpq_file_object_handlers;

    return retval;
}

//MPQ Archive
PHP_METHOD(MPQArchive, __construct)
{
	sc2replay::MPQArchive *mpq_archive = NULL;
    zval *object = getThis();

    mpq_archive = new sc2replay::MPQArchive();
    mpq_archive_object *obj = (mpq_archive_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->mpq_archive = mpq_archive;
}

PHP_METHOD(MPQArchive, load)
{
	char *filename;
	int filename_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
        RETURN_NULL();
    }

	sc2replay::MPQArchive *mpq_archive;
    mpq_archive_object *obj = (mpq_archive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    mpq_archive = obj->mpq_archive;
    
	if (mpq_archive != NULL) {
        RETURN_BOOL(mpq_archive->load(filename));
    }

	RETURN_FALSE;
}

PHP_METHOD(MPQArchive, getFile)
{
	char *filename;
	int filename_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
        RETURN_FALSE;
    }

	sc2replay::MPQArchive *mpq_archive;
    mpq_archive_object *archive_obj = (mpq_archive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    mpq_archive = archive_obj->mpq_archive;

	if (mpq_archive != NULL) {

		zval *mpq_file_zval;

		MAKE_STD_ZVAL(mpq_file_zval);

		if(object_init_ex(mpq_file_zval, mpq_file_ce) == SUCCESS)
		{
			const sc2replay::MPQFile *mpq_file = mpq_archive->getFile(filename);
			mpq_file_object *file_obj = (mpq_file_object *)zend_object_store_get_object(mpq_file_zval TSRMLS_CC);
			file_obj->mpq_file = mpq_file;
			file_obj->mpq_archive = getThis();

			//add_property_zval(mpq_file_zval, "Archive", getThis());
			
			RETVAL_ZVAL(mpq_file_zval, NULL, NULL);
			
			return;
		}
    }

	RETURN_FALSE;
}

//MPQ File
PHP_METHOD(MPQFile, __construct)
{
	/*TODO*/
	RETURN_FALSE;
}

PHP_METHOD(MPQFile, load)
{
	/*TODO*/
	RETURN_FALSE;
}

PHP_METHOD(MPQFile, getArchive)
{
	zval *archive_zval;
	mpq_file_object *file_obj = (mpq_file_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	RETVAL_ZVAL(file_obj->mpq_archive, NULL, NULL);
}

PHP_METHOD(MPQFile, getFileSize)
{
	const sc2replay::MPQFile *mpq_file;
	mpq_file_object *file_obj = (mpq_file_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    mpq_file = file_obj->mpq_file;

	if (mpq_file != NULL) {
		RETURN_LONG(mpq_file->getFileSize());
	}

	RETURN_FALSE;
}

PHP_METHOD(MPQFile, getFileName)
{
	const sc2replay::MPQFile *mpq_file;
	mpq_file_object *file_obj = (mpq_file_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    mpq_file = file_obj->mpq_file;

	if (mpq_file != NULL) {
		RETURN_STRING(mpq_file->getFileName().c_str(), TRUE);
	}

	RETURN_FALSE;
}

PHP_METHOD(MPQFile, getFileContent)
{
	const sc2replay::MPQFile *mpq_file;
	mpq_file_object *file_obj = (mpq_file_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    mpq_file = file_obj->mpq_file;

	if (mpq_file != NULL) {
		const sc2replay::uint8_t *fileContents = mpq_file->getFileContent();

		array_init(return_value);

		for(int i = 0; i < mpq_file->getFileSize(); i++)
		{
			add_index_long(return_value, i, fileContents[i]);
		}

		return;
	}

	RETURN_FALSE;
}