#include "RF24Network_config.h"
#include "RF24Network.h"
#include "RF24NetworkSerialDebug.h"

#ifdef ENERGIA
extern "C" {
  int putchar(int c) {
    Serial.print((char)c);
    return c;
  }
}
#endif

void RF24NetworkHeader::toString() const
{
  printf_P(PSTR("id %04x from 0%o to 0%o type %c"),id,from_node,to_node,type);
}

void NetworkSerialDebug::on_header(uint8_t pipe_num, const RF24NetworkHeader &header, uint8_t *frame_buffer) {
  printf_P(PSTR("%lu: MAC Received on %u "),millis(),pipe_num);
  header.toString();
  const uint16_t* i = reinterpret_cast<const uint16_t*>(frame_buffer + sizeof(RF24NetworkHeader));
  printf_P(PSTR("%lu: NET message %04x\r\n"),millis(), *i);
}

void NetworkSerialDebug::on_enqueue(size_t frame, bool result) {
  printf_P(PSTR("%lu: NET Enqueue @%x "), millis(), frame);
  if (result)
    printf_P(PSTR("ok\r\n"));
  else
    printf_P(PSTR("failed\r\n"));
}

void NetworkSerialDebug::on_receive(const RF24NetworkHeader& header) {
  printf_P(PSTR("%lu: NET Received "), millis());
  header.toString();
  printf_P(PSTR("\r\n"));
}

void NetworkSerialDebug::on_send(const RF24NetworkHeader& header, const void *message, size_t len) {
  printf_P(PSTR("%lu: NET Sending "), millis());
  header.toString();
  if (len) {
    const uint16_t* i = reinterpret_cast<const uint16_t*>(message);
    printf_P(PSTR(" message %04x"), *i);
  }
  printf_P(PSTR("\r\n"));
}

void NetworkSerialDebug::on_write(uint16_t to_node, uint16_t send_node, uint8_t send_pipe) {
  printf_P(PSTR("%lu: MAC Sending to 0%o via 0%o on %x\r\n"), millis(), to_node, send_node, (uint32_t)send_pipe);
}

void NetworkSerialDebug::on_setup_address(uint16_t node_address, uint16_t node_mask, uint16_t parent_node, uint16_t parent_pipe) {
  printf_P(PSTR("setup_address node=0%o mask=0%o parent=0%o pipe=0%o\r\n"), node_address, node_mask, parent_node, (uint32_t)parent_pipe);
}
