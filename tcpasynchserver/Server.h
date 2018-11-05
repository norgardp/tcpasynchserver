#pragma once

#include "Acceptor.h"

class Server
{
public:
	Server();
	~Server();
	void Start(unsigned int port_no, unsigned int thread_pool_size);
	void Stop();

private:
	boost::asio::io_service ios;
	std::unique_ptr<boost::asio::io_service::work> work;
	std::unique_ptr<Acceptor> acc;
	std::vector<std::unique_ptr<std::thread>> thread_pool;
};

