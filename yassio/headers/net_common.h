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

#define	ServerAccept 10
#define	ServerDeny 20
#define	ServerPing 30
#define	AllMessage 40
#define ServerMessage 50
#define Encryption 60

