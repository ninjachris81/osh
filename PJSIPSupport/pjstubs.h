#ifndef PJSTUBS_H
#define PJSTUBS_H

#include <QDebug>

#include <string>
#include <vector>

using namespace std;

namespace pj {
typedef enum pjsip_status_code
{
    PJSIP_SC_NULL = 0,

    PJSIP_SC_TRYING = 100,
    PJSIP_SC_RINGING = 180,
    PJSIP_SC_CALL_BEING_FORWARDED = 181,
    PJSIP_SC_QUEUED = 182,
    PJSIP_SC_PROGRESS = 183,
    PJSIP_SC_EARLY_DIALOG_TERMINATED = 199,

    PJSIP_SC_OK = 200,
    PJSIP_SC_ACCEPTED = 202,
    PJSIP_SC_NO_NOTIFICATION = 204,

    PJSIP_SC_MULTIPLE_CHOICES = 300,
    PJSIP_SC_MOVED_PERMANENTLY = 301,
    PJSIP_SC_MOVED_TEMPORARILY = 302,
    PJSIP_SC_USE_PROXY = 305,
    PJSIP_SC_ALTERNATIVE_SERVICE = 380,

    PJSIP_SC_BAD_REQUEST = 400,
    PJSIP_SC_UNAUTHORIZED = 401,
    PJSIP_SC_PAYMENT_REQUIRED = 402,
    PJSIP_SC_FORBIDDEN = 403,
    PJSIP_SC_NOT_FOUND = 404,
    PJSIP_SC_METHOD_NOT_ALLOWED = 405,
    PJSIP_SC_NOT_ACCEPTABLE = 406,
    PJSIP_SC_PROXY_AUTHENTICATION_REQUIRED = 407,
    PJSIP_SC_REQUEST_TIMEOUT = 408,
    PJSIP_SC_CONFLICT = 409,
    PJSIP_SC_GONE = 410,
    PJSIP_SC_LENGTH_REQUIRED = 411,
    PJSIP_SC_CONDITIONAL_REQUEST_FAILED = 412,
    PJSIP_SC_REQUEST_ENTITY_TOO_LARGE = 413,
    PJSIP_SC_REQUEST_URI_TOO_LONG = 414,
    PJSIP_SC_UNSUPPORTED_MEDIA_TYPE = 415,
    PJSIP_SC_UNSUPPORTED_URI_SCHEME = 416,
    PJSIP_SC_UNKNOWN_RESOURCE_PRIORITY = 417,
    PJSIP_SC_BAD_EXTENSION = 420,
    PJSIP_SC_EXTENSION_REQUIRED = 421,
    PJSIP_SC_SESSION_TIMER_TOO_SMALL = 422,
    PJSIP_SC_INTERVAL_TOO_BRIEF = 423,
    PJSIP_SC_BAD_LOCATION_INFORMATION = 424,
    PJSIP_SC_USE_IDENTITY_HEADER = 428,
    PJSIP_SC_PROVIDE_REFERRER_HEADER = 429,
    PJSIP_SC_FLOW_FAILED = 430,
    PJSIP_SC_ANONIMITY_DISALLOWED = 433,
    PJSIP_SC_BAD_IDENTITY_INFO = 436,
    PJSIP_SC_UNSUPPORTED_CERTIFICATE = 437,
    PJSIP_SC_INVALID_IDENTITY_HEADER = 438,
    PJSIP_SC_FIRST_HOP_LACKS_OUTBOUND_SUPPORT = 439,
    PJSIP_SC_MAX_BREADTH_EXCEEDED = 440,
    PJSIP_SC_BAD_INFO_PACKAGE = 469,
    PJSIP_SC_CONSENT_NEEDED = 470,
    PJSIP_SC_TEMPORARILY_UNAVAILABLE = 480,
    PJSIP_SC_CALL_TSX_DOES_NOT_EXIST = 481,
    PJSIP_SC_LOOP_DETECTED = 482,
    PJSIP_SC_TOO_MANY_HOPS = 483,
    PJSIP_SC_ADDRESS_INCOMPLETE = 484,
    PJSIP_AC_AMBIGUOUS = 485,
    PJSIP_SC_BUSY_HERE = 486,
    PJSIP_SC_REQUEST_TERMINATED = 487,
    PJSIP_SC_NOT_ACCEPTABLE_HERE = 488,
    PJSIP_SC_BAD_EVENT = 489,
    PJSIP_SC_REQUEST_UPDATED = 490,
    PJSIP_SC_REQUEST_PENDING = 491,
    PJSIP_SC_UNDECIPHERABLE = 493,
    PJSIP_SC_SECURITY_AGREEMENT_NEEDED = 494,

    PJSIP_SC_INTERNAL_SERVER_ERROR = 500,
    PJSIP_SC_NOT_IMPLEMENTED = 501,
    PJSIP_SC_BAD_GATEWAY = 502,
    PJSIP_SC_SERVICE_UNAVAILABLE = 503,
    PJSIP_SC_SERVER_TIMEOUT = 504,
    PJSIP_SC_VERSION_NOT_SUPPORTED = 505,
    PJSIP_SC_MESSAGE_TOO_LARGE = 513,
    PJSIP_SC_PUSH_NOTIFICATION_SERVICE_NOT_SUPPORTED = 555,
    PJSIP_SC_PRECONDITION_FAILURE = 580,

    PJSIP_SC_BUSY_EVERYWHERE = 600,
    PJSIP_SC_DECLINE = 603,
    PJSIP_SC_DOES_NOT_EXIST_ANYWHERE = 604,
    PJSIP_SC_NOT_ACCEPTABLE_ANYWHERE = 606,
    PJSIP_SC_UNWANTED = 607,
    PJSIP_SC_REJECTED = 608,

    PJSIP_SC_TSX_TIMEOUT = PJSIP_SC_REQUEST_TIMEOUT,
    /*PJSIP_SC_TSX_RESOLVE_ERROR = 702,*/
    PJSIP_SC_TSX_TRANSPORT_ERROR = PJSIP_SC_SERVICE_UNAVAILABLE,

    /* This is not an actual status code, but rather a constant
     * to force GCC to use 32bit to represent this enum, since
     * we have a code in PJSUA-LIB that assigns an integer
     * to this enum (see pjsua_acc_get_info() function).
     */
    PJSIP_SC__force_32bit = 0x7FFFFFFF

};


struct OnIncomingCallParam {
    int callId;
};

struct OnRegStateParam {

};

struct OnCallStateParam {

};

struct OnCallMediaStateParam {

};

struct CallOpParam {
    int statusCode;

public:
    CallOpParam(bool useDefaultCallSetting = false) {}
};

struct AccountRegConfig {
    string              registrarUri;
};

struct AuthCredInfo {
    string      scheme;
    string      realm;
    string      username;
    int         dataType;
    string      data;
};

typedef vector<AuthCredInfo> AuthCredInfoVector;

struct AccountSipConfig {
    AuthCredInfoVector  authCreds;
};

struct AccountConfig {
    int                 priority;
    string              idUri;

