//
// Created by daniele on 02/02/18.
//

#include "pcap_reader.h"

int PcapReader::read() {
    char errbuff[PCAP_ERRBUF_SIZE];
    cout << this->filename << "\n";
    pcap_t *pcap = pcap_open_offline(this->filename.c_str(), errbuff);

    if (pcap == NULL) {
        cerr << "pcap_open_offline() failed: " << errbuff << endl;
        return 1;
    }

    // start packet processing loop, just like live capture
    if (pcap_loop(pcap, 0, PcapReader::packetHandler, NULL) < 0) {
        cout << "pcap_loop() failed: " << pcap_geterr(pcap);
        return 1;
    }

    cout << "capture finished" << endl;
    return 0;
}

void PcapReader::packetHandler(u_char *userdata, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    const struct ether_header *ethernetHeader;
    const struct ip *ipHeader;
    const struct tcphdr *tcpHeader;
    char sourceIp[INET_ADDRSTRLEN];
    char destIp[INET_ADDRSTRLEN];
    u_int sourcePort, destPort;
    u_char *data;
    int dataLength = 0;

    ethernetHeader = (struct ether_header *) packet;

    if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
        ipHeader = (struct ip *) (packet + sizeof(struct ether_header));
        inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIp, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);

        if (ipHeader->ip_p == IPPROTO_TCP) {
            tcpHeader = (tcphdr *) (packet + sizeof(struct ether_header) + sizeof(struct ip));
            sourcePort = ntohs(tcpHeader->source);
            destPort = ntohs(tcpHeader->dest);
            dataLength = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));

            // print the results
            cout << pkthdr->ts.tv_sec << ":" << pkthdr->ts.tv_usec << " - " << sourceIp << ":" << sourcePort << " -> "
                 << destIp << ":" << destPort << " - " << dataLength << endl;
        }
    } else {
        cout << "no ethernet" << endl;
    }
}