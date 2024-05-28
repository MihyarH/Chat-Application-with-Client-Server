# Chat Application

## Overview

The Chat Application is a multi-threaded client-server chat system implemented in C++. The server handles multiple client connections simultaneously, allowing clients to send and receive messages in real-time. The application demonstrates the use of operating system features such as multi-threading and inter-process communication through socket programming.

## Features

- Multi-threaded server to handle multiple clients concurrently
- Client-server communication using sockets
- User interface built with Qt for the client application
- Ability to send private messages to specific users
- Save and load chat history on the client side
- Basic user authentication with hashed passwords
- Configuration file for server settings

## Project Requirements

- Developed and compiled on a Linux distribution
- Build automation using CMake
- Source code managed with Git and available on GitHub
- Documentation for all classes, structs, and functions

## Table of Contents

- [Project Setup](#project-setup)
- [Building the Project](#building-the-project)
- [Running the Server](#running-the-server)
- [Running the Client](#running-the-client)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Project Setup

### Prerequisites

- A Linux distribution
- Git
- CMake (version 3.10 or higher)
- Qt 6
- OpenSSL
- Google Test (for unit testing)

### Cloning the Repository

Clone the project repository from GitHub:

```bash
git clone https://github.com/MihyarH/Chat-Application-with-Client-Server.git
cd Chat-Application-with-Client-Server
```
