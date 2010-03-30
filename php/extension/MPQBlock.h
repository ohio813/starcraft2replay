#pragma once
#ifndef MPQBLOCK_H
#define MPQBLOCK_H

#include "Includes.h"

//MPQBlock (not implemented)
PHP_METHOD(MPQBlock, __construct);
PHP_METHOD(MPQBlock, __destruct);
PHP_METHOD(MPQBlock, getPackedSize);
PHP_METHOD(MPQBlock, getUnpackedSize);
PHP_METHOD(MPQBlock, getOffset);
PHP_METHOD(MPQBlock, Seed);
PHP_METHOD(MPQBlock, Read);

extern zend_object_handlers mpqblock_object_handlers;

struct mpqblock_object {
    zend_object std;
	mpq_archive_s *archive;
	uint32_t fileNumber;
};

void mpqblock_free_storage(void *object TSRMLS_DC);

zend_object_value mpqblock_create_handler(zend_class_entry *type TSRMLS_DC);

extern zend_class_entry *mpqblock_ce;

extern function_entry mpqblock_methods[];

#endif