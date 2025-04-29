# Photon Live Chat Application

![License](https://img.shields.io/badge/License-MIT-blue.svg)
![Qt Version](https://img.shields.io/badge/Qt-5.15+-green.svg)
![OpenSSL](https://img.shields.io/badge/OpenSSL-1.1.1+-yellow.svg)

A secure, real-time chat application with end-to-end encryption built using Qt framework and OpenSSL.

## Features
- **Secure Communication**: AES-128-CBC encryption for all messages
- **Multi-Client Support**: Server handles multiple concurrent connections
- **Persistent Chat History**: New clients receive previous messages
- **Custom Thread Handling**: Dedicated threads for each client connection
- **Modern GUI**: Clean interface with connection status indicators
- **Cross-Platform**: Built with Qt for Windows/Linux/macOS compatibility

## Installation
### Prerequisites
- Qt5 (>= 5.15)
- OpenSSL development libraries

**Ubuntu/Debian:**
```bash
sudo apt install qt5-default libssl-dev
```

### Build Instructions
```bash
git clone https://github.com/TheLeopard65/Photon-Live-Chat-App.git
cd Photon-Live-Chat-App
qmake Photon-Compiler.pro
make
```

## Usage
**Start Server:**
```bash
cd Server
./Server
```

**Start Client:**
```bash
cd Client
./Client
```

**Client Configuration:**
1. Enter server IP address
2. Choose a nickname
3. Click "CONNECT"
4. Start secure chatting!

Default Port: `7986`

## Security Implementation
- AES-128-CBC encryption with PKCS#7 padding
- Random IV generation for each message
- Secure key derivation (hardcoded demo key)

⚠️ **Security Note:** This implementation uses a hardcoded key for demonstration purposes. For production use:
1. Implement proper key exchange protocol
2. Use environment variables for key storage
3. Consider using TLS for transport security

## Project Structure
```
.
├── Client
│   ├── ChatRoom-client.pro
│   ├── clienttcpsocket.cpp
│   ├── clienttcpsocket.h
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── mainwindow.ui
│   └── Makefile
├── LICENSE
├── Makefile
├── Photon-Compiler.pro
├── README.md
└── Server
    ├── ChatRoom-server.pro
    ├── chatserver.cpp
    ├── chatserver.h
    ├── clienthandlerthread.cpp
    ├── clienthandlerthread.h
    ├── customtcpsocket.cpp
    ├── customtcpsocket.h
    ├── main.cpp
    └── Makefile

3 directories, 21 files
```

## Technical Details
- **Network Protocol**: Custom TCP-based protocol
- **Message Format**:
  ```cpp
  struct {
      QByteArray iv;
      QByteArray ciphertext;
  } encrypted_message;
  ```
- **Thread Management**: Dedicated QThread per client connection
- **Dependencies**:
  - QtCore
  - QtNetwork
  - QtWidgets (Client)
  - OpenSSL Crypto Library

## Contributing
We welcome contributions! Please follow these steps:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/awesome`)
3. Commit your changes (`git commit -am 'Add awesome feature'`)
4. Push to the branch (`git push origin feature/awesome`)
5. Open a Pull Request

## License
Distributed under MIT License. See `LICENSE` for more information.
