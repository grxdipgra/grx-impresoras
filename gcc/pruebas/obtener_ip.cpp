#include <stdio.h>

#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>  //struct ifreq
#include <sys/utsname.h>
#include <netinet/in.h>
#include <net/if.h> //struct ifreq
#include <arpa/inet.h> //usado por inet_ntoa
#include <unistd.h>  // Usado por 'close'
#include <netinet/ether.h> // ather_ntoa()
#include <netdb.h>
#include <pcap.h>
#include <netdb.h>
#include <iostream> //cout
#include <errno.h> //errno

#define IPTOSBUFFERS    12

using namespace std;

void sys_info(struct utsname &info)
{
    if ( uname(&info) != 0)
    {
        cout << "fallo: " << strerror(errno) << '\n';
        //log_handle("Error leyendo la configuración del sistema");
        //return utsname*("NULL");
    }
}

bool is_interface_online(string interface) {
    struct ifreq ifr;
    int sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_IP);
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, interface.c_str());
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0) {
            perror("\tSIOCGIFFLAGS");
    }
    close(sock);
	struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
	strncpy(ifr.ifr_name, "lo", IFNAMSIZ-1);
	printf("\tIP address: %s\n",inet_ntoa(ipaddr->sin_addr));
    return !!(ifr.ifr_flags & IFF_UP);
}

char *iptos(u_long in)
{
    static char output[IPTOSBUFFERS][3*4+3+1];
    static short which;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    snprintf(output[which], sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}

char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
    socklen_t sockaddrlen;

    #ifdef WIN32
    sockaddrlen = sizeof(struct sockaddr_in6);
    #else
    sockaddrlen = sizeof(struct sockaddr_storage);
    #endif


    if(getnameinfo(sockaddr, sockaddrlen, address, addrlen, NULL, 0, NI_NUMERICHOST) != 0) address = NULL;

    return address;
}


void ifprint(pcap_if_t *d)
{
  pcap_addr_t *a;
  char ip6str[128];

  /* Name */
  printf("\tNombre: %s\n",d->name);

  if (is_interface_online(d->name))
  {
	printf("\tActiva: si\n");
  
  /* Description */
  if (d->description)
    printf("\tDescription: %s\n",d->description);

  /* Loopback Address*/
  printf("\tLoopback: %s\n",(d->flags & PCAP_IF_LOOPBACK)?"yes":"no");

  /* IP addresses */
  for(a=d->addresses;a;a=a->next) {
    printf("\tAddress Family: #%d\n",a->addr->sa_family);
  
    switch(a->addr->sa_family)
    {
      case AF_INET:
        printf("\tAddress Family Name: AF_INET\n");
        if (a->addr)
          printf("\tAddress: %s\n",iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
        if (a->netmask)
          printf("\tNetmask: %s\n",iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
        if (a->broadaddr)
          printf("\tBroadcast Address: %s\n",iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
        if (a->dstaddr)
          printf("\tDestination Address: %s\n",iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
        break;

      case AF_INET6:
        printf("\tAddress Family Name: AF_INET6\n");
        if (a->addr)
          printf("\tAddress: %s\n", ip6tos(a->addr, ip6str, sizeof(ip6str)));
       break;

      default:
        printf("\tAddress Family Name: Unknown\n");
        break;
    }
  }
  printf("\n");
  }
  else printf("\tActiva: no\n");
}	

int
main()
{

 struct utsname u_name;

 int fd, ret, i;
 struct ifreq ifr;
 char *dev; 
 char errbuf[PCAP_ERRBUF_SIZE];
 pcap_if_t *interfaces;
 pcap_if_t *aux;
 pcap_addr *ip;
 ret = pcap_findalldevs(&interfaces, errbuf);
    if(ret == -1)
    {
        printf("%s",errbuf);
    };
    for (aux = interfaces;aux;aux=aux->next) 
		{ 
		ifprint(aux);
        //printf("#%d: %s %s %s\n",++i,aux->name,aux->description,aux->addresses);
		}
    /*printf("select a device: "); 
    scanf("%d", &devid);  
    aux=alldevs; 
    while (--devid)
    pdev=pdev->next;  
    printf("Selected %s \n", pdev->name);*/  

 dev = pcap_lookupdev(errbuf);
 printf("Device: %s\n", dev);

 fd = socket(AF_INET, SOCK_DGRAM, 0);

 /* I want to get an IPv4 IP address */
 ifr.ifr_addr.sa_family = AF_INET;

 /* I want IP address attached to "eth0" */
 strncpy(ifr.ifr_name, "lo", IFNAMSIZ-1);

 ioctl(fd, SIOCGIFADDR, &ifr);

 close(fd);

 /* display result */
 printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

 sys_info(u_name);
 //printf("%s", info.sysname);

  printf("   sysname[] = '%s';\n", u_name.sysname);
  printf("  nodename[] = '%s';\n", u_name.nodename);
  printf("   release[] = '%s';\n", u_name.release);
  printf("   version[] = '%s';\n", u_name.version);
  printf("   machine[] = '%s';\n", u_name.machine);
  printf("domainname[] = '%s';\n", u_name.domainname);


 return 0;
}


