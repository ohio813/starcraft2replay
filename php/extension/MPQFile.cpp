#include "MPQArchive.h"
#include "MPQFile.h"

zend_object_handlers mpqfile_object_handlers;

void mpqfile_free_storage(void *object TSRMLS_DC)
{
    mpqfile_object *obj = (mpqfile_object *)object;
    //delete obj->archive; 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value mpqfile_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    mpqfile_object *obj = (mpqfile_object *)emalloc(sizeof(mpqfile_object));
    memset(obj, 0, sizeof(mpqfile_object));
    obj->std.ce = type;
	obj->ready = false;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        mpqfile_free_storage, NULL TSRMLS_CC);
    retval.handlers = &mpqfile_object_handlers;

    return retval;
}

zend_class_entry *mpqfile_ce;

function_entry mpqfile_methods[] = {
    PHP_ME(MPQFile,  __construct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(MPQFile,  __destruct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
	PHP_ME(MPQFile,  getPackedSize,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  getUnpackedSize,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  getOffset,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  getBlocks,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  getEncrypted,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  getCompressed,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  getImploded,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  getFilename,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
	PHP_ME(MPQFile,  getNumber,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
	PHP_ME(MPQFile,  Read,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQFile,  isReady,     NULL, ZEND_ACC_PUBLIC) //Temporary
    {NULL, NULL, NULL}
};

//MPQ FILE FUNCTION  DEFINITIONS

PHP_METHOD(MPQFile, __construct)
{
	//Error code
	int32_t errorCode = LIBMPQ_SUCCESS;

	//Arguments
	zval *obj;
	uint32_t fileNumber = 0;

	//Parse arguments
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                              "Ol", &obj, mpqarchive_ce, &fileNumber) == FAILURE){
        zend_error(E_ERROR, "Bad parameters!");
		RETURN_NULL();
    }

	//Retrieve archive and file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
 	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(obj TSRMLS_CC);
	
	//If archive is ready
	if(archive->ready)
	{
		//Try to get number of files
		uint32_t numFiles = 0;
		errorCode = libmpq__archive_files(archive->archive, &numFiles);

		//If file number is correct
		if(errorCode == 0 && (fileNumber >= 0 && fileNumber < numFiles))
		{
			//File is ready
			file->archive = archive->archive;
			file->fileNumber = fileNumber;
			file->ready = true;
			RETURN_TRUE;
		}else
		{
			zend_error(E_WARNING, "Failed to open file.");
			RETURN_NULL();
		}
	}else
	{
		zend_error(E_WARNING, "Archive not open.");
		RETURN_NULL();
	}
}

PHP_METHOD(MPQFile, __destruct)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to close file.");
		RETURN_NULL();
	}
}
PHP_METHOD(MPQFile, getPackedSize)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	off_t packedSize = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready, get packed size
	if(file->ready) {
		errorCode = libmpq__file_packed_size(file->archive, file->fileNumber, &packedSize);
	} else {
		zend_error(E_WARNING, "MPQ File is not open.");
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

PHP_METHOD(MPQFile, getUnpackedSize)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	off_t unpackedSize = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready, get unpacked size
	if(file->ready) {
		errorCode = libmpq__file_unpacked_size(file->archive, file->fileNumber, &unpackedSize);
	} else {
		zend_error(E_WARNING, "MPQ File is not open.");
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

PHP_METHOD(MPQFile, getOffset)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	off_t offset = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready, get unpacked size
	if(file->ready) {
		errorCode = libmpq__file_offset(file->archive, file->fileNumber, &offset);
	} else {
		zend_error(E_WARNING, "MPQ File is not open.");
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

PHP_METHOD(MPQFile, getBlocks)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	uint32_t blocks = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready, get unpacked size
	if(file->ready) {
		errorCode = libmpq__file_blocks(file->archive, file->fileNumber, &blocks);
	} else {
		zend_error(E_WARNING, "MPQ File is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get blocks.");
		RETURN_NULL();
	} else {
		RETURN_LONG(blocks);
	}
}

PHP_METHOD(MPQFile, getEncrypted)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	uint32_t encrypted = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready, get unpacked size
	if(file->ready) {
		errorCode = libmpq__file_encrypted(file->archive, file->fileNumber, &encrypted);
	} else {
		zend_error(E_WARNING, "MPQ File is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get encrypted.");
		RETURN_NULL();
	} else {
		RETURN_LONG(encrypted);
	}
}

PHP_METHOD(MPQFile, getCompressed)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	uint32_t compressed = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready, get unpacked size
	if(file->ready) {
		errorCode = libmpq__file_compressed(file->archive, file->fileNumber, &compressed);
	} else {
		zend_error(E_WARNING, "MPQ File is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get compressed.");
		RETURN_NULL();
	} else {
		RETURN_LONG(compressed);
	}
}

