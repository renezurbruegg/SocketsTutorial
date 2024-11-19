import socket
import time


# Set up the UDP sender
UDP_IP = "127.0.0.1"  # Receiver's IP. This is the IP of the target system
UDP_PORT = 5005       # Receiver's Port. Port on the receiver system.

# Create a socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Sending messages to {UDP_IP}:{UDP_PORT}. Press Ctrl+C to stop.")

try:
    while True:
        message = input("Enter message to send: ")
        sock.sendto(message.encode(), (UDP_IP, UDP_PORT))
except KeyboardInterrupt:
    print("\nSender shutting down.")
finally:
    sock.close()
