# Reliable-File-Transfer-over-UDP

Developed a reliable file transfer system in C using UDP sockets, implementing custom mechanisms for packet sequencing, acknowledgments, and retransmissions to ensure ordered and loss-free data delivery.

# Key Achievements
Implemented client-server architecture with UDP sockets for file transmission.
Designed a sliding window protocol (5 packets) for sequencing and flow control.
Added reliability features: ACK-based acknowledgment, packet retransmission, and buffering for out-of-order packets.
Successfully achieved reliable and ordered file transfer, mimicking core TCP features on top of UDP.
