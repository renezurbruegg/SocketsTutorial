import socket
import threading
import time

# Configuration for the UDP receiver
UDP_IP = "127.0.0.1"  # Localhost
UDP_PORT = 5005       # Port to listen on
BUFFER_SIZE = 1024    # Size of the buffer for incoming messages

# Initialize a global list to cache messages
message_cache = []
lock = threading.Lock()  # A lock to manage access to the shared cache

def udp_receiver():
    """
    Thread function to receive UDP messages and cache them.
    """
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))

    print(f"Listening for messages on {UDP_IP}:{UDP_PORT}...")
    while True:
        try:
            # Receive data from the socket
            data, addr = sock.recvfrom(BUFFER_SIZE)  # Buffer size is 1024 bytes

            # Safely append the message to the cache
            with lock:
                message_cache.append(data.decode())
        except Exception as e:
            print(f"Error receiving data: {e}")
            break

if __name__ == "__main__":
    # Create and start the receiver thread.
    # This will continuously receive messages in the background, and cache them.
    # using the message_cache list.
    receiver_thread = threading.Thread(target=udp_receiver, daemon=True)
    receiver_thread.start()

    # Peridically print the cached messages in the main thread.
    while True:
        with lock: # This makes sure we don't read the cache while it's being modified by the receiver thread
            if len(message_cache) == 0:
                print("No messages received yet.")
            
            else: 
                print("Received messages:")
                for msg in message_cache:
                    print("-", msg)
                message_cache.clear()  # Clear the cache after printing       
        time.sleep(1)
