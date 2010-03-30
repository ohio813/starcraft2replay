#include "MPQBlock.h"

zend_object_handlers mpqblock_object_handlers;

void mpqblock_free_storage(void *object TSRMLS_DC)
{
    mpqblock_object *obj = (mpqblock_object *)object;
    //delete obj->archive; 

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value mpqblock_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    mpqblock_object *obj = (mpqblock_object *)emalloc(sizeof(mpqblock_object));
    memset(obj, 0, sizeof(mpqblock_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        mpqblock_free_storage, NULL TSRMLS_CC);
    retval.handlers = &mpqblock_object_handlers;

    return retval;
}

zend_class_entry *mpqblock_ce;

function_entry mpqblock_methods[] = {
	PHP_ME(MPQBlock, __construct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(MPQBlock, __destruct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
	PHP_ME(MPQBlock, getPackedSize,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQBlock, getUnpackedSize,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQBlock, getOffset,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQBlock, Seed,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(MPQBlock, Read,     NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

//MPQ BLOCK FUNCTION DEFINITIONS

PHP_METHOD(MPQBlock, __construct)
{
}

PHP_METHOD(MPQBlock, __destruct)
{
}

PHP_METHOD(MPQBlock, getPackedSize)
{
	RETURN_STRING("NOT IMPLEMENTED", 1);
}

PHP_METHOD(MPQBlock, getUnpackedSize)
{
	RETURN_STRING("NOT IMPLEMENTED", 1);
}

PHP_METHOD(MPQBlock, getOffset)
{
	RETURN_STRING("NOT IMPLEMENTED", 1);
}

PHP_METHOD(MPQBlock, Seed)
{
	RETURN_STRING("NOT IMPLEMENTED", 1);
}

PHP_METHOD(MPQBlock, Read)
{
	RETURN_STRING("NOT IMPLEMENTED", 1);
}