    AccountRegConfig    regConfig;
    AccountSipConfig    sipConfig;
};

class Account {
public:
    void create(const AccountConfig &,
                bool make_default=false) {
        qWarning() << "Just a stub account";
    }

};

class AudioMedia {
public:
    void adjustTxLevel(float) {}
    void adjustRxLevel(float) {}
    void startTransmit(AudioMedia) {}
};

class Call {
public:
    Call(Account&, int) { qWarning() << "Just a stub call"; }

    virtual void onCallState(OnCallStateParam &prm) {}
    virtual void onCallMediaState(OnCallMediaStateParam &prm) {}

    void answer(CallOpParam) {}

    void makeCall(const string &, const CallOpParam &) {}

    bool isActive() { return false; }

    void hangup(CallOpParam) {}

    int getId() const {}

    AudioMedia getAudioMedia(int) { }
};

class AudDevManager {
public:
    AudioMedia &getCaptureDevMedia() {}
    AudioMedia &getPlaybackDevMedia() {}
};

typedef enum pjsip_transport_type_e
{
    /** Unspecified. */
    PJSIP_TRANSPORT_UNSPECIFIED,

    /** UDP. */
    PJSIP_TRANSPORT_UDP,

    /** TCP. */
    PJSIP_TRANSPORT_TCP,

    /** TLS. */
    PJSIP_TRANSPORT_TLS,

    /** DTLS, not implemented yet. */
    PJSIP_TRANSPORT_DTLS,

    /** SCTP, not implemented yet. */
    PJSIP_TRANSPORT_SCTP,

    /** Loopback (stream, reliable) */
    PJSIP_TRANSPORT_LOOP,

    /** Loopback (datagram, unreliable) */
    PJSIP_TRANSPORT_LOOP_DGRAM,

    /** Start of user defined transport */
    PJSIP_TRANSPORT_START_OTHER,

    /** Start of IPv6 transports */
    PJSIP_TRANSPORT_IPV6    = 128,

    /** UDP over IPv6 */
    PJSIP_TRANSPORT_UDP6 = PJSIP_TRANSPORT_UDP + PJSIP_TRANSPORT_IPV6,

    /** TCP over IPv6 */
    PJSIP_TRANSPORT_TCP6 = PJSIP_TRANSPORT_TCP + PJSIP_TRANSPORT_IPV6,

    /** TLS over IPv6 */
    PJSIP_TRANSPORT_TLS6 = PJSIP_TRANSPORT_TLS + PJSIP_TRANSPORT_IPV6,

    /** DTLS over IPv6, not implemented yet */
    PJSIP_TRANSPORT_DTLS6 = PJSIP_TRANSPORT_DTLS + PJSIP_TRANSPORT_IPV6

};

struct EpConfig {

};

struct TransportConfig {
    int port;
};

class Endpoint {
public:
    Endpoint() {}
    static Endpoint &instance() {}
    AudDevManager &audDevManager() {}
    void libCreate() { qWarning() << "Just a stub endpoint"; }
    void libInit(EpConfig&) {}
    void transportCreate(pjsip_transport_type_e, const TransportConfig &) {}
    void libStart() {}
};

typedef int             pj_status_t;

struct Error
{
    /** The error code. */
    pj_status_t status;

    /** The PJSUA API operation that throws the error. */
    string      title;

    /** The error message */
    string      reason;

    /** The PJSUA source file that throws the error */
    string      srcFile;

    /** The line number of PJSUA source file that throws the error */
    int         srcLine;

    /** Build error string. */
    string      info(bool multi_line=false) const;

    /** Default constructor */
    Error();

    /**
     * Construct an Error instance from the specified parameters. If
     * \a prm_reason is empty, it will be filled with the error description
     *  for the status code.
     */
    Error(pj_status_t prm_status,
          const string &prm_title,
          const string &prm_reason,
          const string &prm_src_file,
          int prm_src_line);
};


}

#endif // PJSTUBS_H
