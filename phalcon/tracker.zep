
/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */

namespace Phalcon;

use Phalcon\Crypt;

/**
 * Phalcon\Http\Cookie
 *
 * Provide OO wrappers to manage a HTTP cookie
 */
class Tracker
{

    protected static function _uuid4()
    {
        var rand, i, uuid, uuid6, uuid8, uuidString;

        // generate random fields
        let rand = "";
        let i = 0;
        while i < 16 {
            let rand .= chr(mt_rand(0, 255));
            let i++;
        }
        let uuid = rand;
        // set variant
        let uuid8 = chr(ord(substr(uuid, 8, 1)) & 63 | 128);
        // set version
        let uuid6 = chr(ord(substr(uuid, 6, 1)) & 15 | 64);

        // Optimize the most common use
        let uuidString =
            bin2hex(substr(uuid, 0, 4)) . "-" .
            bin2hex(substr(uuid, 4, 2)) . "-" .
            bin2hex(uuid6 . substr(uuid, 7, 1)) . "-" .
            bin2hex(uuid8 . substr(uuid, 9, 1)) . "-" .
            bin2hex(substr(uuid, 10, 6));
        return uuidString;
    }

    public static function init(boolean! withEtag = true, contentType = null, string! cookieKey = "#1dj8$=dp?.akFGa", string! etagKey = "@kSFd5hd7s.)U&-4")
    {
        var cryptCookie, cryptEtag, uidCookie, uidEtag, uid, ifNoneMatch, cookieUid;
        let cryptCookie = new Crypt();
        cryptCookie->setKey(cookieKey);
        let uidCookie = false;
        if fetch cookieUid, _COOKIE["uid"] {
            let uidCookie = cryptCookie->decryptBase64(cookieUid);
        }
        if withEtag {
            let cryptEtag = new Crypt();
            cryptEtag->setKey(etagKey);
            let uidEtag = false;
            if fetch ifNoneMatch, _SERVER["HTTP_IF_NONE_MATCH"] {
                let uidEtag = cryptEtag->decryptBase64(ifNoneMatch);
            }
        }

        header("Cache-Control: private, must-revalidate, proxy-revalidate");
        if contentType !== null {
            header("Content-type: ".contentType);
        }

        if withEtag {
            if !uidEtag && !uidCookie {
                let uid = self::_uuid4();
                header("ETag: " . cryptEtag->encryptBase64(uid));
                setcookie("uid", cryptCookie->encryptBase64(uid), time() + 365 * 86400, "/");
                return uid;
            }

            if (uidEtag && !uidCookie) {
                setcookie("uid", cryptCookie->encryptBase64(uidEtag), time() + 365 * 86400, "/");
                header("HTTP/1.1 304 Not Modified");
                return uidEtag;
            }

            if (!uidEtag && uidCookie) {
                header("ETag: " . cryptEtag->encryptBase64(uidCookie));
                return uidCookie;
            }

            if (uidEtag && uidCookie) {
                header("HTTP/1.1 304 Not Modified");
                return uidCookie;
            }
        }

        if !uidCookie {
            let uid = self::_uuid4();
            setcookie("uid", cryptCookie->encryptBase64(uid), time() + 365 * 86400, "/");
            return uid;
        }
        return uidCookie;
    }
}
