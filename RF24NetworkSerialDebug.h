#ifndef __RF24NETWORK_SERIAL_DEBUG_H
#define __RF24NETWORK_SERIAL_DEBUG_H

class NetworkSerialDebug: public RF24NetworkDebug
{
public:
  void on_header(uint8_t pipe_num, const RF24NetworkHeader &header, uint8_t *frame_buffer);

  void on_enqueue(size_t frame, bool result);

  void on_receive(const RF24NetworkHeader& header);

  virtual void on_send(const RF24NetworkHeader& header, const void *message, size_t len);

  void on_write(uint16_t to_node, uint16_t send_node, uint8_t send_pipe);

  void wrote_pipe(uint8_t out_pipe, bool ok);

  void on_setup_address(uint16_t node_address, uint16_t node_mask, uint16_t parent_node, uint16_t parent_pipe);

  NetworkSerialDebug(RF24Network &network) { network.setDebug(this); }
};

#endif
