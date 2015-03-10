
namespace Phalcon;

use Phalcon\Crypt;

/**
 * Class Tracker
 * @package Nonli\Utils
 */
class Tracker
{
    /**
     * @return string
     */
    protected static function _uuid4()
    {
        var rand, i, uuid, uuid6, uuid8, uuidString;

        let rand = "";
        let i = 0;
        while i < 16 {
            let rand .= chr(mt_rand(0, 255));
            let i++;
        }
        let uuid = rand;
        let uuid8 = chr(ord(substr(uuid, 8, 1)) & 63 | 128);
        let uuid6 = chr(ord(substr(uuid, 6, 1)) & 15 | 64);

        let uuidString =
            bin2hex(substr(uuid, 0, 4)) . "-" .
            bin2hex(substr(uuid, 4, 2)) . "-" .
            bin2hex(uuid6 . substr(uuid, 7, 1)) . "-" .
            bin2hex(uuid8 . substr(uuid, 9, 1)) . "-" .
            bin2hex(substr(uuid, 10, 6));
        return uuidString;
    }

    /**
     * @param bool $withEtag
     * @param string $cookieKey
     * @param string $etagKey
     * @return bool|string
     */
    public static function init(boolean! withEtag = false, string! cookieKey = "#1dj8$=dp?.akFGa", string! etagKey = "@kSFd5hd7s.)U&-4")
    {
        var doNotTrack, cryptCookie, cryptEtag, uidCookie, uidEtag, uid;

        let doNotTrack = isset _COOKIE["dnt"] || isset _SERVER["HTTP_DNT"] ? true : false;

        if !doNotTrack {
            let cryptCookie = new Crypt();
            cryptCookie->setKey(cookieKey);
            let uidCookie = isset _COOKIE["nli"] ? cryptCookie->decryptBase64(_COOKIE["nli"]) : false;

            if withEtag == true {
                let cryptEtag = new Crypt();
                cryptEtag->setKey(etagKey);
                let uidEtag = isset _SERVER["HTTP_IF_NONE_MATCH"] ? cryptEtag->decryptBase64(_SERVER["HTTP_IF_NONE_MATCH"]) : false;
            }

            header("Cache-Control: no-cache");

            if withEtag == true {
                if uidEtag == false && uidCookie == false {
                    let uid = self::_uuid4();
                    header("ETag: " . cryptEtag->encryptBase64(uid));
                    setcookie("nli", cryptCookie->encryptBase64(uid), time() + 365 * 86400, "/");
                    return uid;
                }

                if uidEtag == true && uidCookie == false {
                    setcookie("nli", cryptCookie->encryptBase64(uidEtag), time() + 365 * 86400, "/");
                    header("HTTP/1.1 304 Not Modified");
                    return uidEtag;
                }

                if uidEtag == false && uidCookie == true {
                    header("ETag: " . cryptEtag->encryptBase64(uidCookie));
                    return uidCookie;
                }

                if uidEtag == true && uidCookie == true {
                    if uidEtag == uidCookie {
                        header("HTTP/1.1 304 Not Modified");
                    }
                    return uidCookie;
                }
            }

            if uidCookie == false {
                let uid = self::_uuid4();
                setcookie("nli", cryptCookie->encryptBase64(uid), time() + 365 * 86400, "/");
                return uid;
            }
            setcookie("nli", _COOKIE["nli"], time() + 365 * 86400, "/");
            return uidCookie;
        }
    }
}
