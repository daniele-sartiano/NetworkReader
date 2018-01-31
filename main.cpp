//
// Created by daniele on 29/01/18.
//

#include <iostream>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <getopt.h>


using namespace std;

class PcapReader {
    string filename;
public:
    explicit PcapReader (string f) : filename(f) {}

    int read() {
        char errbuff[PCAP_ERRBUF_SIZE];
        cout << this->filename << "\n";
        pcap_t* pcap = pcap_open_offline(this->filename.c_str(), errbuff);

        if (pcap == NULL) {
            cerr << "pcap_open_offline() failed: " << errbuff << endl;
            return 1;
        }

        // start packet processing loop, just like live capture
        if (pcap_loop(pcap, 0, handler, NULL) < 0) {
            cout << "pcap_loop() failed: " << pcap_geterr(pcap);
            return 1;
        }

        cout << "capture finished" << endl;
        return 0;

    }

    static void handler(u_char *userdata, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
        const struct ether_header* ethernetHeader;
        const struct ip* ipHeader;
        const struct tcphdr* tcpHeader;
        char sourceIp[INET_ADDRSTRLEN];
        char destIp[INET_ADDRSTRLEN];
        u_int sourcePort, destPort;
        u_char *data;
        int dataLength = 0;

        ethernetHeader = (struct ether_header*)packet;

        if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
            ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
            inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIp, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);

            if (ipHeader->ip_p == IPPROTO_TCP) {
                tcpHeader = (tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
                sourcePort = ntohs(tcpHeader->source);
                destPort = ntohs(tcpHeader->dest);
                dataLength = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));

                // print the results
                cout << pkthdr->ts.tv_sec << ":" << pkthdr->ts.tv_usec << " - " << sourceIp << ":" << sourcePort << " -> " << destIp << ":" << destPort << " - " << dataLength << endl;
            }
        } else {
            cout << "no ethernet" << endl;
        }

    }
};

int main(int argc, char* argv[]) {
    const char* nvalue = "";
    int c ;
    while( ( c = getopt (argc, argv, "f:") ) != -1 )
    {
        switch(c)
        {
            case 'f':
                if(optarg) {
                    nvalue = optarg;
                }
                else {
                    cerr << "got a nullptr for optarg for -n\n" ;
                    return(-1);
                }

        }
    }

    PcapReader *reader = new PcapReader(nvalue);
    reader->read();

    return(0);
}