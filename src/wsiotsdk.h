#ifndef __WSIOTSDK_H__
#define __WSIOTSDK_H__

#include "psa_layer/include/svc/crypto.h"
#include "psa_layer/include/entropy.h"

namespace iotex
{
class Devnet
{
  private:


  public:

    void begin(void);
    void begin(iotex_gettime time_f, iotex_mqtt_pub pub_f, iotex_mqtt_sub sub_f);
    void setTimeFunction(iotex_gettime time_f);
    void setMQTTFunctions(iotex_mqtt_pub pub_f, iotex_mqtt_sub sub_f);
    void setDevnetToken(const char token[], int len);
    void setDevnetMQTTTopic(const char topic[], int len, int location = 0);
    void send(void *buf, unsigned int len, enum UserData_Type type);

    char* getMQTTConnectAddr(void);
    int getMQTTConnectPort(void);    

};
} // namespace iotex

#ifdef __cplusplus
extern "C" {
#endif
int iotex_wsiotsdk_init(iotex_gettime get_time_func, iotex_mqtt_pub mqtt_pub, iotex_mqtt_sub mqtt_sub);
#ifdef __cplusplus
}
#endif

extern iotex::Devnet devnet_client;

#endif
