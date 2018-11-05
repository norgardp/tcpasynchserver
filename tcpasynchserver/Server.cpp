#include "stdafx.h"
#include "Server.h"


Server::Server()
{
	work.reset(new boost::asio::io_service::work(ios));
}


Server::~Server()
{
}


void Server::Start(unsigned int port_no, unsigned int thread_pool_size)
{
	assert(thread_pool_size > 0);
	
	acc.reset(new Acceptor(ios, port_no));
	acc->Start();

	// create new threads
	for (unsigned int i{ 0 }; i < thread_pool_size; i++)
	{
		std::unique_ptr<std::thread> th(new std::thread([this]()
		{
			ios.run();
		}));
		thread_pool.push_back(std::move(th));
	}
}


void Server::Stop()
{
	acc->Stop();
	ios.stop();

	for (auto& th : thread_pool)
		th->join();
}
