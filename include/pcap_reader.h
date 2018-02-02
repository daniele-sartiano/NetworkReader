//
// Created by daniele on 02/02/18.
//

#ifndef NETWORKREADER_PCAPREADER_H
#define NETWORKREADER_PCAPREADER_H

#include <iostream>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

using namespace std;

class PcapReader {
    string filename;
public:
    explicit PcapReader (string f) : filename(f) {};

    int read();
private:
    static void packetHandler(u_char *userdata, const struct pcap_pkthdr* pkthdr, const u_char* packet);
};


#endif //NETWORKREADER_PCAPREADER_H
