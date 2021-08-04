#include <stdio.h>
#include "wireshark.h"

int main(int argc, char **argv){
    pcap_hdr_t    file_hdr;
    pcaprec_hdr_t reg_hdr;
    ether_hdr     frame_hdr;
    ip_type       ip;

    FILE *fpcap;

    if (argc != 2 || (fpcap = fopen(argv[1], "rb")) == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        return 1;
    }

    fread(&file_hdr, sizeof(pcap_hdr_t), 1, fpcap);
    fread(&reg_hdr, sizeof(pcaprec_hdr_t), 1, fpcap);
    fread(&frame_hdr, sizeof(ether_hdr), 1, fpcap);
    fread(&ip, sizeof(ip_type), 1, fpcap);

    printf("MAC Src: ");
    for (int i = 0.; i<6; i++) printf("%02x", frame_hdr.ether_shost[i]);
    printf("  MAC Dst: ");
    for (int i = 0.; i<6; i++) printf("%02x", frame_hdr.ether_dhost[i]);
    printf(" | ");
    printf("Src: %08x - Dst: %08x\n", ip.ip_src, ip.ip_dst);

    fclose(fpcap);
}