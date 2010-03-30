#pragma once
#ifndef MPQARCHIVE_H
#define MPQARCHIVE_H

#include "Includes.h"

//MPQArchive
PHP_METHOD(MPQArchive, __construct);
PHP_METHOD(MPQArchive, __destruct);
PHP_METHOD(MPQArchive, getPackedSize);
PHP_METHOD(MPQArchive, getUnpackedSize);
PHP_METHOD(MPQArchive, getOffset);
PHP_METHOD(MPQArchive, getVersion);
PHP_METHOD(MPQArchive, getNumFiles);
PHP_METHOD(MPQArchive, isReady); //Temporary

extern zend_object_handlers mpqarchive_object_handlers;

struct mpqarchive_object {
    zend_object std;
	mpq_archive_s *archive;
	bool ready;
};

void mpqarchive_free_storage(void *object TSRMLS_DC);

zend_object_value mpqarchive_create_handler(zend_class_entry *type TSRMLS_DC);

extern zend_class_entry *mpqarchive_ce;
extern function_entry mpqarchive_methods[];

#endif