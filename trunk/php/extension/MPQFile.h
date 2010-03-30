#pragma once
#ifndef MPQFILE_H
#define MPQFILE_H

#include "Includes.h"

//MPQFile
PHP_METHOD(MPQFile, __construct);
PHP_METHOD(MPQFile, __destruct);
PHP_METHOD(MPQFile, getPackedSize);
PHP_METHOD(MPQFile, getUnpackedSize);
PHP_METHOD(MPQFile, getOffset);
PHP_METHOD(MPQFile, getBlocks);
PHP_METHOD(MPQFile, getEncrypted);
PHP_METHOD(MPQFile, getCompressed);
PHP_METHOD(MPQFile, getImploded);
PHP_METHOD(MPQFile, getFilename);
PHP_METHOD(MPQFile, getNumber);
PHP_METHOD(MPQFile, Read);
PHP_METHOD(MPQFile, isReady); //Temporary

extern zend_object_handlers mpqfile_object_handlers;

struct mpqfile_object {
    zend_object std;
	mpq_archive_s *archive;
	uint32_t fileNumber;
	bool ready;
};

void mpqfile_free_storage(void *object TSRMLS_DC);

zend_object_value mpqfile_create_handler(zend_class_entry *type TSRMLS_DC);

extern zend_class_entry *mpqfile_ce;

extern function_entry mpqfile_methods[];

#endif