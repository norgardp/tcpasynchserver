// tcpasynchserver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	unsigned int port_no{ 3333 };
	try
	{
		Server srv;
		unsigned int thread_pool_size = std::thread::hardware_concurrency() * 2;
		if (thread_pool_size == 0)
			thread_pool_size = DEFAULT_THREAD_POOL_SIZE;

		srv.Start(port_no, thread_pool_size);
		for (int i{ 0 }; i < 6; i++)
		{
			std::cout << "Listening for a connection " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}

		std::cout << "Ears closing." << std::endl;
		srv.Stop();
		std::cout << "Ears closed." << std::endl;
	}
	catch (boost::system::error_code ec)
	{
		std::cout << "Error " << ec.value() << " occurred." << std::endl;
		std::cout << "Error Message: " << ec.message() << std::endl;
	}
    return 0;
}

