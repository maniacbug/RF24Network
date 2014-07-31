#include "RF24Network_config.h"
#include "RF24Network.h"

#if defined(__AVR_ATtinyX4__) || defined(__AVR_ATtinyX5__)
#  define FLASH_PTR(x) ((fstr_t *)x)
#else
#  define FLASH_PTR(x) ((const __FlashStringHelper *)x)
#endif

void RF24NetworkDebug::print_timed(const prog_char *str)
{
  _out.print(millis());
  _out.print(F(": "));
  _out.print(FLASH_PTR(str));
}

void RF24NetworkDebug::print_header(const RF24NetworkHeader &h)
{
  _out.print(F("id "));
  _out.print(h.id, HEX);
  _out.print(F(" from 0"));
  _out.print(h.from_node, OCT);
  _out.print(F(" to 0"));
  _out.print(h.to_node, OCT);
  _out.print(F(" type "));
  _out.print(h.type);
}

void RF24NetworkDebug::on_header(uint8_t pipe_num, const RF24NetworkHeader &header, uint8_t *frame_buffer) {
  print_timed(PSTR("MAC Received on "));
  _out.print(pipe_num, DEC);
  _out.print(' ');
  print_header(header);

  const uint16_t* i = reinterpret_cast<const uint16_t*>(frame_buffer + sizeof(RF24NetworkHeader));
  print_timed(PSTR("NET message "));
  _out.println(*i, HEX);
}

void RF24NetworkDebug::on_enqueue(size_t frame, bool result) {
  print_timed(PSTR("NET Enqueue "));
  _out.print(frame, HEX);
  _out.println(result? F("ok"): F("failed"));
}

void RF24NetworkDebug::on_receive(const RF24NetworkHeader& header) {
  print_timed(PSTR("NET Received "));
  print_header(header);
  _out.println();
}

void RF24NetworkDebug::on_send(const RF24NetworkHeader& header, const void *message, size_t len) {
  print_timed(PSTR("NET Sending "));
  print_header(header);
  if (len) {
    const uint16_t* i = reinterpret_cast<const uint16_t*>(message);
    _out.print(F(" message "));
    _out.print(*i, HEX);
  }
  _out.println();
}

void RF24NetworkDebug::on_write(uint16_t to_node, uint16_t send_node, uint8_t send_pipe) {
  print_timed(PSTR("MAC Sending to 0"));
  _out.print(to_node, OCT);
  _out.print(F(" via 0"));
  _out.print(send_node, OCT);
  _out.print(F(" on "));
  _out.println(send_pipe, HEX);
}

void RF24NetworkDebug::on_setup_address(uint16_t node_address, uint16_t node_mask, uint16_t parent_node, uint16_t parent_pipe) {
  _out.print(F("setup_address node=0"));
  _out.print(node_address, OCT);
  _out.print(F(" mask=0"));
  _out.print(node_mask, OCT);
  _out.print(F(" parent=0"));
  _out.print(parent_node, OCT);
  _out.print(F(" pipe="));
  _out.print(parent_pipe, HEX);
}
