#include "MPQArchive.h"

zend_object_handlers mpqarchive_object_handlers;

void mpqarchive_free_storage(void *object TSRMLS_DC)
{
    mpqarchive_object *obj = (mpqarchive_object *)object;
    //delete obj->archive; 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value mpqarchive_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    mpqarchive_object *obj = (mpqarchive_object *)emalloc(sizeof(mpqarchive_object));
    memset(obj, 0, sizeof(mpqarchive_object));
    obj->std.ce = type;
	obj->ready = false;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        mpqarchive_free_storage, NULL TSRMLS_CC);
    retval.handlers = &mpqarchive_object_handlers;

    return retval;
}

zend_class_entry *mpqarchive_ce;

function_entry mpqarchive_methods[] = {
    PHP_ME(MPQArchive,  __construct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(MPQArchive,  __destruct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
	PHP_ME(MPQArchive,  getPackedSize,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQArchive,  getUnpackedSize,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQArchive,  getOffset,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQArchive,  getVersion,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQArchive,  getNumFiles,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQArchive,  isReady,     NULL, ZEND_ACC_PUBLIC) //Temporary
    {NULL, NULL, NULL}
};

//MPQ ARCHIVE FUNCTION DEFINITIONS

PHP_METHOD(MPQArchive, __construct)
{
	//Error code
	int32_t errorCode = LIBMPQ_SUCCESS;

	//Function arguments
	char *mpq_filename;
	int mpq_filename_length;
	off_t archive_offset = -1;

	//Parse arguments
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                              "s|l", &mpq_filename, &mpq_filename_length, &archive_offset) == FAILURE){
		zend_error(E_ERROR, "Bad parameters!");
		RETURN_NULL();
    }

	//Try to open archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    errorCode = libmpq__archive_open(&archive->archive, mpq_filename, archive_offset);
	if(errorCode != LIBMPQ_SUCCESS)	{
		zend_error(E_WARNING, "Failed to open MPQ archive.");
		RETURN_NULL();
	}
	
	//Archive is open and ready
	archive->ready = true;
	RETURN_TRUE;
}

PHP_METHOD(MPQArchive, __destruct)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Retrieve archive object and close archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If archive is open, close it
	if(archive->ready) {
		errorCode = libmpq__archive_close(archive->archive);
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to close MPQ archive.");
		RETURN_NULL();
	}

	RETURN_TRUE;
}

PHP_METHOD(MPQArchive, getPackedSize)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	off_t packedSize = 0;

	//Retrieve archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If archive is open, get packed size
	if(archive->ready) {
		errorCode = libmpq__archive_packed_size(archive->archive, &packedSize);
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get packed size.");
		RETURN_NULL();
	} else {
		RETURN_LONG(packedSize);
	}
}

PHP_METHOD(MPQArchive, getUnpackedSize)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	off_t unpackedSize = 0;

	//Retrieve archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If archive is open, get unpacked size
	if(archive->ready) {
		errorCode = libmpq__archive_unpacked_size(archive->archive, &unpackedSize);
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get unpacked size.");
		RETURN_NULL();
	} else {
		RETURN_LONG(unpackedSize);
	}
}

PHP_METHOD(MPQArchive, getOffset)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	off_t offset = 0;

	//Retrieve archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If archive is open, get offset
	if(archive->ready) {
		errorCode = libmpq__archive_offset(archive->archive, &offset);
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get offset.");
		RETURN_NULL();
	} else {
		RETURN_LONG(offset);
	}
}

PHP_METHOD(MPQArchive, getVersion)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	uint32_t version = 0;

	//Retrieve archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If archive is open, get offset
	if(archive->ready) {
		errorCode = libmpq__archive_version(archive->archive, &version);
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get version.");
		RETURN_NULL();
	} else {
		//Translate version constant to human readable.
		if(version == LIBMPQ_ARCHIVE_VERSION_ONE) {
			RETURN_LONG(1);
		}else if(version == LIBMPQ_ARCHIVE_VERSION_TWO) {
			RETURN_LONG(2);
		}else {
			RETURN_LONG(-1);
		}
	}
}

PHP_METHOD(MPQArchive, getNumFiles)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	uint32_t numFiles = 0;

	//Retrieve archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If archive is open, get offset
	if(archive->ready) {
		errorCode = libmpq__archive_files(archive->archive, &numFiles);
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get number of files.");
		RETURN_NULL();
	} else {
		RETURN_LONG(numFiles);
	}
}

PHP_METHOD(MPQArchive, isReady)
{
	//Retrieve archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	
	//Return ready status
	RETURN_BOOL(archive->ready);
}