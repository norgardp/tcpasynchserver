#pragma once

#include "Service.h"

class Acceptor
{
public:
	Acceptor(boost::asio::io_service& ios, unsigned int port_no);
	~Acceptor();
	void Start();
	void Stop();
	
private:
	void InitAccept();
	void OnAccept(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> sock);
	boost::asio::io_service& ios;
	boost::asio::ip::tcp::acceptor acceptor;
	std::atomic<bool> isStopped;
};

