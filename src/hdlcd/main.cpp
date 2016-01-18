/**
 * \file main.cpp
 * \brief 
 *
 * The hdlc-tools implement the HDLC protocol to easily talk to devices connected via serial communications
 * Copyright (C) 2016  Florian Evers, florian-evers@gmx.de
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <mutex>
#include <assert.h>
#include <boost/asio.hpp>
#include "ComPortHandlerCollection.h"
#include "ClientAcceptor.h"

int main(int argc, char **argv) {
    boost::asio::io_service io_service;
    boost::asio::signal_set signals_(io_service);
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
    signals_.async_wait([&io_service](boost::system::error_code errorCode, int signalNumber){io_service.stop();});
    
    auto l_ComPortHandlerCollection = std::make_shared<ComPortHandlerCollection>(io_service);

    ClientAcceptor l_ClientAcceptor(io_service, 10000, l_ComPortHandlerCollection);
    io_service.run(); 
    return 0;
}