Parameters
===========

Ethernet
-----------

### `Ethernet.type`

Ethernet frame type.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `Ethernet.src`

Source hardware address.

- Expected length: 6 byte
- Recommended formatting method: `mac()`

### `Ethernet.dst`

Destination hardware address.

- Expected length: 6 byte
- Recommended formatting method: `mac()`

ARP
-------------

### `ARP.hw_type`

Hardware type

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `ARP.pr_type`

Protocol type

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `ARP.hw_size`

Hardware address size

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `ARP.pr_size`

Protocol address size

- Expected length: 1 byte
- Recommended formatting method: `uint()`


### `ARP.op`

ARP operation. `1` means a request, `2` means a reply.

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `ARP.hw_src`

Source hardware address.

- Expected length: defined by `ARP.hw_size`
- Recommended formatting method: `hex()`. If `ARP.hw_type` is `1`, then `mac()`

### `ARP.hw_dst`

Destination hardware address.

- Expected length: defined by `ARP.hw_size`
- Recommended formatting method: `hex()`. If `ARP.hw_type` is `1`, then `mac()`

### `ARP.pr_src`

Source protocol address.

- Expected length: defined by `ARP.pr_size`
- Recommended formatting method: `hex()`. If `ARP.pr_type` is `0x0800`, then `ip4()`

### `ARP.pr_dst`

Destination protocol address.

- Expected length: defined by `ARP.pr_size`
- Recommended formatting method: `hex()`. If `ARP.pr_type` is `0x0800`, then `ip4()`

PPPoE
---------

to be written.

IPv4
---------

### `IPv4.hdr_len`

IPv4 Header length. In IPv4 header, the header length field should be bit shift. PacketMachine must shift the bits before a user access.

- Expected length: 1 byte (originally 4 bits)
- Recommended formatting method: `uint()`

### `IPv4.ver`

IPv4 version

- Expected length: 1 byte (originally 4 bits)
- Recommended formatting method: `uint()`

### `IPv4.tos`

Type of services.

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `IPv4.total_len`

Total length of IP header and data.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `IPv4.id`

ID of IP packet.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `IPv4.offset`

Offset of IP fragmentation.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `IPv4.ttl`

Time to Live.

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `IPv4.proto`

Protocol number of next layer.

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `IPv4.chksum`

Checksum of IP header.

- Expected length: 2 byte
- Recommended formatting method: `hex()`, `raw()` or `uint()`

### `IPv4.src`

Source IP address.

- Expected length: 4 byte
- Recommended formatting method: `ip4()`

### `IPv4.dst`

Destination IP address.

- Expected length: 4 byte
- Recommended formatting method: `ip4()`


UDP
---------

### `UDP.src_port`

UDP source port number.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `UDP.dst_port`

UDP destination port number.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `UDP.length`

UDP header and data length.

- Expected length: 2 byte
- Recommended formatting method: `uint()`


### `UDP.chksum`

Checksum.

- Expected length: 2 byte
- Recommended formatting method: `uint()` or `hex()`


TCP
---------

### `TCP.src_port`

TCP source port number.

- Expected length: 2 byte
- Recommended formatting method: `uint()`


### `TCP.dst_port`

TCP source port number.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `TCP.seq`

Sequence number of TCP stream.

- Expected length: 4 byte
- Recommended formatting method: `uint()`


### `TCP.ack`

Acknowledgment number of TCP stream.

- Expected length: 4 byte
- Recommended formatting method: `uint()`


### `TCP.offset`

Data offset.

- Expected length: 1 byte
- Recommended formatting method: `uint()`


### `TCP.flags`

TCP flag section. See also `TCP.flag_{fin,syn,rst,push,ack,usrg,ece,cwr}`

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `TCP.window`

Window size.

- Expected length: 2 byte
- Recommended formatting method: `uint()`

### `TCP.chksum`

Checksum.

- Expected length: 2 byte
- Recommended formatting method: `uint()` or `hex()`


### `TCP.urgptr`

Urgent Pointer.

- Expected length: 2 byte
- Recommended formatting method: `uint()`.


### `TCP.flag_fin`