PHP_METHOD(MPQFile, getImploded)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	uint32_t imploded = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready, get unpacked size
	if(file->ready) {
		errorCode = libmpq__file_imploded(file->archive, file->fileNumber, &imploded);
	} else {
		zend_error(E_WARNING, "MPQ File is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get imploded.");
		RETURN_NULL();
	} else {
		RETURN_LONG(imploded);
	}
}

PHP_METHOD(MPQFile, getFilename)
{
	/*uint32_t errorCode = 0;

	zval *obj;
	size_t filename_length = 30;
	char *filename = new char[filename_length];
	uint32_t fileNumber;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                              "Ol", &obj, mpqarchive_ce, &fileNumber) == FAILURE){
        RETURN_STRING("Bad parameters!", true);
    }

	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(obj TSRMLS_CC);	

	if(archive->ready) {
		errorCode = libmpq__file_name(archive->archive, fileNumber, filename, filename_length);
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
	}

	if(errorCode != 0) {
		zend_error(E_WARNING, "Failed to get file number.");
		RETURN_NULL();
	} else {
		RETURN_STRING(filename, 1);
	}*/

	RETURN_STRING("NOT IMPLEMENTED, LIBMPQ FUNCTION UNETESTED", 1);
}

PHP_METHOD(MPQFile, getNumber)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Arguments
	zval *obj;
	char *filename;
	size_t filename_length;

	//Return value
	uint32_t fileNumber;

	//Parse arguments
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                              "Os", &obj, mpqarchive_ce, &filename, &filename_length) == FAILURE){
        RETURN_STRING("Bad parameters!", true);
    }

	//Retrieve archive
	mpqarchive_object *archive = (mpqarchive_object *)zend_object_store_get_object(obj TSRMLS_CC);	

	//If archive is open, get number of files
	if(archive->ready) {
		errorCode = libmpq__file_number(archive->archive, filename, &fileNumber);
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
		RETURN_NULL();
	}

	//Check for errors and return
	if(errorCode != LIBMPQ_SUCCESS) {
		zend_error(E_WARNING, "Failed to get file number.");
		RETURN_NULL();
	} else {
		RETURN_LONG(fileNumber);
	}
}

PHP_METHOD(MPQFile, Read)
{
	//Error code
	uint32_t errorCode = LIBMPQ_SUCCESS;

	//Return value
	uint8_t *buffer;
	off_t unpackedSize = 0;
	off_t sizeRead = 0;

	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//If file is ready
	if(file->ready) {
		//Get size and allocate a buffer ofthat size
		errorCode = libmpq__file_unpacked_size(file->archive, file->fileNumber, &unpackedSize);
		buffer = new uint8_t[unpackedSize];
		if(errorCode != LIBMPQ_SUCCESS) {
			zend_error(E_WARNING, "Failed to get file size.");
			RETVAL_NULL();
		}

		//Read file to buffer
		errorCode = libmpq__file_read(file->archive, file->fileNumber, buffer, unpackedSize, &sizeRead);

		//Check for errors and set return value
		if(errorCode != LIBMPQ_SUCCESS) {
			zend_error(E_WARNING, "Failed to read file.");
			RETVAL_NULL();
		} else {
			RETVAL_STRINGL((char *)buffer, unpackedSize, 1);
		}

		//Delete buffer and return
		delete[] buffer;
		return;
	} else {
		zend_error(E_WARNING, "MPQ Archive is not open.");
		RETURN_NULL();
	}
}

PHP_METHOD(MPQFile, isReady)
{
	//Retrieve file
	mpqfile_object *file = (mpqfile_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

	//Return ready status
	RETURN_BOOL(file->ready);
}
