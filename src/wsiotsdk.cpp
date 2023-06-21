#include "wsiotsdk.h"
#include "include/psa/crypto.h"
#include "include/application/devnet/iotex_dev_access.h"

using namespace iotex;

Devnet devnet_client;

void Devnet::begin(void) {
    
    psa_crypto_init();
    iotex_dev_access_init();

}

void Devnet::begin(iotex_gettime time_f, iotex_mqtt_pub pub_f, iotex_mqtt_sub sub_f) {

    psa_crypto_init();
    iotex_dev_access_init();

    iotex_dev_access_set_time_func(time_f);
    iotex_dev_access_set_mqtt_func(pub_f, sub_f);
#if IOTEX_USE_SIGN_FUNC_EXT
    iotex_dev_access_set_sign_func(iotex_sign_message_func);
#endif
    
}

void Devnet::setTimeFunction(iotex_gettime time_f) {

    iotex_dev_access_set_time_func(time_f);

}

void Devnet::setMQTTFunctions(iotex_mqtt_pub pub_f, iotex_mqtt_sub sub_f) {

    iotex_dev_access_set_mqtt_func(pub_f, sub_f);

}

void Devnet::setDevnetToken(const char token[], int len) {

    iotex_dev_access_set_token(token, len);

}

void Devnet::setDevnetMQTTTopic(const char topic[], int len, int location) {

    iotex_dev_access_set_mqtt_topic(topic, len, location);

}

void Devnet::send(void *buf, unsigned int len, enum UserData_Type type) {

    iotex_dev_access_data_upload_with_userdata(buf, len, type);

}

char* Devnet::getMQTTConnectAddr(void) {

    return iotex_dev_access_get_mqtt_connect_addr_in_url();

}

int Devnet::getMQTTConnectPort(void) {

    return iotex_dev_access_get_mqtt_connect_port();
    
}

int iotex_wsiotsdk_init(iotex_gettime get_time_func, iotex_mqtt_pub mqtt_pub, iotex_mqtt_sub mqtt_sub) {

    psa_crypto_init();
    iotex_dev_access_init();

    iotex_dev_access_set_time_func(get_time_func);
    iotex_dev_access_set_mqtt_func(mqtt_pub, mqtt_sub);

	return 0;

}