FIN flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.

### `TCP.flag_syn`

SYN flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.


### `TCP.flag_rst`

RST(Reset the connection) flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.

### `TCP.flag_push`

PSH(Push Function) flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.

### `TCP.flag_ack`

ACK(Acknowledgment field significant) flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.

### `TCP.flag_urg`

URG(Urgent Pointer field significant) flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.

### `TCP.flag_ece`

ECE(ECN Echo) flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.

### `TCP.flag_cwr`

CWR(Congestion window reduced) flag status. If the flag is on, the parameter should be `1`. If not, `0`.

- Expected length: 1 byte
- Recommended formatting method: `uint()`.

### `TCP.optdata`

TCP option field.

- Expected length: `TCP.offset` - 28 bytes (fixed TCP header length)
- Recommended formatting method: `hex()` or `raw()`

### `TCP.segment`

TCP data segment field. (Not reassembled)

- Expected length: N/A
- Recommended formatting method: `hex()` or `raw()`


### `TCP.ssn_id`

to be written.

### `TCP.data`

TCP data segment that is reassembled.

- Expected length: N/A
- Recommended formatting method: `hex()` or `raw()`


ICMP
---------

### `ICMP.type`

ICMP type.

- Expected length: 1 bytes
- Recommended formatting method: `uint()`
- Support `repr()` to convert from type number to description.
    - e.g.) `3` to `Destination Unreachable`


### `ICMP.code`

ICMP code.

- Expected length: 1 bytes
- Recommended formatting method: `uint()`
- Support `repr()` to convert from type number to description.
    - e.g.) If `ICMP.type` is `3` and `ICMP.code` is `1`, then `Host Unreachable`

### `ICMP.chksum`

Checksum.

- Expected length: 2 bytes
- Recommended formatting method: `uint()` or `hex()`


DNS
---------


### `DNS.tx_id`

Transaction ID.

- Expected length: 2 bytes
- Recommended formatting method: `uint()`


### `DNS.is_query`

If QUERY flag is on.

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `DNS.question`

DNS question section.

- Type: `pm::value::Array`
- The parameter has `pm::value::Map` type value(s) in the array as one DNS record
- The `pm::value::Map` type value has following attributes
    - `name`: DNS record name.
	    - Expected length: N/A
		- Recommended formatting method: `repr()`
		- `repr()` method supports string reconstruction with label.
	- `type`: 
	    - Expected length: 2 bytes
		- Recommended formatting method: `uint()` or `repr()`
		- Support `repr()` to show record type name.
		    - e.g.) convert `5` to `CNAME`
	- `data`: 
	    - Expected length: N/A
		- Recommended formatting method: `repr()`
		- `repr()` method supports string reconstruction with label.

Example for `DNS.answer`

```cpp
void callback(const pm::Property& p) {
  if (!p.has_value("DNS.answer")) {
    return;
  }
  const auto& records = p.value("DNS.answer");
  for (size_t i = 0; i < records.size(); i++) {
    const auto& rec = records.get(i);
	std::cout << "Answer No." << (i + 1) << std::endl 
        << "Name: " << rec.find("name") << std::endl
        << "Type: " << rec.find("type") << std::endl
        << "Data: " << rec.find("data") << std::endl << std::endl;
  }
}
```

### `DNS.answer`

DNS answer section in the same manner as `DNS.query`

### `DNS.authority`

DNS authority section in the same manner as `DNS.query`

### `DNS.additional`

DNS additional section in the same manner as `DNS.query`


mDNS
---------

### `mDNS.tx_id`

Transaction ID.

- Expected length: 2 bytes
- Recommended formatting method: `uint()`


### `mDNS.is_query`

If QUERY flag is on.

- Expected length: 1 byte
- Recommended formatting method: `uint()`

### `mDNS.question`

DNS question section in the same manner as `DNS.query`

### `mDNS.answer`

DNS answer section in the same manner as `DNS.query`

### `mDNS.authority`

DNS authority section in the same manner as `DNS.query`

### `mDNS.additional`

DNS additional section in the same manner as `DNS.query`


DHCP
---------

to be written.

