#ifndef PHP_MPQ_H
#define PHP_MPQ_H

#include "zend_include.h"
#include "sc2replay/mpq.h"

//MPQ Archive
extern zend_object_handlers mpq_archive_object_handlers;

struct mpq_archive_object {
    zend_object std;
	sc2replay::MPQArchive *mpq_archive;
};

zend_class_entry *mpq_archive_ce;
extern function_entry mpq_archive_methods[];

void mpq_archive_free_storage(void *object TSRMLS_DC);
zend_object_value mpq_archive_create_handler(zend_class_entry *type TSRMLS_DC);

PHP_METHOD(MPQArchive, __construct);

PHP_METHOD(MPQArchive, load);
PHP_METHOD(MPQArchive, getFile);

//MPQ File
extern zend_object_handlers mpq_file_object_handlers;

struct mpq_file_object {
    zend_object std;
    const sc2replay::MPQFile *mpq_file;
	zval *mpq_archive;
};

zend_class_entry *mpq_file_ce;
extern function_entry mpq_file_methods[];

void mpq_file_free_storage(void *object TSRMLS_DC);
zend_object_value mpq_file_create_handler(zend_class_entry *type TSRMLS_DC);

PHP_METHOD(MPQFile, __construct);

PHP_METHOD(MPQFile, load);
PHP_METHOD(MPQFile, getArchive);

PHP_METHOD(MPQFile, getFileSize);
PHP_METHOD(MPQFile, getFileName);
PHP_METHOD(MPQFile, getFileContent);

#endif