#pragma once
#include <chrono>
#include <iostream>
#include <mutex>
#include <deque>
#include <thread>
#include <memory> 
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#define asio  boost::asio

#define	ServerAccept 0x10
#define	ServerDeny 0x20
#define	ServerPing 0x30
#define	AllMessage 0x40
#define ServerMessage 0x50
#define Encryption 0x60

