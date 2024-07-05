# Encrypted Windows Reverse Shell

This project provides a simple encrypted reverse shell for Windows, which also has the capability to hide itself.

## Usage

### Client Side

1. Compile the reverse shell code using GCC:
    ```sh
    gcc rev.c -lwsock32 -lws2_32 -static-libgcc -o rev
    ```

### Server Side

2. Start a listener to receive the incoming connections. You can use `netcat` or any other listener:
    ```sh
    nc -l 1337
    ```

## Features

- **Encryption**: Ensures that the communication between the client and server is encrypted for added security.
- **Stealth Mode**: The reverse shell hides itself to avoid detection.

## Prerequisites

- **GCC**: Make sure you have GCC installed on your system to compile the code.
- **Netcat (nc)**: A versatile networking tool used for creating the listener.

## Compilation and Execution

1. **Compile the Client Code**:
    ```sh
    gcc rev.c -lwsock32 -lws2_32 -static-libgcc -o rev
    ```
    This command links the necessary Windows socket libraries and outputs an executable named `rev`.

2. **Run the Listener**:
    ```sh
    nc -l 1337
    ```
    This command starts a netcat listener on port `1337` to wait for incoming connections from the reverse shell.

## Credits

- Developed by Vincent Ng
