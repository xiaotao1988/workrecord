/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mytest.h"

/* If you declare any globals in php_mytest.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mytest)
*/

/* True global resources - no need for thread safety here */
static int le_mytest;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mytest.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mytest_globals, mytest_globals)
    STD_PHP_INI_ENTRY("mytest.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mytest_globals, mytest_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_mytest_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_mytest_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "mytest", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(sayhello)
{
	char *name;
	size_t name_len ;
    zval *arr ;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|a", &name , &name_len,&arr) == FAILURE) {
		return;
	}
    php_printf("hello %s\n", name);
    php_printf("name_len %d\n", name_len);
    if (Z_TYPE_P(arr) == IS_ARRAY){
        php_printf("array %s has %d elem\n",Z_ARRVAL_P(arr),zend_hash_num_elements(Z_ARRVAL_P(arr)));
        RETURN_ARR(Z_ARRVAL_P(arr));
    }
	RETURN_STR(name);

}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_mytest_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_mytest_init_globals(zend_mytest_globals *mytest_globals)
{
	mytest_globals->global_value = 0;
	mytest_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mytest)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mytest)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(mytest)
{
#if defined(COMPILE_DL_MYTEST) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mytest)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mytest)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mytest support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ mytest_functions[]
 *
 * Every user visible function must have an entry in mytest_functions[].
 */
const zend_function_entry mytest_functions[] = {
	PHP_FE(sayhello,	NULL)		/* For testing, remove later. */
	PHP_FE(confirm_mytest_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in mytest_functions[] */
};
/* }}} */

/* {{{ mytest_module_entry
 */
zend_module_entry mytest_module_entry = {
	STANDARD_MODULE_HEADER,
	"mytest",
	mytest_functions,
	PHP_MINIT(mytest),
	PHP_MSHUTDOWN(mytest),
	PHP_RINIT(mytest),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mytest),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mytest),
	PHP_MYTEST_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYTEST
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(mytest)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
