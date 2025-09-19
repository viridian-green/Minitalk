# Minitalk: Client-Server Communication with UNIX Signals

## 📋 Table of Contents

- [About](#about)
- [Project Overview](#project-overview)
- [Program Specifications](#program-specifications)
- [Installation & Usage](#installation--usage)
- [Communication Protocol](#communication-protocol)
- [Implementation Details](#implementation-details)
- [Testing & Validation](#testing--validation)
- [Makefile Targets](#makefile-targets)

## About

**Minitalk** is a client-server communication program that demonstrates inter-process communication using UNIX signals. The client sends strings to the server using only SIGUSR1 and SIGUSR2 signals, implementing a custom binary protocol for data transmission.

## Project Overview

This project consists of two separate programs:
- **Server**: Listens for incoming signals and reconstructs messages
- **Client**: Sends messages to the server using signals

### Key Features
- Signal-based communication using only SIGUSR1 and SIGUSR2
- Binary data encoding/decoding
- Error handling and memory management
- Support for multiple consecutive clients
- Real-time message display

## Program Specifications

### Server Program
```bash
./server
```
- Displays its PID upon startup
- Listens for incoming signals from clients
- Reconstructs and displays received messages
- Handles multiple clients sequentially
- Runs continuously until terminated

### Client Program
```bash
./client [server_pid] [message]
```
- Takes server PID and message as arguments
- Encodes message into binary signals
- Sends signals to the specified server process
- Exits after completing transmission

### Allowed Functions
- `write`, `signal`, `sigemptyset`, `sigaddset`
- `sigaction`, `kill`, `getpid`, `malloc`
- `free`, `pause`, `sleep`, `usleep`, `exit`
- Custom `ft_printf` or equivalent

## Installation & Usage

### Compilation
```bash
git clone https://github.com/viridian-green/minitalk.git
cd minitalk
make
```

### Running the Programs

#### Start the Server
```bash
./server
# Output: Server PID: 12345
```

#### Send Messages from Client
```bash
# Send a simple message
./client 12345 "Hello, Server!"

# Send longer text
./client 12345 "This is a longer message that will be transmitted via signals."

# Send special characters
./client 12345 "Message with special chars: !@#$%^&*()"
```

#### Multiple Clients Example
```bash
# Terminal 1 - Server
./server

# Terminal 2 - Client 1
./client 12345 "First message"

# Terminal 3 - Client 2  
./client 12345 "Second message"

# Terminal 4 - Client 3
./client 12345 "Third message"
```

## Communication Protocol

### Signal Encoding
- **SIGUSR1** represents binary '0'
- **SIGUSR2** represents binary '1'

### Transmission Process
1. **Character Encoding**: Each character is converted to its 8-bit ASCII value
2. **Bit-by-bit Transmission**: Each bit is sent as a separate signal
3. **Acknowledgement**: Server confirms receipt of each bit (optional implementation)
4. **Message Reconstruction**: Server reassembles bits into characters

## Implementation Details

### Error Handling Tests
```bash
# Invalid PID
./client 99999 "Hello"      # Should handle gracefully

# Very long message
./client 12345 "$(python -c 'print("A"*10000)')" # Should handle memory properly

# Special characters
./client 12345 "Test with null: \0 and other special chars"
```

### Memory Leak Checking
```bash
# Using valgrind
valgrind --leak-check=full ./server
valgrind --leak-check=full ./client 12345 "Test message"
```

### Concurrent Client Testing
```bash
# Test multiple clients sending simultaneously
for i in {1..10}; do
    ./client 12345 "Message $i" &
done
```

## Performance Optimization

### Signal Overhead Reduction
- Minimize signal handler execution time
- Use efficient bit manipulation
- Avoid complex operations in signal handlers

### Memory Management
- Pre-allocate buffers for message reconstruction
- Implement efficient string appending
- Proper cleanup after each message

### Error Recovery
- Handle signal loss gracefully
- Implement timeouts for stuck transmissions
- Clean up resources on interruption

---

**Note**: This implementation demonstrates low-level UNIX signal programming and inter-process communication. The solution meets all requirements including proper error handling, memory management, and performance constraints while using only the allowed functions.
