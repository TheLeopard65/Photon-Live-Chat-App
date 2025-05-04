# Photon Live Chat Application

![License](https://img.shields.io/badge/License-MIT-blue.svg)
![Qt Version](https://img.shields.io/badge/Qt-5.15+-green.svg)
![OpenSSL](https://img.shields.io/badge/OpenSSL-1.1.1+-yellow.svg)

A secure, real-time chat application designed to ensure privacy through robust end-to-end encryption, leveraging the power of Qt framework for cross-platform GUI development. OpenSSL is integrated to handle secure communication protocols & cryptographic operations. The application supports instant messaging with a focus on user data protection & seamless performance. Its architecture is built to resist eavesdropping, ensuring confidentiality across all transmitted messages.

## Features
- _**Secure Communication**_: AES-128-CBC encryption for all messages
- _**Multi-Client Support**_: Server handles multiple concurrent connections
- _**Persistent Chat History**_: New clients receive previous messages
- _**Custom Thread Handling**_: Dedicated threads for each client connection
- _**Modern GUI**_: Clean interface with connection status indicators
- _**Cross-Platform**_: Built with Qt for Windows/Linux/macOS compatibility

## Installation
### Prerequisites
- Qt5 Library ( Version >= 5.15)
- OpenSSL development libraries

### Build Instructions
```bash
git clone https://github.com/TheLeopard65/Photon-Live-Chat-App.git
cd Photon-Live-Chat-App
./install.sh
```

## Usage
**Start Server:**
```bash
./Server
```

**Start Client:**
```bash
./Client
```

**Client Configuration:**
1. Enter server IP address
2. Choose a nickname
3. Click `CONNECT`
4. Start secure chatting!

## Security Implementation
- AES-128-CBC encryption with PKCS#7 padding
- Random IV generation for each message
- Secure key derivation (hardcoded demo key)

### **Security Note:** This implementation uses a hardcoded key for demonstration purposes. For production use:
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
├── Install.sh
├── LICENSE
├── Makefile
├── Photon-Compiler.pro
├── README.md
├── Requirements.txt
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

3 directories, 23 files
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
- **Default Port**: `7986`

## Contributing
We welcome contributions! Please follow these steps:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/awesome`)
3. Commit your changes (`git commit -am 'Add awesome feature'`)
4. Push to the branch (`git push origin feature/awesome`)
5. Open a Pull Request

## License
Distributed under MIT License. See [LICENSE](LICENSE) for more information.
