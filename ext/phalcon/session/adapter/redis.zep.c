
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


/**
 * Phalcon\Session\Adapter\Memcache
 *
 * This adapter store sessions in memcache
 *
 *<code>
 * $session = new \Phalcon\Session\Adapter\Redis(array(
 *    'uniqueId' => 'my-private-app'
 *    'host' => '127.0.0.1',
 *    'port' => 11211,
 *    'persistent' => TRUE,
 *    'lifetime' => 3600,
 *    'prefix' => 'my_'
 * ));
 *
 * $session->start();
 *
 * $session->set('var', 'some-value');
 *
 * echo $session->get('var');
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Session_Adapter_Redis) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Session\\Adapter, Redis, phalcon, session_adapter_redis, phalcon_session_adapter_ce, phalcon_session_adapter_redis_method_entry, 0);

	zend_declare_property_null(phalcon_session_adapter_redis_ce, SL("_redis"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(phalcon_session_adapter_redis_ce, SL("_lifetime"), 8600, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(phalcon_session_adapter_redis_ce TSRMLS_CC, 1, phalcon_session_adapterinterface_ce);
	return SUCCESS;

}

PHP_METHOD(Phalcon_Session_Adapter_Redis, getRedis) {


	RETURN_MEMBER(this_ptr, "_redis");

}

PHP_METHOD(Phalcon_Session_Adapter_Redis, getLifetime) {


	RETURN_MEMBER(this_ptr, "_lifetime");

}

/**
 * Phalcon\Session\Adapter\Redis constructor
 *
 * @param array options
 */
PHP_METHOD(Phalcon_Session_Adapter_Redis, __construct) {

	zephir_fcall_cache_entry *_11 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_2, *_4, *_6, *_7, *_8, *_9, *_10;
	zval *options = NULL, *lifetime, *_0, *_1, *_3, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options);

	if (!options) {
		ZEPHIR_CPY_WRT(options, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(options);
	}


	if (Z_TYPE_P(options) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(options);
		array_init(options);
	}
	ZEPHIR_OBS_VAR(lifetime);
	if (zephir_array_isset_string_fetch(&lifetime, options, SS("lifetime"), 0 TSRMLS_CC)) {
		zephir_update_property_this(this_ptr, SL("_lifetime"), lifetime TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, phalcon_cache_backend_redis_ce);
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, phalcon_cache_frontend_data_ce);
	ZEPHIR_INIT_VAR(_2);
	zephir_create_array(_2, 1, 0 TSRMLS_CC);
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property_this(&_3, this_ptr, SL("_lifetime"), PH_NOISY_CC);
	zephir_array_update_string(&_2, SL("lifetime"), &_3, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 402, _2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 407, _1, options);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_redis"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_4);
	zephir_create_array(_4, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_4, this_ptr);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_STRING(_5, "open", 1);
	zephir_array_fast_append(_4, _5);
	ZEPHIR_INIT_VAR(_6);
	zephir_create_array(_6, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_6, this_ptr);
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_STRING(_5, "close", 1);
	zephir_array_fast_append(_6, _5);
	ZEPHIR_INIT_VAR(_7);
	zephir_create_array(_7, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_7, this_ptr);
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_STRING(_5, "read", 1);
	zephir_array_fast_append(_7, _5);
	ZEPHIR_INIT_VAR(_8);
	zephir_create_array(_8, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_8, this_ptr);
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_STRING(_5, "write", 1);
	zephir_array_fast_append(_8, _5);
	ZEPHIR_INIT_VAR(_9);
	zephir_create_array(_9, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_9, this_ptr);
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_STRING(_5, "destroy", 1);
	zephir_array_fast_append(_9, _5);
	ZEPHIR_INIT_VAR(_10);
	zephir_create_array(_10, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_10, this_ptr);
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_STRING(_5, "gc", 1);
	zephir_array_fast_append(_10, _5);
	ZEPHIR_CALL_FUNCTION(NULL, "session_set_save_handler", NULL, 404, _4, _6, _7, _8, _9, _10);
	zephir_check_call_status();
	ZEPHIR_CALL_PARENT(NULL, phalcon_session_adapter_redis_ce, this_ptr, "__construct", &_11, 405, options);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Phalcon_Session_Adapter_Redis, open) {


	RETURN_BOOL(1);

}

PHP_METHOD(Phalcon_Session_Adapter_Redis, close) {


	RETURN_BOOL(1);

}

/**
 * {@inheritdoc}
 *
 * @param string sessionId
 * @return mixed
 */
PHP_METHOD(Phalcon_Session_Adapter_Redis, read) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *sessionId, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sessionId);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_redis"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_lifetime"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "get", NULL, 0, sessionId, _1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * {@inheritdoc}
 *
 * @param string sessionId
 * @param string data
 */
PHP_METHOD(Phalcon_Session_Adapter_Redis, write) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *sessionId, *data, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &sessionId, &data);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_redis"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_lifetime"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "save", NULL, 0, sessionId, data, _1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 *
 * @param  string  sessionId
 * @return boolean
 */
PHP_METHOD(Phalcon_Session_Adapter_Redis, destroy) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *session_id = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &session_id);

	if (!session_id) {
		ZEPHIR_CPY_WRT(session_id, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(session_id);
	}


	if (Z_TYPE_P(session_id) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&session_id, this_ptr, "getid", NULL, 0);
		zephir_check_call_status();
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_redis"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "delete", NULL, 0, session_id);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("_started"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	RETURN_MM_BOOL(1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Phalcon_Session_Adapter_Redis, gc) {


	RETURN_BOOL(1);

}

/**
 * Sets session's options
 *
 *<code>
 *	session->setOptions(array(
 *		'uniqueId' => 'my-private-app'
 *	));
 *</code>
 *
 * @param array options
 */
PHP_METHOD(Phalcon_Session_Adapter_Redis, setOptions) {

	zval *options_param = NULL, *uniqueId, *lifetime;
	zval *options = NULL;

	zephir_fetch_params(0, 1, 0, &options_param);

	options = options_param;



	if (zephir_array_isset_string_fetch(&uniqueId, options, SS("uniqueId"), 1 TSRMLS_CC)) {
		zephir_update_property_this(this_ptr, SL("_uniqueId"), uniqueId TSRMLS_CC);
	}
	if (zephir_array_isset_string_fetch(&lifetime, options, SS("lifetime"), 1 TSRMLS_CC)) {
		zephir_update_property_this(this_ptr, SL("_lifetime"), lifetime TSRMLS_CC);
	}
	zephir_update_property_this(this_ptr, SL("_options"), options TSRMLS_CC);

}
