typedef unsigned int guint32;
typedef unsigned short guint16;
typedef unsigned char guint8;

typedef struct pcap_hdr_s {
        guint32 magic_number;   /* magic number */
        guint16 version_major;  /* major version number */
        guint16 version_minor;  /* minor version number */
        guint32 thiszone;       /* GMT to local correction */
        guint32 sigfigs;        /* accuracy of timestamps */
        guint32 snaplen;        /* max length of captured packets, in octets */
        guint32 network;        /* data link type */
} pcap_hdr_t;

typedef struct pcaprec_hdr_s {
        guint32 ts_sec;         /* timestamp seconds */
        guint32 ts_usec;        /* timestamp microseconds */
        guint32 incl_len;       /* number of octets of packet saved in file */
        guint32 orig_len;       /* actual length of packet */
} pcaprec_hdr_t;

typedef struct {
    unsigned char ether_dhost[6];
    unsigned char ether_shost[6];
    guint16 type;
}ether_hdr;

typedef struct {
    guint32 ignorar1;
    guint32 ignorar2;
    guint32 ignorar3;
    guint32 ip_src;
    guint32 ip_dst;
}ip_type;
