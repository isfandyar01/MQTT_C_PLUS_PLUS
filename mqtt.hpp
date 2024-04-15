#ifndef __MQTT_HPP__
#define __MQTT_HPP__

#include <iostream>
#include <stdio.h>

#define MQTT_HEADER_LEN 2
#define MQTT_ACK_LEN 4

/*
 * Stub bytes, useful for generic replies, these represent the first byte in
 * the fixed header
 */
#define CONNACK_BYTE 0x20
#define PUBLISH_BYTE 0x30
#define PUBACK_BYTE 0x40
#define PUBREC_BYTE 0x50
#define PUBREL_BYTE 0x60
#define PUBCOMP_BYTE 0x70
#define SUBACK_BYTE 0x90
#define UNSUBACK_BYTE 0xB0
#define PINGRESP_BYTE 0xD0

enum packet_type {
  connect = 1,
  connack,
  publish,
  puback,
  pubrec,
  pubrel,
  pubcomp,
  subscribe,
  suback,
  unsubscribe,
  unsuback,
  pingreq,
  pingresp,
  disconnect
};

enum qos_level { at_most_once, at_least_once, exactly_once };

union mqtt_header {
  unsigned char byte;
  struct {
    unsigned retain : 1;
    unsigned qos : 2;
    unsigned dup : 1;
    unsigned type : 4;
  } bits;
  /* data */
};

struct mqtt_connect {
  union mqtt_header header;
  union {
    unsigned char byte;
    struct {
      int reserved : 1;
      unsigned clean_session : 1;
      unsigned will : 1;
      unsigned will_qos : 2;
      unsigned will_retain : 1;
      unsigned password : 1;
      unsigned username : 1;
    } bits;
  };
  struct {
    unsigned short keepalive;
    unsigned char *client_id;
    unsigned char *username;
    unsigned char *password;
    unsigned char *will_topic;
    unsigned char *will_message;
  } payload;
};

struct mqtt_connack {
  union mqtt_header header;
  union {
    unsigned char byte;
    struct {
      unsigned session_present : 1;
      unsigned reserved : 7;
    } bits;
  };
  unsigned char rc;
};

#endif // __MQTT_HPP__
