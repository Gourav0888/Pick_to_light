# Pick to Light System using PIC18F4580

A warehouse automation system using **PIC18F4580** microcontrollers with **CAN** and **UART** communication. The system facilitates efficient product picking using client-server architecture.

## Overview

This project implements a **Pick to Light** system with two nodes:  
- **Client Node** (Shop floor operator)  
- **Server Node** (Main warehouse controller)

Used for real-time stock tracking and pick guidance.

## Features

- **Client Node:**
  - Sets `u_st` (universal stock) and `p_id` (product ID)
  - Sends product info to server via **CAN protocol**

- **Server Node:**
  - Receives product info via **CAN**
  - Sends stock data to laptop via **UART**
  - Returns available stock for `p_id` back to client via **CAN**

- **Laptop Interface:**
  - Displays real-time stock data received from server

## Technologies Used

- **Microcontroller**: PIC18F4580  
- **Communication**:  
  - **CAN Protocol** (Client <-> Server)  
  - **UART** (Server <-> Laptop)  
- **IDE**: MPLAB X  
- **Language**: Embedded C  
- **Applications**: Warehouse automation, manual pick guidance

## Usage

1. Power up client and server nodes.
2. Client enters `u_st` and `p_id`.
3. Server sends and receives data accordingly.
4. Laptop displays warehouse stock data.
